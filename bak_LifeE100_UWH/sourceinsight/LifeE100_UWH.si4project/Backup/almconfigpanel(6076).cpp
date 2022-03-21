#include "Includes.h"
#include "almconfigpanel.h"
#include "CMonShareData.h"
#include <QtGui>
#include "SyszuxPinyin.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>

AlmConfigPanel::AlmConfigPanel(QWidget *parent) :
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


    m_pAlmUPresA  = new QLineEdit(this);
	//m_pAlmLPresA  = new QLineEdit(this);
	m_pAlmUTmpA  = new QLineEdit(this);
    m_pAlmUFlowA  = new QLineEdit(this);
    m_pAlmLFlowA  = new QLineEdit(this);
	m_pAlmBubblA  = new QLineEdit(this);
	
    m_pAlmUPresV  = new QLineEdit(this);
	//m_pAlmLPresV  = new QLineEdit(this);
	m_pAlmUTmpV  = new QLineEdit(this);
    m_pAlmUFlowV  = new QLineEdit(this);
    m_pAlmLFlowV  = new QLineEdit(this);
	m_pAlmBubblV  = new QLineEdit(this);

	m_pAlmUWatTmp  = new QLineEdit(this);
	m_pAlmLWatLin  = new QLineEdit(this);
	m_pAlmUWatLin  = new QLineEdit(this);
	m_pAlmLBloodLin  = new QLineEdit(this);

	QFormLayout *formLayout = new QFormLayout;
	
    QLabel *pLabel = new QLabel(tr("--动脉泵告警配置--"));
    pLabel->setMinimumSize(300,30);
    formLayout->addRow(tr(""),pLabel);

    long lEditWidth = 160;

	/*
    AddItem(pFrmLayout,m_pAlmUPresA,tr("压力上限:"),tr("(mmHg)"),lEditWidth+60);
    AddItem(pFrmLayout,m_pAlmUFlowA,tr("流量上限:"),tr("(ml/min)"),lEditWidth+60);
    AddItem(pFrmLayout,m_pAlmLFlowA,tr("流量下限:"),tr("(ml/min)"),lEditWidth+60);
	AddItem(pFrmLayout,m_pAlmBubblA,tr("气泡上限:"),tr("(mm)"),lEditWidth+60);
*/
	QHBoxLayout* pFirstRow	= new QHBoxLayout();
	QFormLayout *pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUPresA,tr("压力上限:"),tr("(mmHg)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUTmpA,tr("血温上限:"),tr("(℃)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);
	
	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUFlowA,tr("流量上限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmLFlowA,tr("流量下限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);

	AddItem(formLayout,m_pAlmBubblA,tr("气泡上限:"),tr("(mm)"),lEditWidth);

    pLabel = new QLabel(tr("--静脉泵告警配置--"));
    pLabel->setMinimumSize(300,30);
    formLayout->addRow(tr(""),pLabel);
	/*
    AddItem(pFrmLayout,m_pAlmUPresV,tr("压力上限:"),tr("(mmHg)"),lEditWidth+60);
    AddItem(pFrmLayout,m_pAlmUFlowV,tr("流量上限:"),tr("(ml/min)"),lEditWidth+60);
    AddItem(pFrmLayout,m_pAlmLFlowV,tr("流量下限:"),tr("(ml/min)"),lEditWidth+60);	
	AddItem(pFrmLayout,m_pAlmBubblV,tr("气泡上限:"),tr("(mm)"),lEditWidth+60);	
*/
	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUPresV,tr("压力上限:"),tr("(mmHg)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUTmpV,tr("血温上限:"),tr("(℃)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);
	
	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUFlowV,tr("流量上限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmLFlowV,tr("流量下限:"),tr("(ml/min)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);
	
	AddItem(formLayout,m_pAlmBubblV,tr("气泡上限:"),tr("(mm)"),lEditWidth);

    pLabel = new QLabel(tr("--水浴告警配置--"));
    pLabel->setMinimumSize(300,30);
    formLayout->addRow(tr(""),pLabel);
	/*
	AddItem(pFrmLayout,m_pAlmUWatTmp,tr("温度上限:"),tr("(℃)"),lEditWidth+60);	
	AddItem(pFrmLayout,m_pAlmUWatLin,tr("水位上限:"),tr("( %)"),lEditWidth+60);
    AddItem(pFrmLayout,m_pAlmLWatLin,tr("水位下限:"),tr("( %)"),lEditWidth+60);
	AddItem(pFrmLayout,m_pAlmLBloodLin,tr("血位下限:"),tr("( %)"),lEditWidth+60);
*/
	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUWatTmp,tr("温度上限:"),tr("(℃)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmUWatLin,tr("水位上限:"),tr("( %)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	formLayout->addRow(pFirstRow);
	
	pFirstRow	= new QHBoxLayout();
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmLWatLin,tr("水位下限:"),tr("( %)"),lEditWidth);
	pFirstRow->addLayout(pFrmLayout);
	pFrmLayout = new QFormLayout;
	AddItem(pFrmLayout,m_pAlmLBloodLin,tr("血位下限:"),tr("( %)"),lEditWidth);
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

