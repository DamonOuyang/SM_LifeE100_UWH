/********************************************************************************
** Form generated from reading UI file 'lockscreendialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKSCREENDIALOG_H
#define UI_LOCKSCREENDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LockScreenDialog
{
public:
    QPushButton *LockScreenBtn;
    QPushButton *boxButton;
    QPushButton *boxButton2;

    void setupUi(QDialog *LockScreenDialog)
    {
        if (LockScreenDialog->objectName().isEmpty())
            LockScreenDialog->setObjectName(QString::fromUtf8("LockScreenDialog"));
        LockScreenDialog->resize(1280, 760);
        LockScreenDialog->setStyleSheet(QString::fromUtf8("#LockScreenDialog\n"
"{\n"
"background: transparent;\n"
"}"));
        LockScreenBtn = new QPushButton(LockScreenDialog);
        LockScreenBtn->setObjectName(QString::fromUtf8("LockScreenBtn"));
        LockScreenBtn->setGeometry(QRect(40, 660, 86, 60));
        LockScreenBtn->setStyleSheet(QString::fromUtf8("#LockScreenBtn{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#LockScreenBtn:focus{outline: none;\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/locked_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockScreenBtn->setIcon(icon);
        LockScreenBtn->setIconSize(QSize(86, 60));
        boxButton = new QPushButton(LockScreenDialog);
        boxButton->setObjectName(QString::fromUtf8("boxButton"));
        boxButton->setGeometry(QRect(0, 0, 1280, 660));
        boxButton->setStyleSheet(QString::fromUtf8("#boxButton{\n"
"background: transparent;\n"
"padding:-1px;\n"
"}\n"
"#boxButton:focus{outline: none;\n"
"}"));
        boxButton2 = new QPushButton(LockScreenDialog);
        boxButton2->setObjectName(QString::fromUtf8("boxButton2"));
        boxButton2->setGeometry(QRect(127, 660, 1161, 100));
        boxButton2->setStyleSheet(QString::fromUtf8("#boxButton2{\n"
"background: transparent;\n"
"padding:-1px;\n"
"}\n"
"#boxButton2:focus{outline: none;\n"
"}"));

        retranslateUi(LockScreenDialog);

        QMetaObject::connectSlotsByName(LockScreenDialog);
    } // setupUi

    void retranslateUi(QDialog *LockScreenDialog)
    {
        LockScreenDialog->setWindowTitle(QApplication::translate("LockScreenDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        LockScreenBtn->setText(QString());
        boxButton->setText(QString());
        boxButton2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockScreenDialog: public Ui_LockScreenDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKSCREENDIALOG_H
