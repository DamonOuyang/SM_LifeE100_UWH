#include "includes.h"
#include "cconfigpanel.h"
#include "basicconfigpanel.h"
#include "almconfigpanel.h"
#include "pourconfigpanel.h"
#include "watconfigpanel.h"
#include "pumpAconfigpanel.h"
#include "pumpVconfigpanel.h"
#include "pulconfigpanel.h"

#include "cshowinfopanel.h"
#include <QSplitter>
#include <QGroupBox>
#include <QListView>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QStackedWidget>
//#include "cshowinfopanel.h"

#include "CMonShareData.h"
#include <QtGui>
#include "cworkthread.h"
//#include "systemsetdialog.h"
#include "cpassworddlg.h"



#define BSC_TAB_INDEX  0x00
#define ALM_TAB_INDEX  0x01
#define POUR_TAB_INDEX  0x02
#define WAT_DEV_TAB_INDEX   0x03
#define APUM_DEV_TAB_INDEX  0x04
#define VPUM_DEV_TAB_INDEX  0x05
#define PUL_PRM_TAB_INDEX   0x06

#define INFO_PANEL_INDEX    0x07
/*

#define BSC_TAB_INDEX  0x00
#define ALM_TAB_INDEX  0x01
#define WAT_DEV_TAB_INDEX   0x02
#define APUM_DEV_TAB_INDEX  0x03
#define VPUM_DEV_TAB_INDEX  0x04
*/

CConfigPanel::CConfigPanel(QWidget *parent) :
    QFrame(parent)
{
    QSplitter*  pSpiltter = new QSplitter();
    QGroupBox*  pLeftGrp  = CreateGroupBox();
    QGroupBox*  pRightGrp = CreateGroupBox();

    pLeftGrp->setTitle(tr("配置选项"));
    pRightGrp->setTitle(tr("配置界面"));
    m_pListView  = new QListView();
    m_pListView->setMaximumSize(210,600);
    m_pListView->setSpacing(10);
    m_pListView->setGridSize(QSize(120,50));
    QHBoxLayout* pMainLayout     = new QHBoxLayout();
    QHBoxLayout* pLeftLayout     = new QHBoxLayout();
    QStackedLayout* pRightLayout = new QStackedLayout();
    pLeftLayout->addWidget(m_pListView);
    pLeftGrp->setLayout(pLeftLayout);
    pRightGrp->setLayout(pRightLayout);
    pSpiltter->addWidget(pLeftGrp);
    pSpiltter->addWidget(pRightGrp);

    pMainLayout->addWidget(pSpiltter);
    this->setLayout(pMainLayout);

    QList<int> listSplitterSize;
    listSplitterSize.append(120);
    listSplitterSize.append(500);
    pSpiltter->setSizes(listSplitterSize);

    QStandardItemModel* pModel = new QStandardItemModel(this);
    QStandardItem *parentItem = pModel->invisibleRootItem();
    QStandardItem *pItem;
    QStringList  strItems;
    strItems<<tr("基本--配置");
    strItems<<tr("告警--配置");
	strItems<<tr("灌注--配置");
    strItems<<tr("水浴--模块");
    strItems<<tr("血泵--动脉");
    strItems<<tr("血泵--静脉");
	strItems<<tr("血泵--脉搏");
    strItems<<tr("调试信息");

    for (long lItemIndex = 0; lItemIndex < strItems.count(); lItemIndex++)
    {
        pItem = new QStandardItem(strItems.at(lItemIndex));
        pItem->setSizeHint(QSize(100,50));
        parentItem->appendRow(pItem);
    }

    m_pListView->setModel(pModel);
    m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_pListView,\
            SIGNAL(clicked(const QModelIndex&)),\
           this,SLOT(OnItemChanged(const QModelIndex&)));


    m_pPagesWidget = new QStackedWidget;
    m_pPagesWidget->addWidget(new BasicConfigPanel(this));
    m_pPagesWidget->addWidget(new AlmConfigPanel);
	m_pPagesWidget->addWidget(new PourConfigPanel);
    m_pPagesWidget->addWidget(new WatConfigPanel);
    m_pPagesWidget->addWidget(new PumAConfigPanel);
    m_pPagesWidget->addWidget(new PumVConfigPanel);
	m_pPagesWidget->addWidget(new PulConfigPanel);

	m_pPagesWidget->addWidget(new CShowInfoPanel);

	
    
    pRightLayout->addWidget(m_pPagesWidget);
    m_pPagesWidget->setCurrentIndex(INFO_PANEL_INDEX);
    m_pListView->selectionModel()->setCurrentIndex(\
		         m_pListView->model()->index(INFO_PANEL_INDEX,0),\
		         QItemSelectionModel::Select);
    //m_pUpdTimer = new QTimer(this);
    //connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnUpdData(void)));
    //m_pUpdTimer->start(1000);
}

