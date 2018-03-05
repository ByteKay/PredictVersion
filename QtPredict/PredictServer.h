/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTEVENT_H
#define _PREDICTEVENT_H
#include "PredictTypeDefines.h"
#include "HexString.h"

struct PredictServerConfigData
{
	DataStructures::HexString mIP;
	__u16 mPort;
};

void Connecting(evutil_socket_t listener, short event, void *arg);
void Disconnect(struct bufferevent *bev, void *ctx);
void Reading(struct bufferevent *bev, void *ctx);
void Writing(struct bufferevent *bev, void *ctx);
void Wrong(struct bufferevent *bev, short error, void *ctx);

class PredictServer
{
public:	
	PredictServer(){}
	virtual ~PredictServer(){}
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void SetConfigData(const PredictServerConfigData& data) = 0;

public:
	PredictServerConfigData mConfigData;
};


#endif