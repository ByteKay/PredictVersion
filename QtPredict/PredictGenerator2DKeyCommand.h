#ifndef PredictGenerator2DKeyCommand_H
#define PredictGenerator2DKeyCommand_H

#include "PredictCommonType.h"
#include "PredictCommand.h"

class PredictGenerator2DKeyCommand : public PredictCommand
{
public:
	PredictGenerator2DKeyCommand();
	virtual ~PredictGenerator2DKeyCommand();

protected:
	virtual void ParseMessage(PredictMessage* message);
	virtual void ExecuteSession(PredictSession* session);

private:
	__u64 mKeyId;
	__s32 mSize;
	__u64 mTimestamp;
	DataStructures::HexString mPath;
};
#endif
