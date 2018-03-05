#include "PredictOriginalKeyUploadCommand.h"

#include "PredictSession.h"
#include "PredictMessage.h"
#include "./streams/DS_FileStream.h"
#include "PredictGameThread.h"
#include "PredictConfig.h"

PredictOriginalKeyUploadCommand::PredictOriginalKeyUploadCommand()
{
	mCommandId = PMT_UPLOAD_KEY;
	mBytes = 0;
	mLength = 0;
}

PredictOriginalKeyUploadCommand::~PredictOriginalKeyUploadCommand()
{
	if (mBytes)
	{
		free(mBytes);
	}
	mBytes = 0;
}

void PredictOriginalKeyUploadCommand::ExecuteSession(PredictSession* session)
{
	PredictGameThread* handle = session->GetThreadHandle();
	if (!handle->IsExistOriginalKey() && mLength)
	{
		std::string keyFile = handle->GetConfig()->mConfigData.GetFullKeyPath();
		DataStructures::FileStream stream(keyFile.c_str(), "wb");
		stream.Write(mBytes, mLength);
		stream.Close();
		handle->GetConfig()->mConfigData.mHasKeyFile = true;
		handle->StatisticKey();
	}
	if (mBytes)
	{
		free(mBytes);
	}
	mBytes = 0;
	mLength = 0;

	//PredictMessage write;
	//write.WriteINT16(PMT_GeneratorKey);
	//write.WriteBoolean(true);
	//session->WriteMessage(&write);
}

void PredictOriginalKeyUploadCommand::ParseMessage(PredictMessage* message)
{
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