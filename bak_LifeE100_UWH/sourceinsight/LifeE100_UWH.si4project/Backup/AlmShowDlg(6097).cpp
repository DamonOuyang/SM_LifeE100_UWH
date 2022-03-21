#include "Includes.h"
#include "AlmShowDlg.h"
#include <QtGui>
#include "fcntl.h"
#include  <sys/wait.h>
#include  <errno.h>
#include  <signal.h>
#include "unistd.h"
#include <sys/types.h>
#include <sys/timeb.h>
#include <dirent.h>
#include <sys/stat.h>
#include "CAlarmDataFile.h"
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>

AlmShowDlg::AlmShowDlg(QWidget *parent) :
    QDialog(parent)
{
    m_lFileDataPos = 0;
    m_lRowIndex    = 0;

    m_pTabWidget  = new QTabWidget(this);
	
    m_pTabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab \n"
	"{	min-width:100px;min-height:50px;color: white;\n"
	"font-family:simhei;\n"
	"font:bold;\n"
    "font:20px;\n"
	"\n"
	"}\n"
	"QTabBar::tab:selected\n"
	"{   \n"
	"  background-color: rgb(86,93,113);\n"
	"	color: rgb(255, 255, 255);\n"
	"	padding:0px;\n"
	"}\n"
	"\n"
	"QTabBar::tab:!selected \n"
	"{\n"
	"   background-color: rgb(225,230,236);\n"
	"	color: rgb(200, 206, 214);\n"
	"	padding:0px;\n"
	"}\n"
	"\n"
	""));	

    m_pRTAlmTab   = new QWidget(this);
    m_pDataAlmTab = new QWidget(this);
    m_pTabWidget->addTab(m_pRTAlmTab, tr("当前告警"));
    m_pTabWidget->addTab(m_pDataAlmTab, tr("历史告警"));

    m_pButBox = new QDialogButtonBox(Qt::Horizontal);

    QPushButton* pDelBut  = new QPushButton(tr("删除"),this);
    pDelBut->setMinimumSize(100,30);
    m_pButBox->addButton(pDelBut,QDialogButtonBox::ActionRole);

    QPushButton* pOkBut = new QPushButton(tr("关闭"),this);
    pOkBut->setMinimumSize(100,30);
    m_pButBox->addButton(pOkBut, QDialogButtonBox::ActionRole);
    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pDelBut,SIGNAL(clicked()),this,SLOT(OnDelAlmItem()));

    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    pMainLayout->addWidget(m_pTabWidget);
    pMainLayout->addWidget(m_pButBox);
    setLayout(pMainLayout);

    AddRTAlarmTab();
    AddDataAlarmTab();

    setWindowTitle("－－－－－设备告警信息列表－－－－－");
    m_bFreeFlag = true;
}
AlmShowDlg::~AlmShowDlg()
{
    ReleaseAll();
}

void AlmShowDlg::AddRTAlarmTab(void)
{
    QVBoxLayout*  pMainLayout = new QVBoxLayout();
    m_pRTAlmTab->setLayout(pMainLayout);

    m_pRTAlmTabView  = new QTableView(this);
    pMainLayout->addWidget(m_pRTAlmTabView);

    m_pRTAlmTabView->setColumnWidth(0,400);
    m_pRTItemModel = new QStandardItemModel(this);
    m_pRTAlmTabView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pRTAlmTabView->setModel(m_pRTItemModel);
    m_pRTAlmTabView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pRTAlmTabView->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pRTAlmTabView->setSortingEnabled(true);
    //m_pRTAlmTabView->horizontalHeader()->setClickable(true);
    m_pRTAlmTabView->horizontalHeader()->setSortIndicatorShown(true);

    QStringList strColNames;
    strColNames<<"告警项目"<<"当前值"<<"告警条件";

    long lColSizes[3];
    lColSizes[0] = 300;
    lColSizes[1] = 100;
    lColSizes[2] = 100;
    long lColIndex;
    m_pRTItemModel->setHorizontalHeaderLabels(strColNames);
    for(lColIndex = 0; lColIndex < (long)m_pRTItemModel->columnCount();lColIndex++)
    {
        m_pRTAlmTabView->setColumnWidth(lColIndex,lColSizes[lColIndex]);
    }
    UpDateRTAlmInfos();
}

