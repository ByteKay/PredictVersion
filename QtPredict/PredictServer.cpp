/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/


#include "PredictServer.h"
#include "PredictSession.h"
#include "PredictKeyHandleUI.h"
#include "FormatString.h"
#include "PredictPrint.h"

void Connecting(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = (struct event_base *)arg;
	struct sockaddr_in ss;
	int slen = sizeof(ss);
	int fd = accept(listener, (struct sockaddr*)&ss, &slen);
	if (fd < 0)
	{
		ClientPrint::PrintMessage("", "accept fail fd = -1.");
		return;
	}
	DataStructures::HexString ip = inet_ntoa(ss.sin_addr);
	if (ip == "127.0.0.1")
	{
		evutil_closesocket(fd);// close socket manual
		return;
	}
	ClientPrint::PrintMessage("", FormatString("someone connected, fd %d, ip: %s, port: %d", fd, ip.C_String(), ntohs(ss.sin_port)));
	struct bufferevent *bev;
	evutil_make_socket_nonblocking(fd);
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	PredictSession* session = new PredictSession(bev);
	session->SetSessionId(PredictGameThread::GeneratorSessionId());
	PredictSessionManager::Instance()->AddSession(session);
	bufferevent_setcb(bev, Reading, Writing, Wrong, session);
	bufferevent_enable(bev, EV_READ | EV_WRITE | EV_PERSIST);
}

void Disconnect(struct bufferevent *bev, void *ctx)
{
	bufferevent_free(bev);
}

void Reading(struct bufferevent *bev, void *ctx)
{
	PredictSession* session = (PredictSession*)ctx;
	session->ReadMessage();
}

void Writing(struct bufferevent *bev, void *ctx)
{
	//evbuffer* output = bufferevent_get_output(bev);
	//int len = evbuffer_get_length(output);
	//ClientPrint::GetPrint()->PrintMessage(FormatString("write bytes len : %d", len));
	//char* bytes = (char*)malloc(len);
	//bufferevent_read(bev, bytes, len);
	//bufferevent_write();
}

void Wrong(struct bufferevent *bev, short error, void *ctx)
{
	// int err = EVUTIL_SOCKET_ERROR();
	PredictSession* sesson = (PredictSession*)ctx;
	sesson->IsNeedRemove(true);
	DataStructures::HexString temp;
	if (error & BEV_EVENT_EOF)
	{
		/* connection has been closed, do any clean up here */
		// Disconnect(bev, ctx);
		temp = "BEV_EVENT_EOF";
	}
	else if (error & BEV_EVENT_ERROR)
	{
		/* check errno to see what error occurred */
		//ClientPrint::PrintMessage(sesson->GetGameName(), "BEV_EVENT_ERROR");
		temp = "BEV_EVENT_ERROR";
		//bufferevent_free(bev);
	}
	else if (error & BEV_EVENT_TIMEOUT)
	{
		/* must be a timeout event handle, handle it */
		//ClientPrint::PrintMessage(sesson->GetGameName(), "BEV_EVENT_TIMEOUT");
		temp = "BEV_EVENT_TIMEOUT";
		//bufferevent_free(bev);
	}
	struct sockaddr_in ss;
	int slen = sizeof(ss);
	int fd = bufferevent_getfd(bev);
	getpeername(bufferevent_getfd(bev), (sockaddr*)&ss, &slen);
	int success = evutil_closesocket(fd);// close socket manual
	ClientPrint::PrintMessage(sesson->GetGameName(), FormatString(" %s someone disconnect, fd %d, ip: %s, port: %d. close socket %s", temp.C_String(), fd, inet_ntoa(ss.sin_addr), ntohs(ss.sin_port), success == 0 ? "successfully" : "failed"));
	bufferevent_free(bev);
}