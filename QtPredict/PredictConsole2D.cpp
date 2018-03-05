#ifdef COCOS2D
#include "PredictConsole2D.h"
#include <QString>
#include <QFile>
#include "ccgamec_config.pb.h"
#include "Perception.pb.h"
#include "PerceptionNew.pb.h"
#include "PredictProtobuf.h"
#include <map>
#include <set>
#include <string>
#include "CommonTypeDefines.h"
#include <fstream>
#include "Template2D.pb.h"

using namespace std;

void TestNewPerception(QString temp)
{
	PerceptionNew perception;
	string str = temp.toStdString();
	bool flag1 = PredictProtobuf::ResolveByArray<PerceptionNew>(str.c_str(), true, &perception);
	if (!flag1)
	{
		return;
	}
	ofstream o("t.txt");
	// convert
	int nodenum = perception.nodenum();
	int nodesize = perception.nodes_size();
	o << "nodenum: " << nodenum << std::endl;
	o << "nodesize: " << nodesize << std::endl;
	for (int i = 0; i < nodesize; ++i)
	{
		o << "********* " << i << " *********" << std::endl;
		const NodeNew* node = &perception.nodes(i);
		o << "key: " << node->uniqkey() << endl;
		o << "id: " << node->id() << std::endl;
		o << "key-size: " << node->keys_size() << std::endl;
		for (int i = 0; i < node->keys_size(); ++i)
		{
			o << "         " << i << ": " << node->keys(i) << std::endl;
		}
		o << "succ-size: " << node->succinfo_size() << std::endl;
		for (int i = 0; i < node->succinfo_size(); ++i)
		{
			const SuccInfoNew* nre = &node->succinfo(i);
			o << "         " << i << ": " << nre->id() << std::endl;
			o << "         " << "  : " << nre->cp() << std::endl;
			o << "         " << "  : " << nre->isnext() << std::endl;
		}
	}
	o.close();
	perception.Clear();
}

void compressPbFile(Perception* perception, ServerConfig* server_config, PathAndKeys* pathAndKeys, QString outPath)
{
	std::map<string, __u64> pathAndKeysMap;
	int nodeSize = pathAndKeys->nodes_size();
	for (int i = 0; i < nodeSize; ++i)
	{
		const PathAndKey* node = &pathAndKeys->nodes(i);
		string path = node->path();
		if (pathAndKeysMap.find(path) == pathAndKeysMap.end())
		{
			pathAndKeysMap.insert(make_pair(path, node->key()));
		}
	}

	std::map<__u64, string> keyName; // key --> name
	int indexSize = server_config->rpfile_size();
	for (int i = 0; i < indexSize; ++i)
	{
		const RPFile* rpFile = &server_config->rpfile(i);
		string zipName = rpFile->name();
		int resoureSize = rpFile->resource_size();
		for (int j = 0; j < resoureSize; ++j)
		{
			const Resource* resour = &rpFile->resource(j);
			string tempKey = resour->path();
			if (pathAndKeysMap.find(tempKey) != pathAndKeysMap.end())
			{
				__u64 key = pathAndKeysMap[tempKey];
				if (keyName.find(key) == keyName.end())
				{
					keyName.insert(make_pair(key, zipName));
				}
			}
		}
	}
	pathAndKeysMap.clear();

	// convert
	int nodenum = perception->nodenum();
	int nodesize = perception->nodes_size();
	PerceptionNew perceptionNew;
	perceptionNew.set_nodenum(nodenum);
	for (int i = 0; i < nodesize; ++i)
	{
		NodeNew* nodeNew = perceptionNew.add_nodes();
		const Node* node = &perception->nodes(i);
		// fisrt
		nodeNew->set_id(node->id());
		nodeNew->set_uniqkey(node->uniqkey());

		// second
		std::set<string> nextZip;
		int keySize = node->keys_size();
		for (int j = 0; j < keySize; ++j)
		{
			__u64 keyId = node->keys(j);
			if (keyName.find(keyId) != keyName.end())
			{
				auto next = nextZip.insert(keyName[keyId]);
				if (next.second)
				{
					nodeNew->add_keys(keyName[keyId]);
				}
			}
		}
		int successSize = node->succinfo_size();
		for (int j = 0; j < successSize; ++j)
		{
			const SuccInfo* su = &node->succinfo(j);
			float cp = su->cp();
			if (cp > 1e-5f)
			{
				SuccInfoNew* newInfo = nodeNew->add_succinfo();
				newInfo->set_cp(cp);
				newInfo->set_id(su->id());
				newInfo->set_isnext(su->isnext());
			}
		}
		nextZip.clear();
	}
	int byteSize = perceptionNew.ByteSize();
	char* bytes = (char*)malloc(byteSize);
	perceptionNew.SerializeToArray(bytes, byteSize);
	QFile compressionFile(outPath);
	if (compressionFile.open(QIODevice::WriteOnly))
	{
		compressionFile.write(bytes, byteSize);
		compressionFile.flush();
		compressionFile.close();
	}
	free(bytes);
	perceptionNew.Clear();
	// TestNewPerception(outPath);
}

void PredictConsole2D::ConvertPerception(int argv, char** args)
{
	if (argv == 4)
	{
		QString perception = QString::fromLocal8Bit(args[1]);
		QString config = QString::fromLocal8Bit(args[2]);
		QString keypath = QString::fromLocal8Bit(args[3]);
		
		if (QFile::exists(perception) && QFile::exists(config))
		{
			Perception old;
			string str1 = perception.toStdString();
			PredictProtobuf::ResolveByArray<Perception>(str1.c_str(), true, &old);
			ServerConfig conf;
			str1 = config.toStdString();
			PredictProtobuf::ResolveByArray<ServerConfig>(str1.c_str(), true, &conf, true);
			PathAndKeys pathAndKeys;
			str1 = keypath.toStdString();
			PredictProtobuf::ResolveByArray<PathAndKeys>(str1.c_str(), true, &pathAndKeys);
			compressPbFile(&old, &conf, &pathAndKeys, perception);
			old.Clear();
			conf.Clear();
			pathAndKeys.Clear();
		}
	}
	else
	{

	}
}
#endif
