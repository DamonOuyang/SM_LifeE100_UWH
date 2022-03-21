/********************************************************************************
** Form generated from reading UI file 'configbatframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGBATFRAME_H
#define UI_CONFIGBATFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configBatFrame
{
public:
    QWidget *batWidget;
    QPushButton *batEditBut;
    QPushButton *batOkBut;
    QPushButton *batCancelBut;

    void setupUi(QFrame *configBatFrame)
    {
        if (configBatFrame->objectName().isEmpty())
            configBatFrame->setObjectName(QString::fromUtf8("configBatFrame"));
        configBatFrame->resize(1075, 655);
        batWidget = new QWidget(configBatFrame);
        batWidget->setObjectName(QString::fromUtf8("batWidget"));
        batWidget->setGeometry(QRect(0, 0, 1075, 520));
        batWidget->setStyleSheet(QString::fromUtf8("#batWidget\n"
"{\n"
"background-image: url(:/images/cfgBat_Bg.png);\n"
"}"));
        batEditBut = new QPushButton(configBatFrame);
        batEditBut->setObjectName(QString::fromUtf8("batEditBut"));
        batEditBut->setGeometry(QRect(555, 555, 160, 60));
        batEditBut->setStyleSheet(QString::fromUtf8("#batEditBut\n"
"{\n"
"background-image: url(:/images/cfgEditBut_Bt.png);\n"
"}\n"
"#batEditBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgEditButDn_Bt.png);\n"
"}\n"
"#batEditBut:focus{outline: none;\n"
"}"));
        batEditBut->setIconSize(QSize(160, 60));
        batOkBut = new QPushButton(configBatFrame);
        batOkBut->setObjectName(QString::fromUtf8("batOkBut"));
        batOkBut->setGeometry(QRect(737, 555, 160, 60));
        batOkBut->setStyleSheet(QString::fromUtf8("#batOkBut\n"
"{\n"
"background-image: url(:/images/cfgOkBut_Bt.png);\n"
"}\n"
"#batOkBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgOkButDn_Bt.png);\n"
"}\n"
"#batOkBut:focus{outline: none;\n"
"}"));
        batOkBut->setIconSize(QSize(160, 60));
        batCancelBut = new QPushButton(configBatFrame);
        batCancelBut->setObjectName(QString::fromUtf8("batCancelBut"));
        batCancelBut->setGeometry(QRect(915, 555, 160, 60));
        batCancelBut->setStyleSheet(QString::fromUtf8("#batCancelBut\n"
"{\n"
"background-image: url(:/images/cfgCancel_Bt.png);\n"
"}\n"
"#batCancelBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgCancelDn_Bt.png);\n"
"}\n"
"#batCancelBut:focus{outline: none;\n"
"}"));
        batCancelBut->setIconSize(QSize(160, 60));

        retranslateUi(configBatFrame);

        QMetaObject::connectSlotsByName(configBatFrame);
    } // setupUi

    void retranslateUi(QFrame *configBatFrame)
    {
        configBatFrame->setWindowTitle(QApplication::translate("configBatFrame", "Frame", 0, QApplication::UnicodeUTF8));
        batEditBut->setText(QString());
        batOkBut->setText(QString());
        batCancelBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class configBatFrame: public Ui_configBatFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGBATFRAME_H
