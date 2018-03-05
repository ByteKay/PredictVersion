/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/
#include "PredictCommonType.h"
#include "PredictCheck.h"
#include "Perception.pb.h"
#include "PredictProtobuf.h"
#include "PredictConfig.h"
#include "PredictKeyHandleUI.h"
#include "FormatString.h"
#include "PredictPrint.h"

std::vector< std::set<__u32> >* g_indexMatSet;

static bool CmpByWeight(const sortNodeType sortNode1, const sortNodeType sortNode2)
{
#if 0
	__u32 index1 = sortNode1.index;
	__u32 index2 = sortNode2.index;
	if (sortNode2.weight == sortNode1.weight)
	{
		std::set<__u32>& indexSet1 = (*g_indexMatSet)[index1];
		std::set<__u32>& indexSet2 = (*g_indexMatSet)[index2];
		if (indexSet1.find(index2) == indexSet1.end()
			&& indexSet2.find(index1) == indexSet2.end()) 
		{
			return index2 > index1;
		}
		else if (indexSet1.find(index2) != indexSet1.end()) 
		{
			return true;
		}
		else if (indexSet2.find(sortNode1.index) != indexSet2.end()) 
		{
			return false;
		}
		else
		{
			return sortNode2.index > sortNode1.index;
		}
	}
#endif
	return sortNode2.weight < sortNode1.weight;
}

void PredictCheck::GetSelectWeight(std::deque<__u32> &preIndexQueue, selectNodeVectType &selectVect, sortNodeVectType &sortNodeVect)
{
	for (selectNodeVectType::iterator it = selectVect.begin(), eit = selectVect.end(); it != eit; it++) {
		selectNodeType selectNode = *it;
		__u32 index = selectNode.index;
		sortNodeType sortNode;
		sortNode.index = index;
		sortNode.weight = 0.0f;
		std::deque<__u32> preNodes = preIndexQueue;
		while (!preNodes.empty())
		{
			__u32 preIndex = preNodes.front();
			sortNode.weight += mCpMat[preIndex][index] * preNodes.size() * selectNode.scale;
			preNodes.pop_front();
		}
		int i = 0;
		for (i = 0; i < sortNodeVect.size(); i++) 
		{
			if (sortNodeVect[i].index == index)
			{
				if (sortNode.weight > sortNodeVect[i].weight)
				{
					sortNodeVect[i].weight = sortNode.weight;
				}
				break;
			}
		}
		if (i == sortNodeVect.size())
		{
			sortNodeVect.push_back(sortNode);
		}
	}
}


PredictCheck::PredictCheck(PredictConfig* config) : mConfig(config)
{

}

PredictCheck::~PredictCheck()
{
	Clear();
}

void PredictCheck::Clear()
{
	mBigObjVect.clear();
	mId2iMap.clear();
	std::map<__u64, std::vector<__u64> >::iterator itrB = mId2kMap.begin();
	while (itrB != mId2kMap.end())
	{
		itrB->second.clear();
		++itrB;
	}
	mId2kMap.clear();

	mPreQueue.clear();
	mPredictVect.clear();
	int size = mCpMat.size();
	for (int i = 0; i < size; ++i)
	{
		mCpMat[i].clear();
	}
	mCpMat.clear();
	size = mIndexMatSet.size();
	for (int i = 0; i < size; ++i)
	{
		mIndexMatSet[i].clear();
	}
	mIndexMatSet.clear();
}

void PredictCheck::Start()
{
	Load();
}

void PredictCheck::CheckResult(__u64 key, std::vector<__u32>* result)
{
	try
	{
		Predict(key);
		result->clear();
		*result = mPredictVect;
	}
	catch (...)
	{
		ClientPrint::PrintMessage(mGameName, "验证有问题...");
	}

}

