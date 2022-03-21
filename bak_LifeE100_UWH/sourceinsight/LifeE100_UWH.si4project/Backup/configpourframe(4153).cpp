#include "configpourframe.h"
#include "ui_configpourframe.h"
#include "CMonShareData.h"
#include "numbkeyboarddialog.h"

configPourFrame::configPourFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::configPourFrame)
{
    ui->setupUi(this);

    m_pCurLineEdit = NULL;

    //动脉
    m_pPourUPresA  = new QLineEdit(this);
	m_pPourUPresA->setGeometry(QRect(155, 85, 100, 36));
    m_pPourUFlowA  = new QLineEdit(this);
	m_pPourUFlowA->setGeometry(QRect(155, 155, 100, 36));
    m_pPourLFlowA  = new QLineEdit(this);
	m_pPourLFlowA->setGeometry(QRect(155, 225, 100, 36));
	m_pPourUTmpA  =  new QLineEdit(this);
	m_pPourUTmpA->setGeometry(QRect(155, 295, 100, 36));
	m_pPourUSpeedA = new QLineEdit(this);
	m_pPourUSpeedA->setGeometry(QRect(155, 365, 100, 36));
	
	//静脉
    m_pPourUPresV  = new QLineEdit(this);
	m_pPourUPresV->setGeometry(QRect(496, 85, 100, 36));
    m_pPourUFlowV  = new QLineEdit(this);
	m_pPourUFlowV->setGeometry(QRect(496, 155, 100, 36));
    m_pPourLFlowV  = new QLineEdit(this);
	m_pPourLFlowV->setGeometry(QRect(496, 225, 100, 36));
	m_pPourUTmpV   = new QLineEdit(this);
	m_pPourUTmpV->setGeometry(QRect(496, 295, 100, 36));
	m_pPourUSpeedV = new QLineEdit(this);
	m_pPourUSpeedV->setGeometry(QRect(496, 365, 100, 36));
    //水浴
	m_pPourUWatTmp  = new QLineEdit(this);
	m_pPourUWatTmp->setGeometry(QRect(838, 85, 100, 36));
	m_pPourUWatLin  = new QLineEdit(this);
	m_pPourUWatLin->setGeometry(QRect(838, 155, 100, 36));

    connect(ui->pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(ui->pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    OnUpdParams();

}

configPourFrame::~configPourFrame()
{
    delete ui;
}

void configPourFrame::OnClickOK(void)
{
	OperLogPour operLogPour;
	//long lGrpID = m_pGrpID->currentIndex();
	
	operLogPour.unType = OPER_LOG_TYPE_POUR;
	operLogPour.unSite = 0;
	GetDateTime(&operLogPour.dtCreate);

	operLogPour.unPourUPresA[0] = g_devConfigInfo_Edt.devPourParam.unPourUPresA;
	operLogPour.unPourUPresA[1] = m_pPourUPresA->text().toFloat()*10;
    //压力保护值比告警值大5
	if(operLogPour.unPourUPresA[1] < (g_devConfigInfo.devAlmParam.unAlmUPresA+50))
	{
		operLogPour.unPourUPresA[1] = g_devConfigInfo.devAlmParam.unAlmUPresA+50;
	}
	else if(operLogPour.unPourUPresA[1] > POUR_PRESS_A)
	{
	    operLogPour.unPourUPresA[1] = POUR_PRESS_A;
	}
	
	operLogPour.unPourUSpeeA[0] = g_devConfigInfo_Edt.devPourParam.unPourUSpeeA;
	operLogPour.unPourUSpeeA[1] = m_pPourUSpeedA->text().toInt();
    //压力保护值比告警值大10
	if(operLogPour.unPourUSpeeA[1] < (g_devConfigInfo.devAlmParam.unAlmUSpeeA+10))
	{
		operLogPour.unPourUSpeeA[1] = g_devConfigInfo.devAlmParam.unAlmUSpeeA+10;
	}
	else if(operLogPour.unPourUSpeeA[1] > POUR_SPEED_MAX_A)
	{
	    operLogPour.unPourUSpeeA[1] = POUR_SPEED_MAX_A;
	}
	else if(operLogPour.unPourUSpeeA[1] < POUR_SPEED_MIN_A)
	{
	    operLogPour.unPourUSpeeA[1] = POUR_SPEED_MIN_A;
	}

	operLogPour.unPourUTmpA[0] = g_devConfigInfo_Edt.devPourParam.unPourUTmpA;
	operLogPour.unPourUTmpA[1] = m_pPourUTmpA->text().toFloat()*10;
	if(operLogPour.unPourUTmpA[1] < (g_devConfigInfo.devAlmParam.unAlmUTmpA+5))
	{
		operLogPour.unPourUTmpA[1] = g_devConfigInfo.devAlmParam.unAlmUTmpA+5;
	}
	else if(operLogPour.unPourUTmpA[1] > POUR_TMP_A)
	{
	    operLogPour.unPourUTmpA[1] = POUR_TMP_A;
	}
	
	operLogPour.unPourUFlowA[0] = g_devConfigInfo_Edt.devPourParam.unPourUFlowA;
	operLogPour.unPourUFlowA[1] = m_pPourUFlowA->text().toInt();
    //流量保护值比告警值大10
	if(operLogPour.unPourUFlowA[1] < (g_devConfigInfo.devAlmParam.unAlmUFlowA+10))
	{
		operLogPour.unPourUFlowA[1] = g_devConfigInfo.devAlmParam.unAlmUFlowA+10;
	}
	else if(operLogPour.unPourUFlowA[1] > POUR_FLO_U_A)
	{
	    operLogPour.unPourUFlowA[1] = POUR_FLO_U_A;
	}	
	operLogPour.unPourLFlowA[0] = g_devConfigInfo_Edt.devPourParam.unPourLFlowA;
	operLogPour.unPourLFlowA[1] = m_pPourLFlowA->text().toInt();
    //流量低保护值比至少和告警值一腿	if(operLogPour.unPourLFlowA[1] < 0)
	{
	    operLogPour.unPourLFlowA[1] = 0;
	}
//静脉=========================================================================
	operLogPour.unPourUPresV[0] = g_devConfigInfo_Edt.devPourParam.unPourUPresV;
	operLogPour.unPourUPresV[1] = m_pPourUPresV->text().toFloat()*10;
	if(operLogPour.unPourUPresV[1] < (g_devConfigInfo.devAlmParam.unAlmUPresV+20))
	{
		operLogPour.unPourUPresV[1] = g_devConfigInfo.devAlmParam.unAlmUPresV+20;
	}
	else if(operLogPour.unPourUPresV[1] > POUR_PRESS_V)
	{
	    operLogPour.unPourUPresV[1] = POUR_PRESS_V;
	}
	operLogPour.unPourUSpeeV[0] = g_devConfigInfo_Edt.devPourParam.unPourUSpeeV;
	operLogPour.unPourUSpeeV[1] = m_pPourUSpeedV->text().toInt();
	if(operLogPour.unPourUSpeeV[1] < (g_devConfigInfo.devAlmParam.unAlmUSpeeV+10))
	{
		operLogPour.unPourUSpeeV[1] = g_devConfigInfo.devAlmParam.unAlmUSpeeV+10;
	}
	else if(operLogPour.unPourUSpeeV[1] > POUR_SPEED_MAX_A)
	{
	    operLogPour.unPourUSpeeV[1] = POUR_SPEED_MAX_A;
	}
	else if(operLogPour.unPourUSpeeV[1] < POUR_SPEED_MIN_A)
	{
	    operLogPour.unPourUSpeeV[1] = POUR_SPEED_MIN_A;
	}

	operLogPour.unPourUTmpV[0] = g_devConfigInfo_Edt.devPourParam.unPourUTmpV;
	operLogPour.unPourUTmpV[1] = m_pPourUTmpV->text().toFloat()*10;
	if(operLogPour.unPourUTmpV[1] < (g_devConfigInfo.devAlmParam.unAlmUTmpA+5))
	{
		operLogPour.unPourUTmpV[1] = g_devConfigInfo.devAlmParam.unAlmUTmpA+5;
	}
	else if(operLogPour.unPourUTmpV[1] > POUR_TMP_A)
	{
	    operLogPour.unPourUTmpV[1] = POUR_TMP_A;
	}


	operLogPour.unPourUFlowV[0] = g_devConfigInfo_Edt.devPourParam.unPourUFlowV;
    operLogPour.unPourUFlowV[1] = m_pPourUFlowV->text().toInt();
	if(operLogPour.unPourUFlowV[1] < (g_devConfigInfo.devAlmParam.unAlmUFlowV+10))
	{
		operLogPour.unPourUFlowV[1] = g_devConfigInfo.devAlmParam.unAlmUFlowV+10;
	}
	else if(operLogPour.unPourUFlowV[1] > POUR_FLO_U_V)
	{
	    operLogPour.unPourUFlowV[1] = POUR_FLO_U_V;
	}	
	operLogPour.unPourLFlowV[0] = g_devConfigInfo_Edt.devPourParam.unPourLFlowV;
	operLogPour.unPourLFlowV[1] = m_pPourLFlowV->text().toInt();
	if(operLogPour.unPourLFlowV[1] < 0)
	{
	    operLogPour.unPourLFlowV[1] = 0;
	}

	//水浴======================================================================
	operLogPour.unPourUWatTmp[0] = g_devConfigInfo_Edt.devPourParam.unPourUWatTmp;
	operLogPour.unPourUWatTmp[1] = m_pPourUWatTmp->text().toFloat()*10;
    //压力保护值比告警值大10
	if(operLogPour.unPourUWatTmp[1] < (g_devConfigInfo.devAlmParam.unAlmUWatTmp+10))
	{
		operLogPour.unPourUWatTmp[1] = g_devConfigInfo.devAlmParam.unAlmUWatTmp+10;
	}
	else if(operLogPour.unPourUWatTmp[1] > WAT_UP_TMP)
	{
	    operLogPour.unPourUWatTmp[1] = WAT_UP_TMP;
	}		
	operLogPour.unPourWatLin[0] = g_devConfigInfo_Edt.devPourParam.unPourWatLin;
	operLogPour.unPourWatLin[1] = m_pPourUWatLin->text().toInt();
	
	SaveOperLogData((const char*)&operLogPour, sizeof(operLogPour));
	SaveOperLogInfo();

    //压力保护值比告警值大10
	g_devConfigInfo_Edt.devPourParam.unPourUPresA = operLogPour.unPourUPresA[1];
	m_pPourUPresA->setText(ValueToString(operLogPour.unPourUPresA[1],10,1));
	g_devConfigInfo_Edt.devPourParam.unPourUSpeeA = operLogPour.unPourUSpeeA[1];
	m_pPourUSpeedA->setText(QString("%1").arg(operLogPour.unPourUSpeeA[1]));
	g_devConfigInfo_Edt.devPourParam.unPourUFlowA = operLogPour.unPourUFlowA[1];
	m_pPourUFlowA->setText(QString("%1").arg(operLogPour.unPourUFlowA[1]));
    g_devConfigInfo_Edt.devPourParam.unPourLFlowA = operLogPour.unPourLFlowA[1];
	m_pPourLFlowA->setText(QString("%1").arg(operLogPour.unPourLFlowA[1]));
//静脉
	g_devConfigInfo_Edt.devPourParam.unPourUPresV = operLogPour.unPourUPresV[1];
	m_pPourUPresV->setText(ValueToString(operLogPour.unPourUPresV[1],10,1));
	g_devConfigInfo_Edt.devPourParam.unPourUSpeeV = operLogPour.unPourUSpeeV[1];
	m_pPourUSpeedV->setText(QString("%1").arg(operLogPour.unPourUSpeeV[1]));
	g_devConfigInfo_Edt.devPourParam.unPourUFlowV = operLogPour.unPourUFlowV[1];
	m_pPourUFlowV->setText(QString("%1").arg(operLogPour.unPourUFlowV[1]));
    g_devConfigInfo_Edt.devPourParam.unPourLFlowV = operLogPour.unPourLFlowV[1];
	m_pPourLFlowV->setText(QString("%1").arg(operLogPour.unPourLFlowV[1]));

	g_devConfigInfo_Edt.devPourParam.unPourUWatTmp = operLogPour.unPourUWatTmp[1];
	m_pPourUWatTmp->setText(ValueToString(operLogPour.unPourUWatTmp[1],10,1));	

	g_devConfigInfo_Edt.devPourParam.unPourWatLin = m_pPourUWatLin->text().toInt();//GetItemValue(m_pPourUWatLin,1);

    g_pCfgDataUI->AddGrpData(CFG_POUR_PRM_ITEM,\
                                sizeof(DevPourParam),\
                                (BYTE*)&g_devConfigInfo_Edt.devPourParam);
}
void configPourFrame::OnClickCancel(void)
{
	OnUpdParams();
}

void configPourFrame::OnUpdParams(void)
{
	m_pPourUPresA->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUPresA,10,1));	
	m_pPourUSpeedA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUSpeeA));
	m_pPourUTmpA->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUTmpA,10,1));
	m_pPourUFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUFlowA));
	m_pPourLFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourLFlowA));
	
	m_pPourUPresV->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUPresV,10,1));
	m_pPourUSpeedV->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUSpeeV));
	m_pPourUTmpV->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUTmpV,10,1));
	m_pPourUFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUFlowV));
	m_pPourLFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourLFlowV));
	
	m_pPourUWatTmp->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUWatTmp,10,1));
	//m_pPourUWatLin->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourWatLin,1,0));
	m_pPourUWatLin->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourWatLin));
}


