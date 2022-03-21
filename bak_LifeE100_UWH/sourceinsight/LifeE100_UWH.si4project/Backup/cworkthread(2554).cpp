#include "includes.h"
#include "cworkthread.h"
#include "cdevcmdhandler.h"
#include "cuartsocket.h"
#include "cmonsharedata.h"
//#include <QHostAddress>
#include "fcntl.h"
#include "unistd.h"
#include <QtGui>
#include "errorstringqueue.h"
#include "csocket.h"
#include "csockethandler.h"
#include "calarmDataFile.h"
#include "csharedataqueue.h"
#include "CSwitPump.h"
#include "CSwitWater.h"
//#include "cpourdevices.h"
#include "cuartsocketBQ40z50.h"
#include "CBQ40z50Battery.h"




//#include "RTC.h"
#include <stdlib.h>
#include "QDebug"




#define  NWK_CHK_SEC_PRD        60      //一分钟
#define  MAX_CMM_TIMEOUT_VAL    (1000L) //1毫秒

CWorkThread::CWorkThread(QObject *parent) :
    QThread(parent)
{
    m_bRunEnd = false;
    m_pErrStrQueue  = NULL;
    m_pSktHandler   = NULL;
    m_pDevCmdHander = NULL;
    m_pUARTSkt0     = NULL;
    m_pUARTSkt1     = NULL;
	m_pUARTSkt2     = NULL;
	m_pUARTSkt3 	= NULL;

    m_bQuitFlag     = false;
    m_bInitFlag     = false;
    m_bBpRunFlag[0]   = false;
	m_bBpRunFlag[1]   = false;
    m_unMsTimer     = 0;
    m_unAlmDlySec = 10;//600;
	m_unDataType[0] = PRE_POUR;
	m_unDataType[1] = PRE_POUR;
	m_unArteryPrmIndex = CFG_ARTERY_SPD_ITEM;//默认转速
	m_unAlmFlowDlySec[0] = 5;
	m_unAlmFlowDlySec[1] = 5;
	m_fdMonInfoFle = -1;
	m_fdMonData = -1;
	m_unMonDlySec = 60;
	m_bOpenMonFile = false;
	m_unWaterPrmIndex = 0x01;

	m_bMcuUpEn = false;
	m_unMcuType = 0;
	m_unMcuUpState = 0xFF;

	m_unVeinPrmIndex = CFG_VEIN_SPD_ITEM;
	memset(&m_pMcuUpInfo,0,sizeof(McuUpdateInfo));
}

CWorkThread::~CWorkThread()
{
    if(NULL!=m_pSktHandler)
    {
        delete m_pSktHandler;
    }
    m_pSktHandler = NULL;
    if(NULL != m_pDevCmdHander)
    {
        delete m_pDevCmdHander;
    }
    m_pDevCmdHander = NULL;

    if(NULL!=m_pErrStrQueue)
    {
        delete m_pErrStrQueue;
    }
    m_pErrStrQueue = NULL;

    if(NULL != m_pUARTSkt0)
    {
        delete m_pUARTSkt0;
    }
    m_pUARTSkt0 = NULL;

    if(NULL != m_pUARTSkt1)
    {
        delete m_pUARTSkt1;
    }
    m_pUARTSkt1 = NULL;

    if(NULL != m_pUARTSkt2)
    {
        delete m_pUARTSkt2;
    }
    m_pUARTSkt2 = NULL;
    if(NULL != m_pUARTSkt3)
    {
        delete m_pUARTSkt3;
    }
    m_pUARTSkt3 = NULL;

}

void CWorkThread::run()
{
    UINT32 unMsTimer;
    int    nIndex;
//	UINT32 unCont = 0;
    m_bQuitFlag = false;
    m_bRunEnd   = true;

    if(false==m_bInitFlag)
    {
        m_bInitFlag = true;
        InitThread();
    }
    ProcInitConfig();
	OpenMonDataInfo();
	if(g_MonSaveInfo.unMonDataNum)
	{
	    m_bOpenMonFile = true;
	    OpenMonDataFile();
	}

    while(false == m_bQuitFlag)
    {
        //处理通信数据
        if(m_pSktHandler->GetCount())
        {
            m_pSktHandler->Select(0,MAX_CMM_TIMEOUT_VAL);
        }
        unMsTimer = GetMsTimer(&m_timeb);
		/*
        if(true==g_bRestartFlag)
        {
            if(0==g_unRestartDlyMs)
            {
                if(true==m_bRebootFlag)
                {
                    SystemEx("reboot -f");
                }
                else
                {
                    RestartSystem();
                }
                while(false == m_bQuitFlag);
            }
            continue;
        }*/

        if(unMsTimer)
        {
            if(true==GetUpdConfigInfo())
            {
                //处理用户配置参数
                ProcInitConfig();
            }

            //处理灌注启停命令
            ProcUsrSrtCmd();

			//处理监控数据保存
			ProcMonInfo();
            m_pDevCmdHander->OnProcTask();
            m_pDevCmdHander->OnMsTimer(unMsTimer);
            m_procPour.ProcTask();
            m_procPour.OnMsTimer(unMsTimer);
			//处理告警日志
            ProcAlmInfo();
            OnMsTimer(unMsTimer);

            for (nIndex = 0; nIndex < m_listCmmSkts.size(); ++nIndex)
            {
                m_listCmmSkts.at(nIndex)->OnMsTimer(unMsTimer);
            }

			ProMcuUpTask();
        }
		g_bWorkThRunRunFlg = true;
    }
    m_bRunEnd = false;
    while(1)
    {
        if(NULL != m_pUARTSkt0)
        {
            m_pUARTSkt0->Close();
        }
        if(NULL!=m_pUARTSkt1)
        {
            m_pUARTSkt1->Close();
        }
        if(NULL!=m_pUARTSkt2)
        {
            m_pUARTSkt2->Close();
        }
        if(NULL!=m_pUARTSkt3)
        {
            m_pUARTSkt3->Close();
        }		
    }
}

void CWorkThread::AddCmmObject(CSocket* pCmmSkt)
{
    m_listCmmSkts.append(pCmmSkt);
    pCmmSkt->SetWorkThread(this);
}

void CWorkThread::SetAllDevTimeOutEn(void)
{
    m_pDevCmdHander->SetTimeOutEn();
}

void CWorkThread::StopRun(void)
{
    m_lckMutex.lock();
    m_bQuitFlag = true;
    m_lckMutex.unlock();
}


void CWorkThread::ProcUsrSrtCmd(void)
{
    UINT32 unUserCmdID = GetUsrBPCmd();
    if(m_unBpGrpID >= MAX_BP_GRP_COUNT || unUserCmdID == USR_BP_CMD_NONE)
    {
        return;
    }
	
	CSwitPump* pPumMod;
	UINT8 unPumType = 0;
	UINT8 unIndex;
	UINT16 unPrmVald;
	if(m_unDevPumType == DEV_APUMP_TYPE)
	{
    	pPumMod = m_listAPumMods.at(m_unBpGrpID);
		unPumType = 0;
		unIndex = CFG_ARTERY_SPD_ITEM;
		unPrmVald = g_devConfigInfo.arteryParm.unSpeed;
	}
	else if(m_unDevPumType == DEV_VPUMP_TYPE)
	{
    	pPumMod = m_listVPumMods.at(m_unBpGrpID);
		unPumType = 1;
		unIndex = 0x01;
		unPrmVald = g_devConfigInfo.veinParm.unSpeed;
	}
	
    OperLogCtl operLogCtl;
    if(unPumType == 0)
    {
		operLogCtl.unType = OPER_CTRL_TYPE_APUM;
    }
    else if(unPumType == 1)
    {
		operLogCtl.unType = OPER_CTRL_TYPE_VPUM;
    }
	operLogCtl.unSite = 0;
	GetDateTime(&operLogCtl.dtCreate);
	operLogCtl.unResult[0] = 0;
	operLogCtl.unResult[1] = 1;	

	SetDevPrm setDevPrm;
	setDevPrm.unIndex = unIndex;
	setDevPrm.unPrmVald = unPrmVald;
	//pPumMod->SetDevParam(&setDevPrm);

    if(USR_BP_CMD_STRT == unUserCmdID)
    {
        operLogCtl.unOperType[0] = 0;
		operLogCtl.unOperType[1] = 1;
			
		//SetDevPrm setDevPrm;
		//setDevPrm.unIndex = unIndex;
		//setDevPrm.unPrmVald = unPrmVald;
		pPumMod->SetDevParam(&setDevPrm);
		
        bool bValidFlag = true;
		QString strError = QString("启动血泵失败!--");
    /**/
		if(false==pPumMod->IsActive())
        {
            strError  += QString("血泵控制模块超时");
            bValidFlag =  false;
			operLogCtl.unResult[1] = 2;
        }
		
        if(true==bValidFlag)
        {
            //启动血泵
            if(false==m_procPour.StartRun(m_unDevPumType, m_unBpGrpID))
            {
                strError  = strError+QString(m_procPour.GetErrorInfo())+QString("\r\n");
                ShowStringInfo(strError.toStdString().c_str(),DLG_SHOW,ICON_ERROR);
				operLogCtl.unResult[1] = 2;
            }
        }
        else
        {
            ShowStringInfo(strError.toStdString().c_str(),DLG_SHOW,ICON_ERROR);
        }
    }
    else if(USR_BP_CMD_STOP==unUserCmdID)
    {
		operLogCtl.unOperType[0] = 1;
		operLogCtl.unOperType[1] = 0;
		operLogCtl.unResult[0] = 1;
		operLogCtl.unResult[1] = 1;

        //停止血泵
		//pPumMod->CtrlDevRun(DEV_OFF);
        m_procPour.StopPump(m_unDevPumType, STP_ERR_USR_CNL_ERR);
		pPumMod->SetDevParam(&setDevPrm);
    }
	SaveOperLogData((const char*)&operLogCtl, sizeof(OperLogCtl));
	SaveOperLogInfo();
	
    SetUsrBPCmd(USR_BP_CMD_NONE);
    m_lckMutex.lock();
    m_bBpRunFlag[unPumType] = m_procPour.IsRun(unPumType);
    m_lckMutex.unlock();
    /**/
}

void CWorkThread::SetArteryParam(void)
{
//	UINT32 unIndex;
	SetDevPrm setDevPrm;
	//m_unArteryPrmIndex
	g_devUpdFlags.bArteryFlag = false;
		
	if(m_unDataType[0] == PRE_POUR)
	{
		m_unArteryPrmIndex = CFG_ARTERY_SPD_ITEM;
	}
	else
	{
		m_unArteryPrmIndex = CFG_ARTERY_PRS_ITEM;
	}
	
	if(m_unArteryPrmIndex==CFG_ARTERY_PRS_ITEM)
	{
		setDevPrm.unPrmVald = g_devConfigInfo.arteryParm.unPress;
	}
	else if(m_unArteryPrmIndex==CFG_ARTERY_SPD_ITEM)
	{
		setDevPrm.unPrmVald = g_devConfigInfo.arteryParm.unSpeed;
	}
	else if(m_unArteryPrmIndex==CFG_ARTERY_FLW_ITEM)
	{
		setDevPrm.unPrmVald = g_devConfigInfo.arteryParm.unFlow;
	}
	setDevPrm.unIndex = m_unArteryPrmIndex;
	
	CSwitPump* pSwitPum;
	pSwitPum = m_listAPumMods.at(0);

    QString strClsName;
	pSwitPum->GetClassName(strClsName);
	printf("A---unEnFlag:%d----------PrmIndex:%u PrmVald:%u\r\n",g_devConfigInfo.arteryParm.unEnFlag,setDevPrm.unIndex,setDevPrm.unPrmVald);
	pSwitPum->SetEnable(g_devConfigInfo.arteryParm.unEnFlag);
	pSwitPum->SetDevParam(&setDevPrm);
	if(true==pSwitPum->IsEnabled())
	{
		m_procPour.AddAPumMod(pSwitPum);
		printf("-------------------------------AddAPumMod-----------\r\n");
	}
	else
	{
		m_procPour.RmvAPumMod(pSwitPum);
		CleanDevAlm(DEV_APUMP_TYPE);
	}
}

void CWorkThread::SetVeinParam(void)
{
	SetDevPrm setDevPrm;
	g_devUpdFlags.bVeinFlag = false;
	
	if(m_unDataType[1] == PRE_POUR)
	{
		m_unVeinPrmIndex = CFG_VEIN_SPD_ITEM;
	}
	else
	{
		m_unVeinPrmIndex = CFG_VEIN_PRS_ITEM;
	}
	
	if(m_unVeinPrmIndex==CFG_VEIN_PRS_ITEM)
	{
		setDevPrm.unPrmVald = g_devConfigInfo.veinParm.unPress;
	}
	else if(m_unVeinPrmIndex==CFG_VEIN_SPD_ITEM)
	{
		setDevPrm.unPrmVald = g_devConfigInfo.veinParm.unSpeed;
	}
	else if(m_unVeinPrmIndex==CFG_VEIN_FLW_ITEM)
	{
		setDevPrm.unPrmVald = g_devConfigInfo.veinParm.unFlow;
	}
	setDevPrm.unIndex = m_unVeinPrmIndex - CFG_VEIN_SPD_ITEM + 1;
	
	CSwitPump* pSwitPum;
	pSwitPum = m_listVPumMods.at(0);

    QString strClsName;
	pSwitPum->GetClassName(strClsName);
	//printf("V--PrmIndex:%u PrmVald:%u\r\n",setDevPrm.unIndex,setDevPrm.unPrmVald);
	pSwitPum->SetEnable(g_devConfigInfo.veinParm.unEnFlag);
	pSwitPum->SetDevParam(&setDevPrm);
	if(true==pSwitPum->IsEnabled())
	{
		m_procPour.AddVPumMod(pSwitPum);
	}
	else
	{
		m_procPour.RmvVPumMod(pSwitPum);
		CleanDevAlm(DEV_VPUMP_TYPE);
	}
}

void CWorkThread::ProcInitConfig(void)
{
    //long lIndex;
    //处理基本配置
    if(true == g_devUpdFlags.bBasicFlag)
    {
        g_devUpdFlags.bBasicFlag = false;
		m_procPour.SetSavePrd(g_devConfigInfo.basicCfgInfo.unMonSavTmt);
    }
    //处理动脉血泵参数更新
    if(true == g_devUpdFlags.bArteryFlag)
    {
		SetArteryParam();
		g_devUpdFlags.bArteryFlag = false;
    }
    if(true == g_devUpdFlags.bVeinFlag)//处理静脉血泵参数更新
    {
		SetVeinParam();
		g_devUpdFlags.bVeinFlag = false;
    }
    if(true == g_devUpdFlags.bWtrRoomFlag)//水浴参数更新
    {
        g_devUpdFlags.bWtrRoomFlag = false;
		/**/
        SetDevPrm setDevPrm;
        CSwitWater* pWatMod;
        
        //考虑多个设备ID
		setDevPrm.unPrmVald = g_devConfigInfo.watRooParam.unTmpVal;
		setDevPrm.unIndex = m_unWaterPrmIndex;

        pWatMod = m_listWatMods.at(0);
        pWatMod->SetEnable(g_devConfigInfo.watRooParam.unEnFlag);
        pWatMod->SetDevParam(&setDevPrm);
		
		
		if(true==pWatMod->IsEnabled())
		{
			m_procPour.AddWaterMod(pWatMod);
		}
		else
		{
			m_procPour.RmvWaterMod(pWatMod);
			CleanDevAlm(DEV_WAT_TYPE);
		}

    }
	if(true == g_devUpdFlags.bBatSetFlag)//电池参数更新
    {
        g_devUpdFlags.bBatSetFlag = false;
        CBq40z50Bat* pBatMod;
        pBatMod = m_listCelMods.at(0);
        pBatMod->SetEnable(g_devConfigInfo.batParam.unEnFlag);
		if(true==pBatMod->IsEnabled())
		{
			m_procPour.AddBq40Z50Mod(pBatMod);
		}
		else
		{
			m_procPour.AddBq40Z50Mod(pBatMod);
		}
    }
    //告警配置更新
    if(true == g_devUpdFlags.bAlmSetFlag)
    {
        g_devUpdFlags.bAlmSetFlag = false;
    }
    //灌注配置更新
    if(true == g_devUpdFlags.bPourSetFlag)
    {
        g_devUpdFlags.bPourSetFlag = false;
    }

	if(true == g_devUpdFlags.bPulSetFlag)
	{
	    g_devUpdFlags.bPulSetFlag = false;
		printf("-----------------------------%u------------------\r\n",m_unDataType[0]);
		if(m_unDataType[0] == STR_POUR)
		{
	    	SetPulesPrm(DEV_APUMP_TYPE, 0);
		}
	}
}

void CWorkThread::InitThread(void)
{
    ftime(&m_timeb);
    SetUsrBPCmd(USR_BP_CMD_NONE);
    //创建相关对象
    m_pErrStrQueue  = new CErrorStringQueue;
    m_pSktHandler   = new CSocketHandler();
    m_pDevCmdHander = new CDevCmdHandler();

    CUARTSocket *pUartSkt = new CUARTSocket(m_pSktHandler);
	//串口对应板子---p5
	/*
	#if RUN_ARM_LINUX
    if(false==pUartSkt->OpenDev("/dev/ttyAMA1",115200))
	#else
	if(false==pUartSkt->OpenDev("/dev/tty1",115200))
	#endif
    {
        printf("Open CommPort:%s FAIL!\r\n","/dev/ttyAMA1");
        delete pUartSkt;
    }
    else
    {
        AddCmmObject(pUartSkt);
        pUartSkt->SetDevCmdHander(m_pDevCmdHander);
        m_pSktHandler->AddSocket(pUartSkt);
        m_pUARTSkt0 = pUartSkt;
        m_pUARTSkt0->SetMaxCmdTimer(1000);
		printf("m_pUARTSkt0 Open OK--------------!\r\n");
    }*/
	//串口对应板子---p1
    pUartSkt = new CUARTSocket(m_pSktHandler);
#if RUN_ARM_LINUX
    if(false==pUartSkt->OpenDev("/dev/ttyAMA2",115200))
#else
	if(false==pUartSkt->OpenDev("/dev/tty1",115200))
#endif
    {
        printf("Open CommPort:%s FAIL!\r\n","/dev/ttyAMA2");
        delete pUartSkt;
    }
    else
    {
        AddCmmObject(pUartSkt);
        pUartSkt->SetDevCmdHander(m_pDevCmdHander);
        m_pSktHandler->AddSocket(pUartSkt);
        m_pUARTSkt1 = pUartSkt;
		m_pUARTSkt1->SetMaxCmdTimer(1000);
		printf("m_pUARTSkt1 Open OK--------------!\r\n");
    }

	//对应板子---p2
	pUartSkt = new CUARTSocket(m_pSktHandler);
#if RUN_ARM_LINUX
    if(false==pUartSkt->OpenDev("/dev/ttyAMA3",115200))
#else
	if(false==pUartSkt->OpenDev((char*)"/dev/tty1",115200))
#endif
    {
        printf("Open CommPort:%s FAIL!\r\n","/dev/ttyAMA3");
        delete pUartSkt;
    }
    else
    {
        AddCmmObject(pUartSkt);
        pUartSkt->SetDevCmdHander(m_pDevCmdHander);
        m_pSktHandler->AddSocket(pUartSkt);
        m_pUARTSkt2 = pUartSkt;
        m_pUARTSkt2->SetMaxCmdTimer(1000);
		printf("m_pUARTSkt2 Open OK--------------!\r\n");
    }

	//对应板子---p4
	//pUartSkt = new CUARTSocket(m_pSktHandler);
	pUartSkt = new CUARTSocketBQ40Z50(m_pSktHandler);
#if RUN_ARM_LINUX
	if(false==pUartSkt->OpenDev("/dev/ttyAMA5",9600))
#else
	if(false==pUartSkt->OpenDev((char*)"/dev/tty1",9600))
#endif
	{
		printf("Open CommPort:%s FAIL!\r\n","/dev/ttyAMA5");
		delete pUartSkt;
	}
	else
	{
		AddCmmObject(pUartSkt);
		pUartSkt->SetDevCmdHander(m_pDevCmdHander);
		m_pSktHandler->AddSocket(pUartSkt);
		m_pUARTSkt3 = pUartSkt;
		m_pUARTSkt3->SetMaxCmdTimer(2000);
		printf("m_pUARTSkt3 Open OK--------------!\r\n");
	}
	
	pUartSkt = new CUARTSocket(m_pSktHandler);
	#if RUN_ARM_LINUX
    if(false==pUartSkt->OpenDev("/dev/ttyAMA1",115200))
	#else
	if(false==pUartSkt->OpenDev("/dev/tty1",115200))
	#endif
    {
        printf("Open CommPort:%s FAIL!\r\n","/dev/ttyAMA1");
        delete pUartSkt;
    }
    else
    {
        AddCmmObject(pUartSkt);
        pUartSkt->SetDevCmdHander(m_pDevCmdHander);
        m_pSktHandler->AddSocket(pUartSkt);
        m_pUARTSkt4 = pUartSkt;
        m_pUARTSkt4->SetMaxCmdTimer(1000);
		printf("m_pUARTSkt0 Open OK--------------!\r\n");
    }		

	CreateArteryMods();//动脉对应设备
	CreateWaterMods(); //水箱对应设备
	CreateVeinMods();  //静脉对应设备
	CreateBQ40Bat();//电池管理板
	m_procPour.SetWorkThread(this);
}

void CWorkThread::CreateArteryMods(void)
{

    CSwitPump* pSwitPum;

    pSwitPum = new CSwitPump();//
    pSwitPum->SetDevID(g_devConfigInfo.arteryParm.unDevID);
	pSwitPum->SetSndID(MAIN_DEV_BAS_ID);
    pSwitPum->SetUARTSocket(m_pUARTSkt4);
    pSwitPum->SetWorkThread(this);
    pSwitPum->SetEnable(false);
    m_pDevCmdHander->AddSubDevice(pSwitPum);
    m_listAPumMods.append(pSwitPum);
}

void CWorkThread::CreateVeinMods(void)
{
    CSwitPump* pSwitPum;
	
    pSwitPum = new CSwitPump();//
    pSwitPum->SetDevID(g_devConfigInfo.veinParm.unDevID);
	pSwitPum->SetSndID(MAIN_DEV_BAS_ID);
    pSwitPum->SetUARTSocket(m_pUARTSkt2);
    pSwitPum->SetWorkThread(this);
    pSwitPum->SetEnable(false);
    m_pDevCmdHander->AddSubDevice(pSwitPum);
    m_listVPumMods.append(pSwitPum);
}

void CWorkThread::CreateWaterMods(void)
{
    CSwitWater* pSwitWat;

    pSwitWat = new CSwitWater();//
    pSwitWat->SetDevID(g_devConfigInfo.watRooParam.unDevID);
	pSwitWat->SetSndID(MAIN_DEV_BAS_ID);
    pSwitWat->SetUARTSocket(m_pUARTSkt1);
    pSwitWat->SetWorkThread(this);
    pSwitWat->SetEnable(false);
    m_pDevCmdHander->AddSubDevice(pSwitWat);
    m_listWatMods.append(pSwitWat);
}


void CWorkThread::CreateBQ40Bat(void)
{
    UINT8 lIndex;
    CBq40z50Bat* pBqCell;

    pBqCell = new CBq40z50Bat();//
    pBqCell->SetDevID(BAT_DEV_BAS_ID);
	pBqCell->SetSndID(MAIN_DEV_BAS_ID);
    pBqCell->SetUARTSocket(m_pUARTSkt3);
    pBqCell->SetWorkThread(this);
    pBqCell->SetEnable(true);
    m_pDevCmdHander->AddSubDevice(pBqCell);
    m_listCelMods.append(pBqCell);
	m_procPour.AddBq40Z50Mod(pBqCell);
}


void CWorkThread::SetDataType(UINT8     unPumType, UINT8 unDataType)
{
    OperLogCtl operLogCtl;
	UINT8 unIndex = 0;

    if(unPumType == DEV_APUMP_TYPE)
    {
		operLogCtl.unType = OPER_CTRL_TYPE_APOUR;
		unIndex = 0;
    }
    if(unPumType == DEV_VPUMP_TYPE)
    {
		operLogCtl.unType = OPER_CTRL_TYPE_VPOUR;
		unIndex = 1;
    }
	operLogCtl.unSite = 0;
	GetDateTime(&operLogCtl.dtCreate);
	operLogCtl.unResult[0] = 1;
	operLogCtl.unResult[1] = 1;
	
	operLogCtl.unOperType[0] = m_unDataType[unIndex];
	operLogCtl.unOperType[1] = unDataType;
	SaveOperLogData((const char*)&operLogCtl, sizeof(OperLogCtl));
	SaveOperLogInfo();	

    m_unDataType[unIndex] = unDataType;
	SetPourState(unPumType, 0);
	//SetPulesPrm(unPumType, 0);
}

