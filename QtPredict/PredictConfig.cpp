/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/


#include "PredictConfig.h"
#include "./streams/DS_FileStream.h"
#include "XMLUtils.h"
#ifdef CHINESE_PATH
#include "QTextStream.h"
#include <QString>
#include <QFile>
#endif
static const char* VALUE = "value";

const char*  PredictConfigData::filePathname = "PredictConfig";
const char*  PredictConfigData::ipName = "IP";
const char*  PredictConfigData::portName = "Port";
const char*  PredictConfigData::isCheckName = "Check";
const char*  PredictConfigData::hasKeyFileName = "HasKeyFile";
const char*  PredictConfigData::hasGenerateFileName = "HasGenerateKeyFile";
const char*  PredictConfigData::keyFileName = "KeyFile";
const char*  PredictConfigData::generateKeyFileName = "GenerateKeyFile";
const char*  PredictConfigData::packageFileName = "PackageFile";
const char*  PredictConfigData::perceptionFileName = "PerceptionFile";
const char*  PredictConfigData::quntityThresholName = "BKQuntityThreshold";
const char*  PredictConfigData::sizeThresholName = "BKSizeThreshold";
const char*  PredictConfigData::minSize = "BKMinSize";
const char*  PredictConfigData::lengthKey = "LengthKey";
const char*	 PredictConfigData::decreaseThreshold = "DecreaseThreshold";
const char*	 PredictConfigData::maxPredictNumber = "MaxPredictNumber";
const char*  PredictConfigData::preIndexNumber = "PreIndexNumber";
const char*  PredictConfigData::writeTempFile = "WriteTempFile";
const char*	 PredictConfigData::maxKeyCountPerConnection = "MaxKeyCountPerConnection";
const char*  PredictConfigData::compressionByName = "Compression";
const char*  PredictConfigData::cpThreashold = "CP";

int PredictConfig::GetIndexByName(const char* name)
{
	if (mNameMap.InHashTable(name))
		return mNameMap[name];
	return -1;
}

PredictConfig::~PredictConfig()
{
	mNameMap.Clear();
}

void PredictConfig::Save()
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> *decl = doc.allocate_node(rapidxml::node_declaration);
	rapidxml::xml_attribute<> *decl_ver = doc.allocate_attribute("version", "1.0");
	decl->append_attribute(decl_ver);
	doc.append_node(decl);
	//create xml tree
	rapidxml::xml_node<> *rootNode = doc.allocate_node(rapidxml::node_element, PredictConfigData::filePathname);
	doc.append_node(rootNode);
	rapidxml::xml_node<> *node = doc.allocate_node(rapidxml::node_element, PredictConfigData::ipName);
	XMLUtils::SetAttribString(&doc, node, VALUE, mConfigData.mIP);
	rootNode->append_node(node);
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::portName);
	XMLUtils::SetAttribInt(&doc, node, VALUE, mConfigData.mPort);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::isCheckName);
	XMLUtils::SetAttribBool(&doc, node, VALUE, mConfigData.mIsCheck);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::hasKeyFileName);
	XMLUtils::SetAttribBool(&doc, node, VALUE, mConfigData.mHasKeyFile);
	rootNode->append_node(node);
	if (mConfigData.mHasKeyFile)
	{
		node = doc.allocate_node(rapidxml::node_element, PredictConfigData::keyFileName);
		XMLUtils::SetAttribString(&doc, node, VALUE, mConfigData.mKeyFile);
		rootNode->append_node(node);
	}
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::hasGenerateFileName);
	XMLUtils::SetAttribBool(&doc, node, VALUE, mConfigData.mHasGenerateFile);
	rootNode->append_node(node);
	if (mConfigData.mHasGenerateFile)
	{
		node = doc.allocate_node(rapidxml::node_element, PredictConfigData::generateKeyFileName);
		XMLUtils::SetAttribString(&doc, node, VALUE, mConfigData.mGenerateKeyFile);
		rootNode->append_node(node);
	}
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::packageFileName);
	XMLUtils::SetAttribString(&doc, node, VALUE, mConfigData.mPackageFile);
	rootNode->append_node(node);
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::perceptionFileName);
	XMLUtils::SetAttribString(&doc, node, VALUE, mConfigData.mPerceptionFile);
	rootNode->append_node(node);
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::quntityThresholName);
	XMLUtils::SetAttribReal(&doc, node, VALUE, mConfigData.mBKQuntityThreshold);
	rootNode->append_node(node);
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::sizeThresholName);
	XMLUtils::SetAttribReal(&doc, node, VALUE, mConfigData.mBKSizeThreshold);
	rootNode->append_node(node);
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::minSize);
	XMLUtils::SetAttribReal(&doc, node, VALUE, mConfigData.mBKMinSize);
	rootNode->append_node(node);
	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::lengthKey);
	XMLUtils::SetAttribInt(&doc, node, VALUE, mConfigData.mKeyLength);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::decreaseThreshold);
	XMLUtils::SetAttribReal(&doc, node, VALUE, mConfigData.mDecreaseThreshold);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::maxPredictNumber);
	XMLUtils::SetAttribInt(&doc, node, VALUE, mConfigData.mMaxPredictNumber);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::preIndexNumber);
	XMLUtils::SetAttribInt(&doc, node, VALUE, mConfigData.mPreIndexNumber);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::writeTempFile);
	XMLUtils::SetAttribInt(&doc, node, VALUE, mConfigData.mWriteTempFile);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::maxKeyCountPerConnection);
	XMLUtils::SetAttribInt(&doc, node, VALUE, mConfigData.mMaxKeyCountPerConnection);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::compressionByName);
	XMLUtils::SetAttribBool(&doc, node, VALUE, mConfigData.mCompression);
	rootNode->append_node(node);

	node = doc.allocate_node(rapidxml::node_element, PredictConfigData::cpThreashold);
	XMLUtils::SetAttribReal(&doc, node, VALUE, mConfigData.mCpThreashold);
	rootNode->append_node(node);


	//out put xml to string
	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);
