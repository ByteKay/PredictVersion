/*
Time  : 2016/06/13
Author: Kay Yang (1025115216@qq.com)
*/

#ifndef CONSOLE
#include "PredictMainWindow.h"
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QUrl>
#include <QtVariantEditorFactory>
#include <QtTreePropertyBrowser>
#include <QMessageBox>
#include "FormatString.h"
#include "DS_HashTable.h"
#include "PredictKeyHandleUI.h"
#include "PredictCalculate.h"
#include "PredictCheck.h"
#include "PredictGeneratorKey.h"
#include "DS_ByteQueue.h"
#include "PredictPrint.h"
#include "PredictConfig.h"
#include "PredictCustomConfig.h"
#include "PredictCommand.h"
#include "PredictGameThread.h"
#include "PredictStatistic.h"
#include "PredictSession.h"

QString g_currentFileDir = QDir::currentPath();
QString g_gameName;
QString g_currentFilePath;
QString g_statisticDir = g_currentFileDir;
PredictKeyHandleUI* g_generatorUi = 0;

#ifdef WIN32
void FindIP(DataStructures::HexString& ip)
{
	WORD v = MAKEWORD(1, 1);
	WSADATA wsaData;
	WSAStartup(v, &wsaData);
	struct hostent *phostinfo = gethostbyname("");
	char *p = inet_ntoa(*((struct in_addr *)(*phostinfo->h_addr_list)));
	ip = p;
	WSACleanup();
}

void PredictMainWindow::GetLocalIPs(DataStructures::HexString& mIP)
{
	int maxCnt = 10;

	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		return;
	}

	char hostname[256];
	ret = gethostname(hostname, sizeof(hostname));
	if (ret == SOCKET_ERROR)
	{
		return;
	}

	HOSTENT* host = gethostbyname(hostname);
	if (host == NULL)
	{
		return;
	}

	int cnt = host->h_length<maxCnt ? host->h_length : maxCnt;
	for (int i = 0; i < cnt; i++)
	{
		in_addr* addr = (in_addr*)*host->h_addr_list;
		char* ip = inet_ntoa(addr[i]);
		PrintText(ip);
		if (ip[0] == '1' && ip[1] == '7' && ip[2] == '2')
		{
			mIP = ip;		
			break;
		}
	}
	WSACleanup();
}

#endif

PredictMainWindow::PredictMainWindow(QWidget *parent) : ui(new Ui::MainWindow())
{
	mConnect = false;
	mServer = 0;
	mIP = "0.0.0.0";
	ui->setupUi(this);
	ui->statusBar->showMessage(tr("欢迎使用，有疑问联系QQ:1025115216或查看注意事项"));
	if (!g_generatorUi)
	{
		g_generatorUi = ui->mKeyUi;
		g_generatorUi->SetMainWidget(this);
		ClientPrint::SetPrint(g_generatorUi);
		g_generatorUi->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
		g_generatorUi->hide();
	}
	InitializeDir();
	BindSignalAndSlot();
#ifdef WIN32
	// GetLocalIPs(mIP);
#endif
}

PredictMainWindow::~PredictMainWindow()
{
	if (ui)
	{
		delete ui;
		ui = 0;
	}
	Close();
	google::protobuf::ShutdownProtobufLibrary();
}


void PredictMainWindow::closeEvent(QCloseEvent *event)
{
	StopServer();
	if (mServer)
		delete mServer;
	mServer = 0;
	if (mApp)
	{
		mApp->closeAllWindows();
	}
}

void PredictMainWindow::Close()
{
	//PredictConfig::Inistance()->Save();
}

void PredictMainWindow::StartServer()
{
	if (!mConnect)
	{
		PredictServerConfigData serverData;
		if (!mServer)
		{
			
			mServer = new PredictServerImpl;
			serverData.mIP = mIP;
			serverData.mPort = mPort;
			mServer->SetConfigData(serverData);
			mServer->Start();
		}
		else
		{
			serverData.mPort = mPort;
			serverData.mIP = mIP;
			mServer->SetConfigData(serverData);
			mServer->Start();
		}
		PrintText(FormatString("服务已开启 %s:%d ...", mIP.C_String(), serverData.mPort));
		mConnect = true;
	}
}

void PredictMainWindow::printText(const QString& text)
{
	std::string str =  text.toStdString();
	PrintText(str.c_str());
}

void PredictMainWindow::StopServer()
{
	if (mConnect)
	{
		if (mServer)
		{
			mServer->Stop();
			PrintText("Server stop ...");
		}
		mConnect = false;
	}
}

void PredictMainWindow::onClearText()
{
	ui->mTextEdit->clear();
}

void PredictMainWindow::onNotice()
{
	if (ui->dockWidget->isHidden())
	{
		ui->dockWidget->show();
	}
	else
	{
		ui->dockWidget->hide();
	}
}

