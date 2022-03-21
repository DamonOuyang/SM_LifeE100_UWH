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

    memset(&m_pumADevData,0,sizeof(m_pumADevData));
	memset(&m_pumVDevData,0,sizeof(m_pumVDevData));
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


bool CPourDevices::StartRun(UINT8 unPumDevType, UINT8 unIndex)
{
    UINT8 unPumType = GetPumDevTypeIndex(unPumDevType);
    if(true==m_bRunFlag[unPumType])
    {
        m_strErrorInfo = "已经在启动中";
        return false;
    }
	
    if(0==m_listAPumModules.count() && unPumType == 0)
    {
        m_strErrorInfo = "没有配置动脉血泵控制模块";
        //m_unStopCode = STP_ERR_UNKOWN_ERR;
        return false;
    }
    if(0==m_listVPumModules.count() && unPumType == 1)
    {
        m_strErrorInfo = "没有配置静脉血泵控制模块";
        //m_unStopCode = STP_ERR_UNKOWN_ERR;
        return false;
    }
	
    OnUpdData(true);//更新实际数据

	if(false==SndPourDevRunCmd(unPumDevType,unIndex,DEV_ON))
	{
		//m_unStopCode = STP_ERR_SND_SUB_CMD_ERR;
		return false;
	}


	//当有其中一个泵开启了，不需要再创建文件
	if(true==m_bRunFlag[0] || true==m_bRunFlag[1])
	{
	    printf("Pum Run bRunFlag[0]:%u bRunFlag[1]:%u \r\n",m_bRunFlag[0],m_bRunFlag[1]);
	    m_bRunFlag[0] = true;
		m_bRunFlag[1] = true;
		return true;
	}
    if(false==CBasicPourProc::StartRun(unPumDevType,unIndex))
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

bool CPourDevices::StopRun(   UINT8 unPumDevType)
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
    SndPourDevRunCmd(unPumDevType,0,DEV_OFF);
    CBasicPourProc::StopRun(unPumDevType);
    m_unStrDlyMs = 1000L*60L*1L;//1分钟
    return true;
}