void PredictCheck::GetPredictSeq(std::deque<__u32> &preIndexQueue, std::vector<__u32> &predictIndexVect)
{
	selectNodeVectType selectVect;
	selectNodeQueueType selectQueue;
	std::deque<__u32> preNodes = preIndexQueue;
	__u32 curIndex = preNodes.back();
	std::vector<float>& cpVect = mCpMat[curIndex];
	for (int i = 0; i < cpVect.size(); i++)
	{
		if (i != curIndex) 
		{
			selectNodeType selectNode;
			selectNode.index = i;
			selectNode.scale = cpVect[i];
			selectVect.push_back(selectNode);
		}
	}
	// g_Print->PrintMessage(FormatString("selectVect.size: %d", selectVect.size()));
	sortNodeVectType sortNodeVect;
	GetSelectWeight(preNodes, selectVect, sortNodeVect);
	g_indexMatSet = &mIndexMatSet;
	sort(sortNodeVect.begin(), sortNodeVect.end(), CmpByWeight);
	int cnt = 0;
	for (sortNodeVectType::iterator it = sortNodeVect.begin(), eit = sortNodeVect.end(); it != eit && cnt < mConfig->mConfigData.mMaxPredictNumber; it++, cnt++)
	{
		ClientPrint::PrintMessage(mGameName, FormatString("index %d, weight: %.5f", it->index, it->weight));
	}
	predictIndexVect.clear();
	cnt = 0;
	for (sortNodeVectType::iterator it = sortNodeVect.begin(), eit = sortNodeVect.end(); it != eit && cnt < mConfig->mConfigData.mMaxPredictNumber; it++, cnt++)
	{
		predictIndexVect.push_back(it->index);
	}
	sortNodeVect.clear();
	selectQueue.clear();
	selectVect.clear();
	preNodes.clear();
}

void PredictCheck::Predict(__u64 key)
{
	if (find(mBigObjVect.begin(), mBigObjVect.end(), key) != mBigObjVect.end())
	{
		__u32 index = mId2iMap[key];
		ClientPrint::PrintMessage(mGameName, FormatString("big object generate, key: 0x%llx index: %d", key, index));
		std::vector<__u32> predictIndexVect;
		mPreQueue.push_back(index);
		GetPredictSeq(mPreQueue, predictIndexVect);

		// g_Print->PrintMessage(FormatString("next size: %d", predictIndexVect.size()));
		if (mPreQueue.size() > mConfig->mConfigData.mPreIndexNumber)
		{
			mPreQueue.pop_front();
		}
		mPredictVect.clear();
		for (std::vector<__u32>::iterator it = predictIndexVect.begin(), eit = predictIndexVect.end(); it != eit; it++) 
		{
			__u32 next = *it;
			// g_Print->PrintMessage(FormatString("next: %d", next));
			mPredictVect.push_back(next);
		}
		predictIndexVect.clear();
	}
}

void PredictCheck::Load()
{
	try
	{
		Clear();
		Perception perception;
		PredictProtobuf::ResolveByArray<Perception>(mConfig->mConfigData.GetFullPerceptionPath().C_String(), &perception);
		ClientPrint::PrintMessage(mGameName, FormatString("nodeNum: %d nodes size: %d", perception.nodenum(), perception.nodes_size()));
		int nodeNum = perception.nodenum();
		mBigObjVect.resize(nodeNum);
		mIndexMatSet.resize(nodeNum);
		mCpMat.resize(nodeNum);
		for (int i = 0; i < mCpMat.size(); i++)
		{
			mCpMat[i].resize(nodeNum);
		}
		for (int i = 0; i < perception.nodes_size(); i++)
		{
			const Node &pbNode = perception.nodes(i);
			__u32 index = pbNode.id();
			__u64 key = pbNode.uniqkey();
			mBigObjVect[index] = key;
			mId2iMap[key] = index;
			for (int j = 0; j < pbNode.succinfo_size(); j++)
			{
				const SuccInfo &succInfo = pbNode.succinfo(j);
				__u32 succ = succInfo.id();
				if (succInfo.has_isnext())
				{
					mIndexMatSet[index].insert(succ);
				}
				mCpMat[index][succ] = succInfo.cp();
			}
			for (int k = 0; k < pbNode.keys_size(); k++)
			{
				mId2kMap[key].push_back(pbNode.keys(k));
			}
		}
		perception.Clear();
		ClientPrint::PrintMessage(mGameName, "Load Perception.txt successfully!");
	}
	catch (...)
	{
		ClientPrint::PrintMessage(mGameName, "Load Perception.txt 有问题!");
	}
}
