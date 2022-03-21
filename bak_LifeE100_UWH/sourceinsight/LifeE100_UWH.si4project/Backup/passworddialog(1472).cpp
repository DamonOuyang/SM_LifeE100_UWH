#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent,bool bModPwdFlag) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}



void PasswordDialog::on_pwdCancel_clicked()
{

}

void PasswordDialog::on_pwdOk_clicked()
{

}

void PasswordDialog::on_pwdEdit_clicked()
{

}
