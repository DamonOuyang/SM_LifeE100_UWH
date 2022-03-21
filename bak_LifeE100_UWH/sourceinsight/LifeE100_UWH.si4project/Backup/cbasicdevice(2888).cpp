#include "cbasicdevice.h"
#include "ccmddataqueue.h"
#include "cuartsocket.h"
#include "cworkthread.h"

#define MAX_DEV_CMD_TMT_COUNT   60
#define CMD_WAIT_RSP_MS_COUNT   3000L

CBasicDevice::CBasicDevice()
{
    m_unCmdMsTimer  = 0;
    m_unDevID    = INVALID_DEV_ID;
    m_unTmtCount = 0;           //超时(次数)
    m_unCmdStat  = CMD_ST_IDLE;	//当前命令状态
    m_bAtvFlag   =  false;
    m_curCmdData.unCmdDataLen = 0;
    m_curCmdData.unCmdID = INVALID_DEV_CMD_ID;
    m_pUARTSkt    = NULL;
    m_pWorkThread = NULL;
    m_unMaxTmtCount = MAX_DEV_CMD_TMT_COUNT;
    m_bEnabled = false;

    m_pCmdDataQueue = new CCmdDataQueue(10);
    memset(m_unCmdCtrlStat,CMD_ST_IDL,sizeof(m_unCmdCtrlStat));
}

CBasicDevice::~CBasicDevice()
{
    delete m_pCmdDataQueue;
}
void CBasicDevice::ProcTask(void)
{
    if(INVALID_DEV_CMD_ID!=m_curCmdData.unCmdID)
    {
        if(CMD_ST_WAIT_RSP!=m_unCmdStat||0==m_unCmdWaitRspMaxMs)
        {
            SendData();
        }
    }
    else
    {
        m_unCmdStat = CMD_ST_IDLE;
    }
}

void CBasicDevice::OnCmdRsp(UINT8 unCmdID)
{
    m_unTmtCount = 0;
    m_unCmdStat = CMD_ST_IDLE;
    m_bAtvFlag = true;
    SetDevTmt(0x00);
    m_strErrorInfo = "";
    if(m_curCmdData.unCmdID==(unCmdID&0x7F))
    {
        m_curCmdData.unCmdID = INVALID_DEV_CMD_ID;
        m_curCmdData.unCmdDataLen = 0;
    }
}

void CBasicDevice::OnMsTimer(UINT32 unMsCount)
{
    if(m_unCmdMsTimer)
    {
        if(m_unCmdMsTimer>=unMsCount)
        {
            m_unCmdMsTimer -= unMsCount;
        }
        else
        {
            m_unCmdMsTimer = 0;
        }
    }
    if(m_unCmdWaitRspMaxMs)
    {
        if(m_unCmdWaitRspMaxMs>=unMsCount)
        {
            m_unCmdWaitRspMaxMs -= unMsCount;
        }
        else
        {
            m_unCmdWaitRspMaxMs = 0;
        }
    }
}

bool CBasicDevice::BuillCmdData(BYTE* pDataBuf,long lDataLen,long lCmdID)
{
    CmdData cmdData;
    if(lDataLen>0)
    {
        memcpy((BYTE*)cmdData.pCmdData,pDataBuf,lDataLen);
    }
    cmdData.unCmdDataLen = lDataLen;
    cmdData.unDevID = (UINT8)m_unDevID;
	cmdData.unSndID = (UINT8)m_unSndID;
    cmdData.unCmdID = (UINT8)lCmdID;
    return m_pCmdDataQueue->AddCmdData(&cmdData);
}

bool CBasicDevice::GetNextCmdData(void)
{
    if(false==m_pCmdDataQueue->IsEmpty())
    {
        m_pCmdDataQueue->GetCmdData(&m_curCmdData);
        m_unCmdStat = CMD_ST_WAIT_SND;
        return true;
    }
    return false;
}


void CBasicDevice::SetMsTimer(UINT32 unMsCount)
{
    m_unCmdMsTimer = unMsCount;
}

