#include "systemsetdialog.h"
#include "ui_systemsetdialog.h"
#include "MyQProxyStyle.h"

SystemSetDialog::SystemSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemSetDialog)
{
    ui->setupUi(this);

    MyQProxyStyle *myQProxyStyle = new MyQProxyStyle();
	myQProxyStyle->SetTabWidth(160);
	myQProxyStyle->SetTabHeigth(65);
	myQProxyStyle->SetFontB(18);
    //ui->tabWidget_2->setTabPosition(QTabWidget::West);
    ui->tabWidget->tabBar()->setStyle(myQProxyStyle);
    MyQProxyStyle *myQProxyStyle2 = new MyQProxyStyle();
    myQProxyStyle2->SetTabWidth(125);
    myQProxyStyle2->SetTabHeigth(65);
    myQProxyStyle2->SetFontB(12);
    ui->tabWidget_2->tabBar()->setStyle(myQProxyStyle2);
	/*
    ui->tabWidget->setStyleSheet(("\n"
"QTabBar::tab \n"
"{	min-width:160px;min-height:65px;\n"
"    color: rgb(247, 176, 0);\n"
"    font-family:simhei;\n"
"}\n"
"QTabBar::tab:selected\n"
"{   \n"
"	background-color: rgb(64, 64, 71);\n"
"	color: rgb(247, 176, 0);\n"
"	padding:0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected \n"
"{\n"
"   background-color: rgb(54, 54, 61);\n"
"	color: rgb(255, 255, 255);\n"
"	padding:0px;\n"
"}"));*/
}

SystemSetDialog::~SystemSetDialog()
{
    delete ui;
}
