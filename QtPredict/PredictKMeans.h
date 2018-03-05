#ifndef PREDICTKMEANS_H
#define PREDICTKMEANS_H
#include "DS_OrderedList.h"

class KMeansGroup;
class KMeansData
{
public:
	KMeansData();
	~KMeansData();
	KMeansData(int index, float quntity);
	KMeansData& operator= (const KMeansData& data);
	float DistanceTo(const KMeansGroup& other);

	float mQuntity;
	int mIndex;

};
int KMeansDataCompare(const float& quntity, const KMeansData& data);
typedef DataStructures::OrderedList<float, KMeansData, KMeansDataCompare> KMEANS_SOURCE;
int KMeansGroupCompare(const float& quntity, const KMeansGroup& data);
typedef DataStructures::OrderedList<float, KMeansGroup, KMeansGroupCompare> KMEANS_GROUP;
class KMeansGroup
{
public:
	KMeansGroup();
	~KMeansGroup();
	static void KMeans(KMEANS_SOURCE* sources, int groups, KMEANS_GROUP* result);
	bool Calculate();
	void Clear();
	KMeansGroup& operator= (const KMeansGroup& data);
	inline int Size()
	{
		return mIndexGroup.Size();
	}
	inline KMeansData At(int index)
	{
		return mIndexGroup[index];
	}

	float mQuntity;
	KMEANS_SOURCE mIndexGroup;
private:	
	static void KMeans(KMEANS_SOURCE* sources, KMEANS_GROUP* result);
};


#endif