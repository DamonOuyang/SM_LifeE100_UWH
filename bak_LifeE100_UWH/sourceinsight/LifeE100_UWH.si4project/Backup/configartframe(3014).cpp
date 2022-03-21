#include "configartframe.h"
#include "ui_configartframe.h"

configArtFrame::configArtFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configArtFrame)
{
    ui->setupUi(this);
}

configArtFrame::~configArtFrame()
{
    delete ui;
}
