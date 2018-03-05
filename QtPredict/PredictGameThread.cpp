#include "PredictGameThread.h"
#include "PredictMessage.h"
#include "PredictCommand.h"
#include "PredictSession.h"
#include "PredictCommandFactory.h"
#include "PredictGeneratorKey.h"
#include "PredictConfig.h"
#include "PredictStatistic.h"
#include "PredictCalculate.h"
#include "PredictCheck.h"
#include "./streams/DS_FileStream.h"
#include "./fileUtils/BaseFileSystem.h"
#include "./fileUtils/_fileExists.h"
#include <direct.h>
#include "PredictPrint.h"
#include "FormatString.h"
#include "PredictProtobuf.h"

#ifdef CHINESE_PATH
#include <QString>
#include <QFile>
#include <QDir>
#endif

static const char* DIR = "./res/";
bool PredictGameThread::mNeedCheck = false;
bool PredictGameThread::mHasBeenInitialized = false;
static int ID_GENERATOR = 100000000;
static SimpleMutex mutex;

void PredictGameThread::SetNeedCheck(bool needCheck)
{
	mNeedCheck = needCheck;
	mHasBeenInitialized = !mNeedCheck;
}

PredictGameThread::PredictGameThread() : DataStructures::HexCommonThread(), mConfig(0), mIsStop(false), mCanCLear(false)
{
	mKeys = new PredictGeneratorKey(mConfig);
	mCheckSession = 0;
	mNeedStatisticKey = false;
}

PredictGameThread::PredictGameThread(const DataStructures::HexString& gameName) : DataStructures::HexCommonThread()
{
	mGameName = gameName;
	DataStructures::HexString dir(DIR);
	dir += gameName;
	mConfig = new PredictConfig(dir);
	mKeys = new PredictGeneratorKey(mConfig);
	mKeys->mGameName = gameName;
	mFlushTimer.StartTimer();
	mCheckSession = 0;
	mNeedStatisticKey = false;
}

PredictGameThread::~PredictGameThread()
{
	mIsStop = true;
	DataStructures::HexCommonThread::ThreadSleep(10);
	if (!mCanCLear)
	{
		DataStructures::HexCommonThread::Kill();
	}
	while (mMessages.Size() > 0)
	{
		delete mMessages.Pop();
	}
	mMessages.Clear();
	if (mKeys)
	{
		//__u64 key = 0;
		//bool wrong = CheckKeysWrong(key);
		//mKeys->WriteToFile(mConfig->mConfigData.GetFullGeneratorPath().C_String(), key);
		mKeys->WriteToFile(mConfig->mConfigData.GetFullGeneratorPath().C_String());
		delete mKeys;		
	}
	mKeys = 0;
	SaveKeyBin();
#ifndef COCOS2D
	mServerConfig.Clear();
#endif
	mKeyUnique.clear();
	if (mConfig)
	{
		mConfig->Save();
		delete mConfig;
	}
	mConfig = 0;
	
}

void PredictGameThread::SaveKeyBin()
{
#ifndef COCOS2D
	mKeyBinMutex.Lock();
	int size = mServerConfig.index_size();
	if (size > 0)
	{
		int size = mServerConfig.ByteSize();
		char* bytes = (char*)malloc(size);
		mServerConfig.SerializeToArray(bytes, size);
		mKeyBinMutex.Unlock(); // unlock first
		QFile file(QStringLiteral("%1").arg(mConfig->mConfigData.GetFullKeyPath().C_String()));
		if (file.open(QIODevice::WriteOnly))
		{
			file.write(bytes, size);
			file.flush();
			file.close();
		}
		free(bytes);
		bytes = 0;
	}
	else
	{
		mKeyBinMutex.Unlock();
	}
#endif
}

void PredictGameThread::NeedStatistic(bool state)
{
	mStatisticKeyMutex.Lock();
	mNeedStatisticKey = state;
	mStatisticKeyMutex.Unlock();
}

