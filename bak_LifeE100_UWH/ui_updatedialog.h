/********************************************************************************
** Form generated from reading UI file 'updatedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEDIALOG_H
#define UI_UPDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UpDateDialog
{
public:
    QPushButton *cancelButton;
    QPushButton *okButton;
    QLabel *label;
    QProgressBar *upMcuBar;

    void setupUi(QDialog *UpDateDialog)
    {
        if (UpDateDialog->objectName().isEmpty())
            UpDateDialog->setObjectName(QStringLiteral("UpDateDialog"));
        UpDateDialog->resize(400, 195);
        cancelButton = new QPushButton(UpDateDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(46, 130, 120, 50));
        okButton = new QPushButton(UpDateDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(233, 130, 120, 50));
        label = new QLabel(UpDateDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 10, 231, 41));
        label->setAlignment(Qt::AlignCenter);
        upMcuBar = new QProgressBar(UpDateDialog);
        upMcuBar->setObjectName(QStringLiteral("upMcuBar"));
        upMcuBar->setGeometry(QRect(50, 70, 300, 25));
        upMcuBar->setValue(0);

        retranslateUi(UpDateDialog);

        QMetaObject::connectSlotsByName(UpDateDialog);
    } // setupUi

    void retranslateUi(QDialog *UpDateDialog)
    {
        UpDateDialog->setWindowTitle(QApplication::translate("UpDateDialog", "\350\256\276\345\244\207\345\215\207\347\272\247", 0));
        cancelButton->setText(QApplication::translate("UpDateDialog", "\345\217\226\346\266\210", 0));
        okButton->setText(QApplication::translate("UpDateDialog", "\347\241\256\350\256\244", 0));
        label->setText(QApplication::translate("UpDateDialog", "\350\257\267\351\200\211\346\213\251\345\215\207\347\272\247\350\256\276\345\244\207\347\261\273\345\236\213", 0));
    } // retranslateUi

};

namespace Ui {
    class UpDateDialog: public Ui_UpDateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEDIALOG_H
