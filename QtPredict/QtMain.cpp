/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#define TEST 0

#include <string>

#ifndef CONSOLE
#include "PredictServerimpl.h"
#include <QtWidgets/QApplication>
#include "PredictMainWindow.h"
#include "./fileUtils/_fileExists.h"
#include <QDir>
#include <QMessageBox>
#include "FormatString.h"
#include "Resource.pb.h"
#include "Perception.pb.h"
#else
#ifndef COCOS2D
#include "PredictConsole.h"
#endif
#include "CommonTypeDefines.h"

#endif

#if TEST
#include "PredictProtobuf.h"
#include "Resource.pb.h"
#include "Perception.pb.h"
#include "PredictMessage.h"
#include "PredictKMeans.h"
#include "PredictGeneratorKey.h"
#include <vector>

void TestProtobuf()
{
	ServerConfig serverConfig;
	PredictProtobuf::ResolveByArray<ServerConfig>("test.pb", &serverConfig);
	qDebug("index size : %d \n", serverConfig.index_size());
	Perception perception;
	PredictProtobuf::ResolveByArray<Perception>("Perception.txt", &perception);
	qDebug("node number : %d \n", perception.nodenum());
}

void TestServer()
{
	static PredictServerImpl serverImpl;
	PredictServerConfigData configData;
	configData.mIP = "127.0.0.1";
	configData.mPort = 9000;
	serverImpl.SetConfigData(configData);
	serverImpl.Start();
}

void test8()
{
	std::vector<int> source;
	source.push_back(2);
	source.push_back(3);
	source.push_back(4);
	source.push_back(5);
	source.push_back(6);
	source.push_back(7);
	source.push_back(8);
	std::vector<int> era;
	era.push_back(3);
	era.push_back(5);
	for (int i = era.size() - 1; i >= 0; --i)
	{
		std::vector<int>::iterator it_tmep = source.begin() + era[i];//  std::find(source.begin(), source.end(), era[i]);
		if (it_tmep != source.end())
		{
			source.erase(it_tmep);
		}
	}
	int size = source.size();
	for (int i = 0; i < size; ++i)
	{
		qDebug("%d \n", source[i]);
	}
	source.clear();
	era.clear();
}
//#ifndef OLD_MESSAGE
//void TestClient()
//{
//#ifdef WIN32
//	WSADATA wsa_data;
//	WSAStartup(0x0201, &wsa_data);
//#endif
//	// build socket
//	unsigned short port = 9000;
//	char* ip = "172.10.1.24";
//	struct sockaddr_in my_address;
//	memset(&my_address, 0, sizeof(my_address));
//	my_address.sin_family = AF_INET;
//	// my_address.sin_addr.s_addr = inet_pton(AF_INET, ip, );// htonl(0x7f000001); // 127.0.0.1
//	inet_pton(AF_INET, ip, &my_address.sin_addr.s_addr);
//	my_address.sin_port = htons(port);
//	struct event_base* base = event_base_new();
//	evutil_socket_t fd;
//	fd = socket(AF_INET, SOCK_STREAM, 0);
//	if (fd < -1)
//	{
//		printf("ERROR FD!\n");
//		return;
//	}
//	struct bufferevent* conn = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
//	int enable = 1;
//	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(enable)) < 0)
//		printf("ERROR: TCP_NODELAY SETTING ERROR!\n");
//	bufferevent_enable(conn, EV_WRITE);
//	if (bufferevent_socket_connect(conn, (struct sockaddr*)&my_address, sizeof(my_address)) == 0)
//		printf("connect success\n");
//
//	PredictMessage temp;
//	temp.WriteINT16(PMT_SET_GAME_NAME);
//	temp.WriteString("test_game");
//	DataStructures::HexString str = temp.ReadAllBytes();
//	PredictMessage message;
//	int len = str.GetLength();
//	message.WriteINT32(len);
//	message.WriteBytes(str.C_String(), len);
//	bufferevent_write(conn, message.ReadAllBytes().C_String(), message.GetLength());
//
//	//int total = 26;
//	//short id = 1;
//	//char wtr[30] = { 0 };
//
//	//unsigned long long keyId = 1000LLU;
//	//unsigned long long second = 100LLU;
//	//unsigned long long umill = 5000000LLU;
//	//memcpy(wtr, &total, 4);
//	//memcpy(wtr + 4, &id, 2);
//	//memcpy(wtr + 6, &keyId, 8);
//	//memcpy(wtr + 14, &second, 8);
//	//memcpy(wtr + 22, &umill, 8);
//	//// start to send data
//	//bufferevent_write(conn, wtr, 30);
//
//	// check the output evbuffer
//	struct evbuffer* output = bufferevent_get_output(conn);
//	len = evbuffer_get_length(output);
//	printf("output buffer has %d bytes left\n", len);
//	event_base_dispatch(base);
//
//
//
//	bufferevent_free(conn);
//	event_base_free(base);
//	printf("Client program is over\n");
//#ifdef WIN32
//	WSACleanup();
//#endif
//}
//#endif