void PredictMainWindow::onCheckNow(bool state)
{
	bool checked = ui->mCheckStart->isChecked();
	PredictGameThread::SetNeedCheck(checked);
	if (checked)
	{
		static QMessageBox customMsgBox;
		customMsgBox.setWindowTitle(tr("验证"));
		customMsgBox.setText("验证只对有Perception.txt文件的游戏有效");
		customMsgBox.exec();
	}
	//QFileSystemModel* model = (QFileSystemModel*)ui->treeView->model();
	//QDir root = model->rootDirectory();
	//QFileInfoList infoList = root.entryInfoList();
	//int size = infoList.size();
	//for (int i = 0; i < size; ++i)
	//{
	//	QFileInfo& info = infoList[i];
	//	if (info.isDir())
	//	{
	//		string gameName = info.fileName().toStdString();
	//		string path = info.filePath().toStdString();
	//		static PredictConfig config;
	//		config.mConfigData.mDir = path.c_str();
	//		bool exist = PredictGameThread::ExistFile(config.mConfigData.GetFullKeyPath()) && PredictGameThread::ExistFile(config.mConfigData.GetFullPerceptionPath());
	//		exist = exist && checked;
	//		if (checked && !exist)
	//		{
	//			PrintText(FormatString("%s： 没有key.bin文件或者Perception.bin文件，请先生成, 然后再验证,验证无效", gameName.c_str()));
	//		}
	//		PredictGameThread* gameThread = PredictCommandManager::Instance()->GetThreadByName(gameName.c_str());
	//		if (gameThread)
	//		{
	//			gameThread->GetConfig()->mConfigData.mIsCheck = exist;
	//		}
	//		else
	//		{
	//			config.Load();
	//			config.mConfigData.mIsCheck = exist;
	//			config.Save();
	//		}
	//	}
	//}
}

void PredictMainWindow::onCalculateAll()
{
	// static PredictCustomConfig customConfig;
	QFileSystemModel* model = (QFileSystemModel*)ui->treeView->model();
	QDir root = model->rootDirectory();
	QFileInfoList infoList = root.entryInfoList();
	int size = infoList.size();
	//for (int i = 0; i < size; ++i)
	//{
	//	static PredictConfig config;
	//	QFileInfo& info = infoList[i];
	//	if (info.isDir())
	//	{
	//		string gameName = info.absoluteFilePath().toStdString();
	//		int len = strlen(gameName.c_str());
	//		int count = gameName.length();
	//		if (len != count)
	//		{
	//			PrintText(FormatString("存在中文路径，请改成英文路径 ： %s", gameName.c_str()));
	//			return;
	//		}
	//	}
	//}
	for (int i = 0; i < size; ++i)
	{
		static PredictConfig config;
		QFileInfo& info = infoList[i];
		if (info.isDir())
		{
			string gameName = info.fileName().toStdString();
			string path = info.filePath().toStdString();	
			config.mConfigData.mDir = path.c_str();
			if (PredictGameThread::ExistFile(config.mConfigData.GetFullKeyPath()) && PredictGameThread::ExistFile(config.mConfigData.GetFullGeneratorPath()))
			{
				PredictGameThread* gameThread = PredictCommandManager::Instance()->GetThreadByName(gameName.c_str());
				if (gameThread)
				{
					// may be syn when loading generator file
					gameThread->Calculate();
				}
				else
				{
					PredictCalculate calculate;
					calculate.mGameName = gameName.c_str();
					config.Load();
					if (config.mConfigData.mBKMinSize == 0.0f)
					{
						PredictStatistic statistic;
						statistic.Statistic(&config);
					}
					calculate.Calculate(&config.mConfigData);
					config.Save();
				}
			}
			else
			{
				PrintText(FormatString("%s： 没有generator.bin文件或者key.bin文件，请检查", gameName.c_str()));
			}
		}
	}
}

void PredictMainWindow::onPreference()
{
	static PredictCustomConfig customConfig;
	string gameName = g_gameName.toStdString();
	PredictGameThread* gameThread = PredictCommandManager::Instance()->GetThreadByName(gameName.c_str());
	if (gameThread)
	{
		customConfig.SetConfig(gameThread->GetConfig());
	}
	else
	{
		static PredictConfig config;
		string gameNameDir = g_currentFileDir.toStdString();
		config.mConfigData.mDir = gameNameDir.c_str();
		// QString temp = QStringLiteral("%1").arg(config.mConfigData.mDir.C_String());
		config.Load();
		customConfig.SetConfig(&config);
	}
	customConfig.show();
}

