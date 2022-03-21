/********************************************************************************
** Form generated from reading UI file 'passworddialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDDIALOG_H
#define UI_PASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasswordDialog
{
public:
    QWidget *pwdWidget;
    QPushButton *pwdCancel;
    QPushButton *pwdOk;
    QPushButton *pwdEdit;

    void setupUi(QDialog *PasswordDialog)
    {
        if (PasswordDialog->objectName().isEmpty())
            PasswordDialog->setObjectName(QString::fromUtf8("PasswordDialog"));
        PasswordDialog->resize(1280, 760);
        PasswordDialog->setStyleSheet(QString::fromUtf8("#PasswordDialog\n"
"{\n"
"background-image: url(:/images/Password/pwdWin_Bg.png);\n"
"}"));
        pwdWidget = new QWidget(PasswordDialog);
        pwdWidget->setObjectName(QString::fromUtf8("pwdWidget"));
        pwdWidget->setGeometry(QRect(340, 195, 600, 370));
        pwdCancel = new QPushButton(pwdWidget);
        pwdCancel->setObjectName(QString::fromUtf8("pwdCancel"));
        pwdCancel->setGeometry(QRect(0, 290, 300, 80));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Password/pwdCancel_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        pwdCancel->setIcon(icon);
        pwdCancel->setIconSize(QSize(300, 80));
        pwdOk = new QPushButton(pwdWidget);
        pwdOk->setObjectName(QString::fromUtf8("pwdOk"));
        pwdOk->setGeometry(QRect(300, 290, 300, 80));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Password/pwdOk_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        pwdOk->setIcon(icon1);
        pwdOk->setIconSize(QSize(300, 80));
        pwdEdit = new QPushButton(pwdWidget);
        pwdEdit->setObjectName(QString::fromUtf8("pwdEdit"));
        pwdEdit->setGeometry(QRect(390, 57, 160, 60));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Password/pwdEedit_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        pwdEdit->setIcon(icon2);
        pwdEdit->setIconSize(QSize(160, 60));

        retranslateUi(PasswordDialog);

        QMetaObject::connectSlotsByName(PasswordDialog);
    } // setupUi

    void retranslateUi(QDialog *PasswordDialog)
    {
        PasswordDialog->setWindowTitle(QApplication::translate("PasswordDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pwdCancel->setText(QString());
        pwdOk->setText(QString());
        pwdEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PasswordDialog: public Ui_PasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDDIALOG_H
