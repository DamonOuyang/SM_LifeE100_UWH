#include "includes.h"
#include "cpourdevices.h"
#include "cworkthread.h"
#include "CSwitPump.h"
#include "CSwitWater.h"


CPourDevices::CPourDevices()
{
    m_unUpdDataMs = 0;
    m_unStrDlyMs  = 0;
    m_unAlmDlyMs  = 1000L*30;

    memset(&m_pumDevData,0,sizeof(m_pumDevData));
    memset(&m_watDevData,0,sizeof(m_watDevData));
	memset(&m_unMcuStateInfo,0,sizeof(m_unMcuStateInfo));
}
CPourDevices::~CPourDevices()
{
    DeleteAllMods();
}

//添加动脉泵设备类进列表
void CPourDevices::AddAPumMod(CSwitPump* pPumModule)
{
    int nItem = 0;
    while(nItem < m_listAPumModules.size())
    {
        if(m_listAPumModules.at(nItem)==pPumModule)
        {
            return ;
        }
        nItem++;
    }
    m_listAPumModules.append(pPumModule);
}


//从列表将动脉泵设备类移除
void CPourDevices::RmvAPumMod(CSwitPump* pPumModule)
{
    int nItem = 0;
    while(nItem < m_listAPumModules.size())
    {
        if(m_listAPumModules.at(nItem)==pPumModule)
        {
            m_listAPumModules.removeAt(nItem);
            return;
        }
        nItem++;
    }
}

//添加静脉泵设备类进列表
void CPourDevices::AddVPumMod(CSwitPump* pPumModule)
{
    int nItem = 0;
    while(nItem < m_listVPumModules.size())
    {
        if(m_listVPumModules.at(nItem)==pPumModule)
        {
            return ;
        }
        nItem++;
    }
    m_listVPumModules.append(pPumModule);
}


//从列表将静脉泵设备类移除
void CPourDevices::RmvVPumMod(CSwitPump* pPumModule)
{
    int nItem = 0;
    while(nItem < m_listVPumModules.size())
    {
        if(m_listVPumModules.at(nItem)==pPumModule)
        {
            m_listVPumModules.removeAt(nItem);
            return;
        }
        nItem++;
    }
}


//添加水浴设备类进列表
void CPourDevices::AddWaterMod(CSwitWater* pWatModule)
{
    int nItem = 0;
    while(nItem < m_listWatModules.size())
    {
        if(m_listWatModules.at(nItem)==pWatModule)
        {
            return ;
        }
        nItem++;
    }
    m_listWatModules.append(pWatModule);
}

//从列表将水浴设备类移除
void CPourDevices::RmvWaterMod(CSwitWater* pWatModule)
{
    int nItem = 0;
    while(nItem < m_listWatModules.size())
    {
        if(m_listWatModules.at(nItem)==pWatModule)
        {
            m_listWatModules.removeAt(nItem);
            return;
        }
        nItem++;
    }
}


void CPourDevices::DeleteAllMods(void)
{
    int unIndex = 0;
    CSwitPump* pPumMod;
	CSwitWater* pWatMod;

	//动脉泵
    while(unIndex < m_listAPumModules.count())
    {
        pPumMod = m_listAPumModules.at(unIndex++);
        delete pPumMod;
    }
    m_listAPumModules.clear();
	
	//静脉泵
    while(unIndex < m_listVPumModules.count())
    {
        pPumMod = m_listVPumModules.at(unIndex++);
        delete pPumMod;
    }
    m_listVPumModules.clear();

    //水浴
    while(unIndex < m_listWatModules.count())
    {
        pWatMod = m_listWatModules.at(unIndex++);
        delete pWatMod;
    }
    m_listWatModules.clear();
}


bool CPourDevices::StartRun(UINT8 unIndex)
{
    if(true==m_bRunFlag)
    {
        m_strErrorInfo = "已经在启动中";
        return false;
    }
    if(0==m_listAPumModules.count())
    {
        m_strErrorInfo = "没有配置血泵控制模块";
        //m_unStopCode = STP_ERR_UNKOWN_ERR;
        return false;
    }

    OnUpdData(true);//更新实际数据

	if(false==SndPourDevRunCmd(DEV_APUMP_TYPE,unIndex,DEV_ON))
	{
		//m_unStopCode = STP_ERR_SND_SUB_CMD_ERR;
		return false;
	}

    if(false==CBasicPourProc::StartRun(unIndex))
    {
        return false;
    }
    m_unSaveSecs = m_unGetSaveSec;
    if(m_unSaveSecs >= 3600||0==m_unSaveSecs)
    {
        m_unSaveSecs = 60;
    }

    return true;
}

