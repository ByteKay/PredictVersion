#include "PredictCommandFactory.h"
#include "PredictCommand.h"
#include "PredictMessage.h"
#include "PredictGeneratorKeyCommand.h"
#include "PredictOriginalKeyUploadCommand.h"
#include "PredictSessionNameCommand.h"
#include "PredictGenerator2DKeyCommand.h"

PredictCommand* PredictCommandFactory::CreateCommand(const short messageId)
{
	PredictCommand* command = 0;
	PredictMessageType messageType = (PredictMessageType)messageId;
	switch (messageType)
	{
	case PMT_GeneratorKey:
		command = new PredictGeneratorKeyCommand;
		break;
	case PMT_SET_GAME_NAME:
		command = new PredictSessionNameCommand;
		break;
	case PMT_UPLOAD_KEY:
		command = new PredictOriginalKeyUploadCommand;
		break;
	case PMT_GeneratorKey2D:
		command = new PredictGenerator2DKeyCommand;
		break;
	default:
		break;
	}
	return command;
}