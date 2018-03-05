/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/
#include "PredictCommonType.h"
#include "PredictCalculate.h"
#include "CommonTypeDefines.h"
#include "PredictConfig.h"
#include "PredictProtobuf.h"
#include "PredictKeyHandleUI.h"
#include "FormatString.h"
#include "Resource.pb.h"
#include "Perception.pb.h"
#include "PredictPrint.h"
#include "DS_OrderedList.h"
#include "PredictKMeans.h"
#include "PerceptionNew.pb.h"
#ifdef CHINESE_PATH
#include <QTextStream>
#include <QString>
#include <QFile>
#endif

PredictCalculate::PredictCalculate()
{

}

PredictCalculate::~PredictCalculate()
{
	Clear();
}

void PredictCalculate::Clear()
{
	totalKeySet.clear();
	objIdVect.clear();
	objIdCom.clear();
	objIdRel.clear();
	int s = objRelMat.size();
	for (int i = 0; i < s; ++i)
	{
		objRelMat[i].clear();
	}
	objRelMat.clear();
	s = objMat.size();
	for (int i = 0; i < s; ++i)
	{
		objMat[i].clear();
	}
	objMat.clear();
	id2iMap.clear();
	i2idMap.clear();

#ifndef OLD
	keyMatVectType::iterator itrB = learnMat.begin();
	keyMatVectType::iterator itrE = learnMat.end();
	while (itrB != itrE)
	{
		itrB->clear();
		itrB++;
	}
#else
	keyMatMatVectType::iterator itrB = learnMat.begin();
	keyMatMatVectType::iterator itrE = learnMat.end();
	while (itrB != itrE)
	{
		int size = itrB->size();
		for (int i = 0; i < size; ++i)
		{
			keyMatVectType* items = &(itrB[i]);
			int iSize = items->size();
			for (int j = 0; j < iSize; ++j)
			{
				vector<keyVectType>* item = &(items[j]);
				int jSize = item->size();
				for (int k = 0; k < jSize; ++k)
				{
					item[k].clear();
				}
				item->clear();
			}
			items->clear();
		}
		itrB->clear();
		itrB++;
	}
#endif
	learnMat.clear();
	keyInfoMap.clear();
	picKeySet.clear();
	allObjVect.clear();

	int size = mIndexMatSet.size();
	for (int i = 0; i < size; ++i)
	{
		mIndexMatSet[i].clear();
	}
	mIndexMatSet.clear();

	size = cpMat.size();
	for (int i = 0; i < size; ++i)
	{
		cpMat[i].clear();
	}
	cpMat.clear();

	id2kMapType::iterator itr = id2kMap.begin();
	while (itr != id2kMap.end())
	{
		itr->second.clear();
		++itr;
	}
	id2kMap.clear();
}

#ifndef OLD
int PredictCalculate::initFromKeyFile(const char *keysFile, keyMatVectType &kMatVect)
{
	string buf;
	keyVectType kVect;
	QFile f(QStringLiteral("%1").arg(keysFile));
	if (f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream fin(&f);
		QString buf;
		int count = 0;
		while (!fin.atEnd())
		{
			buf = fin.readLine();
			
			if (((buf[0] == 'n') && (buf[4] == ':')) || ((buf[1] == 'n') && buf[5] == ':'))
			{
				if (kVect.size() != 0 && (buf[9] == '0' || buf[9] == '0'))
				{
					
				}
			}
			else if ((buf[0] == '0') && (buf[1]) == 'x')
			{
				keyType key;
				std::string temp = buf.toStdString();
				sscanf(temp.c_str(), "0x%llx", &key);
				if (keyInfoMap.find(key) != keyInfoMap.end()) // remove the keys in generator but not in config. this line may be commented because it does not affect. suggest to add it
				{
					if (std::find(kVect.begin(), kVect.end(), key) == kVect.end())
					{
						kVect.push_back(key);
						count++;
					}
				}
			}
			else
			{
				kMatVect.push_back(kVect);
				kVect.clear();
			}
		}
		f.close();
		ClientPrint::PrintMessage(mGameName, FormatString("total count : %d", count));
		if (kVect.size() > 0)
		{
			kMatVect.push_back(kVect);
			kVect.clear();
		}	
		if (kMatVect.empty())
		{
			return -1;
		}
	}
	return 0;
}
#else
int PredictCalculate::initFromKeyFile(const char *keysFile, keyMatMatVectType &mat)
{
	keyMatVectType kMatVect;
	string buf;
	keyVectType kVect;
#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(keysFile));
	if (f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream fin(&f);
		QString buf;
		int count = 0;
		while (!fin.atEnd())
		{  
			buf = fin.readLine();
			if (((buf[0] == 'n') && (buf[4] == ':')) || ((buf[1] == 'n') && buf[5] == ':'))
			{
				if (kVect.size() != 0 && (buf[9] == '0' || buf[9] == '0'))
				{
					kMatVect.push_back(kVect);
				}
			}
			else if ((buf[0] == '0') && (buf[1]) == 'x')
			{
				keyType key;
				std::string temp = buf.toStdString();
				sscanf(temp.c_str(), "0x%llx", &key);
				kVect.push_back(key);
				count++;
			}
			else
			{
				kMatVect.push_back(kVect);
				mat.push_back(kMatVect);
				kVect.clear();
				kMatVect.clear();
			}
		}  
		ClientPrint::PrintMessage(mGameName, FormatString("total count : %d", count));
		if (kVect.size() > 0)
		{
			kMatVect.push_back(kVect);
			mat.push_back(kMatVect);
			kVect.clear();
			kMatVect.clear();
		}
		f.close();
		if (mat.empty())
		{
			return -1;
		}
	}

#else
	ifstream fin(keysFile);
	if (!fin || !fin.is_open())
	{
		ClientPrint::PrintMessage(mGameName, FormatString("Can't open %s", keysFile));
		return -1;
	}
	while (getline(fin, buf))
	{
		if (((buf[0] == 'n') && (buf[4] == ':')) || ((buf[1] == 'n') && buf[5] == ':'))
		{
			if (kVect.size() != 0)
			{
				kMatVect.push_back(kVect);
			}
		}
		else if ((buf[0] == '0') && (buf[1]) == 'x')
		{
			keyType key;
			sscanf(buf.c_str(), "0x%llx", &key);
			kVect.push_back(key);
		}
		else
		{
			kMatVect.push_back(kVect);
			mat.push_back(kMatVect);
			kVect.clear();
			kMatVect.clear();
		}
	}
	if (kVect.size() > 0)
	{
		kMatVect.push_back(kVect);
		mat.push_back(kMatVect);
		kVect.clear();
		kMatVect.clear();
	}
	fin.close();
	if (mat.empty())
	{
		return -1;
	}
#endif
	return 0;
}
#endif

