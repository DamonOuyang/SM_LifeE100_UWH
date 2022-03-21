/********************************************************************************
** Form generated from reading UI file 'testdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTDIALOG_H
#define UI_TESTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QMessageBox>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_testDialog
{
public:
    QMessageBox *closePumInfoWidget;
    QPushButton *cancelPumButton;
    QPushButton *closePumButton;

    void setupUi(QDialog *testDialog)
    {
        if (testDialog->objectName().isEmpty())
            testDialog->setObjectName(QString::fromUtf8("testDialog"));
        testDialog->resize(1280, 760);
        testDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/images/dialogAllWindow_Bg.png);"));
        closePumInfoWidget = new QMessageBox(testDialog);
        closePumInfoWidget->setObjectName(QString::fromUtf8("closePumInfoWidget"));
        closePumInfoWidget->setGeometry(QRect(350, 240, 600, 290));
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

        retranslateUi(testDialog);

        QMetaObject::connectSlotsByName(testDialog);
    } // setupUi

    void retranslateUi(QDialog *testDialog)
    {
        testDialog->setWindowTitle(QApplication::translate("testDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cancelPumButton->setText(QString());
        closePumButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class testDialog: public Ui_testDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
