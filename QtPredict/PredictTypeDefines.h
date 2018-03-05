#ifndef _PREDICTTYPEDEFINES_H
#define _PREDICTTYPEDEFINES_H

#include "PredictCommonType.h"
#include "CommonTypeDefines.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <iomanip>
using namespace std;

typedef __u64 objIdType;
typedef __u64 keyType;

typedef __u32 indexType;
typedef vector<keyType> keyVectType;
typedef set<keyType> keySetType;
typedef vector<keyVectType> keyMatVectType;
typedef pair<objIdType, keyVectType> objPairType;
typedef vector<keyMatVectType> keyMatMatVectType;
typedef vector<objIdType> objVectType;
typedef vector<objVectType> objMatType;
typedef vector<objIdType> objIdVectType;
typedef vector<indexType> indexVectType;
typedef set<objIdType> objIdSetType;
typedef set<indexType> indexSetType;
typedef multiset<indexType> mIndexSetType;
typedef vector<objIdSetType> objIdMatSetType;
typedef vector<indexSetType> indexMatSetType;
typedef vector<mIndexSetType> mIndexMatSetType;
typedef vector<objIdVectType> objIdMatType;
typedef vector<indexVectType> indexMatType;
typedef map<objIdType, indexType> id2iMapType;
typedef map<indexType, objIdType> i2idMapType;
typedef float cpType;
typedef vector<cpType> cpVectType;
typedef vector<cpVectType> cpMatType;
typedef pair<indexType, indexType> indexPairType;
typedef vector<indexPairType> indexPairVectType;
typedef map<objIdType, keyVectType> id2kMapType;
typedef deque<indexType> indexQueueType;

typedef struct sortNode_t
{
	indexType index;
	float weight;
} sortNodeType;
typedef vector<sortNodeType> sortNodeVectType;

typedef struct coefficient_t
{
	unsigned int f00;
	unsigned int f01;
	unsigned int f10;
	unsigned int f11;
} ceType;
typedef vector<ceType> ceVectType;
typedef vector<ceVectType> ceMatType;

struct cmpByCp
{
	bool operator()(const cpType cp1, const cpType cp2) const
	{
		return cp1 > cp2;
	}
};

typedef map<cpType, indexVectType, cmpByCp> cpIndexMapType;
typedef pair<cpType, indexType> cpIndexPairType;
typedef vector<cpIndexPairType> cpIndexVectType;

typedef struct info_t
{
	unsigned int size;
	bool isPicture;
} infoType;
typedef map<keyType, infoType> keyInfoMapType;



typedef struct selectNode_t {
	__u32 index;
	float scale;
} selectNodeType;

typedef std::vector<selectNodeType> selectNodeVectType;
typedef std::deque<selectNodeType> selectNodeQueueType;

#endif