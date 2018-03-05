/*
	Time  : 2016/06/13
	Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTCOMMAND_H
#define _PREDICTCOMMAND_H
#include "PredictTypeDefines.h"
#include "DS_HashTable.h"
#include "HexCommonThread.h"
#include "DS_ThreadSafeQueue.h"
#include "SimpleMutex.h"

class PredictGameThread;
class PredictMessage;
class PredictSession;
/*
	Here, PredictCommand can be splited into BaseMessage and BaseCommand
		then messgaes derived from BaseMessage , and command derived from BaseCommand.
		Message and Command relate in the same [message|command]Id.
	thus, support a HandleInterface, reling on BaseMessage and Session 
*/
class PredictCommand
{
public:
	PredictCommand();
	virtual ~PredictCommand();
	virtual void Execute(PredictMessage* message, PredictSession* session);
	unsigned int GetId();
	void SetCurrentThread(PredictGameThread* ownerThread);
protected:
	virtual void ExecuteSession(PredictSession* session){}
	virtual void ParseMessage(PredictMessage* message){}

protected:
	__u16 mCommandId;
	PredictGameThread* mOwnerThread;
};

class PredictCommandManager
{
public:
	~PredictCommandManager();
	void Execute(PredictMessage* message, PredictSession* session);
	static PredictCommandManager* Instance();
	bool InHashTable(const DataStructures::HexString& gameName);
	void AddGameThread(const DataStructures::HexString& gameName, PredictGameThread* gameThread);
	__u32 GetSessionId(const DataStructures::HexString& gameName);
	PredictGameThread* GetThreadByName(const DataStructures::HexString& gameName);
protected:
	PredictCommandManager();
private:
	DataStructures::HashTable<DataStructures::HexString, PredictGameThread*> mGames;
};

#endif