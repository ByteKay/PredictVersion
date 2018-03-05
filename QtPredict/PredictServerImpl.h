/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/


#ifndef _PREDICTSERVERIMPLE_H
#define _PREDICTSERVERIMPLE_H

#include "PredictCommonType.h"
#include "PredictServer.h"
#include "HexCommonThread.h"

class PredictServerImpl : public PredictServer
{
public:
	PredictServerImpl();
	virtual ~PredictServerImpl();

	virtual void Start();
	virtual void Stop();
	virtual void SetConfigData(const PredictServerConfigData& data);
private:
	class ListenThread : public DataStructures::HexCommonThread
	{
	public:
		ListenThread(PredictServerImpl* owner);
		~ListenThread();
		virtual void Stop();
		virtual void Run();
	private:
		PredictServerImpl* mOwner;
	};

	ListenThread* mListenThread;
};

#endif