void CBasicDevice::SendData(void)
{
    if(INVALID_DEV_CMD_ID != m_curCmdData.unCmdID&&NULL != m_pUARTSkt)
    {
        //发送命令
        if(false==m_pUARTSkt->FindDevCmd(m_unDevID))
        {
            m_pUARTSkt->AddCmdData(&m_curCmdData);
            if(16==m_unDevID)
            {
                //printf("AddCmdID:%u DevID:%lu\r\n",m_curCmdData.unCmdID,m_unDevID);
            }
        }
        else
        {
            printf("-----------------DevID:%lu  CmdExist!!!!-------------------\r\n",m_unDevID);
        }
        m_unCmdStat = CMD_ST_WAIT_RSP;
        m_unCmdWaitRspMaxMs = CMD_WAIT_RSP_MS_COUNT;
    }
}

UINT32 CBasicDevice::GetDevID(void)
{
    return m_unDevID;
}


void CBasicDevice::SetDevID(UINT32 unDevID)
{
    m_unDevID = unDevID;
}

void CBasicDevice::SetSndID(UINT32 unSndID)
{
    m_unSndID = unSndID;
}


void CBasicDevice::OnCmdTimeOut(void)
{
    if(INVALID_DEV_CMD_ID!=m_curCmdData.unCmdID)
    {
        m_unTmtCount++;
        m_strErrorInfo = QString("设备ID<%1>:命令<0x%2>超时,次数:<%3>,发送ID<%4>\r\n")\
                        .arg(m_unDevID).arg(m_curCmdData.unCmdID,0,16).arg(m_unTmtCount)\
                        .arg(m_unSndID);
        ShowInfo(m_strErrorInfo.toStdString().c_str());
		//printf("m_strErrorInfo:%s \r\n",m_strErrorInfo.toStdString().c_str());
        if(m_unTmtCount>m_unMaxTmtCount)
        {
            m_bAtvFlag = false;
            SetDevTmt(m_unTmtCount);
            ClearCmds();
            m_unTmtCount = 0;
            m_unCmdStat  = CMD_ST_IDLE;
            m_strErrorInfo = QString("---------------设备ID<%1>:命令严重超时-------------\r\n").arg(m_unDevID);
            ShowInfo(m_strErrorInfo.toStdString().c_str());
        }
        else
        {
            //重新等待发送
            m_unCmdStat = CMD_ST_WAIT_SND;
			//printf("---------------m_unCmdStat ID:%lu Cmd:%u \r\n",m_unDevID, m_curCmdData.unCmdID);
        }
    }
    else
    {
        m_unCmdStat = CMD_ST_IDLE;
    }
}
void CBasicDevice::SetUARTSocket(CUARTSocket*  pUARTSocket)
{
    m_pUARTSkt = pUARTSocket;
}
void CBasicDevice::SetWorkThread(CWorkThread*  pWorkThread)
{
    m_pWorkThread = pWorkThread;
}

void CBasicDevice::ShowInfo(const char* pStrInfo)
{
    if(NULL!= m_pWorkThread)
    {
        m_pWorkThread->ShowStringInfo(pStrInfo);
    }
    else
    {
        printf(pStrInfo);
    }
}

bool CBasicDevice::IsActive(void)
{
    return m_bAtvFlag;
}

bool CBasicDevice::IsEnabled(void)
{
    return m_bEnabled;
}
void CBasicDevice::SetEnable(bool bEnFlag)
{
    m_bEnabled = bEnFlag;
}

/*
bool CBasicDevice::IsRun(void)
{
    return false;
}
*/
UINT32 CBasicDevice::GetErrCode(void)
{
    return 0L;
}
void CBasicDevice::GetErrorInfo(QString& strError)
{
    strError = "";
}


void CBasicDevice::GetClassName(QString& strClassName)
{
    strClassName = "CBasicDevice";
}

void CBasicDevice::SetCmdCtrlStat(UINT8 unCmdIndex,UINT8 unCmdStat)
{
    if(unCmdIndex<MAX_CMD_TYPE_COUNT)
    {
        m_unCmdCtrlStat[unCmdIndex] = unCmdStat;
    }
}