void CleanSmallOrBigSamples()
{
	KMEANS_SOURCE source;
	KMEANS_GROUP result;
	int groups = 3;
	source.Insert(1.f, KMeansData(0, 1.f), true);
	source.Insert(2.f, KMeansData(1, 2.f), true);
	source.Insert(10.f, KMeansData(2, 10.f), true);
	source.Insert(5.f, KMeansData(3, 5.f), true);
	source.Insert(10.f, KMeansData(4, 10.f), true);
	source.Insert(8.f, KMeansData(5, 8.f), true);
	source.Insert(11.f, KMeansData(6, 11.f), true);
	source.Insert(10.f, KMeansData(7, 10.f), true);
	source.Insert(12.f, KMeansData(8, 12.f), true);
	source.Insert(13.f, KMeansData(9, 13.f), true);
	source.Insert(10.f, KMeansData(10, 10.f), true);
	source.Insert(9.f, KMeansData(11, 9.f), true);
	source.Insert(10.f, KMeansData(12, 10.f), true);
	source.Insert(18.f, KMeansData(13, 18.f), true);
	source.Insert(20.f, KMeansData(14, 20.f), true);
	source.Insert(15.f, KMeansData(15, 23.f), true);

	KMeansGroup::KMeans(&source, groups, &result);
	source.Clear();
	int size = result.Size();
	if (size == groups)
	{
		int groups0 = result[0].Size();
		int groups1 = result[1].Size();
		int groups2 = result[2].Size();
		int groups0Occu = groups0 * 1.0f / (groups0 + groups1 + groups2);
		int groups1Occu = groups1 * 1.0f / (groups0 + groups1 + groups2);
		int groups2Occu = groups2 * 1.0f / (groups0 + groups1 + groups2);
		std::vector<int> eraseIndex;

		{
			float max = 0.8f * result[1].At(0).mQuntity;
			KMeansGroup* group = &result[0];
			for (int i = 0; i < groups0; ++i)
			{
				qDebug("%d -> %d ", 0, group->mIndexGroup[i].mIndex);
				if (group->mIndexGroup[i].mQuntity < max)
				{
					// erase
					eraseIndex.push_back(group->mIndexGroup[i].mIndex);
				}
			}
		}		
		{
			KMeansGroup* group = &result[1];
			for (int i = 0; i < groups1; ++i)
			{
				qDebug("%d -> %d ", 1, group->mIndexGroup[i].mIndex);
			}
		}

		{
			float min = 1.5f * result[1].At(groups1 - 1).mQuntity;
			KMeansGroup* group = &result[2];
			for (int i = 0; i < groups2; ++i)
			{
				qDebug("%d -> %d ", 2, group->mIndexGroup[i].mIndex);
				if (group->mIndexGroup[i].mQuntity > min)
				{
					// erase
					eraseIndex.push_back(group->mIndexGroup[i].mIndex);
				}
			}
		}

		{
			int size = eraseIndex.size();
			if (size >= 1)
			{
				for (int i = 0; i < size; ++i)
				{
					qDebug("%d ", eraseIndex[i]);
				}
			}
		}
		eraseIndex.clear();
	}
	result.Clear();
}

