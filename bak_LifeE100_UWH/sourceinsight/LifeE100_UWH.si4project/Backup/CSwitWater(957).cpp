#include "includes.h"
#include "CSwitWater.h"
#include "cworkthread.h"
#include <arpa/inet.h>

CSwitWater::CSwitWater()
{
    memset(&m_pWaterData,0,sizeof(m_pWaterData));
    m_bGetData = false;
	m_unGetVerFlg = false;
}

void CSwitWater::ProcTask(void)
{
    CSwitModule::ProcTask();
}


void CSwitWater::DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen)
{
    UINT32 unDataPos = 0;
    OnCmdRsp(unCmdID&0x7F);
    switch(unCmdID)
    {
	    case CMD_SUB_DEV_DATA_ACK:
		if(unDataLen <= sizeof(WatDevData))
		{
			//数据上传
			WatDevData* pDevData = (WatDevData*)&pDataBuf[unDataPos];
			
			m_pWaterData.unRunFlg = pDevData->unRunFlg;
			m_pWaterData.unTmpVal = ntohs(pDevData->unTmpVal);
			m_pWaterData.unWatLine = ntohs(pDevData->unWatLine);
			m_pWaterData.unBloodSta = pDevData->unBloodSta;
			m_pWaterData.unDevCode = htonl(pDevData->unDevCode);

            m_bGetData = true;
			//printf("CSwitWater::unRunFlg:%u ---unWatLine:%u---- unBloodSta:%u \r\n",m_pWaterData.unRunFlg,m_pWaterData.unWatLine,m_pWaterData.unBloodSta);
		
			if(m_unGetVerEn == false && m_unGetVerFlg == false)
			{
				m_unGetVerEn = true;
			}
		}
		else
		{
			printf("DataLen:%lu DataSize:%d PktSize Err! --m_pWaterData\r\n",unDataLen,sizeof(WatDevData));
		}
		break;
       
		case CMD_SUB_DEV_PRM_SET_ACK:
			printf("WatDevData::CMD_SUB_DEV_PRM_SET_ACK \r\n");
			SetCmdCtrlStat(CTRL_DEV_PRM_SND,CMD_ST_CFM);
			//m_bSetPrmFlag = false;
			break;
	    case CMD_SUB_DEV_RUN_ACK:
			printf("WatDevData::CMD_SUB_DEV_RUN_ACK \r\n");
	        SetCmdCtrlStat(CTRL_DEV_RUN_SND,CMD_ST_CFM);
	        break;
			/**/
	    case CMD_SUB_DEV_VER_ACK:
			printf("WatDevData::CMD_SUB_DEV_VER_ACK len:%d :%s\r\n",unDataLen,pDataBuf);
	        SetCmdCtrlStat(CTRL_DEV_VER_SND,CMD_ST_CFM);
		    m_unGetVerFlg = true;
			strcpy(m_McuStatInfo.mcuVerInfo.McuVer, (char*)pDataBuf);
			//printf("WatDevData::strcpy  :%s\r\n",pDataBuf);
			break;
		case CMD_SUB_DEV_UP_ACK:
			printf("WatDevData::CMD_SUB_DEV_UP_ACK \r\n");
	        SetCmdCtrlStat(CTRL_UP_SET_SND,CMD_ST_CFM);
		    m_bUpInitFlag = true;
			ClearCmds();
			break;
		case CMD_PACK_DEV_UP_ACK:
		{
			UpPackAck* pUpPackAck = (UpPackAck*)&pDataBuf[unDataPos];
			pUpPackAck->unPkgIndex = ntohs(pUpPackAck->unPkgIndex);
			//printf("---CSwitWater::CMD_PACK_DEV_UP_ACK Result:%u Index:%u\r\n",pUpPackAck->McuUpdResult,pUpPackAck->unPkgIndex);
	        SetCmdCtrlStat(CTRL_UP_PACK_SND,CMD_ST_CFM);
			if(pUpPackAck->McuUpdResult == 0 && \
			   pUpPackAck->unPkgIndex == (m_unTotalPkg-1))
			{
			    m_bUpInitFlag = 0;
			    m_bUpDveFlag = false;
				CloseDevUpdate();
				m_unDevUpSate = UpdSuccess;
				printf("--WatDevData--------UpdSuccess-------------------------\r\n");
				//状态升级成功
			}
			else
			{
			    pUpPackAck->unPkgIndex++;
				SetNextUpPack(pUpPackAck);
				m_unDevUpSate = UpdDoing;
			}
		}
			break;
			
		default:break;
    }
}

bool CSwitWater::IsRun(void)
{
    if(true==m_bAtvFlag && DEV_RUN_ON==m_pWaterData.unRunFlg)
    {
        return true;
    }
    return false;

}

UINT32 CSwitWater::GetErrCode(void)
{
    return m_pWaterData.unDevCode;
}

void CSwitWater::GetCtrlDevData(void* pDevData)
{
    if(m_bGetData == true)
    {
        m_bGetData = false;
	    WatDevData* pWatDevData = (WatDevData*)pDevData;
		memcpy(pWatDevData,(BYTE*)&m_pWaterData,sizeof(m_pWaterData));
    }
	else if(m_bAtvFlag == false)
	{
		memset(&m_pWaterData,0,sizeof(m_pWaterData));
	    WatDevData* pWatDevData = (WatDevData*)pDevData;
		memcpy(pWatDevData,(BYTE*)&m_pWaterData,sizeof(m_pWaterData));
	}
}

void CSwitWater::GetClassName(QString& strClassName)
{
    strClassName = "CSwitWater";
}