bool CWorkThread::IsRunEnd(void)
{
    return m_bRunEnd;
}

void CWorkThread::ShowStringInfo(const char* strInfo,unsigned char unShowMode ,unsigned char unErrIcon)
{
    m_pErrStrQueue->AddErrInfo(strInfo,unShowMode,unErrIcon);
    emit ShowInfo();
}

/**/
void CWorkThread::StartBloodPump(UINT8 unPumDevType, UINT8 unBpGrpID)
{
    //用户手动启动或网络启动或定时启动血泵
    if(unBpGrpID>=MAX_BP_GRP_COUNT)
    {
        return;
    }
	m_unDevPumType = unPumDevType;
    m_unBpGrpID = unBpGrpID;
    SetUsrBPCmd(USR_BP_CMD_STRT);
}


void CWorkThread::StopBloodPump(UINT8 unPumDevType, UINT8 unBpGrpID)
{
    //用户手动停止或网络停止或定时停止血泵
    if(unBpGrpID>=MAX_BP_GRP_COUNT)
    {
        return;
    }
	m_unDevPumType = unPumDevType;
    m_unBpGrpID = unBpGrpID;

    SetUsrBPCmd(USR_BP_CMD_STOP);
}


void CWorkThread::SetUsrBPCmd(unsigned int unUsrBpCmd)//long
{
    m_lckMutex.lock();
    m_unUsrBpCmd = unUsrBpCmd;
    m_lckMutex.unlock();
}

UINT32 CWorkThread::GetUsrBPCmd(void)
{
    UINT8 unUsrBpCmd;
    m_lckMutex.lock();
    unUsrBpCmd = m_unUsrBpCmd;
    m_lckMutex.unlock();
    return unUsrBpCmd;
}

void CWorkThread::SetAlmLedState(UINT8 unAlmSta)
{
    CSwitPump* pSwitPum;
    if(m_listAPumMods.size() > 0)
    {
		pSwitPum = m_listAPumMods.at(0);
		pSwitPum->SetAlmLedState(unAlmSta);
    }

	if(m_listVPumMods.size() > 0)
	{
		CSwitPump* pSwitPum;
		pSwitPum = m_listVPumMods.at(0);
		pSwitPum->SetAlmLedState(unAlmSta);
	}
}

void CWorkThread::SetBatState(UINT8 unBatSta)
{
    if(m_listAPumMods.size() > 0)
    {
		CSwitPump* pSwitPum;
		pSwitPum = m_listAPumMods.at(0);
		pSwitPum->SetBatState(unBatSta);
    }
    if(m_listVPumMods.size() > 0)
    {
		CSwitPump* pSwitPum;
		pSwitPum = m_listVPumMods.at(0);
		pSwitPum->SetBatState(unBatSta);
    }
    if(m_listWatMods.size() > 0)
    {
		CSwitWater* pSwitPum;
		pSwitPum = m_listWatMods.at(0);
		pSwitPum->SetBatState(unBatSta);
    }
}

void CWorkThread::SetPourState(UINT8      unPumType, UINT8 unIndex)
{
	CSwitPump* pSwitPum;
	UINT8 unPumIndex = 0;
	if(unPumType == DEV_APUMP_TYPE)//动脉泵
	{
		pSwitPum = m_listAPumMods.at(unIndex);
		unPumIndex = 0;
	}
	else if(unPumType == DEV_VPUMP_TYPE)//静脉泵
	{
		pSwitPum = m_listVPumMods.at(unIndex);
		unPumIndex = 1;
	}
	pSwitPum->SetPourState(m_unDataType[unPumIndex]);
}

//同步灌注状态
void CWorkThread::SynPourState(UINT8      unPumType, UINT8 unIndex)
{
	m_unDataType[unIndex] = unPumType;
}


void CWorkThread::SetPulesPrm(UINT8      unPumType, UINT8 unIndex)
{
	CSwitPump* pSwitPum;
	if(unPumType != DEV_APUMP_TYPE)//动脉泵
	{
		return ;
	}

	pSwitPum = m_listAPumMods.at(unIndex);
	g_setPulPrm.unPumType = unPumType;
	pSwitPum->SetPulseParam(&g_setPulPrm);
}

void CWorkThread::SetDevState(UINT8     unDevType)
{
    OperLogCtl operLogCtl;
	CSwitModule* pSwitDev;
	INT16 unDevPrm = 0;
	UINT8 unIndex = 0;
	if(unDevType == DEV_APUMP_TYPE)//动脉泵
	{
	    unIndex = 0;
		pSwitDev = m_listAPumMods.at(0);
		if(m_unDataType[unIndex] == PRE_POUR)
		{
		    unDevPrm = g_devConfigInfo_Edt.arteryParm.unSpeed;
		}
		else
		{
		    unDevPrm = g_devConfigInfo_Edt.arteryParm.unPress;
		}
		operLogCtl.unType = OPER_CTRL_REST_APOUR;
	}
	else if(unDevType == DEV_VPUMP_TYPE)
	{
	    pSwitDev = m_listVPumMods.at(0);
		unIndex = 1;
		if(m_unDataType[unIndex] == PRE_POUR)
		{
		    unDevPrm = g_devConfigInfo_Edt.veinParm.unSpeed;
		}
		else
		{
		    unDevPrm = g_devConfigInfo_Edt.veinParm.unPress;
		}
		operLogCtl.unType = OPER_CTRL_REST_VPOUR;
	}
	else if(unDevType == DEV_WAT_TYPE)
	{
	    pSwitDev = m_listWatMods.at(0);
		unDevPrm = g_devConfigInfo_Edt.watRooParam.unTmpVal;
		operLogCtl.unType = OPER_CTRL_REST_WATER;
	}
	else
	{
	    return ;
	}

	operLogCtl.unSite = SYS_CTL;
	GetDateTime(&operLogCtl.dtCreate);
	operLogCtl.unResult[0] = m_unDataType[unIndex];//记录复位时灌注状态
	operLogCtl.unResult[1] = m_unDataType[unIndex];//记录复位时灌注状态
	
	operLogCtl.unOperType[0] = 0;//复位
	operLogCtl.unOperType[1] = 1;//启动
	SaveOperLogData((const char*)&operLogCtl, sizeof(OperLogCtl));
	SaveOperLogInfo();	
	
	SetDevStaSync pPumSta;
	if(unDevType == DEV_WAT_TYPE)
	{
		pPumSta.unDevSat = DEV_ON;
		pPumSta.unPourSta = m_unDataType[0];
	}
	else
	{
		pPumSta.unDevSat = m_bBpRunFlag[unIndex];
		pPumSta.unPourSta = m_unDataType[unIndex];
	}
	pPumSta.unDevVal = unDevPrm;
	pSwitDev->SetDevStateSync(&pPumSta);
}


void CWorkThread::setOpenWatRoom(UINT8 unIndex, UINT8 unOpenFlg, UINT8 unSite)
{
    CSwitWater* pWatMod;

	pWatMod = m_listWatMods.at(unIndex);

    OperLogCtl operLogCtl;

	operLogCtl.unType = OPER_CTRL_TYPE_WAT;
	operLogCtl.unSite = unSite;
	GetDateTime(&operLogCtl.dtCreate);
	operLogCtl.unResult[0] = 0;
	operLogCtl.unResult[1] = 1;

	bool bValidFlag = true;
	QString strError = QString("启/停水浴失败!--");

	if(false==pWatMod->IsActive())
	{
		strError  += QString("水浴控制模块超时");
		bValidFlag =  false;
		//operLogCtl.unResult[1] = 2;
		//启停水浴
		if(DEV_ON == unOpenFlg)
		{
		    operLogCtl.unOperType[0] = 0;
			operLogCtl.unOperType[1] = 0;
		}
		else if(DEV_OFF == unOpenFlg)
		{
			operLogCtl.unOperType[0] = 1;
			operLogCtl.unOperType[1] = 0;
		}
	}

	if(true==bValidFlag)
	{
		//启停水浴
		if(DEV_ON == unOpenFlg)
		{
		    operLogCtl.unOperType[0] = 0;
			operLogCtl.unOperType[1] = 1;
		}
		else if(DEV_OFF == unOpenFlg)
		{
			operLogCtl.unOperType[0] = 1;
			operLogCtl.unOperType[1] = 0;
			operLogCtl.unResult[0] = 1;
			operLogCtl.unResult[1] = 1;
		}
		
		pWatMod->CtrlDevRun(unOpenFlg);
	}
	else
	{
		ShowStringInfo(strError.toStdString().c_str(),DLG_SHOW,ICON_ERROR);
		operLogCtl.unResult[1] = 2;
	}
	SaveOperLogData((const char*)&operLogCtl, sizeof(OperLogCtl));
	SaveOperLogInfo();	
}

bool CWorkThread::GetInfoString(ErrInfo* pErrInfo)
{
    return  m_pErrStrQueue->GetErrInfo(pErrInfo);
}

