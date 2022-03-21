/********************************************************************************
** Form generated from reading UI file 'unlockinfodialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNLOCKINFODIALOG_H
#define UI_UNLOCKINFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_unlockInfoDialog
{
public:
    QWidget *unlockInfoWidget;
    QPushButton *cancelButton;
    QPushButton *unlockButton;

    void setupUi(QDialog *unlockInfoDialog)
    {
        if (unlockInfoDialog->objectName().isEmpty())
            unlockInfoDialog->setObjectName(QString::fromUtf8("unlockInfoDialog"));
        unlockInfoDialog->resize(1280, 760);
        unlockInfoDialog->setStyleSheet(QString::fromUtf8("#unlockInfoDialog{\n"
"background: transparent;\n"
"background-image: url(:/images/dialogAllWindow_Bg.png);\n"
"}"));
        unlockInfoWidget = new QWidget(unlockInfoDialog);
        unlockInfoWidget->setObjectName(QString::fromUtf8("unlockInfoWidget"));
        unlockInfoWidget->setGeometry(QRect(340, 239, 600, 290));
        unlockInfoWidget->setStyleSheet(QString::fromUtf8("#unlockInfoWidget{\n"
"background-image: url(:/images/unLockInfoBox.png);\n"
"}"));
        cancelButton = new QPushButton(unlockInfoWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(0, 210, 300, 80));
        cancelButton->setStyleSheet(QString::fromUtf8("#cancelButton:focus{\n"
"outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/unLockInfoBtDis.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon);
        cancelButton->setIconSize(QSize(300, 80));
        unlockButton = new QPushButton(unlockInfoWidget);
        unlockButton->setObjectName(QString::fromUtf8("unlockButton"));
        unlockButton->setGeometry(QRect(300, 210, 300, 80));
        unlockButton->setStyleSheet(QString::fromUtf8("#unlockButton:focus{\n"
"outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/unLockInfoBtEn.png"), QSize(), QIcon::Normal, QIcon::Off);
        unlockButton->setIcon(icon1);
        unlockButton->setIconSize(QSize(300, 80));

        retranslateUi(unlockInfoDialog);

        QMetaObject::connectSlotsByName(unlockInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *unlockInfoDialog)
    {
        unlockInfoDialog->setWindowTitle(QApplication::translate("unlockInfoDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QString());
        unlockButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class unlockInfoDialog: public Ui_unlockInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNLOCKINFODIALOG_H