#ifdef CHINESE_PATH
	QFile f(QStringLiteral("%1").arg(mConfigData.GetFullConfigPath().C_String()));
	if (f.open(QIODevice::WriteOnly))
	{
		unsigned int length = xml_as_string.length() + 1;
		char* bytes = (char*)malloc(length);
		memset(bytes, 0, length);
		memcpy(bytes, xml_as_string.c_str(), length - 1);
		f.write(bytes, length);
		f.close();
		free(bytes);
		bytes = 0;
	}
#else
	std::ofstream out(mConfigData.GetFullConfigPath().C_String());
	out << xml_as_string.c_str() << "\0";
	out.close();
#endif
}

void PredictConfig::Load()
{
	mConfigData.Reset();
#ifdef CHINESE_PATH
	QString temp = QStringLiteral("%1").arg(mConfigData.GetFullConfigPath().C_String());
	QFile f(temp);
	if (!f.open(QIODevice::ReadOnly))
	{
#if 0
		Save();
#endif
		return;
	}
	QByteArray byteArray = f.readAll();
	unsigned int fileLength = byteArray.length();
	const unsigned int _MAX_FILE_SIZE_ = fileLength + 1;
	char *doc = (char *)malloc(_MAX_FILE_SIZE_);
	memset(doc, 0, _MAX_FILE_SIZE_);
	memcpy(doc, byteArray.data(), _MAX_FILE_SIZE_);
	f.close();

#else
	DataStructures::FileStream stream(mConfigData.GetFullConfigPath().C_String(), "rb");
	if (!stream.CanRead())
	{
#if 0
		Save();
#endif
		return;
	}
	unsigned int fileLength = stream.Length();
	stream.Seek(0, SEEK_SET);
	const unsigned int _MAX_FILE_SIZE_ = fileLength + 1;
	char *doc = (char *)malloc(_MAX_FILE_SIZE_);
	memset(doc, 0, _MAX_FILE_SIZE_);
	stream.Read(doc, _MAX_FILE_SIZE_);
	stream.Close();
#endif

	rapidxml::xml_document<> XMLDoc;
	XMLDoc.parse<0>(doc);
	rapidxml::xml_node<> *rootNode = XMLDoc.first_node(PredictConfigData::filePathname);
	rapidxml::xml_node<> *node = rootNode->first_node(PredictConfigData::ipName);
	mConfigData.mIP = XMLUtils::GetAttrib(node, VALUE);
	node = rootNode->first_node(PredictConfigData::portName);
	mConfigData.mPort = XMLUtils::GetAttribInt(node, VALUE);

	node = rootNode->first_node(PredictConfigData::isCheckName);
	if (node)
	{
		mConfigData.mIsCheck = XMLUtils::GetAttribBool(node, VALUE);
	}
	node = rootNode->first_node(PredictConfigData::hasKeyFileName);
	mConfigData.mHasKeyFile = XMLUtils::GetAttribInt(node, VALUE);
	node = rootNode->first_node(PredictConfigData::keyFileName);
	if (node)
	{
		mConfigData.mKeyFile = XMLUtils::GetAttrib(node, VALUE);
	}
	node = rootNode->first_node(PredictConfigData::hasGenerateFileName);
	mConfigData.mHasGenerateFile = XMLUtils::GetAttribInt(node, VALUE);
	node = rootNode->first_node(PredictConfigData::generateKeyFileName);
	if (node)
	{
		mConfigData.mGenerateKeyFile = XMLUtils::GetAttrib(node, VALUE);
	}
	mConfigData.mIsCheck = mConfigData.mHasKeyFile && mConfigData.mGenerateKeyFile;
	node = rootNode->first_node(PredictConfigData::packageFileName);
	mConfigData.mPackageFile = XMLUtils::GetAttrib(node, VALUE);
	node = rootNode->first_node(PredictConfigData::perceptionFileName);
	mConfigData.mPerceptionFile = XMLUtils::GetAttrib(node, VALUE);
	node = rootNode->first_node(PredictConfigData::quntityThresholName);
	mConfigData.mBKQuntityThreshold = XMLUtils::GetAttribReal(node, VALUE);
	node = rootNode->first_node(PredictConfigData::sizeThresholName);
	mConfigData.mBKSizeThreshold = XMLUtils::GetAttribReal(node, VALUE);
	node = rootNode->first_node(PredictConfigData::minSize);
	if (node)
	{
		mConfigData.mBKMinSize = XMLUtils::GetAttribReal(node, VALUE);
	}
	node = rootNode->first_node(PredictConfigData::lengthKey);
	if (node)
	{
		mConfigData.mKeyLength = XMLUtils::GetAttribInt(node, VALUE);
	}
	node = rootNode->first_node(PredictConfigData::decreaseThreshold);
	if (node)
	{
		mConfigData.mDecreaseThreshold = XMLUtils::GetAttribReal(node, VALUE);
	}

	node = rootNode->first_node(PredictConfigData::maxPredictNumber);
	if (node)
	{
		mConfigData.mMaxPredictNumber = XMLUtils::GetAttribInt(node, VALUE);
	}
	node = rootNode->first_node(PredictConfigData::preIndexNumber);
	if (node)
	{
		mConfigData.mPreIndexNumber = XMLUtils::GetAttribInt(node, VALUE);
	}

	node = rootNode->first_node(PredictConfigData::writeTempFile);
	if (node)
	{
		mConfigData.mWriteTempFile = XMLUtils::GetAttribInt(node, VALUE);
	}

	node = rootNode->first_node(PredictConfigData::maxKeyCountPerConnection);
	if (node)
	{
		mConfigData.mMaxKeyCountPerConnection = XMLUtils::GetAttribInt(node, VALUE);
	}

	node = rootNode->first_node(PredictConfigData::compressionByName);
	if (node)
	{
		mConfigData.mCompression = XMLUtils::GetAttribBool(node, VALUE);
	}

	node = rootNode->first_node(PredictConfigData::cpThreashold);
	if (node)
	{
		mConfigData.mCpThreashold = XMLUtils::GetAttribReal(node, VALUE);
	}

	free(doc);
}

