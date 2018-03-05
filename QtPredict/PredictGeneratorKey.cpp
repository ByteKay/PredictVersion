/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/
#include "PredictCommonType.h"
#include "PredictGeneratorKey.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "PredictCheck.h"
#include "FormatString.h"
#include "PredictKeyHandleUI.h"
#include "HexTimeCounter.h"
#include "PredictConfig.h"
#include "PredictPrint.h"
#ifdef CHINESE_PATH
#include <QTextStream>
#include <QString>
#include <QFile>
#endif

#include <QMessageBox>

int CompareKeyTime(const __u64& time, const ThreeKeyPair& keiPair)
{
#if 1
	if (time < keiPair.mTimestamp)
	{
		return -1;
	}
	if (time == keiPair.mTimestamp)
	{
		return 0;
	}
	return 1;
#else
	if (time < keiPair.mTimestamp)
	{
		return 1;
	}
	if (time == keiPair.mTimestamp)
	{
		return 0;
	}
	return -1;
#endif
}

/*
__u32 PredictGeneratorKey::GeneratorId()
{
	mutex.Lock();
	int id = mTotalSessionCount--;
	mutex.Unlock();
	return id;
}
*/

PredictGeneratorKey::~PredictGeneratorKey()
{
	Clear();
}

PredictGeneratorKey::PredictGeneratorKey(PredictConfig* mConfig) : mConfig(mConfig), mIsNeedCalculate(false), mCheck(0), mIsNeedRecalculate(false)
{
	mLastDecreaseThreashold = mConfig->mConfigData.mDecreaseThreshold;
	// mTotalSessionCount = 100000000;
}

__u32 PredictGeneratorKey::Size()
{
	return mKeySequence.GetHashEntriesSize();
}

void PredictGeneratorKey::IsNeedCalculate(bool check)
{
	mIsNeedCalculate = check;
}

bool PredictGeneratorKey::IsNeedCalculate()
{
	return mIsNeedCalculate;
}

//#define UNIQUE

void PredictGeneratorKey::LoadFromFile(const char* fileName)
{
	bool isNeed = mIsNeedCalculate;
	mIsNeedCalculate = false;
	Clear();
#ifdef UNIQUE
	DataStructures::HashTable<__u64, char> temp;
#endif

#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(fileName));
	if(f.open(QIODevice::ReadOnly | QIODevice::Text))  
	{  
		QTextStream txtInput(&f);  
		QString lineStr;  
		int i = -1;
		int count = 1;
		while(!txtInput.atEnd())  
		{  
			lineStr = txtInput.readLine();  
			if (((lineStr[0] == 'n') && (lineStr[4] == ':')) || ((lineStr[1] == 'n') && lineStr[5] == ':'))
			{
				if (lineStr[8] == '0' || lineStr[9] == '0')
				{
					++i;
					count = 1;
					mKeySequence.Add(i, KEYPAIR_LISTS());
				}
			}
			else if ((lineStr[0] == '0') && (lineStr[1]) == 'x')
			{
				__u64 key;
				std::string str = lineStr.toStdString();
				sscanf_s(str.c_str(), "0x%llx", &key);
				AppendKeyPair(i, key, count++, false);
#ifdef UNIQUE
				if (!temp.InHashTable(key))
				{
					temp.Add(key, 1);
				}
#endif
			}
		}  
		f.close();
	}  
#else

	std::ifstream fin(fileName);
	// mTotalSessionCount = 0;
	mCount = 0;
	if (!fin.is_open()) 
	{
		mIsNeedCalculate = isNeed;
		return;
	}
	std::string buf;
	int i = -1;
	int count = 1;
	while (getline(fin, buf))
	{
		if (((buf[0] == 'n') && (buf[4] == ':')) || ((buf[1] == 'n') && buf[5] == ':'))
		{
			if (lineStr[8] == '0' || lineStr[9] == '0')
			{
				++i;
				count = 1;
				mKeySequence.Add(i, KEYPAIR_LISTS());
			}
		}
		else if ((buf[0] == '0') && (buf[1]) == 'x')
		{
			__u64 key;
			sscanf(buf.c_str(), "0x%llx", &key);
			AppendKeyPair(i, key, count++, false);
		}
	}
	fin.close();
#endif
	mIsNeedCalculate = isNeed;
#ifndef TEST_KEY
	int totalSessionCount = mKeySequence.GetHashEntriesSize();
#else
	int totalSessionCount = mKeySequence.size();
#endif
#ifdef UNIQUE
	int uniqueKeyCount = temp.GetHashEntriesSize();
	temp.Clear();
	ClientPrint::PrintMessage(mGameName, FormatString("unique: %d", uniqueKeyCount));
#endif
	ClientPrint::PrintMessage(mGameName, FormatString("Learn times: %d, total count : %d", totalSessionCount, mCount));
}

