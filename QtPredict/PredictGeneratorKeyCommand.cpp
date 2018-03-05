/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/
#include "PredictGeneratorKeyCommand.h"
#include "PredictMessage.h"
#include "PredictSession.h"
#include "PredictGeneratorKey.h"
#include "PredictGameThread.h"
#include "PredictPrint.h"
#include "FormatString.h"

PredictGeneratorKeyCommand::PredictGeneratorKeyCommand() : PredictCommand()
{
	mCommandId = PMT_GeneratorKey;
}

PredictGeneratorKeyCommand::~PredictGeneratorKeyCommand()
{

}

void PredictGeneratorKeyCommand::ParseMessage(PredictMessage* message)
{
	mKeyId = message->ReadUINT64();
	mTimestamp = message->ReadUINT64();
	__u64 temp = message->ReadUINT64();
	//ClientPrint::PrintMessage("", FormatString("mTimestamp: 0x%llx, %llu, %llu\n", mKeyId, mTimestamp, temp));
	mTimestamp = mTimestamp * 1000000 + temp;
	// = message->ReadUINT64();
}

void PredictGeneratorKeyCommand::ExecuteSession(PredictSession* session)
{
	__u32 id = session->GetSessionId();
	PredictGameThread* thread = session->GetThreadHandle();
	thread->AppendKeyPair(id, mKeyId, mTimestamp);
}