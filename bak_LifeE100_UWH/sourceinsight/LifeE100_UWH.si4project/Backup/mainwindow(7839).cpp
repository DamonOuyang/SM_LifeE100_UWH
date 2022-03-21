#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "includes.h"
#include "setvaldialog.h"
#include "cworkthread.h"
#include "cmonshareData.h"
#include "systemsetdialog.h"
#include "CAlarmDataFile.h"
//#include "AlmShowDlg.h"
#include "cpassworddlg.h"
#include "monThread.h"
#include "lockscreendialog.h"
//#include "calprmdialog.h"
#include "closepumwindialog.h"
#include "almshowdialog.h"
//#include "onlogdialog.h"
#include "loadheaddialog.h"


#include <QString>
#include <QMovie>

#define BAT_NORMAL  0
#define BAT_CHG  1
#define BAT_DIS  2

#define CHECK_BUTTON_SEC 20

#define DEF_PRESS_A  300
#define DEF_SPEED_A  2000

#define DEF_PRESS_V  50
#define DEF_SPEED_V 2000

//设置页面标题定义
#define WAT_TMP_SET_TITLE 0
#define ART_PRE_SET_TITLE 1
#define ART_SPE_SET_TITLE 2
#define VEI_PRE_SET_TITLE 3
#define VEI_SPE_SET_TITLE 4


//pourFloRLb
//preFloRLb
//preFloRLbV
//pourFloRLbV

#if RUN_ARM_LINUX
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
#else
MainWindow::MainWindow(QWidget *parent) :
	ui(new Ui::MainWindow)
#endif
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/win_Icon.png"));//标题栏左上角小图标
	/**/
    ui->centralWidget->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/images/maiBackground.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    ui->centralWidget->setPalette(palette);

	LoadConfigFile();
	CreateAlmFile();
	g_pWorkThread = new CWorkThread();
	g_pMonThread  = new MonThread();
    
	m_pSysSteDlg = new SystemSetDialog(this);
    m_pSysSteDlg->setGeometry(QRect(0, 40, 1280, 760));
	m_pSysSteDlg->hide();
	
	//m_pCalPrmDialog = new calPrmDialog(this);
    //m_pCalPrmDialog->setGeometry(QRect(0, 40, 1280, 760));
	//m_pCalPrmDialog->hide();

	m_pLockScreenDlg = new LockScreenDialog(this);
	m_pLockScreenDlg->setGeometry(QRect(0, 40, 1280, 760));
	m_pLockScreenDlg->setAttribute(Qt::WA_TranslucentBackground);
	m_pLockScreenDlg->hide();
	
	m_pCurLineEdit = NULL;

	//动脉
    m_pPourPressLE = new MyLineEdit(ui->pourWg);
	m_pPourPressLE->setObjectName(QString::fromUtf8("m_pPourPressLE"));
    m_pPourPressLE->setGeometry(QRect(285, 46, 100, 41));
	m_pPourPressLE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    m_pPourPressLE->setText(" ");
	m_pPourPressLE->setStyleSheet(QString::fromUtf8("#m_pPourPressLE\n"
	"{\n"
	"background:transparent;"
	"}\n"
	"QLineEdit{border-width:0;border-style:outset}"));

	m_pPreSpeedLE = new MyLineEdit(ui->prePourWg);
	m_pPreSpeedLE->setObjectName(QString::fromUtf8("m_pPreSpeedLE"));
    m_pPreSpeedLE->setGeometry(QRect(285, 46, 100, 41));
	m_pPreSpeedLE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    m_pPreSpeedLE->setText(" ");
	m_pPreSpeedLE->clearFocus();
	m_pPreSpeedLE->setStyleSheet(QString::fromUtf8("#m_pPreSpeedLE\n"
	"{\n"
	"background:transparent;"
	"}\n"
	"QLineEdit{border-width:0;border-style:outset}"));

    //静脉
    m_pPourPressLE_V = new MyLineEdit(ui->pourWgV);
	m_pPourPressLE_V->setObjectName(QString::fromUtf8("m_pPourPressLE_V"));
    m_pPourPressLE_V->setGeometry(QRect(285, 46, 100, 41));
	m_pPourPressLE_V->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    m_pPourPressLE_V->setText(" ");
	m_pPourPressLE_V->setStyleSheet(QString::fromUtf8("#m_pPourPressLE_V\n"
	"{\n"
	"background:transparent;"
	"}\n"
	"QLineEdit{border-width:0;border-style:outset}"));

	m_pPreSpeedLE_V = new MyLineEdit(ui->prePourWgV);
	m_pPreSpeedLE_V->setObjectName(QString::fromUtf8("m_pPreSpeedLE_V"));
    m_pPreSpeedLE_V->setGeometry(QRect(285, 46, 100, 41));
	m_pPreSpeedLE_V->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    m_pPreSpeedLE_V->setText(" ");
	m_pPreSpeedLE_V->clearFocus();
	m_pPreSpeedLE_V->setStyleSheet(QString::fromUtf8("#m_pPreSpeedLE_V\n"
	"{\n"
	"background:transparent;"
	"}\n"
	"QLineEdit{border-width:0;border-style:outset}"));

	m_pWtrTmpSetBt = new QPushButton(ui->waterTmpWg);
	m_pWtrTmpSetBt->setObjectName(QString::fromUtf8("m_pWtrTmpSetBt"));
	m_pWtrTmpSetBt->setGeometry(QRect(170, 165, 101, 40));
	m_pWtrTmpSetBt->setLayoutDirection(Qt::LeftToRight);
	m_pWtrTmpSetBt->setStyleSheet(QString::fromUtf8("#m_pWtrTmpSetBt\n"
	"{\n"
	"background: transparent;\n"
	"border-width:-1px;\n"
	"padding:-1px;\n"
	"font-family:simhei;\n"
	"color: rgb(255,255,255);\n"
	"font:20px;\n"
	"}\n"
	"\n"
	"#m_pWtrTmpSetBt:focus{outline: none;\n"
	"}"));
	m_pWtrTmpSetBt->setIconSize(QSize(135, 166));
	m_pWtrTmpSetBt->setCheckable(false);
	m_pWtrTmpSetBt->setChecked(false);
ui->centralWidget->hide();

    //水浴
    QObject::connect(m_pWtrTmpSetBt, SIGNAL(clicked()),this, SLOT(WtrTmpSetBtClick(void)));
    //动脉
	connect(m_pPourPressLE, SIGNAL(clicked()),this, SLOT(PourPressLEClick(void)));
	connect(m_pPreSpeedLE, SIGNAL(clicked()),this, SLOT(PreSpeedLEClick(void)));
	QObject::connect(ui->monTabWidget, SIGNAL(currentChanged(int)),this,SLOT(OnMonTabChanged()));
	
	//静脉
	connect(m_pPourPressLE_V, SIGNAL(clicked()),this, SLOT(PourPressLEClickV(void)));
	connect(m_pPreSpeedLE_V, SIGNAL(clicked()),this, SLOT(PreSpeedLEClickV(void)));
	QObject::connect(ui->VmonTabWidget, SIGNAL(currentChanged(int)),this,SLOT(OnMonTabChangedV()));

    //初始化水浴-温度widget
    InitWaterTmpWg();
    //初始化水浴-水位widget
    //ui->WatRoundBar->setDecimals(0);
    InitWaterGageWg(ui->WatRoundBar);

	//OPenSaveInfoFile();
	OPenOperLogInfoFile();

    g_pWorkThread->start();
	g_pourTstData.tstData.unADataType = 0; //启动默认预灌注
	//ui->monTabWidget->setEnabled(false);
	m_bBPRunFlgA = false;
	m_bBPRunFlgV = false;
	m_bFlashFlg = false;
	m_unWatRunCheckSec = 0;
	m_bAlmBeepFlg = false;
	
	m_bPourStrFlgA = false;
    m_unPumpRunA = 0; //泵运行状态
	m_unPourStaA = 0; //灌注状态
	
	m_bPourStrFlgV = false;
    m_unPumpRunV = 0; //泵运行状态
	m_unPourStaV = 0; //灌注状态

	g_pourTstData.tstData.unADataType = 0;
	ui->almOnOffBtn->setEnabled(false);
	ui->monTabWidget->setEnabled(false);
	//ui->arteryHeadWidget->setEnabled(false);
	//ui->BPStrBtn->setEnabled(true);
	ui->VmonTabWidget->setEnabled(false);
	//ui->veinHeadWidget->setEnabled(false);
	
	m_unPourChangRePourSceA = 0;
	m_unPourChangRePourSceV = 0;
	#if RUN_ARM_LINUX
	CtrlBeep(ALM_LEV_N, 1);
    g_pMonThread->start();//调试关闭看门狗初始化
    //SystemEx("echo 0 > /sys/devices/platform/wdt/soft");
    #endif
	m_unAlmFlag = g_devConfigInfo.basicCfgInfo.unAlmEnFlag;
	g_devConfigInfo.basicCfgInfo.unAlmEnFlag = false;//启动默认关闭告警
	//CheckStartInit();//暂时不用
    m_pSecTmer = new QTimer();
    m_pSecTmer->start(100);
    connect(m_pSecTmer, SIGNAL(timeout()), this, SLOT(SecTimer(void)));
	m_bSysReStrFlg = true;
	m_unFlashMainWinS = 0;
	InitBatteryLog();
	ShowChgIcon(false);

	m_unHourTimer = 0;
	m_bHourBeepFlg = false;

	m_bMonTabChgFlagA = false;
	m_bMonTabChgFlagV = false;

	m_unClickNum = 0;
	m_unEntrCalFlag = 0;

    unSetPumStateDlyA = 200;
	unSetPumStateDlyV = 200;
	unSetWatStateDly  = 200;
	
	m_unAlmLev = 0xff;
    m_bAlmFlashFlg = false;
	m_unFlashAlmSec = 0;

	memset(&m_pBatDevData,0,sizeof(m_pBatDevData));
	m_unBatStat = 0;
	
	InitMovieLog();
}

MainWindow::~MainWindow()
{
    m_pSysSteDlg = NULL;
	delete m_pSysSteDlg;
	//m_pCalPrmDialog = NULL;
	//delete m_pCalPrmDialog;

    m_pLockScreenDlg = NULL;
	delete m_pLockScreenDlg;
	
    m_pSecTmer->stop();
	delete m_pSecTmer;
	m_pCurLineEdit = NULL;
	delete m_pCurLineEdit;

	m_pPourPressLE = NULL;
	delete m_pPourPressLE;
	m_pPreSpeedLE = NULL;
	delete m_pPreSpeedLE;

	m_pPourPressLE_V = NULL;
	delete m_pPourPressLE_V;
	m_pPreSpeedLE_V = NULL;
	delete m_pPreSpeedLE_V;

	//delete m_pWtrTmpSetBt;

    delete ui;
}

void MainWindow::InitMovieLog(void)
{
/*
	ui->centralWidget->setContentsMargins(0,0,0,0);
	ui->MovLabel->setContentsMargins(0,0,0,0);
	m_pMovie= new QMovie();
	m_pMovie->setFileName(":/images/LogOnGIF_L0.gif");
	ui->MovLabel->setMovie(m_pMovie);
	m_pMovie->start();
    m_pMovie->setSpeed(100);*/
    //ui->MovLabel->hide();
	m_pLoadHeadDialog = new LoadHeadDialog(this);
	m_pLoadHeadDialog->setGeometry(QRect(0, 0, 1280, 800));
	m_pLoadHeadDialog->hide();    
}

