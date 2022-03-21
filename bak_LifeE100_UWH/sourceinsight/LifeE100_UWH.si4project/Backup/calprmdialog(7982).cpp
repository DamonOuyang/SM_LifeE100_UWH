#include "calprmdialog.h"
#include "ui_calprmdialog.h"

calPrmDialog::calPrmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calPrmDialog)
{
    ui->setupUi(this);
}

calPrmDialog::~calPrmDialog()
{
    delete ui;
}

void calPrmDialog::on_closeButton_clicked()
{

}