void CPourDevices::ProcPourTask(void)
{
    int nItem = 0;
    bool bStopFlag[2] = {0,0};
    CSwitPump* pPumMod;
    if(false == m_bRunFlag[0] && \
	   false == m_bRunFlag[1])
    {
        return;
    }
    if(g_pourTstData.tstInfo.unTotalTime <= 20)
    {
        return;
    }
	
	if(true == m_bRunFlag[0])//动脉血泵
	{
	    while(nItem<m_listAPumModules.count())
	    {
	        pPumMod = m_listAPumModules.at(nItem++);
	        if(false == pPumMod->IsActive())
	        {
	            m_unStopCode = STP_ERR_DEV_TMT_ERR;
	            bStopFlag[0] = true;
	        }
	        else if(true==pPumMod->GetCmdConfirm(CTRL_DEV_RUN_SND))
	        {
	            if(false==pPumMod->IsRun())
	            {
	                QString strClsName;
	                pPumMod->GetClassName(strClsName);
	                if("CSwitPump"==strClsName)
	                {
	                    m_unStopCode = STP_ERR_SUB_STP_ERR;//pPumMod->GetErrCode();
	                }
	                bStopFlag[0] = true;
	                printf("APum-StopRun m_unStopCode: %x \r\n",m_unStopCode);
	                break;
	            }
	        }
        }
    }
	if(true == m_bRunFlag[1])//静脉血泵
	{
	    while(nItem<m_listVPumModules.count())
	    {
	        pPumMod = m_listVPumModules.at(nItem++);
	        if(false == pPumMod->IsActive())
	        {
	            m_unStopCode = STP_ERR_DEV_TMT_ERR;
	            bStopFlag[1] = true;
	        }
	        else if(true==pPumMod->GetCmdConfirm(CTRL_DEV_RUN_SND))
	        {
	            if(false==pPumMod->IsRun())
	            {
	                QString strClsName;
	                pPumMod->GetClassName(strClsName);
	                if("CSwitPump"==strClsName)
	                {
	                    m_unStopCode = STP_ERR_SUB_STP_ERR;//pPumMod->GetErrCode();
	                }
	                bStopFlag[1] = true;
	                printf("VPum-StopRun m_unStopCode: %x \r\n",m_unStopCode);
	                break;
	            }
	        }
        }
    }
	/*
	if(g_devAlmBits.watGrpAlm[0].bTmpUBits)
	{
	    m_unStopCode = STP_ERR_WAT_TMP_ERR;
	    bStopFlag[0] = true;
		bStopFlag[1] = true;
		printf("STP_ERR_WAT_TMP_ERR \r\n");
	}*/

    if(true==bStopFlag[0])
    {
        printf("PumType:%u StopRun--------1\r\n",DEV_APUMP_TYPE);
        StopRun(DEV_APUMP_TYPE);
    }
    if(true==bStopFlag[1])
    {
        printf("PumType:%u StopRun--------1\r\n",DEV_VPUMP_TYPE);
        StopRun(DEV_VPUMP_TYPE);
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
    //动脉血泵设置值
	g_pourTstData.tstData.unASpeeSet = g_devConfigInfo.arteryParm.unSpeed;	//转速(RPM)设定值
	g_pourTstData.tstData.unAPrssSet = g_devConfigInfo.arteryParm.unPress;	//压力(mmHg)设定值
	//动脉血泵数据信息
    g_pourTstData.tstData.unATmpVal  = m_pumADevData.unTmpVal;	//温度(℃)
    g_pourTstData.tstData.unAFlowVal = m_pumADevData.unFlowVal;	//流量(ml)
    g_pourTstData.tstData.unAPrssVal = m_pumADevData.unPrssVal;	//压力(mmHg)
    g_pourTstData.tstData.unASpeeVal = m_pumADevData.unSpeeVal;	//转速(RPM)
    
    //水浴
	g_pourTstData.tstData.unWatTmpSet = g_devConfigInfo.watRooParam.unTmpVal; //水浴温度设定值
	g_pourTstData.tstData.unWatTmpVal = m_watDevData.unTmpVal; //水浴值(℃)
	g_pourTstData.tstData.unWatLine   = m_watDevData.unWatLine;	//水位

    //静脉血泵设置值
    g_pourTstData.tstData.unVSpeeSet = g_devConfigInfo.veinParm.unSpeed;  //静脉转速(RPM)设定值
    g_pourTstData.tstData.unVPrssSet = g_devConfigInfo.veinParm.unPress;	//静脉压力(mmHg)设定值
	//静脉血泵数据信息
    g_pourTstData.tstData.unVTmpVal  = m_pumVDevData.unTmpVal;	//温度(℃)
    g_pourTstData.tstData.unVFlowVal = m_pumVDevData.unFlowVal;	//流量(ml)
    g_pourTstData.tstData.unVPrssVal = m_pumVDevData.unPrssVal;	//压力(mmHg)
    g_pourTstData.tstData.unVSpeeVal = m_pumVDevData.unSpeeVal;	//转速(RPM)	

    m_unUpdDataMs = MAX_UPD_DATA_MS;
}

void CPourDevices::StopPump(   UINT8 unPumDevType, UINT8 unStopCode)
{
    m_unStopCode = unStopCode;
    StopRun(unPumDevType);
}

void CPourDevices::GetStopErrorInfo(QString& strError)
{
    //strError = StopCodeToString(m_unStopCode);
}

bool CPourDevices::SndPourDevRunCmd(     UINT8 unPumDevType, UINT8 unIndex, UINT8 unCode)
{
    CSwitPump* pPumMod;
    //int nItem = 0;

    if(unPumDevType == DEV_APUMP_TYPE)
    {
    	pPumMod = m_listAPumModules.at(unIndex);
    }
    else if(unPumDevType == DEV_VPUMP_TYPE)
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

    if(unType == DEV_APUMP_TYPE)
    {
	    pPumMod = m_listAPumModules.at(unIndex);
		pPumMod->GetClassName(strClsName);
		if("CSwitPump"==strClsName)
		{
			pPumMod->GetCtrlDevData(&m_pumADevData);
			unBufSize = sizeof(PumpDevData);
			memcpy((BYTE*)pDataBuf,(BYTE*)&m_pumADevData,unBufSize);

			pPumMod->GetMcuVersion(&m_unMcuStateInfo[0],0);//动脉血泵第一个下标·
		}
    }
    else if(unType == DEV_VPUMP_TYPE)
    {
	    pPumMod = m_listVPumModules.at(unIndex);
		pPumMod->GetClassName(strClsName);
		if("CSwitPump"==strClsName)
		{
			pPumMod->GetCtrlDevData(&m_pumVDevData);
			unBufSize = sizeof(PumpDevData);
			memcpy((BYTE*)pDataBuf,(BYTE*)&m_pumVDevData,unBufSize);

			pPumMod->GetMcuVersion(&m_unMcuStateInfo[2],0);//静脉血泵第三个下标
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
		
		pWatMod->GetMcuVersion(&m_unMcuStateInfo[1],0);//水浴第二个下标
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

UINT8 CPourDevices::GetBubbleVal(UINT8 unPunType)
{
    if(unPunType == DEV_APUMP_TYPE)
    {
    	return m_pumADevData.unBubbVal;
    }
	return m_pumVDevData.unBubbVal;
}

