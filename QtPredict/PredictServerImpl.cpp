/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#include "PredictServerImpl.h"
#include "PredictSession.h"
#include "PredictPrint.h"
#include "FormatString.h"
struct event ev;
struct timeval tv; 
bool g_break = false;
evutil_socket_t listener;
struct event_base *base;
struct event *listener_event;

// holy shit. in multiple threads, should add a timer to break event_base in the same thread.
// otherwise in different threads, there is no effect when calling event_base_loopbreak
void time_cb(int fd, short _event, void *argc)
{
	if (g_break && base)
	{
		event_del(listener_event);
		evutil_closesocket(listener);
		event_base_loopbreak(base);
	}
	else
	{
		// it will do work that check the channel is active by write one byte to client
		// if something is wrong, maybe the connection is disconnected
		DataStructures::ThreadSafeList<PredictSession*>* sessions = PredictSessionManager::Instance()->GetSessions();
		DataStructures::List<PredictSession*>* list = sessions->LockList();
		int size = list->Size();
		for (int i = 0; i < size; ++i)
		{
			PredictSession* session = (*list)[i];
			if (!session->IsNeedRemove())
			{
				bool res = session->IsActive();
				if (!res)
				{
					ClientPrint::PrintMessage("", "write wrong 1");
				}
			}
		}
		sessions->ReleaseList();
		event_add(&ev, &tv);
	}
}

PredictServerImpl::ListenThread::ListenThread(PredictServerImpl* owner) : DataStructures::HexCommonThread(), mOwner(owner)
{

}

PredictServerImpl::ListenThread::~ListenThread()
{
	Stop();
	mOwner = 0;
}

// may call Kill() directly to Stop
void PredictServerImpl::ListenThread::Stop()
{
	if (base)
	{
		g_break = true;
		// current thread sleep 2 ms
		// the timer interval time is 1 ms
		DataStructures::HexCommonThread::ThreadSleep(10);
		if (base)
		{
			DataStructures::HexCommonThread::Kill();
			event_base_free(base);
			base = 0;
		}
	}
}

void PredictServerImpl::ListenThread::Run()
{
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif
	struct sockaddr_in sin;
	base = event_base_new();
	if (!base)
		return;
	
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(mOwner->mConfigData.mIP);
	sin.sin_port = htons(mOwner->mConfigData.mPort);
	listener = socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_socket_nonblocking(listener);
	int one = 1;
	int neg = 0;
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&neg, sizeof(neg));
	setsockopt(listener, SOL_SOCKET, SO_KEEPALIVE, (char*)&one, sizeof(one));
	setsockopt(listener, IPPROTO_TCP, TCP_NODELAY, (char*)&one, sizeof(one));
	if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		ClientPrint::PrintMessage("", FormatString("端口 %d 绑定错误，检查是否已经被绑定", mOwner->mConfigData.mPort));
		return;
	}
	if (listen(listener, 16) < 0)
	{
		ClientPrint::PrintMessage("", "listen error");
		return;
	}
	listener_event = event_new(base, listener, EV_READ | EV_PERSIST | EV_WRITE, Connecting, (void*)base);
	event_add(listener_event, NULL);
	tv.tv_sec = 1;
	// micro second
	tv.tv_usec = 0;
	evtimer_assign(&ev, base, time_cb, 0);
	event_add(&ev, &tv);
	event_base_dispatch(base);
	if (base)
	{
		event_del(&ev);
		event_base_free(base);
		base = 0;
	}
#ifdef WIN32
	WSACleanup();
#endif
}

PredictServerImpl::PredictServerImpl() : mListenThread(0)
{
}

PredictServerImpl::~PredictServerImpl()
{
	Stop();
}

void PredictServerImpl::Start()
{
	// stop first
	Stop();
	if (!mListenThread)
	{
		mListenThread = new ListenThread(this);
	}
	mListenThread->Start();
}

void PredictServerImpl::Stop()
{
	if (mListenThread)
	{
		delete mListenThread;
	}
	mListenThread = 0;
}

void PredictServerImpl::SetConfigData(const PredictServerConfigData& data)
{
	mConfigData = data;
}