bool CWorkThread::GetUpdConfigInfo(void)
{
    UINT32  unItemIndex;
    UINT32  unDataLen;
    QString strError;
    BYTE* pDataBuf0,*pDataBuf1;
    UINT8 unShowMod = DLG_SHOW;

    if(false==g_pCfgDataUI->GetItemInfo(unItemIndex,unDataLen))
    {
        if(g_devUpdFlags.bPulSetFlag == true)
        {
            return true;
        }
        return false;
    }
    if(unItemIndex==CFG_BASIC_ITEM)
    {
        g_devUpdFlags.bBasicFlag = true;
        g_pCfgDataUI->GetGrpData(unItemIndex,\
                                 unDataLen,\
                                 (BYTE*)&g_devConfigInfo.basicCfgInfo);
		
		//printf("unMonSavTmt:%d --------------------\r\n",g_devConfigInfo.basicCfgInfo.unMonSavTmt);
    }
    else if(unItemIndex==CFG_ARTERY_PRS_ITEM ||\
		    unItemIndex==CFG_ARTERY_SPD_ITEM ||\
		    unItemIndex==CFG_ARTERY_FLW_ITEM)
    {
        g_devUpdFlags.bArteryFlag = true;
		
		m_unArteryPrmIndex = (UINT8)unItemIndex;
        g_pCfgDataUI->GetGrpData(unItemIndex,\
                                 unDataLen,\
                                 (BYTE*)&g_devConfigInfo.arteryParm);

	 //printf("A--unItemIndex:%d ---------m_unArteryPrmIndex:%d-----------\r\n",unItemIndex,m_unArteryPrmIndex);
	 //printf("A--unSpeed:%d unPress:%d\r\n",g_devConfigInfo.arteryParm.unSpeed,g_devConfigInfo.arteryParm.unPress);
		
    }
	else if(unItemIndex==CFG_VEIN_PRS_ITEM ||\
			unItemIndex==CFG_VEIN_SPD_ITEM ||\
			unItemIndex==CFG_VEIN_FLW_ITEM)
	{
		g_devUpdFlags.bVeinFlag = true;
		m_unVeinPrmIndex = unItemIndex - CFG_VEIN_SPD_ITEM + 1;
		g_pCfgDataUI->GetGrpData(unItemIndex,\
								 unDataLen,\
								 (BYTE*)&g_devConfigInfo.veinParm);
		//printf("V--unItemIndex:%d ---------m_unVeinPrmIndex:%d-----------\r\n",unItemIndex,m_unVeinPrmIndex);
		//printf("V--unSpeed:%d unPress:%d\r\n",g_devConfigInfo.veinParm.unSpeed,g_devConfigInfo.veinParm.unPress);
	}
    else if(unItemIndex==CFG_WAT_ROOM_ITEM)
    {
        g_devUpdFlags.bWtrRoomFlag = true;
		m_unWaterPrmIndex = unItemIndex - CFG_WAT_ROOM_ITEM + 1;
        g_pCfgDataUI->GetGrpData(unItemIndex,\
                                 unDataLen,\
                                 (BYTE*)&g_devConfigInfo.watRooParam);
		//printf("unItemIndex:%d ---------m_unArteryPrmIndex:%d-----------\r\n",unItemIndex,m_unArteryPrmIndex);
        //printf("unTmpVal:%d \r\n",g_devConfigInfo.watRooParam.unTmpVal);

    }
    else if(unItemIndex==CFG_BAT_PRM_ITEM)
    {
        g_devUpdFlags.bBatSetFlag = true;
        g_pCfgDataUI->GetGrpData(unItemIndex,\
                                 unDataLen,\
                                 (BYTE*)&g_devConfigInfo.batParam);
    }	
    else if(unItemIndex==CFG_ALM_PRM_ITEM)
    {
    	g_devUpdFlags.bAlmSetFlag = true;
        g_pCfgDataUI->GetGrpData(unItemIndex,\
                                 unDataLen,\
                                 (BYTE*)&g_devConfigInfo.devAlmParam);
		//printf("g_devConfigInfo.devAlmParam.unAlmUTmpA:%d \r\n",g_devConfigInfo.devAlmParam.unAlmUTmpA);
    }
    else if(unItemIndex==CFG_POUR_PRM_ITEM)
    {
    	g_devUpdFlags.bPourSetFlag = true;
        g_pCfgDataUI->GetGrpData(unItemIndex,\
                                 unDataLen,\
                                 (BYTE*)&g_devConfigInfo.devPourParam);
    }

    ShowDiff();
    pDataBuf0 = (BYTE*)&g_devConfigInfo_Edt;
    pDataBuf0 += offsetof(DevCofnigInfo,basicCfgInfo);
    pDataBuf1 = (BYTE*)&g_devConfigInfo;
    pDataBuf1 += offsetof(DevCofnigInfo,basicCfgInfo);
    unDataLen = sizeof(g_devConfigInfo)-offsetof(DevCofnigInfo,basicCfgInfo);
    if(true==SaveConfigInfo(strError))
    {
        QString strCfgFilePath = qApp->applicationDirPath()+CONFIG_FILE_NAME;
        if(true==LoadConfigInfo(strCfgFilePath,strError))
        {
            if(0==memcmp(pDataBuf0,pDataBuf1,unDataLen))
            {
                //ShowStringInfo("保存成功!",unShowMod,ICON_INFO);
                return true;
            }
            else
            {
                UINT32 unIndex;
                QString strErrInfo;
                for(unIndex = 0; unIndex < unDataLen; unIndex++)
                {
                    if(pDataBuf0[unIndex]!=pDataBuf1[unIndex])
                    {
                        strErrInfo += QString("位置：<%1> \r\n").arg(unIndex);
                    }
                }
                strErrInfo = "数据不一致！\r\n"+strErrInfo;
                ShowStringInfo(strErrInfo.toStdString().c_str(),unShowMod,ICON_ERROR);
            }
        }
        else
        {
            ShowStringInfo(strError.toStdString().c_str(),unShowMod,ICON_ERROR);
        }
    }
    else
    {
        //printf("Save Config Files Fail\r\n");
        ShowStringInfo(strError.toStdString().c_str(),unShowMod,ICON_ERROR);
    }
    return false;
}

void CWorkThread::ShowDiff(void)
{
    UINT32 unDataLen;
    BYTE* pDataBuf0,*pDataBuf1;
    pDataBuf0 = (BYTE*)&g_devConfigInfo_Edt;
    pDataBuf0 += offsetof(DevCofnigInfo,basicCfgInfo);
    pDataBuf1 = (BYTE*)&g_devConfigInfo;
    pDataBuf1 += offsetof(DevCofnigInfo,basicCfgInfo);
    unDataLen = sizeof(g_devConfigInfo)-offsetof(DevCofnigInfo,basicCfgInfo);
    if(0!=memcmp(pDataBuf0,pDataBuf1,unDataLen))
    {
        UINT32 unIndex;
        for(unIndex= 0; unIndex < unDataLen; unIndex++)
        {
            if(pDataBuf0[unIndex]!=pDataBuf1[unIndex])
            {
                printf("Pos:%lu\r\n",unIndex);
            }
        }
        printf("B_Pos:%u\r\n",offsetof(DevCofnigInfo,basicCfgInfo));
        printf("N_Pos:%u\r\n",offsetof(DevCofnigInfo,arteryParm));
        printf("BT_Pos:%u\r\n",offsetof(DevCofnigInfo,veinParm));
        printf("CH_Pos:%u\r\n",offsetof(DevCofnigInfo,watRooParam));
        printf("DS_Pos:%u\r\n",offsetof(DevCofnigInfo,devAlmParam));
        memcpy(&g_devConfigInfo_Edt,&g_devConfigInfo,sizeof(g_devConfigInfo));
    }
}


unsigned int CWorkThread::GetBloodPumpGrpID(void)//long
{
    return m_unBpGrpID;
}

/**/
void CWorkThread::OnPumStop(UINT8 unPumType)
{
    m_lckMutex.lock();
    m_bBpRunFlag[unPumType] = false;
    m_lckMutex.unlock();
}
bool CWorkThread::IsPumpRuning(UINT8 unPumType)
{
    return m_bBpRunFlag[unPumType];
}

void CWorkThread::SetPumpRuning(UINT8 unPumType, bool bRunStat)
{
    m_bBpRunFlag[unPumType] = bRunStat;
}

void CWorkThread::ArteryPourAlm(void)
{
	//泵压力高
	if(g_pourTstData.tstData.unAPrssVal > g_devConfigInfo.devAlmParam.unAlmUPresA &&\
		g_pourTstData.tstData.unAPrssVal < PRESS_ERR_VAL_A)//200.0
	{
	    if(g_devAlmBits.ApumGrpAlm.bPressUBits == false && \
		   m_bBpRunFlag[0] == true && m_unDataType[0] == STR_POUR)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPressUBits,\
					   H_P_ALM_ITEM_A_PRE_UP,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unAPrssVal,1);
			g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
			g_devAlmBits.ApumGrpAlm.bPressUBits = true;
	    }
	}
	else if((g_devConfigInfo.devAlmParam.unAlmUPresA - \
			  g_pourTstData.tstData.unAPrssVal)>MAX_ALM_PRES_DIF)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPressUBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPressUBits,\
					   H_P_ALM_ITEM_A_PRE_UP,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unAPrssVal,0);
			g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
			g_devAlmBits.ApumGrpAlm.bPressUBits = false;
	    }
	}
	//泵压力低-技术
	if(g_pourTstData.tstData.unAPrssVal < 0)
	{
		if(g_devAlmBits.ApumGrpAlm.bPressLBits == false && \
		   m_bBpRunFlag[0] == true && m_unDataType[0] == STR_POUR)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPressLBits,\
					 H_T_ALM_ITEM_A_PRE_DN,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unAPrssVal,1);
			g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
			g_devAlmBits.ApumGrpAlm.bPressLBits = true;
		}
	}
	else if(g_pourTstData.tstData.unAPrssVal >= MAX_ALM_PRES_DIF_DN)
	{
		if(g_devAlmBits.ApumGrpAlm.bPressLBits == true)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPressLBits,\
					 H_T_ALM_ITEM_A_PRE_DN,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unAPrssVal,0);
			g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
			g_devAlmBits.ApumGrpAlm.bPressLBits = false;
		}
	}
	//压力传感器异常-技术
	if(g_pourTstData.tstData.unAPrssVal >= PRESS_ERR_VAL_A)
	{
		if(g_devAlmBits.ApumGrpAlm.bPressErrBits == false && \
		   m_bBpRunFlag[0] == true && m_unDataType[0] == STR_POUR)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPressErrBits,\
				   H_T_ALM_ITEM_A_PRE_SEN,APUM_DEV_BAS_ID,0x00,\
				   g_pourTstData.tstData.unAPrssVal,1);
			g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
			g_devAlmBits.ApumGrpAlm.bPressErrBits = true;
		}
	}
	else
	{
		if(g_devAlmBits.ApumGrpAlm.bPressErrBits == true)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPressErrBits,\
				   H_T_ALM_ITEM_A_PRE_SEN,APUM_DEV_BAS_ID,0x00,\
				   g_pourTstData.tstData.unAPrssVal,0);
			g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
			g_devAlmBits.ApumGrpAlm.bPressErrBits = false;
		}
	}
	//泵压流量低
	if(g_pourTstData.tstData.unAFlowVal < g_devConfigInfo.devAlmParam.unAlmLFlowA)
	{
		//流量告警 泵开，等待5秒
		if(m_bBpRunFlag[0] == true	&& m_unDataType[0] == STR_POUR && \
		   m_unAlmFlowDlySec[0] > 5 && g_devAlmBits.ApumGrpAlm.bFlowLBits == false)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFlowLBits,\
					   H_P_ALM_ITEM_A_FLO_DN,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unAFlowVal,1);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
			g_devAlmBits.ApumGrpAlm.bFlowLBits = true;
		}
	}
	else if(g_pourTstData.tstData.unAFlowVal - \
			g_devConfigInfo.devAlmParam.unAlmLFlowA > MAX_ALM_FLOW_DIF)
	{
	    if(g_devAlmBits.ApumGrpAlm.bFlowLBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFlowLBits,\
					   H_P_ALM_ITEM_A_FLO_DN,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unAFlowVal,0);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
			g_devAlmBits.ApumGrpAlm.bFlowLBits = false;
	    }
	}
	//泵压流量高
	if(g_pourTstData.tstData.unAFlowVal >= g_devConfigInfo.devAlmParam.unAlmUFlowA)
	{
		if(m_bBpRunFlag[0] == true && m_unDataType[0] == STR_POUR && \
		   g_devAlmBits.ApumGrpAlm.bFlowUBits == false)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFlowUBits,\
					   H_P_ALM_ITEM_A_FLO_UP,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unAFlowVal,1);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
			g_devAlmBits.ApumGrpAlm.bFlowUBits = true;
		}
	}
	else if(g_devConfigInfo.devAlmParam.unAlmUFlowA - \
			g_pourTstData.tstData.unAFlowVal > MAX_ALM_FLOW_DIF)
	{
	    if(g_devAlmBits.ApumGrpAlm.bFlowUBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFlowUBits,\
					   H_P_ALM_ITEM_A_FLO_UP,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unAFlowVal,0);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
			g_devAlmBits.ApumGrpAlm.bFlowUBits = false;
	    }
	}
	//流量传感器异常
	if(g_pourTstData.tstData.unAFlowVal >= FLOW_ERR_VAL_A || \
	   g_pourTstData.tstData.unAFlowVal <= (FLOW_ERR_VAL_A*-1))
	{
		if(g_devAlmBits.ApumGrpAlm.bFlowSensorBits == false && \
		   m_bBpRunFlag[0] == true && m_unDataType[0] == STR_POUR)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFlowSensorBits,\
					 M_T_ALM_ITEM_A_FLO_SEN,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unAFlowVal,1);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
			g_devAlmBits.ApumGrpAlm.bFlowSensorBits = true;
		}
	}
	else
	{
		if(g_devAlmBits.ApumGrpAlm.bFlowSensorBits == true)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFlowSensorBits,\
					 M_T_ALM_ITEM_A_FLO_SEN,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unAFlowVal,0);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
			g_devAlmBits.ApumGrpAlm.bFlowSensorBits = false;
		}
	}
}

