#include "XMLUtils.h"
#include "FormatString.h"

//sceine rapidxml NEVER save values localy, using local var will cause strange errors, so, we use HexString because of it will cache all strings in program lifetime

rapidxml::xml_node<> *XMLUtils::CreateNodeElement(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *parentNode, const DataStructures::HexString parameter)
{
    char *nodeName = xmlDoc->allocate_string(parameter.C_String());
    rapidxml::xml_node<> *node = xmlDoc->allocate_node(rapidxml::node_element, nodeName);
    parentNode->append_node(node);
    
    return node;
}

DataStructures::HexString XMLUtils::GetAttrib(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, const DataStructures::HexString defaultValue)
{
    if (xmlNode->first_attribute(parameter.C_String()))
        return xmlNode->first_attribute(parameter.C_String())->value();
    else
        return defaultValue;
}

float XMLUtils::GetAttribReal(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, float defaultValue)
{
    if (xmlNode->first_attribute(parameter.C_String()))
        return (float)atof(xmlNode->first_attribute(parameter.C_String())->value());
    else
        return defaultValue;
}

__s32 XMLUtils::GetAttribInt(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, __s32 defaultValue)
{
    if (xmlNode->first_attribute(parameter.C_String()))
        return atol( xmlNode->first_attribute(parameter.C_String())->value());
    else
        return defaultValue;
}

bool XMLUtils::GetAttribBool(rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, bool defaultValue)
{
    if (!xmlNode->first_attribute(parameter.C_String()))
        return defaultValue;
    
    if ((DataStructures::HexString(xmlNode->first_attribute(parameter.C_String())->value()) == "true") || (atoi(xmlNode->first_attribute(parameter.C_String())->value())) > 0)
        return true;
    
    return false;
}

void XMLUtils::SetAttribString(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, const DataStructures::HexString defaultValue)
{
    char *name = xmlDoc->allocate_string(parameter.C_String());
    char *value = xmlDoc->allocate_string(defaultValue.C_String());
    rapidxml::xml_attribute<> *attString = xmlDoc->allocate_attribute(name, value);
    xmlNode->append_attribute( attString );
}

void XMLUtils::SetAttribReal(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, float defaultValue)
{
    DataStructures::HexString value = FormatString("%.5f", defaultValue);
    SetAttribString(xmlDoc, xmlNode, parameter.C_String(), value);
}

void XMLUtils::SetAttribInt(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, __s32 defaultValue)
{
    DataStructures::HexString value = FormatString("%i", defaultValue);
    SetAttribString(xmlDoc, xmlNode, parameter.C_String(), value);
}

void XMLUtils::SetAttribInt32 (rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, __s32 defaultValue)
{
    DataStructures::HexString value = FormatString("%i", defaultValue);
    SetAttribString(xmlDoc, xmlNode, parameter.C_String(), value);
}

void XMLUtils::SetAttribBool(rapidxml::xml_document<> *xmlDoc, rapidxml::xml_node<> *xmlNode, const DataStructures::HexString parameter, bool defaultValue)
{
    DataStructures::HexString value = FormatString("%i", defaultValue == true ? 1 : 0);
    SetAttribString(xmlDoc, xmlNode, parameter.C_String(), value);
}