void PredictMainWindow::onDuplicate()
{
	DataStructures::ThreadSafeList<PredictSession*>* sessions = PredictSessionManager::Instance()->GetSessions();
	DataStructures::List<PredictSession*>*lists = sessions->LockList();
	int size = lists->Size();
	std::set<int> tempSession;
	PredictSession* session = 0;
	for (int i = 0; i < size; ++i)
	{
		session = (*lists)[i];
		tempSession.insert(session->GetSessionId());
	}
	sessions->ReleaseList();
	if (tempSession.size() != size)
	{
		ClientPrint::PrintMessage("", "at least two same session id");
	}
	tempSession.clear();
}

void PredictMainWindow::onOpen()
{
	static QString prefix = "file:///";
	QDesktopServices::openUrl(QUrl((prefix + g_currentFileDir), QUrl::TolerantMode));
}

void PredictMainWindow::InitializeDir()
{
	QFileSystemModel* model = new QFileSystemModel();
	QString str = QDir::currentPath();
	str += "/res";
	model->setRootPath(str);
	//// filter
	QStringList filter;
	filter << "*.bin";
	model->setNameFilterDisables(false);
	model->setNameFilters(filter);
	ui->treeView->setSortingEnabled(false);
	ui->treeView->setModel(model);
	ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	ui->treeView->setRootIndex(model->index(str));
}


void PredictMainWindow::BindSignalAndSlot()
{
	connect(ui->treeView, SIGNAL(doubleClicked(const QModelIndex &)),
		this, SLOT(onDoubleClicked(const QModelIndex&)));
	connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &)),
		this, SLOT(onFileViewMenuReq(const QPoint &)));
	connect(ui->treeView, SIGNAL(pressed(const QModelIndex&)),
		this, SLOT(onFileViewPress(const QModelIndex &)));
	connect(ui->mActionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
	connect(ui->mActionDocument, SIGNAL(triggered()), this, SLOT(onDocument()));
	connect(ui->mActionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	connect(ui->mActionPreferences, SIGNAL(triggered()), this, SLOT(onPreference()));
	connect(ui->mNoticeSomething, SIGNAL(triggered()), this, SLOT(onNotice()));
}

void PredictMainWindow::onAbout()
{
	static QMessageBox customMsgBox;
	customMsgBox.setWindowTitle("About");
	customMsgBox.setText("It is used to predict game resource loaded in some orders.\nIf you have some question about it, please contact us!\nBest Wishes.\n");
	customMsgBox.exec();
}

void PredictMainWindow::onDocument()
{
	// just open the document's folder
	// see onOpen
	QString temp = g_currentFileDir;
	g_currentFileDir = QDir::currentPath();
	onOpen();
	g_currentFileDir = temp;
}

void PredictMainWindow::onDoubleClicked(const QModelIndex& index)
{
	StoreCurrentFile(index);
}

void PredictMainWindow::onFileViewMenuReq(const QPoint & pos)
{
	QMenu* menu = new QMenu(ui->treeView);
	QAction *actionOpen = new QAction(0);
	actionOpen->setText(QStringLiteral("打开目录"));
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	menu->addAction(actionOpen);
	menu->addSeparator();
	menu->addAction(ui->mActionPreferences);
	menu->addSeparator();
	QAction *actionCheck = new QAction(0);
	actionCheck->setText(QStringLiteral("检查连接重复id"));
	menu->addAction(actionCheck);
	connect(actionCheck, SIGNAL(triggered()), this, SLOT(onDuplicate()));
	menu->exec(QCursor::pos());
	delete actionOpen;
}

void PredictMainWindow::onFileViewPress(const QModelIndex &index)
{
	StoreCurrentFile(index);
}



void PredictMainWindow::StoreCurrentFile(const QModelIndex &index)
{
	QFileSystemModel* model = static_cast<QFileSystemModel*>(ui->treeView->model());
	QFileInfo info = model->fileInfo(index);
	if (info.filePath() != g_currentFilePath)
	{
		g_currentFilePath = info.filePath();
		if (info.isFile())
		{
			if (g_currentFileDir != info.absoluteDir().absolutePath())
			{
				g_gameName = info.absoluteDir().dirName();
				g_currentFileDir = info.absoluteDir().absolutePath();
				ui->mTextEdit->append(g_currentFileDir);
			}
		}
		else if(info.isDir())
		{
			if (g_currentFileDir != g_currentFilePath)
			{
				g_gameName = info.fileName();
				g_currentFileDir = g_currentFilePath;
				ui->mTextEdit->append(g_currentFileDir);
			}
		}

	}
}

void PredictMainWindow::PrintText(const DataStructures::HexString& message)
{
	if (ui->mStartPrint->isChecked())
	{
		static int count = 1;
		if (count > 5000)
		{
			ui->mTextEdit->clear();
			count = 0;
		}
		ui->mTextEdit->append(message.C_String());

		QTextCursor cursor = ui->mTextEdit->textCursor();
		cursor.movePosition(QTextCursor::End);
		ui->mTextEdit->setTextCursor(cursor);
	}

}
#endif