#include "Template2D.pb.h"

void PredictCalculate::parseConfig(const ServerConfig &server_config, keyInfoMapType &keyInfoMap, keySetType &keySet)
{
	ClientPrint::PrintMessage(mGameName, FormatString("total keys: %d", server_config.index_size()));
	PathAndKeys pathAndKeys;
	for (int i = 0; i < server_config.index_size(); i++)
	{
		const ResourceIndex &resourceIndex = server_config.index(i);
		infoType info;
		info.size = resourceIndex.size();
		info.isPicture = false;
		PathAndKey* pathAndkey = pathAndKeys.add_nodes();
		std::string name = resourceIndex.name();

		{
			keyType key = resourceIndex.key();
			pathAndkey->set_path(name);
			pathAndkey->set_key(key);
			if (resourceIndex.has_ispicture())
			{
				if (resourceIndex.ispicture() != 0 && resourceIndex.ispicture() != 2)
				{
					info.isPicture = true;
					keySet.insert(key);
				}
			}
			keyInfoMap.insert(make_pair(key, info));
		}
	}
	QFile file(QStringLiteral("%1").arg(configData->GetFullPathAndKeysPath().C_String()));
	if (file.open(QIODevice::WriteOnly))
	{
		int size = pathAndKeys.ByteSize();
		char* datas = (char*)malloc(size);
		pathAndKeys.SerializeToArray(datas, size);
		file.write(datas, size);
		free(datas);
		file.close();
	}
}

bool PredictCalculate::getKeyInfo(const char *configFile, keyInfoMapType &keyInfoMap, keySetType &keySet)
{
	ServerConfig server_config;
	bool flag = PredictProtobuf::ResolveByArray<ServerConfig>(configFile, &server_config);
	if (flag)
	{
		parseConfig(server_config, keyInfoMap, keySet);
		server_config.Clear();
	}
	return flag;
}

#ifndef OLD
void PredictCalculate::getAllObjects(keyMatVectType &learnMat, keyInfoMapType &keyInfoMap, objVectType &objVect, objMatType &objMat)
{
	std::vector<int> needRemoveIndex;
	objVect.clear();
	for (int i = 0; i < learnMat.size(); i++)
	{
		keyVectType& keyVect = learnMat[i];
		objVectType learnObjVect;
		for (int k = 0; k < keyVect.size(); k++)
		{
			keyType key = keyVect[k];
			keyInfoMapType::iterator it = keyInfoMap.find(key);
			if (it != keyInfoMap.end())
			{
				if (it->second.size >= configData->mBKMinSize)
				{
					if (find(objVect.begin(), objVect.end(), key) == objVect.end())
					{
						objVect.push_back(key);
					}
					learnObjVect.push_back(key);
				}
			}
		}
		if (learnObjVect.size() <= 1)
		{
			needRemoveIndex.push_back(i);
			continue;
		}
		objMat.push_back(learnObjVect);
		learnObjVect.clear();
	}
	ClientPrint::PrintMessage(mGameName, FormatString("There are %d  objects in %d", objVect.size(), learnMat.size()));
	int size = needRemoveIndex.size();
	int to = learnMat.size();
	if (size > 0)
	{
		for (int i = size - 1; i >= 0; --i)
		{
			ClientPrint::PrintMessage(mGameName, FormatString("  %d invalid", needRemoveIndex[i]));
			learnMat.erase(learnMat.begin() + needRemoveIndex[i]);
		}
		needRemoveIndex.clear();
	}
	ClientPrint::PrintMessage(mGameName, FormatString("There are %.4f invalidate samplers", size * 1.0f / to));
}
#else
void PredictCalculate::getAllObjects(keyMatMatVectType &learnMat, keyInfoMapType &keyInfoMap, objVectType &objVect, objMatType &objMat)
{
	std::vector<int> needRemoveIndex;
	objVect.clear();
	for (int i = 0; i < learnMat.size(); i++)
	{
		keyMatVectType& kMatVect = learnMat[i];
		objVectType learnObjVect;
		for (int j = 0; j < kMatVect.size(); j++)
		{
			keyVectType& keyVect = kMatVect[j];
			for (int k = 0; k < keyVect.size(); k++)
			{
				keyType key = keyVect[k];
				keyInfoMapType::iterator it = keyInfoMap.find(key);
				if (it != keyInfoMap.end())
				{
					if (it->second.size >= configData->mBKMinSize)
					{
						if (find(objVect.begin(), objVect.end(), key) == objVect.end())
						{
							objVect.push_back(key);
						}
						learnObjVect.push_back(key);
					}
				}
			}
		}
		if (learnObjVect.size() <= 1)
		{
			needRemoveIndex.push_back(i);
			continue;
		}
		objMat.push_back(learnObjVect);
		learnObjVect.clear();
	}
	ClientPrint::PrintMessage(mGameName, FormatString("There are %d  objects in %d", objVect.size(), learnMat.size()));
	int size = needRemoveIndex.size();
	int to = learnMat.size();
	if (size > 0)
	{
		for (int i = size - 1; i >= 0; --i)
		{
			learnMat.erase(learnMat.begin() + needRemoveIndex[i]);
		}
		needRemoveIndex.clear();
	}
	ClientPrint::PrintMessage(mGameName, FormatString("There are %.4f invalidate samplers", size * 1.0f / to));
}
#endif

