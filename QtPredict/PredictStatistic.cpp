/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/
#include "PredictCommonType.h"
#include "PredictStatistic.h"
#include "PredictProtobuf.h"
#include "PredictConfig.h"
#include "FormatString.h"
#include "PredictPrint.h"

int KeyCompare(const __s32& size, const PredictKeyPair& keyPair)
{
	if (size < keyPair.mSize)
	{
		return 1;
	}
	else if (size > keyPair.mSize)
	{
		return -1;
	}
	return 0;
}

PredictKeyPair::PredictKeyPair()
{

}

PredictKeyPair::PredictKeyPair(keyType key, __s32 size) : mSize(size)
{

}

PredictKeyPair::~PredictKeyPair()
{

}

PredictKeyPair& PredictKeyPair::operator = (const PredictKeyPair& other)
{
	if (this != &other)
	{
		// mKeyId = other.mKeyId;
		mSize = other.mSize;
	}
	return *this;
}

bool PredictKeyPair::operator > (const PredictKeyPair&other)
{
	return mSize < other.mSize;
}

bool PredictKeyPair::operator < (const PredictKeyPair&other)
{
	return mSize > other.mSize;
}

bool PredictKeyPair::operator == (const PredictKeyPair&other)
{
	return mSize == other.mSize;
}

PredictStatistic::PredictStatistic()
{

}

PredictStatistic::~PredictStatistic()
{
	Clear();
}

// #define TIME_COUNT

#ifdef TIME_COUNT
#include "HexTimeCounter.h"
#endif
int comp(const void* c1, const void* c2)
{
	int a = *(int*)c1;
	int b = *(int*)c2;
	if (a < b)
		return 1;
	if (a == b)
		return 0;
	return -1;
}

void PredictStatistic::Statistic(PredictConfig* config)
{
#ifndef COCOS2D
	try
	{
#ifdef TIME_COUNT
		HexTimeCounter count;
		count.StartTimer();
#endif
		mKeysConfig.Clear();
		std::string fileName = config->mConfigData.GetFullKeyPath();
		PredictProtobuf::ResolveByArray(fileName.c_str(), &mKeysConfig);
		int size = mKeysConfig.index_size();
		int minQuntity = size * config->mConfigData.mBKQuntityThreshold;
		__u64 totalSize = 0;
		std::vector<int> vectorList;
		for (int i = 0; i < size; ++i)
		{
			const ResourceIndex index = mKeysConfig.index(i);
			int s = index.size();
			vectorList.push_back(s);
			totalSize += s;
		}
		std::qsort(&vectorList[0], vectorList.size(), sizeof(int), comp);
		int sizeThreshold = totalSize * config->mConfigData.mBKSizeThreshold;
		int bigSize = 0;
		for (int i = 0; i < size; ++i)
		{
			if (bigSize < sizeThreshold)
			{
				bigSize += vectorList[i];
				mBigKeysInConfig.Insert(vectorList[i]);
			}
			else
			{
				break;
			}
		}
		float bO = bigSize * 1.0f / totalSize;
		int bigCount = mBigKeysInConfig.Size();
		float sO = bigCount * 1.0f / size;
		if (bigCount > 0)
		{
			__u32 minSize = mBigKeysInConfig[bigCount - 1];
			config->mConfigData.mBKMinSize = minSize;
			config->mConfigData.mBKQuntityThreshold = sO;
			ClientPrint::PrintMessage(mGameName, FormatString("total node: %d, min big size: %d", size, minSize));
		}
		vectorList.clear();
#ifdef TIME_COUNT
		int time = count.GetTimeSlapped();
		ClientPrint::PrintMessage(mGameName, FormatString("time slapped: %d", time));
#endif	
	}
	catch (...)
	{
		ClientPrint::PrintMessage(mGameName, "key.bin statistic wrong! ");
	}
#endif
}

void PredictStatistic::Clear()
{
	mBigKeysInConfig.Clear();
#ifndef COCOS2D
	mKeysConfig.Clear();
#endif
}