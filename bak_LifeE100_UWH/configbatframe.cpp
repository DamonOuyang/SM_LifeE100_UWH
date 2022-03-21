#include "includes.h"
#include "CMonShareData.h"
#include "configbatframe.h"
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

	//电池信息
    m_pBatSoc  = new QLineEdit(this);
	m_pBatSoc->setGeometry(QRect(496, 85, 100, 36));
	m_pBatSoc->setReadOnly(true);
    m_pBatVol  = new QLineEdit(this);
	m_pBatVol->setGeometry(QRect(496, 155, 100, 36));
	m_pBatVol->setReadOnly(true);
    m_pBatCur  = new QLineEdit(this);
	m_pBatCur->setGeometry(QRect(496, 225, 100, 36));
	m_pBatCur->setReadOnly(true);
	m_pBatTmp   = new QLineEdit(this);
	m_pBatTmp->setGeometry(QRect(496, 295, 100, 36));
	m_pBatTmp->setReadOnly(true);
	m_pDisChgNum = new QLineEdit(this);
	m_pDisChgNum->setGeometry(QRect(496, 365, 100, 36));
	m_pDisChgNum->setReadOnly(true);

    connect(ui->batOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->batCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    //connect(ui->batEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    ui->batEditBut->hide();
	//OnUpdParams();
}

configBatFrame::~configBatFrame()
{
    delete ui;
}

void configBatFrame::OnClickOK(void)
{
	OperLogBatDev operLogBatDev;
	
	operLogBatDev.unType = OPER_LOG_TYPE_BAT;
	operLogBatDev.unSite = 0;
	GetDateTime(&operLogBatDev.dtCreate);
	
	operLogBatDev.unEnFlag[0] = g_devConfigInfo_Edt.batParam.unEnFlag;
	operLogBatDev.unEnFlag[1] = m_pDevEnabled->currentIndex();
	
	SaveOperLogData((const char*)&operLogBatDev, sizeof(OperLogBatDev));
	SaveOperLogInfo();
	g_devConfigInfo_Edt.batParam.unEnFlag  = m_pDevEnabled->currentIndex();
	
	//OnUpdParams();
    g_pCfgDataUI->AddGrpData(CFG_BAT_PRM_ITEM,\
                            sizeof(g_devConfigInfo_Edt.batParam),\
                            (BYTE*)&g_devConfigInfo_Edt.batParam);
}
void configBatFrame::OnClickCancel(void)
{
	//OnUpdParams();
}

void configBatFrame::OnUpdParams(BqBatBascInfo *batDevData)
{
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.batParam.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.batParam.unDevID));

	m_pBatTmp->setText(ValueToString(batDevData->unBatTmp,100,2));
	m_pBatCur->setText(QString("%1").arg(batDevData->unBatCur));
	m_pBatVol->setText(QString("%1").arg(batDevData->unBatVol));
	m_pDisChgNum->setText(QString("%1").arg(batDevData->unCycNum));
	m_pBatSoc->setText(QString("%1").arg(batDevData->unBatSoc));

}

