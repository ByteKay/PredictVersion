#ifndef COCOS2D

#include "PredictConsole.h"
#include "HexString.h"
#include "./fileUtils/_fileExists.h"
#include "PredictConfig.h"
#include "./streams/DS_FileStream.h"
#include "PredictCalculate.h"
#include "PredictStatistic.h"
#include "GetTime.h"
#include "PredictPrint.h"
#include "FormatString.h"
#include "PredictProtobuf.h"
#include "Resource.pb.h"

#ifdef CHINESE_PATH
#include <QFile>
#include <QDir>
#include <QTextStream>
#endif


int initFromKeyFile(const char *keysFile, keyVectType &kVect)
{
	string buf;
	QFile f(QString::fromLocal8Bit(keysFile));
	if (f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream fin(&f);
		QString buf;
		while (!fin.atEnd())
		{
			buf = fin.readLine();
			if ((buf[0] == '0') && (buf[1]) == 'x')
			{
				keyType key;
				std::string temp = buf.toStdString();
				sscanf(temp.c_str(), "0x%llx", &key);
				if (std::find(kVect.begin(), kVect.end(), key) == kVect.end())
				{
					kVect.push_back(key);
				}
			}
		}
		f.close();
	}
	return kVect.size();
}

void PredictConsole::Calculate(int argc, char** argv)
{
	DataStructures::HexString configFile(argv[1]);
	DataStructures::HexString generatorFile(argv[2]);
	DataStructures::HexString package(argv[3]);
	DataStructures::HexString perception(argv[4]);
	int minSize = 0;
	if (argc > 5)
	{
		minSize = atoi(argv[5]);
	}
#ifdef CHINESE_PATH
	bool gexist = QFile::exists(QString::fromLocal8Bit(generatorFile.C_String()));
#else
	bool gexist = _fileExists(generatorFile.C_String());
#endif
	if (!gexist)
	{
		ClientPrint::PrintMessage("", FormatString("%s is not fount,please check it£¡", generatorFile));
	}
#ifdef CHINESE_PATH
	bool kexist = QFile::exists(QString::fromLocal8Bit(configFile.C_String()));
#else
	bool kexist = _fileExists(configFile.C_String());
#endif
	if (!kexist)
	{
		ClientPrint::PrintMessage("", FormatString("%s is not fount,please check it£¡", configFile));
	}
	if (gexist && kexist)
	{
		__u64 time = DataStructures::GetTimeNS();
		char dir[25] = { 0 };
		int ran = rand();
		sprintf(dir, "0x%llx%d", time, ran);
		DataStructures::HexString gameName(dir);
#if 0
		int length = gameName.GetLength();
		DataStructures::HexString last = gameName.SubString(length - 1, 1);
		int tempIndex = last.FindIString("/");
		if (tempIndex != -1)
		{
			gameName = gameName.SubString(0, length - 1);
		}
#endif
		PredictConfig config(gameName);
		config.mConfigData.mBKMinSize = minSize;
		// config.mConfigData.mBKSizeThreshold = 0.52f;
#if 0
		std::string fullPath;
		fullPath = getcwd(NULL, 0);
		if (!_directoryExists(config.mConfigData.mDir))
		{
			DataStructures::HexString temp = config.mConfigData.mDir;
			int index = temp.FindIString("/");
			while (index != -1)
			{
				const char* dir1 = temp.SubString(0, index);
				if (!_directoryExists(dir1))
				{
					mkdir(dir1);
				}
				chdir(dir1);
				temp = temp.SubString(index + 1);
				index = temp.FindIString("/");
			}
			if (!_directoryExists(temp))
			{
				mkdir(temp.C_String());
			}
			// mkdir(config.mConfigData.mDir);
			chdir(fullPath.c_str());
		}
#else
#ifdef CHINESE_PATH
		QDir gdir;
		if (!gdir.exists(QStringLiteral("%1").arg(config.mConfigData.mDir.C_String())))
		{
			gdir.mkpath(QStringLiteral("%1").arg(config.mConfigData.mDir.C_String()));
		}
#else
		if (!_directoryExists(config.mConfigData.mDir))
		{
			mkdir(config.mConfigData.mDir.C_String());
		}
#endif
#endif

#ifdef CHINESE_PATH
		QFile file2(QString::fromLocal8Bit(generatorFile.C_String()));
		if (file2.open(QIODevice::ReadOnly))
		{
			file2.close();
			QFile::copy(QString::fromLocal8Bit(generatorFile.C_String()), QString::fromLocal8Bit(config.mConfigData.GetFullGeneratorPath().C_String()));
		}

		QFile file1(QString::fromLocal8Bit(configFile.C_String()));
		if (file1.open(QIODevice::ReadOnly))
		{
			file1.close();
// filter keys to make new-config-file which generator-file contains all keys in new-config-file
#if 0
			QFile::copy(QString::fromLocal8Bit(configFile.C_String()), QString::fromLocal8Bit(config.mConfigData.GetFullKeyPath().C_String()));
#else
			// generator new config data 
			ServerConfig server;
			ServerConfig back;
			PredictProtobuf::ResolveByArray<ServerConfig>(configFile.C_String(), true, &server);
			std::map<keyType, int> temp;
			int indexS = server.index_size();
			for (int i = 0; i < indexS; ++i)
			{
				temp.insert(make_pair(server.index(i).key(), i));
			}
			keyVectType unique;
			initFromKeyFile(generatorFile.C_String(), unique);
			int tempSize = unique.size();
			for (int i = 0; i < tempSize; ++i)
			{
				auto it = temp.find(unique[i]);
				if (it != temp.end())
				{
					ResourceIndex* node = back.add_index();
					node->CopyFrom(server.index(it->second));
				}
			}
			temp.clear();
			back.set_version(server.version());
			back.set_packagename(server.packagename());
			back.set_url(server.url());
			back.set_filetype(server.filetype());
			
			int size = back.ByteSize();
			char* bytes = (char*)malloc(size);
			back.SerializeToArray(bytes, size);
			QFile file(QStringLiteral("%1").arg(config.mConfigData.GetFullKeyPath().C_String()));
			if (file.open(QIODevice::WriteOnly))
			{
				file.write(bytes, size);
				file.flush();
				file.close();
			}
			free(bytes);
			bytes = 0;
			server.Clear();
			unique.clear();
			back.Clear();
#endif
		}
#else
		DataStructures::FileStream stream1(configFile, "rb");
		if (stream1.CanRead())
		{
			int length = stream1.Length();
			char* bytes = (char*)malloc(length);
			stream1.Read(bytes, length);
			stream1.Close();
			DataStructures::FileStream stream2(config.mConfigData.GetFullKeyPath().C_String(), "wb");
			stream2.Write(bytes, length);
			stream2.Close();
			free(bytes);
		}
		DataStructures::FileStream stream2(generatorFile, "rb");
		if (stream2.CanRead())
		{
			int length = stream2.Length();
			char* bytes = (char*)malloc(length);
			stream2.Read(bytes, length);
			stream2.Close();
			DataStructures::FileStream stream(config.mConfigData.GetFullGeneratorPath().C_String(), "wb");
			stream.Write(bytes, length);
			stream.Close();
			free(bytes);
		}
#endif
		if (config.mConfigData.mBKMinSize == 0.0f)
		{
			PredictStatistic statictic;
			statictic.mGameName = gameName;
			statictic.Statistic(&config);
		}
		if (config.mConfigData.mBKMinSize != 0.0f)
		{
			PredictCalculate calculate;
			calculate.mGameName = gameName;
			config.mConfigData.mWriteTempFile = false;
			config.mConfigData.mCompression = true;
			calculate.Calculate(&config.mConfigData);
			ClientPrint::PrintMessage("", "calculate done \n");
#ifdef CHINESE_PATH
			QFile file3(QStringLiteral("%1").arg(config.mConfigData.GetFullPackagePath().C_String()));
			if (file3.open(QIODevice::ReadOnly))
			{
				file3.close();
				QFile::remove(QStringLiteral("%1").arg(QString::fromLocal8Bit(package.C_String())));
				QFile::copy(QStringLiteral("%1").arg(config.mConfigData.GetFullPackagePath().C_String()), QString::fromLocal8Bit(package.C_String()));
			}

			QFile file4(QStringLiteral("%1").arg(config.mConfigData.GetFullCompressionPerceptionPath().C_String()));
			if (file4.open(QIODevice::ReadOnly))
			{
				file4.close();
				QFile::remove(QStringLiteral("%1").arg(QString::fromLocal8Bit(perception.C_String())));
				// QFile::copy(QStringLiteral("%1").arg(config.mConfigData.GetFullPerceptionPath().C_String()), QString::fromLocal8Bit(perception.C_String()));
				QFile::copy(QStringLiteral("%1").arg(config.mConfigData.GetFullCompressionPerceptionPath().C_String()), QString::fromLocal8Bit(perception.C_String()));
			}
			QFile::remove(QStringLiteral("%1").arg(config.mConfigData.GetFullCompressionPerceptionPath().C_String()));
			QFile::remove(QStringLiteral("%1").arg(config.mConfigData.GetFullKeyPath().C_String()));
			QFile::remove(QStringLiteral("%1").arg(config.mConfigData.GetFullGeneratorPath().C_String()));
			QFile::remove(QStringLiteral("%1").arg(config.mConfigData.GetFullPackagePath().C_String()));
			QFile::remove(QStringLiteral("%1").arg(config.mConfigData.GetFullPerceptionPath().C_String()));
			QFile::remove(QStringLiteral("%1").arg(config.mConfigData.GetFullPathAndKeysPath().C_String()));
			QDir dir;
			dir.rmdir(QStringLiteral("%1").arg(config.mConfigData.mDir.C_String()));
#else
			DataStructures::FileStream stream3(config.mConfigData.GetFullPackagePath().C_String(), "rb");
			if (stream3.CanRead())
			{
				int length = stream3.Length();
				char* bytes = (char*)malloc(length);
				stream3.Read(bytes, length);
				stream3.Close();
				DataStructures::FileStream stream(package.C_String(), "wb");
				stream.Write(bytes, length);
				stream.Close();
				free(bytes);
			}
			DataStructures::FileStream stream4(config.mConfigData.GetFullPerceptionPath().C_String(), "rb");
			if (stream4.CanRead())
			{
				int length = stream4.Length();
				char* bytes = (char*)malloc(length);
				stream4.Read(bytes, length);
				stream4.Close();
				DataStructures::FileStream stream(perception.C_String(), "wb");
				stream.Write(bytes, length);
				stream.Close();
				free(bytes);
			}
			remove(config.mConfigData.GetFullKeyPath().C_String());
			remove(config.mConfigData.GetFullGeneratorPath().C_String());
			remove(config.mConfigData.GetFullPackagePath().C_String());
			remove(config.mConfigData.GetFullPerceptionPath().C_String());
			rmdir(config.mConfigData.mDir.C_String());
#endif
		}
		else
		{
			ClientPrint::PrintMessage("", "min size wrong calculate \n");
		}
		google::protobuf::ShutdownProtobufLibrary();
	}
}

#endif