#include "systemsetdialog.h"
#include "ui_systemsetdialog.h"
#include "MyQProxyStyle.h"
#include <QTabBar>

SystemSetDialog::SystemSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemSetDialog)
{
    ui->setupUi(this);

    //ui->tabWidget_2->setTabPosition(QTabWidget::West);
    ui->tabWidget_2->tabBar()->setStyle(new MyQProxyStyle);
    ui->tabWidget->setStyleSheet(QLatin1String("\n"
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
"}"));
}

SystemSetDialog::~SystemSetDialog()
{
    delete ui;
}
