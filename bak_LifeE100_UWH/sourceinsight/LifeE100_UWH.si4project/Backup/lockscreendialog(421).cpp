#include "lockscreendialog.h"
#include "ui_lockscreendialog.h"
#include <QtGui>
LockScreenDialog::LockScreenDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::LockScreenDialog)
{
    ui->setupUi(this);

    m_pUpdTimer = new QTimer(this);
    connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnFirtActiveTimer(void)));
    m_pUpdTimer->start(1000);
	m_pUpdTimer->stop();
	m_unPressedSec = 0;
}

LockScreenDialog::~LockScreenDialog()
{
    m_pUpdTimer->stop();
	delete m_pUpdTimer;
    delete ui;
}

void LockScreenDialog::OnFirtActiveTimer(void)
{
    if(m_unPressedSec < 1)
    {
    	m_unPressedSec++;
    }
	else
	{
		m_bPressedFlag = false;
		m_pUpdTimer->stop();
		m_unPressedSec = 0;
		this->hide();
	}
	//printf("LockScreenDialog::OnFirtActiveTimer m_unPressedSec====%u \r\n",m_unPressedSec);
}

void LockScreenDialog::on_LockScreenBtn_pressed()
{
    if(m_bPressedFlag == false)
    {
        m_bPressedFlag = true;
        m_pUpdTimer->start(1000);
        //printf("LockScreenDialog::on_pushButton_pressed ==== \r\n");
    }
}

void LockScreenDialog::on_LockScreenBtn_released()
{
    m_bPressedFlag = false;
    m_pUpdTimer->stop();
    m_unPressedSec = 0;
    //printf("LockScreenDialog::on_pushButton_released ------- \r\n");
}

void LockScreenDialog::on_boxButton_clicked()
{

}