bool CPourDevices::StopRun(void)
{
    //int nItem = 0;
    QString strError = " ";
    //printf("StopDisCharge:%lu\r\n",m_unStopCode);
    //strError = StopCodeToString(m_unStopCode);
    if(NULL != m_pWorkThread)
    {
        m_pWorkThread->ShowStringInfo(strError.toStdString().c_str());
    }
    else
    {
        printf("StopErr:%lu\r\n",m_unStopCode);
    }
    SndPourDevRunCmd(DEV_APUMP_TYPE,0,DEV_OFF);
    CBasicPourProc::StopRun();
    m_unStrDlyMs = 1000L*60L*1L;//1分钟
    return true;
}

void CPourDevices::ProcPourTask(void)
{
    int nItem       = 0;
    bool bStopFlag  = false;
    CSwitPump* pPumMod;
    if(false == m_bRunFlag)
    {
        return;
    }
    if(g_pourTstData.tstInfo.unTotalTime <= 20)
    {
        return;
    }

    while(nItem<m_listAPumModules.count())
    {
        pPumMod = m_listAPumModules.at(nItem++);
        if(false == pPumMod->IsActive())
        {
            m_unStopCode = STP_ERR_DEV_TMT_ERR;
            bStopFlag = true;
        }
        else if(true==pPumMod->GetCmdConfirm(CTRL_DEV_RUN_SND))
        {
            if(false==pPumMod->IsRun())
            //if(0 == m_pumDevData.unRunFlg)
            {
                QString strClsName;
                pPumMod->GetClassName(strClsName);
                if("CSwitPump"==strClsName)
                {
                    m_unStopCode = STP_ERR_SUB_STP_ERR;//pPumMod->GetErrCode();
                }
                bStopFlag = true;
                printf("StopRun m_unStopCode: %x \r\n",m_unStopCode);
                break;
            }
        }
    }
	if(g_devAlmBits.watGrpAlm[0].bTmpUBits)
	{
	    m_unStopCode = STP_ERR_WAT_TMP_ERR;
	    bStopFlag = true;
	}
    if(true==bStopFlag)
    {
        printf("StopRun--------1\r\n");
        StopRun();
    }
}

void CPourDevices::ProcTask(void)
{
    //UINT32 unCurTmp = 0;
    //int nItem       = 0;
    if(false == m_bSecFlag)
    {
        return ;//每一秒钟执行一次
    }
    CBasicPourProc::ProcTask();

    ProcPourTask();
    OnUpdData(false);
}

void CPourDevices::OnMsTimer(UINT32 unMsCount)
{
    CBasicPourProc::OnMsTimer(unMsCount);
    m_unUpdDataMs  = DoMsTimer(m_unUpdDataMs,unMsCount);
    m_unStrDlyMs   = DoMsTimer(m_unStrDlyMs,unMsCount);
    m_unAlmDlyMs   = DoMsTimer(m_unAlmDlyMs,unMsCount);

    if(0==m_unAlmDlyMs)
    {
        m_unAlmDlyMs = 3000L;//３秒
        //SndAlmLedData();
    }
}

void CPourDevices::SetSavePrd(UINT32 unSaveSecs)
{
    //m_unSaveSecs = unSaveSecs;
    m_unGetSaveSec = unSaveSecs;
}

void CPourDevices::OnUpdData(bool bUpdFlag)
{
    //int   nItem;
    if(0!=m_unUpdDataMs&&false==bUpdFlag)
    {
        return;
    }
    //更新灌注信息
	//g_pourTstData.tstData.unDataType = 0;   //数据类型
	g_pourTstData.tstData.unASpeeSet = g_devConfigInfo.arteryParm.unSpeed;	//转速(RPM)设定值
	g_pourTstData.tstData.unAPrssSet = g_devConfigInfo.arteryParm.unPress;	//压力(mmHg)设定值
    //动脉
    g_pourTstData.tstData.unATmpVal  = m_pumDevData.unTmpVal;	//温度(℃)
    g_pourTstData.tstData.unAFlowVal = m_pumDevData.unFlowVal;	//流量(ml)
    g_pourTstData.tstData.unAPrssVal = m_pumDevData.unPrssVal;	//压力(mmHg)
    g_pourTstData.tstData.unASpeeVal = m_pumDevData.unSpeeVal;	//转速(RPM)
    //水浴
	g_pourTstData.tstData.unWatTmpSet = g_devConfigInfo.watRooParam.unTmpVal; //水浴温度设定值
	g_pourTstData.tstData.unWatTmpVal = m_watDevData.unTmpVal; //水浴值(℃)
	g_pourTstData.tstData.unWatLine   = m_watDevData.unWatLine;	//水位

    m_unUpdDataMs = MAX_UPD_DATA_MS;
}