void MainWindow::SetDevHeadBg(bool bFlag, UINT8 unDev)
{
    if(unDev == DEV_APUMP_TYPE)
    {
        if(bFlag == true)
        {
			ui->arteryHeadWidget->setStyleSheet(QLatin1String("#arteryHeadWidget{\n"
			"background-image: url(:/images/arteryHead_Bg.png);\n"
			"}"));
        }
		else
		{
			ui->arteryHeadWidget->setStyleSheet(QLatin1String("#arteryHeadWidget{\n"
			"background-image: url(:/images/arteryHeadDis_Bg.png);\n"
			"}"));
		}
    }
    if(unDev == DEV_VPUMP_TYPE)
    {
        if(bFlag == true)
        {
			ui->veinHeadWidget->setStyleSheet(QLatin1String("#veinHeadWidget{\n"
			"background-image: url(:/images/veinHead_Bg.png);\n"
			"}"));
        }
		else
		{
			ui->veinHeadWidget->setStyleSheet(QLatin1String("#veinHeadWidget{\n"
			"background-image: url(:/images/veinHeadDis_Bg.png);\n"
			"}"));
		}
    }
}

void MainWindow::LoadConfigFile(void)
{
    QString  strError;
    QString  strError_BAK;
    QString strCfgFilePath = qApp->applicationDirPath()+CONFIG_FILE_NAME;
    QString strCfgFilePath_BAK = qApp->applicationDirPath()+CONFIG_FILE_NAME_BAK;
    QString strPwdFilePath = qApp->applicationDirPath()+ PWD_CONFIG_FILE;

    if(false==LoadDevTypeParam(strError))
    {
        g_devBasicPrmCfg.unDevType = 0;////设备类型
        g_devBasicPrmCfg.unBloPumType = 0; //血泵类型
        g_devBasicPrmCfg.unArteryType = 0; //动脉血泵类型
        g_devBasicPrmCfg.unVeinType = 0;   //静脉血泵类型
        g_devBasicPrmCfg.unWatTRooType = 0; //水浴类型
    	g_devBasicPrmCfg.unAPumCount = 1;
		g_devBasicPrmCfg.unVPumCount = 1;
		g_devBasicPrmCfg.unWatCount = 1;
        InitDefParam();
        //QMessageBox  msgBox(this);
		//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
        //ShowInfo(&msgBox,strError,"错误",QMessageBox::Critical);
		MessageBoxDialog msgBox(this, false);
		msgBox.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
        msgBox.SetMessLabelText(strError);
        msgBox.exec();        
    }
    else if(false==LoadConfigInfo(strCfgFilePath,strError)&&\
            false==LoadConfigInfo(strCfgFilePath_BAK,strError_BAK))
    {
        InitDefParam();
        //QMessageBox  msgBox(this);
		//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
        //ShowInfo(&msgBox,strError,"错误",QMessageBox::Critical);
		MessageBoxDialog msgBox(this, false);
		msgBox.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
        msgBox.SetMessLabelText(strError);
        msgBox.exec();        
    }

	g_devConfigInfo.arteryParm.unDevID = APUM_DEV_BAS_ID;
    m_unAPressSetVal = g_devConfigInfo.arteryParm.unPress;
    m_unASpeedSetVal = g_devConfigInfo.arteryParm.unSpeed;
    g_devConfigInfo.arteryParm.unPress = DEF_PRESS_A;
    g_devConfigInfo.arteryParm.unSpeed = DEF_SPEED_A;
    g_devConfigInfo.arteryParm.unFlow = 0;

    g_devConfigInfo.veinParm.unDevID = VPUM_DEV_BAS_ID;
    m_unVPressSetVal = g_devConfigInfo.veinParm.unPress;
    m_unVSpeedSetVal = g_devConfigInfo.veinParm.unSpeed;
    g_devConfigInfo.veinParm.unPress = DEF_PRESS_V;
    g_devConfigInfo.veinParm.unSpeed = DEF_SPEED_V;
    g_devConfigInfo.veinParm.unFlow = 0;

    g_devConfigInfo.watRooParam.unDevID = WAT_DEV_BAS_ID;
    g_devConfigInfo.watRooParam.unTmpVal = 370;

	g_setPulPrm.unPumType = 0;
	g_setPulPrm.unPulFreq = 75;
	g_setPulPrm.unPulVal = 250;
    memcpy((BYTE*)&g_devConfigInfo_Edt,(BYTE*)&g_devConfigInfo,sizeof(g_devConfigInfo));
    g_devUpdFlags.bBasicFlag  = true;   //基本参数更新
    g_devUpdFlags.bArteryFlag = true;   //动脉参数更新
    g_devUpdFlags.bVeinFlag   = true;   //静脉参数更新
    g_devUpdFlags.bWtrRoomFlag= true;   //水箱参数更新
    g_devUpdFlags.bBatSetFlag = true;   //电池参数更新
    g_devUpdFlags.bAlmSetFlag = true;   //告警配置更新
    g_devUpdFlags.bPourSetFlag = true;   //灌注配置更新
    g_devUpdFlags.bPulSetFlag  = false;
/**/
    if(false==LoadPwdInfo(strPwdFilePath,strError))
    {
        //QMessageBox msgBox;
        //ShowInfo(&msgBox,strError,"错误",QMessageBox::Critical);
        g_pwdCfgInfo.bPwdEnFlg = false;
        strcpy(g_pwdCfgInfo.pAdminStrPwd,"66778899");
        strcpy(g_pwdCfgInfo.pUserStrPwd,"123456");
    }

}

void MainWindow::CreateAlmFile(void)
{
    QString strFilePath;
    strFilePath  = qApp->applicationDirPath()+"/";
    strFilePath += g_devConfigInfo.basicCfgInfo.strLogPath;
    strFilePath += ALM_FILE_NAME;
    if(false==g_pAlmFile->CreateFile(strFilePath))
    {
        printf("CreateFile EROR in AlarmFile!\r\n");
    }
}
void MainWindow::OnMonTabChanged(void)
{
    printf("-------------------Entr OnMonTabChanged Tab:%d \r\n",ui->monTabWidget->currentIndex());
	g_pourTstData.tstData.unADataType = ui->monTabWidget->currentIndex();
	g_pWorkThread->SetDataType(DEV_APUMP_TYPE, g_pourTstData.tstData.unADataType);
	m_bMonTabChgFlagA = true;
	if(m_bPourStrFlgA == false)
	{
	    if(g_pourTstData.tstData.unADataType == STR_POUR)
	    {
	        m_bPourStrFlgA = true;
	    }
	}
}

void MainWindow::setValCanlce(void)
{
	//printf("-------------setValCanlce --------------------\r\n");
    m_pCurLineEdit = NULL;
}
void MainWindow::setValString(QString strIn)
{
/**/
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
		if(m_pCurLineEdit == ui->setWatTmpLE)
		{
			OperLogWatDev operLogWatDev;
			operLogWatDev.unType = OPER_LOG_TYPE_WAT;
			operLogWatDev.unSite = 0;
			GetDateTime(&operLogWatDev.dtCreate);
			operLogWatDev.unEnFlag[0] = g_devConfigInfo_Edt.watRooParam.unEnFlag;
			operLogWatDev.unEnFlag[1] = operLogWatDev.unEnFlag[0];
			operLogWatDev.unTmpVal[0] = g_devConfigInfo_Edt.watRooParam.unTmpVal;
			operLogWatDev.unTmpVal[1] = ui->setWatTmpLE->text().toFloat()*10;
			
			SaveOperLogData((const char*)&operLogWatDev, sizeof(OperLogWatDev));
			SaveOperLogInfo();
		
			g_devConfigInfo_Edt.watRooParam.unTmpVal = ui->setWatTmpLE->text().toFloat()*10;
			g_pCfgDataUI->AddGrpData(CFG_WAT_ROOM_ITEM,\
										sizeof(g_devConfigInfo_Edt.watRooParam),\
										(BYTE*)&g_devConfigInfo_Edt.watRooParam);
		}
		//动脉泵实时设置
		else if(m_pCurLineEdit == ui->preSpeedSetLE || \
			    m_pCurLineEdit == ui->pourPressSetLE)
		{
            UINT32 unCfgItem;
			if(m_pCurLineEdit == ui->preSpeedSetLE)
			{
			    unCfgItem = CFG_ARTERY_SPD_ITEM;
			}
			else if(m_pCurLineEdit == ui->pourPressSetLE)
			{
			    unCfgItem = CFG_ARTERY_PRS_ITEM;
			}

			OperLogPumDev operLogPumDev;
			operLogPumDev.unType = OPER_LOG_TYPE_APUM;
			operLogPumDev.unSite = 0;
			GetDateTime(&operLogPumDev.dtCreate);
			operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.arteryParm.unEnFlag;
			operLogPumDev.unEnFlag[1] = operLogPumDev.unEnFlag[0];
			operLogPumDev.unPress[0] = g_devConfigInfo_Edt.arteryParm.unPress;
			operLogPumDev.unPress[1] = ui->pourPressSetLE->text().toFloat()*10;
			operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.arteryParm.unSpeed;
			operLogPumDev.unSpeed[1] = ui->preSpeedSetLE->text().toInt();
			operLogPumDev.unPress[1] = operLogPumDev.unPress[1]/10;
			operLogPumDev.unPress[1] *= 10;
		
		    SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
			SaveOperLogInfo();			
			g_devConfigInfo_Edt.arteryParm.unSpeed = ui->preSpeedSetLE->text().toInt();
			g_devConfigInfo_Edt.arteryParm.unPress = ui->pourPressSetLE->text().toFloat()*10;
			
			g_pCfgDataUI->AddGrpData(unCfgItem,\
										sizeof(g_devConfigInfo_Edt.arteryParm),\
										(BYTE*)&g_devConfigInfo_Edt.arteryParm);
		}
		/*//静脉血泵实时设置数据*/
		else if(m_pCurLineEdit == ui->preSpeedSetLEV || \
		        m_pCurLineEdit == ui->pourPressSetLEV)
		{
            UINT32 unCfgItem;
			if(m_pCurLineEdit == ui->preSpeedSetLEV)
			{
			    unCfgItem = CFG_VEIN_SPD_ITEM;
			}
			else if(m_pCurLineEdit == ui->pourPressSetLEV)
			{
			    unCfgItem = CFG_VEIN_PRS_ITEM;
			}

			OperLogPumDev operLogPumDev;
			operLogPumDev.unType = OPER_LOG_TYPE_VPUM;
			operLogPumDev.unSite = 0;
			GetDateTime(&operLogPumDev.dtCreate);
			operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.veinParm.unEnFlag;
			operLogPumDev.unEnFlag[1] = operLogPumDev.unEnFlag[0];
			operLogPumDev.unPress[0] = g_devConfigInfo_Edt.veinParm.unPress;
			operLogPumDev.unPress[1] = ui->pourPressSetLEV->text().toFloat()*10;
			operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.veinParm.unSpeed;
			operLogPumDev.unSpeed[1] = ui->preSpeedSetLEV->text().toInt();
			operLogPumDev.unPress[1] = operLogPumDev.unPress[1]/10;
			operLogPumDev.unPress[1] *= 10;
		
		    SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
			SaveOperLogInfo();			
			g_devConfigInfo_Edt.veinParm.unSpeed = ui->preSpeedSetLEV->text().toInt();
			g_devConfigInfo_Edt.veinParm.unPress = ui->pourPressSetLEV->text().toFloat()*10;
			
			g_pCfgDataUI->AddGrpData(unCfgItem,\
										sizeof(g_devConfigInfo_Edt.veinParm),\
										(BYTE*)&g_devConfigInfo_Edt.veinParm);
		}
		else
		{
		    printf("-----------------NO \r\n");
		}
		m_pCurLineEdit = NULL;
    }
}

