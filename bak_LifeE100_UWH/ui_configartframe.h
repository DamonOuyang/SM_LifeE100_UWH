/********************************************************************************
** Form generated from reading UI file 'configartframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGARTFRAME_H
#define UI_CONFIGARTFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configArtFrame
{
public:
    QWidget *artWidget;
    QPushButton *artCancelBut;
    QPushButton *artOkBut;
    QPushButton *artEditBut;

    void setupUi(QFrame *configArtFrame)
    {
        if (configArtFrame->objectName().isEmpty())
            configArtFrame->setObjectName(QString::fromUtf8("configArtFrame"));
        configArtFrame->resize(1075, 655);
        artWidget = new QWidget(configArtFrame);
        artWidget->setObjectName(QString::fromUtf8("artWidget"));
        artWidget->setGeometry(QRect(0, 0, 1075, 520));
        artWidget->setStyleSheet(QString::fromUtf8("#artWidget\n"
"{\n"
"background-image: url(:/images/cfgPum_Bg.png);\n"
"}"));
        artCancelBut = new QPushButton(configArtFrame);
        artCancelBut->setObjectName(QString::fromUtf8("artCancelBut"));
        artCancelBut->setGeometry(QRect(915, 555, 160, 60));
        artCancelBut->setStyleSheet(QString::fromUtf8("#artCancelBut\n"
"{\n"
"background-image: url(:/images/cfgCancel_Bt.png);\n"
"}\n"
"#artCancelBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgCancelDn_Bt.png);\n"
"}\n"
"#artCancelBut:focus{outline: none;\n"
"}"));
        artCancelBut->setIconSize(QSize(160, 60));
        artOkBut = new QPushButton(configArtFrame);
        artOkBut->setObjectName(QString::fromUtf8("artOkBut"));
        artOkBut->setGeometry(QRect(737, 555, 160, 60));
        artOkBut->setStyleSheet(QString::fromUtf8("#artOkBut\n"
"{\n"
"background-image: url(:/images/cfgOkBut_Bt.png);\n"
"}\n"
"#artOkBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgOkButDn_Bt.png);\n"
"}\n"
"#artOkBut:focus{outline: none;\n"
"}"));
        artOkBut->setIconSize(QSize(160, 60));
        artEditBut = new QPushButton(configArtFrame);
        artEditBut->setObjectName(QString::fromUtf8("artEditBut"));
        artEditBut->setGeometry(QRect(555, 555, 160, 60));
        artEditBut->setStyleSheet(QString::fromUtf8("#artEditBut\n"
"{\n"
"background-image: url(:/images/cfgEditBut_Bt.png);\n"
"}\n"
"#artEditBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgEditButDn_Bt.png);\n"
"}\n"
"#artEditBut:focus{outline: none;\n"
"}"));
        artEditBut->setIconSize(QSize(160, 60));

        retranslateUi(configArtFrame);

        QMetaObject::connectSlotsByName(configArtFrame);
    } // setupUi

    void retranslateUi(QFrame *configArtFrame)
    {
        configArtFrame->setWindowTitle(QApplication::translate("configArtFrame", "Frame", 0, QApplication::UnicodeUTF8));
        artCancelBut->setText(QString());
        artOkBut->setText(QString());
        artEditBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class configArtFrame: public Ui_configArtFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGARTFRAME_H
