#include "configpourframe.h"
#include "ui_configpourframe.h"

configPourFrame::configPourFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configPourFrame)
{
    ui->setupUi(this);
}

configPourFrame::~configPourFrame()
{
    delete ui;
}
