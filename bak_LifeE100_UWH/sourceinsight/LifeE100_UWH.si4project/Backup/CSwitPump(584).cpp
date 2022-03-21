#include "includes.h"
#include "CSwitPump.h"
#include "cworkthread.h"
#include <arpa/inet.h>

//#define PUMP_SND_MAX_GET_DATA_MS  500L

CSwitPump::CSwitPump()
{
    memset(&m_pPumpData,0,sizeof(m_pPumpData));
	memset(&m_pSetPulPrm,0,sizeof(m_pSetPulPrm));
    m_bGetData = false;
	m_unGetVerFlg = false;
	m_bStrInitFlg = false;
	m_unPourState = 0;
	m_bUpDveFlag = false;
	m_bAtvFlag = true;
	m_unWatingStrUp = false;
}

void CSwitPump::ProcTask(void)
{
    CBasicDevice::ProcTask();
    if(false==m_bAtvFlag)
    {
        //m_bSetPrmFlag = true;//重设置设备参数
    }
    //查询子设备数据
    if(CMD_ST_IDLE == m_unCmdStat)
    {
        if(false==GetNextCmdData()&&0==m_unCmdMsTimer)
        {
            if(true==m_bAtvFlag)
            {
                if(false == m_bUpDveFlag)
                {
	                if(true==m_bSetPrmFlag)
	                {
	                	SendDevPrm();
						m_bSetPrmFlag = false;
	                }
					else if(m_unGetVerEn == true)
					{
						GetDevVer();
						m_unGetVerEn = false;
					}
					else if(m_bSndPourFlg == true)
					{
					    SndPourState();
					    m_bSndPourFlg = false;
					}
					else if(true == m_bSetPulFlag)
					{
					    SendPulsePrm();
						m_bSetPulFlag = false;
					}
					else if(true == m_bSndUpStrFlag)
					{
					    SndStrUpdateSet();
						m_bSndUpStrFlag = false;
						m_unWatingStrUp = true;
					}
					else if(true == m_bUpInitFlag)
					{
					    m_bUpInitFlag = false;
						if(true == InitDevUpdate())
						{
							UpPackAck pUpPackAck;
							pUpPackAck.McuUpdResult = 0;
							pUpPackAck.unPkgIndex = 0;
							SetNextUpPack(&pUpPackAck);
							m_bUpDveFlag = true;
						}
					}
					else if(m_bUpDveFlag == false&& \
							m_bSndUpStrFlag == false&& \
							m_bSndUpPackFlag == false)
					{
						BuillCmdData(NULL,0,CMD_SUB_DEV_DATA);
					}
                }
				else
				{
				    if(true == m_bSndUpPackFlag)
				    {
				    	BuildUpadteMcuCmd();
						m_bSndUpPackFlag = false;
				    }
				}
		    }
			else
			{
				BuillCmdData(NULL,0,CMD_SUB_DEV_DATA);
				//m_bAtvFlag = true;
			}
			if(m_unWatingStrUp == false)
			{
            	SetMsTimer(SND_MAX_GET_DATA_MS);
			}
			else
			{
			    m_unWatingStrUp = false;
				SetMsTimer(2000);
				printf("------------------------------------------------------dly \r\n");
			}
        }
    }
}

//发送灌注状态
bool CSwitPump::SndPourState(void) 
{
    printf("entr CSwitPump::SndPourState unDevID:%lu \r\n",m_unDevID);
    if(false==BuillCmdData((BYTE*)&m_unPourState,sizeof(m_unPourState),CMD_SND_POUR_STA))
    {
        ClearCmds();
        BuillCmdData((BYTE*)&m_unPourState,sizeof(m_unPourState),CMD_SND_POUR_STA);
    }
    SetCmdCtrlStat(CTRL_POUR_STA_SND,CMD_ST_SND);
    return true;
}

void CSwitPump::SetPourState(UINT8 unStat)
{
    printf("entr CSwitPump::SetPourState unDevID:%lu unStat:%u\r\n",m_unDevID,unStat);
	m_unPourState = unStat;
	m_bSndPourFlg = true;
}

