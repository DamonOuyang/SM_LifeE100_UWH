#include "normalwindowdialog.h"
#include "ui_normalwindowdialog.h"

NormalWindowDialog::NormalWindowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NormalWindowDialog)
{
    ui->setupUi(this);
}

NormalWindowDialog::~NormalWindowDialog()
{
    delete ui;
}

void NormalWindowDialog::on_lockBoxBackBt_clicked()
{
    this->close();
}
