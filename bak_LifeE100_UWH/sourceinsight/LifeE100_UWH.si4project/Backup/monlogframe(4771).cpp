#include "monlogframe.h"
#include "ui_monlogframe.h"

MonLogFrame::MonLogFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MonLogFrame)
{
    ui->setupUi(this);
}

MonLogFrame::~MonLogFrame()
{
    delete ui;
}
