/********************************************************************************
** Form generated from reading UI file 'closepumwindialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOSEPUMWINDIALOG_H
#define UI_CLOSEPUMWINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClosePumWinDialog
{
public:
    QWidget *closePumInfoWidget;
    QPushButton *cancelPumButton;
    QPushButton *closePumButton;

    void setupUi(QDialog *ClosePumWinDialog)
    {
        if (ClosePumWinDialog->objectName().isEmpty())
            ClosePumWinDialog->setObjectName(QString::fromUtf8("ClosePumWinDialog"));
        ClosePumWinDialog->resize(1280, 760);
        ClosePumWinDialog->setStyleSheet(QString::fromUtf8("#ClosePumWinDialog\n"
"{\n"
"background: transparent;\n"
"background-image: url(:/images/dialogAllWindow_Bg.png);\n"
"}"));
        closePumInfoWidget = new QWidget(ClosePumWinDialog);
        closePumInfoWidget->setObjectName(QString::fromUtf8("closePumInfoWidget"));
        closePumInfoWidget->setGeometry(QRect(340, 239, 600, 290));
        closePumInfoWidget->setStyleSheet(QString::fromUtf8("#closePumInfoWidget{\n"
"background-image: url(:/images/closePumWinBg.png);\n"
"}"));
        cancelPumButton = new QPushButton(closePumInfoWidget);
        cancelPumButton->setObjectName(QString::fromUtf8("cancelPumButton"));
        cancelPumButton->setGeometry(QRect(0, 210, 300, 80));
        cancelPumButton->setStyleSheet(QString::fromUtf8("#cancelPumButton:focus{\n"
"outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/close_cal_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelPumButton->setIcon(icon);
        cancelPumButton->setIconSize(QSize(300, 80));
        closePumButton = new QPushButton(closePumInfoWidget);
        closePumButton->setObjectName(QString::fromUtf8("closePumButton"));
        closePumButton->setGeometry(QRect(300, 210, 300, 80));
        closePumButton->setStyleSheet(QString::fromUtf8("#closePumButton:focus{\n"
"outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/closePum_Bt_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        closePumButton->setIcon(icon1);
        closePumButton->setIconSize(QSize(300, 80));

        retranslateUi(ClosePumWinDialog);

        QMetaObject::connectSlotsByName(ClosePumWinDialog);
    } // setupUi

    void retranslateUi(QDialog *ClosePumWinDialog)
    {
        ClosePumWinDialog->setWindowTitle(QApplication::translate("ClosePumWinDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cancelPumButton->setText(QString());
        closePumButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ClosePumWinDialog: public Ui_ClosePumWinDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOSEPUMWINDIALOG_H
