/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTGENERATORKEY_H
#define _PREDICTGENERATORKEY_H
#include "PredictTypeDefines.h"
#include "DS_HashTable.h"
#include "DS_OrderedList.h"
#include "HexTimeCounter.h"

class PredictConfig;
class PredictCheck;
struct ThreeKeyPair
{
	ThreeKeyPair(){}
	ThreeKeyPair(__u32 sessionId, __u64 keyId, __u64 timestamp) : mSessionId(sessionId), mKeyId(keyId), mTimestamp(timestamp){}

	__u32 mSessionId;
	__u64 mKeyId;
	__u64 mTimestamp;
};

int CompareKeyTime(const __u64& time, const ThreeKeyPair& keiPair);
#ifdef ORDER_LIST
typedef DataStructures::OrderedList<__u64, ThreeKeyPair, CompareKeyTime> KEYPAIR_LISTS;
#else
typedef DataStructures::List<ThreeKeyPair> KEYPAIR_LISTS;
#endif

#ifndef HASHTABLE
typedef DataStructures::HashTable<__u32, KEYPAIR_LISTS> KEYTABLE;
typedef KEYTABLE::SimpleIterator SITR;
#else
typedef DataStructures::HashTable<__u32, KEYPAIR_LISTS> KEYTABLE;
typedef KEYTABLE::SimpleIterator SITR;
#endif

class PredictGeneratorKey
{
public:
	PredictGeneratorKey(){}
	PredictGeneratorKey(PredictConfig* mConfig);
	~PredictGeneratorKey();
	bool CheckKeysWrong(__u64& keyResult);
	void LoadFromFile(const char* fileName);
	void WriteToFile(const char* fileName, __u64 key = 0);
	// should be safe in multiple threads	
	void AppendKeyPair(__u32 sessionId, __u64 keyId, __u64 timestamp, bool needCheck);
	__u32 Size();
	void Clear();
	// __u32 GeneratorId();
	// when change game,should save firstly and clear
	void WriteAndClear(const char* fileName);
	bool IsNeedRecalculate();
	void IsNeedRecalculate(bool isNeed);
	void InitializeCheckManual();
	void InitializeCheck();
	void ResetCheck();
	void CheckTimer();
	void IsNeedCalculate(bool check);
	bool IsNeedCalculate();
	bool NeedRecheckNow();
	bool CanBeCalculate();
public:
	DataStructures::HexString mGameName;
	
private:
	KEYTABLE mKeySequence;
	HexTimeCounter mRecheck;
	float mLastDecreaseThreashold;
	PredictCheck* mCheck;
	PredictConfig* mConfig;
	HexTimeCounter mRecalculateTimer;
	bool mIsNeedCalculate;
	bool mIsNeedRecalculate;
	SimpleMutex mMutex;
	int mCount;
private:
	int mTotalSessionCount;
};

#endif