void AlmShowDlg::AddDataAlarmTab(void)
{
    QVBoxLayout*  pMainLayout = new QVBoxLayout();
    m_pDataAlmTab->setLayout(pMainLayout);

    m_pInfoView  = new QTableView(this);
    pMainLayout->addWidget(m_pInfoView);

    m_pInfoView->setColumnWidth(0,400);
    m_pAlmItemModel = new QStandardItemModel(this);
    m_pInfoView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pInfoView->setModel(m_pAlmItemModel);
    m_pInfoView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pInfoView->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pInfoView->setSortingEnabled(true);
    //m_pInfoView->horizontalHeader()->setClickable(true);
    m_pInfoView->horizontalHeader()->setSortIndicatorShown(true);

    m_strColNames <<"告警类别"<<"对象ID"<<"子对象"<<"发生时间"<<"状态"<<"告警值";

    m_lColSizes[0] = 300;
    m_lColSizes[1] = 60;
    m_lColSizes[2] = 60;
    m_lColSizes[3] = 200;
    m_lColSizes[4] = 50;
    m_lColSizes[5] = 100;

    m_pAlmItemModel->setHorizontalHeaderLabels(m_strColNames);
    m_strFilePath  = qApp->applicationDirPath()+"/";
    m_strFilePath += g_devConfigInfo.basicCfgInfo.strLogPath;
    m_strFilePath += ALM_FILE_NAME;
    ShowAlarmInfos();
}

