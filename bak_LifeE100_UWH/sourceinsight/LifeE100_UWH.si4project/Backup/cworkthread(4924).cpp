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

    m_bQuitFlag     = false;
    m_bInitFlag     = false;
    m_bBpRunFlag[0]   = false;
	m_bBpRunFlag[1]   = false;
    m_unMsTimer     = 0;
    m_unAlmDlySec = 5;//600;
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
    }
}

void CWorkThread::AddCmmObject(CSocket* pCmmSkt)
{
    m_listCmmSkts.append(pCmmSkt);
    pCmmSkt->SetWorkThread(this);
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
	
    if(USR_BP_CMD_STRT == unUserCmdID)
    {
        operLogCtl.unOperType[0] = 0;
		operLogCtl.unOperType[1] = 1;
			
		SetDevPrm setDevPrm;
		setDevPrm.unIndex = unIndex;
		setDevPrm.unPrmVald = unPrmVald;
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
	//printf("PrmIndex:%u PrmVald:%u\r\n",setDevPrm.unIndex,setDevPrm.unPrmVald);
	pSwitPum->SetEnable(g_devConfigInfo.arteryParm.unEnFlag);
	pSwitPum->SetDevParam(&setDevPrm);
	if(true==pSwitPum->IsEnabled())
	{
		m_procPour.AddAPumMod(pSwitPum);
	}
	else
	{
		m_procPour.RmvAPumMod(pSwitPum);
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
    }
    if(true == g_devUpdFlags.bVeinFlag)//处理静脉血泵参数更新
    {
		SetVeinParam();
    }
    if(true == g_devUpdFlags.bWtrRoomFlag)//水浴参数更新
    {
        SetDevPrm setDevPrm;
        CSwitWater* pWatMod;
        g_devUpdFlags.bWtrRoomFlag = false;

        //考虑多个设备ID
		setDevPrm.unPrmVald = g_devConfigInfo.watRooParam.unTmpVal;
		setDevPrm.unIndex = m_unWaterPrmIndex;
        //for(lIndex= 0; lIndex < m_listWatMods.size(); lIndex++)
        //{
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
			}
        //}
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
	#if RUN_ARM_LINUX
    if(false==pUartSkt->OpenDev("/dev/ttyAMA1",115200))
	#else
	if(false==pUartSkt->OpenDev("/dev/ttyUSB0",115200))
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
    }

	//串口对应板子---p1
    pUartSkt = new CUARTSocket(m_pSktHandler);
#if RUN_ARM_LINUX
    if(false==pUartSkt->OpenDev("/dev/ttyAMA2",115200))
#else
	if(false==pUartSkt->OpenDev("/dev/ttyUSB1",115200))
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
	if(false==pUartSkt->OpenDev((char*)"/dev/ttyUSB2",115200))
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
		printf("open com2 -----------------------\r\n");
    }
	CreateArteryMods();//动脉对应设备
	CreateWaterMods();//水箱对应设备
	CreateVeinMods();//静脉对应设备
	m_procPour.SetWorkThread(this);
}

void CWorkThread::CreateArteryMods(void)
{
    UINT8 lIndex;
	/**/
    CSwitPump* pSwitPum;
    for(lIndex = 0; lIndex<g_devConfigInfo.basicCfgInfo.unAPumCount; lIndex++)
    {
        pSwitPum = new CSwitPump();//
        pSwitPum->SetDevID(g_devConfigInfo.arteryParm.unDevID);
		pSwitPum->SetSndID(MAIN_DEV_BAS_ID);
        pSwitPum->SetUARTSocket(m_pUARTSkt0);
        pSwitPum->SetWorkThread(this);
        pSwitPum->SetEnable(false);
        m_pDevCmdHander->AddSubDevice(pSwitPum);
        m_listAPumMods.append(pSwitPum);

		printf("-----------------------------CSwitPump:%d -------\r\n",lIndex);
    }
}

