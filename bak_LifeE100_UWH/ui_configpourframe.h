/********************************************************************************
** Form generated from reading UI file 'configpourframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGPOURFRAME_H
#define UI_CONFIGPOURFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configPourFrame
{
public:
    QPushButton *pEditBut;
    QPushButton *pCancelBut;
    QPushButton *pOkBut;
    QWidget *pourWidget;

    void setupUi(QFrame *configPourFrame)
    {
        if (configPourFrame->objectName().isEmpty())
            configPourFrame->setObjectName(QString::fromUtf8("configPourFrame"));
        configPourFrame->resize(1075, 655);
        pEditBut = new QPushButton(configPourFrame);
        pEditBut->setObjectName(QString::fromUtf8("pEditBut"));
        pEditBut->setGeometry(QRect(555, 555, 160, 60));
        pEditBut->setStyleSheet(QString::fromUtf8("#pEditBut\n"
"{\n"
"background-image: url(:/images/cfgEditBut_Bt.png);\n"
"}\n"
"#pEditBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgEditButDn_Bt.png);\n"
"}\n"
"#pEditBut:focus{outline: none;\n"
"}"));
        pEditBut->setIconSize(QSize(160, 60));
        pCancelBut = new QPushButton(configPourFrame);
        pCancelBut->setObjectName(QString::fromUtf8("pCancelBut"));
        pCancelBut->setGeometry(QRect(915, 555, 160, 60));
        pCancelBut->setStyleSheet(QString::fromUtf8("#pCancelBut\n"
"{\n"
"background-image: url(:/images/cfgCancel_Bt.png);\n"
"}\n"
"#pCancelBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgCancelDn_Bt.png);\n"
"}\n"
"#pCancelBut:focus{outline: none;\n"
"}"));
        pCancelBut->setIconSize(QSize(160, 60));
        pOkBut = new QPushButton(configPourFrame);
        pOkBut->setObjectName(QString::fromUtf8("pOkBut"));
        pOkBut->setGeometry(QRect(737, 555, 160, 60));
        pOkBut->setStyleSheet(QString::fromUtf8("#pOkBut\n"
"{\n"
"background-image: url(:/images/cfgOkBut_Bt.png);\n"
"}\n"
"#pOkBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgOkButDn_Bt.png);\n"
"}\n"
"#pOkBut:focus{outline: none;\n"
"}"));
        pOkBut->setIconSize(QSize(160, 60));
        pourWidget = new QWidget(configPourFrame);
        pourWidget->setObjectName(QString::fromUtf8("pourWidget"));
        pourWidget->setGeometry(QRect(0, 0, 1075, 520));
        pourWidget->setStyleSheet(QString::fromUtf8("#pourWidget\n"
"{\n"
"background-image: url(:/images/cfgPour_Bg.png);\n"
"}"));

        retranslateUi(configPourFrame);

        QMetaObject::connectSlotsByName(configPourFrame);
    } // setupUi

    void retranslateUi(QFrame *configPourFrame)
    {
        configPourFrame->setWindowTitle(QApplication::translate("configPourFrame", "Frame", 0, QApplication::UnicodeUTF8));
        pEditBut->setText(QString());
        pCancelBut->setText(QString());
        pOkBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class configPourFrame: public Ui_configPourFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGPOURFRAME_H
