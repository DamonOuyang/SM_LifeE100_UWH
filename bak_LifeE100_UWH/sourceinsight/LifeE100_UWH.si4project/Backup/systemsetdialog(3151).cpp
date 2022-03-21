#include "includes.h"
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


#include "systemsetdialog.h"
#include "ui_systemsetdialog.h"
//#include "dataframedlg.h"
#include "CConfigPanel.h"
#include "monLogframedlg.h"
#include "dataframedlg.h"
#include "cworkthread.h"
#include "updatedialog.h"


#include <QtGui>
//#include "cworkthread.h"
//#include "cpassworddlg.h"



#define  TST_DATA_INDEX     0
#define  OPER_LOG_INDEX     1
#define  CFG_PARAM_INDEX    2
#define  ABOUT_INDEX        3

extern CWorkThread*   g_pWorkThread;

SystemSetDialog::SystemSetDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::SysSetDialog)
{
    ui->setupUi(this);

    backButton = new QPushButton(this);
	backButton->setObjectName(QString::fromUtf8("backButton"));
    backButton->setText("返回");
    backButton->setGeometry(QRect(1100, 5, 100, 30));
	backButton->setMinimumSize(100, 30);
	backButton->hide();
	

    InitPourTestData();
	AddDataFrmUI();
	AddOperSetFrmUI();
    AddConfigFrmUI();

	

	m_pUpDateDialog = new UpDateDialog(this);
    //m_pUpDateDialog->setGeometry(QRect(0, 60, 1280, 740));
	m_pUpDateDialog->hide();

/**/

    m_pTextEdit = new QTextEdit();
    m_pTextEdit->setReadOnly(true);
    QString strCoInfo;//关于公司基本信息
    LoadCompanyInfo(strCoInfo);
    m_pTextEdit->setText(strCoInfo);

	m_pTextEdit->setObjectName(QString::fromUtf8("m_pTextEdit"));
    m_pTextEdit->setStyleSheet(QString::fromUtf8("#m_pTextEdit\n"
		       "{\n"
		        "\font-family:simsun;\
                font:26px;\
                color: rgb(86,93,113);\
                background-color:rgb(225,230,236);"
                "}\n"));


    QVBoxLayout* pMainLayout = new QVBoxLayout();
    ui->tabWidget->widget(ABOUT_INDEX)->setLayout(pMainLayout);
    QPushButton* pBut    = new QPushButton("U盘更新APP");
    //QPushButton* pButRst = new QPushButton("重新启动系统");
	//QPushButton* pButRst = new QPushButton("触摸校正");
	QPushButton* pButPmr = new QPushButton(" ");

    QDialogButtonBox*  pDlgLayout = new QDialogButtonBox(Qt::Horizontal);
    pDlgLayout->addButton(pBut,QDialogButtonBox::ActionRole);
    //pDlgLayout->addButton(pButRst,QDialogButtonBox::ActionRole);
    pDlgLayout->addButton(pButPmr,QDialogButtonBox::ActionRole);
	pButPmr->setFlat(true);
	pButPmr->setStyleSheet("background-color: rgba(0, 0, 0, 0)");

    pBut->setMinimumSize(200,40);
    pBut->setMaximumSize(200,40);
    //pButRst->setMinimumSize(200,40);
    //pButRst->setMaximumSize(200,40);
    pButPmr->setMinimumSize(200,40);
    pButPmr->setMaximumSize(200,40);

    connect(pBut,SIGNAL(clicked()),this,SLOT(OnClickUpdate()));
    //connect(pButRst,SIGNAL(clicked()),this,SLOT(OnClickRestart()));
    connect(pButPmr,SIGNAL(clicked()),this,SLOT(OnClickSetSysPrm()));
    pMainLayout->addWidget(m_pTextEdit);
    pMainLayout->addWidget(pDlgLayout);
    pMainLayout->setAlignment(pBut,Qt::AlignHCenter);

    m_pUpdTimer = new QTimer(this);
    connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnFirtActiveTimer(void)));
    m_pUpdTimer->start(1000);

	connect(backButton,SIGNAL(clicked()),this,SLOT(BackButtonClicked()));
	
	m_unClickNum = 0;
	m_unReSetPrmFlag = 0;
	m_unCheckNetNum = 5;
	m_unRunState = 0;
	m_bFlashPicFlg = false;
	m_bFlashInfoFlag = false;
	m_unDlyFlashInfoSce = 30;

	m_unTestUpSce = 0;
	m_bUpdateFlg = false;
	m_ShowUpDateDlgFlg = false;
}

SystemSetDialog::~SystemSetDialog()
{
    delete ui;
}

void SystemSetDialog::BackButtonClicked(void)
{
    this->hide();
}


void SystemSetDialog::AddDataFrmUI(void)
{
    m_pDataFrmDlg = new DataFrameDlg(ui->tabWidget->widget(TST_DATA_INDEX));
    ui->tabWidget->widget(TST_DATA_INDEX)->setLayout(m_pDataFrmDlg->layout());
    //灌注文件 压力曲线 转速曲线 流量曲线 温度曲线 水浴温度 详细数据
}

void SystemSetDialog::AddOperSetFrmUI(void)
{
    m_pMonLogFrmDlg = new MonLogFrameDlg(ui->tabWidget->widget(OPER_LOG_INDEX));
    ui->tabWidget->widget(OPER_LOG_INDEX)->setLayout(m_pMonLogFrmDlg->layout());
}


void SystemSetDialog::AddConfigFrmUI(void)
{
    m_pCfgPanel = new CConfigPanel(ui->tabWidget->widget(CFG_PARAM_INDEX));
    ui->tabWidget->widget(CFG_PARAM_INDEX)->setLayout(m_pCfgPanel->layout());
}

