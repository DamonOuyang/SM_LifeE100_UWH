#include "Includes.h"
#include "pourconfigpanel.h"
#include "CMonShareData.h"
#include <QtGui>
#include "SyszuxPinyin.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>

PourConfigPanel::PourConfigPanel(QWidget *parent) :
    QFrame(parent)
{
    m_pCurLineEdit = NULL;
    QHBoxLayout* pMainLayout = new QHBoxLayout();
    setLayout(pMainLayout);

    QGroupBox* pLeftGrpBox  = new QGroupBox(this);
    QGroupBox* pRightGrpBox = new QGroupBox(this);
    pRightGrpBox->setMinimumWidth(100);

    pMainLayout->addWidget(pLeftGrpBox);
    pMainLayout->addWidget(pRightGrpBox);


    m_pPourUPresA  = new QLineEdit(this);
	m_pPourUSpeedA = new QLineEdit(this);
    m_pPourUFlowA  = new QLineEdit(this);
    m_pPourLFlowA  = new QLineEdit(this);
	
    m_pPourUPresV  = new QLineEdit(this);
	m_pPourUSpeedV = new QLineEdit(this);
    m_pPourUFlowV  = new QLineEdit(this);
    m_pPourLFlowV  = new QLineEdit(this);

	m_pPourUWatTmp  = new QLineEdit(this);
	m_pPourUWatLin  = new QLineEdit(this);

	QFormLayout *formLayout = new QFormLayout;
	
    QLabel *pLabel = new QLabel(tr("--动脉泵安全配置--"));
    pLabel->setMinimumSize(300,30);
    formLayout->addRow(tr(""),pLabel);

    long lEditWidth = 160;
    
    //AddItem(pFrmLayout,m_pPourUPresA,tr("压力上限:"),tr("(mmHg)"),lEditWidth+60);
	//AddItem(pFrmLayout,m_pPourUSpeedA,tr("转速上限:"),tr("(r/min)"),lEditWidth+60);
    //AddItem(formLayout,m_pPourUFlowA,tr("流量上限:"),tr("(ml/min)"),lEditWidth+60);
    //AddItem(formLayout,m_pPourLFlowA,tr("流量下限:"),tr("(ml/min)"),lEditWidth+60);	

	QHBoxLayout* pFirstRow	= new QHBoxLayout();
	QFormLayout* pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUPresA,tr("压力上限:"),tr("(mmHg)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUSpeedA,tr("转速上限:"),tr("(r/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);

	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUFlowA,tr("流量上限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourLFlowA,tr("流量下限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);


    pLabel = new QLabel(tr("--静脉泵安全配置--"));
    pLabel->setMinimumSize(300,30);
    formLayout->addRow(tr(""),pLabel);
	
    //AddItem(formLayout,m_pPourUPresV,tr("压力上限:"),tr("(mmHg)"),lEditWidth+60);
	//AddItem(formLayout,m_pPourUSpeedV,tr("转速上限:"),tr("(r/min)"),lEditWidth+60);
    //AddItem(formLayout,m_pPourUFlowV,tr("流量上限:"),tr("(ml/min)"),lEditWidth+60);
    //AddItem(formLayout,m_pPourLFlowV,tr("流量下限:"),tr("(ml/min)"),lEditWidth+60);	
	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUPresV,tr("压力上限:"),tr("(mmHg)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUSpeedV,tr("转速上限:"),tr("(r/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);

	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUFlowV,tr("流量上限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourLFlowV,tr("流量下限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);	


    pLabel = new QLabel(tr("--水浴安全配置--"));
    pLabel->setMinimumSize(300,30);
    formLayout->addRow(tr(""),pLabel);
	//AddItem(formLayout,m_pPourUWatTmp,tr("温度上限:"),tr("(℃)"),lEditWidth+60);	
    //AddItem(formLayout,m_pPourUWatLin,tr("水位下限:"),tr("( %)"),lEditWidth+60);		
	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUWatTmp,tr("温度上限:"),tr("(℃)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pPourUWatLin,tr("水位下限:"),tr("( %)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);	

    pLeftGrpBox->setLayout(formLayout);

    QHBoxLayout* pButLayout = new QHBoxLayout();
    QDialogButtonBox* pButs = new QDialogButtonBox(Qt::Vertical);
    pButLayout->addWidget(pButs);
    QPushButton* pOkBut = new QPushButton(tr(SAVE_BUT_NAME));
    pOkBut->setMinimumSize(120,50);
    QPushButton* pCancelBut = new QPushButton(tr(CANCEL_BUT_NAME));
    pCancelBut->setMinimumSize(120,50);
    QPushButton* pEditBut = new QPushButton(tr(INPUT_BUT_NAME));
    pEditBut->setMinimumSize(120,50);

    pButs->addButton(pOkBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pCancelBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pEditBut,QDialogButtonBox::ActionRole);

    pButs->setMinimumSize(140,200);
    pRightGrpBox->setLayout(pButLayout);

    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    OnUpdParams();
}

void PourConfigPanel::OnClickOK(void)
{
	OperLogPour operLogPour;
	//long lGrpID = m_pGrpID->currentIndex();
	
	operLogPour.unType = OPER_LOG_TYPE_POUR;
	operLogPour.unSite = 0;
	GetDateTime(&operLogPour.dtCreate);

	operLogPour.unPourUPresA[0] = g_devConfigInfo_Edt.devPourParam.unPourUPresA;
	operLogPour.unPourUPresA[1] = m_pPourUPresA->text().toFloat()*10;

    //压力保护值比告警值大10
	if(operLogPour.unPourUPresA[1] < (g_devConfigInfo.devAlmParam.unAlmUPresA+100))
	{
		operLogPour.unPourUPresA[1] = g_devConfigInfo.devAlmParam.unAlmUPresA+100;
	}
	
	operLogPour.unPourUSpeeA[0] = g_devConfigInfo_Edt.devPourParam.unPourUSpeeA;
	operLogPour.unPourUSpeeA[1] = m_pPourUSpeedA->text().toInt();
	operLogPour.unPourUFlowA[0] = g_devConfigInfo_Edt.devPourParam.unPourUFlowA;
	operLogPour.unPourUFlowA[1] = m_pPourUFlowA->text().toInt();
	
    //流量保护值比告警值大10
	if(operLogPour.unPourUFlowA[1] < (g_devConfigInfo.devAlmParam.unAlmUFlowA+10))
	{
		operLogPour.unPourUFlowA[1] = g_devConfigInfo.devAlmParam.unAlmUFlowA+10;
	}
	operLogPour.unPourLFlowA[0] = g_devConfigInfo_Edt.devPourParam.unPourLFlowA;
	operLogPour.unPourLFlowA[1] = m_pPourLFlowA->text().toInt();
    //流量低保护值比至少和告警值一致
	if(operLogPour.unPourLFlowA[1] > g_devConfigInfo.devAlmParam.unAlmLFlowA)
	{
		operLogPour.unPourLFlowA[1] = g_devConfigInfo.devAlmParam.unAlmLFlowA;
	}

	operLogPour.unPourUPresV[0] = g_devConfigInfo_Edt.devPourParam.unPourUPresV;
	operLogPour.unPourUPresV[1] = m_pPourUPresV->text().toFloat()*10;
	
	operLogPour.unPourUSpeeV[0] = g_devConfigInfo_Edt.devPourParam.unPourUSpeeV;
	operLogPour.unPourUSpeeV[1] = m_pPourUSpeedV->text().toInt();

	operLogPour.unPourUFlowV[0] = g_devConfigInfo_Edt.devPourParam.unPourUFlowV;
    operLogPour.unPourUFlowV[1] = m_pPourUFlowV->text().toInt();
	operLogPour.unPourLFlowV[0] = g_devConfigInfo_Edt.devPourParam.unPourLFlowV;
	operLogPour.unPourLFlowV[1] = m_pPourLFlowV->text().toInt();

	operLogPour.unPourUWatTmp[0] = g_devConfigInfo_Edt.devPourParam.unPourUWatTmp;
	operLogPour.unPourUWatTmp[1] = m_pPourUWatTmp->text().toFloat()*10;
    //压力保护值比告警值大10
	if(operLogPour.unPourUWatTmp[1] < (g_devConfigInfo.devAlmParam.unAlmUWatTmp+10))
	{
		operLogPour.unPourUWatTmp[1] = g_devConfigInfo.devAlmParam.unAlmUWatTmp+10;
	}
	operLogPour.unPourWatLin[0] = g_devConfigInfo_Edt.devPourParam.unPourWatLin;
	operLogPour.unPourWatLin[1] = m_pPourUWatLin->text().toInt();
	
	SaveOperLogData((const char*)&operLogPour, sizeof(operLogPour));
	SaveOperLogInfo();

    g_devConfigInfo_Edt.devPourParam.unPourUPresA = GetItemValue(m_pPourUPresA,10);
    //压力保护值比告警值大10
	if(g_devConfigInfo_Edt.devPourParam.unPourUPresA < (g_devConfigInfo.devAlmParam.unAlmUPresA+100))
	{
		g_devConfigInfo_Edt.devPourParam.unPourUPresA = g_devConfigInfo.devAlmParam.unAlmUPresA+100;
		m_pPourUPresA->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUPresA,10,1));	
	}
	g_devConfigInfo_Edt.devPourParam.unPourUSpeeA = m_pPourUSpeedA->text().toInt();
	g_devConfigInfo_Edt.devPourParam.unPourUFlowA = m_pPourUFlowA->text().toInt();
    //流量保护值比告警值大10
	if(g_devConfigInfo_Edt.devPourParam.unPourUFlowA < (g_devConfigInfo.devAlmParam.unAlmUFlowA+10))
	{
		g_devConfigInfo_Edt.devPourParam.unPourUFlowA = g_devConfigInfo.devAlmParam.unAlmUFlowA+10;
		m_pPourUFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUFlowA));
	}
	
    g_devConfigInfo_Edt.devPourParam.unPourLFlowA = m_pPourLFlowA->text().toInt();
    //流量低保护值比至少和告警值一致
	if(g_devConfigInfo_Edt.devPourParam.unPourLFlowA > g_devConfigInfo.devAlmParam.unAlmLFlowA)
	{
		g_devConfigInfo_Edt.devPourParam.unPourLFlowA = g_devConfigInfo.devAlmParam.unAlmLFlowA;
		m_pPourLFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourLFlowA));
	}
    g_devConfigInfo_Edt.devPourParam.unPourUPresV = GetItemValue(m_pPourUPresV,10);
	g_devConfigInfo_Edt.devPourParam.unPourUSpeeV = m_pPourUSpeedV->text().toInt();
	g_devConfigInfo_Edt.devPourParam.unPourUFlowV = m_pPourUFlowV->text().toInt();
    g_devConfigInfo_Edt.devPourParam.unPourLFlowV = m_pPourLFlowV->text().toInt();
	
    g_devConfigInfo_Edt.devPourParam.unPourUWatTmp = GetItemValue(m_pPourUWatTmp,10);
    //水温保护值比告警值大1
	if(g_devConfigInfo_Edt.devPourParam.unPourUWatTmp < (g_devConfigInfo.devAlmParam.unAlmUWatTmp+10))
	{
		g_devConfigInfo_Edt.devPourParam.unPourUWatTmp = g_devConfigInfo.devAlmParam.unAlmUWatTmp+10;
		m_pPourUWatTmp->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUWatTmp,10,1));	
	}

	g_devConfigInfo_Edt.devPourParam.unPourWatLin = m_pPourUWatLin->text().toInt();//GetItemValue(m_pPourUWatLin,1);

    g_pCfgDataUI->AddGrpData(CFG_POUR_PRM_ITEM,\
                                sizeof(DevPourParam),\
                                (BYTE*)&g_devConfigInfo_Edt.devPourParam);
}
void PourConfigPanel::OnClickCancel(void)
{

}

