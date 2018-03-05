/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTSTATISTIC_H
#define _PREDICTSTATISTIC_H
#include "PredictTypeDefines.h"
#include "HexString.h"
#include "Resource.pb.h"
#include "DS_OrderedList.h"

class PredictConfig;
class PredictKeyPair;
int KeyCompare(const __s32&, const PredictKeyPair&);

class PredictKeyPair
{
public:
	PredictKeyPair();
	PredictKeyPair(keyType key, __s32 size);
	~PredictKeyPair();
	PredictKeyPair& operator = (const PredictKeyPair& other);
	bool operator > (const PredictKeyPair&other);
	bool operator < (const PredictKeyPair&other);
	bool operator == (const PredictKeyPair&other);
public:
	// keyType mKeyId;
	__s32 mSize;
};

class PredictStatistic
{
public:
	PredictStatistic();
	~PredictStatistic();
	void Statistic(PredictConfig* config);
	inline __u32 BigSize(){ return mBigKeysInConfig.Size(); }
	void Clear();
public:
	DataStructures::HexString mGameName;
private:
#ifndef COCOS2D
	ServerConfig mKeysConfig;
#endif
	DataStructures::List<__s32> mBigKeysInConfig;
};

#endif