void CWorkThread::ArteryPrePourAlm(void)
{
    UINT8 unAlmBits = 0;
    //血温
	if(g_pourTstData.tstData.unATmpVal > g_devConfigInfo.devAlmParam.unAlmUTmpA)
	{
	    if(g_devAlmBits.ApumGrpAlm.bTmpUBits == false && \
		   m_bBpRunFlag[0] == true && m_unDataType[0] == STR_POUR)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bTmpUBits,\
					 H_P_ALM_ITEM_A_TMP_UP,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unATmpVal,1);
			g_DataAlarm.unATmpVal = g_pourTstData.tstData.unATmpVal;
			g_devAlmBits.ApumGrpAlm.bTmpUBits = true;
		}
	}
	else if(g_devConfigInfo.devAlmParam.unAlmUTmpA - \
			g_pourTstData.tstData.unATmpVal > MAX_ALM_TMP_DIF)
	{
		if(g_devAlmBits.ApumGrpAlm.bTmpUBits == true)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bTmpUBits,\
					 H_P_ALM_ITEM_A_TMP_UP,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unATmpVal,0);
			g_DataAlarm.unATmpVal = g_pourTstData.tstData.unATmpVal;
			g_devAlmBits.ApumGrpAlm.bTmpUBits = false;
		}
	}	
	//动脉泵未连接-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_APUMP_TYPE, PUM_LOS_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPumTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPumTmtBits,\
					 H_T_ALM_ITEM_A_PUM_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.ApumGrpAlm.bPumTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPumTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPumTmtBits,\
					 H_T_ALM_ITEM_A_PUM_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.ApumGrpAlm.bPumTmtBits = false;
	    }
	}
	//动脉泵异常-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_APUMP_TYPE, PUM_ERR_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPumErrBits == false)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPumErrBits,\
					 H_T_ALM_ITEM_A_PUM_ERR,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.ApumGrpAlm.bPumErrBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPumErrBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPumErrBits,\
					 H_T_ALM_ITEM_A_PUM_ERR,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.ApumGrpAlm.bPumErrBits = false;
	    }
	}
	//动脉血泵有气泡
	UINT8 unBubbVal = m_procPour.GetBubbleVal(DEV_APUMP_TYPE);
	if(unBubbVal > \
	g_devConfigInfo.devAlmParam.unAlmBubbleA)
	{
		//气泡告警 泵开，等待5秒
		if(m_unAlmFlowDlySec[0] > 5 &&\
		   g_devAlmBits.ApumGrpAlm.bBubblBits == false)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bBubblBits,\
					 H_P_ALM_ITEM_A_BUBBLE,APUM_DEV_BAS_ID,0x00,\
					 unBubbVal,1);
			g_devAlmBits.ApumGrpAlm.bBubblBits = true;
		}
	}
	else if(unBubbVal == 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bBubblBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bBubblBits,\
					 H_P_ALM_ITEM_A_BUBBLE,APUM_DEV_BAS_ID,0x00,\
					 unBubbVal,0);
			g_devAlmBits.ApumGrpAlm.bBubblBits = false;
	    }
	}

	//动脉压力传感器线缆未连接-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_APUMP_TYPE, PUM_PRE_SEN_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPreLinBits == false)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPreLinBits,\
					 M_T_ALM_ITEM_A_PRE_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.ApumGrpAlm.bPreLinBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPreLinBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPreLinBits,\
					 M_T_ALM_ITEM_A_PRE_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.ApumGrpAlm.bPreLinBits = false;
	    }
	}
	//动脉血压监测板失联-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_APUMP_TYPE, PUM_PRE_BOA_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPreTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPreTmtBits,\
					 M_T_ALM_ITEM_A_PRE_DEV_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.ApumGrpAlm.bPreTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bPreTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bPreTmtBits,\
					 M_T_ALM_ITEM_A_PRE_DEV_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.ApumGrpAlm.bPreTmtBits = false;
	    }
	}
	//动脉流量传感器未连接-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_APUMP_TYPE, PUM_FLO_LOS_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.ApumGrpAlm.bFloTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFloTmtBits,\
					 M_T_ALM_ITEM_A_FLO_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.ApumGrpAlm.bFloTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bFloTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bFloTmtBits,\
					 M_T_ALM_ITEM_A_FLO_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.ApumGrpAlm.bFloTmtBits = false;
	    }
	}
	//动脉泵转速高
	if(g_pourTstData.tstData.unASpeeVal >= g_devConfigInfo.devAlmParam.unAlmUSpeeA)
	{
		if(g_devAlmBits.ApumGrpAlm.bSpeedUBits == false)
		{
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bSpeedUBits,\
					   M_T_ALM_ITEM_A_PRE_UP,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unASpeeVal,1);
			g_DataAlarm.unASpeeVal = g_pourTstData.tstData.unASpeeVal;
			g_devAlmBits.ApumGrpAlm.bSpeedUBits = true;
		}
	}
	else if(g_devConfigInfo.devAlmParam.unAlmUSpeeA - \
			g_pourTstData.tstData.unASpeeVal > MAX_ALM_FLOW_DIF)
	{
	    if(g_devAlmBits.ApumGrpAlm.bSpeedUBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bSpeedUBits,\
					   M_T_ALM_ITEM_A_PRE_UP,APUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unASpeeVal,0);
			g_DataAlarm.unASpeeVal = g_pourTstData.tstData.unASpeeVal;
			g_devAlmBits.ApumGrpAlm.bSpeedUBits = false;
	    }
	}

	//动脉血温传感器未连接
	unAlmBits = m_procPour.GetDevAlmState(DEV_APUMP_TYPE, PUM_TMP_LOS_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.ApumGrpAlm.bTmpTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bTmpTmtBits,\
					 L_T_ALM_ITEM_A_TMP_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.ApumGrpAlm.bTmpTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bTmpTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bTmpTmtBits,\
					 L_T_ALM_ITEM_A_TMP_TMT,APUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.ApumGrpAlm.bTmpTmtBits = false;
	    }
	}
	//血温度传感器异常
	if(g_pourTstData.tstData.unATmpVal > RMP_ERR_VAL_A ||\
	   g_pourTstData.tstData.unATmpVal < 0)
	{
	    if(g_devAlmBits.ApumGrpAlm.bTmpSensorBits == false)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bTmpSensorBits,\
					 L_T_ALM_ITEM_A_TMP_SEN,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unATmpVal,1);
			g_DataAlarm.unATmpVal = g_pourTstData.tstData.unATmpVal;
			g_devAlmBits.ApumGrpAlm.bTmpSensorBits = true;
	   	}
	}
	else
	{
	    if(g_devAlmBits.ApumGrpAlm.bTmpSensorBits == true)
	    {
			SetAlmItem(g_devAlmBits.ApumGrpAlm.bTmpSensorBits,\
					 L_T_ALM_ITEM_A_TMP_SEN,APUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unATmpVal,0);
			g_DataAlarm.unATmpVal = g_pourTstData.tstData.unATmpVal;
			g_devAlmBits.ApumGrpAlm.bTmpSensorBits = false;
	    }
	}	
}
void CWorkThread::CheckArteryAlm(void)
{
	//灌注告警
	ArteryPourAlm();
    //开机告警
    ArteryPrePourAlm();
}

//门脉
void CWorkThread::VeinPourAlm(void)
{
	//泵压力高
	if(g_pourTstData.tstData.unVPrssVal > g_devConfigInfo.devAlmParam.unAlmUPresV &&\
		g_pourTstData.tstData.unVPrssVal < PRESS_ERR_VAL_V)//200.0
	{
	    if(g_devAlmBits.VpumGrpAlm.bPressUBits == false && \
		   m_bBpRunFlag[1] == true && m_unDataType[1] == STR_POUR)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPressUBits,\
					   H_P_ALM_ITEM_V_PRE_UP,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVPrssVal,1);
			g_DataAlarm.unVPrssVal = g_pourTstData.tstData.unVPrssVal;
			g_devAlmBits.VpumGrpAlm.bPressUBits = true;
	    }
	}
	else if((g_devConfigInfo.devAlmParam.unAlmUPresV - \
			  g_pourTstData.tstData.unVPrssVal)>MAX_ALM_PRES_DIF)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPressUBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPressUBits,\
					   H_P_ALM_ITEM_V_PRE_UP,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVPrssVal,0);
			g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unVPrssVal;
			g_devAlmBits.VpumGrpAlm.bPressUBits = false;
	    }
	}
	//泵压力低
	if(g_pourTstData.tstData.unVPrssVal < 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPressLBits == false && \
		   m_bBpRunFlag[1] == true && m_unDataType[1] == STR_POUR)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPressLBits,\
					   H_P_ALM_ITEM_V_PRE_DN,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVPrssVal,1);
			g_DataAlarm.unVPrssVal = g_pourTstData.tstData.unVPrssVal;
			g_devAlmBits.VpumGrpAlm.bPressLBits = true;
	    }
	}
	else if(g_pourTstData.tstData.unVPrssVal >= MAX_ALM_PRES_DIF_DN)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPressLBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPressLBits,\
					   H_P_ALM_ITEM_V_PRE_DN,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVPrssVal,0);
			g_DataAlarm.unVPrssVal = g_pourTstData.tstData.unVPrssVal;
			g_devAlmBits.VpumGrpAlm.bPressLBits = false;
	    }
	}
	//压力传感器异常-技术
	if(g_pourTstData.tstData.unVPrssVal >= PRESS_ERR_VAL_V)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPressErrBits == false && \
		   m_bBpRunFlag[1] == true && m_unDataType[1] == STR_POUR)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPressErrBits,\
					 H_T_ALM_ITEM_V_PRE_SEN,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVPrssVal,1);
			g_DataAlarm.unVPrssVal = g_pourTstData.tstData.unVPrssVal;
			g_devAlmBits.VpumGrpAlm.bPressErrBits = true;
	    }
	}
	else
	{
	    if(g_devAlmBits.VpumGrpAlm.bPressErrBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPressErrBits,\
					 H_T_ALM_ITEM_V_PRE_SEN,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVPrssVal,0);
			g_DataAlarm.unVPrssVal = g_pourTstData.tstData.unVPrssVal;
			g_devAlmBits.VpumGrpAlm.bPressErrBits = false;
	    }
	}	
	//泵压流量低
	if(g_pourTstData.tstData.unVFlowVal < g_devConfigInfo.devAlmParam.unAlmLFlowV)
	{
		//流量告警 泵开，等待5秒
		if(m_bBpRunFlag[1] == true	&& m_unDataType[1] == STR_POUR && \
		   m_unAlmFlowDlySec[1] > 5 && g_devAlmBits.VpumGrpAlm.bFlowLBits == false)
		{
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFlowLBits,\
					   H_P_ALM_ITEM_V_FLO_DN,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVFlowVal,1);
			g_DataAlarm.unVFlowVal = g_pourTstData.tstData.unVFlowVal;
			g_devAlmBits.VpumGrpAlm.bFlowLBits = true;
		}
	}
	else if(g_pourTstData.tstData.unVFlowVal - \
			g_devConfigInfo.devAlmParam.unAlmLFlowV > MAX_ALM_FLOW_DIF)
	{
	    if(g_devAlmBits.VpumGrpAlm.bFlowLBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFlowLBits,\
					   H_P_ALM_ITEM_V_FLO_DN,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVFlowVal,0);
			g_DataAlarm.unVFlowVal = g_pourTstData.tstData.unVFlowVal;
			g_devAlmBits.VpumGrpAlm.bFlowLBits = false;
	    }
	}
	//泵压流量高
	if(g_pourTstData.tstData.unVFlowVal >= g_devConfigInfo.devAlmParam.unAlmUFlowV)
	{
		if(m_bBpRunFlag[1] == true && m_unDataType[1] == STR_POUR && \
		   g_devAlmBits.VpumGrpAlm.bFlowUBits == false)
		{
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFlowUBits,\
					   H_P_ALM_ITEM_V_FLO_UP,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVFlowVal,1);
			g_DataAlarm.unVFlowVal = g_pourTstData.tstData.unVFlowVal;
			g_devAlmBits.VpumGrpAlm.bFlowUBits = true;
		}
	}
	else if(g_devConfigInfo.devAlmParam.unAlmUFlowV - \
			g_pourTstData.tstData.unVFlowVal > MAX_ALM_FLOW_DIF)
	{
	    if(g_devAlmBits.VpumGrpAlm.bFlowUBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFlowUBits,\
					   H_P_ALM_ITEM_A_FLO_UP,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVFlowVal,0);
			g_DataAlarm.unVFlowVal = g_pourTstData.tstData.unVFlowVal;
			g_devAlmBits.VpumGrpAlm.bFlowUBits = false;
	    }
	}
}

