#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include  <sys/wait.h>
#include  <errno.h>
#include  <signal.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <dirent.h>
#include <sys/stat.h>
#include <QDialogButtonBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QFileInfo>

#include "systemsetdialog.h"
#include "ui_systemsetdialog.h"
#include "MyQProxyStyle.h"

#include "CConfigPanel.h"
#include "monLogframedlg.h"
#include "dataframedlg.h"
#include "cworkthread.h"
//#include "updatedialog.h"
#include "upchosedevdialog.h"
#include "updategoingdialog.h"


#define  TST_DATA_INDEX     0
#define  OPER_LOG_INDEX     1
#define  CFG_PARAM_INDEX    2
#define  ABOUT_INDEX        3

extern CWorkThread*   g_pWorkThread;


SystemSetDialog::SystemSetDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::SystemSetDialog)  
{
    ui->setupUi(this);
	//setWindowFlags(Qt::FramelessWindowHint);
/**/
    MyQProxyStyle *myQProxyStyle = new MyQProxyStyle();
	myQProxyStyle->SetTabWidth(160);
	myQProxyStyle->SetTabHeigth(65);
	myQProxyStyle->SetFontB(18);
    ui->setTabWidget->tabBar()->setStyle(myQProxyStyle);

    QPushButton* pBackBut = new QPushButton(this);
    pBackBut->setObjectName(QString::fromUtf8("pBackBut"));
	pBackBut->setGeometry(QRect(1080, 20, 160, 60));
	QIcon icon;
	icon.addFile(QString::fromUtf8(":/images/sysSetBack_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
	pBackBut->setIcon(icon);
	pBackBut->setIconSize(QSize(160, 60));

	connect(pBackBut, SIGNAL(clicked()),this, SLOT(BackButtonClicked()));
/**/
	InitPourTestData();
	AddDataFrmUI();
	AddOperSetFrmUI();
	AddConfigFrmUI();

	m_pUpGoing = new UpdateGoingDialog(this);
	m_pUpGoing->setGeometry(QRect(0, 40, 1280, 760));
	m_pUpGoing->hide();

	m_pUpChoseDev = new UpChoseDevDialog(this);
	m_pUpChoseDev->setGeometry(QRect(0, 40, 1280, 760));
	m_pUpChoseDev->hide();

	QString strCoInfo;//关于公司基本信息
	LoadCompanyInfo(strCoInfo);
	ui->pTextEdit->setText(strCoInfo);

	connect(ui->updateBut,SIGNAL(clicked()),this,SLOT(OnClickUpdate()));

	m_pUpdTimer = new QTimer(this);
	connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnFirtActiveTimer(void)));
	m_pUpdTimer->start(1000);

	m_unClickNum = 0;
	m_unReSetPrmFlag = 0;
	m_unCheckUpdateSec = 60;
	m_unRunState = 0;
	m_bFlashPicFlg = false;
	m_bFlashInfoFlag = false;
	m_unDlyFlashInfoSce = 30;

	m_unTestUpSce = 0;
	m_bUpdateFlg = false;
	m_ShowUpDateDlgFlg = false;
	m_unUpDevType = 0;	

}



SystemSetDialog::~SystemSetDialog()
{
	delete m_pDataFrmDlg;
    delete m_pCfgPanel;
	delete m_pMonLogFrmDlg;

	delete m_pUpChoseDev;
	delete m_pUpGoing;

    delete ui;
}

void SystemSetDialog::BackButtonClicked(void)
{
    this->hide();
}