void PredictGeneratorKey::Clear()
{
	SITR itr(&mKeySequence);
	KEYPAIR_LISTS* lists = itr.GetData();
	while (lists)
	{
		lists->Clear();
		itr.FindNext();
		lists = itr.GetData();
	}
	mKeySequence.Clear();
}

void PredictGeneratorKey::WriteAndClear(const char* fileName)
{
	WriteToFile(fileName);
	Clear();
}

bool PredictGeneratorKey::CheckKeysWrong(__u64& keyResult)
{
	struct KeyDistinct
	{
		KeyDistinct(){}
		KeyDistinct(__u64 k, int c): key(k), count(c){}
		KeyDistinct& operator = (const KeyDistinct& other)
		{
			key = other.key;
			count = other.count;
			return *this;
		}
		bool operator == (const KeyDistinct& other)
		{
			return key == other.key;
		}

		__u64 key;
		int count;

	};
	int size = Size();
	bool flag = false;
	if (size > 0)
	{
		DataStructures::List<KeyDistinct> keyFirst;
		SITR itr(&mKeySequence);
		KEYPAIR_LISTS* lists = itr.GetData();
		int max = -1;
		while (lists)
		{
			__u32 size = lists->Size();
			if (size > 0)
			{
				KeyDistinct temp((*lists)[0].mKeyId, 1);
				int index = keyFirst.GetIndexOf(temp);
				if (index > keyFirst.Size())
				{
					keyFirst.Push(temp);
					index = keyFirst.Size() - 1;
				}
				else
				{
					keyFirst[index].count += 1;
				}
				if (keyFirst[index].count > max)
				{
					max = keyFirst[index].count;
					keyResult = keyFirst[index].key;
				}
			}
			itr.FindNext();
			lists = itr.GetData();
		}
		int unique = keyFirst.Size();
		if (unique > 1)
		{
			float occu = max * 1.0f / size;
			//int button = QMessageBox::question(NULL, "Notice", FormatString("存在起始key不一致的序列，相同数量的占比为 %.6f 是否需要清除？", max * 1.0f / size), QMessageBox::Yes, QMessageBox::No);
			//if (button == QMessageBox::Yes)
			if (occu > 0.8f)
			{
				flag = true;
			}
		}
		else
		{
			keyResult = 0;
		}
		keyFirst.Clear();
	}
	return flag;
}

void PredictGeneratorKey::WriteToFile(const char* fileName, __u64 key)
{
	if (mKeySequence.GetHashEntriesSize() == 0)
	{
		return;
	}
	static int NUMBER = 1000;
#ifdef CHINESE_PATH
	QString fileN = QStringLiteral("%1").arg(fileName);
	QFile file(fileN);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream fout(&file);
		SITR itr(&mKeySequence);
		KEYPAIR_LISTS* lists = itr.GetData();
		while (lists)
		{
			__u32 size = lists->Size();
			if (size > 0)
			{
				if (key != 0)
				{
					if ((*lists)[0].mKeyId == key)
					{
						int count = size / NUMBER + 1;
						int start = 0;
						int end = count == 1 ? size : NUMBER;
						for (int c = 0; c < count; ++c)
						{
							fout << "#node: 0x" << c << endl;
							for (int i = start; i < end; i++)
							{
								char temp[20] = { 0 };
								sprintf(temp, "0x%llx", (*lists)[i].mKeyId);
								fout << temp << endl;
							}
							start = end;
							end = start + NUMBER;
							if (end > size)
							{
								end = size;
							}
							if (start == end)
							{
								break;
							}
						}
						fout << endl;
					}
				}
				else
				{
					int count = size / NUMBER + 1;
					int start = 0;
					int end = count == 1 ? size : NUMBER;
					for (int c = 0; c < count; ++c)
					{
						fout << "#node: 0x" << c << endl;
						for (int i = start; i < end; i++)
						{
							char temp[20] = { 0 };
							sprintf(temp, "0x%llx", (*lists)[i].mKeyId);
							fout << temp << endl;
						}
						start = end;
						end = start + NUMBER;
						if (end > size)
						{
							end = size;
						}
						if (start == end)
						{
							break;
						}
					}
					fout << endl;
				}

			}
			itr.FindNext();
			lists = itr.GetData();
		}
		fout.flush();
		file.close();
	}
	

