#include "Includes.h"
#include "watconfigpanel.h"
#include "CMonShareData.h"
#include <QtGui>
#include "SyszuxPinyin.h"
#include <QListWidget>
#include <QFormLayout>
#include <QComboBox>
#include <QDialogButtonBox>

WatConfigPanel::WatConfigPanel(QWidget *parent) :
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
    m_pWatDevList = new QListWidget;
    m_pWatDevList->setViewMode(QListView::ListMode);
    m_pWatDevList->setIconSize(QSize(20, 20));
    m_pWatDevList->setMovement(QListView::Static);
    m_pWatDevList->setMaximumWidth(150);
    m_pWatDevList->setSpacing(5);
    pDevsLayout->addWidget(m_pWatDevList);
    pLeftGrpBox->setLayout(pDevsLayout);

    pLeftGrpBox->setMaximumWidth(130);
    pRightGrpBox->setMinimumWidth(100);
    pMainLayout->addWidget(pLeftGrpBox);
    pMainLayout->addWidget(pMidGrpBox);
    pMainLayout->addWidget(pRightGrpBox);

    QFormLayout *formLayout = new QFormLayout;

    m_pDevID      = new QLineEdit(this);
    m_pDevEnabled = CreateComboBox(this);
    m_pDevEnabled->addItem(tr("禁用"));
    m_pDevEnabled->addItem(tr("启用"));
    m_pDevID->setReadOnly(true);

    long lEditWidth = 120;

    m_pDevID->setMinimumWidth(lEditWidth);
    m_pDevEnabled->setMinimumWidth(lEditWidth);
    m_pDevID->setMaximumWidth(lEditWidth);
    m_pDevEnabled->setMaximumWidth(lEditWidth);
    formLayout->addRow(tr("地址编号:"), m_pDevID);
    formLayout->addRow(tr("使用状态:"), m_pDevEnabled);
    m_pTmpVal = new QLineEdit(this);  //水浴温度设置值
    lEditWidth += 50;
    AddItem(formLayout,m_pTmpVal,tr("水浴温度:"),tr("(℃)"),lEditWidth);

    QLabel *pLabel = new QLabel(tr("--水浴设置值上限配置--"));
    pLabel->setMinimumSize(300,30);
    formLayout->addRow(tr(""),pLabel);
	
	m_pTmpValLimt = new QLineEdit(this);  //水浴温度设置值
	AddItem(formLayout,m_pTmpValLimt,tr("温度上限:"),tr("(℃)"),lEditWidth);

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

    connect(m_pWatDevList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,\
            SLOT(WatDevCurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    m_pWatDevList->setCurrentIndex(m_pWatDevList->model()->index(0,0));
}

void WatConfigPanel::CreateDevItems(void)
{
    for(long lDevItem = 0; lDevItem < 1; lDevItem++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(m_pWatDevList);
        configButton->setIcon(QIcon(":/images/config.png"));
        configButton->setText(QString("模块%1").arg(lDevItem+1,2,10,QLatin1Char('0')));
        configButton->setSizeHint(QSize(80,30));
        configButton->setTextAlignment(Qt::AlignCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

void WatConfigPanel::OnItemClick(QModelIndex  qModelIndex)
{
    long lDevItem = qModelIndex.row();
    if(-1==lDevItem)
    {
        return;
    }
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.watRooParam.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.watRooParam.unDevID));
    m_pTmpVal->setText(ValueToString(g_devConfigInfo_Edt.watRooParam.unTmpVal,10,1));

	m_pTmpValLimt->setText(ValueToString(g_devConfigInfo_Edt.watRooParam.unTmpValLimt,10,1));
}

void WatConfigPanel::WatDevCurrentItemChanged(QListWidgetItem*pCurItem,QListWidgetItem*pPreItem)
{
    long lDevItem = m_pWatDevList->row(pPreItem);
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
    }
    OnItemClick(m_pWatDevList->currentIndex());
}

void WatConfigPanel::OnClickOK(void)
{
    long lDevItem = m_pWatDevList->currentIndex().row();
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
        //保存禁用和启用
        g_pCfgDataUI->AddGrpData(CFG_WAT_ROOM_ITEM,\
                                sizeof(g_devConfigInfo_Edt.watRooParam),\
                                (BYTE*)&g_devConfigInfo_Edt.watRooParam);
    }
}
void WatConfigPanel::OnClickCancel(void)
{

}

void WatConfigPanel::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void WatConfigPanel::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
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

void WatConfigPanel::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pTmpVal == old ||\
	   m_pTmpValLimt == old)
    {
        m_pCurLineEdit = old;
    }
}
void WatConfigPanel::OnUpdParams(void)
{
    OnItemClick(m_pWatDevList->currentIndex());
}

void WatConfigPanel::UpdateItem(long lDevItem)
{
	OperLogWatDev operLogWatDev;
    
	operLogWatDev.unType = OPER_LOG_TYPE_WAT;
	operLogWatDev.unSite = 0;
	GetDateTime(&operLogWatDev.dtCreate);

    if(-1!=lDevItem)
    {
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
    }
}