void PredictCalculate::calcObjectSize(objVectType &allObjVect, keyInfoMapType &keyInfoMap)
{
	unsigned int totalSize = 0;
	for (int i = 0; i < allObjVect.size(); i++)
	{
		objIdType objId = allObjVect[i];
		keyType key = objId;
		totalSize += keyInfoMap[key].size;
	}
	ClientPrint::PrintMessage(mGameName, FormatString("Objects size: %d", totalSize));
}

void PredictCalculate::writeObjectsInfoToFile(objVectType &objVect, keyInfoMapType &keyInfoMap, bool isDebug)
{
	const char* fileName = configData->mDir + "/" + "objects-info.txt";
#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(fileName));
	if (f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream fout(&f);
		unsigned int objectNum = objVect.size();
		ClientPrint::PrintMessage(mGameName, FormatString("There are %d  objects", objectNum));
		for (int i = 0; i < objectNum; i++)
		{
			objIdType objId = objVect[i];
			if (isDebug)
			{
				ClientPrint::PrintMessage(mGameName, FormatString("object 0x%llx , size: %d", objId, keyInfoMap[objId].size));
			}
			fout << "0x" << hex << objId << endl;
		}
		f.close();
	}
	
#else
	ofstream fout(fileName);
	if (!fout)
	{
		ClientPrint::PrintMessage(mGameName, "open output file objects-info.txt fail");
		return;
	}
	ostream::fmtflags old = cout.flags();
	unsigned int objectNum = objVect.size();
	ClientPrint::PrintMessage(mGameName, FormatString("There are %d  objects", objectNum));
	for (int i = 0; i < objectNum; i++)
	{
		objIdType objId = objVect[i];
		if (isDebug)
		{
			ClientPrint::PrintMessage(mGameName, FormatString("object 0x%llx , size: %d", objId, keyInfoMap[objId].size));
		}
		fout << "0x" << hex << objId << endl;
	}
	cout.flags(old);
	fout.close();
#endif
}

void PredictCalculate::setIdIndexMap(objVectType &objVect, bool isDebug)
{
	ostream::fmtflags old = cout.flags();
	id2iMap.clear();
	i2idMap.clear();
	indexType index = 0;
	for (objVectType::iterator it = objVect.begin(), eit = objVect.end(); it != eit; it++, index++)
	{
		objIdType objId = *it;
		if (isDebug)
		{
			cout << "index of id 0x" << hex << objId << " is " << dec << index << endl;
		}
		id2iMap.insert(make_pair(objId, index));
		i2idMap.insert(make_pair(index, objId));
	}
	cout.flags(old);
}

void PredictCalculate::printObjVect(objVectType &objVect, bool isPrintIndex)
{
	//ostream::fmtflags old = cout.flags();
	std::stringstream temp;
	for (int i = 0; i < objVect.size(); i++)
	{
		objIdType objId = objVect[i];
		temp << " " << setw(3) << dec << id2iMap[objId];
		//if (isPrintIndex) 
		//{
		//	cout << " " << setw(3) << dec << id2iMap[objId];
		//}
		//else 
		//{
		//	cout << " 0x" << hex << objId;
		//}
	}
	ClientPrint::PrintMessage(mGameName, FormatString("%s", temp.str().c_str()));
	temp.clear();
	//cout << endl;
	//cout.flags(old);
}

void PredictCalculate::printObjMat(objMatType &objMat)
{
	//ostream::fmtflags old = cout.flags();
	for (int i = 0; i < objMat.size(); i++)
	{
		objVectType& objVect = objMat[i];
		ClientPrint::PrintMessage(mGameName, FormatString("learn from %d, objVect(%d): ", i, objVect.size()));
		printObjVect(objVect, true);
	}
	//cout.flags(old);
}

void PredictCalculate::updateIterator(mIndexSetType::iterator &it, int step)
{
	for (int i = 0; i < step; i++)
	{
		it++;
	}
}

void PredictCalculate::writeGraphToFile(const char *fileName, mIndexMatSetType &indexMatSet, bool isColor)
{
#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(fileName));
	if (f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream fout(&f);

#else
	ofstream fout(fileName);
	if (!fout)
	{
		ClientPrint::PrintMessage(mGameName, "open output file");
		return;
	}
#endif
	fout << "digraph{" << endl;
	fout << "nodes = " << indexMatSet.size() << endl;
	for (int i = 0; i < indexMatSet.size(); i++)
	{
		mIndexSetType& indexSet = indexMatSet[i];
		objIdType objId = i2idMap[i];
		if (isColor)
		{
			string color = "green";
			//fout << "\"0x" << getHexIdStr(objId) << "\" [style=filled, color=\"" << color << "\"]" <<  endl;
			fout << i << " [style=filled, color=\"" << color.c_str() << "\"]" << endl;
		}
		for (mIndexSetType::iterator it = indexSet.begin(), eit = indexSet.end(); it != eit;)
		{
			//objIdType nextObjId = i2idMap[*it];
			//fout << "\"0x" << getHexIdStr(objId) << "\" -> \"0x" << getHexIdStr(nextObjId) << "\"" << endl;
			fout << i << " -> " << *it << endl;
			updateIterator(it, indexSet.count(*it));
		}
	}
	fout << "}" << endl;
	
#ifdef CHINESE_PATH
	fout.flush();
	f.close();
	}
#else
	fout.close();
#endif
}

void PredictCalculate::genGraphForObjMat(objMatType &objMat, mIndexMatSetType &indexMatSet, bool isWriteToFile)
{
	for (int i = 0; i < objMat.size(); i++)
	{
		objVectType& objVect = objMat[i];
		for (int j = 1; j < objVect.size(); j++)
		{
			indexType preIndex = id2iMap[objVect[j - 1]];
			indexType curIndex = id2iMap[objVect[j]];
			indexMatSet[preIndex].insert(curIndex);
		}
	}
	if (configData->mWriteTempFile)
	{
		const char* fileName = configData->mDir + "/" + "objects-graph.dot";
		writeGraphToFile(fileName, indexMatSet, false);
	}
}

