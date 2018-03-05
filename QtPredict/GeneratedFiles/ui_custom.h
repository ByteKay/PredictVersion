/********************************************************************************
** Form generated from reading UI file 'custom.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOM_H
#define UI_CUSTOM_H

#include <QtCore/QVariant>
#include <QtTreePropertyBrowser>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QClickLabel.h"

QT_BEGIN_NAMESPACE

class Ui_CustomConfig
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QtTreePropertyBrowser *mConfig;
    QLabel *mCheckOriginal;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *mSave;
    QPushButton *mCancel;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QClickLabel *mClickLabel;
    QLabel *mIndicate;
    QPushButton *mCalculate;

    void setupUi(QWidget *CustomConfig)
    {
        if (CustomConfig->objectName().isEmpty())
            CustomConfig->setObjectName(QStringLiteral("CustomConfig"));
        CustomConfig->resize(880, 700);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CustomConfig->sizePolicy().hasHeightForWidth());
        CustomConfig->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(CustomConfig);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mConfig = new QtTreePropertyBrowser(CustomConfig);
        mConfig->setObjectName(QStringLiteral("mConfig"));
        sizePolicy.setHeightForWidth(mConfig->sizePolicy().hasHeightForWidth());
        mConfig->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(mConfig);


        verticalLayout->addLayout(horizontalLayout);

        mCheckOriginal = new QLabel(CustomConfig);
        mCheckOriginal->setObjectName(QStringLiteral("mCheckOriginal"));
        QFont font;
        font.setPointSize(16);
        mCheckOriginal->setFont(font);
        mCheckOriginal->setStyleSheet(QStringLiteral("color: rgb(255, 10, 34);"));

        verticalLayout->addWidget(mCheckOriginal);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mSave = new QPushButton(CustomConfig);
        mSave->setObjectName(QStringLiteral("mSave"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mSave->sizePolicy().hasHeightForWidth());
        mSave->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(mSave);

        mCancel = new QPushButton(CustomConfig);
        mCancel->setObjectName(QStringLiteral("mCancel"));
        sizePolicy1.setHeightForWidth(mCancel->sizePolicy().hasHeightForWidth());
        mCancel->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(mCancel);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, 0);
        mClickLabel = new QClickLabel(CustomConfig);
        mClickLabel->setObjectName(QStringLiteral("mClickLabel"));
        sizePolicy1.setHeightForWidth(mClickLabel->sizePolicy().hasHeightForWidth());
        mClickLabel->setSizePolicy(sizePolicy1);
        mClickLabel->setStyleSheet(QStringLiteral("color: rgb(255, 10, 34);"));

        horizontalLayout_3->addWidget(mClickLabel);

        mIndicate = new QLabel(CustomConfig);
        mIndicate->setObjectName(QStringLiteral("mIndicate"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mIndicate->sizePolicy().hasHeightForWidth());
        mIndicate->setSizePolicy(sizePolicy2);
        mIndicate->setStyleSheet(QStringLiteral("color: rgb(255, 10, 34);"));

        horizontalLayout_3->addWidget(mIndicate);


        verticalLayout_2->addLayout(horizontalLayout_3);

        mCalculate = new QPushButton(CustomConfig);
        mCalculate->setObjectName(QStringLiteral("mCalculate"));
        sizePolicy1.setHeightForWidth(mCalculate->sizePolicy().hasHeightForWidth());
        mCalculate->setSizePolicy(sizePolicy1);
        mCalculate->setStyleSheet(QStringLiteral("color: rgb(35, 6, 255);"));

        verticalLayout_2->addWidget(mCalculate);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(CustomConfig);
        QObject::connect(mSave, SIGNAL(clicked()), CustomConfig, SLOT(onSave()));
        QObject::connect(mCancel, SIGNAL(clicked()), CustomConfig, SLOT(onCancel()));
        QObject::connect(mClickLabel, SIGNAL(clicked()), CustomConfig, SLOT(onShowMore()));
        QObject::connect(mCalculate, SIGNAL(clicked()), CustomConfig, SLOT(onCalculate()));

        QMetaObject::connectSlotsByName(CustomConfig);
    } // setupUi

    void retranslateUi(QWidget *CustomConfig)
    {
        CustomConfig->setWindowTitle(QApplication::translate("CustomConfig", "CustomConfig", 0));
        mCheckOriginal->setText(QString());
        mSave->setText(QApplication::translate("CustomConfig", "\344\277\235\345\255\230\350\256\276\347\275\256", 0));
        mCancel->setText(QApplication::translate("CustomConfig", "\345\217\226\346\266\210", 0));
        mClickLabel->setText(QApplication::translate("CustomConfig", "\346\230\276\347\244\272\346\233\264\345\244\232\345\212\237\350\203\275\357\274\232", 0));
        mIndicate->setText(QApplication::translate("CustomConfig", ">>", 0));
        mCalculate->setText(QApplication::translate("CustomConfig", "\347\253\213\345\215\263\350\256\241\347\256\227", 0));
    } // retranslateUi

};

namespace Ui {
    class CustomConfig: public Ui_CustomConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOM_H
