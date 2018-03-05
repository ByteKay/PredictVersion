/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTMESSAGE_H
#define _PREDICTMESSAGE_H
#include "PredictTypeDefines.h"
#include "DS_ByteQueue.h"
#include "HexString.h"

enum PredictMessageType
{
	PMT_NULL = 0,
	PMT_GeneratorKey = 1,
	PMT_SET_GAME_NAME = 2,
	PMT_UPLOAD_KEY = 3,
	PMT_GeneratorKey2D = 4,
	PMT_UNITY = 5
};
class PredictMessage
{
public:
	PredictMessage();
	PredictMessage(const PredictMessage& message);
	PredictMessage& operator=(const PredictMessage& message);
	~PredictMessage();

	void WriteBytes(const char* datas, int len);
	void WriteString(const DataStructures::HexString& str);

	void WriteINT16(__s16 value);
	void WriteINT32(__s32 value);
	void WriteINT64(__s64 value);
	void WriteUINT16(__u16 value);
	void WriteUINT32(__u32 value);
	void WriteUINT64(__u64 value);
	void WriteFloat(float value);
	void WriteDouble(double value);
	void WriteBoolean(bool value);
	
	bool ReadBytes(char* datas, int len, bool peek = false);
	DataStructures::HexString ReadString(bool peek = false);
	__s16 ReadINT16(bool peek = false);
	__s32 ReadINT32(bool peek = false);
	__s64 ReadINT64(bool peek = false);
	__u16 ReadUINT16(bool peek = false);
	__u32 ReadUINT32(bool peek = false);
	__u64 ReadUINT64(bool peek = false);
	float ReadFloat(bool peek = false);
	double ReadDouble(bool peek = false);
	bool ReadBoolen(bool peek = false);

	DataStructures::HexString ReadAllBytes();
	__u32 GetLength();
	char* ToPacket(int& len);
public:
	short mId;
	DataStructures::ByteQueue mBytes;
};


#endif