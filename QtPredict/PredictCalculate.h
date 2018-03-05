/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/


#ifndef _PREDICTCALCULATE_H
#define _PREDICTCALCULATE_H

#include "PredictTypeDefines.h"
#include "HexString.h"
#include "Resource.pb.h"
#include "DS_OrderedList.h"
#ifdef CHINESE_PATH
#include <QString>
#endif
class PredictConfigData;

class PredictCalculate
{
public:
	PredictCalculate();
	~PredictCalculate();
	void Clear();
	void Calculate(PredictConfigData* configData);
private:
#ifdef COMPRESSION
	void compressPbFile(const char* fileName);
#endif
	void CleanSmallOrBigSamples();
	void parseConfig(const ServerConfig &server_config, keyInfoMapType &keyInfoMap, keySetType &keySet);	
	void calcObjectSize(objVectType &allObjVect, keyInfoMapType &keyInfoMap);
	void writeObjectsInfoToFile(objVectType &objVect, keyInfoMapType &keyInfoMap, bool isDebug);;
	void setIdIndexMap(objVectType &objVect, bool isDebug);
	void printObjVect(objVectType &objVect, bool isPrintIndex);
	void printObjMat(objMatType &objMat);
	void updateIterator(mIndexSetType::iterator &it, int step);	
	void genGraphForObjMat(objMatType &objMat, mIndexMatSetType &indexMatSet, bool isWriteToFile);
	int getRemained(indexMatType &visitedMat);
	int updateCpMat(mIndexMatSetType &mIndexMatSet, cpMatType &cpMat, indexMatType &visitedMat);
	void initCpMat(mIndexMatSetType &mIndexMatSet, cpMatType &cpMat);
	void writeCpMatToFile(cpMatType &cpMat, bool isDebug);
	void mergeObjectKey(keyVectType &baseKeyVect, keyVectType &newKeyVect);
	void printKeyInfo(keyInfoMapType &keyInfoMap);
#ifndef OLD
	void getIdKeyMap(keyMatVectType &keyMatVect, keyInfoMapType &keyInfoMap, objVectType &allObjVect, id2kMapType &id2kMap);
	int PredictCalculate::initFromKeyFile(const char *keysFile, keyMatVectType &kMatVect);
	void getAllObjects(keyMatVectType &learnMat, keyInfoMapType &keyInfoMap, objVectType &objVect, objMatType &objMat);
#else
	int initFromKeyFile(const char *keysFile, keyMatMatVectType &mat);
	void getAllObjects(keyMatMatVectType &learnMat, keyInfoMapType &keyInfoMap, objVectType &objVect, objMatType &objMat);
	void getIdKeyMap(keyMatMatVectType &learnMat, keyInfoMapType &keyInfoMap, objVectType &allObjVect, id2kMapType &id2kMap);
#endif
	bool getKeyInfo(const char *configFile, keyInfoMapType &keyInfoMap, keySetType &keySet);
	void writeGraphToFile(const char *fileName, mIndexMatSetType &indexMatSet, bool isColor);
	void writeKeysToFile(const char *fileName, id2kMapType &id2kMap, cpVectType &cpVect, keyInfoMapType &keyInfoMap, bool isForPackage);
	void writeToPbFile(const char *fileName, objVectType &objVect, id2kMapType &id2kMap, cpMatType &cpMat, mIndexMatSetType &indexMatSet);
	void compressPbFile();
public:
	DataStructures::HexString mGameName;
private:
	keySetType totalKeySet;
	objIdVectType objIdVect;
	objIdSetType objIdCom;
	objIdSetType objIdRel;
	objIdMatSetType objRelMat;
	objMatType objMat;
	id2iMapType id2iMap;
	i2idMapType i2idMap;			
	PredictConfigData* configData;
private:
#ifndef OLD
	keyMatVectType learnMat;
#else
	keyMatMatVectType learnMat;
#endif
	keyInfoMapType keyInfoMap;
	keySetType picKeySet;
	objVectType allObjVect;
	mIndexMatSetType mIndexMatSet;
	cpMatType cpMat;
	id2kMapType id2kMap;
};

#endif