void MainWindow::SysAutoChangePress(UINT8 unPumType, UINT16 unPress)
{
    printf("Entr MainWindow::SysAutoChangePress unPumType:%u \r\n",unPumType);
	UINT32 unCfgItem;// = CFG_ARTERY_PRS_ITEM;
	
	OperLogPumDev operLogPumDev;
	if(unPumType == DEV_APUMP_TYPE)
	{
	    unCfgItem = CFG_ARTERY_PRS_ITEM;
		
		operLogPumDev.unType = OPER_LOG_TYPE_APUM;
		operLogPumDev.unSite = SYS_CTL;//系统
		GetDateTime(&operLogPumDev.dtCreate);
		operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.arteryParm.unEnFlag;
		operLogPumDev.unEnFlag[1] = operLogPumDev.unEnFlag[0];
		operLogPumDev.unPress[0] = g_devConfigInfo_Edt.arteryParm.unPress;
		operLogPumDev.unPress[1] = unPress;
		operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.arteryParm.unSpeed;
		operLogPumDev.unSpeed[1] = operLogPumDev.unSpeed[0];
		
		SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
		SaveOperLogInfo();			
		g_devConfigInfo_Edt.arteryParm.unSpeed = operLogPumDev.unSpeed[0];
		g_devConfigInfo_Edt.arteryParm.unPress = operLogPumDev.unPress[1];
		
		g_pCfgDataUI->AddGrpData(unCfgItem,\
									sizeof(g_devConfigInfo_Edt.arteryParm),\
									(BYTE*)&g_devConfigInfo_Edt.arteryParm);
	}
	if(unPumType == DEV_VPUMP_TYPE)
	{
	    unCfgItem = CFG_VEIN_PRS_ITEM;
		
		operLogPumDev.unType = OPER_LOG_TYPE_VPUM;
		operLogPumDev.unSite = SYS_CTL;//系统
		GetDateTime(&operLogPumDev.dtCreate);
		operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.veinParm.unEnFlag;
		operLogPumDev.unEnFlag[1] = operLogPumDev.unEnFlag[0];
		operLogPumDev.unPress[0] = g_devConfigInfo_Edt.veinParm.unPress;
		operLogPumDev.unPress[1] = unPress;
		operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.veinParm.unSpeed;
		operLogPumDev.unSpeed[1] = operLogPumDev.unSpeed[0];
		
		SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
		SaveOperLogInfo();			
		g_devConfigInfo_Edt.veinParm.unSpeed = operLogPumDev.unSpeed[0];
		g_devConfigInfo_Edt.veinParm.unPress = operLogPumDev.unPress[1];
		
		g_pCfgDataUI->AddGrpData(unCfgItem,\
									sizeof(g_devConfigInfo_Edt.veinParm),\
									(BYTE*)&g_devConfigInfo_Edt.veinParm);
	}

}

void MainWindow::CheckAutoPress(void)
{
    //printf("Entr MainWindow::CheckAutoPress bBloodBit:%u unPress:%u\r\n",g_devAlmBits.watGrpAlm[0].bBloodBit,g_devConfigInfo_Edt.arteryParm.unPress);
    //if(g_devAlmBits.watGrpAlm.bBloodBit == 1)
    {
        if(g_devConfigInfo_Edt.arteryParm.unPress != SET_AUTO_PRESS)
        {
        	SysAutoChangePress(DEV_APUMP_TYPE, SET_AUTO_PRESS);
        }
		else if(g_devConfigInfo_Edt.veinParm.unPress != SET_POUR_PRESS_V)
		{
		    SysAutoChangePress(DEV_VPUMP_TYPE, SET_POUR_PRESS_V);
		}
    }
}
void MainWindow::SecTimer()
{
/**/
   if(m_bOnLogFlg == false)
   {
       m_unFlashMainWinS++;
	   m_pLoadHeadDialog->show();

	   if(m_unFlashMainWinS < 20)
	       return ;
	   m_pSecTmer->start(2000);
	   m_bOnLogFlg = true;
	   m_pLoadHeadDialog->HideLog();
	   m_unFlashMainWinS = 0;
	   return ;
   }

   m_unFlashMainWinS++;
   m_unFlashAlmSec++;

   if(m_unFlashMainWinS >= 3)//300毫秒
   	{
	    FlashSysTime();
	    StartPourTime();
		OnUpdParams();
		//CheckPumpWaterState();
		
		CheckWtrRomOnOffBt();	
		CheckPourStopA();
		//CheckPourStopV();不用
		CheckPourPrmA();
		//CheckPourPrmV();
		CheckWatStop();//检测水浴加温停止
		m_unFlashMainWinS = 0;
		//CheckStart();不用
		//CheckAutoPress();不用
		//SetBeepHour();不用
   	}
	if(m_unFlashAlmSec >= m_unFlashHz)
	{
	   TaskAlmPro();
	   m_unFlashAlmSec = 0;
	}
    //500ms
	FlashWaterRoomInfo();
	FlashPumpAInfo();
	FlashPumpVInfo();
	CalCheckClicked();
	FlashBattryInfo();
	BeepRestart();

#if 0
    //测试看门狗
	if(++m_unSliderVal >= 5)
	{
	    printf("1-------------------SetWatchdog -------\r\n");
		SetWatchdog();
		m_unSliderVal = 0;
		printf("2-------------------SetWatchdog -------\r\n");
	}
#endif

#if 0 //test water gage val
    if(++m_unSliderVal > 99)
    {
        m_unSliderVal = 0;
    }
	m_unSliderVal++;
	//m_pRPBar->setValue(m_unSliderVal);
	ui->batWidget->setValue(m_unSliderVal);
	/*
    QString str = QString("%1%").arg(m_unSliderVal);
    ui->gageValLabel->setText(str);
    ui->gageSlider->setValue(m_unSliderVal);

    ui->setWatTmpLE->setText(str);
    qDebug("SecTimevalue,ui->gageSlider->height()r m_unSliderVal %d",m_unSliderVal);*/
#endif

#if 0 //teat button
    bool bBtn;

    bBtn = ui->BPStrBtn->isChecked();
    qDebug("get-BPStrBtn %d",bBtn);
    bBtn =! bBtn;
    qDebug("------------set-BPStrBtn %d--------------------",bBtn);
    ui->BPStrBtn->setChecked(bBtn);

#endif

#if 0 //测试蜂鸣器
    if(m_unSliderVal < 11)
		m_unSliderVal++;
    if(m_unSliderVal == 10)
    {
        on_almOnOffBtn_clicked(1);
    }
#endif
    g_bMainWindRunFlg = true;
}

void MainWindow::RevCloseHead(void)
{
    printf("--------------------------------------RevCloseHead----------------\r\n");
	ui->centralWidget->show();
	g_pWorkThread->SetAllDevTimeOutEn();
	g_devConfigInfo.basicCfgInfo.unAlmEnFlag = m_unAlmFlag;
}

//灌注时长
void MainWindow::StartPourTime(void)
{
    UINT32 unTotalSecs;

	if(m_bPourStrFlgA == false && m_bPourStrFlgV == false)//开始灌注后才计时
	{
		g_pourTstData.tstInfo.unTotalTime = 0;
	}
	unTotalSecs = g_pourTstData.tstInfo.unTotalTime;
	/*
	if(unTotalSecs%3600 == 0 && unTotalSecs != 0)
	{
	    m_bHourBeepFlg = true;
		ui->almOnOffBtn->setChecked(true);
    	ui->almOnOffBtn->setEnabled(true);
		printf("One Hour Set Beep Flag -----------------------------\r\n");
	}*/
	
    QString strHou = QString("%1:").arg(unTotalSecs/3600,2,10,QLatin1Char('0'));
    unTotalSecs = unTotalSecs%3600;
    QString strMin = QString("%1:").arg(unTotalSecs/60,2,10,QLatin1Char('0'));
    unTotalSecs = unTotalSecs%60;
    QString strSec = QString("%1").arg(unTotalSecs,2,10,QLatin1Char('0'));
    ui->strTmtLabel->setText(strHou+strMin+strSec);//灌注时长
    //ui->strTmtLabel->setText(tr("显示中文"));
}

void MainWindow::FlashSysTime(void)
{
    DateTime dtCurDateTime;
    GetDateTime(&dtCurDateTime);
    ui->sysTmtLabel->setText(DateTimeToString(&dtCurDateTime));
}

//刷新水浴温度、压力
void MainWindow::FlashWaterRoomInfo(void)
{
    if(g_devConfigInfo.watRooParam.unEnFlag == false)
    {
		m_unWatRunState = 0;
		return ;
    }
	WatDevData watDevData;
	memset(&watDevData,0,sizeof(watDevData));
	g_pWorkThread->GetDevData(DEV_WAT_TYPE, 0, (BYTE*)&watDevData,sizeof(WatDevData));

    m_unWatRunState = watDevData.unRunFlg;

	if(m_unWatRunState == 0 && \
	   1==ui->wtrRomOnOffBt->isChecked() && \
	   m_unBatStat != BAT_DIS)
	{
		if(unSetWatStateDly == 0)
		{
			g_pWorkThread->SetDevState(DEV_WAT_TYPE);
			unSetWatStateDly = 10*30;
		}
	}
	if(unSetWatStateDly)
	{
		unSetWatStateDly--;
	}
    m_pRPBar->setValue(watDevData.unWatLine);
	ui->showTmpLabel->setText(ValueToString(watDevData.unTmpVal,10,1));//温度
}