void AlmShowDlg::ShowAlarmInfos(void)
{
    long lColIndex;
    QStandardItemModel* pItemModel;
    pItemModel = (QStandardItemModel*)m_pInfoView->model();
    for(lColIndex = 0; lColIndex < (long)pItemModel->columnCount();lColIndex++)
    {
        m_pInfoView->setColumnWidth(lColIndex,m_lColSizes[lColIndex]);
    }
    ReadAlmFileInfo();
}
void AlmShowDlg::OnDelAlmItem(void)
{
    QPushButton* pNewBut;
    QMessageBox  msgBox(this);
    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("你是否想删除告警文件?");
    pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(100,30);
    pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
    pNewBut->setMinimumSize(100,30);
    QSpacerItem* horizontalSpacer = new QSpacerItem(250, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    SetMessageBoxFont(&msgBox);
    if(QMessageBox::AcceptRole == msgBox.exec())
    {
        g_pAlmFile->Delete();

        QString strFilePath;
        strFilePath  = qApp->applicationDirPath()+"/";
        strFilePath += g_devConfigInfo.basicCfgInfo.strLogPath;
        strFilePath += ALM_FILE_NAME;
        g_pAlmFile->CreateFile(strFilePath);

        OnClickOK();
    }
}

#define MAX_PER_READ_ALM_COUNT   1000
void AlmShowDlg::ReadAlmFileInfo(void)
{
    AlmItemEx  almItemEx[MAX_PER_READ_ALM_COUNT];

    UINT32 unRecCount = g_pAlmFile->GetRecCount();
    if(unRecCount>MAX_ALM_SHOW_SOUNT)
    {
        unRecCount = MAX_ALM_SHOW_SOUNT;
    }
    UINT32 unFrmIndex = 0;
    UINT32 unRecIndex = 0;
    UINT32 unPerReadAlmCount = MAX_PER_READ_ALM_COUNT;
    printf("TotalAlarmCount:%lu\r\n",unRecCount);
    while(unFrmIndex < unRecCount&&0!=unPerReadAlmCount)
    {
        unPerReadAlmCount = unRecCount-unFrmIndex;
        if(unPerReadAlmCount>=MAX_PER_READ_ALM_COUNT)
        {
            unPerReadAlmCount = MAX_PER_READ_ALM_COUNT;
        }
        if(true==g_pAlmFile->ReadAlmData(unFrmIndex,almItemEx,unPerReadAlmCount))
        {
            //printf("AlmItemCount:%lu\r\n",unPerReadAlmCount);
            for(unRecIndex = 0; unRecIndex < unPerReadAlmCount; unRecIndex++)
            {
                AddAlmItem(&almItemEx[unRecIndex].almItem);
            }
        }
        else
        {
            break;
        }
        unFrmIndex += unPerReadAlmCount;
    }
}

void AlmShowDlg::AddAlmItem(AlmItem* pAlmItem)
{
    QStandardItem* pNewItem;
    QStandardItemModel* pItemModel;
    pItemModel = (QStandardItemModel*)m_pInfoView->model();

    long lColIndex = 0;

	if(ALM_ITEM_SUB_DEV_TMT == pAlmItem->unAlmID)
	{
		pNewItem = new QStandardItem(AlmTmtIDToName(pAlmItem->unAlmObjID));
	}
	else
	{
	    pNewItem = new QStandardItem(AlmIDToName(pAlmItem->unAlmID));
	}
    pItemModel->setItem(m_lRowIndex ,lColIndex++, pNewItem);

    pNewItem = new QStandardItem(QString("%1").arg(pAlmItem->unAlmObjID));
    pItemModel->setItem(m_lRowIndex ,lColIndex++, pNewItem);

    pNewItem = new QStandardItem(QString("%1").arg(pAlmItem->unAlmSubObjID));
    pItemModel->setItem(m_lRowIndex ,lColIndex++, pNewItem);

    pNewItem = new QStandardItem(DateTimeToString(&pAlmItem->dtCreate));
    pItemModel->setItem(m_lRowIndex ,lColIndex++, pNewItem);

    pNewItem = new QStandardItem(AlmFlagToString(pAlmItem->unAlmFlag));
    pItemModel->setItem(m_lRowIndex ,lColIndex++, pNewItem);

    if(0==pAlmItem->unAlmFlag)
    {
        pNewItem = new QStandardItem("-----");
    }
    else
    {
        if(ALM_ITEM_A_PRE_DN==pAlmItem->unAlmID ||\
		   ALM_ITEM_A_PRE_UP==pAlmItem->unAlmID ||\
		   ALM_ITEM_A_TMP_UP==pAlmItem->unAlmID ||\
		   ALM_ERROE_A_TMP ==pAlmItem->unAlmID  ||\
		   ALM_ITEM_V_PRE_DN==pAlmItem->unAlmID ||\
		   ALM_ITEM_V_PRE_UP==pAlmItem->unAlmID ||\
		   ALM_ITEM_V_TMP_UP==pAlmItem->unAlmID ||\
		   ALM_ERROE_V_TMP ==pAlmItem->unAlmID)
        {
            pNewItem = new QStandardItem(ValueToString(pAlmItem->unAlmVal,10,1));
        }
        else
        {
			pNewItem = new QStandardItem(QString("%1").arg(pAlmItem->unAlmVal));
        }
    }
    pItemModel->setItem(m_lRowIndex ,lColIndex++, pNewItem);

    m_lRowIndex++;
}



void AlmShowDlg::OnClickOK(void)
{
    done(QDialog::Accepted);
	ReleaseAll();
}

void AlmShowDlg::UpDateRTAlmInfos(void)
{
    QStandardItemModel* pItemModel;
    pItemModel = (QStandardItemModel*)m_pRTAlmTabView->model();
    pItemModel->removeRows(0,pItemModel->rowCount());

    UINT8  unGrpIndex;
    //UINT32 unBatIndex;
    UINT32 unRowIndex;

    UINT8 unIndex;

    QString  strAlmItem;
    QString  strItemVal;
    QString  strItemAlmVal;

    //memset(&g_devAlmBits,0xFF,sizeof(g_devAlmBits));
    unRowIndex = 0;
    for(unGrpIndex = 0; unGrpIndex < g_devConfigInfo.basicCfgInfo.unAPumCount; unGrpIndex++ )
    {
        //动脉泵-压力
        if(g_devAlmBits.ApumGrpAlm[unGrpIndex].bPressUBits)
        {
            strAlmItem = QString("动脉血泵组<%1>---压力高").arg(unGrpIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unAPrssVal,10,1);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresA,10,1);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }

        //动脉泵-流量
        if(g_devAlmBits.ApumGrpAlm[unGrpIndex].bFlowUBits)
        {
            strAlmItem = QString("动脉血泵组<%1>---流量高").arg(unGrpIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unAFlowVal,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.ApumGrpAlm[unGrpIndex].bFlowLBits)
        {
            strAlmItem = QString("动脉血泵组<%1>---流量低").arg(unGrpIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unAFlowVal,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.ApumGrpAlm[unGrpIndex].bBubblBits)
        {
            strAlmItem = QString("动脉血泵组<%1>---有汽包").arg(unGrpIndex+1);
            strItemVal = ValueToString(1,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmBubbleA,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.ApumGrpAlm[unGrpIndex].bTmpUBits)
        {
            strAlmItem = QString("动脉血泵组<%1>---血温高").arg(unGrpIndex+1);
            strItemVal = ValueToString(1,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.ApumGrpAlm[unGrpIndex].bTmpErrBits)
        {
            strAlmItem = QString("动脉血泵组<%1>---血温异常").arg(unGrpIndex+1);
            strItemVal = ValueToString(1,1,0);
            strItemAlmVal = ValueToString(1,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }		
    }

    //动脉泵-超时
    for(unIndex = 0; unIndex < g_devConfigInfo.basicCfgInfo.unAPumCount; unIndex++)
    {
        if((g_devAlmBits.unAPumModBits>>unIndex)&0x01)
        {
            strAlmItem = QString("动脉血泵模块<%1>---通信超时").arg(unIndex+1);
            strItemVal = QString("60");
            strItemAlmVal = QString("60");
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
    }
	//静脉泵-超时
    for(unIndex = 0; unIndex < g_devConfigInfo.basicCfgInfo.unVPumCount; unIndex++)
    {
        if((g_devAlmBits.unVPumModBits>>unIndex)&0x01)
        {
            strAlmItem = QString("静脉血泵模块<%1>---通信超时").arg(unIndex+1);
            strItemVal = QString("60");
            strItemAlmVal = QString("60");
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
		
        //静脉泵-压力
        if(g_devAlmBits.VpumGrpAlm[unIndex].bPressUBits)
        {
            strAlmItem = QString("静脉血泵组<%1>---压力高").arg(unIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unVPrssVal,10,1);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresV,10,1);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }

        //静脉泵-流量
        if(g_devAlmBits.VpumGrpAlm[unIndex].bFlowUBits)
        {
            strAlmItem = QString("静脉血泵组<%1>---流量高").arg(unIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unVFlowVal,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.VpumGrpAlm[unIndex].bFlowLBits)
        {
            strAlmItem = QString("静脉血泵组<%1>---流量低").arg(unIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unVFlowVal,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.VpumGrpAlm[unIndex].bBubblBits)
        {
            strAlmItem = QString("静脉血泵组<%1>---有汽包").arg(unIndex+1);
            strItemVal = ValueToString(1,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmBubbleV,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.VpumGrpAlm[unIndex].bTmpUBits)
        {
            strAlmItem = QString("静脉血泵组<%1>---血温高").arg(unIndex+1);
            strItemVal = ValueToString(1,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
        if(g_devAlmBits.VpumGrpAlm[unIndex].bTmpErrBits)
        {
            strAlmItem = QString("静脉血泵组<%1>---血温异常").arg(unIndex+1);
            strItemVal = ValueToString(1,1,0);
            strItemAlmVal = ValueToString(1,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }			
    }
	//水浴-超时
    for(unIndex = 0; unIndex < g_devConfigInfo.basicCfgInfo.unWatCount; unIndex++)
    {
        if((g_devAlmBits.unWatModBits>>unIndex)&0x01)
        {
            strAlmItem = QString("水浴模块<%1>---通信超时").arg(unIndex+1);
            strItemVal = QString("60");
            strItemAlmVal = QString("60");
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }

        //水浴-温度高
        if(g_devAlmBits.watGrpAlm[unIndex].bTmpUBits)
        {
            strAlmItem = QString("水浴模块<%1>---温度高").arg(unIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unWatTmpVal,10,1);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp,10,1);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
	     //水浴-水位高告警
        if(g_devAlmBits.watGrpAlm[unIndex].bLinUBits)
        {
            strAlmItem = QString("水浴模块<%1>---水位高告警").arg(unIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unWatLine,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUWatLin,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }
		//水浴-水位低告警
        if(g_devAlmBits.watGrpAlm[unIndex].bLinLBits)
        {
            strAlmItem = QString("水浴模块<%1>---水位低告警").arg(unIndex+1);
            strItemVal = ValueToString(g_DataAlarm.unWatLine,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLWatLin,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }	
	     //水浴-血液告警
        if(g_devAlmBits.watGrpAlm[unIndex].bBloodBit)
        {
            strAlmItem = QString("水浴模块<%1>---血液液位低").arg(unIndex+1);
            strItemVal = ValueToString(200,1,0);
            strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmBloodLin,1,0);
            AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
        }			
    }
    if(g_devAlmBits.unSysRestartBit)
    {
        strAlmItem = QString("---系统重新启动---");
        strItemVal = QString("-------");
        strItemAlmVal = QString("------");
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
}

void AlmShowDlg::AddRLAlmItem(UINT32 unRowIndex,QString strItemName,QString strItemVal,QString strAlmVal)
{
    QStandardItem* pNewItem;
    QStandardItemModel* pItemModel;
    pItemModel = (QStandardItemModel*)m_pRTAlmTabView->model();

    long lColIndex = 0;
    pNewItem = new QStandardItem(strItemName);
    pItemModel->setItem(unRowIndex ,lColIndex++, pNewItem);

    pNewItem = new QStandardItem(strItemVal);
    pItemModel->setItem(unRowIndex ,lColIndex++, pNewItem);

    pNewItem = new QStandardItem(strAlmVal);
    pItemModel->setItem(unRowIndex ,lColIndex++, pNewItem);

}
void AlmShowDlg::closeEvent(QCloseEvent *event)
{
    event->accept();
    ReleaseAll();
}

void AlmShowDlg::ReleaseAll()
{
    if(true==m_bFreeFlag)
    {
        m_pRTItemModel->clear();
        m_pAlmItemModel->clear();
        delete m_pRTItemModel;
        delete m_pAlmItemModel;

        delete m_pRTAlmTabView;
        delete m_pInfoView;
        m_pInfoView = NULL;
        m_pRTAlmTabView = NULL;
        m_bFreeFlag = false;
    }
}
