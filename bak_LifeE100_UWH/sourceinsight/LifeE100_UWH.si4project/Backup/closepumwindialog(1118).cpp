#include "unlockinfodialog.h"
#include "ui_unlockinfodialog.h"

unlockInfoDialog::unlockInfoDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::unlockInfoDialog)
{
    ui->setupUi(this);
	
    //connect(this,SIGNAL(sendUnlockCanlce(void)),parent,SLOT(setUnlockCanlce(void)));//
    connect(this,SIGNAL(sendUnlockOk(void)),parent,SLOT(setUnlockOk(void)));//
}

unlockInfoDialog::~unlockInfoDialog()
{
    delete ui;
}

void unlockInfoDialog::on_cancelButton_clicked()
{
    //emit sendUnlockCanlce();
    this->close();
}

void unlockInfoDialog::on_unlockButton_clicked()
{
    emit sendUnlockOk();
    this->close();
}

