#include "unlockinfodialog.h"
#include "ui_unlockinfodialog.h"

unlockInfoDialog::unlockInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::unlockInfoDialog)
{
    ui->setupUi(this);
}

unlockInfoDialog::~unlockInfoDialog()
{
    delete ui;
}

void unlockInfoDialog::on_cancelButton_clicked()
{

}

void unlockInfoDialog::on_unlockButton_clicked()
{

}