//刷新动脉血泵数据
void MainWindow::FlashPumpAInfo(void)
{
    if(g_devConfigInfo.arteryParm.unEnFlag == false)
    {
        m_unPumpRunA = 0;
        return ;
    }
	
	PumpDevData pumDevData;
	memset(&pumDevData,0,sizeof(pumDevData));
	g_pWorkThread->GetDevData(DEV_APUMP_TYPE, 0, (BYTE*)&pumDevData,sizeof(PumpDevData));

    m_unPumpRunA = pumDevData.unRunFlg;
	m_unPourStaA = pumDevData.unPourSta;


	//printf("11-StaA:%d-------RunFlgA:%d---------------\r\n",m_unPourStaA,m_unPumpRunA);
	if(m_bMonTabChgFlagA == true)
	{
	    if(m_unPourStaA == g_pourTstData.tstData.unADataType)
	    {
	        UINT8 unCfgItem = 0;
	        if(m_unPourStaA == PRE_POUR)
	        {
	            unCfgItem = CFG_ARTERY_SPD_ITEM;
	        }
			else if(m_unPourStaA == STR_POUR)
			{
				unCfgItem = CFG_ARTERY_PRS_ITEM;
			}
	        SetDefPumPrmA(SWT_CTL, unCfgItem, DEF_PRESS_A, DEF_SPEED_A);
			m_bMonTabChgFlagA = false;
			printf("StaA:%d------------m_unPourStaA == g_pourTstData.tstData.unADataType----------\r\n",m_unPourStaA);
	    }
	}
	else
	{
	    if(m_unPumpRunA == 0 && 1==ui->BPStrBtn->isChecked())
	    {
	        if(unSetPumStateDlyA == 0)
	        {
	            g_pWorkThread->SetDevState(DEV_APUMP_TYPE);
				unSetPumStateDlyA = 10*30;
	        }
	    }
	    if(unSetPumStateDlyA)
	    {
			unSetPumStateDlyA--;
	    }
	}
	//printf("MainWindow::unPrssVal:%u unSpeeVal:%u \r\n",pumDevData.unPrssVal,pumDevData.unSpeeVal);

    ui->preSpeedLb->setText(ValueToString(pumDevData.unSpeeVal,1,0));
	
	if(m_unPumpRunA == 1)
	{
		ui->preFlowLb->setText(ValueToString(pumDevData.unFlowVal,1,0));
		ui->pourFlowLb->setText(ValueToString(pumDevData.unFlowVal,1,0));
	}
	else
	{
	    ui->preFlowLb->setText("--");
		ui->pourFlowLb->setText("--");
	}
	ui->preTmpLb->setText(ValueToString(pumDevData.unTmpVal,10,1));
	//ui->prePressLb->setText(ValueToString(pumDevData.unPrssVal,10,1));
	if(pumDevData.unPrssVal < 0)
	{
	    ui->prePressLb->setText(ValueToString((pumDevData.unPrssVal-5)/10,1,0));
	}
	else
	{
		ui->prePressLb->setText(ValueToString((pumDevData.unPrssVal+5)/10,1,0));
	}

    //ui->pourPressLb->setText(ValueToString(pumDevData.unPrssVal,10,1));
    if(pumDevData.unPrssVal < 0)
    {
        ui->pourPressLb->setText(ValueToString((pumDevData.unPrssVal-5)/10,1,0));
    }
	else
	{
    	ui->pourPressLb->setText(ValueToString((pumDevData.unPrssVal+5)/10,1,0));
	}
	
	
	ui->pourTmpLb->setText(ValueToString(pumDevData.unTmpVal,10,1));
	ui->pourSpeedLb->setText(ValueToString(pumDevData.unSpeeVal,1,0));

    if(m_unPourStaA == STR_POUR && \
	   pumDevData.unPrssVal > 0 && \
	   pumDevData.unFlowVal > 0 && \
	   m_unPumpRunA == 1)
    {
        UINT32 unFloR = pumDevData.unPrssVal*100;
		unFloR = unFloR/pumDevData.unFlowVal;
		
        ui->pourFloRLb->setText(ValueToString(unFloR,1,0));
		ui->preFloRLb->setText(ValueToString(unFloR,1,0));
    }
	else
	{
	    ui->pourFloRLb->setText("--");
		ui->preFloRLb->setText("--");
	}
}
//刷新静脉血泵数据
void MainWindow::FlashPumpVInfo(void)
{
    if(g_devConfigInfo.veinParm.unEnFlag == false)
    {
        //m_unPumpRunV = 0;
        return ;
    }
	
	PumpDevData pumDevData;
	memset(&pumDevData,0,sizeof(pumDevData));
	g_pWorkThread->GetDevData(DEV_VPUMP_TYPE, 0, (BYTE*)&pumDevData,sizeof(PumpDevData));

    m_unPumpRunV = pumDevData.unRunFlg;
	m_unPourStaV = pumDevData.unPourSta;
	//printf("MainWindow::unPrssVal:%u unSpeeVal:%u \r\n",pumDevData.unPrssVal,pumDevData.unSpeeVal);
	if(m_bMonTabChgFlagV == true)
	{
	    if(m_unPourStaV == g_pourTstData.tstData.unVDataType)
	    {
	        UINT8 unCfgItem = 0;
	        if(m_unPourStaV == PRE_POUR)
	        {
	            unCfgItem = CFG_VEIN_SPD_ITEM;
	        }
			else if(m_unPourStaV == STR_POUR)
			{
				unCfgItem = CFG_VEIN_PRS_ITEM;
			}
	        SetDefPumPrmV(SWT_CTL, unCfgItem, DEF_PRESS_V, DEF_SPEED_V);
			m_bMonTabChgFlagV = false;
			printf("StaV:%d------------m_unPourStaV == g_pourTstData.tstData.unVDataType----------\r\n",m_unPourStaV);
	    }
	}
	else
	{
	    if(m_unPumpRunV == 0 && 1==ui->BPStrBtnV->isChecked())
	    {
	        if(unSetPumStateDlyV == 0)
	        {
	            g_pWorkThread->SetDevState(DEV_VPUMP_TYPE);
				unSetPumStateDlyV = 10*30;
	        }
	    }

	   if(unSetPumStateDlyV)
	   {
		   unSetPumStateDlyV--;
	   }
	}


    ui->preSpeedLbV->setText(ValueToString(pumDevData.unSpeeVal,1,0));
	if(m_unPumpRunV == 1)
	{
		ui->preFlowLbV->setText(ValueToString(pumDevData.unFlowVal,1,0));
		ui->pourFlowLbV->setText(ValueToString(pumDevData.unFlowVal,1,0));
	}
	else
	{
	    ui->preFlowLbV->setText("--");
		ui->pourFlowLbV->setText("--");
	}
	ui->preTmpLbV->setText(ValueToString(pumDevData.unTmpVal,10,1));
	ui->prePressLbV->setText(ValueToString(pumDevData.unPrssVal,10,1));

    ui->pourPressLbV->setText(ValueToString(pumDevData.unPrssVal,10,1));
	
	ui->pourTmpLbV->setText(ValueToString(pumDevData.unTmpVal,10,1));
	ui->pourSpeedLbV->setText(ValueToString(pumDevData.unSpeeVal,1,0));

    if(m_unPourStaV == STR_POUR && \
	   pumDevData.unPrssVal > 0 && \
	   pumDevData.unFlowVal > 0 && \
	   m_unPumpRunV == 1)
    {
        UINT32 unFloR = pumDevData.unPrssVal*1000;
		unFloR = unFloR/pumDevData.unFlowVal;
		
        ui->pourFloRLbV->setText(ValueToString(unFloR,10,1));
		ui->preFloRLbV->setText(ValueToString(unFloR,10,1));
    }
	else
	{
	    ui->pourFloRLbV->setText("--");
		ui->preFloRLbV->setText("--");
	}
}


//初始化水浴-温度
void MainWindow::InitWaterTmpWg(void)
{
    //ui->waterTmpWg->setEnabled(false);
	m_unWatRunState = 0; //水浴运行状态
	ui->setWatTmpLE->setEnabled(false);
    ui->setWatTmpLE->setText(ValueToString(g_devConfigInfo_Edt.watRooParam.unTmpVal,10,1));
}

//初始化水浴-压力
void MainWindow::InitWaterGageWg(QRoundProgressBar* bar)
{
	m_pRPBar = bar;

	QGradientStop stop1;
	stop1.first = 0;stop1.second = QColor(255, 204, 143);
	QGradientStops s;
	s.append(stop1);
	m_pRPBar->setDataColors(s);

    m_pRPBar->setDecimals(0);
    m_unSliderVal = 0;
    m_pRPBar->setFormat("%v");
    m_pRPBar->setRange(0, 100);
    m_pRPBar->setValue(0);
	m_pRPBar->setTextColor(QColor(255, 255, 255));
}
//初始化电池-图标
void MainWindow::InitBatteryLog(void)
{
    ui->batWidget->setRange(0, 100);
    ui->batWidget->setValue(0);
}

void MainWindow::OnUpdParams(void)
{
    ui->setWatTmpLE->setText(ValueToString(g_devConfigInfo_Edt.watRooParam.unTmpVal,10,1));

	//动脉-预灌注
	ui->preSpeedSetLE->setText(QString("%1").arg(g_devConfigInfo_Edt.arteryParm.unSpeed));
    //ui->prePressSetLb->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unPress,10,1));
    //动脉-灌注
    ui->pourPressSetLE->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unPress/10,1,0));
    //ui->pourSpeedSetLb->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unSpeed,10,1));

	//静脉-预灌注
	ui->preSpeedSetLEV->setText(QString("%1").arg(g_devConfigInfo_Edt.veinParm.unSpeed));
    //ui->prePressSetLb->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unPress,10,1));
    //静脉-灌注
    ui->pourPressSetLEV->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unPress,10,1));
    //ui->pourSpeedSetLb->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unSpeed,10,1));
}
/*
//初始化水位槽
void MainWindow::connectToSlider(QRoundProgressBar* bar)
{
    m_pRPBar = bar;
    m_pRPBar->setRange(0, 100);
    m_pRPBar->setValue(0);
}
*/


//血泵按钮响应
void MainWindow::on_BPStrBtn_clicked(bool checked)
{
    printf("on_BPStrBtn_clicked ---------A %d ",checked);

	if(checked == 1)
	{
		g_devConfigInfo.arteryParm.unSpeed = SET_SPEED_DEF;
		g_devConfigInfo_Edt.arteryParm.unSpeed = SET_SPEED_DEF;
		ui->monTabWidget->setEnabled(true);
		SetDevHeadBg(true, DEV_APUMP_TYPE);
		g_pWorkThread->StartBloodPump(DEV_APUMP_TYPE,0);
		m_bBPRunFlgA = true;
		//ui->monTabWidget->setTabEnabled(0,true);
		ui->monTabWidget->setCurrentIndex(0);//启动血泵默认为预灌注状态
	}
	else if(checked == 0)
	{
		m_unClosePumDev = DEV_APUMP_TYPE;
		ClosePumWinDialog  closePumWin(this);
		closePumWin.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
		closePumWin.setWindowModality(Qt::ApplicationModal);
		closePumWin.exec();
        
	}
	unSetPumStateDlyA = 10*30;
}
/**/
void MainWindow::closePumWinBack(bool bState)
{
    if(m_unClosePumDev == DEV_APUMP_TYPE)
    {
		if(bState == true)
		{
			m_unPumpRunA = 0;
			m_unPourStaA = 0;
			ui->monTabWidget->setCurrentIndex(PRE_POUR);
			ui->monTabWidget->setEnabled(false);
			SetDevHeadBg(false, DEV_APUMP_TYPE);
			on_almOnOffBtn_clicked(0);
			g_devConfigInfo.arteryParm.unSpeed = SET_SPEED_DEF;
			g_devConfigInfo_Edt.arteryParm.unSpeed = SET_SPEED_DEF;
			g_pWorkThread->StopBloodPump(DEV_APUMP_TYPE,0);
            ClosePumCleanAlm(DEV_APUMP_TYPE);
		}
		else
		{
			ui->BPStrBtn->setChecked(1);//取消不关闭
		}
    }
    else if(m_unClosePumDev == DEV_VPUMP_TYPE)
    {
		if(bState == true)
		{
		    m_unPumpRunV = 0;
			m_unPourStaV = 0;
			ui->VmonTabWidget->setCurrentIndex(PRE_POUR);
			ui->VmonTabWidget->setEnabled(false);
			SetDevHeadBg(false, DEV_VPUMP_TYPE);
			on_almOnOffBtn_clicked(0);
			g_devConfigInfo.veinParm.unSpeed = SET_SPEED_DEF;
			g_devConfigInfo_Edt.veinParm.unSpeed = SET_SPEED_DEF;
			g_pWorkThread->StopBloodPump(DEV_VPUMP_TYPE,0);
			ClosePumCleanAlm(DEV_VPUMP_TYPE);
		}
		else
		{
			ui->BPStrBtnV->setChecked(1);//取消不关闭
		}
    }
	m_unClosePumDev = 0;
}

