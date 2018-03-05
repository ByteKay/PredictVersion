/*
Time  : 2016/06/18
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef PredictSessionNameCommand_H
#define PredictSessionNameCommand_H
#include "PredictCommonType.h"
#include "PredictCommand.h"
class PredictSession;
class PredictMessage;

/// should be the first command
class PredictSessionNameCommand : public PredictCommand
{
public:
	PredictSessionNameCommand();
	~PredictSessionNameCommand();
protected:
	virtual void ExecuteSession(PredictSession* session);
	virtual void ParseMessage(PredictMessage* message);

private:
	DataStructures::HexString mGameName;
	DataStructures::HexString mGameKey;
	char* mBytes;
	int mLength;
};

#endif