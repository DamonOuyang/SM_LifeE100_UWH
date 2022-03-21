#include "configartframe.h"
#include "ui_configartframe.h"
//#include "CMonShareData.h"
#include "cmonsharedata.h"
#include "numbkeyboarddialog.h"

configArtFrame::configArtFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configArtFrame)
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

    m_pPress = new QLineEdit(this);  //动脉血泵压力设置值
    m_pPress->setGeometry(QRect(155, 225, 100, 36));
    m_pSpeed = new QLineEdit(this);  //动脉血泵转速设置值
    m_pSpeed->setGeometry(QRect(155, 295, 100, 36));

    m_pPressLimt = new QLineEdit(this);  //动脉血泵压力设置值
    m_pPressLimt->setGeometry(QRect(496, 85, 100, 36));
    m_pSpeedLimt = new QLineEdit(this);  //动脉血泵转速设置值
    m_pSpeedLimt->setGeometry(QRect(496, 155, 100, 36));

    connect(ui->artOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->artCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(ui->artEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    OnUpdParams();
}

configArtFrame::~configArtFrame()
{
    delete ui;
}

void configArtFrame::OnClickOK(void)
{
	OperLogPumDev operLogPumDev;
    
	operLogPumDev.unType = OPER_LOG_TYPE_APUM;
	operLogPumDev.unSite = 0;
	GetDateTime(&operLogPumDev.dtCreate);

	operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.arteryParm.unEnFlag;
	operLogPumDev.unEnFlag[1] = m_pDevEnabled->currentIndex();
	
	operLogPumDev.unPress[0] = g_devConfigInfo_Edt.arteryParm.unPress;
	operLogPumDev.unPress[1] = m_pPress->text().toFloat()*10;
	operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.arteryParm.unSpeed;
	operLogPumDev.unSpeed[1] = m_pSpeed->text().toInt();
	operLogPumDev.unPress[1] = operLogPumDev.unPress[1]/10;
	operLogPumDev.unPress[1] *= 10;

	operLogPumDev.unPressLimt[0] = g_devConfigInfo_Edt.arteryParm.unPressLimt;
    operLogPumDev.unPressLimt[1] = m_pPressLimt->text().toFloat()*10;
	operLogPumDev.unSpeedLimt[0] = g_devConfigInfo_Edt.arteryParm.unSpeedLimt;
	operLogPumDev.unSpeedLimt[1] = m_pSpeedLimt->text().toInt();
	operLogPumDev.unPressLimt[1] = operLogPumDev.unPressLimt[1]/10;
	operLogPumDev.unPressLimt[1] *= 10;
	
	SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
	SaveOperLogInfo();

    g_devConfigInfo_Edt.arteryParm.unEnFlag  = m_pDevEnabled->currentIndex();
	g_devConfigInfo_Edt.arteryParm.unPress = GetItemValue(m_pPress,10);
	g_devConfigInfo_Edt.arteryParm.unSpeed = GetItemValue(m_pSpeed,1);
	g_devConfigInfo_Edt.arteryParm.unPress = g_devConfigInfo_Edt.arteryParm.unPress/10;
	g_devConfigInfo_Edt.arteryParm.unPress*=10;

    g_devConfigInfo_Edt.arteryParm.unPressLimt = GetItemValue(m_pPressLimt,1);
	g_devConfigInfo_Edt.arteryParm.unSpeedLimt = GetItemValue(m_pSpeedLimt,1);
    g_devConfigInfo_Edt.arteryParm.unPressLimt = g_devConfigInfo_Edt.arteryParm.unPressLimt/10;
    g_devConfigInfo_Edt.arteryParm.unPressLimt *= 10;
		
	OnUpdParams();
    //保存禁用和启用
    g_pCfgDataUI->AddGrpData(CFG_ARTERY_PRS_ITEM,\
                            sizeof(g_devConfigInfo_Edt.arteryParm),\
                            (BYTE*)&g_devConfigInfo_Edt.arteryParm);
}
void configArtFrame::OnClickCancel(void)
{
	OnUpdParams();
}

void configArtFrame::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void configArtFrame::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        //SyszuxPinyin dlgInputPanel(this);
        NumbKeyboardDialog dlgInputPanel(this);
		dlgInputPanel.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));

        if(m_pPress == m_pCurLineEdit ||\
		   m_pPressLimt == m_pCurLineEdit)
        {
            dlgInputPanel.SetInputMask(QString("0000"));// dm?
        }
		else if(m_pSpeed == m_pCurLineEdit ||\
			    m_pSpeedLimt == m_pCurLineEdit)
		{
		    dlgInputPanel.SetInputMask(QString("0000"));
		}
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void configArtFrame::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pPress == old ||
	   m_pSpeed == old ||
       m_pPressLimt == old ||
	   m_pSpeedLimt == old)
    {
        m_pCurLineEdit = old;
    }
}
void configArtFrame::OnUpdParams(void)
{
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.arteryParm.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.arteryParm.unDevID));
    m_pPress->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unPress,1,1));
	m_pSpeed->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unSpeed,1,0));

//    m_pPressLimt->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unPressLimt,100,1));
    m_pPressLimt->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unPressLimt,1,0)); //dm
	m_pSpeedLimt->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unSpeedLimt,1,0));
}

