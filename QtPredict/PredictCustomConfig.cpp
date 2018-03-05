#ifndef CONSOLE
#include "PredictTypeDefines.h"
#include "PredictCustomConfig.h"
#include "PredictConfig.h"
#include <QMessageBox>
#include <QtVariantPropertyManager>
#include <QtTreePropertyBrowser>
#include "DS_HashTable.h"
#include <QCloseEvent>
#include "./fileUtils/_fileExists.h"

#include "PredictCalculate.h"
#include "PredictStatistic.h"

PredictCustomConfig::PredictCustomConfig(QWidget* parent) : QWidget(parent), ui(new Ui::CustomConfig()), mChanged(false)
{
	ui->setupUi(this);
	g_variantManager = new QtVariantPropertyManager();
	g_variantFactory = new QtVariantEditorFactory();
	ui->mCalculate->hide();
}

PredictCustomConfig::~PredictCustomConfig()
{
	if (ui)
		delete ui;
	ui = 0;
	g_variantsMap.Clear();
}

void PredictCustomConfig::SetConfig(PredictConfig* config)
{
	mConfig = config;
	Refresh();
}

void PredictCustomConfig::Refresh()
{
	if (mConfig)
	{
		PredictConfig* config = mConfig;
		if (g_topItem)
		{
			g_variantsMap[PredictConfigData::keyFileName]->setValue(config->mConfigData.mKeyFile.C_String());
			g_variantsMap[PredictConfigData::generateKeyFileName]->setValue(config->mConfigData.mGenerateKeyFile.C_String());
			g_variantsMap[PredictConfigData::quntityThresholName]->setValue(config->mConfigData.mBKQuntityThreshold);
			g_variantsMap[PredictConfigData::sizeThresholName]->setValue(config->mConfigData.mBKSizeThreshold);
			g_variantsMap[PredictConfigData::minSize]->setValue(config->mConfigData.mBKMinSize);
			g_variantsMap[PredictConfigData::decreaseThreshold]->setValue(config->mConfigData.mDecreaseThreshold);
			g_variantsMap[PredictConfigData::maxPredictNumber]->setValue(config->mConfigData.mMaxPredictNumber);
			g_variantsMap[PredictConfigData::preIndexNumber]->setValue(config->mConfigData.mPreIndexNumber);
			g_variantsMap[PredictConfigData::writeTempFile]->setValue(config->mConfigData.mWriteTempFile);
			g_variantsMap[PredictConfigData::maxKeyCountPerConnection]->setValue(config->mConfigData.mMaxKeyCountPerConnection);
			g_variantsMap[PredictConfigData::compressionByName]->setValue(config->mConfigData.mCompression);
			g_variantsMap[PredictConfigData::cpThreashold]->setValue(config->mConfigData.mCpThreashold);
		}
		else
		{
			g_variantsMap.Clear();
			g_topItem = g_variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), "Config");
			
			QtVariantProperty *item = g_variantManager->addProperty(QVariant::Bool, PredictConfigData::hasKeyFileName);
			item->setEnabled(false);
			item->setValue(config->mConfigData.mHasKeyFile);
			//g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::hasKeyFileName, item);
			item = g_variantManager->addProperty(QVariant::Bool, PredictConfigData::hasGenerateFileName);
			item->setEnabled(false);
			item->setValue(config->mConfigData.mHasGenerateFile);
			//g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::hasGenerateFileName, item);
			item = g_variantManager->addProperty(QVariant::String, PredictConfigData::keyFileName);
			item->setValue(config->mConfigData.mKeyFile.C_String());
			item->setEnabled(false);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::keyFileName, item);
			item = g_variantManager->addProperty(QVariant::String, PredictConfigData::generateKeyFileName);
			item->setValue(config->mConfigData.mGenerateKeyFile.C_String());
			item->setEnabled(false);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::generateKeyFileName, item);
			item = g_variantManager->addProperty(QVariant::String, PredictConfigData::packageFileName);
			item->setEnabled(false);
			item->setValue(config->mConfigData.mPackageFile.C_String());
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::packageFileName, item);
			item = g_variantManager->addProperty(QVariant::String, PredictConfigData::perceptionFileName);
			item->setEnabled(false);
			item->setValue(config->mConfigData.mPerceptionFile.C_String());
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::perceptionFileName, item);
			item = g_variantManager->addProperty(QVariant::Double, PredictConfigData::quntityThresholName);
			item->setAttribute(QLatin1String("decimals"), 6);
			item->setEnabled(false);
			item->setValue(config->mConfigData.mBKQuntityThreshold);
			item->setAttribute(QLatin1String("minimum"), 0);
			item->setAttribute(QLatin1String("maximum"), 1);
			item->setAttribute(QLatin1String("singleStep"), 0.01);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::quntityThresholName, item);
			item = g_variantManager->addProperty(QVariant::Double, PredictConfigData::sizeThresholName);
			item->setValue(config->mConfigData.mBKSizeThreshold);
			item->setAttribute(QLatin1String("minimum"), 0);
			item->setAttribute(QLatin1String("maximum"), 1);
			item->setAttribute(QLatin1String("singleStep"), 0.01);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::sizeThresholName, item);

			item = g_variantManager->addProperty(QVariant::Int, PredictConfigData::minSize);
			item->setValue(config->mConfigData.mBKMinSize);
			item->setEnabled(false);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::minSize, item);

			item = g_variantManager->addProperty(QVariant::Double, PredictConfigData::decreaseThreshold);
			item->setValue(config->mConfigData.mDecreaseThreshold);
			item->setAttribute(QLatin1String("minimum"), 0.05f);
			item->setAttribute(QLatin1String("maximum"), 0.95f);
			item->setAttribute(QLatin1String("singleStep"), 0.01);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::decreaseThreshold, item);

			item = g_variantManager->addProperty(QVariant::Int, PredictConfigData::maxPredictNumber);
			item->setValue(config->mConfigData.mMaxPredictNumber);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::maxPredictNumber, item);


			item = g_variantManager->addProperty(QVariant::Int, PredictConfigData::preIndexNumber);
			item->setValue(config->mConfigData.mPreIndexNumber);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::preIndexNumber, item);

			item = g_variantManager->addProperty(QVariant::Bool, PredictConfigData::writeTempFile);
			item->setValue(config->mConfigData.mWriteTempFile);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::writeTempFile, item);

			item = g_variantManager->addProperty(QVariant::Int, PredictConfigData::maxKeyCountPerConnection);
			item->setValue(config->mConfigData.mMaxKeyCountPerConnection);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::maxKeyCountPerConnection, item);

			item = g_variantManager->addProperty(QVariant::Bool, PredictConfigData::compressionByName);
			item->setValue(config->mConfigData.mCompression);
			g_topItem->addSubProperty(item);
			g_variantsMap.Add(PredictConfigData::compressionByName, item);
			item = g_variantManager->addProperty(QVariant::Double, PredictConfigData::cpThreashold);
			item->setValue(config->mConfigData.mCpThreashold);
			item->setEnabled(false);
			g_topItem->addSubProperty(item);
			item->setAttribute(QLatin1String("decimals"), 5);
			g_variantsMap.Add(PredictConfigData::cpThreashold, item);
			
			// to add here
			///////////////////////////////////////////////////////////////////////////////////////
			ui->mConfig->setFactoryForManager(g_variantManager, g_variantFactory);
			ui->mConfig->addProperty(g_topItem);
			ui->mConfig->setPropertiesWithoutValueMarked(true);
			ui->mConfig->setRootIsDecorated(false);
			ui->mConfig->setResizeMode(QtTreePropertyBrowser::ResizeMode::ResizeToContents);
			onStatistic();
			// add here
			connect(g_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
				this, SLOT(onValueChanged(QtProperty *, const QVariant &)));
			mChanged = false;
		}
		CheckKey();
		ui->mConfig->show();
	}
}

