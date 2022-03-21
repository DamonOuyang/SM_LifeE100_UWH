/********************************************************************************
** Form generated from reading UI file 'almshowdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALMSHOWDIALOG_H
#define UI_ALMSHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlmShowDialog
{
public:
    QPushButton *almWinBack;
    QTabWidget *almTabWidget;
    QWidget *almRTTab;
    QWidget *almRTWg;
    QWidget *almDataTab;
    QWidget *almDataWg;

    void setupUi(QDialog *AlmShowDialog)
    {
        if (AlmShowDialog->objectName().isEmpty())
            AlmShowDialog->setObjectName(QString::fromUtf8("AlmShowDialog"));
        AlmShowDialog->resize(1280, 760);
        AlmShowDialog->setStyleSheet(QString::fromUtf8("#AlmShowDialog\n"
"{\n"
"background-image: url(:/images/almShowWin_Bg.png);\n"
"}"));
        almWinBack = new QPushButton(AlmShowDialog);
        almWinBack->setObjectName(QString::fromUtf8("almWinBack"));
        almWinBack->setGeometry(QRect(190, 540, 900, 80));
        almWinBack->setStyleSheet(QString::fromUtf8("#almWinBack:focus{\n"
"outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/almShowBack_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        almWinBack->setIcon(icon);
        almWinBack->setIconSize(QSize(900, 80));
        almTabWidget = new QTabWidget(AlmShowDialog);
        almTabWidget->setObjectName(QString::fromUtf8("almTabWidget"));
        almTabWidget->setGeometry(QRect(190, 140, 900, 400));
        almTabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab \n"
"{	\n"
"    min-width:450px;min-height:80px;\n"
"    border-top-left-radius: 0px;\n"
"    border-top-right-radius: 0px;\n"
"}\n"
"QTabBar::tab:selected\n"
"{   \n"
"     margin-left: 0px;\n"
"     margin-right: -16px;\n"
"	padding:0px;\n"
"}\n"
"QTabBar::tab:selected:Disabled\n"
"{ \n"
"padding:0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected \n"
"{\n"
"\n"
"	padding:0px;\n"
"}\n"
"QTabBar::tab:!selected:Disabled\n"
"{\n"
"\n"
"	padding:0px;\n"
"}\n"
"\n"
"QTabWidget::pane\n"
"{\n"
"	border: 0px;\n"
"	top:0px;\n"
"	left: 0px;\n"
"}"));
        almTabWidget->setTabPosition(QTabWidget::North);
        almTabWidget->setTabShape(QTabWidget::Rounded);
        almTabWidget->setIconSize(QSize(450, 80));
        almTabWidget->setUsesScrollButtons(false);
        almRTTab = new QWidget();
        almRTTab->setObjectName(QString::fromUtf8("almRTTab"));
        almRTWg = new QWidget(almRTTab);
        almRTWg->setObjectName(QString::fromUtf8("almRTWg"));
        almRTWg->setGeometry(QRect(0, 0, 900, 320));
        almRTWg->setStyleSheet(QString::fromUtf8("#almRTWg{\n"
"background-image: url(:/images/almShowTab_Bg.png);\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/almRTTabDis_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/images/almRTTabEn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        icon1.addFile(QString::fromUtf8(":/images/prePourDis_Icon.png"), QSize(), QIcon::Disabled, QIcon::On);
        almTabWidget->addTab(almRTTab, icon1, QString());
        almDataTab = new QWidget();
        almDataTab->setObjectName(QString::fromUtf8("almDataTab"));
        almDataWg = new QWidget(almDataTab);
        almDataWg->setObjectName(QString::fromUtf8("almDataWg"));
        almDataWg->setGeometry(QRect(0, 0, 900, 320));
        almDataWg->setStyleSheet(QString::fromUtf8("#almDataWg{\n"
"background-image: url(:/images/almShowTab_Bg.png);\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/almDataTabDis_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/images/almDataTabEn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        icon2.addFile(QString::fromUtf8(":/images/pourDis_Icon.png"), QSize(), QIcon::Disabled, QIcon::Off);
        almTabWidget->addTab(almDataTab, icon2, QString());

        retranslateUi(AlmShowDialog);

        almTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AlmShowDialog);
    } // setupUi

    void retranslateUi(QDialog *AlmShowDialog)
    {
        AlmShowDialog->setWindowTitle(QApplication::translate("AlmShowDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        almWinBack->setText(QString());
        almTabWidget->setTabText(almTabWidget->indexOf(almRTTab), QString());
        almTabWidget->setTabText(almTabWidget->indexOf(almDataTab), QString());
    } // retranslateUi

};

namespace Ui {
    class AlmShowDialog: public Ui_AlmShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALMSHOWDIALOG_H
