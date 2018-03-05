#ifndef CONSOLE
#ifndef _PREDICTCUSTOMCONFIG_H
#define _PREDICTCUSTOMCONFIG_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_custom.h"
#include "HexString.h"
#include "DS_HashTable.h"
class PredictConfig;
class QtProperty;
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtTreePropertyBrowser;
class QVariant;
class QtVariantProperty;
class PredictCustomConfig : public QWidget
{
	Q_OBJECT
public:
	PredictCustomConfig(QWidget* parent = 0);
	~PredictCustomConfig();
	void SetConfig(PredictConfig* config);

protected:
	void closeEvent(QCloseEvent *event);
public slots:
	void onSave();
	void onCancel();
	void onValueChanged(QtProperty* prop, const QVariant &var);
	void onShowMore();
	void onStatistic();
	void onCalculate();
private:
	void Refresh();
	void CheckKey();
private:
	Ui::CustomConfig* ui;
	PredictConfig* mConfig;
	bool mChanged;
private:
	QtVariantPropertyManager* g_variantManager = 0;
	QtVariantEditorFactory* g_variantFactory = 0;
	QtTreePropertyBrowser* g_variantEditor = 0;
	QtProperty* g_topItem = 0;
	DataStructures::HashTable<DataStructures::HexString, QtVariantProperty *> g_variantsMap;
};
#endif
#endif