/********************************************************************************
** Form generated from reading UI file 'systemsetdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSETDIALOG_H
#define UI_SYSTEMSETDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemSetDialog
{
public:
    QTabWidget *setTabWidget;
    QWidget *dataTabDlg;
    QWidget *logTabDlg;
    QWidget *cfgTabDlg;
    QWidget *aboutTabDlg;
    QTextEdit *pTextEdit;
    QPushButton *updateBut;

    void setupUi(QDialog *SystemSetDialog)
    {
        if (SystemSetDialog->objectName().isEmpty())
            SystemSetDialog->setObjectName(QString::fromUtf8("SystemSetDialog"));
        SystemSetDialog->resize(1280, 760);
        SystemSetDialog->setStyleSheet(QString::fromUtf8("#SystemSetDialog{\n"
"background-color: rgb(38, 38, 44);\n"
"}\n"
""));
        setTabWidget = new QTabWidget(SystemSetDialog);
        setTabWidget->setObjectName(QString::fromUtf8("setTabWidget"));
        setTabWidget->setGeometry(QRect(40, 20, 1200, 740));
        setTabWidget->setMinimumSize(QSize(1200, 605));
        QFont font;
        font.setPointSize(20);
        font.setItalic(false);
        setTabWidget->setFont(font);
        setTabWidget->setAutoFillBackground(false);
        setTabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane\n"
"{\n"
"padding:-1px;\n"
"top:-1px;\n"
"}"));
        setTabWidget->setUsesScrollButtons(false);
        setTabWidget->setDocumentMode(false);
        dataTabDlg = new QWidget();
        dataTabDlg->setObjectName(QString::fromUtf8("dataTabDlg"));
        dataTabDlg->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 38, 44);"));
        setTabWidget->addTab(dataTabDlg, QString());
        logTabDlg = new QWidget();
        logTabDlg->setObjectName(QString::fromUtf8("logTabDlg"));
        logTabDlg->setStyleSheet(QString::fromUtf8("#logTabDlg\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        setTabWidget->addTab(logTabDlg, QString());
        cfgTabDlg = new QWidget();
        cfgTabDlg->setObjectName(QString::fromUtf8("cfgTabDlg"));
        cfgTabDlg->setStyleSheet(QString::fromUtf8("#cfgTabDlg\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        setTabWidget->addTab(cfgTabDlg, QString());
        aboutTabDlg = new QWidget();
        aboutTabDlg->setObjectName(QString::fromUtf8("aboutTabDlg"));
        aboutTabDlg->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 38, 44);"));
        pTextEdit = new QTextEdit(aboutTabDlg);
        pTextEdit->setObjectName(QString::fromUtf8("pTextEdit"));
        pTextEdit->setGeometry(QRect(0, 20, 1200, 520));
        pTextEdit->setStyleSheet(QString::fromUtf8("#pTextEdit\n"
"{\n"
"background-color: rgb(64, 64, 71);\n"
"font-family:simhei;\n"
"color: rgb(255,255,255);\n"
"font:18px;\n"
"}"));
        updateBut = new QPushButton(aboutTabDlg);
        updateBut->setObjectName(QString::fromUtf8("updateBut"));
        updateBut->setGeometry(QRect(1039, 574, 160, 60));
        updateBut->setStyleSheet(QString::fromUtf8("#updateBut\n"
"{\n"
"background-image: url(:/images/update_Bt.png);\n"
"}\n"
"#updateBut:pressed\n"
"{\n"
"background-image: url(:/images/updateDn_Bt.png);\n"
"}\n"
"#updateBut:focus{outline: none;\n"
"}"));
        updateBut->setIconSize(QSize(160, 60));
        setTabWidget->addTab(aboutTabDlg, QString());

        retranslateUi(SystemSetDialog);

        setTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SystemSetDialog);
    } // setupUi

    void retranslateUi(QDialog *SystemSetDialog)
    {
        SystemSetDialog->setWindowTitle(QApplication::translate("SystemSetDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        setTabWidget->setTabText(setTabWidget->indexOf(dataTabDlg), QApplication::translate("SystemSetDialog", "\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        setTabWidget->setTabText(setTabWidget->indexOf(logTabDlg), QApplication::translate("SystemSetDialog", "\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
        setTabWidget->setTabText(setTabWidget->indexOf(cfgTabDlg), QApplication::translate("SystemSetDialog", "\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        updateBut->setText(QString());
        setTabWidget->setTabText(setTabWidget->indexOf(aboutTabDlg), QApplication::translate("SystemSetDialog", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SystemSetDialog: public Ui_SystemSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSETDIALOG_H
