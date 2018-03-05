/*
Time  : 2016/06/18
Author: Kay Yang (1025115216@qq.com)
*/


#ifndef PredictOriginalKeyUploadCommand_H
#define PredictOriginalKeyUploadCommand_H
#include "PredictCommonType.h"
#include "PredictCommand.h"
class PredictSession;
class PredictMessage;

class PredictOriginalKeyUploadCommand : public PredictCommand
{
public:
	PredictOriginalKeyUploadCommand();
	virtual ~PredictOriginalKeyUploadCommand();
protected:
	virtual void ExecuteSession(PredictSession* session);
	virtual void ParseMessage(PredictMessage* message);
private:
	char* mBytes;
	int mLength;
};

#endif
