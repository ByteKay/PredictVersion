/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/


#ifndef _PREDICTCONFIG_H
#define _PREDICTCONFIG_H

#include "HexString.h"
#include "DS_HashTable.h"
#pragma execution_character_set("utf-8")
class PredictConfigData
{
public:
	static const char* filePathname;
	static const char*  ipName;
	static const char*  portName;
	static const char*  isCheckName;
	static const char*  hasKeyFileName;
	static const char*  hasGenerateFileName;
	static const char*  keyFileName;
	static const char*  generateKeyFileName;
	static const char*  packageFileName;
	static const char*  perceptionFileName;
	static const char*  quntityThresholName;
	static const char*  sizeThresholName;
	static const char*  minSize;
	static const char*	lengthKey;
	static const char*	decreaseThreshold;
	static const char*	maxPredictNumber;
	static const char*	preIndexNumber;
	static const char*	writeTempFile;
	static const char*  maxKeyCountPerConnection;
	static const char*  compressionByName;
	static const char*  cpThreashold;
	DataStructures::HexString mDir;
	DataStructures::HexString mFilePath;	
	DataStructures::HexString mIP;
	unsigned short mPort;
	bool mIsCheck;
	bool mHasKeyFile;
	bool mHasGenerateFile;
	DataStructures::HexString mKeyFile;
	DataStructures::HexString mGenerateKeyFile;
	DataStructures::HexString mPackageFile;
	DataStructures::HexString mPerceptionFile;
	float mBKQuntityThreshold;
	float mBKSizeThreshold;
	float mBKMinSize;
	__u32 mPreIndexNumber;
	__u32 mMaxPredictNumber;
	float mDecreaseThreshold;
	bool mWriteTempFile;
	int mKeyLength;
	int mMaxKeyCountPerConnection;
	bool mCompression;
	float mCpThreashold;

	PredictConfigData()
	{
		mDir = ".";
		mFilePath = "config.xml";
		Reset();
	}

	DataStructures::HexString GetFullPathAndKeysPath()
	{
		return mDir + "/pathAndKeys.txt";
	}

	DataStructures::HexString GetFullConfigPath()
	{
		return mDir + "/config.xml";
	}

	DataStructures::HexString GetFullGeneratorPath()
	{
		return mDir + "/" + mGenerateKeyFile;
	}

	DataStructures::HexString GetFullKeyPath()
	{
		return mDir + "/" + mKeyFile;
	}

	DataStructures::HexString GetFullPackagePath()
	{
		return mDir + "/" + mPackageFile;
	}

	DataStructures::HexString GetTemp()
	{
		return mDir + "/" + "temp.txt";
	}

	DataStructures::HexString GetFullCompressionPerceptionPath()
	{
		return mDir + "/" + "compressionPerception.txt";
	}

	DataStructures::HexString GetFullPerceptionPath()
	{
		return mDir + "/" + mPerceptionFile;
	}

	void Reset()
	{
		mIP = "127.0.0.1";
		mPort = 8888;
		mIsCheck = false;
		mHasKeyFile = false;
		mKeyFile = "key.bin";
		mHasGenerateFile = true;
		mGenerateKeyFile = "generator.bin";
		mPackageFile = "df-xh-object-keys.txt";
		mPerceptionFile = "Perception.txt";
		mBKQuntityThreshold = 0.1f;
		mBKSizeThreshold = 0.8f;
		mBKMinSize = 0.0f;
		mKeyLength = 0;
		mPreIndexNumber = 5;
		mMaxPredictNumber = 15;
		mDecreaseThreshold = 0.95f;
		mWriteTempFile = false;
		mMaxKeyCountPerConnection = 5000000;
		mCompression = false;
		mCpThreashold = 1e-5f;
	}
};

class PredictConfig
{
public:
	PredictConfig(bool load = false);
	PredictConfig(const DataStructures::HexString& dir);
	~PredictConfig();
	void InitializeNamemap();
	void Save();
	void Load();
	void SetValue(const char* name, const char* value);

private:
	int GetIndexByName(const char* name);
public:
	PredictConfigData mConfigData;
	DataStructures::HashTable<DataStructures::HexString, int> mNameMap;
	bool mNeedStatistic;
};

#endif