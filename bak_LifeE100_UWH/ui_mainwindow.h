/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QRoundProgressBar.h"
#include "BatteryLogManage.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *waterTmpWg;
    QPushButton *wtrRomOnOffBt;
    QLabel *showTmpLabel;
    QLineEdit *setWatTmpLE;
    QLabel *sysTmtLabel;
    QWidget *waterGageWg;
    QRoundProgressBar *WatRoundBar;
    QVBoxLayout *verticalLayout;
    QWidget *strTmtWg;
    QLabel *strTmtLabel;
    QTabWidget *monTabWidget;
    QWidget *prePourTab;
    QWidget *prePourWg;
    QLabel *preFlowLb;
    QLabel *preTmpLb;
    QLabel *prePressLb;
    QLineEdit *preSpeedSetLE;
    QLabel *preSpeedLb;
    QLabel *preFloRLb;
    QWidget *pourTab;
    QWidget *pourWg;
    QLabel *pourFlowLb;
    QLabel *pourTmpLb;
    QLabel *pourSpeedLb;
    QLineEdit *pourPressSetLE;
    QLabel *pourPressLb;
    QLabel *pourFloRLb;
    QWidget *alarmWg;
    QLabel *almShowLb;
    QPushButton *almShowBtn;
    QPushButton *almOnOffBtn;
    QPushButton *sysSetBtn;
    QPushButton *unLockScreenBtn;
    QWidget *arteryHeadWidget;
    QPushButton *BPStrBtn;
    QWidget *veinHeadWidget;
    QPushButton *BPStrBtnV;
    QTabWidget *VmonTabWidget;
    QWidget *prePourTabV;
    QWidget *prePourWgV;
    QLabel *preFlowLbV;
    QLabel *preTmpLbV;
    QLabel *prePressLbV;
    QLineEdit *preSpeedSetLEV;
    QLabel *preSpeedLbV;
    QLabel *preFloRLbV;
    QWidget *pourTabV;
    QWidget *pourWgV;
    QLabel *pourFlowLbV;
    QLabel *pourTmpLbV;
    QLabel *pourSpeedLbV;
    QLineEdit *pourPressSetLEV;
    QLabel *pourPressLbV;
    QLabel *pourFloRLbV;
    BatteryLogManage *batWidget;
    QLabel *batSocLabel;
    QLabel *chgIconLb;
    QWidget *acLinkLog;
    QWidget *batLinkLog;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 800);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        waterTmpWg = new QWidget(centralWidget);
        waterTmpWg->setObjectName(QString::fromUtf8("waterTmpWg"));
        waterTmpWg->setGeometry(QRect(40, 180, 300, 245));
        waterTmpWg->setStyleSheet(QString::fromUtf8("#waterTmpWg{\n"
"background-image: url(:/images/waterRoomTmpOff_Bg.png);\n"
"}"));
        wtrRomOnOffBt = new QPushButton(waterTmpWg);
        wtrRomOnOffBt->setObjectName(QString::fromUtf8("wtrRomOnOffBt"));
        wtrRomOnOffBt->setGeometry(QRect(187, 28, 66, 66));
        wtrRomOnOffBt->setStyleSheet(QString::fromUtf8("#wtrRomOnOffBt\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#wtrRomOnOffBt:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/tmpOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/images/tmpOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QString::fromUtf8(":/images/tmpOff_Icon.png"), QSize(), QIcon::Disabled, QIcon::Off);
        wtrRomOnOffBt->setIcon(icon);
        wtrRomOnOffBt->setIconSize(QSize(135, 66));
        wtrRomOnOffBt->setCheckable(true);
        wtrRomOnOffBt->setFlat(true);
        showTmpLabel = new QLabel(waterTmpWg);
        showTmpLabel->setObjectName(QString::fromUtf8("showTmpLabel"));
        showTmpLabel->setGeometry(QRect(0, 166, 170, 36));
        showTmpLabel->setStyleSheet(QString::fromUtf8("#showTmpLabel\n"
"{\n"
"font-family:simhei;\n"
"color: rgb(255, 204, 143);\n"
"font:36px;\n"
"}"));
        showTmpLabel->setAlignment(Qt::AlignCenter);
        setWatTmpLE = new QLineEdit(waterTmpWg);
        setWatTmpLE->setObjectName(QString::fromUtf8("setWatTmpLE"));
        setWatTmpLE->setGeometry(QRect(170, 170, 75, 25));
        setWatTmpLE->setCursor(QCursor(Qt::ArrowCursor));
        setWatTmpLE->setStyleSheet(QString::fromUtf8("#setWatTmpLE{\n"
"background: transparent;\n"
"font-family:simhei;\n"
"color: rgb(255,255,255);\n"
"font:24px;\n"
"}\n"
"#setWatTmpLE{\n"
"border-width:0;border-style:outset\n"
"}"));
        setWatTmpLE->setAlignment(Qt::AlignCenter);
        setWatTmpLE->setDragEnabled(false);
        setWatTmpLE->setReadOnly(true);
        sysTmtLabel = new QLabel(centralWidget);
        sysTmtLabel->setObjectName(QString::fromUtf8("sysTmtLabel"));
        sysTmtLabel->setGeometry(QRect(40, 8, 300, 25));
        sysTmtLabel->setStyleSheet(QString::fromUtf8("#sysTmtLabel\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        waterGageWg = new QWidget(centralWidget);
        waterGageWg->setObjectName(QString::fromUtf8("waterGageWg"));
        waterGageWg->setGeometry(QRect(40, 445, 300, 100));
        waterGageWg->setStyleSheet(QString::fromUtf8("#waterGageWg{\n"
"image: url(:/images/waterRoomGage_Bg.png);\n"
"}"));
        WatRoundBar = new QRoundProgressBar(waterGageWg);
        WatRoundBar->setObjectName(QString::fromUtf8("WatRoundBar"));
        WatRoundBar->setGeometry(QRect(190, 20, 60, 60));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(54, 54, 61, 255));
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
        QBrush brush6(QColor(85, 85, 85, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        QBrush brush7(QColor(64, 64, 71, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush3);
        QBrush brush8(QColor(255, 170, 0, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush8);
        QBrush brush9(QColor(115, 115, 115, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush9);
        QBrush brush10(QColor(255, 255, 220, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        QBrush brush11(QColor(0, 0, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush11);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush11);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush3);
        QBrush brush12(QColor(50, 100, 150, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush12);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush11);
        WatRoundBar->setPalette(palette);
        verticalLayout = new QVBoxLayout(WatRoundBar);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        strTmtWg = new QWidget(centralWidget);
        strTmtWg->setObjectName(QString::fromUtf8("strTmtWg"));
        strTmtWg->setGeometry(QRect(40, 60, 300, 100));
        strTmtWg->setStyleSheet(QString::fromUtf8("#strTmtWg{\n"
"image: url(:/images/strTmt_Bg.png);\n"
"}"));
        strTmtLabel = new QLabel(strTmtWg);
        strTmtLabel->setObjectName(QString::fromUtf8("strTmtLabel"));
        strTmtLabel->setGeometry(QRect(0, 53, 300, 25));
        strTmtLabel->setStyleSheet(QString::fromUtf8("#strTmtLabel\n"
"{\n"
"   font-family:simhei;\n"
"   color: rgb(255,255,255);\n"
"   font:24px;\n"
"}"));
        strTmtLabel->setAlignment(Qt::AlignCenter);
        monTabWidget = new QTabWidget(centralWidget);
        monTabWidget->setObjectName(QString::fromUtf8("monTabWidget"));
        monTabWidget->setGeometry(QRect(360, 180, 430, 590));
        monTabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab \n"
"{	\n"
"    min-width:215px;min-height:90px;\n"
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
        monTabWidget->setTabPosition(QTabWidget::South);
        monTabWidget->setTabShape(QTabWidget::Rounded);
        monTabWidget->setIconSize(QSize(215, 90));
        monTabWidget->setUsesScrollButtons(false);
        prePourTab = new QWidget();
        prePourTab->setObjectName(QString::fromUtf8("prePourTab"));
        prePourWg = new QWidget(prePourTab);
        prePourWg->setObjectName(QString::fromUtf8("prePourWg"));
        prePourWg->setGeometry(QRect(0, 0, 430, 500));
        prePourWg->setStyleSheet(QString::fromUtf8("#prePourWg{\n"
"	background-image: url(:/images/monDataPrePour_Bg.png);\n"
"}\n"
"#prePourWg:Disabled{\n"
"background-image: url(:/images/monDataPrePourOff_Bg.png);\n"
"}"));
        preFlowLb = new QLabel(prePourWg);
        preFlowLb->setObjectName(QString::fromUtf8("preFlowLb"));
        preFlowLb->setGeometry(QRect(99, 170, 140, 60));
        preFlowLb->setStyleSheet(QString::fromUtf8("#preFlowLb\n"
"{\n"
"color: rgb(255, 202, 234);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preFlowLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        preTmpLb = new QLabel(prePourWg);
        preTmpLb->setObjectName(QString::fromUtf8("preTmpLb"));
        preTmpLb->setGeometry(QRect(99, 295, 140, 60));
        preTmpLb->setStyleSheet(QString::fromUtf8("#preTmpLb\n"
"{\n"
"color: rgb(255, 202, 234);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preTmpLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        prePressLb = new QLabel(prePourWg);
        prePressLb->setObjectName(QString::fromUtf8("prePressLb"));
        prePressLb->setGeometry(QRect(115, 419, 70, 25));
        prePressLb->setStyleSheet(QString::fromUtf8("#prePressLb\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        prePressLb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        preSpeedSetLE = new QLineEdit(prePourWg);
        preSpeedSetLE->setObjectName(QString::fromUtf8("preSpeedSetLE"));
        preSpeedSetLE->setGeometry(QRect(285, 48, 75, 40));
        preSpeedSetLE->setStyleSheet(QString::fromUtf8("#preSpeedSetLE{\n"
"background: transparent;\n"
"color:rgb(255,255,255);\n"
"font-family:simhei;\n"
"font:24px;\n"
"}\n"
"QLineEdit{\n"
"border-width:0;border-style:outset\n"
"}"));
        preSpeedSetLE->setAlignment(Qt::AlignCenter);
        preSpeedLb = new QLabel(prePourWg);
        preSpeedLb->setObjectName(QString::fromUtf8("preSpeedLb"));
        preSpeedLb->setGeometry(QRect(99, 40, 140, 60));
        preSpeedLb->setStyleSheet(QString::fromUtf8("#preSpeedLb\n"
"{\n"
"color: rgb(255, 202, 234);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preSpeedLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        preFloRLb = new QLabel(prePourWg);
        preFloRLb->setObjectName(QString::fromUtf8("preFloRLb"));
        preFloRLb->setGeometry(QRect(330, 419, 70, 25));
        preFloRLb->setStyleSheet(QString::fromUtf8("#preFloRLb\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        preFloRLb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/prePourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/images/prePourOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        icon1.addFile(QString::fromUtf8(":/images/prePourOff_Icon.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/images/prePourDis_Icon.png"), QSize(), QIcon::Disabled, QIcon::On);
        monTabWidget->addTab(prePourTab, icon1, QString());
        pourTab = new QWidget();
        pourTab->setObjectName(QString::fromUtf8("pourTab"));
        pourTab->setMaximumSize(QSize(814, 562));
        pourTab->setSizeIncrement(QSize(814, 562));
        pourWg = new QWidget(pourTab);
        pourWg->setObjectName(QString::fromUtf8("pourWg"));
        pourWg->setGeometry(QRect(0, 0, 430, 500));
        pourWg->setStyleSheet(QString::fromUtf8("#pourWg{\n"
"background-image: url(:/images/monDataPour_Bg.png);\n"
"\n"
"}"));
        pourFlowLb = new QLabel(pourWg);
        pourFlowLb->setObjectName(QString::fromUtf8("pourFlowLb"));
        pourFlowLb->setGeometry(QRect(99, 170, 140, 60));
        pourFlowLb->setStyleSheet(QString::fromUtf8("#pourFlowLb\n"
"{\n"
"color: rgb(255, 202, 234);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourFlowLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pourTmpLb = new QLabel(pourWg);
        pourTmpLb->setObjectName(QString::fromUtf8("pourTmpLb"));
        pourTmpLb->setGeometry(QRect(99, 295, 140, 60));
        pourTmpLb->setStyleSheet(QString::fromUtf8("#pourTmpLb\n"
"{\n"
"color: rgb(255, 202, 234);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourTmpLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pourSpeedLb = new QLabel(pourWg);
        pourSpeedLb->setObjectName(QString::fromUtf8("pourSpeedLb"));
        pourSpeedLb->setGeometry(QRect(115, 419, 70, 25));
        pourSpeedLb->setStyleSheet(QString::fromUtf8("#pourSpeedLb\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        pourSpeedLb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pourPressSetLE = new QLineEdit(pourWg);
        pourPressSetLE->setObjectName(QString::fromUtf8("pourPressSetLE"));
        pourPressSetLE->setGeometry(QRect(285, 48, 75, 40));
        pourPressSetLE->setStyleSheet(QString::fromUtf8("#pourPressSetLE{\n"
"background: transparent;\n"
"color:rgb(255,255,255);\n"
"font-family:simhei;\n"
"font:24px;\n"
"}\n"
"QLineEdit{\n"
"border-width:0;border-style:outset\n"
"}"));
        pourPressSetLE->setAlignment(Qt::AlignCenter);
        pourPressLb = new QLabel(pourWg);
        pourPressLb->setObjectName(QString::fromUtf8("pourPressLb"));
        pourPressLb->setGeometry(QRect(99, 40, 140, 60));
        pourPressLb->setStyleSheet(QString::fromUtf8("#pourPressLb\n"
"{\n"
"color: rgb(255, 202, 234);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourPressLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pourFloRLb = new QLabel(pourWg);
        pourFloRLb->setObjectName(QString::fromUtf8("pourFloRLb"));
        pourFloRLb->setGeometry(QRect(330, 419, 70, 25));
        pourFloRLb->setStyleSheet(QString::fromUtf8("#pourFloRLb\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        pourFloRLb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/pourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/images/pourOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        icon2.addFile(QString::fromUtf8(":/images/pourDis_Icon.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/images/pourDis_Icon.png"), QSize(), QIcon::Disabled, QIcon::On);
        monTabWidget->addTab(pourTab, icon2, QString());
        alarmWg = new QWidget(centralWidget);
        alarmWg->setObjectName(QString::fromUtf8("alarmWg"));
        alarmWg->setGeometry(QRect(40, 565, 300, 115));
        alarmWg->setStyleSheet(QString::fromUtf8("#alarmWg\n"
"{\n"
"	border: 0px;\n"
"	top:0px;\n"
"	left: 0px;\n"
"}"));
        almShowLb = new QLabel(alarmWg);
        almShowLb->setObjectName(QString::fromUtf8("almShowLb"));
        almShowLb->setGeometry(QRect(0, 0, 300, 115));
        almShowLb->setStyleSheet(QString::fromUtf8("#almShowLb{\n"
"background-image: url(:/images/alarm.png);\n"
"   font-family:simhei;\n"
"   font:bold;\n"
"   font:26px;\n"
"}"));
        almShowLb->setAlignment(Qt::AlignCenter);
        almShowBtn = new QPushButton(alarmWg);
        almShowBtn->setObjectName(QString::fromUtf8("almShowBtn"));
        almShowBtn->setGeometry(QRect(0, 0, 300, 113));
        almShowBtn->setStyleSheet(QString::fromUtf8("#almShowBtn{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px\n"
"}\n"
"#almShowBtn:focus{outline: none;\n"
"}"));
        almShowBtn->setCheckable(false);
        almShowBtn->setFlat(false);
        almOnOffBtn = new QPushButton(centralWidget);
        almOnOffBtn->setObjectName(QString::fromUtf8("almOnOffBtn"));
        almOnOffBtn->setGeometry(QRect(147, 700, 86, 60));
        almOnOffBtn->setStyleSheet(QString::fromUtf8("#almOnOffBtn{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#almOnOffBtn:focus{outline: none;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/alarmDis_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/images/alarmOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        icon3.addFile(QString::fromUtf8(":/images/alarmOff_Icon.png"), QSize(), QIcon::Disabled, QIcon::Off);
        almOnOffBtn->setIcon(icon3);
        almOnOffBtn->setIconSize(QSize(86, 60));
        almOnOffBtn->setCheckable(true);
        almOnOffBtn->setFlat(true);
        sysSetBtn = new QPushButton(centralWidget);
        sysSetBtn->setObjectName(QString::fromUtf8("sysSetBtn"));
        sysSetBtn->setGeometry(QRect(254, 700, 86, 60));
        sysSetBtn->setStyleSheet(QString::fromUtf8("#sysSetBtn{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#sysSetBtn:focus{outline: none;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/sysSet_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        sysSetBtn->setIcon(icon4);
        sysSetBtn->setIconSize(QSize(86, 60));
        sysSetBtn->setFlat(true);
        unLockScreenBtn = new QPushButton(centralWidget);
        unLockScreenBtn->setObjectName(QString::fromUtf8("unLockScreenBtn"));
        unLockScreenBtn->setGeometry(QRect(40, 700, 86, 60));
        unLockScreenBtn->setStyleSheet(QString::fromUtf8("#unLockScreenBtn{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#unLockScreenBtn:focus{outline: none;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/unLocking_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        unLockScreenBtn->setIcon(icon5);
        unLockScreenBtn->setIconSize(QSize(86, 60));
        unLockScreenBtn->setFlat(true);
        arteryHeadWidget = new QWidget(centralWidget);
        arteryHeadWidget->setObjectName(QString::fromUtf8("arteryHeadWidget"));
        arteryHeadWidget->setGeometry(QRect(360, 60, 430, 120));
        arteryHeadWidget->setStyleSheet(QString::fromUtf8("#arteryHeadWidget{\n"
"background-image: url(:/images/arteryHeadDis_Bg.png);\n"
"}"));
        BPStrBtn = new QPushButton(arteryHeadWidget);
        BPStrBtn->setObjectName(QString::fromUtf8("BPStrBtn"));
        BPStrBtn->setGeometry(QRect(302, 27, 66, 66));
        BPStrBtn->setStyleSheet(QString::fromUtf8("#BPStrBtn\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#BPStrBtn:focus{outline: none;\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/BP_Stop_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/images/BP_Start_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        BPStrBtn->setIcon(icon6);
        BPStrBtn->setIconSize(QSize(139, 139));
        BPStrBtn->setCheckable(true);
        BPStrBtn->setFlat(true);
        veinHeadWidget = new QWidget(centralWidget);
        veinHeadWidget->setObjectName(QString::fromUtf8("veinHeadWidget"));
        veinHeadWidget->setGeometry(QRect(810, 60, 430, 120));
        veinHeadWidget->setStyleSheet(QString::fromUtf8("#veinHeadWidget{\n"
"background-image: url(:/images/veinHeadDis_Bg.png);\n"
"}\n"
""));
        BPStrBtnV = new QPushButton(veinHeadWidget);
        BPStrBtnV->setObjectName(QString::fromUtf8("BPStrBtnV"));
        BPStrBtnV->setGeometry(QRect(302, 27, 66, 66));
        BPStrBtnV->setStyleSheet(QString::fromUtf8("#BPStrBtnV\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#BPStrBtnV:focus{outline: none;\n"
"}"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/vBP_Stop_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/images/vBP_Start_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        BPStrBtnV->setIcon(icon7);
        BPStrBtnV->setIconSize(QSize(139, 139));
        BPStrBtnV->setCheckable(true);
        BPStrBtnV->setFlat(true);
        VmonTabWidget = new QTabWidget(centralWidget);
        VmonTabWidget->setObjectName(QString::fromUtf8("VmonTabWidget"));
        VmonTabWidget->setGeometry(QRect(810, 180, 430, 590));
        VmonTabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab \n"
"{	\n"
"    min-width:215px;min-height:90px;\n"
"    border-top-left-radius: 0px;\n"
"    border-top-right-radius: 0px;\n"
"}\n"
"QTabBar::tab:selected\n"
"{   \n"
" \n"
"     margin-left: 0px;\n"
"     margin-right: -16px;\n"
"\n"
"	padding:0px;\n"
"}\n"
"QTabBar::tab:selected:Disabled\n"
"{ \n"
"\n"
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
        VmonTabWidget->setTabPosition(QTabWidget::South);
        VmonTabWidget->setIconSize(QSize(215, 90));
        VmonTabWidget->setUsesScrollButtons(false);
        prePourTabV = new QWidget();
        prePourTabV->setObjectName(QString::fromUtf8("prePourTabV"));
        prePourWgV = new QWidget(prePourTabV);
        prePourWgV->setObjectName(QString::fromUtf8("prePourWgV"));
        prePourWgV->setGeometry(QRect(0, 0, 430, 500));
        prePourWgV->setStyleSheet(QString::fromUtf8("#prePourWgV{\n"
"background-image: url(:/images/monDataPrePour_Bg.png);\n"
"}\n"
"#prePourWgV:Disabled{\n"
"background-image: url(:/images/monDataPrePourOff_Bg.png);\n"
"}"));
        preFlowLbV = new QLabel(prePourWgV);
        preFlowLbV->setObjectName(QString::fromUtf8("preFlowLbV"));
        preFlowLbV->setGeometry(QRect(99, 170, 140, 60));
        preFlowLbV->setStyleSheet(QString::fromUtf8("#preFlowLbV\n"
"{\n"
"color: rgb(179, 228, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preFlowLbV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        preTmpLbV = new QLabel(prePourWgV);
        preTmpLbV->setObjectName(QString::fromUtf8("preTmpLbV"));
        preTmpLbV->setGeometry(QRect(99, 295, 140, 60));
        preTmpLbV->setStyleSheet(QString::fromUtf8("#preTmpLbV\n"
"{\n"
"color: rgb(179, 228, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preTmpLbV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        prePressLbV = new QLabel(prePourWgV);
        prePressLbV->setObjectName(QString::fromUtf8("prePressLbV"));
        prePressLbV->setGeometry(QRect(115, 419, 70, 25));
        prePressLbV->setStyleSheet(QString::fromUtf8("#prePressLbV\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        prePressLbV->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        preSpeedSetLEV = new QLineEdit(prePourWgV);
        preSpeedSetLEV->setObjectName(QString::fromUtf8("preSpeedSetLEV"));
        preSpeedSetLEV->setGeometry(QRect(285, 48, 75, 40));
        preSpeedSetLEV->setStyleSheet(QString::fromUtf8("#preSpeedSetLEV{\n"
"background: transparent;\n"
"color:rgb(255,255,255);\n"
"font-family:simhei;\n"
"font:24px;\n"
"}\n"
"QLineEdit{\n"
"border-width:0;border-style:outset\n"
"}"));
        preSpeedSetLEV->setAlignment(Qt::AlignCenter);
        preSpeedLbV = new QLabel(prePourWgV);
        preSpeedLbV->setObjectName(QString::fromUtf8("preSpeedLbV"));
        preSpeedLbV->setGeometry(QRect(99, 40, 140, 60));
        preSpeedLbV->setStyleSheet(QString::fromUtf8("#preSpeedLbV\n"
"{\n"
"color: rgb(179, 228, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preSpeedLbV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        preFloRLbV = new QLabel(prePourWgV);
        preFloRLbV->setObjectName(QString::fromUtf8("preFloRLbV"));
        preFloRLbV->setGeometry(QRect(330, 419, 70, 25));
        preFloRLbV->setStyleSheet(QString::fromUtf8("#preFloRLbV\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        preFloRLbV->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/prePourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/images/prePourOn_IconV.png"), QSize(), QIcon::Normal, QIcon::On);
        icon8.addFile(QString::fromUtf8(":/images/prePourDis_IconV.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/images/prePourDis_IconV.png"), QSize(), QIcon::Disabled, QIcon::On);
        VmonTabWidget->addTab(prePourTabV, icon8, QString());
        pourTabV = new QWidget();
        pourTabV->setObjectName(QString::fromUtf8("pourTabV"));
        pourTabV->setMaximumSize(QSize(814, 562));
        pourTabV->setSizeIncrement(QSize(814, 562));
        pourWgV = new QWidget(pourTabV);
        pourWgV->setObjectName(QString::fromUtf8("pourWgV"));
        pourWgV->setGeometry(QRect(0, 0, 430, 500));
        pourWgV->setStyleSheet(QString::fromUtf8("#pourWgV{\n"
"background-image: url(:/images/monDataPour_Bg.png);\n"
"\n"
"}"));
        pourFlowLbV = new QLabel(pourWgV);
        pourFlowLbV->setObjectName(QString::fromUtf8("pourFlowLbV"));
        pourFlowLbV->setGeometry(QRect(99, 170, 140, 60));
        pourFlowLbV->setStyleSheet(QString::fromUtf8("#pourFlowLbV\n"
"{\n"
"color: rgb(179, 228, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourFlowLbV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pourTmpLbV = new QLabel(pourWgV);
        pourTmpLbV->setObjectName(QString::fromUtf8("pourTmpLbV"));
        pourTmpLbV->setGeometry(QRect(99, 295, 140, 60));
        pourTmpLbV->setStyleSheet(QString::fromUtf8("#pourTmpLbV\n"
"{\n"
"color: rgb(179, 228, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourTmpLbV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pourSpeedLbV = new QLabel(pourWgV);
        pourSpeedLbV->setObjectName(QString::fromUtf8("pourSpeedLbV"));
        pourSpeedLbV->setGeometry(QRect(115, 419, 70, 25));
        pourSpeedLbV->setStyleSheet(QString::fromUtf8("#pourSpeedLbV\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        pourSpeedLbV->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pourPressSetLEV = new QLineEdit(pourWgV);
        pourPressSetLEV->setObjectName(QString::fromUtf8("pourPressSetLEV"));
        pourPressSetLEV->setGeometry(QRect(285, 48, 75, 40));
        pourPressSetLEV->setStyleSheet(QString::fromUtf8("#pourPressSetLEV{\n"
"background: transparent;\n"
"color:rgb(255,255,255);\n"
"font-family:simhei;\n"
"font:24px;\n"
"}\n"
"QLineEdit{\n"
"border-width:0;border-style:outset\n"
"}"));
        pourPressSetLEV->setAlignment(Qt::AlignCenter);
        pourPressLbV = new QLabel(pourWgV);
        pourPressLbV->setObjectName(QString::fromUtf8("pourPressLbV"));
        pourPressLbV->setGeometry(QRect(99, 40, 140, 60));
        pourPressLbV->setStyleSheet(QString::fromUtf8("#pourPressLbV\n"
"{\n"
"color: rgb(179, 228, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourPressLbV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pourFloRLbV = new QLabel(pourWgV);
        pourFloRLbV->setObjectName(QString::fromUtf8("pourFloRLbV"));
        pourFloRLbV->setGeometry(QRect(330, 419, 70, 25));
        pourFloRLbV->setStyleSheet(QString::fromUtf8("#pourFloRLbV\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        pourFloRLbV->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/pourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/images/pourOn_IconV.png"), QSize(), QIcon::Normal, QIcon::On);
        icon9.addFile(QString::fromUtf8(":/images/pourDis_Icon.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/images/pourDis_Icon.png"), QSize(), QIcon::Disabled, QIcon::On);
        VmonTabWidget->addTab(pourTabV, icon9, QString());
        batWidget = new BatteryLogManage(centralWidget);
        batWidget->setObjectName(QString::fromUtf8("batWidget"));
        batWidget->setGeometry(QRect(1160, 12, 35, 17));
        batSocLabel = new QLabel(centralWidget);
        batSocLabel->setObjectName(QString::fromUtf8("batSocLabel"));
        batSocLabel->setGeometry(QRect(1116, 6, 38, 18));
        batSocLabel->setStyleSheet(QString::fromUtf8("#batSocLabel\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:16px;\n"
"}"));
        batSocLabel->setAlignment(Qt::AlignCenter);
        chgIconLb = new QLabel(centralWidget);
        chgIconLb->setObjectName(QString::fromUtf8("chgIconLb"));
        chgIconLb->setGeometry(QRect(1170, 5, 13, 7));
        chgIconLb->setStyleSheet(QString::fromUtf8("#chgIconLb{\n"
"image: url(:/images/chgLog_Icon.png);\n"
"}"));
        acLinkLog = new QWidget(centralWidget);
        acLinkLog->setObjectName(QString::fromUtf8("acLinkLog"));
        acLinkLog->setGeometry(QRect(1203, 12, 36, 17));
        batLinkLog = new QWidget(centralWidget);
        batLinkLog->setObjectName(QString::fromUtf8("batLinkLog"));
        batLinkLog->setGeometry(QRect(1090, 6, 17, 17));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        monTabWidget->setCurrentIndex(0);
        VmonTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        wtrRomOnOffBt->setText(QString());
        showTmpLabel->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        setWatTmpLE->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        sysTmtLabel->setText(QString());
        strTmtLabel->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preFlowLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preTmpLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        prePressLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preSpeedSetLE->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preSpeedLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preFloRLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        monTabWidget->setTabText(monTabWidget->indexOf(prePourTab), QString());
        pourFlowLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourTmpLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourSpeedLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourPressSetLE->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourPressLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourFloRLb->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        monTabWidget->setTabText(monTabWidget->indexOf(pourTab), QString());
        almShowLb->setText(QString());
        almShowBtn->setText(QString());
        almOnOffBtn->setText(QString());
        sysSetBtn->setText(QString());
        unLockScreenBtn->setText(QString());
        BPStrBtn->setText(QString());
        BPStrBtnV->setText(QString());
        preFlowLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preTmpLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        prePressLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preSpeedSetLEV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preSpeedLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        preFloRLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        VmonTabWidget->setTabText(VmonTabWidget->indexOf(prePourTabV), QString());
        pourFlowLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourTmpLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourSpeedLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourPressSetLEV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourPressLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pourFloRLbV->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        VmonTabWidget->setTabText(VmonTabWidget->indexOf(pourTabV), QString());
        batSocLabel->setText(QString());
        chgIconLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
