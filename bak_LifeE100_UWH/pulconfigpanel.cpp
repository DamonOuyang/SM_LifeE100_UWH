#include "Includes.h"
#include "pulconfigpanel.h"
#include "CMonShareData.h"
#include <QtGui>
#include "SyszuxPinyin.h"
#include <QListWidget>
#include <QFormLayout>
#include <QComboBox>
#include <QDialogButtonBox>

PulConfigPanel::PulConfigPanel(QWidget *parent) :
    QFrame(parent)
{
    m_pCurLineEdit = NULL;
    QHBoxLayout* pMainLayout = new QHBoxLayout();
    setLayout(pMainLayout);


    QGroupBox* pLeftGrpBox  = CreateGroupBox();
    QGroupBox* pMidGrpBox   = CreateGroupBox();
    pLeftGrpBox->setTitle(tr("模块选项"));
    pMidGrpBox->setTitle(tr(""));

    QGroupBox* pRightGrpBox = new QGroupBox();
    QVBoxLayout* pDevsLayout = new QVBoxLayout();
    m_pPulDevList = new QListWidget;
    m_pPulDevList->setViewMode(QListView::ListMode);
    m_pPulDevList->setIconSize(QSize(20, 20));
    m_pPulDevList->setMovement(QListView::Static);
    m_pPulDevList->setMaximumWidth(150);
    m_pPulDevList->setSpacing(5);
    pDevsLayout->addWidget(m_pPulDevList);
    pLeftGrpBox->setLayout(pDevsLayout);

    pLeftGrpBox->setMaximumWidth(130);
    pRightGrpBox->setMinimumWidth(100);
    pMainLayout->addWidget(pLeftGrpBox);
    pMainLayout->addWidget(pMidGrpBox);
    pMainLayout->addWidget(pRightGrpBox);

    QFormLayout *formLayout = new QFormLayout;

    m_pDevEnabled = CreateComboBox(this);
    m_pDevEnabled->addItem(tr("关闭"));
    m_pDevEnabled->addItem(tr("启用"));

    long lEditWidth = 120;

    m_pDevEnabled->setMinimumWidth(lEditWidth);
    m_pDevEnabled->setMaximumWidth(lEditWidth);
    formLayout->addRow(tr("使用状态:"), m_pDevEnabled);
	
    m_pPulVal = new QLineEdit(this);  //动脉血泵压搏动频率设置值
    m_pPulFreq = new QLineEdit(this);  //动脉血泵搏动范围设置值
    
    m_pPulVal->setMinimumWidth(lEditWidth);
    m_pPulVal->setMaximumWidth(lEditWidth);
    m_pPulFreq->setMinimumWidth(lEditWidth);
    m_pPulFreq->setMaximumWidth(lEditWidth);
	
	formLayout->addRow(tr("搏动范围:"), m_pPulVal);
	formLayout->addRow(tr("搏动频率:"), m_pPulFreq);
    //lEditWidth += 50;
    //AddItem(formLayout,m_pPress,tr("搏动频率:"),tr(" "),lEditWidth);
	//AddItem(formLayout,m_pSpeed,tr("搏动范围:"),tr(" "),lEditWidth);


    pMidGrpBox->setLayout(formLayout);

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
    CreateDevItems();

    connect(m_pPulDevList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,\
            SLOT(PulDevCurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    m_pPulDevList->setCurrentIndex(m_pPulDevList->model()->index(0,0));
}

void PulConfigPanel::CreateDevItems(void)
{
    for(long lDevItem = 0; lDevItem < 1; lDevItem++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(m_pPulDevList);
        configButton->setIcon(QIcon(":/images/config.png"));
        configButton->setText(QString("模块%1").arg(lDevItem+1,2,10,QLatin1Char('0')));
        configButton->setSizeHint(QSize(80,30));
        configButton->setTextAlignment(Qt::AlignCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

void PulConfigPanel::OnItemClick(QModelIndex  qModelIndex)
{
    long lDevItem = qModelIndex.row();
    if(-1==lDevItem)
    {
        return;
    }
    m_pDevEnabled->setCurrentIndex(g_setPulPrm.unPumType);
    m_pPulVal->setText(ValueToString(g_setPulPrm.unPulVal,10,1));
	m_pPulFreq->setText(ValueToString(g_setPulPrm.unPulFreq,1,0));
}

void PulConfigPanel::PulDevCurrentItemChanged(QListWidgetItem*pCurItem,QListWidgetItem*pPreItem)
{
    long lDevItem = m_pPulDevList->row(pPreItem);
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
    }
    OnItemClick(m_pPulDevList->currentIndex());
}

void PulConfigPanel::OnClickOK(void)
{
    long lDevItem = m_pPulDevList->currentIndex().row();
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
        //保存禁用和启用
        g_devUpdFlags.bPulSetFlag = true;
    }
}
void PulConfigPanel::OnClickCancel(void)
{

}

void PulConfigPanel::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void PulConfigPanel::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
        if(m_pPulVal == m_pCurLineEdit)
        {
            dlgInputPanel.SetInputMask(QString("00.0"));
        }
		else if(m_pPulFreq == m_pCurLineEdit)
		{
		    dlgInputPanel.SetInputMask(QString("00"));
		}
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void PulConfigPanel::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pPulFreq == old ||\
	   m_pPulVal == old)
    {
        m_pCurLineEdit = old;
    }
}
void PulConfigPanel::OnUpdParams(void)
{
    OnItemClick(m_pPulDevList->currentIndex());
}

void PulConfigPanel::UpdateItem(long lDevItem)
{
	OperLogPumDev operLogPulPrm;
    
	operLogPulPrm.unType = OPER_LOG_TYPE_PUL;
	operLogPulPrm.unSite = 0;
	GetDateTime(&operLogPulPrm.dtCreate);

    if(-1!=lDevItem)
    {
		operLogPulPrm.unEnFlag[0] = g_setPulPrm.unPumType;
		operLogPulPrm.unEnFlag[1] = m_pDevEnabled->currentIndex();
		operLogPulPrm.unPress[0] = g_setPulPrm.unPulVal;
		operLogPulPrm.unPress[1] = m_pPulVal->text().toFloat()*10;
		
		operLogPulPrm.unSpeed[0] = g_setPulPrm.unPulFreq;
		operLogPulPrm.unSpeed[1] = m_pPulFreq->text().toInt();
		
		SaveOperLogData((const char*)&operLogPulPrm, sizeof(OperLogPumDev));
		SaveOperLogInfo();


        g_setPulPrm.unPumType  = m_pDevEnabled->currentIndex();
    	g_setPulPrm.unPulVal = GetItemValue(m_pPulVal,10);
		g_setPulPrm.unPulFreq = GetItemValue(m_pPulFreq,1);
    }
}