void CWorkThread::VeinPrePourAlm(void)
{
    UINT8 unAlmBits = 0;
    //血温
	if(g_pourTstData.tstData.unVTmpVal > g_devConfigInfo.devAlmParam.unAlmUTmpV)
	{
	    if(g_devAlmBits.VpumGrpAlm.bTmpUBits == false && \
		   m_bBpRunFlag[1] == true && m_unDataType[1] == STR_POUR)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bTmpUBits,\
					 H_P_ALM_ITEM_V_TMP_UP,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVTmpVal,1);
			g_DataAlarm.unVTmpVal = g_pourTstData.tstData.unVTmpVal;
			g_devAlmBits.VpumGrpAlm.bTmpUBits = true;
		}
	}
	else if(g_devConfigInfo.devAlmParam.unAlmUTmpV - \
			g_pourTstData.tstData.unVTmpVal > MAX_ALM_TMP_DIF)
	{
		if(g_devAlmBits.VpumGrpAlm.bTmpUBits == true)
		{
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bTmpUBits,\
					 H_P_ALM_ITEM_V_TMP_UP,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVTmpVal,0);
			g_DataAlarm.unVTmpVal = g_pourTstData.tstData.unVTmpVal;
			g_devAlmBits.VpumGrpAlm.bTmpUBits = false;
		}
	}
	//静脉泵未连接-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_VPUMP_TYPE, PUM_LOS_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPumTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPumTmtBits,\
					 H_T_ALM_ITEM_V_PUM_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.VpumGrpAlm.bPumTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPumTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPumTmtBits,\
					 H_T_ALM_ITEM_V_PUM_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.VpumGrpAlm.bPumTmtBits = false;
	    }
	}
	//静脉泵异常-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_APUMP_TYPE, PUM_ERR_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPumErrBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPumErrBits,\
					 H_T_ALM_ITEM_V_PUM_ERR,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.VpumGrpAlm.bPumErrBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPumErrBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPumErrBits,\
					 H_T_ALM_ITEM_V_PUM_ERR,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.VpumGrpAlm.bPumErrBits = false;
	    }
	}
	//静脉血泵有气泡
	UINT8 unBubbVal = m_procPour.GetBubbleVal(DEV_VPUMP_TYPE);
	if(unBubbVal > \
	g_devConfigInfo.devAlmParam.unAlmBubbleV)
	{
		//气泡告警 泵开，等待5秒
		if(m_unAlmFlowDlySec[1] > 5 &&\
		   g_devAlmBits.VpumGrpAlm.bBubblBits == false)
		{
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bBubblBits,\
					 H_P_ALM_ITEM_V_BUBBLE,VPUM_DEV_BAS_ID,0x00,\
					 unBubbVal,1);
			g_devAlmBits.VpumGrpAlm.bBubblBits = true;
		}
	}
	else if(unBubbVal == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bBubblBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bBubblBits,\
					 H_P_ALM_ITEM_V_BUBBLE,VPUM_DEV_BAS_ID,0x00,\
					 unBubbVal,0);
			g_devAlmBits.VpumGrpAlm.bBubblBits = false;
	    }
	}	
	//静脉压力传感器线缆未连接-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_VPUMP_TYPE, PUM_PRE_SEN_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPreLinBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPreLinBits,\
					 M_T_ALM_ITEM_V_PRE_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.VpumGrpAlm.bPreLinBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPreLinBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPreLinBits,\
					 M_T_ALM_ITEM_V_PRE_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.VpumGrpAlm.bPreLinBits = false;
	    }
	}
	//静脉血压监测板失联-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_VPUMP_TYPE, PUM_PRE_BOA_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPreTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPreTmtBits,\
					 M_T_ALM_ITEM_V_PRE_DEV_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.VpumGrpAlm.bPreTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bPreTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bPreTmtBits,\
					 M_T_ALM_ITEM_V_PRE_DEV_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.VpumGrpAlm.bPreTmtBits = false;
	    }
	}
	//静脉流量传感器未连接-技术
	unAlmBits = m_procPour.GetDevAlmState(DEV_VPUMP_TYPE, PUM_FLO_LOS_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.VpumGrpAlm.bFloTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFloTmtBits,\
					 M_T_ALM_ITEM_V_FLO_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.VpumGrpAlm.bFloTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bFloTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFloTmtBits,\
					 M_T_ALM_ITEM_V_FLO_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.VpumGrpAlm.bFloTmtBits = false;
	    }
	}
	//静脉泵转速高
	if(g_pourTstData.tstData.unVSpeeVal >= g_devConfigInfo.devAlmParam.unAlmUSpeeV)
	{
		if(g_devAlmBits.VpumGrpAlm.bSpeedUBits == false)
		{
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bSpeedUBits,\
					   M_T_ALM_ITEM_V_PRE_UP,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unASpeeVal,1);
			g_DataAlarm.unVSpeeVal = g_pourTstData.tstData.unVSpeeVal;
			g_devAlmBits.VpumGrpAlm.bSpeedUBits = true;
		}
	}
	else if(g_devConfigInfo.devAlmParam.unAlmUSpeeV - \
			g_pourTstData.tstData.unVSpeeVal > MAX_ALM_FLOW_DIF)
	{
	    if(g_devAlmBits.VpumGrpAlm.bSpeedUBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bSpeedUBits,\
					   M_T_ALM_ITEM_V_PRE_UP,VPUM_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unVSpeeVal,0);
			g_DataAlarm.unVSpeeVal = g_pourTstData.tstData.unVSpeeVal;
			g_devAlmBits.VpumGrpAlm.bSpeedUBits = false;
	    }
	}
	//静流量传感器异常
	if(g_pourTstData.tstData.unVFlowVal >= FLOW_ERR_VAL_V || \
	   g_pourTstData.tstData.unVFlowVal <= (FLOW_ERR_VAL_V*-1))
	{
	    if(g_devAlmBits.VpumGrpAlm.bFlowSensorBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFlowSensorBits,\
					 M_T_ALM_ITEM_V_FLO_SEN,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVFlowVal,1);
			g_DataAlarm.unVFlowVal = g_pourTstData.tstData.unVFlowVal;
			g_devAlmBits.VpumGrpAlm.bFlowSensorBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bFlowSensorBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bFlowSensorBits,\
					 M_T_ALM_ITEM_V_FLO_SEN,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVFlowVal,0);
			g_devAlmBits.VpumGrpAlm.bFlowSensorBits = false;
	    }
	}
	//静脉血温传感器未连接
	unAlmBits = m_procPour.GetDevAlmState(DEV_VPUMP_TYPE, PUM_TMP_LOS_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.VpumGrpAlm.bTmpTmtBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bTmpTmtBits,\
					 L_T_ALM_ITEM_V_TMP_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,1);
			g_devAlmBits.VpumGrpAlm.bTmpTmtBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bTmpTmtBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bTmpTmtBits,\
					 L_T_ALM_ITEM_V_TMP_TMT,VPUM_DEV_BAS_ID,0x00,\
					 unAlmBits,0);
			g_devAlmBits.VpumGrpAlm.bTmpTmtBits = false;
	    }
	}
	//血温度传感器异常
	if(g_pourTstData.tstData.unVTmpVal > RMP_ERR_VAL_V ||\
	   g_pourTstData.tstData.unVTmpVal < 0)
	{
	    if(g_devAlmBits.VpumGrpAlm.bTmpSensorBits == false)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bTmpSensorBits,\
					 L_T_ALM_ITEM_V_TMP_SEN,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVTmpVal,1);
			g_DataAlarm.unVTmpVal = g_pourTstData.tstData.unVTmpVal;
			g_devAlmBits.VpumGrpAlm.bTmpSensorBits = true;
	    }
	}
	else
	{
	    if(g_devAlmBits.VpumGrpAlm.bTmpSensorBits == true)
	    {
			SetAlmItem(g_devAlmBits.VpumGrpAlm.bTmpSensorBits,\
					 L_T_ALM_ITEM_V_TMP_SEN,VPUM_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unVTmpVal,0);
			g_DataAlarm.unVTmpVal = g_pourTstData.tstData.unVTmpVal;
			g_devAlmBits.VpumGrpAlm.bTmpSensorBits = false;
	    }
	}	
}

void CWorkThread::CheckVeinAlm(void)
{
	//灌注告警
	VeinPourAlm();
    //开机告警
    VeinPrePourAlm();
}

