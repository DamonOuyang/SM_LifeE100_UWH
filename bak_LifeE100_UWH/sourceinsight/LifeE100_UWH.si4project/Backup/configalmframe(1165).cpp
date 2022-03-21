#include "includes.h"
#include "configalmframe.h"
#include "ui_configalmframe.h"
#include "CMonShareData.h"
#include "numbkeyboarddialog.h"

configAlmFrame::configAlmFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configAlmFrame)
{
    ui->setupUi(this);

	m_pCurLineEdit = NULL;
    //动脉
	m_pAlmUPresA  = new QLineEdit(this);
	m_pAlmUPresA->setGeometry(QRect(155, 85, 100, 36));
	m_pAlmUFlowA  = new QLineEdit(this);
	m_pAlmUFlowA->setGeometry(QRect(155, 155, 100, 36));
	m_pAlmLFlowA  = new QLineEdit(this);
	m_pAlmLFlowA->setGeometry(QRect(155, 225, 100, 36));
	//m_pAlmLPresA	= new QLineEdit(this);
	m_pAlmUTmpA  = new QLineEdit(this);
	m_pAlmUTmpA->setGeometry(QRect(155, 295, 100, 36));
	m_pAlmBubblA  = new QLineEdit(this);
	m_pAlmBubblA->setGeometry(QRect(155, 365, 100, 36));
	//静脉
	m_pAlmUPresV  = new QLineEdit(this);
	m_pAlmUPresV->setGeometry(QRect(496, 85, 100, 36));
	m_pAlmUFlowV  = new QLineEdit(this);
	m_pAlmUFlowV->setGeometry(QRect(496, 155, 100, 36));
	m_pAlmLFlowV  = new QLineEdit(this);
	m_pAlmLFlowV->setGeometry(QRect(496, 225, 100, 36));
	//m_pAlmLPresV	= new QLineEdit(this);
	m_pAlmUTmpV  = new QLineEdit(this);
	m_pAlmUTmpV->setGeometry(QRect(496, 295, 100, 36));
	m_pAlmBubblV  = new QLineEdit(this);
    m_pAlmBubblV->setGeometry(QRect(496, 365, 100, 36));
	//水浴
	m_pAlmUWatTmp  = new QLineEdit(this);
	m_pAlmUWatTmp->setGeometry(QRect(838, 85, 100, 36));
	m_pAlmUWatLin  = new QLineEdit(this);
	m_pAlmUWatLin->setGeometry(QRect(838, 155, 100, 36));
	m_pAlmLWatLin  = new QLineEdit(this);
	m_pAlmLWatLin->setGeometry(QRect(838, 225, 100, 36));
	m_pAlmLBloodLin  = new QLineEdit(this);
	m_pAlmLBloodLin->setGeometry(QRect(838, 295, 100, 36));
	
    connect(ui->aOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->aCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(ui->aEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
	connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
	OnUpdParams();

}

configAlmFrame::~configAlmFrame()
{
    delete ui;
}

void configAlmFrame::OnClickOK(void)
{
	OperLogAlm operLogAlm;
	//long lGrpID = m_pGrpID->currentIndex();
	
	operLogAlm.unType = OPER_LOG_TYPE_ALM;
	operLogAlm.unSite = 0;
	GetDateTime(&operLogAlm.dtCreate);

	operLogAlm.unAlmUPresA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUPresA;
	operLogAlm.unAlmUPresA[1] = m_pAlmUPresA->text().toFloat()*10;
    //压力上限告警值比保护值小10
	if(operLogAlm.unAlmUPresA[1] > SET_ALM_PRES_U_A)
	{
		operLogAlm.unAlmUPresA[1] = SET_ALM_PRES_U_A;
	}
	
	operLogAlm.unAlmUTmpA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA;
	operLogAlm.unAlmUTmpA[1] = m_pAlmUTmpA->text().toFloat()*10;
    //水温上限告警值比保护值小10
	if(operLogAlm.unAlmUTmpA[1] > SET_ALM_TMP_U_A)
	{
		operLogAlm.unAlmUTmpA[1] = SET_ALM_TMP_U_A;
	}
	
	operLogAlm.unAlmUFlowA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA;
	operLogAlm.unAlmUFlowA[1] = m_pAlmUFlowA->text().toInt();
    //流量上限告警值比保护值小10
	if(operLogAlm.unAlmUFlowA[1] > SET_ALM_FLO_U_A)
	{
		operLogAlm.unAlmUFlowA[1] = SET_ALM_FLO_U_A;
	}
	operLogAlm.unAlmLFlowA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA;
	operLogAlm.unAlmLFlowA[1] = m_pAlmLFlowA->text().toInt();
    //流量下限告警值至少不小于保护值
	if(operLogAlm.unAlmLFlowA[1] < SET_ALM_FLO_L_A)
	{
		operLogAlm.unAlmLFlowA[1] = SET_ALM_FLO_L_A;
	}
	operLogAlm.unAlmBubbleA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmBubbleA;
	operLogAlm.unAlmBubbleA[1] = m_pAlmBubblA->text().toInt();

//静脉
	operLogAlm.unAlmUPresV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUPresV;
	operLogAlm.unAlmUPresV[1] = m_pAlmUPresV->text().toFloat()*10;
	if(operLogAlm.unAlmUPresV[1] > SET_ALM_PRES_U_V)
	{
		operLogAlm.unAlmUPresV[1] = SET_ALM_PRES_U_V;
	}

	operLogAlm.unAlmUTmpV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV;
	operLogAlm.unAlmUTmpV[1] = m_pAlmUTmpV->text().toFloat()*10;
    //水温上限告警值比保护值小10
	if(operLogAlm.unAlmUTmpV[1] > SET_ALM_TMP_U_V)
	{
		operLogAlm.unAlmUTmpV[1] = SET_ALM_TMP_U_V;
	}
	operLogAlm.unAlmUFlowV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV;
    operLogAlm.unAlmUFlowV[1] = m_pAlmUFlowV->text().toInt();
	if(operLogAlm.unAlmUFlowV[1] > SET_ALM_FLO_U_V)
	{
		operLogAlm.unAlmUFlowV[1] = SET_ALM_FLO_U_V;
	}	
	operLogAlm.unAlmLFlowV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV;
	operLogAlm.unAlmLFlowV[1] = m_pAlmLFlowV->text().toInt();
	if(operLogAlm.unAlmLFlowV[1] < SET_ALM_FLO_L_V)
	{
		operLogAlm.unAlmLFlowV[1] = SET_ALM_FLO_L_V;
	}
	
	operLogAlm.unAlmBubbleV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmBubbleV;
	operLogAlm.unAlmBubbleV[1] = m_pAlmBubblV->text().toInt();

//水浴
	operLogAlm.unAlmUWatTmp[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp;
	operLogAlm.unAlmUWatTmp[1] = m_pAlmUWatTmp->text().toFloat()*10;
    //水温上限告警值比保护值小10
	if(operLogAlm.unAlmUWatTmp[1] > SET_ALM_TMP_U_WAT)
	{
		operLogAlm.unAlmUWatTmp[1] = SET_ALM_TMP_U_WAT;
	}

	operLogAlm.unAlmUWatLin[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUWatLin;
	operLogAlm.unAlmUWatLin[1] = m_pAlmUWatLin->text().toInt();
	
	operLogAlm.unAlmLWatLin[0] = g_devConfigInfo_Edt.devAlmParam.unAlmLWatLin;
	operLogAlm.unAlmLWatLin[1] = m_pAlmLWatLin->text().toInt();

	operLogAlm.unAlmBloodLin[0] = g_devConfigInfo_Edt.devAlmParam.unAlmBloodLin;
	operLogAlm.unAlmBloodLin[1] = m_pAlmLBloodLin->text().toInt();
	
	SaveOperLogData((const char*)&operLogAlm, sizeof(operLogAlm));
	SaveOperLogInfo();

//---------------动脉-------------------

	g_devConfigInfo_Edt.devAlmParam.unAlmUPresA = operLogAlm.unAlmUPresA[1];
	m_pAlmUPresA->setText(ValueToString(operLogAlm.unAlmUPresA[1],10,1));
	
	g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA = operLogAlm.unAlmUTmpA[1];
	m_pAlmUTmpA->setText(ValueToString(operLogAlm.unAlmUTmpA[1],10,1));
	
	g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA = operLogAlm.unAlmUFlowA[1];
	m_pAlmUFlowA->setText(QString("%1").arg(operLogAlm.unAlmUFlowA[1]));

	g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA = operLogAlm.unAlmLFlowA[1];
	m_pAlmLFlowA->setText(QString("%1").arg(operLogAlm.unAlmLFlowA[1]));
	
	g_devConfigInfo_Edt.devAlmParam.unAlmBubbleA = m_pAlmBubblA->text().toInt();

//---------------------静脉-------------------------------
	g_devConfigInfo_Edt.devAlmParam.unAlmUPresV = operLogAlm.unAlmUPresV[1];
	m_pAlmUPresV->setText(ValueToString(operLogAlm.unAlmUPresV[1],10,1));
	
	g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV = operLogAlm.unAlmUTmpV[1];
	m_pAlmUTmpV->setText(ValueToString(operLogAlm.unAlmUTmpV[1],10,1));
	
	g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV = operLogAlm.unAlmUFlowV[1];
	m_pAlmUFlowV->setText(QString("%1").arg(operLogAlm.unAlmUFlowV[1]));

	g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV = operLogAlm.unAlmLFlowV[1];
	m_pAlmLFlowV->setText(QString("%1").arg(operLogAlm.unAlmLFlowV[1]));
	
	g_devConfigInfo_Edt.devAlmParam.unAlmBubbleV = m_pAlmBubblV->text().toInt();
	
//---------------------水浴-------------------------------	
	g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp = operLogAlm.unAlmUWatTmp[1];
	m_pAlmUWatTmp->setText(ValueToString(operLogAlm.unAlmUWatTmp[1],10,1));
		
	g_devConfigInfo_Edt.devAlmParam.unAlmUWatLin = m_pAlmUWatLin->text().toInt();
	g_devConfigInfo_Edt.devAlmParam.unAlmLWatLin = m_pAlmLWatLin->text().toInt();
	g_devConfigInfo_Edt.devAlmParam.unAlmBloodLin = m_pAlmLBloodLin->text().toInt();

    g_pCfgDataUI->AddGrpData(CFG_ALM_PRM_ITEM,\
                                sizeof(DevAlmParam),\
                                (BYTE*)&g_devConfigInfo_Edt.devAlmParam);
}
void configAlmFrame::OnClickCancel(void)
{

}

void configAlmFrame::OnUpdParams(void)
{
	m_pAlmUPresA->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresA,10,1));
	m_pAlmUTmpA->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA,10,1));
	m_pAlmUFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA));
	m_pAlmLFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA));
	m_pAlmBubblA->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmBubbleA));
	
	m_pAlmUPresV->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresV,10,1));
	m_pAlmUTmpV->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV,10,1));
	m_pAlmUFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV));
	m_pAlmLFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV));
	m_pAlmBubblV->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmBubbleV));
	
	m_pAlmUWatTmp->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp,10,1));
	m_pAlmUWatLin->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmUWatLin));
	m_pAlmLWatLin->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmLWatLin));
	m_pAlmLBloodLin->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmBloodLin));
}