void SystemSetDialog::InitPourTestData(void)
{
    memset(&g_pourTstData,0,sizeof(PourTstData));

    g_pourTstData.tstInfo.unStopType = 0xFF;

    GetSystemTime(g_pourTstData.tstInfo.dtStart);	//启动时间
    GetSystemTime(g_pourTstData.tstInfo.dtEnd);     //停止时间
    g_pourTstData.tstInfo.unRecords     = 0;     //记录条数
    g_pourTstData.tstInfo.unSectorID    = 0;     //扇区ID
    g_pourTstData.tstInfo.unTotalTime   = 0;     //启动总时间，以秒为单位

	//动脉
    g_pourTstData.tstData.unADataType = 0;   //数据类型
    g_pourTstData.tstData.unASpeeSet = 0;	//转速(RPM)设定值
    g_pourTstData.tstData.unAPrssSet = 0;	//压力(mmHg)设定值
    
    g_pourTstData.tstData.unATmpVal = 0;	//温度(℃)
    g_pourTstData.tstData.unAFlowVal = 0;	//流量(ml)
    g_pourTstData.tstData.unAPrssVal = 0;	//压力(mmHg)
    g_pourTstData.tstData.unASpeeVal = 0;	//转速(RPM)
    //水浴
	g_pourTstData.tstData.unWatTmpSet = 0; //水浴温度设定值
	g_pourTstData.tstData.unWatTmpVal = 0; //水浴值(℃)
	g_pourTstData.tstData.unWatLine   = 0; //水浴水位

	//静脉
	/**/
    g_pourTstData.tstData.unVDataType = 0;   //数据类型
    g_pourTstData.tstData.unVSpeeSet = 0;	//转速(RPM)设定值
    g_pourTstData.tstData.unVPrssSet = 0;	//压力(mmHg)设定值
    
    g_pourTstData.tstData.unVTmpVal = 0;	//温度(℃)
    g_pourTstData.tstData.unVFlowVal = 0;	//流量(ml)
    g_pourTstData.tstData.unVPrssVal = 0;	//压力(mmHg)
    g_pourTstData.tstData.unVSpeeVal = 0;	//转速(RPM)
    
    GetSystemTime(g_pourTstData.tstData.dtSample);	//采样时间
}
void SystemSetDialog::GetSystemTime(DateTime& dateTime)
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    dateTime.unYear = curDateTime.date().year()-2000;
    dateTime.unMonth = curDateTime.date().month();
    dateTime.unDay  =  curDateTime.date().day();
    dateTime.unHour =  curDateTime.time().hour();
    dateTime.unMinute = curDateTime.time().minute();
    dateTime.unSecond = curDateTime.time().second();
}

void SystemSetDialog::AddDataFrmUI(void)
{
    m_pDataFrmDlg = new DataFrameDlg(ui->setTabWidget->widget(TST_DATA_INDEX));
    m_pDataFrmDlg->setGeometry(QRect(0, 20, 1200, 675));
    ui->setTabWidget->widget(TST_DATA_INDEX)->setLayout(m_pDataFrmDlg->layout());
    //灌注文件 压力曲线 转速曲线 流量曲线 温度曲线 水浴温度 详细数据
}

void SystemSetDialog::AddOperSetFrmUI(void)//监控日志 操作日志
{
    m_pMonLogFrmDlg = new MonLogFrameDlg(ui->setTabWidget->widget(OPER_LOG_INDEX));
	m_pMonLogFrmDlg->setGeometry(QRect(0, 20, 1200, 675));
    ui->setTabWidget->widget(OPER_LOG_INDEX)->setLayout(m_pMonLogFrmDlg->layout());
}
/**/
void SystemSetDialog::AddConfigFrmUI(void)
{
    m_pCfgPanel = new CConfigPanel(ui->setTabWidget->widget(CFG_PARAM_INDEX));
	m_pCfgPanel->setGeometry(QRect(0, 20, 1200, 675));
    ui->setTabWidget->widget(CFG_PARAM_INDEX)->setLayout(m_pCfgPanel->layout());
}

void SystemSetDialog::FlashCfgDevPrm(BqBatBascInfo *batDevData)
{
    m_pCfgPanel->FlashSubDevPrm(batDevData);
	m_pMonLogFrmDlg->ShowTestDetail();
	m_pDataFrmDlg->ListFileInfos();
}
void SystemSetDialog::OnClickUpdate(void)
{
	if(m_ShowUpDateDlgFlg == false)
	{
	    m_ShowUpDateDlgFlg = true;
		m_pUpChoseDev->show();
		//m_pUpDateDialog->SetDevType(DEV_MAIN_TYPE);
	}
}
void SystemSetDialog::UpdateFail(UINT8 unPre, UINT8 unFailType)
{
    //m_pUpDateDialog->SetUpMcuBar(unPre, unFailType);
	m_ShowUpDateDlgFlg = false;
	m_pUpChoseDev->hide();
}

