/********************************************************************************
** Form generated from reading UI file 'setvaldialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETVALDIALOG_H
#define UI_SETVALDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetValDialog
{
public:
    QWidget *setValWidget;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QPushButton *reduceButton;
    QPushButton *addButton;
    QLineEdit *lineEdit;
    QLabel *titleLabel;

    void setupUi(QDialog *SetValDialog)
    {
        if (SetValDialog->objectName().isEmpty())
            SetValDialog->setObjectName(QString::fromUtf8("SetValDialog"));
        SetValDialog->resize(1280, 760);
        SetValDialog->setStyleSheet(QString::fromUtf8("#SetValDialog{\n"
"background-image: url(:/images/setValWindowBg.png);\n"
"}"));
        setValWidget = new QWidget(SetValDialog);
        setValWidget->setObjectName(QString::fromUtf8("setValWidget"));
        setValWidget->setGeometry(QRect(340, 195, 600, 370));
        setValWidget->setStyleSheet(QString::fromUtf8("#setValWidget\n"
"{\n"
"background-image: url(:/images/setValBg.png);\n"
"}"));
        cancelButton = new QPushButton(setValWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(0, 290, 300, 80));
        cancelButton->setStyleSheet(QString::fromUtf8("#cancelButton\n"
"{\n"
"background: transparent;\n"
"background-image: url(:/images/setVal_cal_Icon.png);\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#cancelButton:focus{\n"
"outline: none;\n"
"}"));
        okButton = new QPushButton(setValWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(300, 290, 300, 80));
        okButton->setStyleSheet(QString::fromUtf8("#okButton\n"
"{\n"
"background: transparent;\n"
"background-image: url(:/images/setVal_ok_Icon.png);\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#okButton:focus{\n"
"outline: none;\n"
"}"));
        reduceButton = new QPushButton(setValWidget);
        reduceButton->setObjectName(QString::fromUtf8("reduceButton"));
        reduceButton->setGeometry(QRect(120, 154, 60, 60));
        reduceButton->setStyleSheet(QString::fromUtf8("#reduceButton\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"}\n"
"\n"
"#reduceButton:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/setVal_redu_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        reduceButton->setIcon(icon);
        reduceButton->setIconSize(QSize(60, 60));
        addButton = new QPushButton(setValWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(420, 154, 60, 60));
        addButton->setStyleSheet(QString::fromUtf8("#addButton\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"}\n"
"#addButton:focus{\n"
"outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/setVal_add_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon1);
        addButton->setIconSize(QSize(60, 60));
        lineEdit = new QLineEdit(setValWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 155, 200, 60));
        lineEdit->setLayoutDirection(Qt::LeftToRight);
        lineEdit->setStyleSheet(QString::fromUtf8("#lineEdit{\n"
"background: transparent;\n"
"color: rgb(255, 202, 234);\n"
"font:bold;\n"
"font:60px;\n"
"}\n"
"#lineEdit{\n"
"border-width:0;border-style:outset\n"
"}"));
        lineEdit->setAlignment(Qt::AlignCenter);
        titleLabel = new QLabel(setValWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 0, 600, 80));
        titleLabel->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(SetValDialog);

        QMetaObject::connectSlotsByName(SetValDialog);
    } // setupUi

    void retranslateUi(QDialog *SetValDialog)
    {
        SetValDialog->setWindowTitle(QApplication::translate("SetValDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QString());
        okButton->setText(QString());
        reduceButton->setText(QString());
        addButton->setText(QString());
        lineEdit->setText(QString());
        titleLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SetValDialog: public Ui_SetValDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETVALDIALOG_H
