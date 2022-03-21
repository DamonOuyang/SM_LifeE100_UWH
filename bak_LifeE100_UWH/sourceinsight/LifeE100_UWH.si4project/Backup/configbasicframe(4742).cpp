#include "configbasicframe.h"
#include "ui_configbasicframe.h"

ConfigBasicFrame::ConfigBasicFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConfigBasicFrame)
{
    ui->setupUi(this);
}

ConfigBasicFrame::~ConfigBasicFrame()
{
    delete ui;
}
