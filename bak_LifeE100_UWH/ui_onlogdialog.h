/********************************************************************************
** Form generated from reading UI file 'onlogdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLOGDIALOG_H
#define UI_ONLOGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnLogDialog
{
public:
    QWidget *onLogWidget;
    QLabel *MovLabel;

    void setupUi(QDialog *OnLogDialog)
    {
        if (OnLogDialog->objectName().isEmpty())
            OnLogDialog->setObjectName(QString::fromUtf8("OnLogDialog"));
        OnLogDialog->resize(1280, 800);
        onLogWidget = new QWidget(OnLogDialog);
        onLogWidget->setObjectName(QString::fromUtf8("onLogWidget"));
        onLogWidget->setGeometry(QRect(0, 0, 1280, 800));
        MovLabel = new QLabel(onLogWidget);
        MovLabel->setObjectName(QString::fromUtf8("MovLabel"));
        MovLabel->setGeometry(QRect(0, 0, 1280, 800));

        retranslateUi(OnLogDialog);

        QMetaObject::connectSlotsByName(OnLogDialog);
    } // setupUi

    void retranslateUi(QDialog *OnLogDialog)
    {
        OnLogDialog->setWindowTitle(QApplication::translate("OnLogDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        MovLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OnLogDialog: public Ui_OnLogDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLOGDIALOG_H