bool CSwitPump::SetDevParam(SetDevPrm* pDevPrmCfg)
{
    if(m_bStrInitFlg == false)
    {
        m_bStrInitFlg = true;
		return false;
    }
    printf("entr CSwitPump::SetDevParam unDevID:%lu unIndex:%u unPrmVald:%d\r\n",m_unDevID,pDevPrmCfg->unIndex,pDevPrmCfg->unPrmVald);
    memcpy(&m_devParam,pDevPrmCfg,sizeof(pDevPrmCfg));//设备控制参数
    m_bSetPrmFlag = true;
	m_unCmdMsTimer = 0;
    return true;
}


void CSwitPump::DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen)
{
    UINT32 unDataPos = 0;
    OnCmdRsp(unCmdID&0x7F);
    switch(unCmdID)
    {
	    case CMD_SUB_DEV_DATA_ACK:
		if(unDataLen <= sizeof(PumpDevData))
		{
			//数据上传
			PumpDevData* pDevData = (PumpDevData*)&pDataBuf[unDataPos];

			m_lckMutex.lock();
			m_pPumpData.unRunFlg = pDevData->unRunFlg;
			m_pPumpData.unPourSta = pDevData->unPourSta;
			m_pPumpData.unTmpVal = ntohs(pDevData->unTmpVal);
			m_pPumpData.unFlowVal = ntohs(pDevData->unFlowVal);
			m_pPumpData.unPrssVal = ntohs(pDevData->unPrssVal);
			m_pPumpData.unSpeeVal = ntohs(pDevData->unSpeeVal);
			m_pPumpData.unDevCode = htonl(pDevData->unDevCode);
            m_lckMutex.unlock();
            m_bGetData = true;
			//printf("CSwitPump::-----unRunFlg:%u unPourSta:%u \r\n",m_pPumpData.unRunFlg,m_pPumpData.unPourSta);
			//printf("unPrssVal:%u unSpeeVal:%u \r\n",m_pPumpData.unPrssVal,m_pPumpData.unSpeeVal);
			if(m_unGetVerEn == false && m_unGetVerFlg == false)
			{
				m_unGetVerEn = true;
			}
		}
		else
		{
			printf("DataLen:%lu DataSize:%lu PktSize Err! --PumpDevData\r\n",unDataLen,sizeof(PumpDevData));
		}
		break;
       
		case CMD_SUB_DEV_PRM_SET_ACK:
			printf("CSwitPump::CMD_SUB_DEV_PRM_SET_ACK \r\n");
			SetCmdCtrlStat(CTRL_DEV_PRM_SND,CMD_ST_CFM);
			//m_bSetPrmFlag = false;
			break;
	    case CMD_SUB_DEV_RUN_ACK:
			printf("CSwitPump::CMD_SUB_DEV_RUN_ACK \r\n");
	        SetCmdCtrlStat(CTRL_DEV_RUN_SND,CMD_ST_CFM);
		m_unCmdMsTimer = 0;
	        break;
			/**/
	    case CMD_SUB_DEV_VER_ACK:
			printf("CSwitPump::CMD_SUB_DEV_VER_ACK len:%d :%s\r\n",unDataLen,pDataBuf);
	        SetCmdCtrlStat(CTRL_DEV_VER_SND,CMD_ST_CFM);
		    m_unGetVerFlg = true;
			strcpy(m_McuStatInfo.mcuVerInfo.McuVer, (char*)pDataBuf);
			//printf("CSwitPump::strcpy  :%s\r\n",pDataBuf);
			break;
			
		case CMD_SND_POUR_STA_ACK:
			printf("CSwitPump::CMD_SND_POUR_STA_ACK \r\n");
			SetCmdCtrlStat(CTRL_POUR_STA_SND,CMD_ST_CFM);
			break;
		case CMD_SUB_DEV_UP_ACK:
			printf("---CSwitPump::CMD_SUB_DEV_UP_ACK \r\n");
			SetCmdCtrlStat(CTRL_UP_SET_SND,CMD_ST_CFM);
			m_bUpInitFlag = true;
			ClearCmds();
			break;
		case CMD_PACK_DEV_UP_ACK:
		{
			UpPackAck* pUpPackAck = (UpPackAck*)&pDataBuf[unDataPos];
			pUpPackAck->unPkgIndex = ntohs(pUpPackAck->unPkgIndex);
			//printf("---CSwitPump::CMD_PACK_DEV_UP_ACK Result:%u Index:%u\r\n",pUpPackAck->McuUpdResult,pUpPackAck->unPkgIndex);
			SetCmdCtrlStat(CTRL_UP_PACK_SND,CMD_ST_CFM);
			if(pUpPackAck->McuUpdResult == 0 && \
			   pUpPackAck->unPkgIndex == (m_unTotalPkg-1))
			{
			    m_bUpInitFlag = 0;
				m_bUpDveFlag = false;
				CloseDevUpdate();
				m_unDevUpSate = UpdSuccess;
				printf("--CSwitPump--------UpdSuccess---------------------------------\r\n");
			}
			else
			{
			    pUpPackAck->unPkgIndex++;
				SetNextUpPack(pUpPackAck);
				m_unDevUpSate = UpdDoing;
			}
		}
		break;
		case CMD_SND_PUL_PRM_ACK:
			printf("CSwitPump::CMD_SND_PUL_PRM_ACK \r\n");
			SetCmdCtrlStat(CTRL_PUL_PRM_SND,CMD_ST_CFM);
			break;
		default:break;
    }
}