void AlmConfigPanel::OnClickOK(void)
{
	OperLogAlm operLogAlm;
	//long lGrpID = m_pGrpID->currentIndex();
	
	operLogAlm.unType = OPER_LOG_TYPE_ALM;
	operLogAlm.unSite = 0;
	GetDateTime(&operLogAlm.dtCreate);

	operLogAlm.unAlmUPresA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUPresA;
	operLogAlm.unAlmUPresA[1] = m_pAlmUPresA->text().toFloat()*10;
    //压力上限告警值比保护值小10
	if(operLogAlm.unAlmUPresA[1] > (g_devConfigInfo.devPourParam.unPourUPresA-50))
	{
		operLogAlm.unAlmUPresA[1] = g_devConfigInfo.devPourParam.unPourUPresA-50;
	}
	
	operLogAlm.unAlmUTmpA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA;
	operLogAlm.unAlmUTmpA[1] = m_pAlmUTmpA->text().toFloat()*10;
    //水温上限告警值比保护值小10
	if(operLogAlm.unAlmUTmpA[1] > (g_devConfigInfo.devPourParam.unPourUWatTmp-10))
	{
		operLogAlm.unAlmUTmpA[1] = g_devConfigInfo.devPourParam.unPourUWatTmp-10;
	}
	
	operLogAlm.unAlmUFlowA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA;
	operLogAlm.unAlmUFlowA[1] = m_pAlmUFlowA->text().toInt();
    //流量上限告警值比保护值小10
	if(operLogAlm.unAlmUFlowA[1] > (g_devConfigInfo.devPourParam.unPourUFlowA-10))
	{
		operLogAlm.unAlmUFlowA[1] = g_devConfigInfo.devPourParam.unPourUFlowA-10;
	}
	operLogAlm.unAlmLFlowA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA;
	operLogAlm.unAlmLFlowA[1] = m_pAlmLFlowA->text().toInt();
    //流量下限告警值至少不小于保护值
	if(operLogAlm.unAlmLFlowA[1] < g_devConfigInfo.devPourParam.unPourLFlowA)
	{
		operLogAlm.unAlmLFlowA[1] = g_devConfigInfo.devPourParam.unPourLFlowA;
	}
	operLogAlm.unAlmBubbleA[0] = g_devConfigInfo_Edt.devAlmParam.unAlmBubbleA;
	operLogAlm.unAlmBubbleA[1] = m_pAlmBubblA->text().toInt();

	operLogAlm.unAlmUPresV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUPresV;
	operLogAlm.unAlmUPresV[1] = m_pAlmUPresV->text().toFloat()*10;

	operLogAlm.unAlmUTmpV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV;
	operLogAlm.unAlmUTmpV[1] = m_pAlmUTmpV->text().toFloat()*10;
    //水温上限告警值比保护值小10
	if(operLogAlm.unAlmUTmpV[1] > (g_devConfigInfo.devPourParam.unPourUWatTmp-10))
	{
		operLogAlm.unAlmUTmpV[1] = g_devConfigInfo.devPourParam.unPourUWatTmp-10;
	}
	
	operLogAlm.unAlmUFlowV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV;
    operLogAlm.unAlmUFlowV[1] = m_pAlmUFlowV->text().toInt();
	operLogAlm.unAlmLFlowV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV;
	operLogAlm.unAlmLFlowV[1] = m_pAlmLFlowV->text().toInt();
	operLogAlm.unAlmBubbleV[0] = g_devConfigInfo_Edt.devAlmParam.unAlmBubbleV;
	operLogAlm.unAlmBubbleV[1] = m_pAlmBubblV->text().toInt();

	operLogAlm.unAlmUWatTmp[0] = g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp;
	operLogAlm.unAlmUWatTmp[1] = m_pAlmUWatTmp->text().toFloat()*10;
    //水温上限告警值比保护值小10
	if(operLogAlm.unAlmUWatTmp[1] > (g_devConfigInfo.devPourParam.unPourUWatTmp-10))
	{
		operLogAlm.unAlmUWatTmp[1] = g_devConfigInfo.devPourParam.unPourUWatTmp-10;
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
    g_devConfigInfo_Edt.devAlmParam.unAlmUPresA = GetItemValue(m_pAlmUPresA,10);
    //压力上限告警值比保护值小10
	if(g_devConfigInfo_Edt.devAlmParam.unAlmUPresA > (g_devConfigInfo.devPourParam.unPourUPresA-50))
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmUPresA = g_devConfigInfo.devPourParam.unPourUPresA-50;
		m_pAlmUPresA->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresA,10,1));
	}
	
    g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA = GetItemValue(m_pAlmUTmpA,10);
    //血温上限告警值比保护值小10
	if(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA > (g_devConfigInfo.devPourParam.unPourUTmpA-10))
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA = g_devConfigInfo.devPourParam.unPourUTmpA-10;
		m_pAlmUTmpA->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA,10,1));
	}
	
	g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA = m_pAlmUFlowA->text().toInt();
    //流量上限告警值比保护值小10
	if(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA > (g_devConfigInfo.devPourParam.unPourUFlowA-10))
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA = g_devConfigInfo.devPourParam.unPourUFlowA-10;
		m_pAlmUFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA));
	}
    g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA = m_pAlmLFlowA->text().toInt();
    //流量下限告警值至少不小于保护值
	if(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA < g_devConfigInfo.devPourParam.unPourLFlowA)
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA = g_devConfigInfo.devPourParam.unPourLFlowA;
		m_pAlmLFlowA->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA));
	}
	g_devConfigInfo_Edt.devAlmParam.unAlmBubbleA = m_pAlmBubblA->text().toInt();