//检测泵和水浴状态，并和下位机匹配
void MainWindow::CheckPumpWaterState(void)
{   
    //动脉
	if(false==g_pWorkThread->IsPumpRuning(0) && \
	   true == m_bBPRunFlgA)
	{
	    ui->BPStrBtn->setChecked(0);
		ui->monTabWidget->setEnabled(false);
		SetDevHeadBg(false, DEV_APUMP_TYPE);
		m_bBPRunFlgA = false;
		m_bPourStrFlgA = false;
	}
	//静脉
	if(false==g_pWorkThread->IsPumpRuning(1) && \
	   true == m_bBPRunFlgV)
	{
	    ui->BPStrBtnV->setChecked(0);
		ui->VmonTabWidget->setEnabled(false);
		SetDevHeadBg(false, DEV_VPUMP_TYPE);
		m_bBPRunFlgV = false;
		m_bPourStrFlgV = false;
	}	   

    //系统重启检测匹配下位机状态
    if(m_bSysReStrFlg == true)
    {
        m_pSecTmer->start(100);

		//动脉
		if(m_unPumpRunA == 1)
		{
		    if(0 == ui->BPStrBtn->isChecked())
		    {
		        ui->BPStrBtn->setChecked(1);
				ui->monTabWidget->setEnabled(true);
				SetDevHeadBg(true, DEV_APUMP_TYPE);
				g_pWorkThread->StartBloodPump(DEV_APUMP_TYPE,0);
				m_bBPRunFlgA = true;
				g_pWorkThread->SetPumpRuning(0, true);
				g_pWorkThread->SynPourState(m_unPourStaA,0);
				ui->monTabWidget->setCurrentIndex(m_unPourStaA);//启动血泵灌注状态与下位机一致
				g_devConfigInfo.arteryParm.unPress = m_unAPressSetVal;
				g_devConfigInfo.arteryParm.unSpeed = m_unASpeedSetVal;
				g_devConfigInfo_Edt.arteryParm.unPress = m_unAPressSetVal;
				g_devConfigInfo_Edt.arteryParm.unSpeed = m_unASpeedSetVal;
				printf("-------------reboot--------m_unPourStaA:%u \r\n",m_unPourStaA);
				if(0 == ui->BPStrBtn->isChecked())
				{
					ui->BPStrBtn->setChecked(1);
				}
		    }
		}
        //静脉
		if(m_unPumpRunV == 1)
		{
		    if(0 == ui->BPStrBtnV->isChecked())
		    {
		        ui->BPStrBtnV->setChecked(1);
				ui->VmonTabWidget->setEnabled(true);
				SetDevHeadBg(true, DEV_VPUMP_TYPE);
				g_pWorkThread->StartBloodPump(DEV_VPUMP_TYPE,0);
				m_bBPRunFlgV = true;
				g_pWorkThread->SetPumpRuning(1, true);
				g_pWorkThread->SynPourState(m_unPourStaV,1);
				ui->VmonTabWidget->setCurrentIndex(m_unPourStaV);//启动血泵灌注状态与下位机一致
				printf("-------------reboot--------m_unPourStaV:%u \r\n",m_unPourStaV);
				
				g_devConfigInfo.veinParm.unPress = m_unVPressSetVal;
				g_devConfigInfo.veinParm.unSpeed = m_unVSpeedSetVal;
				g_devConfigInfo_Edt.veinParm.unPress = m_unVPressSetVal;
				g_devConfigInfo_Edt.veinParm.unSpeed = m_unVSpeedSetVal;
				if(0 == ui->BPStrBtnV->isChecked())
				{
				    ui->BPStrBtnV->setChecked(1);
				}
		    }
		}
		//水浴
		if(m_unWatRunState == 1)
		{
		    if(0 == ui->wtrRomOnOffBt->isChecked())
		    {
		        ui->wtrRomOnOffBt->setChecked(1);
				//ui->waterTmpWg->setEnabled(true);
				SetWaterWidgetBg(true);
				//printf("----------------------------------------------SetWaterWidgetBg--1\r\n");
				SetDevHeadBg(true, DEV_WAT_TYPE);
		    }
		}
		m_bSysReStrFlg = false;
    }
}

//水浴开关按钮响应
void MainWindow::on_wtrRomOnOffBt_clicked(bool checked)
{
    UINT8 unOpenFlg;
    if(checked)
    {
		unOpenFlg = DEV_ON;
    }
    else
    {
		unOpenFlg = DEV_OFF;
    }
/**/
	if(unOpenFlg == DEV_ON && \
	  (g_devAlmBits.watGrpAlm.bLinLBits || g_devAlmBits.watGrpAlm.bLinUBits))
	{
	    ui->wtrRomOnOffBt->setChecked(0);
		SetWaterWidgetBg(false);
		//printf("----------------------------------------------SetWaterWidgetBg--2\r\n");
	    QString strError = QString("水位告警!");
	    g_pWorkThread->ShowStringInfo(strError.toStdString().c_str(),DLG_SHOW,ICON_ERROR);
	}
	else
	{
		g_pWorkThread->setOpenWatRoom(0, unOpenFlg, 0);
		SetWaterWidgetBg(checked);
		//printf("----------------------------------------------SetWaterWidgetBg--3\r\n");
	}
	m_unWatRunCheckSec = 20;
	unSetWatStateDly = 10*30;
}
//检测水浴开关是否打开
void MainWindow::CheckWtrRomOnOffBt(void)
{  
	if(ui->wtrRomOnOffBt->isChecked() == 1)
	{
	    if(m_unWatRunState == DEV_OFF && m_unWatRunCheckSec == 0)
	    {
	       ui->wtrRomOnOffBt->setChecked(0);
		   //ui->waterTmpWg->setEnabled(false);
		   SetWaterWidgetBg(false);
		   //printf("----------------------------------------------SetWaterWidgetBg--4\r\n");
	    }
	}

	if(m_unWatRunCheckSec > 0)
	{
	    m_unWatRunCheckSec--;
	}
}

//水浴温度设置按钮响应
void MainWindow::WtrTmpSetBtClick(void)
{
	//qDebug()<<"on_wtrTmpSetBt_clicked";
    if(m_pCurLineEdit == NULL)
    {
	    m_pCurLineEdit = ui->setWatTmpLE;
			
	    SetValDialog  setValDialog(this);
		setValDialog.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
	    setValDialog.SetDefaultVal(ui->setWatTmpLE->text(),WAT_TMP_SET_TITLE);
		setValDialog.SetValLimit(SET_TMP_LIMIT_MIN,g_devConfigInfo.watRooParam.unTmpValLimt,SET_STEP_1,10,1,1);
	    setValDialog.setWindowModality(Qt::ApplicationModal);
	    setValDialog.exec();
    }
	else
	{
	     qDebug()<<"m_pCurLineEdit != NULL";
	}
}

//动脉预灌注调节转速
void MainWindow::PourPressLEClick(void)
{
    //qDebug()<<"PourPressLEClick";
	
	if(m_pCurLineEdit == NULL)
	{
	    m_pCurLineEdit = ui->pourPressSetLE;//m_pPourPressLE;
		
	    SetValDialog  setValDialog(this);
		setValDialog.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
	    setValDialog.SetDefaultVal(ui->pourPressSetLE->text(),ART_PRE_SET_TITLE);
		setValDialog.SetValLimit(SET_PRESS_LIMIT_MIN,g_devConfigInfo.arteryParm.unPressLimt,SET_STEP_1,1,0,1);
	    setValDialog.setWindowModality(Qt::ApplicationModal);
	    setValDialog.exec();
	}
	else
	{
	     qDebug()<<"m_pCurLineEdit != NULL";
	}
}

//静脉预灌注调节转速
void MainWindow::PreSpeedLEClick(void)
{
    //qDebug()<<"PreSpeedLEClick";
    if(m_pCurLineEdit == NULL)
    {
		m_pCurLineEdit = ui->preSpeedSetLE;

	    SetValDialog  setValDialog(this);
		setValDialog.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
	    setValDialog.SetDefaultVal(ui->preSpeedSetLE->text(),ART_SPE_SET_TITLE);
		setValDialog.SetValLimit(SET_SPEED_LIMIT_MIN,g_devConfigInfo.arteryParm.unSpeedLimt,SET_STEP_1,1,0,10);
	    setValDialog.setWindowModality(Qt::ApplicationModal);
	    setValDialog.exec();
    }
	else
	{
	     qDebug()<<"m_pCurLineEdit != NULL";
	}
}


//进入系统设置按钮
void MainWindow::on_sysSetBtn_clicked()
{
	m_pSysSteDlg->show();
	m_pSysSteDlg->FlashCfgDevPrm(&m_pBatDevData);
	
}

