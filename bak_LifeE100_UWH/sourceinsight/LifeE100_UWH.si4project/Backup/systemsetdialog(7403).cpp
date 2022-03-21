#include "systemsetdialog.h"
#include "ui_systemsetdialog.h"
#include "MyQProxyStyle.h"

SystemSetDialog::SystemSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemSetDialog)
{
    ui->setupUi(this);

    ui->tabWidget_2->setTabPosition(QTabWidget::West);
    ui->tabWidget_2->tabBar()->setStyle(new MyQProxyStyle);
}

SystemSetDialog::~SystemSetDialog()
{
    delete ui;
}