void PredictGameThread::LoadKeyBin()
{
#ifndef COCOS2D
	mKeyBinMutex.Lock();
	mServerConfig.Clear();
	PredictProtobuf::ResolveByArray(mConfig->mConfigData.GetFullKeyPath().C_String(), &mServerConfig);
	mKeyBinMutex.Unlock();
	int size = mServerConfig.index_size();
	for (int i = 0; i < size; ++i)
	{
		mKeyUnique.insert(mServerConfig.index(i).key());
		// ClientPrint::PrintMessage(mGameName, FormatString("size %d",mServerConfig.index(i).size()));
	}
	mKeyBinTimer.StartTimer();
#endif
}


PredictGeneratorKey* PredictGameThread::GetKeysContain()
{
	return mKeys;
}

bool PredictGameThread::ExistsDir(const char* dirName)
{
#ifdef CHINESE_PATH
	QDir dir;
	QString d = QStringLiteral("%1%2").arg(DIR).arg(dirName);
	QString t = dir.currentPath();
	return dir.exists(d);
#else
	DataStructures::HexString dirGame(dirName);
	dirGame = DIR + dirGame;
	return _directoryExists(dirGame.C_String());
#endif
}

void PredictGameThread::AppendKeySize(__u64 keyId, __u32 size, DataStructures::HexString path)
{
#ifndef COCOS2D
	mKeyBinMutex.Lock();
	if (mKeyUnique.insert(keyId).second)
	{
		ResourceIndex* resourceIndex = mServerConfig.add_index();
		resourceIndex->set_key(keyId);
		resourceIndex->set_size(size);
		resourceIndex->set_name(path.C_String());
		mNewKey = true;
	}
	mKeyBinMutex.Unlock();
#endif
}

bool PredictGameThread::MakeGameDir(const char* dirName)
{
#ifdef CHINESE_PATH
	QDir dir;
	bool is = dir.mkpath(QStringLiteral("%1%2").arg(DIR).arg(dirName));
	return is;
#else
	DataStructures::HexString dirGame(dirName);
	dirGame = DIR + dirGame;
	int result = mkdir(dirGame.C_String());
	return result == 0 ? true : false;
#endif
}

bool PredictGameThread::CheckKeysWrong(__u64& key)
{
	bool flag = mKeys->CheckKeysWrong(key);
	return flag;
}

bool PredictGameThread::ExistFile(const char* filePath)
{
#ifdef CHINESE_PATH
	return QFile::exists(QStringLiteral("%1").arg(filePath));
#else
	return _fileExists(filePath);
#endif
}

bool PredictGameThread::IsExistOriginalKey()
{
	return ExistFile(mConfig->mConfigData.GetFullKeyPath().C_String());
}

bool PredictGameThread::NeedPredict(PredictSession* session)
{
	int index;
	bool exist = PredictSessionManager::Instance()->ExistSession(mCheckSession, index);
	if (!exist || !mCheckSession || mCheckSession->IsNeedRemove())
	{
		mCheckSession = session;
		return true;
	}
	return false;
}

void PredictGameThread::AppendKeyPair(__u32 sessionId, __u64 keyId, __u64 timestamp)
{
	bool needCheck = false;
	if (mCheckSession && mCheckSession->GetSessionId() == sessionId)
	{
		needCheck = true;
	}
	mKeys->AppendKeyPair(sessionId, keyId, timestamp, needCheck && mNeedCheck);
}

bool PredictGameThread::IsExistGeneratorKey()
{
	return ExistFile(mConfig->mConfigData.GetFullGeneratorPath().C_String());
}

bool PredictGameThread::IsExistPerceptionKey()
{
	return ExistFile(mConfig->mConfigData.GetFullPerceptionPath().C_String());
}

void PredictGameThread::InitializeKey()
{
	if (mKeys)
	{
		mKeys->LoadFromFile(mConfig->mConfigData.GetFullGeneratorPath().C_String());
	}
}

int PredictGameThread::GeneratorSessionId()
{
	mutex.Lock();
	int id = ID_GENERATOR--;
	mutex.Unlock();
	return id;
}

