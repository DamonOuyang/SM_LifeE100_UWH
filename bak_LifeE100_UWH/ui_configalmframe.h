/********************************************************************************
** Form generated from reading UI file 'configalmframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGALMFRAME_H
#define UI_CONFIGALMFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configAlmFrame
{
public:
    QPushButton *aOkBut;
    QPushButton *aCancelBut;
    QWidget *almWidget;
    QPushButton *aEditBut;

    void setupUi(QFrame *configAlmFrame)
    {
        if (configAlmFrame->objectName().isEmpty())
            configAlmFrame->setObjectName(QString::fromUtf8("configAlmFrame"));
        configAlmFrame->resize(1075, 655);
        aOkBut = new QPushButton(configAlmFrame);
        aOkBut->setObjectName(QString::fromUtf8("aOkBut"));
        aOkBut->setGeometry(QRect(737, 555, 160, 60));
        aOkBut->setStyleSheet(QString::fromUtf8("#aOkBut\n"
"{\n"
"background-image: url(:/images/cfgOkBut_Bt.png);\n"
"}\n"
"#aOkBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgOkButDn_Bt.png);\n"
"}\n"
"#aOkBut:focus{outline: none;\n"
"}"));
        aOkBut->setIconSize(QSize(160, 60));
        aCancelBut = new QPushButton(configAlmFrame);
        aCancelBut->setObjectName(QString::fromUtf8("aCancelBut"));
        aCancelBut->setGeometry(QRect(915, 555, 160, 60));
        aCancelBut->setStyleSheet(QString::fromUtf8("#aCancelBut\n"
"{\n"
"background-image: url(:/images/cfgCancel_Bt.png);\n"
"}\n"
"#aCancelBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgCancelDn_Bt.png);\n"
"}\n"
"#aCancelBut:focus{outline: none;\n"
"}"));
        aCancelBut->setIconSize(QSize(160, 60));
        almWidget = new QWidget(configAlmFrame);
        almWidget->setObjectName(QString::fromUtf8("almWidget"));
        almWidget->setGeometry(QRect(0, 0, 1075, 520));
        almWidget->setStyleSheet(QString::fromUtf8("#almWidget\n"
"{\n"
"background-image: url(:/images/cfgAlm_Bg.png);\n"
"}"));
        aEditBut = new QPushButton(configAlmFrame);
        aEditBut->setObjectName(QString::fromUtf8("aEditBut"));
        aEditBut->setGeometry(QRect(555, 555, 160, 60));
        aEditBut->setStyleSheet(QString::fromUtf8("#aEditBut\n"
"{\n"
"background-image: url(:/images/cfgEditBut_Bt.png);\n"
"}\n"
"#aEditBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgEditButDn_Bt.png);\n"
"}\n"
"#aEditBut:focus{outline: none;\n"
"}"));
        aEditBut->setIconSize(QSize(160, 60));

        retranslateUi(configAlmFrame);

        QMetaObject::connectSlotsByName(configAlmFrame);
    } // setupUi

    void retranslateUi(QFrame *configAlmFrame)
    {
        configAlmFrame->setWindowTitle(QApplication::translate("configAlmFrame", "Frame", 0, QApplication::UnicodeUTF8));
        aOkBut->setText(QString());
        aCancelBut->setText(QString());
        aEditBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class configAlmFrame: public Ui_configAlmFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGALMFRAME_H
