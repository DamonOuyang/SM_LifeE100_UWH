#include "Includes.h"
#include "pumpAconfigpanel.h"
#include "CMonShareData.h"
#include <QtGui>
#include "SyszuxPinyin.h"
#include <QListWidget>
#include <QFormLayout>
#include <QComboBox>
#include <QDialogButtonBox>

PumAConfigPanel::PumAConfigPanel(QWidget *parent) :
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
    m_pPumADevList = new QListWidget;
    m_pPumADevList->setViewMode(QListView::ListMode);
    m_pPumADevList->setIconSize(QSize(20, 20));
    m_pPumADevList->setMovement(QListView::Static);
    m_pPumADevList->setMaximumWidth(150);
    m_pPumADevList->setSpacing(5);
    pDevsLayout->addWidget(m_pPumADevList);
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

    connect(m_pPumADevList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,\
            SLOT(PumDevCurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    m_pPumADevList->setCurrentIndex(m_pPumADevList->model()->index(0,0));
}

void PumAConfigPanel::CreateDevItems(void)
{
    for(long lDevItem = 0; lDevItem < 1; lDevItem++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(m_pPumADevList);
        configButton->setIcon(QIcon(":/images/config.png"));
        configButton->setText(QString("模块%1").arg(lDevItem+1,2,10,QLatin1Char('0')));
        configButton->setSizeHint(QSize(80,30));
        configButton->setTextAlignment(Qt::AlignCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

void PumAConfigPanel::OnItemClick(QModelIndex     qModelIndex)
{
    long lDevItem = qModelIndex.row();
    if(-1==lDevItem)
    {
        return;
    }
    m_pDevEnabled->setCurrentIndex(g_devConfigInfo_Edt.arteryParm.unEnFlag);
    m_pDevID->setText(QString("%1").arg(g_devConfigInfo_Edt.arteryParm.unDevID));
    m_pPress->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unPress,10,1));
	m_pSpeed->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unSpeed,1,0));
}

void PumAConfigPanel::PumDevCurrentItemChanged(QListWidgetItem*pCurItem,QListWidgetItem*pPreItem)
{
    long lDevItem = m_pPumADevList->row(pPreItem);
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
    }
    OnItemClick(m_pPumADevList->currentIndex());
}

void PumAConfigPanel::OnClickOK(void)
{
    long lDevItem = m_pPumADevList->currentIndex().row();
    if(-1!=lDevItem)
    {
        UpdateItem(lDevItem);
		OnUpdParams();
        //保存禁用和启用
        g_pCfgDataUI->AddGrpData(CFG_ARTERY_PRS_ITEM,\
                                sizeof(g_devConfigInfo_Edt.arteryParm),\
                                (BYTE*)&g_devConfigInfo_Edt.arteryParm);
    }
}
void PumAConfigPanel::OnClickCancel(void)
{

}

void PumAConfigPanel::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void PumAConfigPanel::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
        if(m_pPress == m_pCurLineEdit)
        {
            dlgInputPanel.SetInputMask(QString("000.0"));
        }
		else if(m_pSpeed == m_pCurLineEdit)
		{
		    dlgInputPanel.SetInputMask(QString("0000"));
		}
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void PumAConfigPanel::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pPress == old ||\
	   m_pSpeed == old)
    {
        m_pCurLineEdit = old;
    }
}
void PumAConfigPanel::OnUpdParams(void)
{
    OnItemClick(m_pPumADevList->currentIndex());
}

void PumAConfigPanel::UpdateItem(long lDevItem)
{
	OperLogPumDev operLogPumDev;
    
	operLogPumDev.unType = OPER_LOG_TYPE_PUM;
	operLogPumDev.unSite = 0;
	GetDateTime(&operLogPumDev.dtCreate);

    if(-1!=lDevItem)
    {
		operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.arteryParm.unEnFlag;
		operLogPumDev.unEnFlag[1] = m_pDevEnabled->currentIndex();
		operLogPumDev.unPress[0] = g_devConfigInfo_Edt.arteryParm.unPress;
		operLogPumDev.unPress[1] = m_pPress->text().toFloat()*10;
		operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.arteryParm.unSpeed;
		operLogPumDev.unSpeed[1] = m_pSpeed->text().toInt();
		
		operLogPumDev.unPress[1] = operLogPumDev.unPress[1]/10;
		operLogPumDev.unPress[1] *= 10;
		SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
		SaveOperLogInfo();


        g_devConfigInfo_Edt.arteryParm.unEnFlag  = m_pDevEnabled->currentIndex();
    	g_devConfigInfo_Edt.arteryParm.unPress = GetItemValue(m_pPress,10);
		g_devConfigInfo_Edt.arteryParm.unSpeed = GetItemValue(m_pSpeed,1);

		g_devConfigInfo_Edt.arteryParm.unPress = g_devConfigInfo_Edt.arteryParm.unPress/10;
		g_devConfigInfo_Edt.arteryParm.unPress*=10;
    }
}

