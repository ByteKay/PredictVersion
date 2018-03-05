/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "PredictKeyHandleUI.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *mActionDocument;
    QAction *mActionOpen;
    QAction *mActionAbout;
    QAction *mActionPreferences;
    QAction *mNotice;
    QAction *mNoticeSomething;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *mStartPrint;
    QCheckBox *mCheckStart;
    QPushButton *mCalculateAll;
    QPushButton *mClearTextEditor;
    QHBoxLayout *horizontalLayout_5;
    QTextEdit *mTextEdit;
    QHBoxLayout *horizontalLayout;
    PredictKeyHandleUI *mKeyUi;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menu;
    QDockWidget *mGameDockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *mNoticeContent;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1122, 769);
        mActionDocument = new QAction(MainWindow);
        mActionDocument->setObjectName(QStringLiteral("mActionDocument"));
        mActionOpen = new QAction(MainWindow);
        mActionOpen->setObjectName(QStringLiteral("mActionOpen"));
        mActionAbout = new QAction(MainWindow);
        mActionAbout->setObjectName(QStringLiteral("mActionAbout"));
        mActionPreferences = new QAction(MainWindow);
        mActionPreferences->setObjectName(QStringLiteral("mActionPreferences"));
        mNotice = new QAction(MainWindow);
        mNotice->setObjectName(QStringLiteral("mNotice"));
        mNoticeSomething = new QAction(MainWindow);
        mNoticeSomething->setObjectName(QStringLiteral("mNoticeSomething"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_6 = new QHBoxLayout(centralwidget);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mStartPrint = new QCheckBox(centralwidget);
        mStartPrint->setObjectName(QStringLiteral("mStartPrint"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mStartPrint->sizePolicy().hasHeightForWidth());
        mStartPrint->setSizePolicy(sizePolicy);
        mStartPrint->setChecked(true);

        horizontalLayout_2->addWidget(mStartPrint);

        mCheckStart = new QCheckBox(centralwidget);
        mCheckStart->setObjectName(QStringLiteral("mCheckStart"));
        sizePolicy.setHeightForWidth(mCheckStart->sizePolicy().hasHeightForWidth());
        mCheckStart->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(mCheckStart);

        mCalculateAll = new QPushButton(centralwidget);
        mCalculateAll->setObjectName(QStringLiteral("mCalculateAll"));
        sizePolicy.setHeightForWidth(mCalculateAll->sizePolicy().hasHeightForWidth());
        mCalculateAll->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(mCalculateAll);

        mClearTextEditor = new QPushButton(centralwidget);
        mClearTextEditor->setObjectName(QStringLiteral("mClearTextEditor"));
        sizePolicy.setHeightForWidth(mClearTextEditor->sizePolicy().hasHeightForWidth());
        mClearTextEditor->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(mClearTextEditor);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        mTextEdit = new QTextEdit(centralwidget);
        mTextEdit->setObjectName(QStringLiteral("mTextEdit"));
        mTextEdit->setEnabled(true);
        QFont font;
        font.setFamily(QStringLiteral("Microsoft JhengHei"));
        font.setPointSize(16);
        mTextEdit->setFont(font);
        mTextEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(mTextEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        mKeyUi = new PredictKeyHandleUI(centralwidget);
        mKeyUi->setObjectName(QStringLiteral("mKeyUi"));

        horizontalLayout->addWidget(mKeyUi);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_6->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1122, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        mGameDockWidget = new QDockWidget(MainWindow);
        mGameDockWidget->setObjectName(QStringLiteral("mGameDockWidget"));
        mGameDockWidget->setEnabled(true);
        mGameDockWidget->setMinimumSize(QSize(310, 700));
        mGameDockWidget->setFloating(false);
        mGameDockWidget->setFeatures(QDockWidget::DockWidgetMovable);
        mGameDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QStringLiteral("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);
        treeView->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout->addWidget(treeView);

        mGameDockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), mGameDockWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setStyleSheet(QStringLiteral("color:rgb(255, 1, 5)"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        mNoticeContent = new QTextEdit(dockWidgetContents_2);
        mNoticeContent->setObjectName(QStringLiteral("mNoticeContent"));
        mNoticeContent->setReadOnly(true);

        verticalLayout_3->addWidget(mNoticeContent);

        dockWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menu->menuAction());
        menuFile->addAction(mActionDocument);
        menuFile->addAction(mActionOpen);
        menuFile->addSeparator();
        menuFile->addAction(mActionAbout);
        menuFile->addAction(mActionPreferences);
        menu->addAction(mNoticeSomething);

        retranslateUi(MainWindow);
        QObject::connect(mClearTextEditor, SIGNAL(clicked()), MainWindow, SLOT(onClearText()));
        QObject::connect(mCalculateAll, SIGNAL(clicked()), MainWindow, SLOT(onCalculateAll()));
        QObject::connect(mCheckStart, SIGNAL(toggled(bool)), MainWindow, SLOT(onCheckNow(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PredictTool", 0));
        mActionDocument->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\346\241\243", 0));
        mActionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\211\200\345\234\250\347\233\256\345\275\225", 0));
        mActionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
        mActionPreferences->setText(QApplication::translate("MainWindow", "\351\205\215\347\275\256\350\256\276\347\275\256", 0));
        mNotice->setText(QApplication::translate("MainWindow", "\346\263\250\346\204\217\344\272\213\351\241\271", 0));
        mNoticeSomething->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213", 0));
        mStartPrint->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\346\211\223\345\215\260", 0));
        mCheckStart->setText(QApplication::translate("MainWindow", "\351\252\214\350\257\201", 0));
        mCalculateAll->setText(QApplication::translate("MainWindow", "\344\270\200\351\224\256\350\256\241\347\256\227", 0));
        mClearTextEditor->setText(QApplication::translate("MainWindow", "\346\270\205\345\261\217", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\263\250\346\204\217\344\272\213\351\241\271", 0));
        mNoticeContent->setDocumentTitle(QApplication::translate("MainWindow", "\346\263\250\346\204\217\344\272\213\351\241\271", 0));
        mNoticeContent->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><title>\346\263\250\346\204\217\344\272\213\351\241\271</title><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">\346\263\250\346\204\217\344\272\213\351\241\271-&gt;\346\237\245\347\234\213(\345\205\263\351\227\255\346\210\226\346\230\276\347\244\272\346\255\244\345\206\205\345\256\271)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">0 \344\270\215\350\203\275\345\214\205\345\220\253\344\270\255\346\226\207\350\267\257\345\276\204\357\274\214\345\217\252\350\203"
                        "\275\346\230\257\350\213\261\346\226\207\350\267\257\345\276\204</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">1 \347\224\237\346\210\220Key\346\240\267\346\234\254\346\227\266\357\274\214\351\234\200\350\246\201\344\273\2160\347\255\211\347\272\247\347\216\251\350\265\267</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">  (1)\345\205\263\351\227\255\351\230\262\347\201\253\345\242\231\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">  (2)\346\265\213\350\257\225\344\272\272\345\221\230\346\265\213\350\257\225\345\211\215\357\274\214\345\205\263\351\227\255\347\214\216\350\261\271wifi\357\274\214\344"
                        "\273\245\345\205\215\350\277\236\346\216\245\344\270\215\344\270\212;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">  \346\210\226\350\200\205\344\277\256\346\224\271\347\214\216\350\261\271wifi\347\232\204\350\256\276\347\275\256\343\200\202\350\256\276\347\275\256\344\270\255\345\277\203-&gt;\351\253\230\347\272\247\350\256\276\347\275\256-&gt;\345\205\261\344\272\253\346\250\241\345\274\217,\345\213\276\351\200\211</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">  &quot;ICS\345\205\261\344\272\253\346\250\241\345\274\217&quot;(\350\257\245\347\275\221\347\273\234\346\250\241\345\274\217\344\270\213\357\274\214\351\231\220\351\200\237\344\274\232\350\242\253\347\246\201\346\255\242\346\216\211\357\274\214\350\267\221key\344\270\215\345\217"
                        "\227\345\275\261\345\223\215)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#000000;\">2 \344\270\200\351\224\256\350\256\241\347\256\227</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#000000;\">    \345\257\271\350\261\241\357\274\232\346\211\200\346\234\211\346\270\270\346\210\217</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#000000;\">    \345\212\237\350\203\275\357\274\232\350\256\241\347\256\227\346\211\200\346\234\211\346\273\241\350\266\263\350\247\204\345\210\2312\347\232\204\346\270\270\346\210\217\347\232\204Package.bin\345\222\214Perception.bin\344\270\244\344\270\252\346\226\207\344\273\266</span></p>\n"
"<p style=\" margi"
                        "n-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#000000;\">    \347\274\272\347\202\271\357\274\232\350\256\241\347\256\227\346\211\200\346\234\211\346\270\270\346\210\217\357\274\214\351\200\237\345\272\246\347\225\245\346\205\242\357\274\233\345\217\257\347\202\271\351\200\211\346\270\270\346\210\217\345\220\215\357\274\214\342\200\234\351\205\215\347\275\256\350\256\276\347\275\256\342\200\235\347\252\227\345\217\243\357\274\214\342\200\234\351\253\230\347\272\247\345\212\237\350\203\275\342\200\235\344\270\255\342\200\234\347\253\213\345\215\263\350\256\241\347\256\227\342\200\235\345\217\252\350\256\241\347\256\227\351\200\211\344\270\255\347\232\204\346\270\270\346\210\217</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">3 \351\252\214\350\257\201</span></p>\n"
"<p style=\" margin"
                        "-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">    \345\257\271\350\261\241\357\274\232\346\211\200\346\234\211\346\270\270\346\210\217</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">    \345\212\237\350\203\275\357\274\232\351\252\214\350\257\201\350\256\241\347\256\227\347\232\204\347\273\223\346\236\234\351\242\204\346\265\213\345\207\206\347\241\256\346\200\247\343\200\202\350\247\202\345\257\237\346\211\223\345\215\260\346\225\260\346\215\256</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">    \346\263\250\346\204\217\357\274\232\346\257\217\344\270\200\344\270\252\346\270\270\346\210\217\345\217\252\345\257\271\344\270\200\344\270\252"
                        "\347\216\251\345\256\266\350\277\233\350\241\214\351\252\214\350\257\201\357\274\214\345\271\266\344\270\215\346\230\257\350\257\245\346\270\270\346\210\217\347\232\204\346\211\200\346\234\211\347\216\251\345\256\266\357\274\233\345\274\200\345\220\257\351\252\214\350\257\201\345\220\216\357\274\214\351\207\215\346\226\260\350\277\236\346\216\245\345\215\263\345\217\257</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#000000;\">4 \351\252\214\350\257\201\347\273\223\346\236\234\346\257\224\350\276\203\346\273\241\346\204\217\347\232\204\346\203\205\345\206\265\344\270\213\357\274\214\344\275\277\347\224\250\347\224\237\346\210\220\347\232\204Package.bin\346\226\207\344\273\266\346\211\223\345\214\205\350\265\204\346\272\220</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;"
                        " color:#ff0000;\">5 \347\202\271\345\207\273\345\217\263\350\276\271\346\270\270\346\210\217\345\220\215\357\274\214\345\217\263\351\224\256\357\274\214\351\200\211\346\213\251 \346\211\223\345\274\200\347\233\256\345\275\225\357\274\214\345\217\257\344\273\245\345\277\253\351\200\237\345\256\232\344\275\215\345\210\260\347\243\201\347\233\230\347\233\256\345\275\225</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
