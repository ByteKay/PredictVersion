/********************************************************************************
** Form generated from reading UI file 'generator.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATOR_H
#define UI_GENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneratorUI
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTextEdit *mTextEdit;
    QHBoxLayout *horizontalLayout;
    QCheckBox *mGeneratorKey;
    QPushButton *mStart;
    QPushButton *mDump;
    QPushButton *mStop;

    void setupUi(QWidget *GeneratorUI)
    {
        if (GeneratorUI->objectName().isEmpty())
            GeneratorUI->setObjectName(QStringLiteral("GeneratorUI"));
        GeneratorUI->resize(733, 205);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GeneratorUI->sizePolicy().hasHeightForWidth());
        GeneratorUI->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(GeneratorUI);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mTextEdit = new QTextEdit(GeneratorUI);
        mTextEdit->setObjectName(QStringLiteral("mTextEdit"));
        mTextEdit->setReadOnly(true);

        verticalLayout->addWidget(mTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mGeneratorKey = new QCheckBox(GeneratorUI);
        mGeneratorKey->setObjectName(QStringLiteral("mGeneratorKey"));
        mGeneratorKey->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mGeneratorKey->sizePolicy().hasHeightForWidth());
        mGeneratorKey->setSizePolicy(sizePolicy1);
        mGeneratorKey->setChecked(true);

        horizontalLayout->addWidget(mGeneratorKey);

        mStart = new QPushButton(GeneratorUI);
        mStart->setObjectName(QStringLiteral("mStart"));
        sizePolicy1.setHeightForWidth(mStart->sizePolicy().hasHeightForWidth());
        mStart->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QStringLiteral(":/start/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        mStart->setIcon(icon);
        mStart->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(mStart);

        mDump = new QPushButton(GeneratorUI);
        mDump->setObjectName(QStringLiteral("mDump"));
        mDump->setEnabled(false);
        sizePolicy1.setHeightForWidth(mDump->sizePolicy().hasHeightForWidth());
        mDump->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(mDump);

        mStop = new QPushButton(GeneratorUI);
        mStop->setObjectName(QStringLiteral("mStop"));
        mStop->setEnabled(false);
        sizePolicy1.setHeightForWidth(mStop->sizePolicy().hasHeightForWidth());
        mStop->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/stop/images/stop.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        mStop->setIcon(icon1);

        horizontalLayout->addWidget(mStop);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(GeneratorUI);
        QObject::connect(mStart, SIGNAL(clicked()), GeneratorUI, SLOT(onStart()));
        QObject::connect(mDump, SIGNAL(clicked()), GeneratorUI, SLOT(onDump()));
        QObject::connect(mStop, SIGNAL(clicked()), GeneratorUI, SLOT(onStop()));
        QObject::connect(mGeneratorKey, SIGNAL(toggled(bool)), GeneratorUI, SLOT(onToggle(bool)));

        QMetaObject::connectSlotsByName(GeneratorUI);
    } // setupUi

    void retranslateUi(QWidget *GeneratorUI)
    {
        GeneratorUI->setWindowTitle(QApplication::translate("GeneratorUI", "GeneratorKey", 0));
        mTextEdit->setHtml(QApplication::translate("GeneratorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\350\277\231\344\270\200\346\255\245\357\274\214\345\267\262\347\273\217\346\214\207\345\256\232\344\272\206\350\276\223\345\207\272\346\226\207\344\273\266\345\220\215\357\274\214\346\216\245\344\270\213\346\235\245\351\200\211\346\213\251\345\212\237\350\203\275\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ff0000;\">IsGeneratorKey</span><span style=\" font-size:12pt;\">: \351\273\230\350\256\244"
                        "\346\230\257\345\213\276\351\200\211\357\274\214\350\241\250\347\244\272\346\224\266\351\233\206keys\357\274\233\345\217\226\346\266\210\345\213\276\351\200\211\357\274\214\350\241\250\347\244\272\351\252\214\350\257\201\351\242\204\346\265\213\347\232\204\345\207\206\347\241\256\346\200\247,\345\220\214\346\227\266\344\271\237\344\274\232\346\224\266\351\233\206keys.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ff0000;\">Start</span><span style=\" font-size:12pt;\">\357\274\232\345\274\200\345\220\257\346\234\215\345\212\241\347\253\257\357\274\214\346\220\234\351\233\206\346\240\267\346\234\254keys.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ff0000;\">Stop</span><span style=\" font-size:12pt;\">\357\274\232\345\205\263\351\227\255\346\234\215\345\212\241"
                        "\347\253\257</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt;\">\347\202\271\345\207\273Generator/Check\345\205\263\351\227\255\346\210\226\346\230\276\347\244\272\346\255\244\347\252\227\345\217\243</span></p></body></html>", 0));
        mGeneratorKey->setText(QApplication::translate("GeneratorUI", "IsGeneratorKey", 0));
        mStart->setText(QApplication::translate("GeneratorUI", "Start", 0));
        mDump->setText(QApplication::translate("GeneratorUI", "Dump", 0));
        mStop->setText(QApplication::translate("GeneratorUI", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class GeneratorUI: public Ui_GeneratorUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATOR_H