bool  CBasicDevice::HasCmdSnd(void)
{
    if(true==m_pCmdDataQueue->IsEmpty()&&\
            INVALID_DEV_CMD_ID==m_curCmdData.unCmdID)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void CBasicDevice::ClearCmds(void)
{
    m_pCmdDataQueue->ClearQueue();
    m_curCmdData.unCmdDataLen = 0;
    m_curCmdData.unCmdID = INVALID_DEV_CMD_ID;
}

bool CBasicDevice::GetCmdConfirm(UINT8 unCmdIndex)
{
    if(unCmdIndex<MAX_CMD_TYPE_COUNT)
    {
        if(CMD_ST_SND!=m_unCmdCtrlStat[unCmdIndex])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void CBasicDevice::SetDevTmt(UINT16 unTmtCount)
{
    if(NULL!= m_pWorkThread)
    {
        UINT8 unAlmFlag;
        BYTE  bVal;
        QString strClsName;
        GetClassName(strClsName);
        if(false==m_bAtvFlag)
        {
            unAlmFlag = 1;
        }
        else
        {
            unAlmFlag = 0;
        }
		
        if("CSwitPump"==strClsName)
        {
            //泵模块块
            bVal = g_devAlmBits.unAPumModBits;
            bVal = (bVal>>(m_unDevID-APUM_DEV_BAS_ID))&0x01;
            if(true==m_pWorkThread->SetAlmItem(bVal,ALM_ITEM_SUB_DEV_TMT,\
                                      m_unDevID,0x00,unTmtCount,unAlmFlag))
            {
                if(1==unAlmFlag)
                {
                    bVal = (0x01<<(m_unDevID-APUM_DEV_BAS_ID));
                    g_devAlmBits.unAPumModBits = g_devAlmBits.unAPumModBits|bVal;
					
					if(g_almItemEx.almItem.unAlmID != ALM_ITEM_WAT_TMP_UP ||\
					   g_almItemEx.unUpdFlag != 1)
					{
						g_almItemEx.almItem.unAlmID = ALM_ITEM_SUB_DEV_TMT;
						g_almItemEx.almItem.unAlmObjID = APUM_DEV_BAS_ID;
					}
                }
                else
                {
                    bVal = (0x01<<(m_unDevID-APUM_DEV_BAS_ID));
                    bVal = ~bVal;
                    g_devAlmBits.unAPumModBits = g_devAlmBits.unAPumModBits&bVal;
					/**/
					if(g_almItemEx.almItem.unAlmID == ALM_ITEM_SUB_DEV_TMT)
					{
						g_almItemEx.almItem.unAlmID = 0;
						g_almItemEx.almItem.unAlmObjID = 0;
					}
                }
            }
        }
        else if("CSwitWater"==strClsName)
        {
            //水浴模块块
            bVal = g_devAlmBits.unWatModBits;
            bVal = (bVal>>(m_unDevID-WAT_DEV_BAS_ID))&0x01;
            if(true==m_pWorkThread->SetAlmItem(bVal,ALM_ITEM_SUB_DEV_TMT,\
                                      m_unDevID,0x00,unTmtCount,unAlmFlag))
            {
                if(1==unAlmFlag)
                {
                    bVal = (0x01<<(m_unDevID-WAT_DEV_BAS_ID));
                    g_devAlmBits.unWatModBits = g_devAlmBits.unWatModBits|bVal;
					
					if(g_almItemEx.almItem.unAlmID != ALM_ITEM_WAT_TMP_UP ||\
					   g_almItemEx.unUpdFlag != 1)
					{
						g_almItemEx.almItem.unAlmID = ALM_ITEM_SUB_DEV_TMT;
						g_almItemEx.almItem.unAlmObjID = WAT_DEV_BAS_ID;
					}
                }
                else
                {
                    bVal = (0x01<<(m_unDevID-WAT_DEV_BAS_ID));
                    bVal = ~bVal;
                    g_devAlmBits.unWatModBits = g_devAlmBits.unWatModBits&bVal;
					
					if(g_almItemEx.almItem.unAlmID == ALM_ITEM_SUB_DEV_TMT)
					{
						g_almItemEx.almItem.unAlmID = 0;
						g_almItemEx.almItem.unAlmObjID = 0;
					}
                }
            }
        }
    }
}
int CBasicDevice::GetSubDevSocket(void)
{
    return m_pUARTSkt->GetSocket();
}
