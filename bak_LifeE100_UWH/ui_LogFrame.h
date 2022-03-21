/********************************************************************************
** Form generated from reading UI file 'LogFrame.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGFRAME_H
#define UI_LOGFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogFrame
{
public:
    QTabWidget *logTabWidget;
    QWidget *tabMonData;
    QWidget *tabOperLog;
    QPushButton *goNextButton;
    QLabel *label;
    QPushButton *goFirstButton;
    QPushButton *goEndButton;
    QPushButton *goLastButton;
    QPushButton *delAllButton;
    QPushButton *delCurrButton;
    QWidget *opreLogWidget;
    QGroupBox *beforeGroupBox;
    QGroupBox *laterGroupBox;

    void setupUi(QFrame *LogFrame)
    {
        if (LogFrame->objectName().isEmpty())
            LogFrame->setObjectName(QString::fromUtf8("LogFrame"));
        LogFrame->resize(1280, 680);
        LogFrame->setFrameShape(QFrame::StyledPanel);
        LogFrame->setFrameShadow(QFrame::Raised);
        logTabWidget = new QTabWidget(LogFrame);
        logTabWidget->setObjectName(QString::fromUtf8("logTabWidget"));
        logTabWidget->setGeometry(QRect(0, 0, 1200, 655));
        logTabWidget->setStyleSheet(QString::fromUtf8(""));
        logTabWidget->setTabPosition(QTabWidget::West);
        tabMonData = new QWidget();
        tabMonData->setObjectName(QString::fromUtf8("tabMonData"));
        tabMonData->setStyleSheet(QString::fromUtf8("#tabMonData\n"
"{\n"
"background-color: rgb(64, 64, 71);\n"
"}"));
        logTabWidget->addTab(tabMonData, QString());
        tabOperLog = new QWidget();
        tabOperLog->setObjectName(QString::fromUtf8("tabOperLog"));
        tabOperLog->setStyleSheet(QString::fromUtf8("#tabOperLog\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        goNextButton = new QPushButton(tabOperLog);
        goNextButton->setObjectName(QString::fromUtf8("goNextButton"));
        goNextButton->setGeometry(QRect(525, 555, 160, 60));
        goNextButton->setStyleSheet(QString::fromUtf8("#goNextButton\n"
"{\n"
"background-image: url(:/images/opreNext_Bt.png);\n"
"}\n"
"#goNextButton:pressed\n"
"{\n"
"background-image: url(:/images/opreNextDn_Bt.png);\n"
"}\n"
"#goNextButton:focus{outline: none;\n"
"}"));
        goNextButton->setIconSize(QSize(160, 60));
        label = new QLabel(tabOperLog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(420, 560, 100, 50));
        label->setAlignment(Qt::AlignCenter);
        goFirstButton = new QPushButton(tabOperLog);
        goFirstButton->setObjectName(QString::fromUtf8("goFirstButton"));
        goFirstButton->setGeometry(QRect(75, 555, 160, 60));
        goFirstButton->setStyleSheet(QString::fromUtf8("#goFirstButton\n"
"{\n"
"background-image: url(:/images/opreFirst_Bt.png);\n"
"}\n"
"#goFirstButton:pressed\n"
"{\n"
"background-image: url(:/images/opreFirstDn_Bt.png);\n"
"}\n"
"#goFirstButton:focus{outline: none;\n"
"}"));
        goFirstButton->setIconSize(QSize(160, 60));
        goEndButton = new QPushButton(tabOperLog);
        goEndButton->setObjectName(QString::fromUtf8("goEndButton"));
        goEndButton->setGeometry(QRect(705, 555, 160, 60));
        goEndButton->setStyleSheet(QString::fromUtf8("#goEndButton\n"
"{\n"
"background-image: url(:/images/opreEnd_Bt.png);\n"
"}\n"
"#goEndButton:pressed\n"
"{\n"
"background-image: url(:/images/opreEndDn_Bt.png);\n"
"}\n"
"#goEndButton:focus{outline: none;\n"
"}"));
        goEndButton->setIconSize(QSize(160, 60));
        goLastButton = new QPushButton(tabOperLog);
        goLastButton->setObjectName(QString::fromUtf8("goLastButton"));
        goLastButton->setGeometry(QRect(255, 556, 160, 60));
        goLastButton->setStyleSheet(QString::fromUtf8("#goLastButton\n"
"{\n"
"background-image: url(:/images/opreLast_Bt.png);\n"
"}\n"
"#goLastButton:pressed\n"
"{\n"
"background-image: url(:/images/opreLastDn_Bt.png);\n"
"}\n"
"#goLastButton:focus{outline: none;\n"
"}"));
        goLastButton->setIconSize(QSize(160, 60));
        delAllButton = new QPushButton(tabOperLog);
        delAllButton->setObjectName(QString::fromUtf8("delAllButton"));
        delAllButton->setGeometry(QRect(885, 555, 160, 60));
        delAllButton->setStyleSheet(QString::fromUtf8("#delAllButton\n"
"{\n"
"background-image: url(:/images/opreDelAll_Bt.png);\n"
"}\n"
"#delAllButton:pressed\n"
"{\n"
"background-image: url(:/images/opreDelAllDn_Bt.png);\n"
"}\n"
"#delAllButton:focus{outline: none;\n"
"}"));
        delAllButton->setIconSize(QSize(160, 60));
        delCurrButton = new QPushButton(tabOperLog);
        delCurrButton->setObjectName(QString::fromUtf8("delCurrButton"));
        delCurrButton->setGeometry(QRect(1000, 520, 160, 60));
        opreLogWidget = new QWidget(tabOperLog);
        opreLogWidget->setObjectName(QString::fromUtf8("opreLogWidget"));
        opreLogWidget->setGeometry(QRect(0, 0, 1075, 520));
        opreLogWidget->setStyleSheet(QString::fromUtf8("#opreLogWidget\n"
"{\n"
"background-image: url(:/images/opreLog_Bg.png);\n"
"}"));
        beforeGroupBox = new QGroupBox(opreLogWidget);
        beforeGroupBox->setObjectName(QString::fromUtf8("beforeGroupBox"));
        beforeGroupBox->setGeometry(QRect(0, 39, 537, 480));
        beforeGroupBox->setStyleSheet(QString::fromUtf8("#beforeGroupBox\n"
"{\n"
"background: transparent;\n"
"border:none;\n"
"}"));
        laterGroupBox = new QGroupBox(opreLogWidget);
        laterGroupBox->setObjectName(QString::fromUtf8("laterGroupBox"));
        laterGroupBox->setGeometry(QRect(538, 39, 537, 480));
        laterGroupBox->setStyleSheet(QString::fromUtf8("#laterGroupBox\n"
"{\n"
"background: transparent;\n"
"border:none;\n"
"}"));
        logTabWidget->addTab(tabOperLog, QString());

        retranslateUi(LogFrame);

        logTabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LogFrame);
    } // setupUi

    void retranslateUi(QFrame *LogFrame)
    {
        LogFrame->setWindowTitle(QApplication::translate("LogFrame", "Frame", 0, QApplication::UnicodeUTF8));
        logTabWidget->setTabText(logTabWidget->indexOf(tabMonData), QApplication::translate("LogFrame", "\347\233\221\346\216\247\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
        goNextButton->setText(QString());
        label->setText(QString());
        goFirstButton->setText(QString());
        goEndButton->setText(QString());
        goLastButton->setText(QString());
        delAllButton->setText(QString());
        delCurrButton->setText(QApplication::translate("LogFrame", "\345\210\240\351\231\244\345\275\223\345\211\215", 0, QApplication::UnicodeUTF8));
        beforeGroupBox->setTitle(QString());
        laterGroupBox->setTitle(QString());
        logTabWidget->setTabText(logTabWidget->indexOf(tabOperLog), QApplication::translate("LogFrame", "\346\223\215\344\275\234\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogFrame: public Ui_LogFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGFRAME_H
