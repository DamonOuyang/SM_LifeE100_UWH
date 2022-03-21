/********************************************************************************
** Form generated from reading UI file 'configbasicframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGBASICFRAME_H
#define UI_CONFIGBASICFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigBasicFrame
{
public:
    QPushButton *bModPwd;
    QPushButton *bCancelBut;
    QPushButton *bExitPwd;
    QWidget *basicWidget;
    QPushButton *bOkBut;
    QPushButton *bEditBut;

    void setupUi(QFrame *ConfigBasicFrame)
    {
        if (ConfigBasicFrame->objectName().isEmpty())
            ConfigBasicFrame->setObjectName(QString::fromUtf8("ConfigBasicFrame"));
        ConfigBasicFrame->resize(1075, 655);
        bModPwd = new QPushButton(ConfigBasicFrame);
        bModPwd->setObjectName(QString::fromUtf8("bModPwd"));
        bModPwd->setGeometry(QRect(375, 555, 160, 60));
        bModPwd->setStyleSheet(QString::fromUtf8("#bModPwd\n"
"{\n"
"background-image: url(:/images/cfgModPwd_Bt.png);\n"
"}\n"
"#bModPwd:pressed\n"
"{\n"
"background-image: url(:/images/cfgModPwdDn_Bt.png);\n"
"}\n"
"#bModPwd:focus{outline: none;\n"
"}"));
        bModPwd->setIconSize(QSize(160, 60));
        bCancelBut = new QPushButton(ConfigBasicFrame);
        bCancelBut->setObjectName(QString::fromUtf8("bCancelBut"));
        bCancelBut->setGeometry(QRect(915, 555, 160, 60));
        bCancelBut->setStyleSheet(QString::fromUtf8("#bCancelBut\n"
"{\n"
"background-image: url(:/images/cfgCancel_Bt.png);\n"
"}\n"
"#bCancelBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgCancelDn_Bt.png);\n"
"}\n"
"#bCancelBut:focus{outline: none;\n"
"}"));
        bCancelBut->setIconSize(QSize(160, 60));
        bExitPwd = new QPushButton(ConfigBasicFrame);
        bExitPwd->setObjectName(QString::fromUtf8("bExitPwd"));
        bExitPwd->setGeometry(QRect(195, 555, 160, 60));
        bExitPwd->setStyleSheet(QString::fromUtf8("#bExitPwd\n"
"{\n"
"background-image: url(:/images/cfgExitPwd_Bt.png);\n"
"}\n"
"#bExitPwd:pressed\n"
"{\n"
"background-image: url(:/images/cfgExitPwdDn_Bt.png);\n"
"}\n"
"#bExitPwd:focus{outline: none;\n"
"}"));
        bExitPwd->setIconSize(QSize(160, 60));
        bExitPwd->setCheckable(false);
        bExitPwd->setAutoExclusive(false);
        basicWidget = new QWidget(ConfigBasicFrame);
        basicWidget->setObjectName(QString::fromUtf8("basicWidget"));
        basicWidget->setGeometry(QRect(0, 0, 1075, 520));
        basicWidget->setStyleSheet(QString::fromUtf8("#basicWidget\n"
"{\n"
"background-image: url(:/images/cfgBasic_Bg.png);\n"
"}"));
        bOkBut = new QPushButton(ConfigBasicFrame);
        bOkBut->setObjectName(QString::fromUtf8("bOkBut"));
        bOkBut->setGeometry(QRect(737, 555, 160, 60));
        bOkBut->setStyleSheet(QString::fromUtf8("#bOkBut\n"
"{\n"
"background-image: url(:/images/cfgOkBut_Bt.png);\n"
"}\n"
"#bOkBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgOkButDn_Bt.png);\n"
"}\n"
"#bOkBut:focus{outline: none;\n"
"}"));
        bOkBut->setIconSize(QSize(160, 60));
        bEditBut = new QPushButton(ConfigBasicFrame);
        bEditBut->setObjectName(QString::fromUtf8("bEditBut"));
        bEditBut->setGeometry(QRect(555, 555, 160, 60));
        bEditBut->setStyleSheet(QString::fromUtf8("#bEditBut\n"
"{\n"
"background-image: url(:/images/cfgEditBut_Bt.png);\n"
"}\n"
"#bEditBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgEditButDn_Bt.png);\n"
"}\n"
"#bEditBut:focus{outline: none;\n"
"}"));
        bEditBut->setIconSize(QSize(160, 60));

        retranslateUi(ConfigBasicFrame);

        QMetaObject::connectSlotsByName(ConfigBasicFrame);
    } // setupUi

    void retranslateUi(QFrame *ConfigBasicFrame)
    {
        ConfigBasicFrame->setWindowTitle(QApplication::translate("ConfigBasicFrame", "Frame", 0, QApplication::UnicodeUTF8));
        bModPwd->setText(QString());
        bCancelBut->setText(QString());
        bExitPwd->setText(QString());
        bOkBut->setText(QString());
        bEditBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ConfigBasicFrame: public Ui_ConfigBasicFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGBASICFRAME_H