void configAlmFrame::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void configAlmFrame::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        //SyszuxPinyin dlgInputPanel(this);
        NumbKeyboardDialog dlgInputPanel(this);

        if(m_pCurLineEdit==m_pAlmUPresA||m_pCurLineEdit==m_pAlmUPresV||\
           m_pCurLineEdit==m_pAlmUWatTmp||\
           m_pCurLineEdit==m_pAlmUTmpA||m_pCurLineEdit==m_pAlmUTmpV)
        {
            dlgInputPanel.SetInputMask(QString("0000.0"));
        }
		else if(m_pCurLineEdit==m_pAlmLWatLin||m_pCurLineEdit==m_pAlmLBloodLin||\
			    m_pCurLineEdit==m_pAlmUWatLin)
		{
		    dlgInputPanel.SetInputMask(QString("000"));
		}
		else if(m_pCurLineEdit==m_pAlmUFlowA||m_pCurLineEdit==m_pAlmLFlowA||\
                m_pCurLineEdit==m_pAlmUFlowV||m_pCurLineEdit==m_pAlmLFlowV||\
                m_pCurLineEdit==m_pAlmBubblA||m_pCurLineEdit==m_pAlmBubblV)
		{
		    dlgInputPanel.SetInputMask(QString("0000"));
		}
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void configAlmFrame::OnFocusChanged(QWidget * old, QWidget * now)
{
    if( m_pAlmUPresA == old ||\
        m_pAlmUTmpA ==  old ||\
        m_pAlmUFlowA == old ||\
        m_pAlmLFlowA == old ||\
        m_pAlmUPresV == old ||\
        m_pAlmUTmpV ==  old ||\
        m_pAlmUFlowV == old ||\
        m_pAlmLFlowV == old ||\
        m_pAlmUWatTmp== old ||\
        m_pAlmLWatLin== old ||\
        m_pAlmUWatLin== old ||\
        m_pAlmLBloodLin==old||\
        m_pAlmBubblA == old ||\
        m_pAlmBubblV == old)
    {
        m_pCurLineEdit = old;
    }
}

