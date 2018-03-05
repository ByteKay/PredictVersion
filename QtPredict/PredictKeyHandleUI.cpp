/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/
#ifndef CONSOLE
#include "PredictKeyHandleUI.h"
#include "PredictGeneratorKey.h"
#include "PredictMainWindow.h"
#include "QDebug"
#include "PredictCheck.h"

TextEditorThread::TextEditorThread() : mStopped(false)
{

}

TextEditorThread::~TextEditorThread()
{
	mMessages.Clear();
}
void TextEditorThread::Push(const QString& text)
{
	mMutex.Lock();
	mMessages.Push(text);
	mMutex.Unlock();
}

void TextEditorThread::SetStop(bool isStop)
{
	mStopped = isStop;
}

void TextEditorThread::run()
{
	while (!mStopped)
	{	
		while (mMessages.Size() > 0)
		{
			mMutex.Lock();
			emit MsgSignal(mMessages.Pop());
			mMutex.Unlock();
		}
		QThread::msleep(1);
	}
}

PredictKeyHandleUI::PredictKeyHandleUI(QWidget* parent) : QWidget(parent), ui(new Ui::GeneratorUI())
{
	ui->setupUi(this);
	mTextEditor = new TextEditorThread();
	mTextEditor->start();
}

PredictKeyHandleUI::~PredictKeyHandleUI()
{
	if (ui)
	{
		delete ui;
	}
	ui = 0;
	mTextEditor->SetStop(true);
	while (mTextEditor->isRunning())
	{
		Sleep(2);
	}
	if (mTextEditor)
		delete mTextEditor;
	mTextEditor = 0;
}

void PredictKeyHandleUI::LoadOldKeySequence()
{
	//PredictGeneratorKey::Instance()->Clear();
	//PredictGeneratorKey::Instance()->LoadFromFile(PredictConfig::Inistance()->mConfigData.GetFullGeneratorPath().C_String());
}



void PredictKeyHandleUI::onStart()
{
	//LoadOldKeySequence();
	//PredictCheck::Instance()->Start();
	//PredictMainWindow* mainWind = (PredictMainWindow*)mOwner;
	//mainWind->StartServer();
	//ui->mGeneratorKey->setEnabled(false);
	//ui->mStart->setEnabled(false);
	//ui->mDump->setEnabled(true);
	//ui->mStop->setEnabled(true);
}

void PredictKeyHandleUI::onDump()
{
	//PredictGeneratorKey::Instance()->WriteToFile(PredictConfig::Inistance()->mConfigData.GetFullGeneratorPath().C_String());
}

void PredictKeyHandleUI::onStop()
{
	//PredictGeneratorKey::Instance()->WriteToFile(PredictConfig::Inistance()->mConfigData.GetFullGeneratorPath().C_String());
	//mTextEditor->Push("Write keys file successfully!");
	//PredictMainWindow* mainWind = (PredictMainWindow*)mOwner;
	//mainWind->StopServer();
	//ui->mGeneratorKey->setEnabled(true);
	//ui->mStart->setEnabled(true);
	//ui->mDump->setEnabled(false);
	//ui->mStop->setEnabled(false);
	
}

void PredictKeyHandleUI::onToggle(bool state)
{
	//PredictGeneratorKey::Instance()->ToggleGeneratorKey(state);
}

void PredictKeyHandleUI::PrintMessage(const QString& text)
{
	mTextEditor->Push(text);
}

void PredictKeyHandleUI::SetMainWidget(PredictMainWindow* owner)
{
	mOwner = owner;
	if (mOwner)
	{
		connect(mTextEditor, SIGNAL(MsgSignal(const QString&)), mOwner, SLOT(printText(const QString&)));
	}
}

void PredictKeyHandleUI::closeEvent(QCloseEvent *event)
{
	//if (ui->mStop->isEnabled())
	//{
	//	onStop();
	//}
}
#endif