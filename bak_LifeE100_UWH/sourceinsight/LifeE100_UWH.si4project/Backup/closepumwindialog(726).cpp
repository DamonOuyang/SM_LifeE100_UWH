#include "closepumwindialog.h"
#include "ui_closepumwindialog.h"

ClosePumWinDialog::ClosePumWinDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::closePumWinDialog)
{
    ui->setupUi(this);
	connect(this,SIGNAL(sendCloseState(bool)),parent,SLOT(closePumWinBack(void)));//
}

ClosePumWinDialog::~ClosePumWinDialog()
{
    delete ui;
}

void ClosePumWinDialog::on_cancelButton_clicked()
{
    emit sendCloseState(false);
    this->close();
}

void ClosePumWinDialog::on_unlockButton_clicked()
{
    emit sendCloseState(true);
    this->close();
}

