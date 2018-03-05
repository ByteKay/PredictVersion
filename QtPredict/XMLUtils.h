#ifndef _XML_UTILS
#define _XML_UTILS

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "HexString.h"

class XMLUtils
{
public:
    XMLUtils() {}
    virtual ~XMLUtils() {}
    
    static rapidxml::xml_node<> *CreateNodeElement(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *parentNode, const DataStructures::HexString parameter);
    
	static DataStructures::HexString GetAttrib(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, const DataStructures::HexString defaultValue = "");
	static float GetAttribReal(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, float defaultValue = 0.0f);
	static __s32 GetAttribInt(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, __s32 defaultValue = 0.0f);
	static bool GetAttribBool(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, bool defaultValue = false);

	static void SetAttribString(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, const DataStructures::HexString defaultValue = "");
	static void SetAttribReal(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, float defaultValue = 0.0f);
	static void SetAttribInt(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, __s32 defaultValue = 0);
	static void SetAttribInt32(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, __s32 defaultValue = 0);
	static void SetAttribBool(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, bool defaultValue = false);

};

#endif