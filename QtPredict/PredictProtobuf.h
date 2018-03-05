/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/


#ifndef _PREDICTPROTOBUF_H
#define _PREDICTPROTOBUF_H
#ifndef CHINESE_PATH
#include "./streams/DS_FileStream.h"
#include <fstream>
#else
#include <QFile>
#include <QByteArray>
//#include <google/protobuf/io/zero_copy_stream_impl.h>
//#include <google/protobuf/io/coded_stream.h>
//#include <fcntl.h>
#endif

namespace PredictProtobuf
{
	template<typename T>
	bool ResolveByStream(const char* fileName, T* resource)
	{
		if (resource)
		{
			std::fstream input(fileName, ios::in | ios::binary);
			if (input.is_open())
			{
				if (resource->ParseFromIstream(&input))
				{
					return true;
				}
			}
		}
		return false;
	}

	template<typename T>
	bool ResolveByArray(const char* fileName, bool local, T* resource, bool encrpt = false)
	{
		if (resource)
		{
#ifdef CHINESE_PATH
			QString filePath;
			if (local)
			{
				filePath = QString::fromLocal8Bit(fileName);
			}
			else
			{
				filePath = QStringLiteral("%1").arg(fileName);
			}
			QFile file(filePath);
			if (file.open(QIODevice::ReadOnly))
			{
				QByteArray byteArray = file.readAll();
				if (encrpt)
				{
					// 2d cci.bin
					int len = byteArray.length();
					for (int i = 0; i < len; ++i)
					{
						byteArray[i] = byteArray[i].operator char() ^ 0x40;
					}	
				}
				resource->ParseFromArray(byteArray.data(), byteArray.length());
				file.close();
				return true;
			}
#else
			DataStructures::FileStream file(fileName, "rb");
			if (file.CanRead())
			{
				__s32 len = (__s32)file.Length();
				char* bytes = (char*)malloc(len * sizeof(char));
				memset(bytes, 0, len);
				file.Read(bytes, len);
				resource->ParseFromArray(bytes, len);
				free(bytes);
				return true;
			}
#endif
		}
		return false;
	}

	template<typename T>
	bool ResolveByArray(const char* fileName, T* resource)
	{
		if (resource)
		{
#ifdef CHINESE_PATH
			QFile file(QStringLiteral("%1").arg(fileName));
			if (file.open(QIODevice::ReadOnly))
			{
				QByteArray byteArray = file.readAll();	
				resource->ParseFromArray(byteArray.data(), byteArray.length());
				file.close();
				return true;
			}	
#else
			DataStructures::FileStream file(fileName, "rb");
			if (file.CanRead())
			{
				__s32 len = (__s32)file.Length();
				char* bytes = (char*)malloc(len * sizeof(char));
				memset(bytes, 0, len);
				file.Read(bytes, len);
				resource->ParseFromArray(bytes, len);
				free(bytes);
				return true;
			}
#endif
		}
		return false;
	}
};

#endif