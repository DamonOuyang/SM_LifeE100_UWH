/********************************************************************************
** Form generated from reading UI file 'messageboxdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOXDIALOG_H
#define UI_MESSAGEBOXDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MessageBoxDialog
{
public:
    QLabel *label;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QPushButton *okButton1;

    void setupUi(QDialog *MessageBoxDialog)
    {
        if (MessageBoxDialog->objectName().isEmpty())
            MessageBoxDialog->setObjectName(QString::fromUtf8("MessageBoxDialog"));
        MessageBoxDialog->resize(1280, 760);
        MessageBoxDialog->setStyleSheet(QString::fromUtf8("#MessageBoxDialog\n"
"{\n"
"background-image: url(:/images/MessgBox/messgBox_Bg.png);\n"
"}"));
        label = new QLabel(MessageBoxDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(340, 320, 600, 40));
        label->setStyleSheet(QString::fromUtf8("#label\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:24px;\n"
"}"));
        label->setAlignment(Qt::AlignCenter);
        cancelButton = new QPushButton(MessageBoxDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(340, 445, 300, 80));
        cancelButton->setStyleSheet(QString::fromUtf8("#cancelButton:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/MessgBox/messgCancel_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon);
        cancelButton->setIconSize(QSize(300, 80));
        okButton = new QPushButton(MessageBoxDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(640, 445, 300, 80));
        okButton->setStyleSheet(QString::fromUtf8("#okButton:focus{outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/MessgBox/messgOk_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon1);
        okButton->setIconSize(QSize(300, 80));
        okButton1 = new QPushButton(MessageBoxDialog);
        okButton1->setObjectName(QString::fromUtf8("okButton1"));
        okButton1->setGeometry(QRect(340, 445, 600, 80));
        okButton1->setStyleSheet(QString::fromUtf8("#okButton1:focus{outline: none;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/MessgBox/messgBack_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        okButton1->setIcon(icon2);
        okButton1->setIconSize(QSize(600, 80));

        retranslateUi(MessageBoxDialog);

        QMetaObject::connectSlotsByName(MessageBoxDialog);
    } // setupUi

    void retranslateUi(QDialog *MessageBoxDialog)
    {
        MessageBoxDialog->setWindowTitle(QApplication::translate("MessageBoxDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        cancelButton->setText(QString());
        okButton->setText(QString());
        okButton1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MessageBoxDialog: public Ui_MessageBoxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOXDIALOG_H