//---------------------静脉-------------------------------
    g_devConfigInfo_Edt.devAlmParam.unAlmUPresV = GetItemValue(m_pAlmUPresV,10);
    //压力上限告警值比保护值小10
	if(g_devConfigInfo_Edt.devAlmParam.unAlmUPresV > (g_devConfigInfo.devPourParam.unPourUPresV-20))
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmUPresV = g_devConfigInfo.devPourParam.unPourUPresV-20;
		m_pAlmUPresV->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresV,10,1));
	}
	
    g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV = GetItemValue(m_pAlmUTmpV,10);
    //血温上限告警值比保护值小10
	if(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV > (g_devConfigInfo.devPourParam.unPourUTmpV-10))
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV = g_devConfigInfo.devPourParam.unPourUTmpV-10;
		m_pAlmUTmpV->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV,10,1));
	}
	
	g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV = m_pAlmUFlowV->text().toInt();
    //流量上限告警值比保护值小10
	if(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV > (g_devConfigInfo.devPourParam.unPourUFlowV-10))
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV = g_devConfigInfo.devPourParam.unPourUFlowV-10;
		m_pAlmUFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV));
	}
    g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV = m_pAlmLFlowV->text().toInt();
    //流量下限告警值至少不小于保护值
	if(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV < g_devConfigInfo.devPourParam.unPourLFlowV)
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV = g_devConfigInfo.devPourParam.unPourLFlowV;
		m_pAlmLFlowV->setText(QString("%1").arg(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV));
	}
	g_devConfigInfo_Edt.devAlmParam.unAlmBubbleV = m_pAlmBubblV->text().toInt();
	
    g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp = GetItemValue(m_pAlmUWatTmp,10);
    //水温上限告警值比保护值小1
	if(g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp > (g_devConfigInfo.devPourParam.unPourUWatTmp-10))
	{
		g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp = g_devConfigInfo.devPourParam.unPourUWatTmp-10;
		m_pAlmUWatTmp->setText(ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp,10,1));
	}
	g_devConfigInfo_Edt.devAlmParam.unAlmUWatLin = m_pAlmUWatLin->text().toInt();
	g_devConfigInfo_Edt.devAlmParam.unAlmLWatLin = m_pAlmLWatLin->text().toInt();
	g_devConfigInfo_Edt.devAlmParam.unAlmBloodLin = m_pAlmLBloodLin->text().toInt();

    g_pCfgDataUI->AddGrpData(CFG_ALM_PRM_ITEM,\
                                sizeof(DevAlmParam),\
                                (BYTE*)&g_devConfigInfo_Edt.devAlmParam);
}
void AlmConfigPanel::OnClickCancel(void)
{

}

void AlmConfigPanel::OnUpdParams(void)
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


void AlmConfigPanel::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void AlmConfigPanel::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
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

void AlmConfigPanel::OnFocusChanged(QWidget * old, QWidget * now)
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
