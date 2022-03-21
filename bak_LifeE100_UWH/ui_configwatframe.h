/********************************************************************************
** Form generated from reading UI file 'configwatframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWATFRAME_H
#define UI_CONFIGWATFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configWatFrame
{
public:
    QWidget *watWidget;
    QPushButton *wOkBut;
    QPushButton *wEditBut;
    QPushButton *wCancelBut;

    void setupUi(QFrame *configWatFrame)
    {
        if (configWatFrame->objectName().isEmpty())
            configWatFrame->setObjectName(QString::fromUtf8("configWatFrame"));
        configWatFrame->resize(1075, 655);
        watWidget = new QWidget(configWatFrame);
        watWidget->setObjectName(QString::fromUtf8("watWidget"));
        watWidget->setGeometry(QRect(0, 0, 1075, 520));
        watWidget->setStyleSheet(QString::fromUtf8("#watWidget\n"
"{\n"
"background-image: url(:/images/cfgWat_Bg.png);\n"
"}"));
        wOkBut = new QPushButton(configWatFrame);
        wOkBut->setObjectName(QString::fromUtf8("wOkBut"));
        wOkBut->setGeometry(QRect(737, 555, 160, 60));
        wOkBut->setStyleSheet(QString::fromUtf8("#wOkBut\n"
"{\n"
"background-image: url(:/images/cfgOkBut_Bt.png);\n"
"}\n"
"#wOkBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgOkButDn_Bt.png);\n"
"}\n"
"#wOkBut:focus{outline: none;\n"
"}"));
        wOkBut->setIconSize(QSize(160, 60));
        wEditBut = new QPushButton(configWatFrame);
        wEditBut->setObjectName(QString::fromUtf8("wEditBut"));
        wEditBut->setGeometry(QRect(555, 555, 160, 60));
        wEditBut->setStyleSheet(QString::fromUtf8("#wEditBut\n"
"{\n"
"background-image: url(:/images/cfgEditBut_Bt.png);\n"
"}\n"
"#wEditBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgEditButDn_Bt.png);\n"
"}\n"
"#wEditBut:focus{outline: none;\n"
"}"));
        wEditBut->setIconSize(QSize(160, 60));
        wCancelBut = new QPushButton(configWatFrame);
        wCancelBut->setObjectName(QString::fromUtf8("wCancelBut"));
        wCancelBut->setGeometry(QRect(915, 555, 160, 60));
        wCancelBut->setStyleSheet(QString::fromUtf8("#wCancelBut\n"
"{\n"
"background-image: url(:/images/cfgCancel_Bt.png);\n"
"}\n"
"#wCancelBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgCancelDn_Bt.png);\n"
"}\n"
"#wCancelBut:focus{outline: none;\n"
"}"));
        wCancelBut->setIconSize(QSize(160, 60));

        retranslateUi(configWatFrame);

        QMetaObject::connectSlotsByName(configWatFrame);
    } // setupUi

    void retranslateUi(QFrame *configWatFrame)
    {
        configWatFrame->setWindowTitle(QApplication::translate("configWatFrame", "Frame", 0, QApplication::UnicodeUTF8));
        wOkBut->setText(QString());
        wEditBut->setText(QString());
        wCancelBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class configWatFrame: public Ui_configWatFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWATFRAME_H
