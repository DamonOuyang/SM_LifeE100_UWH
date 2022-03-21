#include "upchosedevdialog.h"
#include "ui_upchosedevdialog.h"

UpChoseDevDialog::UpChoseDevDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpChoseDevDialog)
{
    ui->setupUi(this);
}

UpChoseDevDialog::~UpChoseDevDialog()
{
    delete ui;
}

void UpChoseDevDialog::on_pushButton1_clicked(bool checked)
{

}

void UpChoseDevDialog::on_pushButton2_clicked(bool checked)
{

}

void UpChoseDevDialog::on_pushButton3_clicked(bool checked)
{

}

void UpChoseDevDialog::on_pushButton4_clicked(bool checked)
{

}

void UpChoseDevDialog::on_upCancel_clicked()
{

}

void UpChoseDevDialog::on_upOk_clicked()
{

}
