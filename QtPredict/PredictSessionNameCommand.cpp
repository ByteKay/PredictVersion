#include "PredictSessionNameCommand.h"
#include "PredictMessage.h"
#include "PredictSession.h"
#include "PredictCommand.h"
#include "PredictConfig.h"
#include "./streams/DS_FileStream.h"
#include "PredictPrint.h"

PredictSessionNameCommand::PredictSessionNameCommand()
{
	mCommandId = PMT_SET_GAME_NAME;
	mBytes = 0;
}

PredictSessionNameCommand::~PredictSessionNameCommand()
{
	if (mBytes)
	{
		free(mBytes);
	}
	mBytes = 0;
}

void PredictSessionNameCommand::ExecuteSession(PredictSession* session)
{
	session->SetGameName(mGameName);
	DataStructures::HexString gameName = session->GetGameName();
	int sessionId = -1;

	if (gameName != DataStructures::HexString())
	{

	}

	if (gameName != DataStructures::HexString() && !PredictGameThread::ExistsDir(gameName.C_String()))
	{
		PredictGameThread::MakeGameDir(gameName.C_String());
	}

	PredictGameThread* thread = 0;
	if (gameName != DataStructures::HexString() && !PredictCommandManager::Instance()->InHashTable(gameName))
	{
		thread = new PredictGameThread(gameName);
		PredictCommandManager::Instance()->AddGameThread(gameName, thread);
		thread->Start();
	}
	if (!thread)
	{
		thread = PredictCommandManager::Instance()->GetThreadByName(gameName);
	}
	if (!thread)
	{
		ClientPrint::PrintMessage("", "游戏名传入有问题，请检查");
		return;
	}
	session->SetThreadHandle(thread);
	// session->SetSessionId(thread->GeneratorSessionId());

	if (mLength)
	{
		// thread->GetConfig()->mConfigData.mKeyFile = mGameKey;
		int len = thread->GetConfig()->mConfigData.mKeyLength;
		if (len != mLength)
		{
			std::string keyFile = thread->GetConfig()->mConfigData.GetFullKeyPath();
			DataStructures::FileStream stream(keyFile.c_str(), "wb");
			stream.Write(mBytes, mLength);
			stream.Close();
			thread->GetConfig()->mConfigData.mHasKeyFile = true;
			// thread->StatisticKey();
			thread->NeedStatistic(true);
			thread->GetConfig()->mConfigData.mKeyLength = mLength;
		}
	}
	if (mBytes)
	{
		free(mBytes);
	}
	mBytes = 0;
	mLength = 0;

	// here change the predict session, one thread retain one session to predict.not for all
	thread->NeedPredict(session);

	//bool exist = thread->IsExistOriginalKey();
	//PredictMessage write;
	//write.WriteINT16(PMT_UPLOAD_KEY);
	//write.WriteBoolean(!exist);
	//session->WriteMessage(&write);
}

void PredictSessionNameCommand::ParseMessage(PredictMessage* message)
{
	mGameName = message->ReadString();
	mGameKey = message->ReadString();
	bool exist = message->ReadBoolen();
	if (exist)
	{
		mLength = message->ReadINT32();
		if (mLength)
		{
			mBytes = (char*)malloc(mLength);
			message->ReadBytes(mBytes, mLength);
		}
	}
}