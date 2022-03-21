#include "loadheaddialog.h"
#include "ui_loadheaddialog.h"

LoadHeadDialog::LoadHeadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadHeadDialog)
{
    ui->setupUi(this);
}

LoadHeadDialog::~LoadHeadDialog()
{
    delete ui;
}

void LoadHeadDialog::on_loadLastBut_clicked()
{

}

void LoadHeadDialog::on_loadNextBut_clicked()
{

}