bool CSwitPump::IsRun(void)
{
    if(true==m_bAtvFlag)
    {
        if(DEV_RUN_ON == m_pPumpData.unRunFlg)
        {
        	return true;
        }
    }
    return false;
}

UINT32 CSwitPump::GetErrCode(void)
{
    return m_pPumpData.unDevCode;
}

void CSwitPump::GetCtrlDevData(void* pDevData)
{
    if(m_bGetData == true)
    {
        m_lckMutex.lock();
        m_bGetData = false;
	    PumpDevData* pPumpDevData = (PumpDevData*)pDevData;
		memcpy(pPumpDevData,(BYTE*)&m_pPumpData,sizeof(m_pPumpData));
		m_lckMutex.unlock();
    }
	else if(m_bAtvFlag == false)
	{
		memset(&m_pPumpData,0,sizeof(m_pPumpData));
	    PumpDevData* pPumpDevData = (PumpDevData*)pDevData;
		memcpy(pPumpDevData,(BYTE*)&m_pPumpData,sizeof(m_pPumpData));
	}
}

void CSwitPump::GetClassName(QString& strClassName)
{
    strClassName = "CSwitPump";
}


bool CSwitPump::SetPulseParam(SetPulPrm* pPluPrm)
{
    printf("---------------CSwitPump::SetPulseParam--unPourSta:%u--------------------\r\n",m_pPumpData.unPourSta);
	if(m_pPumpData.unPourSta == 0)
	{
		return false;
	}
	printf("entr CSwitPump::SetPulseParam unDevID:%lu unPumType:%u unPulFreq:%u unPulVal:%u\r\n",\
	        m_unDevID,pPluPrm->unPumType,pPluPrm->unPulFreq,pPluPrm->unPulVal);

	memcpy(&m_pSetPulPrm,pPluPrm,sizeof(pPluPrm));//脉搏控制参数
	m_bSetPulFlag = true;
	return true;
}

void CSwitPump::SendPulsePrm(void)
{
    printf("CSwitPump::SendPulsePrm devID:%lu SndID:%lu\r\n",m_unDevID,m_unSndID);
    m_pSetPulPrm.unPulVal = htons(m_pSetPulPrm.unPulVal);
    BuillCmdData((BYTE*)&m_pSetPulPrm,sizeof(m_pSetPulPrm),CMD_SND_PUL_PRM);
    SetCmdCtrlStat(CTRL_PUL_PRM_SND,CMD_ST_SND);
}


