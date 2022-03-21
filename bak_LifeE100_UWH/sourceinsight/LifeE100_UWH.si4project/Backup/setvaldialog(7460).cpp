﻿#include "setvaldialog.h"
#include "ui_setvaldialog.h"
#include "includes.h"
#include"QDebug"

SetValDialog::SetValDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetValDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    m_unLimitVal = 6000;
	m_unStep = 1;
	m_lFactScale = 1;
	m_lDotNum = 0;
	m_unTmtStep = 1;
	
	ui->lineEdit->setEnabled(false);


    m_reduceTimer = new QTimer();
    connect(m_reduceTimer, SIGNAL(timeout()), this, SLOT(OnReduceTimer(void)));

    m_addValTimer = new QTimer();
    connect(m_addValTimer, SIGNAL(timeout()), this, SLOT(OnAddButtonTimer(void)));

    connect(this,SIGNAL(sendSetNumber(QString)),parent,SLOT(setValString(QString)));//
    connect(this,SIGNAL(sendSetCanlce(void)),parent,SLOT(setValCanlce(void)));//
}

SetValDialog::~SetValDialog()
{
    //qDebug()<<"~SetValDialog";
    if(m_reduceTimer)
    {
        //qDebug()<<"m_reduceTimer == true";
        m_reduceTimer->stop();
		delete m_reduceTimer;
		m_reduceTimer = NULL;

    }
    if(m_addValTimer)
    {
        //qDebug()<<"m_addValTimer == true";
        m_addValTimer->stop();
		delete m_addValTimer;
		m_addValTimer = NULL;
    }

    delete ui;
}
//确认
void SetValDialog::on_okButton_clicked()
{
    emit sendSetNumber(ui->lineEdit->text());
    this->close();
}

void SetValDialog::on_cancelButton_clicked()
{
    emit sendSetCanlce();
    this->close();
}

void SetValDialog::SetDefaultVal(QString strDefVal)
{
    ui->lineEdit->setText(strDefVal);
    //qDebug("reduce strDefVal : %d ",strDefVal.toFloat()*10);
    //qDebug("reduce lineEdit : %d ",ui->lineEdit->text().toFloat()*10);
}


void SetValDialog::SetValLimit(UINT32 unLimitVal, UINT8 unStep, int lFactScale,int lDotNum,UINT8 unTmtStep)
{
    m_unLimitVal = unLimitVal;
	m_unStep = unStep;
	m_lFactScale = lFactScale;
	m_lDotNum = lDotNum;
	m_unTmtStep = unTmtStep;

	if(m_unTmtStep > 20)
	{
	    m_unTmtStep = 20;
	}
}


void SetValDialog::on_reduceButton_pressed()
{
    //qDebug()<<"on_reduceButton_pressed";
    m_reduceTimer->start(800);

    int unLine = 1;
	if(m_lFactScale >= 10)
	{
    	unLine = ui->lineEdit->text().toFloat()*m_lFactScale;
	}
	else
	{
	    unLine = ui->lineEdit->text().toInt();
	}
    //qDebug()<<"on_reduceButton_pressed-2";
    if(unLine >= m_unStep)
    {
        unLine = unLine - m_unStep;
    }
    else
    {
        unLine = 0;
    }
    ui->lineEdit->setText(ValueToString(unLine,m_lFactScale,m_lDotNum));


    //qDebug("reduce lineEdit : %d ",unLine);
}

void SetValDialog::on_reduceButton_released()
{
    //qDebug()<<"on_reduceButton_released";
    m_reduceTimer->stop();
}

void SetValDialog::OnReduceTimer()
{
    //qDebug()<<"on_reduce_timer";

    m_reduceTimer->start(100/m_unTmtStep);
 

    int unLine = 1;
	UINT8 unStep;
	if(m_lFactScale >= 10)
	{
    	unLine = ui->lineEdit->text().toFloat()*m_lFactScale;
	}
	else
	{
	    unLine = ui->lineEdit->text().toInt();
	}

    unStep = m_unStep*m_unTmtStep;
    if(unLine >= unStep)
    {
        unLine = unLine - unStep;
    }
    else
    {
        unLine = 0;
    }
    ui->lineEdit->setText(ValueToString(unLine,m_lFactScale,m_lDotNum));
    //qDebug("reduce lineEdit : %d ",unLine);
}

void SetValDialog::on_addButton_pressed()
{
    int unLine = 1;
	if(m_lFactScale >= 10)
	{
    	unLine = ui->lineEdit->text().toFloat()*m_lFactScale;
	}
	else
	{
	    unLine = ui->lineEdit->text().toInt();
	}

    if(unLine < m_unLimitVal)
    {
        unLine = unLine + m_unStep;
    }
    else
    {
        unLine = m_unLimitVal;
    }
    ui->lineEdit->setText(ValueToString(unLine,m_lFactScale,m_lDotNum));
    m_addValTimer->start(800);
    //qDebug("add lineEdit : %d ",unLine);
    //qDebug()<<"on_addButton_pressed";
}

void SetValDialog::on_addButton_released()
{
    m_addValTimer->stop();
    //qDebug()<<"on_addButton_released";
}

void SetValDialog::OnAddButtonTimer()
{
    //qDebug()<<"on_addButton_timer";
    m_addValTimer->start(100/m_unTmtStep);

    int unLine = 1;
	UINT8 unStep;
	if(m_lFactScale >= 10)
	{
    	unLine = ui->lineEdit->text().toFloat()*m_lFactScale;
	}
	else
	{
	    unLine = ui->lineEdit->text().toInt();
	}

    unStep = m_unStep*m_unTmtStep;
    if(unLine < m_unLimitVal)
    {
        unLine = unLine + unStep;
    }
    else
    {
        unLine = m_unLimitVal;
    }
    ui->lineEdit->setText(ValueToString(unLine,m_lFactScale,m_lDotNum));

    //qDebug("add lineEdit : %d ",unLine);
}
