﻿#include "configbatframe.h"
#include "ui_configbatframe.h"

configBatFrame::configBatFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configBatFrame)
{
    ui->setupUi(this);

    m_pDevID      = new QLineEdit(this);
	m_pDevID->setGeometry(QRect(155, 85, 100, 36));
    m_pDevEnabled = CreateComboBox(this);
	m_pDevEnabled->setGeometry(QRect(155, 155, 100, 36));
    m_pDevEnabled->addItem(tr("禁用"));
    m_pDevEnabled->addItem(tr("启用"));
    m_pDevID->setReadOnly(true);


    connect(ui->batOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->batCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    //connect(ui->batEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    ui->batEditBut->hide();
}

configBatFrame::~configBatFrame()
{
    delete ui;
}

void configBatFrame::OnClickOK(void)
{
	OperLogWatDev operLogWatDev;
	
	operLogWatDev.unType = OPER_LOG_TYPE_BAT;
	operLogWatDev.unSite = 0;
	GetDateTime(&operLogWatDev.dtCreate);
	
	operLogWatDev.unEnFlag[0] = g_devConfigInfo_Edt.batParam.unEnFlag;
	operLogWatDev.unEnFlag[1] = m_pDevEnabled->currentIndex();
	
	SaveOperLogData((const char*)&operLogWatDev, sizeof(OperLogBatDev));
	SaveOperLogInfo();
	
	OnUpdParams();
    g_pCfgDataUI->AddGrpData(CFG_BAT_PRM_ITEM,\
                            sizeof(g_devConfigInfo_Edt.batParam),\
                            (BYTE*)&g_devConfigInfo_Edt.batParam);
}
void configBatFrame::OnClickCancel(void)
{
	OnUpdParams();
}

void configBatFrame::OnUpdParams(void)
{
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.batParam.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.batParam.unDevID));
}

