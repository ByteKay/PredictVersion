/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef CONSOLE
#ifndef _QtPredictMainWindow_H
#define _QtPredictMainWindow_H
#include "PredictTypeDefines.h"
#include "PredictServerImpl.h"
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QWidget>
#include "ui_mainwindow.h"

class QtProperty;
class PredictMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	PredictMainWindow(QWidget *parent = 0);
	~PredictMainWindow();

	// close it, maybe want save the config information. confirm it ?
	void Close();
	void StartServer();
	void StopServer();
	void PrintText(const DataStructures::HexString& message);
protected:
	void closeEvent(QCloseEvent *event);

public slots:
	void onCheckNow(bool state);
	void onCalculateAll();
	void onNotice();
	void onPreference();
	void onOpen();
	void onDuplicate();
	void onAbout();
	void onDocument();
	void printText(const QString& text);
	void onClearText();
	// file
	void onDoubleClicked(const QModelIndex& index);
	void onFileViewMenuReq(const QPoint & pos);
	void onFileViewPress(const QModelIndex &index);
private:
	void InitializeDir();
	void BindSignalAndSlot();
	void StoreCurrentFile(const QModelIndex &index);
public:
	QApplication* mApp;
	DataStructures::HexString mIP;
	__u16 mPort;
private:
#ifdef WIN32
	void GetLocalIPs(DataStructures::HexString& mIP);
#endif
	Ui::MainWindow *ui;
	PredictServerImpl* mServer;
	bool mConnect;
};

#endif
#endif