PredictConfig::PredictConfig(const DataStructures::HexString& dir) : mNeedStatistic(false)
{
	mConfigData.mDir = dir;
	InitializeNamemap();
	Load();
}

void PredictConfig::InitializeNamemap()
{
	mNameMap.Add(PredictConfigData::filePathname, 1);
	mNameMap.Add(PredictConfigData::ipName, 2);
	mNameMap.Add(PredictConfigData::portName, 3);
	mNameMap.Add(PredictConfigData::isCheckName, 4);
	mNameMap.Add(PredictConfigData::hasKeyFileName, 5);
	mNameMap.Add(PredictConfigData::hasGenerateFileName, 6);
	mNameMap.Add(PredictConfigData::keyFileName, 7);
	mNameMap.Add(PredictConfigData::generateKeyFileName, 8);
	mNameMap.Add(PredictConfigData::packageFileName, 9);
	mNameMap.Add(PredictConfigData::perceptionFileName, 10);
	mNameMap.Add(PredictConfigData::quntityThresholName, 11);
	mNameMap.Add(PredictConfigData::sizeThresholName, 12);
	mNameMap.Add(PredictConfigData::minSize, 13);
	mNameMap.Add(PredictConfigData::decreaseThreshold, 14);
	mNameMap.Add(PredictConfigData::maxPredictNumber, 15);
	mNameMap.Add(PredictConfigData::preIndexNumber, 16);
	mNameMap.Add(PredictConfigData::writeTempFile, 17);
	mNameMap.Add(PredictConfigData::maxKeyCountPerConnection, 18);
	mNameMap.Add(PredictConfigData::compressionByName, 19);
	mNameMap.Add(PredictConfigData::cpThreashold, 20);
}

