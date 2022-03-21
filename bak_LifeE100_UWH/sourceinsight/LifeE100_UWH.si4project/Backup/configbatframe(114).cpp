#include "configbatframe.h"
#include "ui_configbatframe.h"

configBatFrame::configBatFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configBatFrame)
{
    ui->setupUi(this);
}

configBatFrame::~configBatFrame()
{
    delete ui;
}
