#include "configveiframe.h"
#include "ui_configveiframe.h"

configVeiFrame::configVeiFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configVeiFrame)
{
    ui->setupUi(this);
}

configVeiFrame::~configVeiFrame()
{
    delete ui;
}
