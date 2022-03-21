#include "messageboxdialog.h"
#include "ui_messageboxdialog.h"

MessageBoxDialog::MessageBoxDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageBoxDialog)
{
    ui->setupUi(this);
}

MessageBoxDialog::~MessageBoxDialog()
{
    delete ui;
}

void MessageBoxDialog::on_cancelButton_clicked()
{

}

void MessageBoxDialog::on_okButton_clicked()
{

}

void MessageBoxDialog::on_okButton1_clicked()
{

}
