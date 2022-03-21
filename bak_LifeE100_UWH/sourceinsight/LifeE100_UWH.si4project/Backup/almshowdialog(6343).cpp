#include "almshowdialog.h"
#include "ui_almshowdialog.h"

AlmShowDialog::AlmShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlmShowDialog)
{
    ui->setupUi(this);
}

AlmShowDialog::~AlmShowDialog()
{
    delete ui;
}
