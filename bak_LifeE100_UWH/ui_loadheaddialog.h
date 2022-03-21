/********************************************************************************
** Form generated from reading UI file 'loadheaddialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADHEADDIALOG_H
#define UI_LOADHEADDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadHeadDialog
{
public:
    QWidget *imgWidget;
    QPushButton *loadLastBut;
    QPushButton *loadNextBut;
    QPushButton *loadOkBut;
    QPushButton *loseAllBut;
    QLabel *LogLabel;

    void setupUi(QDialog *LoadHeadDialog)
    {
        if (LoadHeadDialog->objectName().isEmpty())
            LoadHeadDialog->setObjectName(QString::fromUtf8("LoadHeadDialog"));
        LoadHeadDialog->resize(1280, 800);
        LoadHeadDialog->setStyleSheet(QString::fromUtf8("#LoadHeadDialog\n"
"{\n"
"background-image: url(:/images/Head/loadHead_Bg.png);\n"
"}"));
        imgWidget = new QWidget(LoadHeadDialog);
        imgWidget->setObjectName(QString::fromUtf8("imgWidget"));
        imgWidget->setGeometry(QRect(40, 60, 1200, 580));
        imgWidget->setStyleSheet(QString::fromUtf8("#imgWidget\n"
"{\n"
"background: transparent;\n"
"	border-image: url(:/images/Head/step1_img.png);\n"
"}"));
        loadLastBut = new QPushButton(LoadHeadDialog);
        loadLastBut->setObjectName(QString::fromUtf8("loadLastBut"));
        loadLastBut->setGeometry(QRect(40, 680, 400, 80));
        loadLastBut->setStyleSheet(QString::fromUtf8("#loadLastBut:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Head/last_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadLastBut->setIcon(icon);
        loadLastBut->setIconSize(QSize(400, 80));
        loadNextBut = new QPushButton(LoadHeadDialog);
        loadNextBut->setObjectName(QString::fromUtf8("loadNextBut"));
        loadNextBut->setGeometry(QRect(440, 680, 800, 80));
        loadNextBut->setStyleSheet(QString::fromUtf8("#loadNextBut:focus{outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Head/next_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadNextBut->setIcon(icon1);
        loadNextBut->setIconSize(QSize(800, 80));
        loadOkBut = new QPushButton(LoadHeadDialog);
        loadOkBut->setObjectName(QString::fromUtf8("loadOkBut"));
        loadOkBut->setGeometry(QRect(440, 680, 800, 80));
        loadOkBut->setStyleSheet(QString::fromUtf8("#loadNextBut:focus{outline: none;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Head/Finish_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadOkBut->setIcon(icon2);
        loadOkBut->setIconSize(QSize(800, 80));
        loseAllBut = new QPushButton(LoadHeadDialog);
        loseAllBut->setObjectName(QString::fromUtf8("loseAllBut"));
        loseAllBut->setGeometry(QRect(40, 680, 400, 80));
        loseAllBut->setStyleSheet(QString::fromUtf8("#loseAllBut:focus{outline: none;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/Head/loseAll_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        loseAllBut->setIcon(icon3);
        loseAllBut->setIconSize(QSize(400, 80));
        LogLabel = new QLabel(LoadHeadDialog);
        LogLabel->setObjectName(QString::fromUtf8("LogLabel"));
        LogLabel->setGeometry(QRect(0, 0, 1280, 800));
        LogLabel->setStyleSheet(QString::fromUtf8("#LogLabel\n"
"{\n"
"background-image: url(:/images/LogOn_Win.png);\n"
"}"));

        retranslateUi(LoadHeadDialog);

        QMetaObject::connectSlotsByName(LoadHeadDialog);
    } // setupUi

    void retranslateUi(QDialog *LoadHeadDialog)
    {
        LoadHeadDialog->setWindowTitle(QApplication::translate("LoadHeadDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        loadLastBut->setText(QString());
        loadNextBut->setText(QString());
        loadOkBut->setText(QString());
        loseAllBut->setText(QString());
        LogLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoadHeadDialog: public Ui_LoadHeadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADHEADDIALOG_H
