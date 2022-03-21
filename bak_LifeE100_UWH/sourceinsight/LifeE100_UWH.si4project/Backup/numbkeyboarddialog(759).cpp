#include "numbkeyboarddialog.h"
#include "ui_numbkeyboarddialog.h"

NumbKeyboardDialog::NumbKeyboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumbKeyboardDialog)
{
    ui->setupUi(this);
}

NumbKeyboardDialog::~NumbKeyboardDialog()
{
    delete ui;
}
