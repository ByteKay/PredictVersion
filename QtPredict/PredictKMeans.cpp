#include "PredictKMeans.h"

KMeansData::KMeansData() : mIndex(-1), mQuntity(0)
{

}
KMeansData::KMeansData(int index, float quntity) : mIndex(index), mQuntity(quntity)
{

}

KMeansData& KMeansData::operator= (const KMeansData& data)
{
	mQuntity = data.mQuntity;
	mIndex = data.mIndex;
	return *this;
}

KMeansData::~KMeansData()
{

}

float KMeansData::DistanceTo(const KMeansGroup& other)
{
	float d = this->mQuntity - other.mQuntity;
	return d < 0 ? -d : d;
}

KMeansGroup& KMeansGroup::operator= (const KMeansGroup& data)
{
	if (this != &data)
	{
		mIndexGroup.Clear();
		mQuntity = data.mQuntity;
		mIndexGroup = data.mIndexGroup;
	}
	return *this;
}

KMeansGroup::KMeansGroup()
{

}

KMeansGroup::~KMeansGroup()
{
	Clear();
}

void KMeansGroup::Clear()
{
	mIndexGroup.Clear();
}

bool KMeansGroup::Calculate()
{
	int size = mIndexGroup.Size();
	float temp = 0;
	for (int i = 0; i < size; ++i)
	{
		temp += mIndexGroup[i].mQuntity;
	}
	if (size > 0)
	{
		temp = temp * 1.0f / size;
	}
	if (temp - mQuntity < 1e-5f && temp - mQuntity > -1e-5f)
	{
		return true;
	}
	mQuntity = temp;
	return false;
}

int KMeansDataCompare(const float& quntity, const KMeansData& data)
{
	if (quntity < data.mQuntity)
		return -1;
	if (quntity == data.mQuntity)
		return 0;
	return 1;
}
int KMeansGroupCompare(const float& quntity, const KMeansGroup& data)
{
	if (quntity < data.mQuntity)
		return -1;
	if (quntity == data.mQuntity)
		return 0;
	return 1;
}

void KMeansGroup::KMeans(KMEANS_SOURCE* sources, KMEANS_GROUP* initialGroups)
{
	int size1 = sources->Size();
	KMeansGroup* group = 0;
	for (int i1 = 0; i1 < size1; ++i1)
	{
		KMeansData* source = &(*sources)[i1];
		int index;
		int minD = 1e9;
		int size2 = initialGroups->Size();

		for (int i2 = 0; i2 < size2; ++i2)
		{
			group = &(*initialGroups)[i2];
			int d = source->DistanceTo(*group);
			if (minD > d)
			{
				minD = d;
				index = i2;
			}
		}
		group = &(*initialGroups)[index];
		group->mIndexGroup.Insert(source->mQuntity, *source, true);
	}
	int size2 = initialGroups->Size();
	bool needAgain = false;
	for (int i2 = 0; i2 < size2; ++i2)
	{
		group = &(*initialGroups)[i2];
		needAgain = !group->Calculate();
	}
	if (needAgain)
	{
		for (int i2 = 0; i2 < size2; ++i2)
		{
			group = &(*initialGroups)[i2];
			group->Clear();
		}
		KMeans(sources, initialGroups);
	}
}


void KMeansGroup::KMeans(KMEANS_SOURCE* sources, int groups, KMEANS_GROUP* result)
{
	int size = sources->Size();
	KMEANS_SOURCE tempList;
	for (int i = 0; i < size; ++i)
	{
		KMeansData* data = &(*sources)[i];
		tempList.Insert(data->mQuntity, *data, false);
	}
	int unique = tempList.Size();
	if (unique < groups)
	{
		return;
	}
	result->Clear();
	int step = 0;
	int temp = 0;
	if (unique > groups * 2)
	{
		step = unique / (groups * 2);
		temp = step;
		step *= 2;
	}
	else
	{
		step = 1;
	}
	for (int i = 0; i < groups; ++i)
	{
		KMeansGroup group_;
		group_.mQuntity = tempList[temp].mQuntity;
		result->Insert(group_.mQuntity, group_, true);
		temp += step;
	}
	tempList.Clear();
	KMeans(sources, result);
	int size2 = result->Size();
	KMeansGroup* group;
	for (int i2 = 0; i2 < size2; ++i2)
	{
		group = &(*result)[i2];
	}
}