void Test()
{

	//char temp[20] = { 0 };
	//sprintf(temp, "%d", 1);
	//int s = 0;
	//FormatScanfString(temp, "%d", &s);
	//printf("");
}
#endif

#ifdef Test
#include "PredictMessage.h"
class TestThread : public DataStructures::HexCommonThread
{
public:
	TestThread(){}
	~TestThread(){}
	bool IsStop()
	{
		return stop;
	}

	virtual void Run()
	{
		stop = false;
		evutil_socket_t fd;
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd < -1)
		{
			printf("ERROR FD!\n");
			return;
		}
		conn = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
		int enable = 1;
		if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(enable)) < 0)
			printf("ERROR: TCP_NODELAY SETTING ERROR!\n");
		bufferevent_enable(conn, EV_WRITE);
		if (bufferevent_socket_connect(conn, (struct sockaddr*)&my_address, sizeof(my_address)) == 0)
			printf("connect success\n");
		// DataStructures::HexString game = FormatString("test_game_%d", i);
		DataStructures::HexString game = "test";
		{
			PredictMessage temp;
			temp.WriteINT16(PMT_SET_GAME_NAME);
			temp.WriteString(game);
			temp.WriteString("test_key");
			temp.WriteBoolean(false);
			int len;
			char* data = temp.ToPacket(len);
			if (data)
			{
				bufferevent_write(conn, data, len);
				free(data);
				len = 0;
			}
		}
		Sleep(0);
		for (int i = 0; i < 10000; ++i)
		{
			PredictMessage key;
			key.WriteINT16(PMT_GeneratorKey);
			key.WriteUINT64(i);
			key.WriteUINT64(i);
			int len;
			char* data = key.ToPacket(len);
			if (data)
			{
				bufferevent_write(conn, data, len);
				free(data);
				len = 0;
			}
		}
		stop = true;
	}
	bool stop;
	struct event_base* base;
	struct sockaddr_in* my_address;
	struct bufferevent* conn;
};

void TestClient(char** argv)
{
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif
	// build socket
	unsigned short port = 8888;
	char* ip = "172.10.1.24";
	struct sockaddr_in my_address;
	memset(&my_address, 0, sizeof(my_address));
	my_address.sin_family = AF_INET;
	// my_address.sin_addr.s_addr = inet_pton(AF_INET, ip, );// htonl(0x7f000001); // 127.0.0.1
	inet_pton(AF_INET, ip, &my_address.sin_addr.s_addr);
	my_address.sin_port = htons(port);
	struct event_base* base = event_base_new();
	const int count = 2;
	struct bufferevent*  conns[count];
	for (int i = 0; i < count; ++i)
	{
		evutil_socket_t fd;
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd < -1)
		{
			printf("ERROR FD!\n");
			return;
		}
		struct bufferevent* conn = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
		conns[i] = conn;
		int enable = 1;
		if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(enable)) < 0)
			printf("ERROR: TCP_NODELAY SETTING ERROR!\n");
		bufferevent_enable(conn, EV_WRITE);
		if (bufferevent_socket_connect(conn, (struct sockaddr*)&my_address, sizeof(my_address)) == 0)
			printf("connect success\n");
		// DataStructures::HexString game = FormatString("test_game_%d", i);
		DataStructures::HexString game = argv[1];
		{
			PredictMessage temp;
			temp.WriteINT16(PMT_SET_GAME_NAME);
			temp.WriteString(game);
			temp.WriteString("test_key");
			temp.WriteBoolean(false);
			int len;
			char* data = temp.ToPacket(len);
			if (data)
			{
				bufferevent_write(conn, data, len);
				free(data);
				len = 0;
			}
		}
		Sleep(0);
		for (int i = 0; i < 10000; ++i)
		{
			PredictMessage key;
			key.WriteINT16(PMT_GeneratorKey);
			key.WriteUINT64(i);
			key.WriteUINT64(i);
			int len;
			char* data = key.ToPacket(len);
			if (data)
			{
				bufferevent_write(conn, data, len);
				free(data);
				len = 0;
			}
		}
	}

	event_base_dispatch(base);
	Sleep(1000);
	
	event_base_free(base);
	for (int i = 0; i < count; ++i)
	{
		bufferevent_free(conns[i]);
	}
	printf("Client program is over\n");