void configPourFrame::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void configPourFrame::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        //SyszuxPinyin dlgInputPanel(this);
        NumbKeyboardDialog dlgInputPanel(this);
		dlgInputPanel..setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
        if(m_pCurLineEdit==m_pPourUPresA||m_pCurLineEdit==m_pPourUPresV||\
           m_pCurLineEdit==m_pPourUWatTmp||\
           m_pCurLineEdit==m_pPourUTmpA||m_pCurLineEdit==m_pPourUTmpV)
        {
            dlgInputPanel.SetInputMask(QString("0000.0"));
        }
		else if(m_pCurLineEdit==m_pPourUWatLin)
		{
		    dlgInputPanel.SetInputMask(QString("000"));
		}
		else if(m_pCurLineEdit==m_pPourUFlowA||m_pCurLineEdit==m_pPourLFlowA||\
                m_pCurLineEdit==m_pPourUFlowV||m_pCurLineEdit==m_pPourLFlowV)
		{
		    dlgInputPanel.SetInputMask(QString("0000"));
		}
		else if(m_pCurLineEdit==m_pPourUSpeedA||m_pCurLineEdit==m_pPourUSpeedV)
		{
		    dlgInputPanel.SetInputMask(QString("00000"));
		}				
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void configPourFrame::OnFocusChanged(QWidget * old, QWidget * now)
{
    if( m_pPourUPresA == old ||\
        m_pPourUFlowA == old ||\
        m_pPourUTmpA  == old ||\
        m_pPourLFlowA == old ||\
        m_pPourUPresV == old ||\
        m_pPourUFlowV == old ||\
        m_pPourUTmpV  == old ||\
        m_pPourLFlowV == old ||\
        m_pPourUWatTmp== old ||\
        m_pPourUWatLin== old||\
        m_pPourUSpeedA== old||\
        m_pPourUSpeedV== old)
    {
        m_pCurLineEdit = old;
    }
}

