#include "cshowinfoframe.h"
#include "ui_cshowinfoframe.h"

CShowInfoFrame::CShowInfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CShowInfoFrame)
{
    ui->setupUi(this);
}

CShowInfoFrame::~CShowInfoFrame()
{
    delete ui;
}