void CWorkThread::CheckWaterAlm(void)
{
    UINT8 unAlmBits = 0;
    //水温过高
	if(g_pourTstData.tstData.unWatTmpVal >= g_devConfigInfo.devAlmParam.unAlmUWatTmp &&\
	   g_pourTstData.tstData.unWatTmpVal < TMP_ERR_VAL_W)
	{
	    if(g_devAlmBits.watGrpAlm.bTmpUBits == false)
	    {
			SetAlmItem(g_devAlmBits.watGrpAlm.bTmpUBits,\
					   H_T_ALM_ITEM_WAT_TMP_UP,WAT_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unWatTmpVal,1);
			g_DataAlarm.unWatTmpVal = g_pourTstData.tstData.unWatTmpVal;
			g_devAlmBits.watGrpAlm.bTmpUBits = true;
	    }
	}
	else if((g_devConfigInfo.devAlmParam.unAlmUWatTmp - \
			 g_pourTstData.tstData.unWatTmpVal)>MAX_ALM_WAT_TMP_DIF)
	{
	    if(g_devAlmBits.watGrpAlm.bTmpUBits == true)
	    {
			SetAlmItem(g_devAlmBits.watGrpAlm.bTmpUBits,\
					   H_T_ALM_ITEM_WAT_TMP_UP,WAT_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unWatTmpVal,0);
			g_DataAlarm.unWatTmpVal = g_pourTstData.tstData.unWatTmpVal;
			g_devAlmBits.watGrpAlm.bTmpUBits = false;
	    }
	}

	 //水压过高
	 //if(g_pourTstData.tstData.unWatPreVal >= g_devConfigInfo.devAlmParam.unAlmUWatPre &&\
		//g_pourTstData.tstData.unWatPreVal < PRESS_ERR_VAL_W)
	 unAlmBits = m_procPour.GetDevAlmState(DEV_WAT_TYPE, WAT_LIN_UP_BITS);
	 if(unAlmBits == 1)
	 {
		 if(g_devAlmBits.watGrpAlm.bWatPreUBits == false)
		 {
			 SetAlmItem(g_devAlmBits.watGrpAlm.bWatPreUBits,\
						H_T_ALM_ITEM_WAT_PPRE_UP,WAT_DEV_BAS_ID,0x00,0,1);
			 g_devAlmBits.watGrpAlm.bWatPreUBits = true;
		 }
	 }
	 //else if((g_devConfigInfo.devAlmParam.unAlmUWatPre - \
			  //g_pourTstData.tstData.unWatPreVal)>MAX_ALM_WAT_PRE_DIF)
	 else if(unAlmBits == 0)
	 {
		 if(g_devAlmBits.watGrpAlm.bWatPreUBits == true)
		 {
			 SetAlmItem(g_devAlmBits.watGrpAlm.bWatPreUBits,\
						H_T_ALM_ITEM_WAT_PPRE_UP,WAT_DEV_BAS_ID,0x00,0,0);
			 g_devAlmBits.watGrpAlm.bWatPreUBits = false;
		 }
	 }
	//水浴水温传感器异常
	unAlmBits = m_procPour.GetDevAlmState(DEV_WAT_TYPE, WAT_TMP_BITS);
	if(unAlmBits == 1)
	{
	    if(g_devAlmBits.watGrpAlm.bTmpSensorBits == false)
	    {
			SetAlmItem(g_devAlmBits.watGrpAlm.bTmpSensorBits,\
				       H_T_ALM_ITEM_WAT_TMP_SEN,WAT_DEV_BAS_ID,0x00,\
				       unAlmBits,1);
			g_devAlmBits.watGrpAlm.bTmpSensorBits = true;
	    }
	}
	else if(unAlmBits == 0)
	{
	    if(g_devAlmBits.watGrpAlm.bTmpSensorBits == true)
	    {
			SetAlmItem(g_devAlmBits.watGrpAlm.bTmpSensorBits,\
				       H_T_ALM_ITEM_WAT_TMP_SEN,WAT_DEV_BAS_ID,0x00,\
				       unAlmBits,0);
			g_devAlmBits.watGrpAlm.bTmpSensorBits = false;
	    }
	}
	//水浴---水位低
	if(g_devConfigInfo.devAlmParam.unAlmLWatLin > g_pourTstData.tstData.unWatLine)
	{
		if(g_devAlmBits.watGrpAlm.bLinLBits == false)
		{
			SetAlmItem(g_devAlmBits.watGrpAlm.bLinLBits,\
					   M_T_ALM_ITEM_WAT_LIN_DN,WAT_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unWatLine,1);
			g_DataAlarm.unWatLine = g_pourTstData.tstData.unWatLine;
			g_devAlmBits.watGrpAlm.bLinLBits = true;
		}
	}
	else if((g_pourTstData.tstData.unWatLine - \
		     g_devConfigInfo.devAlmParam.unAlmLWatLin)>=MAX_ALM_WAT_LIN_DIF)
	{
		if(g_devAlmBits.watGrpAlm.bLinLBits == true)
		{
			SetAlmItem(g_devAlmBits.watGrpAlm.bLinLBits,\
					   M_T_ALM_ITEM_WAT_LIN_DN,WAT_DEV_BAS_ID,0x00,\
					   g_DataAlarm.unWatLine,0);
			g_DataAlarm.unWatLine = g_pourTstData.tstData.unWatLine;
			g_devAlmBits.watGrpAlm.bLinLBits = false;
		}
	}
	//水浴风扇异常
	unAlmBits = m_procPour.GetDevAlmState(DEV_WAT_TYPE, WAT_FAN_BITS);
	if(unAlmBits == 1)
	{
		if(g_devAlmBits.watGrpAlm.bFanBits == false)
		{
			SetAlmItem(g_devAlmBits.watGrpAlm.bFanBits,\
					   M_T_ALM_ITEM_WAT_FAN_ERR,WAT_DEV_BAS_ID,0x00,\
					   unAlmBits,1);
			g_devAlmBits.watGrpAlm.bFanBits = true;
		}
	}
	else if(unAlmBits == 0)
	{
		if(g_devAlmBits.watGrpAlm.bFanBits == true)
		{
			SetAlmItem(g_devAlmBits.watGrpAlm.bFanBits,\
					M_T_ALM_ITEM_WAT_FAN_ERR,WAT_DEV_BAS_ID,0x00,\
					unAlmBits,0);
			g_devAlmBits.watGrpAlm.bFanBits = false;
		}
	}
	 //水浴---水位高
	 if(g_pourTstData.tstData.unWatLine >= g_devConfigInfo.devAlmParam.unAlmUWatLin)
	{
	    if(g_devAlmBits.watGrpAlm.bLinUBits == false)
	    {
			SetAlmItem(g_devAlmBits.watGrpAlm.bLinUBits,\
					   L_T_ALM_ITEM_WAT_LIN_UP,WAT_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unWatLine,1);
			g_DataAlarm.unWatLine = g_pourTstData.tstData.unWatLine;
			g_devAlmBits.watGrpAlm.bLinUBits = 1;
	    }
	}
	else if((g_devConfigInfo.devAlmParam.unAlmUWatLin - \
			  g_pourTstData.tstData.unWatLine)>=MAX_ALM_WAT_LIN_DIF)
	{
	    if(g_devAlmBits.watGrpAlm.bLinUBits == true)
	    {
			SetAlmItem(g_devAlmBits.watGrpAlm.bLinUBits,\
					   L_T_ALM_ITEM_WAT_LIN_UP,WAT_DEV_BAS_ID,0x00,\
					   g_pourTstData.tstData.unWatLine,0);
			g_devAlmBits.watGrpAlm.bLinUBits = 0;
	    }
	}
}
void CWorkThread::CheckBatteryAlm(void)
{
	//电量低
	UINT8 unAlmVal = 0;
	UINT16 unTmpVal = 0;
	unAlmVal = m_procPour.GetBatterySoc();
	if(unAlmVal <= 20)
	{
	    if(g_devAlmBits.BatAlm.bBatSocBits == false)
	    {
			SetAlmItem(g_devAlmBits.BatAlm.bBatSocBits,\
					 H_T_ALM_ITEM_BAT_VOL_DN,BAT_DEV_BAS_ID,0x00,\
					 unAlmVal,1);
			g_devAlmBits.BatAlm.bBatSocBits = true;
	    }
	}
	else if(unAlmVal > 20)
	{
	    if(g_devAlmBits.BatAlm.bBatSocBits == true)
	    {
			SetAlmItem(g_devAlmBits.BatAlm.bBatSocBits,\
					 H_T_ALM_ITEM_BAT_VOL_DN,BAT_DEV_BAS_ID,0x00,\
					 unAlmVal,0);
			g_devAlmBits.BatAlm.bBatSocBits = false;
	    }
	}
	//过温
	unTmpVal = m_procPour.GetBatteryTmp();
	unAlmVal = m_procPour.GetBatteryLos();
    UINT16 unBatTmpAlm = 0;
	if(unAlmVal == 1)
	{
		unBatTmpAlm = 550;
	}
	else
	{
	    unBatTmpAlm = 450;
	}
	if(unTmpVal >= unBatTmpAlm)//55°
	{
	    if(g_devAlmBits.BatAlm.bBatTmpBits == false)
	    {
			SetAlmItem(g_devAlmBits.BatAlm.bBatTmpBits,\
					 M_T_ALM_ITEM_BAT_TMP_UP,BAT_DEV_BAS_ID,0x00,\
					 unTmpVal,1);
			g_devAlmBits.BatAlm.bBatTmpBits = true;
	    }
	}
	else if(unTmpVal < (unBatTmpAlm-10))
	{
	    if(g_devAlmBits.BatAlm.bBatTmpBits == true)
	    {
			SetAlmItem(g_devAlmBits.BatAlm.bBatTmpBits,\
					 M_T_ALM_ITEM_BAT_TMP_UP,BAT_DEV_BAS_ID,0x00,\
					 unTmpVal,0);
			g_devAlmBits.BatAlm.bBatTmpBits = false;
	    }
	}
	//电池放电
	if(unAlmVal == 1)
	{
	    if(g_devAlmBits.BatAlm.bACLosBits == false)
	    {
			SetAlmItem(g_devAlmBits.BatAlm.bACLosBits,\
					 M_T_ALM_ITEM_AC_LOS,BAT_DEV_BAS_ID,0x00,\
					 unAlmVal,1);
			g_devAlmBits.BatAlm.bBatSocBits = true;
	    }
	}
	else if(unAlmVal == 0)
	{
	    if(g_devAlmBits.BatAlm.bACLosBits == true)
	    {
			SetAlmItem(g_devAlmBits.BatAlm.bACLosBits,\
					 M_T_ALM_ITEM_AC_LOS,BAT_DEV_BAS_ID,0x00,\
					 unAlmVal,0);
			g_devAlmBits.BatAlm.bACLosBits = false;
	    }
	}
}

void CWorkThread::ProcAlmInfo(void)
{
    UINT8 unIndex;
	/**/
    if(false==g_devConfigInfo.basicCfgInfo.unAlmEnFlag)
    {
        return;
    }
    if(m_unAlmDlySec)
    {
        //延迟时间未到
        return;
    }

    bool bAlmFlag = false;
	UINT8 unSenState = 0;
	//动脉泵
    CheckArteryAlm();
	CheckVeinAlm();
	CheckWaterAlm();
	
/*
	//水浴---血位
	UINT8 unBloodSta = m_procPour.GetWatBloodState();
	if(unBloodSta >= \
	   g_devConfigInfo.devAlmParam.unAlmBloodLin)
	{
	   SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bBloodBit,\
				  ALM_ITEM_BLOOD_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
				  unBloodSta,1);
	   
	   SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bBloodBit,\
				  ALM_ITEM_BLOOD_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
				  unBloodSta,1);
	   g_devAlmBits.watGrpAlm[unIndex].bBloodBit = 1;
	   bAlmFlag = true;
	}
	//else if(DifVal(unBloodSta,\
				  //g_devConfigInfo.devAlmParam.unAlmBloodLin)>MAX_ALM_BLOOD_LIN_DIF)
	else if(unBloodSta == 0)
	{
	   SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bBloodBit,\
				  ALM_ITEM_BLOOD_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
				  unBloodSta,0);
	   
	   SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bBloodBit,\
				  ALM_ITEM_BLOOD_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
				  unBloodSta,0);
	   g_devAlmBits.watGrpAlm[unIndex].bBloodBit = 0;
	}
*/
}

bool CWorkThread::SetAlmItem(UINT8 unPreAlmFlag,UINT8 unAlmID,UINT8 unAlmObjID,
                                 UINT8 unAlmSubObjID,INT32 unAlmVal,UINT8 unAlmFlag)
{
    if(m_unAlmDlySec)
    {
        //延迟时间未到
        return false;
    }
    if(false==g_devConfigInfo.basicCfgInfo.unAlmEnFlag)
    {
        return false;
    }
    if(unAlmFlag!=unPreAlmFlag)
    {
        QString strErr;
        AlmItemEx almItemEx;
        //printf("AlmID:%u AlmObjID:%u AlmSubObj:%u Val:%lu\r\n",unAlmID,unAlmObjID,unAlmSubObjID,unAlmVal,unAlmFlag);
        GetDateTime(&(almItemEx.almItem.dtCreate)); //产生告警时间
        almItemEx.almItem.unAlmID = unAlmID;
        almItemEx.almItem.unAlmObjID = unAlmObjID;
        almItemEx.almItem.unAlmSubObjID = unAlmSubObjID;
        almItemEx.almItem.unAlmFlag = unAlmFlag;
        almItemEx.almItem.unAlmVal = unAlmVal;
        almItemEx.unUpdFlag = 0;
        g_pAlmFile->WriteAlmData(&almItemEx,1);

        //更新设备当前告警时间
        memcpy(&g_devAlmBits.dtCreate,&almItemEx.almItem.dtCreate,sizeof(g_devAlmBits.dtCreate));
        return true;
    }
    return false;
}

bool CWorkThread::SetWindowShowAlm(UINT8 unPreAlmFlag,UINT8 unAlmID,UINT8 unAlmObjID,
								         UINT8 unAlmSubObjID,INT32 unAlmVal,UINT8 unAlmFlag)
{
	if(unAlmFlag!=unPreAlmFlag)
	{
	    if(unAlmID == ALM_ITEM_WAT_TMP_UP && g_almItemEx.unUpdFlag == 1)
	    {
	        g_almItemEx.unUpdFlag = unAlmFlag;
	    }
		
		if(g_almItemEx.almItem.unAlmID == ALM_ITEM_WAT_TMP_UP &&\
		   g_almItemEx.unUpdFlag == 1)
		{
		    return false;
		}
		else
		{
			QString strErr;
			AlmItemEx almItemEx;
			//printf("AlmID:%u AlmObjID:%u AlmSubObj:%u Val:%lu\r\n",unAlmID,unAlmObjID,unAlmSubObjID,unAlmVal,unAlmFlag);
			GetDateTime(&(almItemEx.almItem.dtCreate)); //产生告警时间
			almItemEx.almItem.unAlmID = unAlmID;
			almItemEx.almItem.unAlmObjID = unAlmObjID;
			almItemEx.almItem.unAlmSubObjID = unAlmSubObjID;
			almItemEx.almItem.unAlmFlag = unAlmFlag;
			almItemEx.almItem.unAlmVal = unAlmVal;
			almItemEx.unUpdFlag = unAlmFlag;
			
			memcpy(&g_almItemEx,&almItemEx,sizeof(AlmItemEx));
			if(g_almItemEx.unUpdFlag == 0)
			{
			    //g_almItemEx.almItem.unAlmID = 0;
			}
			printf("22-g_almItemEx.unUpdFlag :%u \r\n",g_almItemEx.unUpdFlag);
			return true;
		}
	}
	return false;
}


UINT32 CWorkThread::DifVal(UINT32 unVal0,UINT32 unVal1)
{
    return abs(unVal0-unVal1);
}
void CWorkThread::OnMsTimer(UINT32 unMsCount)
{
    if(m_unMsTimer)
    {
        if(m_unMsTimer>=unMsCount)
        {
            m_unMsTimer -= unMsCount;
        }
        else
        {
            m_unMsTimer = 0;
        }
    }
    else
    {
        m_unMsTimer = 1000;

        if(m_unAlmDlySec)
        {
            m_unAlmDlySec--;
        }

		for(UINT8 i = 0; i < 2; i++)
		{
			if(m_bBpRunFlag[i] == true)
			{
			    if(m_unAlmFlowDlySec[i] <= 5)
			    {
			        m_unAlmFlowDlySec[i]++;
			    }
			}
			else
			{
			    m_unAlmFlowDlySec[i] = 0;
			}
		}
		
		if(m_unMonDlySec)
		{
			m_unMonDlySec--;
		}
		if(m_bMcuUpEn == true)
		{
		    m_bGetUpInfoFlg = true;
		}
    }
}