int PredictCalculate::getRemained(indexMatType &visitedMat)
{
	int objNum = visitedMat.size();
	int remained = 0;
	for (int i = 0; i < objNum; i++)
	{
		for (int j = 0; j < objNum; j++)
		{
			if (i != j && (visitedMat[i][j] == 0))
			{
				remained++;
			}
		}
	}
	return remained;
}

int PredictCalculate::updateCpMat(mIndexMatSetType &mIndexMatSet, cpMatType &cpMat, indexMatType &visitedMat)
{
	int learnNum = objMat.size();
	int objNum = cpMat.size();
	for (int i = 0; i < objNum; i++)
	{
		cpVectType &cpVect = cpMat[i];
		for (int j = 0; j < learnNum; j++)
		{
			objVectType& objVect = objMat[j];
			cpType lastCp = 1.0f;
			int start = 0;
			for (start = 0; start < objVect.size() - 1; start++)
			{
				indexType index = id2iMap[objVect[start]];
				if (index == i) {
					lastCp = cpVect[id2iMap[objVect[start + 1]]];
					break;
				}
			}
			for (int k = start + 1; k < objVect.size() - 1; k++)
			{
				indexType index1 = id2iMap[objVect[k]];
				indexType index2 = id2iMap[objVect[k + 1]];
				mIndexSetType& indexSet = mIndexMatSet[index1];
				if ((visitedMat[index1][index2] == 1) && (i != index2))
				{
					cpType cp = (cpType)indexSet.count(index2) / learnNum;
					if (cp > 1.0f)
					{
						cp = 1.0f;
					}
					if (visitedMat[i][index2] == 0)
					{
						cpVect[index2] = lastCp * cp * configData->mDecreaseThreshold;
						lastCp = cpVect[index2];
						visitedMat[i][index2] = 2;
					}
					else if (i == index1) 
					{
						lastCp = cpVect[index2];
					}
					else
					{
						lastCp = lastCp * cp * configData->mDecreaseThreshold;
						if (lastCp > cpVect[index2] && visitedMat[i][index2] == 2)
						{
							cpVect[index2] = lastCp;
						}
						else
						{

						}
					}
				}
			}
		}
	}
	int remained = getRemained(visitedMat);
	return remained;
}


void PredictCalculate::initCpMat(mIndexMatSetType &mIndexMatSet, cpMatType &cpMat)
{
	int objNum = cpMat.size();
	for (int i = 0; i < objNum; i++)
	{
		cpMat[i].resize(objNum);
		for (int j = 0; j < objNum; j++)
		{
			cpMat[i][j] = 0.0f;
		}
	}
	indexMatType visitedMat(objNum);
	for (int i = 0; i < objNum; i++)
	{
		visitedMat[i].resize(objNum);
		for (int j = 0; j < objNum; j++)
		{
			visitedMat[i][j] = 0;
		}
	}
	for (int i = 0; i < mIndexMatSet.size(); i++)
	{
		mIndexSetType* indexSet = &mIndexMatSet[i];
		for (mIndexSetType::iterator it = indexSet->begin(), eit = indexSet->end(); it != eit;)
		{
			indexType index = *it;
			int cnt = indexSet->count(index);
			cpType cp = (cpType)cnt / indexSet->size();
			cpMat[i][index] = cp;
			visitedMat[i][index] = 1;
			updateIterator(it, cnt);
		}
	}
	int remained = updateCpMat(mIndexMatSet, cpMat, visitedMat);
	int size = visitedMat.size();
	for (int i = 0; i < size; ++i)
	{
		visitedMat[i].clear();
	}
	visitedMat.clear();
}

void PredictCalculate::writeCpMatToFile(cpMatType &cpMat, bool isDebug)
{
	const char* fileName = configData->mDir + "/" + "cond-prop.txt";
#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(fileName));
	if (f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream fout(&f);
#else
	ofstream fout(fileName);
	if (!fout) {
		ClientPrint::PrintMessage(mGameName, "open output file");
		return;
	}
#endif
	int objectNum = cpMat.size();
	fout << "objects = " << objectNum << endl;
	for (int i = 0; i < objectNum; i++)
	{
		for (int j = 0; j < objectNum; j++)
		{
			cpType condProb = cpMat[i][j];
			if (condProb > 0.0f)
			{
				if (isDebug)
				{
					cout << "P(" << j << "|" << i << "): " << condProb << endl;
				}
				fout << "P(" << j << "|" << i << "): " << condProb << endl;
			}
		}
	}
#ifdef CHINESE_PATH
	fout.flush();
	f.close();
}
#else
	fout.close();
#endif
}

