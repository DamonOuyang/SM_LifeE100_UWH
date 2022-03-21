#include "almshowdialog.h"
#include "ui_almshowdialog.h"

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

#define MAX_PER_READ_ALM_COUNT   1000
#define MAX_ALM_SHOW_SOUNT  10000


AlmShowDialog::AlmShowDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::AlmShowDialog)
{
    ui->setupUi(this);
/**/
    m_lFileDataPos = 0;
    m_lRowIndex    = 0;


    //m_pButBox = new QDialogButtonBox(Qt::Horizontal);


    //m_pButBox->addButton(ui->almWinBack, QDialogButtonBox::ActionRole);
    connect(ui->almWinBack,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    //connect(pDelBut,SIGNAL(clicked()),this,SLOT(OnDelAlmItem()));


    AddRTAlarmTab();
    AddDataAlarmTab();

    //setWindowTitle("－－－－－设备告警信息列表－－－－－");
    m_bFreeFlag = true;
}

void AlmShowDialog::AddRTAlarmTab(void)
{
    QVBoxLayout*  pMainLayout = new QVBoxLayout();
    ui->almRTTab->setLayout(pMainLayout);

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
	m_pRTAlmTabView->setStyleSheet("background-color:transparent");
    m_pRTAlmTabView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#36363D;color:white;font:24px;}");  //行表头
    //m_pRTAlmTabView->verticalHeader()->setStyleSheet("QHeaderView::section{background-color:transparent;color:white;}");    //列表头
	m_pRTAlmTabView->verticalHeader()->setVisible(false);

    QStringList strColNames;
    strColNames<<"告警项目"<<"当前值"<<"告警条件";

    long lColSizes[3];
    lColSizes[0] = 400;
    lColSizes[1] = 100;
    lColSizes[2] = 100;
    long lColIndex;
    m_pRTItemModel->setHorizontalHeaderLabels(strColNames);
    for(lColIndex = 0; lColIndex < (long)m_pRTItemModel->columnCount();lColIndex++)
    {
        m_pRTAlmTabView->setColumnWidth(lColIndex,lColSizes[lColIndex]);//#36363D
        
    }
    UpDateRTAlmInfos();
}

void AlmShowDialog::AddDataAlarmTab(void)
{
    QVBoxLayout*  pMainLayout = new QVBoxLayout();
    ui->almDataTab->setLayout(pMainLayout);

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
	m_pInfoView->setStyleSheet("background-color:transparent");
    m_pInfoView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#36363D;color:white;}");  //行表头
    //m_pInfoView->verticalHeader()->setStyleSheet("QHeaderView::section{background-color:transparent;color:white;}");    //列表头
	m_pInfoView->verticalHeader()->setVisible(false);

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
	m_pInfoView->sortByColumn(3,Qt::DescendingOrder);
}	

void AlmShowDialog::ShowAlarmInfos(void)
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
/*
void AlmShowDialog::OnDelAlmItem(void)
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
*/

void AlmShowDialog::ReadAlmFileInfo(void)
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
    //printf("TotalAlarmCount:%lu\r\n",unRecCount);
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

void AlmShowDialog::AddAlmItem(AlmItem* pAlmItem)
{
    QStandardItem* pNewItem;
    QStandardItemModel* pItemModel;
    pItemModel = (QStandardItemModel*)m_pInfoView->model();

    long lColIndex = 0;
/*
	if(ALM_ITEM_SUB_DEV_TMT == pAlmItem->unAlmID)
	{
		pNewItem = new QStandardItem(AlmTmtIDToName(pAlmItem->unAlmObjID));
	}
	else
	{
	    pNewItem = new QStandardItem(AlmIDToName(pAlmItem->unAlmID));
	}*/
	pNewItem = new QStandardItem(AlmIDToName(pAlmItem->unAlmID));
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
        if(H_T_ALM_ITEM_A_PRE_DN==pAlmItem->unAlmID ||\
		   H_P_ALM_ITEM_A_PRE_UP==pAlmItem->unAlmID ||\
		   H_P_ALM_ITEM_A_TMP_UP==pAlmItem->unAlmID ||\
		   L_T_ALM_ITEM_A_TMP_SEN==pAlmItem->unAlmID ||\
		   H_P_ALM_ITEM_V_PRE_DN==pAlmItem->unAlmID ||\
		   H_P_ALM_ITEM_V_PRE_UP==pAlmItem->unAlmID ||\
		   H_P_ALM_ITEM_V_TMP_UP==pAlmItem->unAlmID ||\
		   L_T_ALM_ITEM_V_TMP_SEN ==pAlmItem->unAlmID  ||\
		   H_T_ALM_ITEM_WAT_TMP_UP==pAlmItem->unAlmID||\
		   H_T_ALM_ITEM_WAT_TMP_SEN==pAlmItem->unAlmID)
        {
            pNewItem = new QStandardItem(ValueToString(pAlmItem->unAlmVal,10,1));
        }
        else
        {
			pNewItem = new QStandardItem(QString("%1").arg(pAlmItem->unAlmVal));
        }
    }
    //pItemModel->setRowCount(m_lRowIndex)->setForeground(QBrush(QColor(54, 54, 61)));
    pItemModel->setItem(m_lRowIndex ,lColIndex++, pNewItem);

    m_lRowIndex++;
}