void PourConfigPanel::OnUpdParams(void)
{
	m_pPourUPresA->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUPresA,10,1));	
	m_pPourUSpeedA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUSpeeA));
	m_pPourUFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUFlowA));
	m_pPourLFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourLFlowA));
	
	m_pPourUPresV->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUPresV,10,1));
	m_pPourUSpeedV->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUSpeeV));
	m_pPourUFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourUFlowV));
	m_pPourLFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourLFlowV));
	
	m_pPourUWatTmp->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourUWatTmp,10,1));
	//m_pPourUWatLin->setText(ValueToString(g_devConfigInfo_Edt.devPourParam.unPourWatLin,1,0));
	m_pPourUWatLin->setText(QString("%1").arg(g_devConfigInfo_Edt.devPourParam.unPourWatLin));
}


void PourConfigPanel::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void PourConfigPanel::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
        if(m_pCurLineEdit==m_pPourUPresA||m_pCurLineEdit==m_pPourUPresV||\
           m_pCurLineEdit==m_pPourUWatTmp)
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

void PourConfigPanel::OnFocusChanged(QWidget * old, QWidget * now)
{
    if( m_pPourUPresA == old ||\
        m_pPourUFlowA == old ||\
        m_pPourLFlowA == old ||\
        m_pPourUPresV == old ||\
        m_pPourUFlowV == old ||\
        m_pPourLFlowV == old ||\
        m_pPourUWatTmp== old ||\
        m_pPourUWatLin== old||\
        m_pPourUSpeedA== old||\
        m_pPourUSpeedV== old)
    {
        m_pCurLineEdit = old;
    }
}
