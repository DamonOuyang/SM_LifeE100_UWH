#include "closepumwindialog.h"
#include "ui_closepumwindialog.h"

ClosePumWinDialog::ClosePumWinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClosePumWinDialog)
{
    ui->setupUi(this);
}

ClosePumWinDialog::~ClosePumWinDialog()
{
    delete ui;
}

void ClosePumWinDialog::on_cancelPumButton_clicked()
{

}

void ClosePumWinDialog::on_closePumButton_clicked()
{

}