void CPourDevices::StopPump(UINT8 unStopCode)
{
    m_unStopCode = unStopCode;
    StopRun();
}

void CPourDevices::GetStopErrorInfo(QString& strError)
{
    //strError = StopCodeToString(m_unStopCode);
}

bool CPourDevices::SndPourDevRunCmd(     UINT8 unPumType, UINT8 unIndex, UINT8 unCode)
{
    CSwitPump* pPumMod;
    //int nItem = 0;

    if(unPumType == DEV_APUMP_TYPE)
    {
    	pPumMod = m_listAPumModules.at(unIndex);
    }
    else if(unPumType == DEV_VPUMP_TYPE)
    {
    	pPumMod = m_listVPumModules.at(unIndex);
    }	
    if(false==pPumMod->CtrlDevRun(unCode))
    {
        m_strErrorInfo = QString("泵模块<%1>:<%2>命令发送失败!\r\n").arg(pPumMod->GetDevID()).arg(unCode);
        printf(m_strErrorInfo.toStdString().c_str());
        return false;
    }
    return true;
}

bool CPourDevices::IsAllActive(void)
{
    int nItem = 0;
    CSwitPump* pPumMod;
    while(nItem<m_listAPumModules.count())
    {
        pPumMod = m_listAPumModules.at(nItem++);
        if(false==pPumMod->IsActive())
        {
           return false;
        }
    }
    if(nItem>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CPourDevices::SetGrpID(UINT32 unGrpID)
{
    m_unBatGrpID = unGrpID;
}

UINT32 CPourDevices::GetPumpData(UINT8 unType, UINT8 unIndex, BYTE* pDataBuf,UINT32& unBufSize)
{
	CSwitPump* pPumMod;
	QString strClsName;
    UINT32 unDataPos;

    if(unType == APUM_DEV_BAS_ID)
    {
	    pPumMod = m_listAPumModules.at(unIndex);
		pPumMod->GetClassName(strClsName);
		if("CSwitPump"==strClsName)
		{
			pPumMod->GetCtrlDevData(&m_pumDevData);
			unBufSize = sizeof(PumpDevData);
			memcpy((BYTE*)pDataBuf,(BYTE*)&m_pumDevData,unBufSize);

			pPumMod->GetMcuVersion(&m_unMcuStateInfo[0],0);//动脉血泵第一个
		}
    }
    else if(unType == DEV_VPUMP_TYPE)
    {
	    pPumMod = m_listVPumModules.at(unIndex);
		pPumMod->GetClassName(strClsName);
		if("CSwitPump"==strClsName)
		{
			pPumMod->GetCtrlDevData(&m_pumDevData);
			unBufSize = sizeof(PumpDevData);
			memcpy((BYTE*)pDataBuf,(BYTE*)&m_pumDevData,unBufSize);
		}
    }
	
    unDataPos = unBufSize;
    return unDataPos;
}

UINT32 CPourDevices::GetWatRoomData(UINT8 unIndex, BYTE* pDataBuf,UINT32& unBufSize)
{
	CSwitWater* pWatMod;
	QString strClsName;
    UINT32 unDataPos;

    pWatMod = m_listWatModules.at(unIndex);
	pWatMod->GetClassName(strClsName);
	if("CSwitWater"==strClsName)
	{
		pWatMod->GetCtrlDevData(&m_watDevData);
		unBufSize = sizeof(m_watDevData);
		memcpy((BYTE*)pDataBuf,(BYTE*)&m_watDevData,unBufSize);
		
		pWatMod->GetMcuVersion(&m_unMcuStateInfo[1],0);//水浴第二个
	}
    unDataPos = unBufSize;
    return unDataPos;
}

UINT8 CPourDevices::GetWatBloodState(void)
{
    return m_watDevData.unBloodSta;
}

void CPourDevices::GetMucVerInfo(BYTE* pDataBuf)
{
    memcpy(pDataBuf,m_unMcuStateInfo,sizeof(m_unMcuStateInfo));
}