void PredictCustomConfig::CheckKey()
{
#ifdef CHINESE_PATH
	bool exist = QFile::exists(QStringLiteral("%1").arg(mConfig->mConfigData.GetFullKeyPath().C_String()));
#else
	bool exist = _fileExists(mConfig->mConfigData.GetFullKeyPath().C_String());
#endif
	if (!exist)
	{
		ui->mCheckOriginal->setText(QStringLiteral("原始key文件不存在，请设置！"));
		return;
	}
	else
	{
		ui->mCheckOriginal->setText("");
	}
	if (mConfig->mNeedStatistic)
	{
		mConfig->mNeedStatistic = false;
		onStatistic();
	}
}

#include "PredictPrint.h"

void PredictCustomConfig::onStatistic()
{
	if (mConfig)
	{
#ifdef CHINESE_PATH
		bool exist = QFile::exists(QStringLiteral("%1").arg(mConfig->mConfigData.GetFullKeyPath().C_String()));
#else
		bool exist = _fileExists(mConfig->mConfigData.GetFullKeyPath().C_String());
#endif
		if (!exist)
		{
			QMessageBox::question(NULL, "Notice", QStringLiteral("不存在原始key文件，请先上传或添加！"), QMessageBox::Yes);
			return;
		}
		// if (mConfig->mConfigData.mBKSizeThreshold != 0)
		{
			PredictStatistic statistic;
			ClientPrint::PrintMessage("", "统计计算中...");
			statistic.Statistic(mConfig);
			ClientPrint::PrintMessage("", "统计计算完成");
			mConfig->Save();
			Refresh();
		}
	}
}