void CWorkThread::CreateVeinMods(void)
{
    UINT8 lIndex;
    CSwitPump* pSwitPum;
    for(lIndex = 0; lIndex<g_devConfigInfo.basicCfgInfo.unVPumCount; lIndex++)
    {
        pSwitPum = new CSwitPump();//
        pSwitPum->SetDevID(g_devConfigInfo.veinParm.unDevID);
		pSwitPum->SetSndID(MAIN_DEV_BAS_ID);
        pSwitPum->SetUARTSocket(m_pUARTSkt2);
        pSwitPum->SetWorkThread(this);
        pSwitPum->SetEnable(false);
        m_pDevCmdHander->AddSubDevice(pSwitPum);
        m_listVPumMods.append(pSwitPum);
    }
}

void CWorkThread::CreateWaterMods(void)
{
    UINT8 lIndex;
    CSwitWater* pSwitWat;
    for(lIndex = 0; lIndex<g_devConfigInfo.basicCfgInfo.unWatCount; lIndex++)
    {
        pSwitWat = new CSwitWater();//
        pSwitWat->SetDevID(g_devConfigInfo.watRooParam.unDevID);
		pSwitWat->SetSndID(MAIN_DEV_BAS_ID);
        pSwitWat->SetUARTSocket(m_pUARTSkt1);
        pSwitWat->SetWorkThread(this);
        pSwitWat->SetEnable(false);
        m_pDevCmdHander->AddSubDevice(pSwitWat);
        m_listWatMods.append(pSwitWat);
    }

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


void CWorkThread::setOpenWatRoom(UINT8 unIndex, UINT8 unOpenFlg)
{
    CSwitWater* pWatMod;

	pWatMod = m_listWatMods.at(unIndex);

    OperLogCtl operLogCtl;

	operLogCtl.unType = OPER_CTRL_TYPE_WAT;
	operLogCtl.unSite = 0;
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
    else if(unItemIndex==CFG_ALM_PRM_ITEM)
    {
    	g_devUpdFlags.bAlmSetFlag = true;
        g_pCfgDataUI->GetGrpData(unItemIndex,\
                                 unDataLen,\
                                 (BYTE*)&g_devConfigInfo.devAlmParam);
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

void CWorkThread::ProcAlmInfo(void)
{
    UINT8 unIndex;
	/*
    if(false==g_devConfigInfo.basicCfgInfo.unAlmEnFlag||\
	   PRE_POUR == m_unDataType[])
    {
        return;
    }*/
    if(m_unAlmDlySec)
    {
        //延迟时间未到
        return;
    }

    bool bAlmFlag = false;
	//动脉泵
    for(unIndex = 0; unIndex < g_devConfigInfo.basicCfgInfo.unAPumCount; unIndex++)
    {
        //泵压力高
        if((g_pourTstData.tstData.unAPrssVal >= \
            g_devConfigInfo.devAlmParam.unAlmUPresA)&&\
            g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits == false)
        {
            if(m_bBpRunFlag[0] == true)
            {
	            SetAlmItem(g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits,\
	                       ALM_ITEM_A_PRE_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
	                       g_pourTstData.tstData.unAPrssVal,1);
				
                g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
					
	            SetWindowShowAlm(g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits,\
	                       ALM_ITEM_A_PRE_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
	                       g_pourTstData.tstData.unAPrssVal,1);
				g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits = 1;
	            bAlmFlag = true;
            }

			//printf("sss-------unAPrssVal:%d ---unAlmUPresA:%d \r\n",g_pourTstData.tstData.unAPrssVal,g_devConfigInfo.devAlmParam.unAlmUPresA);
        }
        else if(((g_devConfigInfo.devAlmParam.unAlmUPresA - \
                  g_pourTstData.tstData.unAPrssVal)>MAX_ALM_PRES_DIF)&&\
                  g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits == true)
        {
            SetAlmItem(g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits,\
                       ALM_ITEM_A_PRE_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unAPrssVal,0);
            g_DataAlarm.unAPrssVal = g_pourTstData.tstData.unAPrssVal;
			
            SetWindowShowAlm(g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits,\
                       ALM_ITEM_A_PRE_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unAPrssVal,0);	
			g_devAlmBits.ApumGrpAlm[unIndex].bPressUBits = 0;
			//printf("eee-------unAPrssVal:%d ---unAlmUPresA:%d \r\n",g_pourTstData.tstData.unAPrssVal,g_devConfigInfo.devAlmParam.unAlmUPresA);
        }
        //泵压流量高
        if((g_pourTstData.tstData.unAFlowVal >= \
            g_devConfigInfo.devAlmParam.unAlmUFlowA)&&\
            g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits == false)
        {
            if(m_bBpRunFlag[0] == true)
            {
	            SetAlmItem(g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits,\
	                       ALM_ITEM_A_FLO_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
	                       g_pourTstData.tstData.unAFlowVal,1);
				g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;

				SetWindowShowAlm(g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits,\
	                       ALM_ITEM_A_FLO_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
	                       g_pourTstData.tstData.unAFlowVal,1);
				g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits = 1;
	            bAlmFlag = true;
            }
        }
        else if(((g_devConfigInfo.devAlmParam.unAlmUFlowA - \
                  g_pourTstData.tstData.unAFlowVal)>MAX_ALM_FLOW_DIF)&&\
                  g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits == true)
        {
            SetAlmItem(g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits,\
                       ALM_ITEM_A_FLO_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unAFlowVal,0);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
			
			SetWindowShowAlm(g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits,\
                       ALM_ITEM_A_FLO_UP,unIndex+APUM_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unAFlowVal,0);
            g_devAlmBits.ApumGrpAlm[unIndex].bFlowUBits = 0;
        }
        //泵压流量低
        if((g_pourTstData.tstData.unAFlowVal < \
            g_devConfigInfo.devAlmParam.unAlmLFlowA)&&\
            g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits == false)
        {
            //流量告警 泵开，等待5秒
            if(m_bBpRunFlag[0] == true && m_unAlmFlowDlySec[0] > 5)
            {
	            SetAlmItem(g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits,\
	                       ALM_ITEM_A_FLO_DN,unIndex+APUM_DEV_BAS_ID,0x00,\
	                       g_pourTstData.tstData.unAFlowVal,1);
				g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;

				SetWindowShowAlm(g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits,\
	                       ALM_ITEM_A_FLO_DN,unIndex+APUM_DEV_BAS_ID,0x00,\
	                       g_pourTstData.tstData.unAFlowVal,1);
				g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits = 1;
	            bAlmFlag = true;
            }
        }
        else if(((g_pourTstData.tstData.unAFlowVal - \
                  g_devConfigInfo.devAlmParam.unAlmLFlowA)>MAX_ALM_FLOW_DIF)&&\
                  g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits == true)
        {
            SetAlmItem(g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits,\
                       ALM_ITEM_A_FLO_DN,unIndex+APUM_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unAFlowVal,0);
			g_DataAlarm.unAFlowVal = g_pourTstData.tstData.unAFlowVal;
            
			SetWindowShowAlm(g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits,\
                       ALM_ITEM_A_FLO_DN,unIndex+APUM_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unAFlowVal,0);

			g_devAlmBits.ApumGrpAlm[unIndex].bFlowLBits = 0;
        }				

    }
	
	//水浴---温度
    for(unIndex = 0; unIndex < g_devConfigInfo.basicCfgInfo.unWatCount; unIndex++)
    {
        if((g_pourTstData.tstData.unWatTmpVal >= \
            g_devConfigInfo.devAlmParam.unAlmUWatTmp)&&\
            g_devAlmBits.watGrpAlm[unIndex].bTmpUBits == false)
        {
            SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bTmpUBits,\
                       ALM_ITEM_WAT_TMP_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unWatTmpVal,1);
            g_DataAlarm.unWatTmpVal = g_pourTstData.tstData.unWatTmpVal;

			SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bTmpUBits,\
                       ALM_ITEM_WAT_TMP_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unWatTmpVal,1);
			g_devAlmBits.watGrpAlm[unIndex].bTmpUBits = 1;
            bAlmFlag = true;
        }
        else if(((g_devConfigInfo.devAlmParam.unAlmUWatTmp - \
			     g_pourTstData.tstData.unWatTmpVal)>MAX_ALM_WAT_TMP_DIF)&&\
			     g_devAlmBits.watGrpAlm[unIndex].bTmpUBits == true)
        {
            SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bTmpUBits,\
                       ALM_ITEM_WAT_TMP_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unWatTmpVal,0);
			g_DataAlarm.unWatTmpVal = g_pourTstData.tstData.unWatTmpVal;
			
			SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bTmpUBits,\
                       ALM_ITEM_WAT_TMP_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
                       g_pourTstData.tstData.unWatTmpVal,0);
            g_devAlmBits.watGrpAlm[unIndex].bTmpUBits = 0;
        }

        //水浴---水位高
		if((g_pourTstData.tstData.unWatLine >= \
			g_devConfigInfo.devAlmParam.unAlmUWatLin) &&\
			g_devAlmBits.watGrpAlm[unIndex].bLinUBits == false)
	   {
		   SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bLinUBits,\
					  ALM_ITEM_WAT_LIN_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
					  g_pourTstData.tstData.unWatLine,1);
		   g_DataAlarm.unWatLine = g_pourTstData.tstData.unWatLine;
		   
		   SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bLinUBits,\
					  ALM_ITEM_WAT_LIN_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
					  g_pourTstData.tstData.unWatLine,1);
		   g_devAlmBits.watGrpAlm[unIndex].bLinUBits = 1;
		   bAlmFlag = true;
	   }
	   else if(((g_devConfigInfo.devAlmParam.unAlmUWatLin - \
	   	         g_pourTstData.tstData.unWatLine)>=MAX_ALM_WAT_LIN_DIF)&&\
	   	         g_devAlmBits.watGrpAlm[unIndex].bLinUBits == true)
	   {
		   SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bLinUBits,\
					  ALM_ITEM_WAT_LIN_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
					  g_pourTstData.tstData.unWatLine,0);
		   
		   g_DataAlarm.unWatLine = g_pourTstData.tstData.unWatLine;
		   SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bLinUBits,\
					  ALM_ITEM_WAT_LIN_UP,unIndex+WAT_DEV_BAS_ID,0x00,\
					  g_pourTstData.tstData.unWatLine,0);
		   g_devAlmBits.watGrpAlm[unIndex].bLinUBits = 0;
		}
	   //水浴---水位低
	   /**/
	   if((g_devConfigInfo.devAlmParam.unAlmLWatLin > \
	   	   g_pourTstData.tstData.unWatLine) &&\
	   	   g_devAlmBits.watGrpAlm[unIndex].bLinLBits == false)
	  {
		  SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bLinLBits,\
					 ALM_ITEM_WAT_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unWatLine,1);
		  g_DataAlarm.unWatLine = g_pourTstData.tstData.unWatLine;

		  SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bLinLBits,\
					 ALM_ITEM_WAT_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
					 g_DataAlarm.unWatLine,1);
		  g_devAlmBits.watGrpAlm[unIndex].bLinLBits = 1;
		  bAlmFlag = true;
	  }
	  else if(((g_pourTstData.tstData.unWatLine - \
	  	        g_devConfigInfo.devAlmParam.unAlmLWatLin)>=MAX_ALM_WAT_LIN_DIF)&&\
	  	        g_devAlmBits.watGrpAlm[unIndex].bLinLBits == true)
	  {
		  SetAlmItem(g_devAlmBits.watGrpAlm[unIndex].bLinLBits,\
					 ALM_ITEM_WAT_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
					 g_DataAlarm.unWatLine,0);
		  g_DataAlarm.unWatLine = g_pourTstData.tstData.unWatLine;
		  
		  SetWindowShowAlm(g_devAlmBits.watGrpAlm[unIndex].bLinLBits,\
					 ALM_ITEM_WAT_LIN_DN,unIndex+WAT_DEV_BAS_ID,0x00,\
					 g_pourTstData.tstData.unWatLine,0);
		  g_devAlmBits.watGrpAlm[unIndex].bLinLBits = 0;
	   }
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
    }
	//m_unAlmDlySec = 1;
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

    return unReturn;
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