//每次进入系统配置刷新子设备配置参数
void CConfigPanel::FlashSubDevPrm(void)
{
    OnUpdData();
}

void CConfigPanel::OnItemChanged(const QModelIndex & index )
{

    m_pPagesWidget->setCurrentIndex(index.row());
	if(INFO_PANEL_INDEX != index.row())
	{
		if(true==g_pwdCfgInfo.bPwdEnFlg&&true==g_bLoginFlag)
		{
			g_bLoginFlag = false;
			CPasswordDlg  pwdDlg(this,false);
			//pwdDlg.resize(500,300);
			if(QDialog::Rejected==pwdDlg.exec())
			{
				m_pPagesWidget->setCurrentIndex(INFO_PANEL_INDEX);
				m_pListView->selectionModel()->setCurrentIndex(\
					         m_pListView->model()->index(INFO_PANEL_INDEX,0),\
					         QItemSelectionModel::ClearAndSelect);
				g_bLoginFlag = true;
			}
		}
	}
}

void CConfigPanel::OnUpdData(void)
{
    printf("Entr CConfigPanel::OnUpdData \r\n");
    UINT32 unItemIndex;
    UINT32 unDataLen;
	

    g_pCfgDataNwk->GetGrpData(unItemIndex,\
                                unDataLen,\
                                (BYTE*)&g_devConfigInfo_Edt.basicCfgInfo);
    ((BasicConfigPanel*)(m_pPagesWidget->widget(BSC_TAB_INDEX)))->OnUpdParams();


    g_pCfgDataNwk->GetGrpData(unItemIndex,\
                                unDataLen,\
                                (BYTE*)&g_devConfigInfo_Edt.watRooParam);
    ((WatConfigPanel*)(m_pPagesWidget->widget(WAT_DEV_TAB_INDEX)))->OnUpdParams();

    g_pCfgDataNwk->GetGrpData(unItemIndex,\
                                unDataLen,\
                                (BYTE*)&g_devConfigInfo_Edt.arteryParm);
    ((PumAConfigPanel*)(m_pPagesWidget->widget(APUM_DEV_TAB_INDEX)))->OnUpdParams();

    g_pCfgDataNwk->GetGrpData(unItemIndex,\
                                unDataLen,\
                                (BYTE*)&g_devConfigInfo_Edt.veinParm);
    ((PumVConfigPanel*)(m_pPagesWidget->widget(VPUM_DEV_TAB_INDEX)))->OnUpdParams();
	

    ((PulConfigPanel*)(m_pPagesWidget->widget(PUL_PRM_TAB_INDEX)))->OnUpdParams();	
}

void CConfigPanel::ExitLoginFun(void)
{
    printf("entr CConfigPanel::ExitLogin \r\n");
	m_pPagesWidget->setCurrentIndex(INFO_PANEL_INDEX);
	m_pListView->selectionModel()->setCurrentIndex(\
				 m_pListView->model()->index(INFO_PANEL_INDEX,0),\
				 QItemSelectionModel::ClearAndSelect);
}

