#include "testdialog.h"
#include "ui_testdialog.h"

testDialog::testDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testDialog)
{
    ui->setupUi(this);
    ui->closePumButton = ui->closePumInfoWidget->addButton(tr(""), QMessageBox::AcceptRole);
    ui->cancelPumButton = ui->closePumInfoWidget->addButton(tr(""), QMessageBox::RejectRole);
}

testDialog::~testDialog()
{
    delete ui;
}