PredictConfig::PredictConfig(bool load) : mNeedStatistic(false)
{
	InitializeNamemap();
	if (load)
	{
		Load();
	}
}

void PredictConfig::SetValue(const char* name, const char* value)
{
	int index = GetIndexByName(name);
	switch (index)
	{
	case 1:
		mConfigData.mFilePath = value;
		break;
	case 2:
		mConfigData.mIP = value;
		break;
	case 3:
		mConfigData.mPort = atoi(value);
		break;
	//case 4:
	//	mConfigData.mIsCheck = value[0] == 't' || value[0] == 'T';
	//	break;
	//case 5:
	//	mConfigData.mHasKeyFile = value[0] == 't' || value[0] == 'T';
	//	break;
	//case 6:
	//	mConfigData.mHasGenerateFile = value[0] == 't' || value[0] == 'T';
	//	break;
	case 7:
		mConfigData.mKeyFile = value;
		mConfigData.mHasKeyFile = true;
		if (mConfigData.mKeyFile == "")
			mConfigData.mHasKeyFile = false;
		mConfigData.mIsCheck = mConfigData.mHasKeyFile && mConfigData.mHasGenerateFile;
		break;
	case 8:
		mConfigData.mGenerateKeyFile = value;
		mConfigData.mHasGenerateFile = true;
		if (mConfigData.mGenerateKeyFile == "")
			mConfigData.mHasGenerateFile = false;
		mConfigData.mIsCheck = mConfigData.mHasKeyFile && mConfigData.mHasGenerateFile;
		break;
	case 9:
		mConfigData.mPackageFile = value;
		break;
	case 10:
		mConfigData.mPerceptionFile = value;
		break;
	case 11:
		mConfigData.mBKQuntityThreshold = atof(value);
		break;
	case 12:
		mConfigData.mBKSizeThreshold = atof(value);
		mNeedStatistic = true;
		break;
	case 13:
		mConfigData.mBKMinSize = atof(value);
		break;
	case 14:
		mConfigData.mDecreaseThreshold = atof(value);
		break;
	case 15:
		mConfigData.mMaxPredictNumber = atoi(value);
		break;
	case 16:
		mConfigData.mPreIndexNumber = atoi(value);
		break;
	case 17:
		mConfigData.mWriteTempFile = value[0] == 't' || value[0] == 'T';
		break;
	case 18:
		mConfigData.mMaxKeyCountPerConnection = atoi(value);
		break;
	case 19:
		mConfigData.mCompression = value[0] == 't' || value[0] == 'T';
		break;
	case 20:
		mConfigData.mCpThreashold = atof(value);
		break;
	default:
		break;
	}
}