void PredictCalculate::mergeObjectKey(keyVectType &baseKeyVect, keyVectType &newKeyVect)
{
	for (int i = 0; i < newKeyVect.size(); i++)
	{
		keyType key = newKeyVect[i];
		if (find(baseKeyVect.begin(), baseKeyVect.end(), key) == baseKeyVect.end())
		{
			baseKeyVect.push_back(key);
		}
	}
}
#ifndef OLD
void PredictCalculate::getIdKeyMap(keyMatVectType &keyMatVect, keyInfoMapType &keyInfoMap, objVectType &allObjVect, id2kMapType &id2kMap)
{
	int learnNum = keyMatVect.size();
#if 0
	keyMatVectType keyMatVect(learnNum);
	for (int i = 0; i < learnNum; i++)
	{
		keyMatVectType& kMatVect = learnMat[i];
		for (int j = 0; j < kMatVect.size(); j++)
		{
			keyVectType& keyVect = kMatVect[j];
			for (int k = 0; k < keyVect.size(); k++)
			{
				keyType key = keyVect[k];
				if (keyInfoMap.find(key) != keyInfoMap.end())
				{
					keyMatVect[i].push_back(key);
				}
			}
		}
	}
#endif
#if 0
	for (int i = 0; i < learnNum; i++)
	{
		keyVectType& keyVect = keyMatVect[i];
		keyVectType objKeyVect;
		keyType last_key = (__u64)-1;// added by kay 20160902
		for (int j = 0; j < keyVect.size(); j++)
		{
			keyType key = keyVect[j];
			objKeyVect.push_back(key);
			if (find(allObjVect.begin(), allObjVect.end(), key) != allObjVect.end())
			{
				objIdType objId = key;
				if (id2kMap.find(objId) == id2kMap.end())
				{
					id2kMap.insert(make_pair(objId, objKeyVect));
				}
				else
				{
					mergeObjectKey(id2kMap[objId], objKeyVect);
				}
				objKeyVect.clear();
				last_key = key;
			}
		}
		if (last_key != (__u64)-1)
		{
			mergeObjectKey(id2kMap[last_key], objKeyVect);
		}
		objKeyVect.clear();
	}
#else
	/*
	define:
		00010000100001000100100000
		where 0 is small key and 1 is big key
	step:
		1 the first big key 1 binding previous and latter small keys
		2 the left big key 1 binding the latter small keys
	result:
		00010000
		10000
		1000
		100
		100000
	*/
	for (int i = 0; i < learnNum; i++)
	{
		keyVectType& keyVect = keyMatVect[i];
		keyVectType objKeyVect;
		vector<keyType> keys;
		for (int j = 0; j < keyVect.size(); j++)
		{
			keyType key = keyVect[j];
			objKeyVect.push_back(key);
			if (find(allObjVect.begin(), allObjVect.end(), key) != allObjVect.end())
			{
				keys.push_back(key);
				int size = keys.size();
				if (size > 1)
				{
					objIdType objId = keys[size - 2];
					if (id2kMap.find(objId) == id2kMap.end())
					{
						id2kMap.insert(make_pair(objId, objKeyVect));
					}
					else
					{
						mergeObjectKey(id2kMap[objId], objKeyVect);
					}
					objKeyVect.clear();
				}
			}
		}
		// handle last key, binding the left objKeyVect
		int size = keys.size();
		if (size > 0)
		{
			objIdType objId = keys[size - 1];
			if (id2kMap.find(objId) == id2kMap.end())
			{
				id2kMap.insert(make_pair(objId, objKeyVect));
			}
			else
			{
				mergeObjectKey(id2kMap[objId], objKeyVect);
			}
			objKeyVect.clear();
		}

		keys.clear();
	}
#endif
}
#else
void PredictCalculate::getIdKeyMap(keyMatMatVectType &learnMat, keyInfoMapType &keyInfoMap, objVectType &allObjVect, id2kMapType &id2kMap)
{
	int learnNum = learnMat.size();
	keyMatVectType keyMatVect(learnNum);
	for (int i = 0; i < learnNum; i++)
	{
		keyMatVectType& kMatVect = learnMat[i];
		for (int j = 0; j < kMatVect.size(); j++)
		{
			keyVectType& keyVect = kMatVect[j];
			for (int k = 0; k < keyVect.size(); k++)
			{
				keyType key = keyVect[k];
				if (keyInfoMap.find(key) != keyInfoMap.end())
				{
					keyMatVect[i].push_back(key);
				}
			}
		}
	}

	for (int i = 0; i < learnNum; i++)
	{
		keyVectType& keyVect = keyMatVect[i];
		keyVectType objKeyVect;
		for (int j = 0; j < keyVect.size(); j++)
		{
			keyType key = keyVect[j];
			objKeyVect.push_back(key);
			if (find(allObjVect.begin(), allObjVect.end(), key) != allObjVect.end())
			{
				objIdType objId = key;
				if (id2kMap.find(objId) == id2kMap.end())
				{
					id2kMap.insert(make_pair(objId, objKeyVect));
				}
				else
				{
					mergeObjectKey(id2kMap[objId], objKeyVect);
				}
				objKeyVect.clear();
			}
		}
		objKeyVect.clear();
	}
	int size = keyMatVect.size();
	for (int i = 0; i < size; ++i)
	{
		keyMatVect[i].clear();
	}
	keyMatVect.clear();
}
#endif

void PredictCalculate::printKeyInfo(keyInfoMapType &keyInfoMap)
{
	const char* fileName = configData->mDir + "/" + "big-objects.txt";
	unsigned int picCount = 0;
	unsigned int bigObjCount = 0;
	unsigned int totalSize = 0;
	unsigned int bigObjectsSize = 0;

#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(fileName));
	if (f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream fout(&f);
#else
	ofstream fout(fileName);
	if (!fout)
	{
		ClientPrint::PrintMessage(mGameName, "open output file");
		return;
	}
#endif
	// ostream::fmtflags old = cout.flags();

	for (keyInfoMapType::iterator it = keyInfoMap.begin(), eit = keyInfoMap.end(); it != eit; it++)
	{
		unsigned int objSize = it->second.size;
		if (it->second.isPicture)
		{
			//cout << "key: 0x" << hex << it->first << " size: 0x" << it->second.size << " isPicture: " << boolalpha << it->second.isPicture << endl;
			picCount++;
		}
		totalSize += objSize;
		if (objSize >= configData->mBKMinSize)
		{
			bigObjCount++;
			bigObjectsSize += objSize;
			//cout << "key: 0x" << hex << it->first << " size: 0x" << dec << objSize << " is a big object" << endl;
			fout << "0x" << hex << it->first << endl;
		}
	}
#ifdef CHINESE_PATH
	fout.flush();
	f.close();
}
#else
	fout.close();
#endif
	float picProp = (float)picCount / keyInfoMap.size();
	float objProp = (float)bigObjCount / keyInfoMap.size();
	float bigProp = (float)bigObjectsSize / totalSize;
	ClientPrint::PrintMessage(mGameName, FormatString("total %d keys,  %d pictures, picProp:  %.4f", keyInfoMap.size(), picCount, picProp));
	ClientPrint::PrintMessage(mGameName, FormatString("total %d keys,  %d big objects, objProp: %.4f", keyInfoMap.size(), bigObjCount, objProp));
	ClientPrint::PrintMessage(mGameName, FormatString("total %d size, big objects size: %d, bigProp: %.4f", totalSize, bigObjectsSize, bigProp));
}

