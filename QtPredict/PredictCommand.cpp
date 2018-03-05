/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/
#include "PredictCommand.h"
#include "PredictPrint.h"
#include "PredictMessage.h"
#include "PredictCommandFactory.h"
#include "PredictSession.h"
#include "PredictGameThread.h"

PredictCommand::PredictCommand()
{
	mCommandId = PMT_NULL;
}

PredictCommand::~PredictCommand()
{

}

void PredictCommand::Execute(PredictMessage* message, PredictSession* session)
{
	this->ParseMessage(message);
	this->ExecuteSession(session);
}

unsigned int PredictCommand::GetId()
{ 
	return mCommandId; 
}

void PredictCommand::SetCurrentThread(PredictGameThread* ownerThread)
{
	mOwnerThread = ownerThread;
}

PredictCommandManager::~PredictCommandManager()
{
	DataStructures::HashTable<DataStructures::HexString, PredictGameThread*>::SimpleIterator itr(&mGames);
	PredictGameThread** command = itr.GetData();
	while (command && *command)
	{
//		(*command)->Kill();
		delete *command;
		itr.FindNext();
		command = itr.GetData();
	}
	mGames.Clear();
}

bool PredictCommandManager::InHashTable(const DataStructures::HexString& gameName)
{
	return mGames.InHashTable(gameName);
}

__u32 PredictCommandManager::GetSessionId(const DataStructures::HexString& gameName)
{
	// should exists
	return mGames[gameName]->GeneratorSessionId();
}

PredictGameThread* PredictCommandManager::GetThreadByName(const DataStructures::HexString& gameName)
{
	PredictGameThread* thread = 0;
	if (mGames.InHashTable(gameName))
	{
		thread = mGames[gameName];
	}
	return thread;
}

void PredictCommandManager::AddGameThread(const DataStructures::HexString& gameName, PredictGameThread* gameThread)
{
	mGames.Add(gameName, gameThread);
}

void PredictCommandManager::Execute(PredictMessage* message, PredictSession* session)
{
	if (message->mId == PMT_SET_GAME_NAME)
	{
		PredictCommand* command = PredictCommandFactory::CreateCommand(message->mId);
		if (command)
		{
			command->Execute(message, session);
			delete command;
			command = 0;
		}
		// print error
	}
	else
	{
		DataStructures::HexString gameName = session->GetGameName();
		if (mGames.InHashTable(gameName))
		{
			mGames[gameName]->Submit(message, session);
		}
	}
}

PredictCommandManager* PredictCommandManager::Instance()
{
	static PredictCommandManager manager;
	return &manager;
}

PredictCommandManager::PredictCommandManager()
{

}
