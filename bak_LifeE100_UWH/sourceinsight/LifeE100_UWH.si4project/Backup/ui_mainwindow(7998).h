/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <batterylogmanage.h>
#include "QRoundProgressBar.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *waterTmpWg;
    QPushButton *wtrTmpSetBt;
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
    QWidget *pourTab;
    QWidget *pourWg;
    QLabel *pourFlowLb;
    QLabel *pourTmpLb;
    QLabel *pourSpeedLb;
    QLineEdit *pourPressSetLE;
    QLabel *pourPressLb;
    QWidget *alarmWg;
    QLabel *almShowLb;
    QPushButton *almOnOffBtn;
    QPushButton *sysSetBtn;
    QPushButton *almShowBtn;
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
    QWidget *pourTabV;
    QWidget *pourWgV;
    QLabel *pourFlowLbV;
    QLabel *pourTmpLbV;
    QLabel *pourSpeedLbV;
    QLineEdit *pourPressSetLEV;
    QLabel *pourPressLbV;
    QPushButton *calPrmButton;
    BatteryLogManage *widget;
    QPushButton *sysSetBackBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 800);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        waterTmpWg = new QWidget(centralWidget);
        waterTmpWg->setObjectName(QStringLiteral("waterTmpWg"));
        waterTmpWg->setGeometry(QRect(40, 180, 300, 245));
        waterTmpWg->setStyleSheet(QLatin1String("#waterTmpWg{\n"
"image: url(:/images/waterRoomTmp_Bg.png);\n"
"}"));
        wtrTmpSetBt = new QPushButton(waterTmpWg);
        wtrTmpSetBt->setObjectName(QStringLiteral("wtrTmpSetBt"));
        wtrTmpSetBt->setGeometry(QRect(170, 165, 101, 40));
        wtrTmpSetBt->setLayoutDirection(Qt::LeftToRight);
        wtrTmpSetBt->setStyleSheet(QLatin1String("#wtrTmpSetBt\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"font-family:simhei;\n"
"color: rgb(255,255,255);\n"
"font:20px;\n"
"}\n"
"\n"
"#wtrTmpSetBt:focus{outline: none;\n"
"}"));
        wtrTmpSetBt->setIconSize(QSize(135, 166));
        wtrTmpSetBt->setCheckable(false);
        wtrTmpSetBt->setChecked(false);
        wtrRomOnOffBt = new QPushButton(waterTmpWg);
        wtrRomOnOffBt->setObjectName(QStringLiteral("wtrRomOnOffBt"));
        wtrRomOnOffBt->setGeometry(QRect(187, 28, 66, 66));
        wtrRomOnOffBt->setStyleSheet(QLatin1String("#wtrRomOnOffBt\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#wtrRomOnOffBt:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/tmpOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/tmpOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        wtrRomOnOffBt->setIcon(icon);
        wtrRomOnOffBt->setIconSize(QSize(135, 66));
        wtrRomOnOffBt->setCheckable(true);
        wtrRomOnOffBt->setFlat(true);
        showTmpLabel = new QLabel(waterTmpWg);
        showTmpLabel->setObjectName(QStringLiteral("showTmpLabel"));
        showTmpLabel->setGeometry(QRect(0, 166, 170, 36));
        showTmpLabel->setStyleSheet(QLatin1String("#showTmpLabel\n"
"{\n"
"font-family:simhei;\n"
"color: rgb(247, 176, 0);\n"
"font:36px;\n"
"}"));
        showTmpLabel->setAlignment(Qt::AlignCenter);
        setWatTmpLE = new QLineEdit(waterTmpWg);
        setWatTmpLE->setObjectName(QStringLiteral("setWatTmpLE"));
        setWatTmpLE->setGeometry(QRect(170, 172, 75, 25));
        setWatTmpLE->setCursor(QCursor(Qt::ArrowCursor));
        setWatTmpLE->setStyleSheet(QLatin1String("#setWatTmpLE{\n"
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
        sysTmtLabel->setObjectName(QStringLiteral("sysTmtLabel"));
        sysTmtLabel->setGeometry(QRect(40, 8, 300, 25));
        sysTmtLabel->setStyleSheet(QLatin1String("#sysTmtLabel\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        waterGageWg = new QWidget(centralWidget);
        waterGageWg->setObjectName(QStringLiteral("waterGageWg"));
        waterGageWg->setGeometry(QRect(40, 445, 300, 100));
        waterGageWg->setStyleSheet(QLatin1String("#waterGageWg{\n"
"image: url(:/images/waterRoomGage_Bg.png);\n"
"}"));
        WatRoundBar = new QRoundProgressBar(waterGageWg);
        WatRoundBar->setObjectName(QStringLiteral("WatRoundBar"));
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
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        strTmtWg = new QWidget(centralWidget);
        strTmtWg->setObjectName(QStringLiteral("strTmtWg"));
        strTmtWg->setGeometry(QRect(40, 60, 300, 100));
        strTmtWg->setStyleSheet(QLatin1String("#strTmtWg{\n"
"image: url(:/images/strTmt_Bg.png);\n"
"}"));
        strTmtLabel = new QLabel(strTmtWg);
        strTmtLabel->setObjectName(QStringLiteral("strTmtLabel"));
        strTmtLabel->setGeometry(QRect(0, 53, 300, 25));
        strTmtLabel->setStyleSheet(QLatin1String("#strTmtLabel\n"
"{\n"
"   font-family:simhei;\n"
"   color: rgb(255,255,255);\n"
"   font:24px;\n"
"}"));
        strTmtLabel->setAlignment(Qt::AlignCenter);
        monTabWidget = new QTabWidget(centralWidget);
        monTabWidget->setObjectName(QStringLiteral("monTabWidget"));
        monTabWidget->setGeometry(QRect(360, 180, 430, 590));
        monTabWidget->setStyleSheet(QLatin1String("QTabBar::tab \n"
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
        prePourTab->setObjectName(QStringLiteral("prePourTab"));
        prePourWg = new QWidget(prePourTab);
        prePourWg->setObjectName(QStringLiteral("prePourWg"));
        prePourWg->setGeometry(QRect(0, 0, 430, 500));
        prePourWg->setStyleSheet(QLatin1String("#prePourWg{\n"
"	background-image: url(:/images/monDataPrePour_Bg.png);\n"
"}"));
        preFlowLb = new QLabel(prePourWg);
        preFlowLb->setObjectName(QStringLiteral("preFlowLb"));
        preFlowLb->setGeometry(QRect(120, 170, 140, 60));
        preFlowLb->setStyleSheet(QLatin1String("#preFlowLb\n"
"{\n"
"color: rgb(255, 153, 199);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preFlowLb->setAlignment(Qt::AlignCenter);
        preTmpLb = new QLabel(prePourWg);
        preTmpLb->setObjectName(QStringLiteral("preTmpLb"));
        preTmpLb->setGeometry(QRect(120, 295, 140, 60));
        preTmpLb->setStyleSheet(QLatin1String("#preTmpLb\n"
"{\n"
"color: rgb(255, 153, 199);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preTmpLb->setAlignment(Qt::AlignCenter);
        prePressLb = new QLabel(prePourWg);
        prePressLb->setObjectName(QStringLiteral("prePressLb"));
        prePressLb->setGeometry(QRect(110, 420, 70, 30));
        prePressLb->setStyleSheet(QLatin1String("#prePressLb\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(225,230,236);\n"
"font:26px;\n"
"}"));
        prePressLb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        preSpeedSetLE = new QLineEdit(prePourWg);
        preSpeedSetLE->setObjectName(QStringLiteral("preSpeedSetLE"));
        preSpeedSetLE->setGeometry(QRect(285, 48, 75, 40));
        preSpeedSetLE->setStyleSheet(QLatin1String("#preSpeedSetLE{\n"
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
        preSpeedLb->setObjectName(QStringLiteral("preSpeedLb"));
        preSpeedLb->setGeometry(QRect(120, 40, 140, 60));
        preSpeedLb->setStyleSheet(QLatin1String("#preSpeedLb\n"
"{\n"
"color: rgb(255, 153, 199);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preSpeedLb->setAlignment(Qt::AlignCenter);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/prePourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/images/prePourOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        monTabWidget->addTab(prePourTab, icon1, QString());
        pourTab = new QWidget();
        pourTab->setObjectName(QStringLiteral("pourTab"));
        pourTab->setMaximumSize(QSize(814, 562));
        pourTab->setSizeIncrement(QSize(814, 562));
        pourWg = new QWidget(pourTab);
        pourWg->setObjectName(QStringLiteral("pourWg"));
        pourWg->setGeometry(QRect(0, 0, 430, 500));
        pourWg->setStyleSheet(QLatin1String("#pourWg{\n"
"background-image: url(:/images/monDataPour_Bg.png);\n"
"\n"
"}"));
        pourFlowLb = new QLabel(pourWg);
        pourFlowLb->setObjectName(QStringLiteral("pourFlowLb"));
        pourFlowLb->setGeometry(QRect(120, 170, 140, 60));
        pourFlowLb->setStyleSheet(QLatin1String("#pourFlowLb\n"
"{\n"
"color: rgb(255, 153, 199);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourFlowLb->setAlignment(Qt::AlignCenter);
        pourTmpLb = new QLabel(pourWg);
        pourTmpLb->setObjectName(QStringLiteral("pourTmpLb"));
        pourTmpLb->setGeometry(QRect(120, 295, 140, 60));
        pourTmpLb->setStyleSheet(QLatin1String("#pourTmpLb\n"
"{\n"
"color: rgb(255, 153, 199);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourTmpLb->setAlignment(Qt::AlignCenter);
        pourSpeedLb = new QLabel(pourWg);
        pourSpeedLb->setObjectName(QStringLiteral("pourSpeedLb"));
        pourSpeedLb->setGeometry(QRect(115, 420, 100, 25));
        pourSpeedLb->setStyleSheet(QLatin1String("#pourSpeedLb\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(225,230,236);\n"
"font:24px;\n"
"}"));
        pourSpeedLb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pourPressSetLE = new QLineEdit(pourWg);
        pourPressSetLE->setObjectName(QStringLiteral("pourPressSetLE"));
        pourPressSetLE->setGeometry(QRect(285, 48, 75, 40));
        pourPressSetLE->setStyleSheet(QLatin1String("#pourPressSetLE{\n"
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
        pourPressLb->setObjectName(QStringLiteral("pourPressLb"));
        pourPressLb->setGeometry(QRect(120, 40, 140, 60));
        pourPressLb->setStyleSheet(QLatin1String("#pourPressLb\n"
"{\n"
"color: rgb(255, 153, 199);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourPressLb->setAlignment(Qt::AlignCenter);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/pourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":/images/pourOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        monTabWidget->addTab(pourTab, icon2, QString());
        alarmWg = new QWidget(centralWidget);
        alarmWg->setObjectName(QStringLiteral("alarmWg"));
        alarmWg->setGeometry(QRect(40, 565, 300, 115));
        alarmWg->setStyleSheet(QLatin1String("#alarmWg\n"
"{\n"
"	border: 0px;\n"
"	top:0px;\n"
"	left: 0px;\n"
"}"));
        almShowLb = new QLabel(alarmWg);
        almShowLb->setObjectName(QStringLiteral("almShowLb"));
        almShowLb->setGeometry(QRect(0, 0, 300, 115));
        almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
"background-image: url(:/images/alarm.png);\n"
"   font-family:simhei;\n"
"   font:bold;\n"
"   font:26px;\n"
"}"));
        almOnOffBtn = new QPushButton(centralWidget);
        almOnOffBtn->setObjectName(QStringLiteral("almOnOffBtn"));
        almOnOffBtn->setGeometry(QRect(40, 700, 80, 60));
        almOnOffBtn->setStyleSheet(QLatin1String("#almOnOffBtn{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#almOnOffBtn:focus{outline: none;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/alarmOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QStringLiteral(":/images/alarmOn_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        almOnOffBtn->setIcon(icon3);
        almOnOffBtn->setIconSize(QSize(86, 60));
        almOnOffBtn->setCheckable(true);
        almOnOffBtn->setFlat(true);
        sysSetBtn = new QPushButton(centralWidget);
        sysSetBtn->setObjectName(QStringLiteral("sysSetBtn"));
        sysSetBtn->setGeometry(QRect(254, 700, 86, 60));
        sysSetBtn->setStyleSheet(QLatin1String("\n"
"#sysSetBtn{\n"
"background: transparent;\n"
"	background-image: url(:/images/sysSet_Icon.png);\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#sysSetBtn:pressed{\n"
"background-image: url(:/images/sysSet_Icon.png);\n"
"}\n"
"#sysSetBtn:focus{outline: none;\n"
"}"));
        sysSetBtn->setIconSize(QSize(86, 60));
        sysSetBtn->setFlat(true);
        almShowBtn = new QPushButton(centralWidget);
        almShowBtn->setObjectName(QStringLiteral("almShowBtn"));
        almShowBtn->setGeometry(QRect(40, 565, 300, 115));
        almShowBtn->setStyleSheet(QLatin1String("#almShowBtn{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px\n"
"}\n"
"#almShowBtn:focus{outline: none;\n"
"}"));
        almShowBtn->setCheckable(false);
        almShowBtn->setFlat(false);
        unLockScreenBtn = new QPushButton(centralWidget);
        unLockScreenBtn->setObjectName(QStringLiteral("unLockScreenBtn"));
        unLockScreenBtn->setGeometry(QRect(147, 700, 86, 60));
        unLockScreenBtn->setStyleSheet(QLatin1String("#unLockScreenBtn{\n"
"background: transparent;\n"
"	background-image: url(:/images/unLocking_Icon.png);\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"#unLockScreenBtn:pressed{\n"
"background-image: url(:/images/unLocking_Icon.png);\n"
"}\n"
"#unLockScreenBtn:focus{outline: none;\n"
"}"));
        unLockScreenBtn->setIconSize(QSize(86, 60));
        unLockScreenBtn->setFlat(true);
        arteryHeadWidget = new QWidget(centralWidget);
        arteryHeadWidget->setObjectName(QStringLiteral("arteryHeadWidget"));
        arteryHeadWidget->setGeometry(QRect(360, 60, 430, 120));
        arteryHeadWidget->setStyleSheet(QLatin1String("#arteryHeadWidget{\n"
"background-image: url(:/images/arteryHead_Bg.png);\n"
"}"));
        BPStrBtn = new QPushButton(arteryHeadWidget);
        BPStrBtn->setObjectName(QStringLiteral("BPStrBtn"));
        BPStrBtn->setGeometry(QRect(302, 27, 66, 66));
        BPStrBtn->setStyleSheet(QLatin1String("#BPStrBtn\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#BPStrBtn:focus{outline: none;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/BP_Stop_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QStringLiteral(":/images/BP_Start_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        BPStrBtn->setIcon(icon4);
        BPStrBtn->setIconSize(QSize(139, 139));
        BPStrBtn->setCheckable(true);
        BPStrBtn->setFlat(true);
        veinHeadWidget = new QWidget(centralWidget);
        veinHeadWidget->setObjectName(QStringLiteral("veinHeadWidget"));
        veinHeadWidget->setGeometry(QRect(810, 60, 430, 120));
        veinHeadWidget->setStyleSheet(QLatin1String("#veinHeadWidget{\n"
"background-image: url(:/images/veinHead_Bg.png);\n"
"}"));
        BPStrBtnV = new QPushButton(veinHeadWidget);
        BPStrBtnV->setObjectName(QStringLiteral("BPStrBtnV"));
        BPStrBtnV->setGeometry(QRect(302, 27, 66, 66));
        BPStrBtnV->setStyleSheet(QLatin1String("#BPStrBtnV\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#BPStrBtnV:focus{outline: none;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/vBP_Stop_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QStringLiteral(":/images/vBP_Start_Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        BPStrBtnV->setIcon(icon5);
        BPStrBtnV->setIconSize(QSize(139, 139));
        BPStrBtnV->setCheckable(true);
        BPStrBtnV->setFlat(true);
        VmonTabWidget = new QTabWidget(centralWidget);
        VmonTabWidget->setObjectName(QStringLiteral("VmonTabWidget"));
        VmonTabWidget->setGeometry(QRect(810, 180, 430, 590));
        VmonTabWidget->setStyleSheet(QLatin1String("QTabBar::tab \n"
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
        prePourTabV->setObjectName(QStringLiteral("prePourTabV"));
        prePourWgV = new QWidget(prePourTabV);
        prePourWgV->setObjectName(QStringLiteral("prePourWgV"));
        prePourWgV->setGeometry(QRect(0, 0, 430, 500));
        prePourWgV->setStyleSheet(QLatin1String("#prePourWgV{\n"
"background-image: url(:/images/monDataPrePour_Bg.png);\n"
"\n"
"}"));
        preFlowLbV = new QLabel(prePourWgV);
        preFlowLbV->setObjectName(QStringLiteral("preFlowLbV"));
        preFlowLbV->setGeometry(QRect(120, 170, 140, 60));
        preFlowLbV->setStyleSheet(QLatin1String("#preFlowLbV\n"
"{\n"
"color: rgb(128, 192, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preFlowLbV->setAlignment(Qt::AlignCenter);
        preTmpLbV = new QLabel(prePourWgV);
        preTmpLbV->setObjectName(QStringLiteral("preTmpLbV"));
        preTmpLbV->setGeometry(QRect(120, 295, 140, 60));
        preTmpLbV->setStyleSheet(QLatin1String("#preTmpLbV\n"
"{\n"
"color: rgb(128, 192, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preTmpLbV->setAlignment(Qt::AlignCenter);
        prePressLbV = new QLabel(prePourWgV);
        prePressLbV->setObjectName(QStringLiteral("prePressLbV"));
        prePressLbV->setGeometry(QRect(115, 420, 100, 25));
        prePressLbV->setStyleSheet(QLatin1String("#prePressLbV\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        prePressLbV->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        preSpeedSetLEV = new QLineEdit(prePourWgV);
        preSpeedSetLEV->setObjectName(QStringLiteral("preSpeedSetLEV"));
        preSpeedSetLEV->setGeometry(QRect(285, 48, 75, 40));
        preSpeedSetLEV->setStyleSheet(QLatin1String("#preSpeedSetLEV{\n"
"background: transparent;\n"
"color:rgb(225,230,236);\n"
"font-family:simhei;\n"
"font:24px;\n"
"}\n"
"QLineEdit{\n"
"border-width:0;border-style:outset\n"
"}"));
        preSpeedSetLEV->setAlignment(Qt::AlignCenter);
        preSpeedLbV = new QLabel(prePourWgV);
        preSpeedLbV->setObjectName(QStringLiteral("preSpeedLbV"));
        preSpeedLbV->setGeometry(QRect(120, 40, 140, 60));
        preSpeedLbV->setStyleSheet(QLatin1String("#preSpeedLbV\n"
"{\n"
"color: rgb(128, 192, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        preSpeedLbV->setAlignment(Qt::AlignCenter);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/prePourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QStringLiteral(":/images/prePourOn_IconV.png"), QSize(), QIcon::Normal, QIcon::On);
        VmonTabWidget->addTab(prePourTabV, icon6, QString());
        pourTabV = new QWidget();
        pourTabV->setObjectName(QStringLiteral("pourTabV"));
        pourTabV->setMaximumSize(QSize(814, 562));
        pourTabV->setSizeIncrement(QSize(814, 562));
        pourWgV = new QWidget(pourTabV);
        pourWgV->setObjectName(QStringLiteral("pourWgV"));
        pourWgV->setGeometry(QRect(0, 0, 430, 500));
        pourWgV->setStyleSheet(QLatin1String("#pourWgV{\n"
"background-image: url(:/images/monDataPour_Bg.png);\n"
"\n"
"}"));
        pourFlowLbV = new QLabel(pourWgV);
        pourFlowLbV->setObjectName(QStringLiteral("pourFlowLbV"));
        pourFlowLbV->setGeometry(QRect(120, 170, 140, 60));
        pourFlowLbV->setStyleSheet(QLatin1String("#pourFlowLbV\n"
"{\n"
"color: rgb(128, 192, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourFlowLbV->setAlignment(Qt::AlignCenter);
        pourTmpLbV = new QLabel(pourWgV);
        pourTmpLbV->setObjectName(QStringLiteral("pourTmpLbV"));
        pourTmpLbV->setGeometry(QRect(120, 295, 140, 60));
        pourTmpLbV->setStyleSheet(QLatin1String("#pourTmpLbV\n"
"{\n"
"color: rgb(128, 192, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourTmpLbV->setAlignment(Qt::AlignCenter);
        pourSpeedLbV = new QLabel(pourWgV);
        pourSpeedLbV->setObjectName(QStringLiteral("pourSpeedLbV"));
        pourSpeedLbV->setGeometry(QRect(115, 420, 100, 25));
        pourSpeedLbV->setStyleSheet(QLatin1String("#pourSpeedLbV\n"
"{\n"
"font-family:simhei;\n"
"color:rgb(255,255,255);\n"
"font:24px;\n"
"}"));
        pourSpeedLbV->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pourPressSetLEV = new QLineEdit(pourWgV);
        pourPressSetLEV->setObjectName(QStringLiteral("pourPressSetLEV"));
        pourPressSetLEV->setGeometry(QRect(285, 48, 75, 40));
        pourPressSetLEV->setStyleSheet(QLatin1String("#pourPressSetLEV{\n"
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
        pourPressLbV->setObjectName(QStringLiteral("pourPressLbV"));
        pourPressLbV->setGeometry(QRect(120, 40, 140, 60));
        pourPressLbV->setStyleSheet(QLatin1String("#pourPressLbV\n"
"{\n"
"color: rgb(128, 192, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:48px;\n"
"}"));
        pourPressLbV->setAlignment(Qt::AlignCenter);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/pourOff_Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QStringLiteral(":/images/pourOn_IconV.png"), QSize(), QIcon::Normal, QIcon::On);
        VmonTabWidget->addTab(pourTabV, icon7, QString());
        calPrmButton = new QPushButton(centralWidget);
        calPrmButton->setObjectName(QStringLiteral("calPrmButton"));
        calPrmButton->setGeometry(QRect(560, 0, 191, 60));
        calPrmButton->setStyleSheet(QLatin1String("#calPrmButton{\n"
"background: transparent;\n"
"padding:-1px;\n"
"}"));
        widget = new BatteryLogManage(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(1160, 4, 80, 39));
        sysSetBackBtn = new QPushButton(widget);
        sysSetBackBtn->setObjectName(QStringLiteral("sysSetBackBtn"));
        sysSetBackBtn->setGeometry(QRect(-10, 0, 100, 40));
        sysSetBackBtn->setStyleSheet(QLatin1String("#sysSetBackBtn{\n"
"background: transparent;\n"
"	border-image: url(:/images/sysSetBack_Icon.png);\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        monTabWidget->setCurrentIndex(0);
        VmonTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        wtrTmpSetBt->setText(QString());
        wtrRomOnOffBt->setText(QString());
        showTmpLabel->setText(QApplication::translate("MainWindow", "0", 0));
        setWatTmpLE->setText(QApplication::translate("MainWindow", "0", 0));
        sysTmtLabel->setText(QString());
        strTmtLabel->setText(QApplication::translate("MainWindow", "0", 0));
        preFlowLb->setText(QApplication::translate("MainWindow", "0", 0));
        preTmpLb->setText(QApplication::translate("MainWindow", "0", 0));
        prePressLb->setText(QApplication::translate("MainWindow", "0", 0));
        preSpeedSetLE->setText(QApplication::translate("MainWindow", "0", 0));
        preSpeedLb->setText(QApplication::translate("MainWindow", "0", 0));
        monTabWidget->setTabText(monTabWidget->indexOf(prePourTab), QString());
        pourFlowLb->setText(QApplication::translate("MainWindow", "0", 0));
        pourTmpLb->setText(QApplication::translate("MainWindow", "0", 0));
        pourSpeedLb->setText(QApplication::translate("MainWindow", "0", 0));
        pourPressSetLE->setText(QApplication::translate("MainWindow", "0", 0));
        pourPressLb->setText(QApplication::translate("MainWindow", "0", 0));
        monTabWidget->setTabText(monTabWidget->indexOf(pourTab), QString());
        almShowLb->setText(QString());
        almOnOffBtn->setText(QString());
        sysSetBtn->setText(QString());
        almShowBtn->setText(QString());
        unLockScreenBtn->setText(QString());
        BPStrBtn->setText(QString());
        BPStrBtnV->setText(QString());
        preFlowLbV->setText(QApplication::translate("MainWindow", "0", 0));
        preTmpLbV->setText(QApplication::translate("MainWindow", "0", 0));
        prePressLbV->setText(QApplication::translate("MainWindow", "0", 0));
        preSpeedSetLEV->setText(QApplication::translate("MainWindow", "0", 0));
        preSpeedLbV->setText(QApplication::translate("MainWindow", "0", 0));
        VmonTabWidget->setTabText(VmonTabWidget->indexOf(prePourTabV), QString());
        pourFlowLbV->setText(QApplication::translate("MainWindow", "0", 0));
        pourTmpLbV->setText(QApplication::translate("MainWindow", "0", 0));
        pourSpeedLbV->setText(QApplication::translate("MainWindow", "0", 0));
        pourPressSetLEV->setText(QApplication::translate("MainWindow", "0", 0));
        pourPressLbV->setText(QApplication::translate("MainWindow", "0", 0));
        VmonTabWidget->setTabText(VmonTabWidget->indexOf(pourTabV), QString());
        calPrmButton->setText(QString());
        sysSetBackBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
