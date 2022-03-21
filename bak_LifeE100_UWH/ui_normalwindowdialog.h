/********************************************************************************
** Form generated from reading UI file 'normalwindowdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMALWINDOWDIALOG_H
#define UI_NORMALWINDOWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NormalWindowDialog
{
public:
    QWidget *lockInfoWidget;
    QPushButton *lockBoxBackBt;

    void setupUi(QDialog *NormalWindowDialog)
    {
        if (NormalWindowDialog->objectName().isEmpty())
            NormalWindowDialog->setObjectName(QString::fromUtf8("NormalWindowDialog"));
        NormalWindowDialog->resize(1280, 760);
        NormalWindowDialog->setStyleSheet(QString::fromUtf8("#NormalWindowDialog{\n"
"background: transparent;\n"
"background-image: url(:/images/dialogAllWindow_Bg.png);\n"
"}"));
        lockInfoWidget = new QWidget(NormalWindowDialog);
        lockInfoWidget->setObjectName(QString::fromUtf8("lockInfoWidget"));
        lockInfoWidget->setGeometry(QRect(340, 235, 600, 290));
        lockInfoWidget->setStyleSheet(QString::fromUtf8("#lockInfoWidget{\n"
"background-image: url(:/images/lockInfoBox.png);\n"
"}"));
        lockBoxBackBt = new QPushButton(lockInfoWidget);
        lockBoxBackBt->setObjectName(QString::fromUtf8("lockBoxBackBt"));
        lockBoxBackBt->setGeometry(QRect(0, 210, 600, 80));
        lockBoxBackBt->setStyleSheet(QString::fromUtf8("#lockBoxBackBt:focus{\n"
"outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/lockInfoBack.png"), QSize(), QIcon::Normal, QIcon::Off);
        lockBoxBackBt->setIcon(icon);
        lockBoxBackBt->setIconSize(QSize(600, 80));

        retranslateUi(NormalWindowDialog);

        QMetaObject::connectSlotsByName(NormalWindowDialog);
    } // setupUi

    void retranslateUi(QDialog *NormalWindowDialog)
    {
        NormalWindowDialog->setWindowTitle(QApplication::translate("NormalWindowDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        lockBoxBackBt->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NormalWindowDialog: public Ui_NormalWindowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMALWINDOWDIALOG_H
