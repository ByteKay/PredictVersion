/*
Time  : 2016/06/18
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef PredictGameThread_H
#define PredictGameThread_H

#include "PredictCommonType.h"
#include "HexCommonThread.h"
#include "DS_ThreadSafeQueue.h"
#include "HexTimeCounter.h"
#include "PredictMessage.h"
#include "SimpleMutex.h"
#include "Resource.pb.h"

class PredictSession;
class PredictConfig;
class PredictGeneratorKey;

class PredictGameThread : public DataStructures::HexCommonThread
{
public:
	PredictGameThread();
	PredictGameThread(const DataStructures::HexString& gameName);
	virtual ~PredictGameThread();
	void Submit(PredictMessage* message, PredictSession* session);
	virtual void Run();
	PredictGeneratorKey* GetKeysContain();
	PredictConfig* GetConfig();
	void StatisticKey();
	void Calculate();
	static int GeneratorSessionId();
	void InitializeKey();
	void AppendKeyPair(__u32 sessionId, __u64 keyId, __u64 timestamp);
	bool NeedPredict(PredictSession* session);
	void RefreshConfig();
	bool IsExistOriginalKey();
	bool IsExistPerceptionKey();
	bool IsExistGeneratorKey();
	static bool ExistFile(const char* filePath);
	static bool ExistsDir(const char* dirName);
	static bool MakeGameDir(const char* dirName);	
	static int GeneratorId();
	void AppendKeySize(__u64 keyId, __u32 size, DataStructures::HexString path);
	void SaveKeyBin();
	void LoadKeyBin();
	void NeedStatistic(bool state);
public:
#ifndef COCOS2D
	ServerConfig mServerConfig;
#endif
	std::set<__u64> mKeyUnique;
	SimpleMutex mKeyBinMutex;
	HexTimeCounter mKeyBinTimer;
	bool mNewKey;
public:
	bool mNeedStatisticKey;
	SimpleMutex mStatisticKeyMutex;
private:
	bool CheckKeysWrong(__u64& key);
	struct SessionMessage
	{
		SessionMessage(){}
		PredictMessage mMessage;
		PredictSession* mSession;
		SessionMessage& operator = (const SessionMessage& other)
		{
			mMessage = other.mMessage;
			mSession = other.mSession;
			return *this;
		}
		SessionMessage(PredictMessage* message, PredictSession* session) : mMessage(*message), mSession(session){}
	};
	PredictGeneratorKey* mKeys;
	PredictConfig* mConfig;
	DataStructures::HexString mGameName;
	SimpleMutex mMutex;
private:
	HexTimeCounter mFlushTimer;
	bool mIsStartCheck;
	bool mIsStop;
	bool mCanCLear;
	
private:
	DataStructures::ThreadSafeQueue<SessionMessage*> mMessages;
	PredictSession* mCheckSession;
public:
	static void SetNeedCheck(bool needCheck);
	static bool mNeedCheck;
	static bool mHasBeenInitialized;
};

#endif