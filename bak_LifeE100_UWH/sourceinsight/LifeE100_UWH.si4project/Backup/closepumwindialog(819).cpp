#include "closepumwindialog.h"
#include "ui_closepumwindialog.h"

ClosePumWinDialog::ClosePumWinDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::ClosePumWinDialog)
{
    ui->setupUi(this);
    //ui->closePumButton = ui->closePumInfoWidget->addButton(tr(""), QMessageBox::AcceptRole);
    //ui->cancelPumButton = ui->closePumInfoWidget->addButton(tr(""), QMessageBox::RejectRole);

    //connect(this,SIGNAL(sendCloseState(bool)),parent,SLOT(closePumWinBack(bool)));
}

ClosePumWinDialog::~ClosePumWinDialog()
{
    delete ui;
}

void ClosePumWinDialog::on_cancelPumButton_clicked()
{
    //emit sendCloseState(false);
    this->close();
}

void ClosePumWinDialog::on_closePumButton_clicked()
{
    //emit sendCloseState(true);
    this->close();
}
