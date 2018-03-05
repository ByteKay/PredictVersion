/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#include "PredictMessage.h"

PredictMessage::PredictMessage() : mId(-1){}

PredictMessage::~PredictMessage()
{
	mBytes.Clear();
}

PredictMessage::PredictMessage(const PredictMessage& message)
{
	if (this != &message)
	{
		mBytes = message.mBytes;
		mId = message.mId;
	}
}

PredictMessage& PredictMessage::operator = (const PredictMessage& message)
{
	if (this != &message)
	{
		mBytes = message.mBytes;
		mId = message.mId;
	}
	return *this;
}

void PredictMessage::WriteBytes(const char* datas, int len)
{
	mBytes.WriteBytes(datas, len);
}

void PredictMessage::WriteString(const DataStructures::HexString& str) 
{
	int len = str.GetLength();
	WriteINT32(len);
	if (len > 0)
	{
		WriteBytes(str.C_String(), len);
	}
}

void PredictMessage::WriteINT16(__s16 value)
{
	WriteBytes((char*)&value, sizeof(__s16));
}

void PredictMessage::WriteINT32(__s32 value)
{
	WriteBytes((char*)&value, sizeof(__s32));
}

void PredictMessage::WriteINT64(__s64 value)
{
	WriteBytes((char*)&value, sizeof(__s64));
}

void PredictMessage::WriteUINT16(__u16 value)
{
	WriteBytes((char*)&value, sizeof(__u16));
}

void PredictMessage::WriteUINT32(__u32 value)
{
	WriteBytes((char*)&value, sizeof(__u32));
}

void PredictMessage::WriteUINT64(__u64 value)
{
	WriteBytes((char*)&value, sizeof(__u64));
}

void PredictMessage::WriteFloat(float value)
{
	WriteBytes((char*)&value, sizeof(float));
}

void PredictMessage::WriteDouble(double value)
{
	WriteBytes((char*)&value, sizeof(double));
}

bool PredictMessage::ReadBytes(char* datas, int len, bool peek)
{
	return mBytes.ReadBytes(datas, len, peek);
}

__u32 PredictMessage::GetLength()
{
	return mBytes.GetBytesWritten();
}

// need free out side
char* PredictMessage::ToPacket(int& length)
{
	int len = mBytes.GetBytesWritten();
	length = len + 4;
	char* datas = (char*)malloc(length);
	memset(datas, 0, length);
	ReadBytes(datas + 4, len);
	memcpy(datas, &len, 4);
	return datas;
}

// when no length speciafied by the first 4 bytes
DataStructures::HexString PredictMessage::ReadAllBytes()
{
	int len = mBytes.GetBytesWritten();
	char* datas = (char*)malloc(len + 1);
	memset(datas, 0, len + 1);
	ReadBytes(datas, len, false);
	DataStructures::HexString result(datas);
	free(datas);
	return result;
}

DataStructures::HexString PredictMessage::ReadString(bool peek)
{
	__s32 len = ReadINT32(peek);
	DataStructures::HexString value;
	if (len > 0)
	{
		if (peek)
		{
			len = len + sizeof(__s32);
			char* datas = (char*)malloc(len + 1);
			memset(datas, 0, len + 1);
			ReadBytes(datas, len, peek);
			value = (datas + sizeof(__s32));
			free(datas);
		}
		else
		{
			char* datas = (char*)malloc(len + 1);
			memset(datas, 0, len + 1);
			ReadBytes(datas, len, peek);
			value = datas;
			free(datas);
		}	
	}
	return value;
}

__s16 PredictMessage::ReadINT16(bool peek)
{
	int len = sizeof(__s16);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	__s16 value = *((__s16*)datas);
	free(datas);
	return value;
}

__s32 PredictMessage::ReadINT32(bool peek)
{
	int len = sizeof(__s32);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	__s32 value = *((__s32*)datas);
	free(datas);
	return value;
}

__s64 PredictMessage::ReadINT64(bool peek)
{
	int len = sizeof(__s64);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	__s64 value = *((__s64*)datas);
	free(datas);
	return value;
}

__u16 PredictMessage::ReadUINT16(bool peek)
{
	int len = sizeof(__u16);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	__u16 value = *((__u16*)datas);
	free(datas);
	return value;
}

__u32 PredictMessage::ReadUINT32(bool peek)
{
	int len = sizeof(__u32);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	__u32 value = *((__u32*)datas);
	free(datas);
	return value;
}

__u64 PredictMessage::ReadUINT64(bool peek)
{
	int len = sizeof(__u64);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	__u64 value = *((__u64*)datas);
	free(datas);
	return value;
}

float PredictMessage::ReadFloat(bool peek)
{
	int len = sizeof(float);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	float value = *((float*)datas);
	free(datas);
	return value;
}

double PredictMessage::ReadDouble(bool peek)
{
	int len = sizeof(double);
	char* datas = (char*)malloc(len);
	memset(datas, 0, len);
	ReadBytes(datas, len, peek);
	double value = *((double*)datas);
	free(datas);
	return value;
}

void PredictMessage::WriteBoolean(bool value)
{
	char bl = value ? 1 : 0;
	WriteBytes(&bl, 1);
}

bool PredictMessage::ReadBoolen(bool peek)
{
	char bl[1];
	ReadBytes(bl, 1, peek);
	bool value = bl[0] == 1 ? true : false;
	return value;
}