void PredictGameThread::Calculate()
{
	mMutex.Lock();
	if (mConfig->mConfigData.mBKMinSize == 0.0f)
	{
		StatisticKey();
	}
	PredictCalculate calculate;
	calculate.mGameName = mGameName;
	calculate.Calculate(&mConfig->mConfigData);
	mConfig->mConfigData.mIsCheck = true;
	mMutex.Unlock();
}

void PredictGameThread::StatisticKey()
{
	PredictStatistic statisticOrigianlKeys;
	statisticOrigianlKeys.Statistic(mConfig);
}

PredictConfig* PredictGameThread::GetConfig()
{
	return mConfig;
}

void PredictGameThread::Submit(PredictMessage* message, PredictSession* session)
{
	if (!mIsStop)
	{
		mMessages.Push(new SessionMessage(message, session));
	}
}

void PredictGameThread::Run()
{
	ClientPrint::PrintMessage(mGameName, " thread start ...");
	InitializeKey();
	LoadKeyBin();
	mNewKey = false;
	while (!mIsStop)
	{
		try
		{
			/*
			// check timer
			mKeys->CheckTimer();
			// just call once
			if (mKeys->IsNeedCalculate())
			{
			// reset session
			mCheckSession = 0;
			// instance ,just for once
			Calculate();
			if (IsExistPerceptionKey())
			{
			mKeys->InitializeCheck();
			}
			}
			// judge need to recalculate and refresh check
			if (mKeys->IsNeedRecalculate())
			{
			// reset session
			mCheckSession = 0;
			Calculate();
			mKeys->ResetCheck();
			}
			*/	
			if (mNeedStatisticKey)
			{
				mStatisticKeyMutex.Lock();
				StatisticKey();
				mNeedStatisticKey = false;
				mStatisticKeyMutex.Unlock();
			}
			
			if (mNewKey && mKeyBinTimer.GetTimeSlapped() > 10000) // 10 seconds
			{
				SaveKeyBin();
				mNewKey = false;
				mKeyBinTimer.StartTimer();
			}

			if (mNeedCheck && !mHasBeenInitialized)
			{
				if (IsExistPerceptionKey() && IsExistOriginalKey())
				{
					mCheckSession = 0;
					mKeys->InitializeCheckManual();
					mHasBeenInitialized = true;
				}
			}
			bool changed = false;
			// here, it may not think about thread safety
			DataStructures::List<PredictSession*> remove;
			//static int ii = 0;
			while (mMessages.Size() > 0)
			{
				//ClientPrint::PrintMessage(mGameName, FormatString("%d", ii++));
				// execute message
				SessionMessage* message = mMessages.Pop();
				if (message->mSession->KeyCount() < mConfig->mConfigData.mMaxKeyCountPerConnection)
				{
					PredictCommand* command = PredictCommandFactory::CreateCommand(message->mMessage.mId);
					if (command)
					{
						command->Execute(&message->mMessage, message->mSession);
						message->mSession->IncreaseKeyCount();
						delete command;
						command = 0;
						changed = true;
					}
				}
				if (message)
				{
					if (message->mSession->IsNeedRemove())
					{
						remove.Push(message->mSession);
					}
					delete message;
					message = 0;
				}
			}
			if (remove.Size() > 0)
			{
				for (int i = 0; i < remove.Size(); ++i)
				{
					PredictSessionManager::Instance()->RemoveSession(remove[i]);
				}
				remove.Clear();
			}
			// need to write key into file
			__u32 timeSlapped = mFlushTimer.GetTimeSlapped();
			if ((changed && timeSlapped > 5000) || (!changed && timeSlapped > 30000))
			{
				mMutex.Lock();
				mKeys->WriteToFile(mConfig->mConfigData.GetFullGeneratorPath().C_String());
				mMutex.Unlock();
				mFlushTimer.StartTimer();
			}
		}
		catch (...)
		{
			ClientPrint::PrintMessage(mGameName, "Ö´ÐÐÓÐÎó");
		}
		DataStructures::HexCommonThread::ThreadSleep(1);
	}
	mCanCLear = true;
}

