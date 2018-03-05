/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef _PREDICTHECK_H
#define _PREDICTHECK_H
#include "PredictTypeDefines.h"
#include "HexString.h"

class PredictConfig;
class PredictCheck
{
public:
	~PredictCheck();
	PredictCheck(PredictConfig* config);
	void Clear();
	void CheckResult(__u64 key, std::vector<__u32>* result);
	void Start();
private:
	void Predict(__u64 key);
	void Load();
	void GetPredictSeq(std::deque<__u32> &preIndexQueue, std::vector<__u32> &predictIndexVect);
	void GetSelectWeight(std::deque<__u32> &preIndexQueue, selectNodeVectType &selectVect, sortNodeVectType &sortNodeVect);
public:
	DataStructures::HexString mGameName;
private:
	std::vector<__u64> mBigObjVect;
	std::map<__u64, __u32> mId2iMap;
	std::map<__u64, std::vector<__u64> > mId2kMap;
	std::deque<__u32> mPreQueue;
	std::vector<__u32> mPredictVect;
	std::vector< std::vector<float> > mCpMat;
	std::vector< std::set<__u32> > mIndexMatSet;
private:
	PredictConfig* mConfig;
};

#endif