void SystemSetDialog::UpChooseDev(unsigned char unTpye)
{
    printf("-------------------UpChooseDev:%u---------------------\r\n",unTpye);
    UINT8 unUpMcuFlg = unTpye;
	/**/
    QMessageBox  msgBox(this);
	msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
    QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    QPushButton* pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(160,60);

    QString strPathName;
    QFileInfo  dir("/udisk/");
    if(!dir.isDir())
    {
        msgBox.setWindowTitle("提示");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("未发现U盘，请插入U盘!");
        SetMessageBoxFont(&msgBox);
        msgBox.exec();
		UpdateFail(0, UpdFindFileErr);
        return;
    }

    QFileInfo  UpdDir("/udisk/UpdateFiles/");
    if(!UpdDir.isDir())
    {
        msgBox.setWindowTitle("错误");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("未发现升级文件，请拷入文件!");
        SetMessageBoxFont(&msgBox);
        msgBox.exec();
		UpdateFail(0, UpdFindFileErr);
        return;
    }

    QString strCpy;
	if(unUpMcuFlg > 0)
	{
		strCpy = QString("cp -r /udisk/UpdateFiles/McuSoft %1/").arg(qApp->applicationDirPath());
	}
	else
	{
	    strCpy = QString("cp -r /udisk/UpdateFiles/* %1/").arg(qApp->applicationDirPath());
	}
    printf("CopyCmd:%s\r\n",strCpy.toStdString().c_str());
    if(SystemEx(strCpy.toStdString().c_str())<0)
    {
        msgBox.setWindowTitle("错误");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("拷贝程序升级文件失败!");
        SetMessageBoxFont(&msgBox);
        msgBox.exec();
		UpdateFail(0, UpdFindFileErr);
        return;
    }

    SystemEx("sync");
	

	if(unUpMcuFlg > 0)
	{
		g_pWorkThread->SetUpdateMcu(unUpMcuFlg);
		m_bUpdateFlg = true;
		m_pUpGoing->show();
	}

	if(0x00 != unUpMcuFlg) //没有找到单片机文件
	{
		printf("USB update for MCU APP!\n");
		//g_pWorkThread->SetUpdateMcu();
		//调用升级MCU程序
		m_unUpDevType = unUpMcuFlg;
	}
	else
	{
		OperLogCtl operLogCtl;
		operLogCtl.unType = OPER_CTRL_SYS_UP;
		operLogCtl.unSite = LOC_CTL;
		GetDateTime(&operLogCtl.dtCreate);
		operLogCtl.unResult[0] = 0;
		operLogCtl.unResult[1] = 1;
		
		operLogCtl.unOperType[0] = 0;
		operLogCtl.unOperType[1] = 1;
		SaveOperLogData((const char*)&operLogCtl, sizeof(OperLogCtl));
		SaveOperLogInfo();
		
    	SystemEx("reboot -f");
	}
}

void SystemSetDialog::UpCanlce(void)
{
    printf("-------------------uddate UpCanlce---------------------\r\n");
	m_ShowUpDateDlgFlg = false;

	/**/
    QFileInfo  UpdDir("/home/McuSoft/");
    if(UpdDir.isDir())
    {
        SystemEx("rm -rf /home/McuSoft");
    }
    //m_pUpGoing->show();
}

void SystemSetDialog::FlashCompanyInfo(void)
{
    QString strCoInfo;//关于公司基本信息
    LoadCompanyInfo(strCoInfo);

	McuUpdateState unMcuUpdInfo[10];
	for(UINT8 unIndex = 0; unIndex < 10; unIndex++)
	{
		memset(&unMcuUpdInfo[unIndex],0,sizeof(McuUpdateState));
	}
	g_pWorkThread->GetAllMcuVer((BYTE*)unMcuUpdInfo);

	QString strVersion  = QString("动脉泵版本：%1").arg(unMcuUpdInfo[0].mcuVerInfo.McuVer);
	strCoInfo+= QString("%1\r\n").arg(strVersion);
	
	strVersion  = QString("  水浴版本：%1").arg(unMcuUpdInfo[1].mcuVerInfo.McuVer);
	strCoInfo+= QString("%1\r\n").arg(strVersion);

	strVersion  = QString("静脉泵版本：%1").arg(unMcuUpdInfo[2].mcuVerInfo.McuVer);
	strCoInfo+= QString("%1\r\n").arg(strVersion);

    ui->pTextEdit->setText(strCoInfo);
}