void PredictCalculate::writeKeysToFile(const char *fileName, id2kMapType &id2kMap, cpVectType &cpVect, keyInfoMapType &keyInfoMap, bool isForPackage)
{
	cpIndexMapType cpIndexMap;
	keySetType visitedKeySet;
#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(fileName));
	if (f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream fout(&f);
#else
	ofstream fout(fileName);
	if (!fout)
	{
		ClientPrint::PrintMessage(mGameName, "cannot open output keys file !");
		return;
	}
#endif

	cpVect[0] = 1;
	for (int i = 0; i < cpVect.size(); i++)
	{
		cpType cp = cpVect[i];
		if (cpIndexMap.find(cp) != cpIndexMap.end())
		{
			indexVectType &indexVect = cpIndexMap[cp];
			indexVect.push_back(i);
		}
		else
		{
			indexVectType indexVect;
			indexVect.push_back(i);
			cpIndexMap.insert(make_pair(cp, indexVect));
		}
	}
	for (cpIndexMapType::iterator it = cpIndexMap.begin(), eit = cpIndexMap.end(); it != eit; it++)
	{
		indexVectType indexVect = it->second;
		for (int i = 0; i < indexVect.size(); i++)
		{
			indexType index = indexVect[i];
			objIdType objId = i2idMap[index];
			keyVectType keyVect = id2kMap[objId];
			if (!isForPackage) {
				fout << "node: 0x" << hex << index << endl;
			}
			for (int j = 0; j < keyVect.size(); j++)
			{
				keyType key = keyVect[j];
				if (visitedKeySet.find(key) == visitedKeySet.end())
				{
					fout << "0x" << hex << key << endl;
					visitedKeySet.insert(key);
				}
			}
		}
	}
#ifdef CHINESE_PATH
	fout.flush();
	f.close();
}
#else
	fout.close();
#endif
	visitedKeySet.clear();
	cpIndexMapType::iterator itrB = cpIndexMap.begin();
	cpIndexMapType::iterator itrE = cpIndexMap.end();
	while (itrB != itrE)
	{
		itrB->second.clear();
		++itrB;
	}
	cpIndexMap.clear();
}

void PredictCalculate::writeToPbFile(const char *fileName, objVectType &objVect, id2kMapType &id2kMap, cpMatType &cpMat, mIndexMatSetType &indexMatSet)
{
	Perception perception;
	perception.set_nodenum(objVect.size());
	Node *pbNode;
	for (int i = 0; i < objVect.size(); i++)
	{
		pbNode = perception.add_nodes();
		indexType index = i;
		objIdType objId = objVect[index];
		pbNode->set_id(i);
		pbNode->set_uniqkey(objId);
		keyVectType keyVect = id2kMap[objId];
		for (int j = 0; j < keyVect.size(); j++)
		{
			pbNode->add_keys(keyVect[j]);
		}
		cpVectType cpVect = cpMat[i];
		SuccInfo *succInfo;
		for (int k = 0; k < cpVect.size(); k++)
		{
			succInfo = pbNode->add_succinfo();
			succInfo->set_id(k);
			succInfo->set_cp(cpVect[k]);
			mIndexSetType indexSet = indexMatSet[i];
			if (indexSet.find(k) != indexSet.end())
			{
				succInfo->set_isnext(true);
			}
		}
	}
#ifdef CHINESE_PATH
	QFile file(QStringLiteral("%1").arg(fileName));
	if (file.open(QIODevice::WriteOnly))
	{
		int size = perception.ByteSize();
		char* datas = (char*)malloc(size);
		perception.SerializeToArray(datas, size);
		file.write(datas, size);
		free(datas);
		file.close();
	} 
#else
	DataStructures::FileStream fileS(fileName, "wb");
	if (fileS.CanWrite())
	{
		int size = perception.ByteSize();
		char* datas = (char*)malloc(size);
		perception.SerializeToArray(datas, size);
		fileS.Write(datas, size);
		fileS.Close();
		free(datas);
	}
#endif
	ClientPrint::PrintMessage(mGameName, FormatString("nodeNum: %d nodes size: %d", perception.nodenum(), perception.nodes_size()));
	ClientPrint::PrintMessage(mGameName, "write pb file successfully !");
	perception.Clear();
}

void PredictCalculate::CleanSmallOrBigSamples()
{
#ifdef OLD
	KMEANS_SOURCE source;
	int size = learnMat.size();
	for (int i = 0; i < size; ++i)
	{
		int qun = 0;
		int size2 = learnMat[i].size();
		for (int j = 0; j < size2; ++j)
		{
			qun += learnMat[i][j].size();
		}
		source.Insert(qun, KMeansData(i, qun), true);
	}
	KMEANS_GROUP result;
	int groups = 3;
	KMeansGroup::KMeans(&source, groups, &result);
	source.Clear();
	size = result.Size();
	if (size == groups)
	{
		std::vector<int> eraseIndex;
		if (size == groups)
		{
			int groups0 = result[0].Size();
			int groups1 = result[1].Size();
			int groups2 = result[2].Size();
			int groups0Occu = groups0 * 1.0f / (groups0 + groups1 + groups2);
			int groups1Occu = groups1 * 1.0f / (groups0 + groups1 + groups2);
			int groups2Occu = groups2 * 1.0f / (groups0 + groups1 + groups2);
			{
				float max = 0.75f * result[1].At(0).mQuntity;
				KMeansGroup* group = &result[0];
				for (int i = 0; i < groups0; ++i)
				{
					if (group->mIndexGroup[i].mQuntity < max)
					{
						// erase
						eraseIndex.push_back(group->mIndexGroup[i].mIndex);
					}
				}
			}

			{
				float min = 1.5f * result[1].At(groups1 - 1).mQuntity;
				KMeansGroup* group = &result[2];
				for (int i = 0; i < groups2; ++i)
				{
					if (group->mIndexGroup[i].mQuntity > min)
					{
						// erase
						eraseIndex.push_back(group->mIndexGroup[i].mIndex);
					}
				}
			}
		}

		{
			int size = eraseIndex.size();
			if (size > 1)
			{
				std::sort(eraseIndex.begin(), eraseIndex.end());
				int i = 0;
				for (i = size - 1; i >= 0; --i)
				{
					keyMatMatVectType::iterator it = learnMat.begin() + eraseIndex[i];
					if (it != learnMat.end())
					{
						int s = learnMat[eraseIndex[i]].size();
						for (int j = 0; j < s; ++j)
						{
							learnMat[i][j].clear();
						}
						learnMat[i].clear();
						learnMat.erase(it);
					}
				}
			}
		}
		eraseIndex.clear();
		ClientPrint::PrintMessage(mGameName, "clear some small samplers");
	}
	result.Clear();
#endif
}

