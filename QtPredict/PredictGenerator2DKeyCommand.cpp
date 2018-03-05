#include "PredictGenerator2DKeyCommand.h"
#include "PredictMessage.h"
#include "PredictSession.h"
#include "PredictGeneratorKey.h"
#include "PredictGameThread.h"
#include "PredictPrint.h"
#include "FormatString.h"

PredictGenerator2DKeyCommand::PredictGenerator2DKeyCommand()
{
	mPath = "";
}

PredictGenerator2DKeyCommand::~PredictGenerator2DKeyCommand()
{

}

void PredictGenerator2DKeyCommand::ParseMessage(PredictMessage* message)
{
	mKeyId = message->ReadUINT64();
	mTimestamp = message->ReadUINT64();
	__u64 temp = message->ReadUINT64();
	mTimestamp = mTimestamp * 1000000 + temp;
	mSize = message->ReadINT32();
	// mPath = message->ReadString();
}

void PredictGenerator2DKeyCommand::ExecuteSession(PredictSession* session)
{
	__u32 id = session->GetSessionId();
	PredictGameThread* thread = session->GetThreadHandle();
	thread->AppendKeyPair(id, mKeyId, mTimestamp);
	thread->AppendKeySize(mKeyId, mSize, mPath);
}
