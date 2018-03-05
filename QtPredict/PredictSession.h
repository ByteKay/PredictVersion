/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTSESSION_H
#define _PREDICTSESSION_H
#include "PredictCommonType.h"
#include "HexCommonThread.h"
#include "PredictGameThread.h"
#include "DS_ByteQueue.h"
#include "DS_ThreadSafeList.h"

class PredictMessage;


class PredictSession
{
public:
	PredictSession();
	PredictSession(bufferevent* channel);
	~PredictSession();
	void WriteMessage(const char* bytes, __u32 len);
	void WriteMessage(PredictMessage* message);
	void ReadMessage();
	void SetGameName(const DataStructures::HexString& gameName);
	DataStructures::HexString GetGameName();
	void SetSessionId(int sid);
	int GetSessionId();
	__u64 GetLastKeyTime();
	void SetLastKeyTime(__u64 timestamp);
	PredictGameThread* GetThreadHandle();
	void SetThreadHandle(PredictGameThread* thread);
	inline bufferevent* GetChannel(){ return mChannel; }
	bool IsNeedRemove();
	void IsNeedRemove(bool isNeedRemove);
	bool IsActive();
	int KeyCount();
	void IncreaseKeyCount(int n = 1);
private:
	void HandleMessage();
	void CreateMessages(DataStructures::List<PredictMessage*>* messages);
private:
	// first initialize mGameName
	DataStructures::HexString mGameName;
	// mOwnerhandleThread
	PredictGameThread* mOwnerhandleThread;
	// second initialize mSessionId
	int mSessionId;
	// restore the bytes read from client
	DataStructures::ByteQueue mBytes;
	// read or write bytes instance
	bufferevent* mChannel;
	// count key
	int mKeyCount;
private:
	__u64 mLastTimestamp;// for key
private:
	bool mIsNeedRemove;
};

/// maybe the manager should be owned by thread self that can control its sessions
class PredictSessionManager
{
public:
	~PredictSessionManager();
	static PredictSessionManager* Instance();
	void AddSession(PredictSession* session);
	void RemoveSession(PredictSession* session);
	bool ExistSession(PredictSession* session, int& index);
	inline DataStructures::ThreadSafeList<PredictSession*>* GetSessions()
	{
		return &mSessions;
	}
private:
	PredictSessionManager();
public:
	SimpleMutex mMutex;
private:
	DataStructures::ThreadSafeList<PredictSession*> mSessions;
};

#endif