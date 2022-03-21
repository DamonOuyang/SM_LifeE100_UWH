#include "onlogdialog.h"
#include "ui_onlogdialog.h"

#include <QMovie>

OnLogDialog::OnLogDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::OnLogDialog)
{
    ui->setupUi(this);
	ui->onLogWidget->setContentsMargins(0,0,0,0);
	ui->MovLabel->setContentsMargins(0,0,0,0);
	m_pMovie= new QMovie();
	m_pMovie->setFileName(":/images/LogOnGIF_L0.gif");
	ui->MovLabel->setMovie(m_pMovie);
	//m_pMovie->start();
}

OnLogDialog::~OnLogDialog()
{
    m_pMovie->stop();
	delete m_pMovie;
    delete ui;
}

void OnLogDialog::StopLogMovie(void)
{
	m_pMovie->stop();
}

void OnLogDialog::StartLogMovie(void)
{
	m_pMovie->start();
}