void AlmShowDialog::UpDateRTAlmInfos(void)
{
    QStandardItemModel* pItemModel;
    pItemModel = (QStandardItemModel*)m_pRTAlmTabView->model();
    pItemModel->removeRows(0,pItemModel->rowCount());

    UINT32 unRowIndex;

    QString  strAlmItem;
    QString  strItemVal;
    QString  strItemAlmVal;

    //动脉泵-压力
    unRowIndex = 0;
    if(g_devAlmBits.ApumGrpAlm.bPressUBits)
    {
        strAlmItem = QString("动脉压力高");
        strItemVal = ValueToString(g_DataAlarm.unAPrssVal,10,1);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresV,10,1);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bPressLBits)
    {
        strAlmItem = QString("动脉压力低");
        strItemVal = ValueToString(g_DataAlarm.unAPrssVal,10,1);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLPresA,10,1);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bPressErrBits)
    {
        strAlmItem = QString("动脉压力异常");
        strItemVal = ValueToString(g_DataAlarm.unAPrssVal,10,1);
        strItemAlmVal = ValueToString(0,0,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    //动脉血温
    if(g_devAlmBits.ApumGrpAlm.bTmpUBits)
    {
        strAlmItem = QString("动脉血液温度高");
        strItemVal = ValueToString(g_DataAlarm.unATmpVal,10,1);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpA,10,1);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }

    //动脉泵-流量
    if(g_devAlmBits.ApumGrpAlm.bFlowLBits)
    {
        strAlmItem = QString("动脉流量低") ;
        strItemVal = ValueToString(g_DataAlarm.unAFlowVal,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowA,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }    
    if(g_devAlmBits.ApumGrpAlm.bFlowUBits)
    {
        strAlmItem = QString("动脉流量高");
        strItemVal = ValueToString(g_DataAlarm.unAFlowVal,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowA,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    //控制板失联
	if(g_devAlmBits.unAPumModBits)
	{
		strAlmItem = QString("动脉控制板失联");
		strItemVal = QString("5");
		strItemAlmVal = QString("5");
		AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
	}
	//
    if(g_devAlmBits.ApumGrpAlm.bPumTmtBits)
    {
        strAlmItem = QString("动脉泵未连接");
        strItemVal = QString("60");
        strItemAlmVal = QString("60");
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bPumErrBits)
    {
        strAlmItem = QString("动脉泵异常");
        strItemVal = ValueToString(g_DataAlarm.unAFlowVal,1,0);
        strItemAlmVal = ValueToString(0,0,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }

    if(g_devAlmBits.ApumGrpAlm.bBubblBits)
    {
        strAlmItem = QString("动脉管路有气泡");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmBubbleA,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bPreLinBits)
    {
        strAlmItem = QString("动脉血压传感器线缆失联");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bPreTmtBits)
    {
        strAlmItem = QString("动脉血压监测板失联");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bFloTmtBits)
    {
        strAlmItem = QString("动脉流量传感器未连接");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bSpeedUBits)
    {
        strAlmItem = QString("动脉泵转速高");
        strItemVal = ValueToString(g_DataAlarm.unASpeeVal,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUSpeeA,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bFlowSensorBits)
    {
        strAlmItem = QString("动脉流量异常");
        strItemVal = ValueToString(g_DataAlarm.unAFlowVal,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bTmpTmtBits)
    {
        strAlmItem = QString("动脉血温传感器未连接");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.ApumGrpAlm.bTmpSensorBits)
    {
        strAlmItem = QString("动脉血温传感器异常");
        strItemVal = ValueToString(g_DataAlarm.unATmpVal,10,1);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }

	//静脉泵
    if(g_devAlmBits.VpumGrpAlm.bPressUBits)
    {
        strAlmItem = QString("门脉压力高");
        strItemVal = ValueToString(g_DataAlarm.unVPrssVal,10,1);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUPresV,10,1);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bPressLBits)
    {
        strAlmItem = QString("门脉压力低");
        strItemVal = ValueToString(g_DataAlarm.unVPrssVal,10,1);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLPresV,10,1);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bPressErrBits)
    {
        strAlmItem = QString("门脉压力异常");
        strItemVal = ValueToString(g_DataAlarm.unVPrssVal,10,1);
        strItemAlmVal = ValueToString(0,0,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    //动脉血温
    if(g_devAlmBits.VpumGrpAlm.bTmpUBits)
    {
        strAlmItem = QString("门脉血液温度高");
        strItemVal = ValueToString(g_DataAlarm.unVTmpVal,10,1);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUTmpV,10,1);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }

    //动脉泵-流量
    if(g_devAlmBits.VpumGrpAlm.bFlowLBits)
    {
        strAlmItem = QString("门脉流量低") ;
        strItemVal = ValueToString(g_DataAlarm.unVFlowVal,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLFlowV,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }    
    if(g_devAlmBits.VpumGrpAlm.bFlowUBits)
    {
        strAlmItem = QString("门脉流量高");
        strItemVal = ValueToString(g_DataAlarm.unVFlowVal,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUFlowV,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    //控制板失联
	if(g_devAlmBits.unVPumModBits)
	{
		strAlmItem = QString("门脉控制板失联");
		strItemVal = QString("5");
		strItemAlmVal = QString("5");
		AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
	}
	//
    if(g_devAlmBits.VpumGrpAlm.bPumTmtBits)
    {
        strAlmItem = QString("门脉泵未连接");
        strItemVal = QString("1");
        strItemAlmVal = QString("1");
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bPumErrBits)
    {
        strAlmItem = QString("门脉泵异常");
        strItemVal = ValueToString(g_DataAlarm.unVFlowVal,1,0);
        strItemAlmVal = ValueToString(0,0,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }

    if(g_devAlmBits.VpumGrpAlm.bBubblBits)
    {
        strAlmItem = QString("门脉管路有气泡");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmBubbleV,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bPreLinBits)
    {
        strAlmItem = QString("门脉血压传感器线缆失联");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bPreTmtBits)
    {
        strAlmItem = QString("门脉血压监测板失联");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bFloTmtBits)
    {
        strAlmItem = QString("门脉流量传感器未连接");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bSpeedUBits)
    {
        strAlmItem = QString("门脉泵转速高");
        strItemVal = ValueToString(g_DataAlarm.unVSpeeVal,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUSpeeV,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bFlowSensorBits)
    {
        strAlmItem = QString("门脉流量异常");
        strItemVal = ValueToString(g_DataAlarm.unVFlowVal,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bTmpTmtBits)
    {
        strAlmItem = QString("门脉血温传感器未连接");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.VpumGrpAlm.bTmpSensorBits)
    {
        strAlmItem = QString("门脉血温传感器异常");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }

	//水浴
    //水浴-温度高
    if(g_devAlmBits.watGrpAlm.bTmpUBits)
    {
        strAlmItem = QString("水浴温度高");
        strItemVal = ValueToString(g_DataAlarm.unWatTmpVal,10,1);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUWatTmp,10,1);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.watGrpAlm.bWatPreUBits)
    {
        strAlmItem = QString("变温系统压力超限值");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
		printf("--------------------------------------------here----\r\n");
    }
    if(g_devAlmBits.watGrpAlm.bTmpSensorBits)
    {
        strAlmItem = QString("水浴温度传感器异常");
        strItemVal = ValueToString(g_DataAlarm.unWatTmpVal,10,1);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }	
    if(g_devAlmBits.unWatModBits)
    {
        strAlmItem = QString("水浴控制板失联");
        strItemVal = QString("5");
        strItemAlmVal = QString("5");
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
	//水浴-水位低告警
    if(g_devAlmBits.watGrpAlm.bLinLBits)
    {
        strAlmItem = QString("水箱液位低");
        strItemVal = ValueToString(g_DataAlarm.unWatLine,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmLWatLin,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.watGrpAlm.bFanBits)
    {
        strAlmItem = QString("系统风扇故障");
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.watGrpAlm.bLinUBits)
    {
        strAlmItem = QString("水箱液位高");
        strItemVal = ValueToString(g_DataAlarm.unWatLine,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmUWatLin,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
	/*
     //水浴-血液告警
    if(g_devAlmBits.watGrpAlm.bBloodBit)
    {
        strAlmItem = QString("水浴模块<%1>---血液液位低");
        strItemVal = ValueToString(200,1,0);
        strItemAlmVal = ValueToString(g_devConfigInfo_Edt.devAlmParam.unAlmBloodLin,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }


    if(g_devAlmBits.watGrpAlm[unIndex].bLinSensorBits)
    {
        strAlmItem = QString("水浴模块<%1>---水位传感器异常").arg(unIndex+1);
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
    if(g_devAlmBits.watGrpAlm[unIndex].bBloSensorBits)
    {
        strAlmItem = QString("水浴模块<%1>---血位传感器异常").arg(unIndex+1);
        strItemVal = ValueToString(1,1,0);
        strItemAlmVal = ValueToString(1,1,0);
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }*/
	//备用电源
	//水浴-温度高
	if(g_devAlmBits.BatAlm.bACLosBits)
	{
		strAlmItem = QString("电源线未连接");
		strItemVal = QString("---");
		strItemAlmVal = QString("---");
		AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
	}
	if(g_devAlmBits.BatAlm.bBatSocBits)
	{
		strAlmItem = QString("电池电量低");
		strItemVal = QString("---");
		strItemAlmVal = QString("---");
		AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
	}
	if(g_devAlmBits.BatAlm.bBatTmpBits)
	{
		strAlmItem = QString("电池过温");
		strItemVal = QString("---");//ValueToString(1,1,0);
		strItemAlmVal = QString("---");//ValueToString(1,1,0);
		AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
	}	
	if(g_devAlmBits.unBatModBits)
	{
		strAlmItem = QString("电池模块失联");
		strItemVal = QString("60");
		strItemAlmVal = QString("60");
		AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
	}
	//水浴-水位低告警
	if(g_devAlmBits.BatAlm.bBatChkBits)
	{
		strAlmItem = QString("电池检测周期到");
		strItemVal = QString("---");
		strItemAlmVal = QString("---");
		AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
	}

	//系统重启
    if(g_devAlmBits.unSysRestartBit)
    {
        strAlmItem = QString("---系统重新启动---");
        strItemVal = QString("---");
        strItemAlmVal = QString("---");
        AddRLAlmItem(unRowIndex++,strAlmItem,strItemVal,strItemAlmVal);
    }
}

void AlmShowDialog::AddRLAlmItem(UINT32 unRowIndex,QString strItemName,QString strItemVal,QString strAlmVal)
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


AlmShowDialog::~AlmShowDialog()
{
    delete ui;
}
void AlmShowDialog::OnClickOK(void)
{
    done(QDialog::Accepted);
	ReleaseAll();
}
void AlmShowDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    ReleaseAll();
}

void AlmShowDialog::ReleaseAll()
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