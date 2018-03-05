/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef CONSOLE
#ifndef _PREDICTGENERATORKEYUI_H
#define _PREDICTGENERATORKEYUI_H
#include "PredictTypeDefines.h"
#include "ui_generator.h"
#include "HexString.h"
#include <QWidget>
#include <QThread>
#include "DS_Queue.h"
#include "SimpleMutex.h"
#pragma execution_character_set("utf-8")
class PredictMainWindow;

class TextEditorThread : public QThread
{
	Q_OBJECT
public:
	TextEditorThread();
	~TextEditorThread();
	void Push(const QString& text);
	void SetStop(bool);
signals:
	void MsgSignal(const QString& text);
protected:
	void run();
private:
	SimpleMutex mMutex;
	bool mStopped;
	DataStructures::Queue<QString> mMessages;
};

class PredictKeyHandleUI : public QWidget
{
	Q_OBJECT
public:
	PredictKeyHandleUI(QWidget* parent = 0);
	~PredictKeyHandleUI();
	void SetMainWidget(PredictMainWindow* owner);
	void PrintMessage(const QString&  text);

protected:
	void closeEvent(QCloseEvent *event);
private:
	// first, do it
	void LoadOldKeySequence();

signals:
	void printText(const DataStructures::HexString text);

private slots:
	void onStart();
	void onDump();
	void onStop();
	void onToggle(bool state);
private:
	Ui::GeneratorUI *ui;
	PredictMainWindow* mOwner;
	TextEditorThread* mTextEditor;
};
#endif
#endif