void SystemSetDialog::FlashCfgDevPrm(void)
{
    m_pCfgPanel->FlashSubDevPrm();
	m_pMonLogFrmDlg->ShowTestDetail();
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

void SystemSetDialog::OnClickUpdate(void)
{
	//UpDateDialog  upDateDialog(this);
	//upDateDialog.setGeometry(QRect(554, 190, SET_VAL_DLG_W, SET_VAL_DLG_H));
	//upDateDialog.setWindowModality(Qt::ApplicationModal);
	//upDateDialog.exec();
	if(m_ShowUpDateDlgFlg == false)
	{
	    m_ShowUpDateDlgFlg = true;
		m_pUpDateDialog->show();
		m_pUpDateDialog->SetDevType(DEV_MAIN_TYPE);
	}
}
void SystemSetDialog::UpdateFail(UINT8 unFailType)
{
    m_pUpDateDialog->SetUpMcuBar(0, unFailType);
	m_ShowUpDateDlgFlg = false;
	m_pUpDateDialog->hide();
}

void SystemSetDialog::UpChooseType(UINT8 unTpye)
{
    printf("-------------------UpChooseType:%u---------------------\r\n",unTpye);
    UINT8 unUpMcuFlg = unTpye;
	/**/
    QMessageBox  msgBox(this);
    QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    QPushButton* pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(120,50);

    QString strPathName;
    QFileInfo  dir("/udisk/");
    if(!dir.isDir())
    {
        msgBox.setWindowTitle("提示");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("未发现U盘，请插入U盘!");
        SetMessageBoxFont(&msgBox);
        msgBox.exec();
		UpdateFail(UpdFindFileErr);
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
		UpdateFail(UpdFindFileErr);
        return;
    }

    QString strCpy = QString("cp -r /udisk/UpdateFiles/* %1/").arg(qApp->applicationDirPath());
    printf("CopyCmd:%s\r\n",strCpy.toStdString().c_str());
    if(SystemEx(strCpy.toStdString().c_str())<0)
    {
        msgBox.setWindowTitle("错误");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("程序升级失败!");
        SetMessageBoxFont(&msgBox);
        msgBox.exec();
		UpdateFail(UpdFileChkErr);
        return;
    }

	//SystemEx("cp -r /udisk/qtShell/* /mnt/sysconfig/");
    SystemEx("sync");

	if(unUpMcuFlg > 0)
	{
		g_pWorkThread->SetUpdateMcu(unUpMcuFlg);
		m_bUpdateFlg = true;
	}

	if(0x00 != unUpMcuFlg) //没有找到单片机文件
	{
		printf("USB update for MCU APP!\n");
		//g_pWorkThread->SetUpdateMcu();
		//调用升级MCU程序
	}
	else
	{
    	SystemEx("reboot -f");
	}

}


void SystemSetDialog::UpCanlce(void)
{
    printf("-------------------uddate UpCanlce---------------------\r\n");
	m_ShowUpDateDlgFlg = false;
    QFileInfo  UpdDir("/home/McuSoft/");
    if(UpdDir.isDir())
    {
        SystemEx("rm -rf /home/McuSoft");
    }
}

void SystemSetDialog::OnClickRestart(void)
{
    /*
    QPushButton* pNewBut;
    QMessageBox  msgBox(this);
    SetMessageBoxFont(&msgBox);
    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("你确认是否需要重新启动应用程序?");
    pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(100,30);
    pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
    pNewBut->setMinimumSize(100,30);
    QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    if(QMessageBox::AcceptRole == msgBox.exec())
    {
        g_pWorkThread->StopRun();
        if(true==g_pWorkThread->IsRunEnd())
        {
            fclose(stdout);
            SystemEx("./PowerSystemMon -qws");
            qApp->quit();
        }
    }
    */
    //SystemEx("/usr/local/tslib/bin/ts_calibrate");//2018-05-17
}

void SystemSetDialog::OnClickSetSysPrm(void)
{
    /*if(m_unClickNum >= 3)
	{

	    QPushButton* pNewBut;
	    QMessageBox  msgBox(this);
	    SetMessageBoxFont(&msgBox);
	    msgBox.setWindowTitle("提示");
	    msgBox.setIcon(QMessageBox::Warning);
	    msgBox.setText("你确认是否需要重新设置系统参数?");
	    pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
	    pNewBut->setMinimumSize(100,30);
	    pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
	    pNewBut->setMinimumSize(100,30);
	    QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	    QGridLayout* layout = (QGridLayout*)msgBox.layout();
	    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
	    if(QMessageBox::AcceptRole == msgBox.exec())
	    {
	        g_pMonThread->CloseWatchdog();
			g_pMonThread->terminate();
			g_pMonThread->wait();

	        g_pWorkThread->StopRun();
	        if(true==g_pWorkThread->IsRunEnd())
	        {
	            //fclose(stdout);
				qApp->quit();
	            SystemEx("./PowerSystemMon -qws -cfg");
	        }
	    }
		m_unClickNum=0;
	}
	else
	{
		m_unClickNum++;
	}*/
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

    m_pTextEdit->setText(strCoInfo);
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
	/*

	m_unCheckNetNum++;
	if(m_unCheckNetNum >= 5)
	{
	    m_unCheckNetNum = 0;
	}
*/

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
			m_pUpDateDialog->SetUpMcuBar(unPre,pMcuUpInfo.unMcuUpdState);
		}

		if(pMcuUpInfo.unMcuUpdState >= UpdSuccess)
		{
		    m_bUpdateFlg = false;
		}
	}
}
