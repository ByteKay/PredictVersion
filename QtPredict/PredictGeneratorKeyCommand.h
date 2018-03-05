/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/


#ifndef _PREDICTGENERATORKEYCOMMAND_H
#define _PREDICTGENERATORKEYCOMMAND_H
#include "PredictCommonType.h"
#include "PredictCommand.h"

class PredictGeneratorKeyCommand : public PredictCommand
{
public:
	PredictGeneratorKeyCommand();
	virtual ~PredictGeneratorKeyCommand();

protected:
	virtual void ParseMessage(PredictMessage* message);
	virtual void ExecuteSession(PredictSession* session);

private:
	__u64 mKeyId;
	__u64 mTimestamp;
};

#endif