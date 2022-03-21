#include "onlogdialog.h"
#include "ui_onlogdialog.h"

OnLogDialog::OnLogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnLogDialog)
{
    ui->setupUi(this);
}

OnLogDialog::~OnLogDialog()
{
    delete ui;
}
