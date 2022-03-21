#include "Includes.h"
#include "pumpVconfigpanel.h"
#include "CMonShareData.h"
#include <QtGui>
#include "SyszuxPinyin.h"

PumVConfigPanel::PumVConfigPanel(QWidget *parent) :
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
    m_pPumVDevList = new QListWidget;
    m_pPumVDevList->setViewMode(QListView::ListMode);
    m_pPumVDevList->setIconSize(QSize(20, 20));
    m_pPumVDevList->setMovement(QListView::Static);
    m_pPumVDevList->setMaximumWidth(150);
    m_pPumVDevList->setSpacing(5);
    pDevsLayout->addWidget(m_pPumVDevList);
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
	
    m_pPress = new QLineEdit(this);  //动脉血泵压力设置值
    m_pSpeed = new QLineEdit(this);  //动脉血泵转速设置值
    lEditWidth += 50;
    AddItem(formLayout,m_pPress,tr("血泵压力:"),tr("(mmHg)"),lEditWidth);
	AddItem(formLayout,m_pSpeed,tr("血泵转速:"),tr("( RPM)"),lEditWidth);


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

    connect(m_pPumVDevList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,\
            SLOT(PumDevCurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    m_pPumVDevList->setCurrentIndex(m_pPumVDevList->model()->index(0,0));
}

void PumVConfigPanel::CreateDevItems(void)
{
    for(long lDevItem = 0; lDevItem < 1; lDevItem++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(m_pPumVDevList);
        configButton->setIcon(QIcon(":/images/config.png"));
        configButton->setText(QString("模块%1").arg(lDevItem+1,2,10,QLatin1Char('0')));
        configButton->setSizeHint(QSize(80,30));
        configButton->setTextAlignment(Qt::AlignCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

void PumVConfigPanel::OnItemClick(QModelIndex  qModelIndex)
{
    long lDevItem = qModelIndex.row();
    if(-1==lDevItem)
    {
        return;
    }
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.veinParm.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.veinParm.unDevID));
    m_pPress->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unPress,10,1));
	m_pSpeed->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unSpeed,10,1));
}

void PumVConfigPanel::PumDevCurrentItemChanged(QListWidgetItem*pCurItem,QListWidgetItem*pPreItem)
{
    long lDevItem = m_pPumVDevList->row(pPreItem);
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
    }
    OnItemClick(m_pPumVDevList->currentIndex());
}

void PumVConfigPanel::OnClickOK(void)
{
    long lDevItem = m_pPumVDevList->currentIndex().row();
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
        //保存禁用和启用
        g_pCfgDataUI->AddGrpData(CFG_VEIN_PRS_ITEM,\
                                sizeof(g_devConfigInfo_Edt.veinParm),\
                                (BYTE*)&g_devConfigInfo_Edt.veinParm);
    }
}
void PumVConfigPanel::OnClickCancel(void)
{

}

void PumVConfigPanel::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void PumVConfigPanel::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
        if(m_pPress == m_pCurLineEdit||\
		   m_pSpeed == m_pCurLineEdit)
        {
            dlgInputPanel.SetInputMask(QString("0000.0"));
        }
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void PumVConfigPanel::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pPress == old ||\
	   m_pSpeed == old)
    {
        m_pCurLineEdit = old;
    }
}
void PumVConfigPanel::OnUpdParams(void)
{
    OnItemClick(m_pPumVDevList->currentIndex());
}

void PumVConfigPanel::UpdateItem(long lDevItem)
{
    if(-1!=lDevItem)
    {
        g_devConfigInfo_Edt.veinParm.unEnFlag  = m_pDevEnabled->currentIndex();
    	g_devConfigInfo_Edt.veinParm.unPress = GetItemValue(m_pPress,10);
		g_devConfigInfo_Edt.veinParm.unSpeed = GetItemValue(m_pSpeed,10);
    }
}