#ifdef COMPRESSION
#include "./compression/DS_QuickLZCore.h"
void PredictCalculate::compressPbFile(const char* fileName)
{
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray byteArray = file.readAll();
		unsigned int len = byteArray.length();
		DataStructures::QuickLZCoreLevel1 compressor;
		unsigned char *compressedData;
		unsigned int compressedLength = compressor.EncodeArray((unsigned char *)byteArray.data(), len, &compressedData);
		file.close();
		ClientPrint::PrintMessage("", FormatString("before: %d, after: %d", len, compressedLength));
		QFile temp("compress.txt");
		if (temp.open(QIODevice::WriteOnly))
		{
			temp.write((const char*)compressedData, compressedLength);
			temp.flush();
			temp.close();
		}
	}
}
#endif

void TestNewPerception(PredictConfigData* configData)
{
	PerceptionNew perception;
	bool flag1 = PredictProtobuf::ResolveByArray<PerceptionNew>(configData->GetFullCompressionPerceptionPath().C_String(), &perception);
	if (!flag1)
	{
		ClientPrint::PrintMessage("", "Perception wrong, compression failed");
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

void PredictCalculate::compressPbFile()
{
	Perception perception;
	bool flag1 = PredictProtobuf::ResolveByArray<Perception>(configData->GetFullPerceptionPath().C_String(), &perception);
	if (!flag1)
	{
		ClientPrint::PrintMessage(mGameName, "Perception wrong, compression failed");
		return;
	}
	ServerConfig server_config;
	bool flag2 = PredictProtobuf::ResolveByArray<ServerConfig>(configData->GetFullKeyPath().C_String(), &server_config);
	if (!flag2)
	{
		ClientPrint::PrintMessage(mGameName, "config wrong, compression failed");
		return;
	}
	std::map<__u64, string> keyName; // key --> name
	int indexSize = server_config.index_size();
	for (int i = 0; i < indexSize; ++i)
	{
		const ResourceIndex* resourceIndex = &server_config.index(i);
		keyName[resourceIndex->key()] = resourceIndex->name();
	}

	// convert
	int nodenum = perception.nodenum();
	int nodesize = perception.nodes_size();

#if 0 // has something wrong
	for (int i = 0; i < nodesize; ++i)
	{
		const Node* node = &perception.nodes(i);
		Node* temp = const_cast<Node*>(node);
		int keysize = temp->keys_size();
		std::set<string> nameset;
		for (int j = 0; j < keysize; ++j)
		{
			string name = keyName[node->keys(j)];
			auto exist = nameset.insert(name);
			if (exist.second)
			{
				temp->add_keynames(name);
			}
		}	
		nameset.clear();
		temp->clear_keys();
	}
	
	int byteSize = perception.ByteSize();
	char* bytes = (char*)malloc(byteSize);
	perception.SerializeToArray(bytes, byteSize);
	QFile compressionFile(configData->GetFullCompressionPerceptionPath().C_String());
	if (compressionFile.open(QIODevice::WriteOnly))
	{
		compressionFile.write(bytes, byteSize);
		compressionFile.flush();
		compressionFile.close();
	}
	free(bytes);
	perception.Clear();
	keyName.clear();
#else
	PerceptionNew perceptionNew;
	perceptionNew.set_nodenum(nodenum);
	for (int i = 0; i < nodesize; ++i)
	{
		NodeNew* nodeNew = perceptionNew.add_nodes();
		const Node* node = &perception.nodes(i);
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
			if (cp > configData->mCpThreashold)
			{
				SuccInfoNew* newInfo = nodeNew->add_succinfo();
				newInfo->set_cp(cp);
				newInfo->set_id(su->id());
				newInfo->set_isnext(su->isnext());
			}
		}	
		nextZip.clear();
	}
	server_config.Clear();
	perception.Clear();
	int byteSize = perceptionNew.ByteSize();
	char* bytes = (char*)malloc(byteSize);
	perceptionNew.SerializeToArray(bytes, byteSize);
	QFile compressionFile(configData->GetFullCompressionPerceptionPath().C_String());
	if (compressionFile.open(QIODevice::WriteOnly))
	{
		compressionFile.write(bytes, byteSize);
		compressionFile.flush();
		compressionFile.close();
	}
	free(bytes);
	perceptionNew.Clear();
	// TestNewPerception(configData);
#endif
	ClientPrint::PrintMessage(mGameName, "compression successfully!");
}

void PredictCalculate::Calculate(PredictConfigData* config)
{
#ifndef OLD
	try
	{
		ClientPrint::PrintMessage(mGameName, "Calculate starting...");
		if (config->mBKMinSize == 0.0f)
		{
			ClientPrint::PrintMessage(mGameName, "minSize is wrong, confirm key.bin please");
		}
		else
		{
			Clear();
			configData = config;
			if (configData->mGenerateKeyFile == DataStructures::HexString() || configData->mKeyFile == DataStructures::HexString())
			{
				ClientPrint::PrintMessage(mGameName, "key file or generator file may be null, please set it firstly !");
				return;
			}
			if (configData->mPackageFile == DataStructures::HexString() || configData->mPerceptionFile == DataStructures::HexString())
			{
				ClientPrint::PrintMessage(mGameName, "package file or perception file may be null, please set it firstly !");
				return;
			}

			if (!getKeyInfo(configData->GetFullKeyPath().C_String(), keyInfoMap, picKeySet))
			{
				ClientPrint::PrintMessage(mGameName, "key file may be null, please set it firstly !");
				return;
			}
			else
			{
				ClientPrint::PrintMessage(mGameName, "key file loaded successfully!");
			}

			if (initFromKeyFile(configData->GetFullGeneratorPath().C_String(), learnMat) != 0)
			{
				ClientPrint::PrintMessage(mGameName, "generator file may be null, please set it firstly !");
				return;
			}
			else
			{
				ClientPrint::PrintMessage(mGameName, "generator file loaded successfully!");
			}
			// CleanSmallOrBigSamples();


			getAllObjects(learnMat, keyInfoMap, allObjVect, objMat);
			calcObjectSize(allObjVect, keyInfoMap);
			setIdIndexMap(allObjVect, false);
			int learnNum = learnMat.size();
			int objectNum = allObjVect.size();
			mIndexMatSet.resize(objectNum);
			cpMat.resize(objectNum);
			genGraphForObjMat(objMat, mIndexMatSet, false);
			initCpMat(mIndexMatSet, cpMat);
			getIdKeyMap(learnMat, keyInfoMap, allObjVect, id2kMap);
#if 0
			auto b = id2kMap.begin();
			auto e = id2kMap.end();
			int cc = 0;
			while (b != e)
			{
				cc += b->second.size();
				++b;
			}
			ClientPrint::PrintMessage(FormatString(" size = %d \n", cc), "");
#endif
			printObjMat(objMat);
			if (config->mWriteTempFile)
			{
				writeObjectsInfoToFile(allObjVect, keyInfoMap, false);
				writeCpMatToFile(cpMat, false);
				printKeyInfo(keyInfoMap);
				writeKeysToFile(configData->GetTemp().C_String(), id2kMap, cpMat[0], keyInfoMap, false);
			}
			writeKeysToFile(configData->GetFullPackagePath().C_String(), id2kMap, cpMat[0], keyInfoMap, true);
			writeToPbFile(configData->GetFullPerceptionPath().C_String(), allObjVect, id2kMap, cpMat, mIndexMatSet);
			if (configData->mCompression)
			{
				compressPbFile();
			}
#ifdef COMPRESSION
			compressPbFile(configData->GetFullPerceptionPath().C_String());
#endif
			Clear();
		}
		ClientPrint::PrintMessage(mGameName, "calculate completed!");
	}
	catch (...)
	{
		ClientPrint::PrintMessage(mGameName, "calculate failed...");
	}
#else
	try
	{
		ClientPrint::PrintMessage(mGameName, "Calculate starting...");
		if (config->mBKMinSize == 0.0f)
		{
			ClientPrint::PrintMessage(mGameName, "minSize is wrong, confirm key.bin please");
		}
		else
		{
			Clear();
			configData = config;
			if (configData->mGenerateKeyFile == DataStructures::HexString() || configData->mKeyFile == DataStructures::HexString())
			{
				ClientPrint::PrintMessage(mGameName, "key file or generator file may be null, please set it firstly !");
				return;
			}
			if (configData->mPackageFile == DataStructures::HexString() || configData->mPerceptionFile == DataStructures::HexString())
			{
				ClientPrint::PrintMessage(mGameName, "package file or perception file may be null, please set it firstly !");
				return;
			}

			if (initFromKeyFile(configData->GetFullGeneratorPath().C_String(), learnMat) != 0)
			{
				ClientPrint::PrintMessage(mGameName, "generator file may be null, please set it firstly !");
				return;
			}
			else
			{
				ClientPrint::PrintMessage(mGameName, "generator file loaded successfully!");
			}
			// CleanSmallOrBigSamples();

			if (!getKeyInfo(configData->GetFullKeyPath().C_String(), keyInfoMap, picKeySet))
			{
				ClientPrint::PrintMessage(mGameName, "key file may be null, please set it firstly !");
				return;
			}
			else
			{
				ClientPrint::PrintMessage(mGameName, "key file loaded successfully!");
			}
#if 1
			getAllObjects(learnMat, keyInfoMap, allObjVect, objMat);
			calcObjectSize(allObjVect, keyInfoMap);
			setIdIndexMap(allObjVect, false);
			int learnNum = learnMat.size();
			int objectNum = allObjVect.size();
			mIndexMatSet.resize(objectNum);
			cpMat.resize(objectNum);
			genGraphForObjMat(objMat, mIndexMatSet, false);
			initCpMat(mIndexMatSet, cpMat);
			getIdKeyMap(learnMat, keyInfoMap, allObjVect, id2kMap);
			// printObjMat(objMat);
			if (config->mWriteTempFile)
			{
				writeObjectsInfoToFile(allObjVect, keyInfoMap, false);
				// printObjMat(objMat);
				writeCpMatToFile(cpMat, false);
				printKeyInfo(keyInfoMap);
				writeKeysToFile(configData->GetTemp().C_String(), id2kMap, cpMat[0], keyInfoMap, false);
			}
			writeKeysToFile(configData->GetFullPackagePath().C_String(), id2kMap, cpMat[0], keyInfoMap, true);
			writeToPbFile(configData->GetFullPerceptionPath().C_String(), allObjVect, id2kMap, cpMat, mIndexMatSet);
#endif
			Clear();
		}
		ClientPrint::PrintMessage(mGameName, "calculate completed!");
	}
	catch (...)
	{
		ClientPrint::PrintMessage(mGameName, "calculate failed...");
	}
#endif
}