void MainWindow::on_almShowBtn_clicked()
{

    //AlmShowDlg  almShowDlg(this);
    AlmShowDialog almShowDlg(this);
    //almShowDlg.setStyleSheet("QComboBox QAbstractItemView::item {height: 30px;}");
	almShowDlg.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
    if(QDialog::Accepted==almShowDlg.exec())
    {
    }
}
/*
void MainWindow::TaskAlmPro(void)
{	
    QString strAlmText;
    //CheckAlmBeep();
	bool bHasAlarm = false;
	UINT8 unGetLevel;

	bHasAlarm = HasAlarm();

	if(true == bHasAlarm)
	{
		ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
		"background-image: url(:/images/alarmed_Icon.png);\n"
		"   font-family:simhei;\n"
		"   color:rgb(255,255,255);\n"
		"   font:bold;\n"
		"   font:26px;\n"
		"}"));
		if(g_almItemEx.almItem.unAlmID != 0 && g_almItemEx.almItem.unAlmFlag != 0)
		{
			strAlmText = AlmIDToName(g_almItemEx.almItem.unAlmID, &unGetLevel);
		}
		else
		{
			strAlmText = CheckOneAlmShow();
			if(strAlmText != " ")
			{
			    if(g_almItemEx.unUpdFlag == 0 && m_bCloseBeepFlag == true)
			    {
			        g_almItemEx.unUpdFlag = 1;
			    }
			}
			else
			{
				ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
				"background-image: url(:/images/alarm.png);\n"
				"	font-family:simhei;\n"
				"	color:rgb(255,255,255);\n"
				"	font:bold;\n"
				"	font:26px;\n"
				"}"));
				if(1 == ui->almOnOffBtn->isChecked() && m_bHourBeepFlg == false)
				{
		            ui->almOnOffBtn->setChecked(0);
		            ui->almOnOffBtn->setEnabled(0);
					g_pWorkThread->CtrlBeep(0);
					m_bAlmBeepFlg = false;
				}
				ui->almShowLb->setText(" ");			
			}
		}
		ui->almShowLb->setText(strAlmText);
	}
	else
	{
		ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
		"background-image: url(:/images/alarm.png);\n"
		"	font-family:simhei;\n"
		"	color:rgb(255,255,255);\n"
		"	font:bold;\n"
		"	font:26px;\n"
		"}"));
		if(1 == ui->almOnOffBtn->isChecked() && m_bHourBeepFlg == false)
		{
            ui->almOnOffBtn->setChecked(0);
            ui->almOnOffBtn->setEnabled(0);
			g_pWorkThread->CtrlBeep(0);
			m_bAlmBeepFlg = false;
		}
		ui->almShowLb->setText(" ");	
	}
	CheckAlmBeep();
}
*/
void MainWindow::TaskAlmPro(void)
{	
	QString strAlmText = " ";
	static QString strAlmTextOld = " ";
	//CheckAlmBeep();
	bool bHasAlarm = false;
	UINT8 unGetLevel = 0;

	bHasAlarm = HasAlarm();

    //bHasAlarm = true;
	if(true == bHasAlarm)
	{
		strAlmText = CheckOneAlmShow(&unGetLevel);
		//unGetLevel = ALM_LEV_M;
		if(unGetLevel == ALM_LEV_H)// && m_unAlmLev != ALM_LEV_H)
		{
			ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
			"background-image: url(:/images/alarmed_Icon.png);\n"
			"	font-family:simhei;\n"
			"	color:rgb(255,255,255);\n"
			"	font:bold;\n"
			"	font:26px;\n"
			"}"));
		}
		else if(unGetLevel == ALM_LEV_M)// && m_unAlmLev != ALM_LEV_M)
		{
			ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
			"background-image: url(:/images/alarmed_m_Icon.png);\n"
			"	font-family:simhei;\n"
			"	color:rgb(0,0,0);\n"
			"	font:bold;\n"
			"	font:26px;\n"
			"}"));
		}
		else if(unGetLevel == ALM_LEV_L)// && m_unAlmLev != ALM_LEV_L)
		{
		    m_bAlmFlashFlg = false;
			ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
			"background-image: url(:/images/alarmed_l_Icon.png);\n"
			"	font-family:simhei;\n"
			"	color:rgb(0,0,0);\n"
			"	font:bold;\n"
			"	font:26px;\n"
			"}"));		
		}
		
		if(m_bAlmFlashFlg == true)
		{
			ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
			"background-image: url(:/images/alarm.png);\n"
			"	font-family:simhei;\n"
			"	color:rgb(255,255,255);\n"
			"	font:bold;\n"
			"	font:26px;\n"
			"}"));
		}
		ui->almShowLb->setText(strAlmText);
		m_bAlmFlashFlg =! m_bAlmFlashFlg;
		if(strAlmText != strAlmTextOld)
		{
		    m_unBeepRestSec = 0;
			strAlmTextOld = strAlmText;
		}
		if(unGetLevel == ALM_LEV_H)
		{
		    m_unFlashHz = 3;
		}
		else if(unGetLevel == ALM_LEV_M)
		{
		    m_unFlashHz = 10;
		}
	}
	else
	{
	    ui->almShowLb->setText("系统正常运行");
		ui->almShowLb->setStyleSheet(QLatin1String("#almShowLb{\n"
		"background-image: url(:/images/alarm.png);\n"
		"	font-family:simhei;\n"
		"	color:rgb(255,255,255);\n"
		"	font:bold;\n"
		"	font:26px;\n"
		"}"));	
		if(1 == ui->almOnOffBtn->isChecked() && m_bHourBeepFlg == false)
		{
			ui->almOnOffBtn->setChecked(0);
			ui->almOnOffBtn->setEnabled(0);
			CtrlBeep(unGetLevel, 1);
			m_bAlmBeepFlg = false;
		}
		ui->almShowLb->setText(" ");	
	}
	if(m_unAlmLev != unGetLevel)
	{
	    //设置下位机亮灯
	    g_pWorkThread->SetAlmLedState(unGetLevel);
	}
	CheckAlmBeep(unGetLevel);
}

