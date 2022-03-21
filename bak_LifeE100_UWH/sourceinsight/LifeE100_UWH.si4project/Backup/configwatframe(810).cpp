#include "configwatframe.h"
#include "ui_configwatframe.h"

configWatFrame::configWatFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configWatFrame)
{
    ui->setupUi(this);
}

configWatFrame::~configWatFrame()
{
    delete ui;
}
