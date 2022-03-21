/********************************************************************************
** Form generated from reading UI file 'lockscreendialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKSCREENDIALOG_H
#define UI_LOCKSCREENDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

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
            LockScreenDialog->setObjectName(QStringLiteral("LockScreenDialog"));
        LockScreenDialog->resize(1280, 740);
        LockScreenBtn = new QPushButton(LockScreenDialog);
        LockScreenBtn->setObjectName(QStringLiteral("LockScreenBtn"));
        LockScreenBtn->setGeometry(QRect(40, 640, 140, 60));
        LockScreenBtn->setStyleSheet(QLatin1String("#LockScreenBtn{\n"
"background: transparent;\n"
"	background-image: url(:/images/locked_Icon.png);\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#LockScreenBtn:pressed{\n"
"background-image: url(:/images/locked_Icon.png);\n"
"}"));
        boxButton = new QPushButton(LockScreenDialog);
        boxButton->setObjectName(QStringLiteral("boxButton"));
        boxButton->setGeometry(QRect(0, 0, 1280, 641));
        boxButton->setStyleSheet(QLatin1String("#boxButton{\n"
"background: transparent;\n"
"padding:-1px;\n"
"}\n"
"#wtrTmpSetBt:focus{outline: none;\n"
"}"));
        boxButton2 = new QPushButton(LockScreenDialog);
        boxButton2->setObjectName(QStringLiteral("boxButton2"));
        boxButton2->setGeometry(QRect(180, 640, 1101, 111));
        boxButton2->setStyleSheet(QLatin1String("#boxButton2{\n"
"background: transparent;\n"
"padding:-1px;\n"
"}\n"
"#wtrTmpSetBt:focus{outline: none;\n"
"}"));

        retranslateUi(LockScreenDialog);

        QMetaObject::connectSlotsByName(LockScreenDialog);
    } // setupUi

    void retranslateUi(QDialog *LockScreenDialog)
    {
        LockScreenDialog->setWindowTitle(QApplication::translate("LockScreenDialog", "Dialog", 0));
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