UINT32 CWorkThread::GetDevData(UINT8      untype, UINT8 unIndex, BYTE* pDataBuf,UINT32 unBufSize)
{
    UINT32 unReturn = 0;
    memset(pDataBuf,0,unBufSize);

    if(untype == DEV_APUMP_TYPE || untype == DEV_VPUMP_TYPE)
    {
		unReturn = m_procPour.GetPumpData(untype,unIndex,pDataBuf,unBufSize);
    }
    else if(untype == DEV_WAT_TYPE)
    {
		unReturn = m_procPour.GetWatRoomData(unIndex,pDataBuf,unBufSize);
    }
	else if(untype == DEV_BAT_TYPE)
	{
	    m_procPour.GetBatBascData(unIndex,pDataBuf,unBufSize);
	}

    return unReturn;
}

bool CWorkThread::GetBatLinkState(void)
{
    return m_procPour.GetBatLink();
}
void CWorkThread::GetAllMcuVer(UINT8* pDataBuf)
{
	m_procPour.GetMucVerInfo(pDataBuf);
}


//蜂鸣器控制开关
void CWorkThread::CtrlBeep(UINT8 unCtrl)
{
/*
	if(unCtrl == DEV_ON)//开蜂鸣器
	{
		SystemEx("echo 1 > /sys/class/gpio/gpio72/value");
	}
	else if(unCtrl == DEV_OFF)//关蜂鸣器
	{
		SystemEx("echo 0 > /sys/class/gpio/gpio72/value");
	}
*/
	QString strPathName = QString("echo %1 > /sys/class/gpio/gpio72/value").arg(unCtrl);
	SystemEx(strPathName.toStdString().c_str());
}


//监控日志
//存储文件信息
bool CWorkThread::ReadMonDataInfo(QString pFileName)
{
    bool bReturn = true;

    m_fdMonInfoFle = open(pFileName.toStdString().c_str() ,O_RDWR|O_CREAT,0666);
    if(m_fdMonInfoFle == -1)
    {
        m_strErrorInfo =QString("打开文件:<%1>失败,\r\n错误原因--<%2>\r\n").arg(pFileName)\
                .arg(strerror(errno));

        return false;
    }
    lseek(m_fdMonInfoFle,0L,SEEK_SET);
    read(m_fdMonInfoFle,(char*)&(g_MonSaveInfo),sizeof(MonSaveInfo));
    return bReturn;
}

void CWorkThread::OpenMonDataInfo(void)
{
    QString saveStrPathName;
	saveStrPathName  = qApp->applicationDirPath() + "/MonLog";
	//saveStrPathName += g_devConfigInfo.basicCfgInfo.strLogPath;
	saveStrPathName += SAVE_FILE_INFO_NAME;
	ReadMonDataInfo(saveStrPathName);

	//printf("saveStrPathName:%s \r\n",saveStrPathName.toStdString().c_str());
	//printf("-m_fdMonInfoFle:%d-----------get MonNum:%d unMonCurrPar:%d \r\n",m_fdMonInfoFle,g_MonSaveInfo.unMonDataNum,g_MonSaveInfo.unMonCurrPar);
}

bool CWorkThread::SaveMonDataInfo(void)
{
    if(-1==m_fdMonInfoFle)
    {
        return false;
    }
    //printf("Save TestData...\r\n");
    lseek(m_fdMonInfoFle,0L,SEEK_SET);
    write(m_fdMonInfoFle,(const char*)&(g_MonSaveInfo),sizeof(MonSaveInfo));

    fsync(m_fdMonInfoFle);

	
	//printf("Save-m_fdMonInfoFle:%d-----------get MonNum:%d unMonCurrPar:%d \r\n",m_fdMonInfoFle,g_MonSaveInfo.unMonDataNum,g_MonSaveInfo.unMonCurrPar);
    return true;
}

void CWorkThread::OpenMonDataFile(void)
{
    printf("open =========MonFile \r\n");
    QString filePathName;

//	UINT32 unTestDataLen;
	
	filePathName  = qApp->applicationDirPath() + "/MonLog";
	filePathName += SAVE_MON_DATA_NAME;

	QFile qFile(filePathName);
	qFile.open(QIODevice::ReadOnly);
	QDataStream readStream(&qFile);

	long   lTestDataSize;
	ulong  lItemIndex;
	lItemIndex = 0;

	while(!readStream.atEnd()&&lItemIndex<g_MonSaveInfo.unMonDataNum)
	{
		lTestDataSize = sizeof(PourData);
		readStream.readRawData((char*)&g_DataTests[lItemIndex],lTestDataSize);
		lItemIndex++;
	}
}

void CWorkThread::ProcMonInfo(void)
{
    if(m_unMonDlySec)
    {
        //延迟时间未到
        return;
    }
	
    UINT32 unDataPos;
    UINT32 unTestDataLen;
//	UINT32 unIndex;
	PourData  testDataMon;

    unTestDataLen = sizeof(PourData);
	memcpy(&testDataMon,&g_pourTstData.tstData,unTestDataLen);
    GetDateTime(&testDataMon.dtSample);
	//更新显示数据
	memcpy(&g_DataTests[g_MonSaveInfo.unMonCurrPar],&testDataMon,unTestDataLen);
	
	if(m_fdMonData == -1)
	{
		  QString filePathName;
		  filePathName	= qApp->applicationDirPath() + "/MonLog";
		  filePathName += SAVE_MON_DATA_NAME;
		  //printf("===mon=======%s	\r\n",filePathName.toStdString().c_str());
		  if(-1==(m_fdMonData=open(filePathName.toStdString().c_str(),O_WRONLY|O_CREAT,0666)))
		  {
			  m_strErrorInfo =QString("打开文件:<%1>失败,\r\n错误原因--<%2>\r\n").arg(filePathName)\
					  .arg(strerror(errno));
			  return;
		  }
	}

    if(-1==m_fdMonData)
    {
        return;
    }
	
    unDataPos  = g_MonSaveInfo.unMonCurrPar;
    unDataPos *= unTestDataLen;
    if(unDataPos != (UINT32)lseek(m_fdMonData,unDataPos,SEEK_SET))
    {
        printf("LSEEK Func Error DatwaPos:%lu\r\n",unDataPos);
    }
    if(unTestDataLen!=(UINT32)write(m_fdMonData,(const char*)&(testDataMon),unTestDataLen))
    {
        printf("WriteFile Error DataPos:%lu\r\n",unDataPos);
    }
    else
    {
        fsync(m_fdMonData);
    }

	m_unMonDlySec = g_devConfigInfo.basicCfgInfo.unMonSavTmt;
	if(g_MonSaveInfo.unMonCurrPar >= SAVE_MON_LOG_NUM)
	{
	    g_MonSaveInfo.unMonCurrPar = 0;
	}
	else
	{
	    g_MonSaveInfo.unMonCurrPar++;
	}
	
	if(g_MonSaveInfo.unMonDataNum < SAVE_MON_LOG_NUM)
	{
	    g_MonSaveInfo.unMonDataNum++;
	}

	SaveMonDataInfo();

	if(m_bOpenMonFile == false)
	{
		m_bOpenMonFile = true;
		OpenMonDataFile();
	}
}

//==================================远程升级===============================
/*
void CWorkThread::SetSysUpd(bool bUpdFlag)
{
    m_bUpdateFlag = bUpdFlag;
	m_pUdpModule->m_bTimeOutTimer = 0;
}
*/
void CWorkThread::ProMcuUpTask(void)
{
    if(false == m_bMcuUpEn)
    {
        return;
    }
	if(m_unMcuUpState == 0xFF)
	{
		memset(&m_pMcuUpInfo,0,sizeof(m_pMcuUpInfo));
		m_unMcuUpState = CheckUpdateFileType(m_unMcuType);
		m_pMcuUpInfo.unMcuUpdState = m_unMcuUpState;
		if(m_unMcuUpState > 0)
		{
		    m_bMcuUpEn = false;
			m_unMcuUpState = 0xFF;
		}
		//m_pMcuUpInfo.unTotalPkg = 30;//测试打开
	}
	if(m_bGetUpInfoFlg == true)
	{
	    m_bGetUpInfoFlg = false;
        if(DEV_APUMP_TYPE == m_unMcuType)
        { 
            m_lckUpStat.lock();
            CSwitPump *pSwitPump;
			pSwitPump = m_listAPumMods.at(0);
			pSwitPump->GetDevUpdateInfo(&m_pMcuUpInfo);//测试屏蔽
			m_lckUpStat.unlock();
        }
        else if(DEV_WAT_TYPE == m_unMcuType)
        {
            m_lckUpStat.lock();
            CSwitWater *pSwitWater;
			pSwitWater = m_listWatMods.at(0);
			pSwitWater->GetDevUpdateInfo(&m_pMcuUpInfo);
			m_lckUpStat.unlock();
        }
        else if(DEV_VPUMP_TYPE == m_unMcuType)
        {
            m_lckUpStat.lock();
            CSwitPump *pSwitPump;
			pSwitPump = m_listVPumMods.at(0);
			pSwitPump->GetDevUpdateInfo(&m_pMcuUpInfo);//测试屏蔽
			m_lckUpStat.unlock();
        }

		if(m_pMcuUpInfo.unMcuUpdState >= UpdSuccess)
		{
		    m_bMcuUpEn = false;
			m_unMcuUpState = 0xFF;
		}
	}
}

McuUpdateInfo CWorkThread::GetDevUpdateInfo(void)//(McuUpdateInfo *mcuUpInfo)
{
	//memcpy(mcuUpInfo,&m_pMcuUpInfo,sizeof(m_pMcuUpInfo));
	//mcuUpInfo->unMcuUpdState = m_pMcuUpInfo.unMcuUpdState;
	//mcuUpInfo->unPkgIndex = m_pMcuUpInfo.unPkgIndex;
	//mcuUpInfo->unTotalPkg = m_pMcuUpInfo.unTotalPkg;
	return m_pMcuUpInfo;
}
void CWorkThread::SetUpdateMcu(UINT8 unType)
{	
    m_unMcuType = unType;
	m_bMcuUpEn = true;
}
void CWorkThread::SetUpdateMcuFail(void)
{	
	memset(&m_pMcuUpInfo,0,sizeof(McuUpdateInfo));
	m_bMcuUpEn = false;
	m_unMcuUpState = 0xFF;
}


UINT8 CWorkThread::CheckUpdateFileType(UINT8 unType)
{
    UINT8 unStm32Ret,unPicRet,unRet;
    char updatePath[128] = {0x00};
    char TypefromFileName[32] = {0x00}; //从文件名获取到的devType
    char VerfromFileName[64] = {0x00};  //从文件名获取到的VER
    QString strMcuOldFile = "";
	QString strPath;
	QString strRmPath;
	QString strMkdir;
	char strCpFile[256] = {0x00};

    memset(updatePath,0,sizeof(updatePath));
    memset(TypefromFileName,0,sizeof(TypefromFileName));
    memset(VerfromFileName,0,sizeof(VerfromFileName));
	memset(strCpFile,0,sizeof(strCpFile));
	
    unPicRet = FindMCUSoftwareFile(updatePath, TypefromFileName, VerfromFileName,unType);

    if(unPicRet != 0) //没有找到文件
    {
        printf("Not found the MCU software file for pic Device! unPicRet :%d\r\n" ,unPicRet);
		return UpdFindFileErr;
    }
	else
	{
	    printf("Get MCU File Path is [%s]\r\n", updatePath);
        int nItem = 0;
        if(DEV_APUMP_TYPE == unType)
        {
            CSwitPump *pSwitPump;
			while(nItem < m_listAPumMods.count())
			{
				pSwitPump = m_listAPumMods.at(nItem);
				pSwitPump->SetDevUpdate(updatePath);
				nItem++;
			}
        }
        else if(DEV_WAT_TYPE == unType)
        {
            CSwitWater *pSwitWater;
			while(nItem < m_listWatMods.count())
			{
				pSwitWater = m_listWatMods.at(nItem);
				pSwitWater->SetDevUpdate(updatePath);
				nItem++;
			}
        }
        else if(DEV_VPUMP_TYPE == unType)
        {
            CSwitPump *pSwitPump;
			while(nItem < m_listVPumMods.count())
			{
				pSwitPump = m_listVPumMods.at(nItem);
				pSwitPump->SetDevUpdate(updatePath);
				nItem++;
			}
        }
	}

	return 0;
}


