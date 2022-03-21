/********************************************************************************
** Form generated from reading UI file 'updategoingdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEGOINGDIALOG_H
#define UI_UPDATEGOINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include "QRoundProgressBar.h"

QT_BEGIN_NAMESPACE

class Ui_UpdateGoingDialog
{
public:
    QRoundProgressBar *UpdRoundBar;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *closeButton;

    void setupUi(QDialog *UpdateGoingDialog)
    {
        if (UpdateGoingDialog->objectName().isEmpty())
            UpdateGoingDialog->setObjectName(QString::fromUtf8("UpdateGoingDialog"));
        UpdateGoingDialog->resize(1280, 760);
        UpdateGoingDialog->setStyleSheet(QString::fromUtf8("#UpdateGoingDialog{\n"
"image: url(:/images/Update/UpdateGoing_Bg.png);\n"
"}"));
        UpdRoundBar = new QRoundProgressBar(UpdateGoingDialog);
        UpdRoundBar->setObjectName(QString::fromUtf8("UpdRoundBar"));
        UpdRoundBar->setGeometry(QRect(473, 213, 334, 334));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(239, 41, 41, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush);
        QBrush brush3(QColor(71, 71, 71, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush3);
        QBrush brush4(QColor(38, 38, 38, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush4);
        QBrush brush5(QColor(138, 226, 52, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush3);
        QBrush brush6(QColor(255, 170, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush6);
        QBrush brush7(QColor(115, 115, 115, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        QBrush brush9(QColor(0, 0, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush3);
        QBrush brush10(QColor(50, 100, 150, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        UpdRoundBar->setPalette(palette);
        UpdRoundBar->setStyleSheet(QString::fromUtf8("#UpdRoundBar\n"
"{\n"
"background: transparent;\n"
"\n"
"}"));
        verticalLayout = new QVBoxLayout(UpdRoundBar);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(UpdateGoingDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(473, 140, 334, 40));
        label->setStyleSheet(QString::fromUtf8("#label{\n"
"   font-family:simhei;\n"
"  color: rgb(247, 176, 0);\n"
"   font:bold;\n"
"   font:18px;\n"
"}"));
        label->setAlignment(Qt::AlignCenter);
        closeButton = new QPushButton(UpdateGoingDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(500, 660, 280, 60));
        closeButton->setStyleSheet(QString::fromUtf8("#closeButton:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Update/upClose_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeButton->setIcon(icon);
        closeButton->setIconSize(QSize(280, 60));

        retranslateUi(UpdateGoingDialog);

        QMetaObject::connectSlotsByName(UpdateGoingDialog);
    } // setupUi

    void retranslateUi(QDialog *UpdateGoingDialog)
    {
        UpdateGoingDialog->setWindowTitle(QApplication::translate("UpdateGoingDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        closeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UpdateGoingDialog: public Ui_UpdateGoingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEGOINGDIALOG_H
