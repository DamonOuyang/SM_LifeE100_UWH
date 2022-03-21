/********************************************************************************
** Form generated from reading UI file 'configveiframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGVEIFRAME_H
#define UI_CONFIGVEIFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configVeiFrame
{
public:
    QPushButton *veiCancelBut;
    QWidget *veiWidget;
    QPushButton *veiEditBut;
    QPushButton *veiOkBut;

    void setupUi(QFrame *configVeiFrame)
    {
        if (configVeiFrame->objectName().isEmpty())
            configVeiFrame->setObjectName(QString::fromUtf8("configVeiFrame"));
        configVeiFrame->resize(1075, 655);
        veiCancelBut = new QPushButton(configVeiFrame);
        veiCancelBut->setObjectName(QString::fromUtf8("veiCancelBut"));
        veiCancelBut->setGeometry(QRect(915, 555, 160, 60));
        veiCancelBut->setStyleSheet(QString::fromUtf8("#veiCancelBut\n"
"{\n"
"background-image: url(:/images/cfgCancel_Bt.png);\n"
"}\n"
"#veiCancelBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgCancelDn_Bt.png);\n"
"}\n"
"#veiCancelBut:focus{outline: none;\n"
"}"));
        veiCancelBut->setIconSize(QSize(160, 60));
        veiWidget = new QWidget(configVeiFrame);
        veiWidget->setObjectName(QString::fromUtf8("veiWidget"));
        veiWidget->setGeometry(QRect(0, 0, 1075, 520));
        veiWidget->setStyleSheet(QString::fromUtf8("#veiWidget\n"
"{\n"
"background-image: url(:/images/cfgPum_Bg.png);\n"
"}"));
        veiEditBut = new QPushButton(configVeiFrame);
        veiEditBut->setObjectName(QString::fromUtf8("veiEditBut"));
        veiEditBut->setGeometry(QRect(555, 555, 160, 60));
        veiEditBut->setStyleSheet(QString::fromUtf8("#veiEditBut\n"
"{\n"
"background-image: url(:/images/cfgEditBut_Bt.png);\n"
"}\n"
"#veiEditBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgEditButDn_Bt.png);\n"
"}\n"
"#veiEditBut:focus{outline: none;\n"
"}"));
        veiEditBut->setIconSize(QSize(160, 60));
        veiOkBut = new QPushButton(configVeiFrame);
        veiOkBut->setObjectName(QString::fromUtf8("veiOkBut"));
        veiOkBut->setGeometry(QRect(737, 555, 160, 60));
        veiOkBut->setStyleSheet(QString::fromUtf8("#veiOkBut\n"
"{\n"
"background-image: url(:/images/cfgOkBut_Bt.png);\n"
"}\n"
"#veiOkBut:pressed\n"
"{\n"
"background-image: url(:/images/cfgOkButDn_Bt.png);\n"
"}\n"
"#veiOkBut:focus{outline: none;\n"
"}"));
        veiOkBut->setIconSize(QSize(160, 60));

        retranslateUi(configVeiFrame);

        QMetaObject::connectSlotsByName(configVeiFrame);
    } // setupUi

    void retranslateUi(QFrame *configVeiFrame)
    {
        configVeiFrame->setWindowTitle(QApplication::translate("configVeiFrame", "Frame", 0, QApplication::UnicodeUTF8));
        veiCancelBut->setText(QString());
        veiEditBut->setText(QString());
        veiOkBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class configVeiFrame: public Ui_configVeiFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGVEIFRAME_H
