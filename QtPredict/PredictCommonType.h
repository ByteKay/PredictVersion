/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#include <sys/types.h>
#include <event2/event-config.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>  
#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/util.h>
#include <event2/buffer.h>  
#include <event2/bufferevent.h>  

#ifndef _WIN32
#include <sys/queue.h>
#include <unistd.h>
#endif

#include <time.h>
#ifdef _EVENT_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#else
#include <netinet/in.h>  
#include <sys/socket.h>  
#include <unistd.h> 
#include <arpa/inet.h>
#endif