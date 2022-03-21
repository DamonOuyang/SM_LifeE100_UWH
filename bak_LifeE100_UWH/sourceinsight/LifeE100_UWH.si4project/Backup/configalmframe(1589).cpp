#include "configalmframe.h"
#include "ui_configalmframe.h"

configAlmFrame::configAlmFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configAlmFrame)
{
    ui->setupUi(this);
}

configAlmFrame::~configAlmFrame()
{
    delete ui;
}