void PredictCustomConfig::onCalculate()
{
	if (mConfig)
	{
#ifdef CHINESE_PATH
		bool exist = QFile::exists(QStringLiteral("%1").arg(mConfig->mConfigData.GetFullGeneratorPath().C_String()));
#else
		bool exist = _fileExists(mConfig->mConfigData.GetFullGeneratorPath().C_String());
#endif
		if (!exist)
		{
			QMessageBox::question(NULL, "Notice", QStringLiteral("不存在样本key文件，请先生成！"), QMessageBox::Yes);
			return;
		}
		if (mConfig->mConfigData.mBKMinSize == 0.0f)
		{
			PredictStatistic statictic;
			statictic.Statistic(mConfig);
		}
		PredictCalculate calculate;
		calculate.Calculate(&mConfig->mConfigData);
		QMessageBox::question(NULL, "Notice", QStringLiteral("计算完成，请查看结果。"), QMessageBox::Yes);
	}
}

void PredictCustomConfig::onShowMore()
{
	if (ui->mCalculate->isHidden())
	{
		ui->mCalculate->show();
	}
	else
	{
		ui->mCalculate->hide();
	}
}

void PredictCustomConfig::onValueChanged(QtProperty* prop, const QVariant &var)
{
	// Be aware that it should not use prop->propertyName().toStdString().c_str(). otherwise, there will be wrong.
	std::string str = prop->propertyName().toStdString();
	const char* name = str.c_str();
	std::string str2 = prop->valueText().toStdString();
	const char* value = str2.c_str();
	mConfig->SetValue(name, value);
	Refresh();
	mChanged = true;
}

void PredictCustomConfig::closeEvent(QCloseEvent *event)
{
	if (mChanged)
	{
		QMessageBox::StandardButton button = QMessageBox::question(NULL, "Notice", QStringLiteral("文件有改变，需要保存吗？"), QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes);
		if (button == QMessageBox::Yes)
		{
			onSave();
		}
	}
}

void PredictCustomConfig::onSave()
{
	if (mConfig)
	{
		mConfig->Save();
	}
	this->hide();
	onShowMore();
}

void PredictCustomConfig::onCancel()
{
	this->hide();
	onShowMore();
}
#endif