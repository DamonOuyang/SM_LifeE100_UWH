#include "configwatframe.h"
#include "ui_configwatframe.h"

#include "CMonShareData.h"
#include "numbkeyboarddialog.h"

configWatFrame::configWatFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configWatFrame)
{
    ui->setupUi(this);
	
    m_pCurLineEdit = NULL;

    m_pDevID      = new QLineEdit(this);
	m_pDevID->setGeometry(QRect(155, 85, 100, 36));
    m_pDevEnabled = CreateComboBox(this);
	m_pDevEnabled->setGeometry(QRect(155, 155, 100, 36));
    m_pDevEnabled->addItem(tr("禁用"));
    m_pDevEnabled->addItem(tr("启用"));
    m_pDevID->setReadOnly(true);

    m_pTmpVal = new QLineEdit(this);  //水浴温度设置值
    m_pTmpVal->setGeometry(QRect(155, 225, 100, 36));
	
	m_pTmpValLimt = new QLineEdit(this);  //水浴温度设置值
    m_pTmpValLimt->setGeometry(QRect(496, 85, 100, 36));


    connect(ui->wOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->wCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(ui->wEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    OnUpdParams();
}

configWatFrame::~configWatFrame()
{
    delete ui;
}

void configWatFrame::OnClickOK(void)
{
	OperLogWatDev operLogWatDev;
	
	operLogWatDev.unType = OPER_LOG_TYPE_WAT;
	operLogWatDev.unSite = 0;
	GetDateTime(&operLogWatDev.dtCreate);
	
	operLogWatDev.unEnFlag[0] = g_devConfigInfo_Edt.watRooParam.unEnFlag;
	operLogWatDev.unEnFlag[1] = m_pDevEnabled->currentIndex();
	operLogWatDev.unTmpVal[0] = g_devConfigInfo_Edt.watRooParam.unTmpVal;
	operLogWatDev.unTmpVal[1] = m_pTmpVal->text().toFloat()*10;
	
	operLogWatDev.unTmpValLimt[0] = g_devConfigInfo_Edt.watRooParam.unTmpValLimt;
	operLogWatDev.unTmpValLimt[1] = m_pTmpValLimt->text().toFloat()*10; 	
	
	SaveOperLogData((const char*)&operLogWatDev, sizeof(OperLogWatDev));
	SaveOperLogInfo();
	
	g_devConfigInfo_Edt.watRooParam.unEnFlag  = m_pDevEnabled->currentIndex();
	g_devConfigInfo_Edt.watRooParam.unTmpVal = GetItemValue(m_pTmpVal,10);
	g_devConfigInfo_Edt.watRooParam.unTmpValLimt = GetItemValue(m_pTmpValLimt,10);

	OnUpdParams();
    g_pCfgDataUI->AddGrpData(CFG_WAT_ROOM_ITEM,\
                            sizeof(g_devConfigInfo_Edt.watRooParam),\
                            (BYTE*)&g_devConfigInfo_Edt.watRooParam);
}
void configWatFrame::OnClickCancel(void)
{
	OnUpdParams();
}

void configWatFrame::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void configWatFrame::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        //SyszuxPinyin dlgInputPanel(this);
        NumbKeyboardDialog dlgInputPanel(this);
        if(m_pTmpVal == m_pCurLineEdit ||\
		   m_pTmpValLimt == m_pCurLineEdit)
        {
            dlgInputPanel.SetInputMask(QString("00.0"));
        }
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void configWatFrame::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pTmpVal == old ||\
	   m_pTmpValLimt == old)
    {
        m_pCurLineEdit = old;
    }
}
void configWatFrame::OnUpdParams(void)
{
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.watRooParam.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.watRooParam.unDevID));
    m_pTmpVal->setText(ValueToString(g_devConfigInfo_Edt.watRooParam.unTmpVal,10,1));

	m_pTmpValLimt->setText(ValueToString(g_devConfigInfo_Edt.watRooParam.unTmpValLimt,10,1));
}


