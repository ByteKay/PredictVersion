/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#include "PredictSession.h"
#include "PredictMessage.h"
#include "PredictCommand.h"

PredictSession::PredictSession()
{
	mChannel = 0;
	mSessionId = -1;
	mIsNeedRemove = false;
	mKeyCount = 0;
}
	
PredictSession::PredictSession(bufferevent* channel)
{
	mChannel = channel;
	mSessionId = -1;
	mIsNeedRemove = false;
	mKeyCount = 0;
}

int PredictSession::KeyCount()
{
	return mKeyCount;
}

void PredictSession::IncreaseKeyCount(int n)
{
	mKeyCount += n;
}

bool PredictSession::IsActive()
{
	if (!IsNeedRemove())
	{
		char c = 1;
		int r = bufferevent_write(mChannel, &c, 1);
		if (r < 0)
		{
			printf("write wrong 2 \n");
			return false;
		}
		else
		{
			return true;
		}
	}
	return !IsNeedRemove();
}


bool PredictSession::IsNeedRemove()
{
	return mIsNeedRemove;
}

void PredictSession::IsNeedRemove(bool isNeedRemove)
{
	mIsNeedRemove = isNeedRemove;
}

PredictSession::~PredictSession()
{
	mBytes.Clear();
	mSessionId = -1;
}

void PredictSession::WriteMessage(PredictMessage* message)
{
	int len = 0;
	char* data = message->ToPacket(len);
	bufferevent_write(mChannel, data, len);
	free(data);
}

void PredictSession::WriteMessage(const char* bytes, __u32 len)
{
	bufferevent_write(mChannel, bytes, len);
}

void PredictSession::SetSessionId(int sid)
{
	mSessionId = sid;
}

 int PredictSession::GetSessionId()
{
	return mSessionId;
}

 PredictGameThread* PredictSession::GetThreadHandle()
 {
	 return mOwnerhandleThread;
 }

 void PredictSession::SetThreadHandle(PredictGameThread* thread)
 {
	 mOwnerhandleThread = thread;
 }

 __u64 PredictSession::GetLastKeyTime()
 {
	 return mLastTimestamp;
 }

 void PredictSession::SetLastKeyTime(__u64 timestamp)
 {
	 mLastTimestamp = timestamp;
 }

void PredictSession::ReadMessage()
{
	evbuffer* input = bufferevent_get_input(mChannel);
	int len = evbuffer_get_length(input);
	char* bytes = (char*)malloc(len);
	bufferevent_read(mChannel, bytes, len);
	mBytes.WriteBytes(bytes, len);
	free(bytes);
	HandleMessage();
}

void PredictSession::SetGameName(const DataStructures::HexString& gameName)
{
	mGameName = gameName;
}

DataStructures::HexString PredictSession::GetGameName()
{
	return mGameName;
}

void PredictSession::HandleMessage()
{
	DataStructures::List<PredictMessage*> messages;
	CreateMessages(&messages);
	if (messages.Size() > 0)
	{
		int size = messages.Size();
		for (int i = 0; i < size; ++i)
		{
			// to do here, wrap in a thread
			PredictCommandManager::Instance()->Execute(messages[i], this);
			delete messages[i];
			messages[i] = 0;
		}
		messages.Clear();
	}
}

#ifndef OLD_MESSAGE
void PredictSession::CreateMessages(DataStructures::List<PredictMessage*>* messages)
{
	messages->Clear();
	char len[4] = { 0 };
	while (true)
	{
		memset(len, 0, 4);
		int remainBytes = mBytes.GetBytesWritten();
		if (remainBytes < 4)
			break;
		mBytes.ReadBytes(len, 4, true);
		int charLen = *(int*)len;
		if (remainBytes < 4 + charLen)
			break;
		PredictMessage* packet = new PredictMessage;
		messages->Push(packet);
		// discard
		mBytes.ReadBytes(len, 4, false);
		memset(len, 0, 4);
		mBytes.ReadBytes(len, 2, false);
		packet->mId = *(int*)len;
		charLen -= 2;
		if (charLen > 0)
		{
			char* d = (char*)malloc(charLen);
			mBytes.ReadBytes(d, charLen, false);
			packet->WriteBytes(d, charLen);
			free(d);
		}
		else
		{
			// just be zero
			packet->mBytes.Clear();
		}
	}
}
#else
void PredictSession::CreateMessages(DataStructures::List<PredictMessage*>* messages)
{
	messages->Clear();
	char len;
	while (true)
	{
		memset(&len, 0, sizeof(char));
		int remainBytes = mBytes.GetBytesWritten();
		if (remainBytes < sizeof(char))
			return;
		mBytes.ReadBytes(&len, sizeof(char), true);
		int charLen = len;
		if (remainBytes < sizeof(char)+charLen)
			return;
		PredictMessage* packet = new PredictMessage;
		messages->Push(packet);
		// discard
		mBytes.ReadBytes(&len, sizeof(char), false);
		packet->mId = PMT_GeneratorKey;
		if (charLen > 0)
		{
			char* d = (char*)malloc(charLen);
			mBytes.ReadBytes(d, charLen, false);
			packet->WriteBytes(d, charLen);
			free(d);
		}
		else
		{
			// just be zero
			packet->mBytes.Clear();
		}
	}
}
#endif

bool PredictSessionManager::ExistSession(PredictSession* session, int& index)
{
	DataStructures::List<PredictSession*>* temp = mSessions.LockList();
	unsigned int i = temp->GetIndexOf(session);
	bool re = i >= temp->Size();
	mSessions.ReleaseList();
	index = i;
	return !re;
}

void PredictSessionManager::RemoveSession(PredictSession* session)
{
	if (session)
	{
		DataStructures::List<PredictSession*>* temp = mSessions.LockList();
		unsigned int index = temp->GetIndexOf(session);
		bool re = index >= temp->Size();
		if (!re)
		{
			delete (*temp)[index];
			(*temp)[index] = 0;
			temp->RemoveAtIndex(index);
		}
		mSessions.ReleaseList();
	}
}

PredictSessionManager::~PredictSessionManager()
{
	DataStructures::List<PredictSession*>* temp = mSessions.LockList();
	int size = temp->Size();
	for (int i = 0; i < size; ++i)
	{
		if ((*temp)[i])
		{
			delete (*temp)[i];
			(*temp)[i] = 0;
		}
	}
	temp->Clear();
	mSessions.ReleaseList();
}

PredictSessionManager* PredictSessionManager::Instance()
{
	static PredictSessionManager sessionManager;
	return &sessionManager;
}

void PredictSessionManager::AddSession(PredictSession* session)
{
	mSessions.Push(session);
}

PredictSessionManager::PredictSessionManager()
{

}