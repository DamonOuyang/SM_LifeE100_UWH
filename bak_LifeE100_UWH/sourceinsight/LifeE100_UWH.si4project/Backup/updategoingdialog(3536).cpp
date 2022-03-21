#include "updategoingdialog.h"
#include "ui_updategoingdialog.h"

UpdateGoingDialog::UpdateGoingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateGoingDialog)
{
    ui->setupUi(this);
}

UpdateGoingDialog::~UpdateGoingDialog()
{
    delete ui;
}