void SystemSetDialog::OnFirtActiveTimer(void)
{
    m_pUpdTimer->stop();
	if(m_unDlyFlashInfoSce)
		m_unDlyFlashInfoSce--;
	if(m_unDlyFlashInfoSce == 0 && m_bFlashInfoFlag == false)
	{
	    m_bFlashInfoFlag = true;
		FlashCompanyInfo();
		printf("-----------Flash FlashCompanyInfo--------------\r\n");
	}
    /*
    if(true==g_pwdCfgInfo.bPwdEnFlg&&true==g_bLoginFlag)
    {
        g_bLoginFlag = false;
        CPasswordDlg  pwdDlg(this,false);
		//pwdDlg.resize(500,300);
        while(QDialog::Rejected==pwdDlg.exec());
    }
    */
    m_pUpdTimer->start(1000);

//3秒后点击重新设置参数不满足，重新设置为0 
	if(m_unClickNum)
	{
		m_unReSetPrmFlag++;
		if(m_unReSetPrmFlag > 3)
		{
			m_unClickNum = 0;
			m_unReSetPrmFlag = 0;
		}
	}
	else
	{
		if(m_unReSetPrmFlag)
		{
			m_unReSetPrmFlag = 0;
		}
	}

	if(m_bUpdateFlg == true)
	{
		UINT8 unPre = 0;
		McuUpdateInfo pMcuUpInfo;

		//memset(&pMcuUpInfo,0,sizeof(pMcuUpInfo));
		pMcuUpInfo = g_pWorkThread->GetDevUpdateInfo();//(&pMcuUpInfo);

		if(pMcuUpInfo.unTotalPkg != 0)
		{
			unPre = pMcuUpInfo.unPkgIndex*100/pMcuUpInfo.unTotalPkg;
		}

		printf("unPre:%u unPkgIndex:%u unTotalPkg:%u unMcuUpdState:%u \r\n",unPre,pMcuUpInfo.unPkgIndex,pMcuUpInfo.unTotalPkg,pMcuUpInfo.unMcuUpdState);

		if(pMcuUpInfo.unPkgIndex <= pMcuUpInfo.unTotalPkg)
		{
			m_pUpGoing->SetUpMcuBar(unPre,pMcuUpInfo.unMcuUpdState);
		}
		
		if(m_unCheckUpdateSec > 0)
		{
		    m_unCheckUpdateSec--;
		}

		if(pMcuUpInfo.unMcuUpdState >= UpdSuccess || m_unCheckUpdateSec == 0)
		{
		    OperLogCtl operLogCtl;

			if(m_unUpDevType == DEV_APUMP_TYPE)
			{
			    operLogCtl.unType = OPER_CTRL_UP_APOUR;
			}
			else if(m_unUpDevType == DEV_WAT_TYPE)
			{
			    operLogCtl.unType = OPER_CTRL_UP_WATER;
			}			
			else if(m_unUpDevType == DEV_VPUMP_TYPE)
			{
			    operLogCtl.unType = OPER_CTRL_UP_VPOUR;
			}
			
			operLogCtl.unSite = LOC_CTL;
			GetDateTime(&operLogCtl.dtCreate);
			operLogCtl.unResult[0] = 0;
			operLogCtl.unResult[1] = 1;
			
			operLogCtl.unOperType[0] = 0;
			operLogCtl.unOperType[1] = 1;
			
		    m_bUpdateFlg = false;
			m_ShowUpDateDlgFlg = false;
			if(m_unCheckUpdateSec == 0)
			{
			   m_pUpGoing->SetUpMcuBar(unPre, UpdSndPackErr);
			   g_pWorkThread->SetUpdateMcuFail();
			   operLogCtl.unResult[1] = 2;
			}
			m_unCheckUpdateSec = 60;
			
			SaveOperLogData((const char*)&operLogCtl, sizeof(OperLogCtl));
			SaveOperLogInfo();
			m_unUpDevType = 0;
		}
	}
}