void MainWindow::CtrlBeep(UINT8 unCtrlLev, UINT8 checked)
{
    if(unCtrlLev > ALM_LEV_A)
		return ;
    QString strPathName;


    strPathName = QString("echo %1 > /sys/class/gpio/gpio17/value").arg(1);
	SystemEx(strPathName.toStdString().c_str());
    strPathName = QString("echo %1 > /sys/class/gpio/gpio18/value").arg(1);
	SystemEx(strPathName.toStdString().c_str());
	
	strPathName = QString("echo %1 > /sys/class/gpio/gpio19/value").arg(1);
	SystemEx(strPathName.toStdString().c_str());
    strPathName = QString("echo %1 > /sys/class/gpio/gpio20/value").arg(1);
	SystemEx(strPathName.toStdString().c_str());
	
	strPathName = QString("echo %1 > /sys/class/gpio/gpio21/value").arg(1);
	SystemEx(strPathName.toStdString().c_str());
	strPathName = QString("echo %1 > /sys/class/gpio/gpio22/value").arg(1);
	SystemEx(strPathName.toStdString().c_str());
	
    if(unCtrlLev == ALM_LEV_H)
    {
        strPathName = QString("echo %1 > /sys/class/gpio/gpio17/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
		strPathName = QString("echo %1 > /sys/class/gpio/gpio18/value").arg(checked);
    }
    else if(unCtrlLev == ALM_LEV_M)
    {
        strPathName = QString("echo %1 > /sys/class/gpio/gpio19/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
		strPathName = QString("echo %1 > /sys/class/gpio/gpio20/value").arg(checked);
    }
    else if(unCtrlLev == ALM_LEV_L)
    {
        strPathName = QString("echo %1 > /sys/class/gpio/gpio23/value").arg(1);
		SystemEx(strPathName.toStdString().c_str());
		strPathName = QString("echo %1 > /sys/class/gpio/gpio24/value").arg(0);
		SystemEx(strPathName.toStdString().c_str());
		
        strPathName = QString("echo %1 > /sys/class/gpio/gpio21/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
		strPathName = QString("echo %1 > /sys/class/gpio/gpio22/value").arg(checked);
    }
	else if(unCtrlLev == ALM_LEV_A)
	{
        strPathName = QString("echo %1 > /sys/class/gpio/gpio23/value").arg(0);
		SystemEx(strPathName.toStdString().c_str());
		strPathName = QString("echo %1 > /sys/class/gpio/gpio24/value").arg(1);
		SystemEx(strPathName.toStdString().c_str());
		
		strPathName = QString("echo %1 > /sys/class/gpio/gpio22/value").arg(checked);
	}

	/*
	else if(unCtrlLev == ALM_LEV_N)
	{
	    strPathName = QString("echo %1 > /sys/class/gpio/gpio17/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
	    strPathName = QString("echo %1 > /sys/class/gpio/gpio18/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
		
		strPathName = QString("echo %1 > /sys/class/gpio/gpio19/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
	    strPathName = QString("echo %1 > /sys/class/gpio/gpio20/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
		
		strPathName = QString("echo %1 > /sys/class/gpio/gpio21/value").arg(checked);
		SystemEx(strPathName.toStdString().c_str());
		strPathName = QString("echo %1 > /sys/class/gpio/gpio22/value").arg(checked);
	}*/
	
	SystemEx(strPathName.toStdString().c_str());

    UINT8 unBeepVol = unCtrlLev;
	if(checked > 0)
		unBeepVol = ALM_LEV_N;
	CtrlBeepVolume(unBeepVol);
}

void MainWindow::CtrlBeepVolume(UINT8 unCtrlLev)
{
    QString strPathName1,strPathName2;
/**/
    if(unCtrlLev == ALM_LEV_H)
    {
        strPathName1 = QString("echo %1 > /sys/class/gpio/gpio23/value").arg(1);
		strPathName2 = QString("echo %1 > /sys/class/gpio/gpio24/value").arg(1);
    }
    else if(unCtrlLev == ALM_LEV_M || unCtrlLev == ALM_LEV_L)
    {
        strPathName1 = QString("echo %1 > /sys/class/gpio/gpio23/value").arg(1);
		strPathName2 = QString("echo %1 > /sys/class/gpio/gpio24/value").arg(0);
    }
    else if(unCtrlLev == ALM_LEV_A)
    {
        strPathName1 = QString("echo %1 > /sys/class/gpio/gpio23/value").arg(0);
		strPathName2 = QString("echo %1 > /sys/class/gpio/gpio24/value").arg(1);
    }
    else if(unCtrlLev == ALM_LEV_N)
    {
        strPathName1 = QString("echo %1 > /sys/class/gpio/gpio23/value").arg(0);
		strPathName2 = QString("echo %1 > /sys/class/gpio/gpio24/value").arg(0);
    }	
	SystemEx(strPathName1.toStdString().c_str());
	SystemEx(strPathName2.toStdString().c_str());
}

void MainWindow::BeepRestart(void)
{
    if(m_bCloseBeepFlag == false)
    {
        if(m_unBeepRestSec > 0)
			m_unBeepRestSec--;
		else
		{
		    m_bCloseBeepFlag = true;
			on_almOnOffBtn_clicked(true);
		}
    }
}

void MainWindow::on_almOnOffBtn_clicked(bool checked)
{
    bool bHasAlarm = HasAlarm();

	if(bHasAlarm)
	{
	    m_bCloseBeepFlag = checked;
		m_unBeepRestSec = 1200;//2分钟
	}
    
	if(false == bHasAlarm || checked == 1)
	{
	    ui->almOnOffBtn->setChecked(checked);
	    ui->almOnOffBtn->setEnabled(checked);
	}

	CtrlBeep(m_unAlmLev, !checked);
	if(checked == 0)
	{
		m_bAlmBeepFlg = false;
		g_almItemEx.unUpdFlag = 0;
		m_bHourBeepFlg = false;
		m_unHourTimer = 0;
	}
	//printf("--------------------------checked:%u-------------------\r\n",checked);
}
/**/
void MainWindow::CheckAlmBeep(UINT8 unNewAlmLev)
{
	bool checked = false;
	if(unNewAlmLev > 0)
		checked = true;
    if(unNewAlmLev != m_unAlmLev)
    {
        m_unAlmLev = unNewAlmLev;
        on_almOnOffBtn_clicked(checked);
    /*
		CtrlBeep(m_unAlmLev, checked);
		if(checked == 0)
		{
			m_bAlmBeepFlg = false;
			g_almItemEx.unUpdFlag = 0;
			m_bHourBeepFlg = false;
			m_unHourTimer = 0;
		}*/
	}
}

bool MainWindow::HasAlarm(void)
{
    BYTE* pDataBuf   = (BYTE*)&g_devAlmBits;
    UINT32 unDataLen = sizeof(g_devAlmBits);
    UINT32 unDataPos = sizeof(DateTime);
    while(unDataPos<unDataLen)
    {
        if(pDataBuf[unDataPos])
        {
            return true;
        }
        unDataPos++;
    }
    return false;
}
//检测灌注停止条件(切换预灌注)
void MainWindow::CheckPourStopA(void)
{
   if(STR_POUR != ui->monTabWidget->currentIndex())
   {
       return ;
   }
//压力上下限,流量上下限
   if(g_pourTstData.tstData.unAPrssVal >= g_devConfigInfo.devPourParam.unPourUPresA || \
   	  g_devAlmBits.ApumGrpAlm.bPressErrBits ||\
	  g_pourTstData.tstData.unAFlowVal >= g_devConfigInfo.devPourParam.unPourUFlowA)//g_devAlmBits.ApumGrpAlm.bFlowUBits
   {
       if(m_unPourChangRePourSceA >= 2)
       {
           ui->monTabWidget->setCurrentIndex(PRE_POUR);
		   m_unPourChangRePourSceA = 0;
       }
	   else
	   {
	       m_unPourChangRePourSceA++;
	   }
   }
}

void MainWindow::SetDefPumPrmA(UINT8 unSite, UINT8 unCfgItem, UINT16 unPress, UINT16 unSpeed)
{
	OperLogPumDev operLogPumDev;
	operLogPumDev.unType = OPER_LOG_TYPE_APUM;
	operLogPumDev.unSite = unSite;
	GetDateTime(&operLogPumDev.dtCreate);
	operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.arteryParm.unEnFlag;
	operLogPumDev.unEnFlag[1] = operLogPumDev.unEnFlag[0];
	
	operLogPumDev.unPress[0] = g_devConfigInfo_Edt.arteryParm.unPress;
	if(unCfgItem == CFG_ARTERY_PRS_ITEM)
	{
		operLogPumDev.unPress[1] = unPress;
		g_devConfigInfo_Edt.arteryParm.unPress = unPress;
	}
	else
	{
		operLogPumDev.unPress[1] = g_devConfigInfo_Edt.arteryParm.unPress;
	}
	
	operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.arteryParm.unSpeed;
	if(unCfgItem == CFG_ARTERY_SPD_ITEM)
	{
		operLogPumDev.unSpeed[1] = unSpeed;
		g_devConfigInfo_Edt.arteryParm.unSpeed = unSpeed;
	}
	else
	{
		operLogPumDev.unSpeed[1] = g_devConfigInfo_Edt.arteryParm.unSpeed;
	}
	
	operLogPumDev.unPress[1] = operLogPumDev.unPress[1]/10;
	operLogPumDev.unPress[1] *= 10;

    operLogPumDev.unPressLimt[0] = g_devConfigInfo_Edt.arteryParm.unPressLimt;    //血泵压力设置值上限
    operLogPumDev.unPressLimt[1] = operLogPumDev.unPressLimt[0];
	
    operLogPumDev.unSpeedLimt[0] = g_devConfigInfo_Edt.arteryParm.unSpeedLimt;    //血泵转速设置值上限
    operLogPumDev.unSpeedLimt[1] = operLogPumDev.unSpeedLimt[0];


	//动脉-预灌注
	ui->preSpeedSetLE->setText(QString("%1").arg(g_devConfigInfo_Edt.arteryParm.unSpeed));
    ui->pourPressSetLE->setText(ValueToString(g_devConfigInfo_Edt.arteryParm.unPress/10,1,0));

	SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
	SaveOperLogInfo();			
	
	g_pCfgDataUI->AddGrpData(unCfgItem,\
								sizeof(g_devConfigInfo_Edt.arteryParm),\
								(BYTE*)&g_devConfigInfo_Edt.arteryParm);    
}
void MainWindow::CheckPourPrmA(void)
{
	//动脉泵实时设置
	if(false == m_bBPRunFlgA)
	{
	    return ;
	}
	
	UINT32 unCfgItem = 0;
	if(g_pourTstData.tstData.unASpeeVal > g_devConfigInfo.devPourParam.unPourUSpeeA)
	{
		unCfgItem = CFG_ARTERY_SPD_ITEM;
	}
	/*
	else if(g_pourTstData.tstData.unAPrssVal > g_devConfigInfo.devPourParam.unPourUPresA)
	{
		unCfgItem = CFG_ARTERY_PRS_ITEM;
	}*/
	else
	{
	    return ;
	}
	if(m_unPourChangRePourSceA > 0)
	{
		m_unPourChangRePourSceA--;
		return ;
	}
	
    SetDefPumPrmA(SYS_CTL, unCfgItem, SET_POUR_PRESS, SET_POUR_SPEED);

	m_unPourChangRePourSceA = SET_POUR_VAL_TMT;
}


//检测水浴加温止条件
void MainWindow::CheckWatStop(void)
{
    //if(g_devAlmBits.watGrpAlm[0].bTmpUBits||\
	   //g_devAlmBits.ApumGrpAlm[0].bTmpUBits||g_devAlmBits.VpumGrpAlm[1].bTmpUBits)
	if(g_pourTstData.tstData.unWatTmpVal >= g_devConfigInfo.devPourParam.unPourUWatTmp||\
	   g_pourTstData.tstData.unATmpVal >= g_devConfigInfo.devPourParam.unPourUTmpA||\
	   g_pourTstData.tstData.unVTmpVal >= g_devConfigInfo.devPourParam.unPourUTmpV)
    {
		if(ui->wtrRomOnOffBt->isChecked() == 1)
		{
		    if(m_unWatRunState == DEV_ON && m_unWatRunCheckSec == 0)
		    {
		        UINT8 unSite = 0;
				if(g_pourTstData.tstData.unWatTmpVal >= g_devConfigInfo.devPourParam.unPourUWatTmp)
				{
				    unSite = WAT_TMP;
				}
				else if(g_pourTstData.tstData.unATmpVal >= g_devConfigInfo.devPourParam.unPourUTmpA)
				{
				    unSite = APUM_TMP;
				}
				else if(g_pourTstData.tstData.unVTmpVal >= g_devConfigInfo.devPourParam.unPourUTmpV)
				{
				    unSite = VPUM_TMP;
				}
		    	//on_wtrRomOnOffBt_clicked(DEV_OFF, unSite);
		    	g_pWorkThread->setOpenWatRoom(0, DEV_OFF, unSite);
				m_unWatRunCheckSec = 20;
				unSetWatStateDly = 10*30;
		    }
		}
    }
}


void MainWindow::CheckStartInit(void)
{
    pCheckMsgBox = new QMessageBox(this);
	pCheckBut    = new QPushButton();
	m_unCheckStartDly = 60;
	m_unStartCheckFlag = false;
	pCheckMsgBox->setWindowTitle("提示");
	pCheckMsgBox->setIcon(QMessageBox::Critical);
	pCheckMsgBox->setText(QString("系统自检中<%1>s").arg(m_unCheckStartDly));
	pCheckBut = pCheckMsgBox->addButton("关闭", QMessageBox::RejectRole);//AcceptRole
	pCheckBut->setMinimumSize(100,30);
	pCheckBut->hide();
	SetMessageBoxFont(pCheckMsgBox);
	pCheckMsgBox->exec();
}
void MainWindow::CheckStart(void)
{
	if(m_unCheckStartDly)
	{
		m_unCheckStartDly--;
		pCheckMsgBox->setText(QString("系统自检中<%1>s").arg(m_unCheckStartDly));
	}
	else
	{
	    pCheckMsgBox->setText("系统自检完成!");
	    pCheckBut->show();
	}
}

void MainWindow::SetBeepHour(void)
{
    if(m_bHourBeepFlg == true && m_bAlmBeepFlg == false)
    {
        m_unHourTimer++;
        if(m_unHourTimer == 1)
        {
        	g_pWorkThread->CtrlBeep(1);
        }
		else if(m_unHourTimer == 6)
		{
		    g_pWorkThread->CtrlBeep(0);
			m_unHourTimer = 0;
		}
    }
	else
	{
	    if(m_bHourBeepFlg == true)
	    {
		    m_bHourBeepFlg = false;
			m_unHourTimer = 0;
	    }
	}
}

void MainWindow::FlashMainWindowPrePourBg(bool bLock)
{
    if(m_unPumpRunA == 0)
    {
		if(g_pourTstData.tstData.unADataType == PRE_POUR)
		{
		    if(bLock == true)
		    {
		        ui->prePourWg->setStyleSheet(QLatin1String("#prePourWg{\n"
		        "background-image:url(:/images/monDataPrePourLock_Bg.png);\n"
		        "}"));
		    }
			else
			{
		        ui->prePourWg->setStyleSheet(QLatin1String("#prePourWg{\n"
		        "background-image:url(:/images/monDataPrePour_Bg.png);\n"
		        "}"));		
			}
		}
		else
		{
		    if(bLock == true)
		    {
		        ui->pourWg->setStyleSheet(QLatin1String("#pourWg{\n"
		        "background-image:url(:/images/monDataPourLock_Bg.png);\n"
		        "}"));
		    }
			else
			{
		        ui->pourWg->setStyleSheet(QLatin1String("#pourWg{\n"
		        "background-image:url(:/images/monDataPour_Bg.png);\n"
		        "}"));		
			}
		}
    }

	if(m_unPumpRunV == 0)
	{
		if(g_pourTstData.tstData.unVDataType == PRE_POUR)
		{
		    if(bLock == true)
		    {
		        ui->prePourWgV->setStyleSheet(QLatin1String("#prePourWgV{\n"
		        "background-image: url(:/images/monDataPrePourLock_Bg.png);\n"
		        "}"));
		    }
			else
			{
		        ui->prePourWgV->setStyleSheet(QLatin1String("#prePourWgV{\n"
		        "background-image: url(:/images/monDataPrePour_Bg.png);\n"
		        "}"));
			}
		}
		else
		{
		    if(bLock == true)
		    {
		        ui->pourWgV->setStyleSheet(QLatin1String("#pourWgV{\n"
		        "background-image: url(:/images/monDataPourLock_Bg.png);\n"
		        "}"));
		    }
			else
			{
				ui->pourWgV->setStyleSheet(QLatin1String("#pourWgV{\n"
				"background-image: url(:/images/monDataPour_Bg.png);\n"
				"}"));
			}
		}     
	}
	
    if(bLock == true)
    {
        ui->waterTmpWg->setStyleSheet(QLatin1String("#waterTmpWg{\n"
        "background-image: url(:/images/waterRoomTmpLock_Bg.png);\n"
        "}"));
    }
	else
	{
	    if(m_unWatRunState == 1)
	    	SetWaterWidgetBg(true);
		else
			SetWaterWidgetBg(false);
		//printf("----------------------------------------------SetWaterWidgetBg--5\r\n");
	}
}
void MainWindow::SetWaterWidgetBg(bool bOpen)
{
	//if(m_unWatRunState == 1 || bOpen == true)
	if(bOpen == true)
	{
		ui->waterTmpWg->setStyleSheet(QLatin1String("#waterTmpWg{\n"
		"background-image: url(:/images/waterRoomTmp_Bg.png);\n"
		"}"));
		//printf("-----------------------------------------------bOpen:%u-------1\r\n",bOpen);
	}
	else
	{
		ui->waterTmpWg->setStyleSheet(QLatin1String("#waterTmpWg{\n"
		"background-image: url(:/images/waterRoomTmpOff_Bg.png);\n"
		"}"));
		
		//printf("-----------------------------------------------bOpen:%u-------2\r\n",bOpen);
	}
}
void MainWindow::setLock(void)
{
    //printf("----------------------------------------------setLock----------\r\n");
    FlashMainWindowPrePourBg(false);
}
void MainWindow::on_unLockScreenBtn_clicked()
{
    m_pLockScreenDlg->show();
	FlashMainWindowPrePourBg(true);
}

//---------------------------------------静脉界面操作接口-----------------------------------
//静脉血泵
void MainWindow::on_BPStrBtnV_clicked(bool checked)
{
    printf("on_BPStrBtnV_clicked ------------V %d \r\n",checked);

	if(checked == 1)
	{
		g_devConfigInfo.veinParm.unSpeed = SET_SPEED_DEF;
		g_devConfigInfo_Edt.veinParm.unSpeed = SET_SPEED_DEF;
		
		ui->VmonTabWidget->setEnabled(true);
		//SetDevHeadBg(true, DEV_VPUMP_TYPE);
		g_pWorkThread->StartBloodPump(DEV_VPUMP_TYPE,0);
		m_bBPRunFlgV = true;
		ui->VmonTabWidget->setCurrentIndex(0);//启动血泵默认为预灌注状态
	}
	else if(checked == 0)
	{
		m_unClosePumDev = DEV_VPUMP_TYPE;
		ClosePumWinDialog  closePumWin(this);
		closePumWin.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
		closePumWin.setWindowModality(Qt::ApplicationModal);
		closePumWin.exec();
	}
	unSetPumStateDlyV = 10*30;
}

void MainWindow::CheckPourStopV(void)
{
   if(STR_POUR != ui->VmonTabWidget->currentIndex())
   {
       return ;
   }

//压力上下限,流量上下限
  if(g_devAlmBits.VpumGrpAlm.bPressUBits || g_devAlmBits.VpumGrpAlm.bPressUBits ||\
	 g_devAlmBits.VpumGrpAlm.bFlowUBits || g_devAlmBits.VpumGrpAlm.bFlowLBits)
   {
       if(m_unPourChangRePourSceV >= 2)
       {
           ui->VmonTabWidget->setCurrentIndex(PRE_POUR);
		   m_unPourChangRePourSceV = 0;
       }
	   else
	   {
	       m_unPourChangRePourSceV++;
	   }
   }
}
void MainWindow::SetDefPumPrmV(UINT8 unSite, UINT8 unCfgItem, UINT16 unPress, UINT16 unSpeed)
{
	OperLogPumDev operLogPumDev;
	operLogPumDev.unType = OPER_LOG_TYPE_VPUM;
	operLogPumDev.unSite = unSite;
	GetDateTime(&operLogPumDev.dtCreate);
	operLogPumDev.unEnFlag[0] = g_devConfigInfo_Edt.veinParm.unEnFlag;
	operLogPumDev.unEnFlag[1] = operLogPumDev.unEnFlag[0];
	operLogPumDev.unPress[0] = g_devConfigInfo_Edt.veinParm.unPress;
	if(unCfgItem == CFG_VEIN_PRS_ITEM)
	{
		operLogPumDev.unPress[1] = unPress;
		g_devConfigInfo_Edt.veinParm.unPress = unPress;
	}
	else
	{
		operLogPumDev.unPress[1] = g_devConfigInfo_Edt.veinParm.unPress;
	}
	
	operLogPumDev.unSpeed[0] = g_devConfigInfo_Edt.veinParm.unSpeed;
	if(unCfgItem == CFG_VEIN_SPD_ITEM)
	{
		operLogPumDev.unSpeed[1] = unSpeed;
		g_devConfigInfo_Edt.veinParm.unSpeed = unSpeed;
	}
	else
	{
		operLogPumDev.unSpeed[1] = g_devConfigInfo_Edt.veinParm.unSpeed;
	}
	
	operLogPumDev.unPress[1] = operLogPumDev.unPress[1]/10;
	operLogPumDev.unPress[1] *= 10;

    operLogPumDev.unPressLimt[0] = g_devConfigInfo_Edt.veinParm.unPressLimt;    //血泵压力设置值上限
    operLogPumDev.unPressLimt[1] = operLogPumDev.unPressLimt[0];
	
    operLogPumDev.unSpeedLimt[0] = g_devConfigInfo_Edt.veinParm.unSpeedLimt;    //血泵转速设置值上限
    operLogPumDev.unSpeedLimt[1] = operLogPumDev.unSpeedLimt[0];	
	
	//静脉-灌注
	ui->preSpeedSetLEV->setText(QString("%1").arg(g_devConfigInfo_Edt.veinParm.unSpeed));
    ui->pourPressSetLEV->setText(ValueToString(g_devConfigInfo_Edt.veinParm.unPress,10,1));


	SaveOperLogData((const char*)&operLogPumDev, sizeof(OperLogPumDev));
	SaveOperLogInfo();			
	
	g_pCfgDataUI->AddGrpData(unCfgItem,\
								sizeof(g_devConfigInfo_Edt.veinParm),\
								(BYTE*)&g_devConfigInfo_Edt.veinParm);

}

void MainWindow::CheckPourPrmV(void)
{
	//动脉泵实时设置
	if(false == m_bBPRunFlgV)
	{
	    return ;
	}
	
	UINT32 unCfgItem = 0;
	if(g_pourTstData.tstData.unVSpeeVal > g_devConfigInfo.devPourParam.unPourUSpeeV)
	{
		unCfgItem = CFG_VEIN_SPD_ITEM;
	}
	/*
	else if(g_pourTstData.tstData.unVPrssVal > g_devConfigInfo.devPourParam.unPourUPresV)
	{
		unCfgItem = CFG_VEIN_PRS_ITEM;
	}*/
	else
	{
	    return ;
	}
	if(m_unPourChangRePourSceV > 0)
	{
		m_unPourChangRePourSceV--;
		return ;
	}
	SetDefPumPrmV(SYS_CTL, unCfgItem, SET_POUR_PRESS_V, SET_POUR_SPEED_V);

	m_unPourChangRePourSceV = SET_POUR_VAL_TMT;
}

void MainWindow::OnMonTabChangedV(void)
{
    printf("--------------------Entr OnMonTabChangedV-------V Tab:%d \r\n",ui->VmonTabWidget->currentIndex());
	g_pourTstData.tstData.unVDataType = ui->VmonTabWidget->currentIndex();
	g_pWorkThread->SetDataType(DEV_VPUMP_TYPE, g_pourTstData.tstData.unVDataType);
	m_bMonTabChgFlagV = true;
	if(m_bPourStrFlgV == false)
	{
	    if(g_pourTstData.tstData.unVDataType == STR_POUR)
	    {
	        m_bPourStrFlgV = true;
	    }
	}
}

//动脉预灌注调节转速
void MainWindow::PourPressLEClickV(void)
{
    //qDebug()<<"PourPressLEClick";
	
	if(m_pCurLineEdit == NULL)
	{
	    m_pCurLineEdit = ui->pourPressSetLEV;//ui->pourPressSetLEV;//m_pPourPressLE;
		
	    SetValDialog  setValDialog(this);
		setValDialog.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
	    setValDialog.SetDefaultVal(ui->pourPressLbV->text(),VEI_PRE_SET_TITLE);
		setValDialog.SetValLimit(SET_PRESS_LIMIT_MIN_V,g_devConfigInfo.veinParm.unPressLimt,SET_STEP_1,10,1,1);
	    setValDialog.setWindowModality(Qt::ApplicationModal);
	    setValDialog.exec();
	}
	else
	{
	     qDebug()<<"m_pCurLineEdit != NULL";
	}
}

//静脉预灌注调节转速
void MainWindow::PreSpeedLEClickV(void)
{
    //qDebug()<<"PreSpeedLEClick";
    if(m_pCurLineEdit == NULL)
    {
		m_pCurLineEdit = ui->preSpeedSetLEV;

	    SetValDialog  setValDialog(this);
		setValDialog.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
	    setValDialog.SetDefaultVal(ui->preSpeedSetLEV->text(),VEI_SPE_SET_TITLE);
		setValDialog.SetValLimit(SET_SPEED_LIMIT_MIN_V,g_devConfigInfo.veinParm.unSpeedLimt,SET_STEP_1,1,0,10);
	    setValDialog.setWindowModality(Qt::ApplicationModal);
	    setValDialog.exec();
    }
	else
	{
	     qDebug()<<"m_pCurLineEdit != NULL";
	}
}


void MainWindow::CalCheckClicked(void)
{
//3秒后点击重新设置参数不满足，重新设置为0 
	if(m_unClickNum)
	{
		m_unEntrCalFlag++;
		if(m_unEntrCalFlag > 30)
		{
			m_unClickNum = 0;
			m_unEntrCalFlag = 0;
		}
	}
	else
	{
		if(m_unEntrCalFlag)
		{
			m_unEntrCalFlag = 0;
		}
	}
}

void MainWindow::FlashBattryInfo(void)
{
    if(g_devConfigInfo.batParam.unEnFlag == false)
    {
		return ;
    }
	BqBatBascInfo batDevData;
	memset(&batDevData,0,sizeof(batDevData));
	g_pWorkThread->GetDevData(DEV_BAT_TYPE, 0, (BYTE*)&batDevData,sizeof(BqBatBascInfo));

    bool bDisChg = false;
	UINT8 unBatStat = 0;

	if(batDevData.unBatCur > 100)
	{
		unBatStat = 1;
	}
	else if(batDevData.unBatCur < -500)
	{
		unBatStat = 2;
		bDisChg = true;
	}
    else if(batDevData.unBatCur == 0)
    {
		unBatStat = 0;
    }
    m_pBatDevData.unBatCur = batDevData.unBatCur;
	m_pBatDevData.unBatSoc = batDevData.unBatSoc;
	m_pBatDevData.unBatTmp = batDevData.unBatTmp;
	m_pBatDevData.unBatVol = batDevData.unBatVol;
	m_pBatDevData.unCycNum = batDevData.unCycNum;
	ShowChgIcon(unBatStat);
	ShowBatteryLinkLog(g_pWorkThread->GetBatLinkState());
	ShowACLinkLog(bDisChg);

    ui->batWidget->setValue(batDevData.unBatSoc, bDisChg);
	ui->batSocLabel->setText(QString("%1").arg(batDevData.unBatSoc)+"%");
	
	//ui->showTmpLabel->setText(ValueToString(watDevData.unTmpVal,10,1));//温度
	if(unBatStat != m_unBatStat)
	{
	    m_unBatStat = unBatStat;
		g_pWorkThread->SetBatState(m_unBatStat);
	}
}

void MainWindow::ShowBatteryLinkLog(bool bLinkFlg)
{
    QImage* img = new QImage;
    if(bLinkFlg == true)
    {
    	img->load(QString(":/images/batteryLink_Icon.png"));
	}
	else
	{
		img->load(QString(":/images/batteryUnlink_Icon.png"));
	}
    QImage scaledimg;
    scaledimg = img->scaled(ui->batLinkLog->width(),ui->batLinkLog->height(),Qt::KeepAspectRatio);
    ui->batLinkLog->setPixmap(QPixmap::fromImage(scaledimg));
}
void MainWindow::ShowACLinkLog(bool bLinkFlg)
{
    QImage* img = new QImage;
    if(bLinkFlg == true)
    {
    	img->load(QString(":/images/acUnlink_Icon.png"));
	}
	else
	{
		img->load(QString(":/images/acLink_Icon.png"));
	}
    QImage scaledimg;
    scaledimg = img->scaled(ui->acLinkLog->width(),ui->acLinkLog->height(),Qt::KeepAspectRatio);
    ui->acLinkLog->setPixmap(QPixmap::fromImage(scaledimg));
}


void MainWindow::ShowChgIcon(UINT8 unBatStat)
{
    if(unBatStat == 1)
    {
        ui->chgIconLb->show();
    }
	else
	{
	    ui->chgIconLb->hide();
	}
}

void MainWindow::ClosePumCleanAlm(UINT8 unDevType)
{
    if(unDevType == DEV_APUMP_TYPE)
    {
        g_devAlmBits.ApumGrpAlm.bPressLBits = 0;
		g_devAlmBits.ApumGrpAlm.bPressUBits = 0;
		g_devAlmBits.ApumGrpAlm.bFlowUBits = 0;
		g_devAlmBits.ApumGrpAlm.bFlowLBits = 0;
    }
    else if(unDevType == DEV_VPUMP_TYPE)
    {
        g_devAlmBits.VpumGrpAlm.bPressLBits = 0;
		g_devAlmBits.VpumGrpAlm.bPressUBits = 0;
		g_devAlmBits.VpumGrpAlm.bFlowUBits = 0;
		g_devAlmBits.VpumGrpAlm.bFlowLBits = 0;
    }
}
