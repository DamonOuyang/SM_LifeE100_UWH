/********************************************************************************
** Form generated from reading UI file 'monlogframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONLOGFRAME_H
#define UI_MONLOGFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MonLogFrame
{
public:
    QTabWidget *logTabWidget;
    QWidget *tabMonData;
    QWidget *tabOperLog;
    QWidget *opreLogWidget;
    QPushButton *goLastButton;
    QLabel *label;
    QPushButton *goNextButton;
    QPushButton *goFirstButton;
    QPushButton *goEndButton;
    QPushButton *delAllButton;

    void setupUi(QFrame *MonLogFrame)
    {
        if (MonLogFrame->objectName().isEmpty())
            MonLogFrame->setObjectName(QString::fromUtf8("MonLogFrame"));
        MonLogFrame->resize(1280, 680);
        logTabWidget = new QTabWidget(MonLogFrame);
        logTabWidget->setObjectName(QString::fromUtf8("logTabWidget"));
        logTabWidget->setGeometry(QRect(0, 0, 1200, 655));
        logTabWidget->setTabPosition(QTabWidget::West);
        tabMonData = new QWidget();
        tabMonData->setObjectName(QString::fromUtf8("tabMonData"));
        logTabWidget->addTab(tabMonData, QString());
        tabOperLog = new QWidget();
        tabOperLog->setObjectName(QString::fromUtf8("tabOperLog"));
        tabOperLog->setStyleSheet(QString::fromUtf8(""));
        opreLogWidget = new QWidget(tabOperLog);
        opreLogWidget->setObjectName(QString::fromUtf8("opreLogWidget"));
        opreLogWidget->setGeometry(QRect(0, 0, 1075, 520));
        opreLogWidget->setStyleSheet(QString::fromUtf8("#opreLogWidget\n"
"{\n"
"background-image: url(:/images/opreLog_Bg.png);\n"
"}"));
        goLastButton = new QPushButton(tabOperLog);
        goLastButton->setObjectName(QString::fromUtf8("goLastButton"));
        goLastButton->setGeometry(QRect(286, 555, 160, 60));
        goLastButton->setStyleSheet(QString::fromUtf8("#goLastButton:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/opreLast_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        goLastButton->setIcon(icon);
        goLastButton->setIconSize(QSize(160, 60));
        label = new QLabel(tabOperLog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(451, 555, 100, 50));
        label->setAlignment(Qt::AlignCenter);
        goNextButton = new QPushButton(tabOperLog);
        goNextButton->setObjectName(QString::fromUtf8("goNextButton"));
        goNextButton->setGeometry(QRect(556, 555, 160, 60));
        goNextButton->setStyleSheet(QString::fromUtf8("#goNextButton:focus{outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/opreNext_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        goNextButton->setIcon(icon1);
        goNextButton->setIconSize(QSize(160, 60));
        goFirstButton = new QPushButton(tabOperLog);
        goFirstButton->setObjectName(QString::fromUtf8("goFirstButton"));
        goFirstButton->setGeometry(QRect(106, 555, 160, 60));
        goFirstButton->setStyleSheet(QString::fromUtf8("#goFirstButton:focus{outline: none;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/opreFirst_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        goFirstButton->setIcon(icon2);
        goFirstButton->setIconSize(QSize(160, 60));
        goEndButton = new QPushButton(tabOperLog);
        goEndButton->setObjectName(QString::fromUtf8("goEndButton"));
        goEndButton->setGeometry(QRect(736, 555, 160, 60));
        goEndButton->setStyleSheet(QString::fromUtf8("#goEndButton:focus{outline: none;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/opreEnd_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        goEndButton->setIcon(icon3);
        goEndButton->setIconSize(QSize(160, 60));
        delAllButton = new QPushButton(tabOperLog);
        delAllButton->setObjectName(QString::fromUtf8("delAllButton"));
        delAllButton->setGeometry(QRect(916, 555, 160, 60));
        delAllButton->setStyleSheet(QString::fromUtf8("#delAllButton:focus{outline: none;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/opreDelAll_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        delAllButton->setIcon(icon4);
        delAllButton->setIconSize(QSize(160, 60));
        logTabWidget->addTab(tabOperLog, QString());

        retranslateUi(MonLogFrame);

        logTabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MonLogFrame);
    } // setupUi

    void retranslateUi(QFrame *MonLogFrame)
    {
        MonLogFrame->setWindowTitle(QApplication::translate("MonLogFrame", "Frame", 0, QApplication::UnicodeUTF8));
        logTabWidget->setTabText(logTabWidget->indexOf(tabMonData), QApplication::translate("MonLogFrame", "\347\233\221\346\216\247\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
        goLastButton->setText(QString());
        label->setText(QString());
        goNextButton->setText(QString());
        goFirstButton->setText(QString());
        goEndButton->setText(QString());
        delAllButton->setText(QString());
        logTabWidget->setTabText(logTabWidget->indexOf(tabOperLog), QApplication::translate("MonLogFrame", "\346\223\215\344\275\234\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MonLogFrame: public Ui_MonLogFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONLOGFRAME_H
