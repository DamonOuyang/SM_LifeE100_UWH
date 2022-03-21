#include "configveiframe.h"
#include "ui_configveiframe.h"
#include "CMonShareData.h"
#include "numbkeyboarddialog.h"

configVeiFrame::configVeiFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configVeiFrame)
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

    connect(ui->veiOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->veiCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(ui->veiEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    OnUpdParams();	
}

configVeiFrame::~configVeiFrame()
{
    delete ui;
}

void configVeiFrame::OnClickOK(void)
{
	OperLogPumDev operLogPumDev;
    
	operLogPumDev.unType = OPER_LOG_TYPE_VPUM;
	operLogPumDev.unSite = 0;
	GetDateTime(&operLogPumDev.dtCreate);

	operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.veinParm.unEnFlag;
	operLogPumDev.unEnFlag[1] = m_pDevEnabled->currentIndex();
	
	operLogPumDev.unPress[0] = g_devConfigInfo_Edt.veinParm.unPress;
	operLogPumDev.unPress[1] = m_pPress->text().toFloat()*10;
	operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.veinParm.unSpeed;
	operLogPumDev.unSpeed[1] = m_pSpeed->text().toInt();
	operLogPumDev.unPress[1] = operLogPumDev.unPress[1]/10;
	operLogPumDev.unPress[1] *= 10;

	operLogPumDev.unPressLimt[0] = g_devConfigInfo_Edt.veinParm.unPressLimt;
	operLogPumDev.unPressLimt[1] = m_pPressLimt->text().toFloat()*10;
	operLogPumDev.unSpeedLimt[0] = g_devConfigInfo_Edt.veinParm.unSpeedLimt;
	operLogPumDev.unSpeedLimt[1] = m_pSpeedLimt->text().toInt();
	operLogPumDev.unPressLimt[1] = operLogPumDev.unPressLimt[1]/10;
	operLogPumDev.unPressLimt[1] *= 10;
	
	SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
	SaveOperLogInfo();

    g_devConfigInfo_Edt.veinParm.unEnFlag  = m_pDevEnabled->currentIndex();
	g_devConfigInfo_Edt.veinParm.unPress = GetItemValue(m_pPress,10);
	g_devConfigInfo_Edt.veinParm.unSpeed = GetItemValue(m_pSpeed,1);
	g_devConfigInfo_Edt.veinParm.unPress = g_devConfigInfo_Edt.veinParm.unPress/10;
	g_devConfigInfo_Edt.veinParm.unPress*=10;

	g_devConfigInfo_Edt.veinParm.unPressLimt = GetItemValue(m_pPressLimt,10);
	g_devConfigInfo_Edt.veinParm.unSpeedLimt = GetItemValue(m_pSpeedLimt,1);
	g_devConfigInfo_Edt.veinParm.unPressLimt = g_devConfigInfo_Edt.veinParm.unPressLimt/10;
	g_devConfigInfo_Edt.veinParm.unPressLimt*=10;	
		
	OnUpdParams();
    //保存禁用和启用
    g_pCfgDataUI->AddGrpData(CFG_VEIN_PRS_ITEM,\
                            sizeof(g_devConfigInfo_Edt.veinParm),\
                            (BYTE*)&g_devConfigInfo_Edt.veinParm);
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

        if(m_pPress == m_pCurLineEdit ||\
		   m_pPressLimt == m_pCurLineEdit)
        {
            dlgInputPanel.SetInputMask(QString("000.0"));
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
    if(m_pPress == old ||\
	   m_pSpeed == old ||
	   m_pPressLimt == old ||\
	   m_pSpeedLimt == old)
    {
        m_pCurLineEdit = old;
    }
}
void configArtFrame::OnUpdParams(void)
{
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.veinParm.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.veinParm.unDevID));
    m_pPress->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unPress,10,1));
	m_pSpeed->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unSpeed,1,0));

	m_pPressLimt->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unPressLimt,10,1));
	m_pSpeedLimt->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unSpeedLimt,1,0));
}