#else
	std::ofstream fout(fileName);
	if (!fout && !fout.is_open())
	{
		ClientPrint::PrintMessage(mGameName, FormatString("Cannot open output keys file : %s !", fileName));
	}

	SITR itr(&mKeySequence);
	KEYPAIR_LISTS* lists = itr.GetData();
	while (lists)
	{	
		__u32 size = lists->Size();
		if (size > 0)
		{
			fout << "#node: 0x" << std::hex << 0 << std::endl;
			for (int i = 0; i < size; i++)
			{
				char temp[20] = { 0 };
				sprintf(temp, "0x%llx", (*lists)[i].mKeyId);
				fout << temp << std::endl;
			}
			fout << std::endl;
		}
		itr.FindNext();
		lists = itr.GetData();
	}
	fout.close();
#endif
}

bool PredictGeneratorKey::IsNeedRecalculate()
{
	return mIsNeedRecalculate;
}

void PredictGeneratorKey::IsNeedRecalculate(bool isNeed)
{
	mIsNeedRecalculate = isNeed;
}

void PredictGeneratorKey::InitializeCheckManual()
{
	if (!mCheck)
	{
		mCheck = new PredictCheck(mConfig);
		mCheck->mGameName = mGameName;
		mCheck->Start();
		ClientPrint::PrintMessage(mGameName, "验证开始...");
	}
	else
	{
		mCheck->Start();
		// ClientPrint::PrintMessage(mGameName, "验证开始...");
	}
}

void PredictGeneratorKey::InitializeCheck()
{
	if (!mCheck && mIsNeedCalculate)
	{
		mCheck = new PredictCheck(mConfig);
		mCheck->mGameName = mGameName;
		mCheck->Start();
		mIsNeedCalculate = false;
		ClientPrint::PrintMessage(mGameName, "验证开始...");
	}
}

// should calculate before call this function
void PredictGeneratorKey::ResetCheck()
{
	if (mCheck && mIsNeedRecalculate)
	{
		mCheck->Start();
		mIsNeedRecalculate = false;
		mRecalculateTimer.StartTimer();
		ClientPrint::PrintMessage(mGameName, "已重新计算, 更新预测规则...");
	}
}

bool PredictGeneratorKey::NeedRecheckNow()
{
	bool needRecheck = false;
	float decrease = mConfig->mConfigData.mDecreaseThreshold;
	if (decrease != mLastDecreaseThreashold)
	{
		mRecheck.StartTimer();
		mLastDecreaseThreashold = decrease;
	}
	else
	{
		if (!mRecheck.IsTimerStopped())
		{
			int timeSlapped = mRecheck.GetTimeSlapped();
			if (timeSlapped > 3000)
			{
				needRecheck = true;
				mRecheck.StopTimer();
			}
		}
	}
	return needRecheck;
}

bool PredictGeneratorKey::CanBeCalculate()
{
	int size = mKeySequence.GetHashEntriesSize();
	if (size > 5 && mCount > 1000)
	{
		return true;
	}
	return false;
}

void PredictGeneratorKey::CheckTimer()
{
	if (!mCheck && !mIsNeedCalculate)
	{
		int size = mKeySequence.GetHashEntriesSize();
		// first according to the size
		// second accoding to time slapped
		if (size > 5 && mCount > 1000)
		{
			mIsNeedCalculate = true;
			mRecalculateTimer.StartTimer();
		}
	}
	else
	{
		__u32 time = mRecalculateTimer.GetTimeSlapped();
		bool need = NeedRecheckNow();
		if (need || (time > 900000)) // 15 minutues
		{
			// need recalculate
			mIsNeedRecalculate = true;
		}
	}
}

void PredictGeneratorKey::AppendKeyPair(__u32 sessionId, __u64 keyId, __u64 timestamp, bool needCheck)
{

	if (!mKeySequence.InHashTable(sessionId))
	{
		mKeySequence.Add(sessionId, KEYPAIR_LISTS());
#ifdef ORDER_LIST
	}
	mKeySequence[sessionId].Insert(timestamp, ThreeKeyPair(sessionId, keyId, timestamp), true);
#else
		mKeySequence[sessionId].Push(ThreeKeyPair(sessionId, keyId, timestamp));
	}
	else
	{
		mKeySequence[sessionId].Push(ThreeKeyPair(sessionId, keyId, timestamp));
#if 0
		KEYPAIR_LISTS* temp = &mKeySequence[sessionId];
		int size = temp->Size();
		if (size > 0)
		{
			if (timestamp < (*temp)[size - 1].mTimestamp)
			{
				ClientPrint::PrintMessage(mGameName, FormatString("0xllx has been ever discarded", keyId));
			}
		}
#endif

	}
#endif
	// ClientPrint::PrintMessage(mGameName, FormatString("%d", keyId));
	mCount++;
	if (needCheck && mCheck)
	{
		std::vector<__u32> result;
		mCheck->CheckResult(keyId, &result);
		result.clear();
	}
}