#ifdef WIN32
	WSACleanup();
#endif
}

#endif

bool ContainChinese(const std::string& data)
{
	const char *str = data.c_str();
	int len = data.length();
	for (int i = 0; i < len - 1; ++i)
	{
		if (str[i] >= 0 && str[i] <= 127)
		{
			continue;
		}
		else
		{
			return true;
		}

	}
	return false;
}
#ifndef COCOS2D
BOOL _ExitFlag = 0;
BOOL WINAPI ConsoleHandler(DWORD msgType)
{
	if (msgType == CTRL_C_EVENT)
	{
		printf("Ctrl-C!\n");
		_ExitFlag = 1;
		return TRUE;
	}
	else if (msgType == CTRL_CLOSE_EVENT)
	{
		printf("Close console window!\n");
		_ExitFlag = 1;
		return TRUE;
	}
	return FALSE;
}
#endif

#include "DS_List.h"
#include <QTextCodec>
#include "PredictChinesePath.h"
#include "PredictCheck.h"
#include "PredictConsole2D.h"

int main(int argc, char** argv)
{
#ifdef Test
	TestClient(argv);
	getchar();
	return 0;
#endif
	//SetConsoleCtrlHandler(ConsoleHandler, true);
#ifndef CONSOLE
#ifndef CHINESE_PATH
	QString str = QDir::currentPath();
	std::string temp = str.toStdString();
	if (ContainChinese(temp))
	{
		QMessageBox customMsgBox;
		customMsgBox.setWindowTitle("中文");
		customMsgBox.setText(FormatString("%s, 包含中文路径，请改成 英文路径", temp.c_str()));
		customMsgBox.exec();
		return 0;
	}
	if (!_directoryExists("./res"))
	{
		mkdir("./res");
	}
#else
	//QTextCodec* codec = QTextCodec::codecForName("utf8");
	//QTextCodec::setCodecForCStrings(codec);
	//QTextCodec::setCodecForTr(codec);
	//QTextCodec::setCodecForLocale(codec);
	//QString fileName = QFileDialog::getOpenFileName();
	//if (!fileName.isEmpty())
	//{

	//	const char*p = fileName.toStdString().data();
	//	qDebug("%s", p);
	//	QString temp = tr(p);
	//	ui->lineEdit->setText(temp);
	//}
	QDir dir;
	if (!dir.exists("./res"))
	{
		dir.mkpath("./res");
	}
#endif
	DataStructures::HexString temp1 = "0.0.0.0";
	__u16 port = 8888;
	if (argc >= 2)
	{
		temp1 = argv[1];
	}
	if (argc >= 3)
	{
		port = atoi(argv[2]);
	}
	QApplication a(argc, argv);
	PredictMainWindow w;
	w.mIP = temp1;
	w.mPort = port;
	w.mApp = &a;
	w.show();
	w.StartServer();
	a.exec();
#else
#ifndef COCOS2D
	if (argc > 4)
	{
		PredictConsole::Calculate(argc, argv);
	}
#else
	//__u64 temp1;
	//__u64 temp2;
	//__u64 temp3;
	//__u64 temp4;
	//char* testStr1 = "0x178e23";
	//char* testStr2 = "178e23";
	//sscanf(testStr1, "0x%llx", &temp1);
	//sscanf(testStr1, "%llx", &temp2);
	//sscanf(testStr2, "0x%llx", &temp3);
	//sscanf(testStr2, "%llx", &temp4);

	//printf("%lld %lld %lld %lld \n", temp1, temp2, temp3, temp4);
	
	if (argc > 2)
	{
		PredictConsole2D::ConvertPerception(argc, argv);
	}
#endif
	else if (argc == 1)
	{
		printf("wrong specialized arguments,please acoording to the follow rule: \n");
		printf("   config_file_path key_file_path out_package_path out_perception_path (either absolute path or relate path is okay):\n");
		printf("          calculate final result files and write them(df - xh - object - keys.txt and Perception.txt) down into the specialized out_game_name_dir \n");
	}
	// for (; !_ExitFlag; Sleep(300));
#endif
	
	return 0;
}