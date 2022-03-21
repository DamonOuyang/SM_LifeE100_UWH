#include "cconfigpanel.h"
#include "ui_cconfigpanel.h"

CConfigPanel::CConfigPanel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CConfigPanel)
{
    ui->setupUi(this);
}

CConfigPanel::~CConfigPanel()
{
    delete ui;
}
