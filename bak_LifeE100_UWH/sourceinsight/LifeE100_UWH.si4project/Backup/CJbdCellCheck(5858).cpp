#include "includes.h"
#include "CJbdCellCheck.h"
#include "cworkthread.h"
#include <arpa/inet.h>

#define CMD_BAS_INFO_DATA        0x03	//主机发送读取基本信息 0x03 指令


CJbdCell::CJbdCell()
{
    //memset(&m_pWaterData,0,sizeof(m_pWaterData));
    m_bGetData = false;
	m_unGetVerFlg = false;
}

void CJbdCell::ProcTask(void)
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
            //CtrlRs485RvcSnd(1);
            //BuillCmdData(NULL,0,CMD_BAS_INFO_DATA);
			//CtrlRs485RvcSnd(0);
			//printf("-----------------------CMD_BAS_INFO_DATA----------------------------\r\n");
        }
		//SetMsTimer(3000);
    }
}


void CJbdCell::OnCmdRsp(UINT8 unCmdID)
{
    CBasicDevice::OnCmdRsp(unCmdID);
    m_curCmdData.unCmdID = INVALID_DEV_CMD_ID;
    m_curCmdData.unCmdDataLen = 0;
}


void CJbdCell::DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen)
{
    UINT32 unDataPos = 0;

    OnCmdRsp(unCmdID&0x7F);
    switch(unCmdID)
    {
	    case CMD_BAS_INFO_DATA:
			printf("-----------------CMD_BAS_INFO_DATA---------------\r\n");
			for(UINT8 i = 0; i < unDataLen; i++)
				printf("%02x ",pDataBuf[i]);
			printf("\r\n");
			/*
		if(unDataLen <= sizeof(WatDevData))
		{
			//数据上传
			WatDevData* pDevData = (WatDevData*)&pDataBuf[unDataPos];
			
			m_pWaterData.unRunFlg = pDevData->unRunFlg;
			m_pWaterData.unTmpVal = ntohs(pDevData->unTmpVal);
			m_pWaterData.unWatLine = ntohs(pDevData->unWatLine);
			m_pWaterData.unBloodSta = pDevData->unBloodSta;
			m_pWaterData.unDevCode = htonl(pDevData->unDevCode);
		}
		else
		{
			printf("DataLen:%lu DataSize:%d PktSize Err! --m_pWaterData\r\n",unDataLen,sizeof(WatDevData));
		}*/
		break;
       		
		default:break;
    }
}

bool CJbdCell::IsRun(void)
{
    if(true==m_bAtvFlag)// && DEV_RUN_ON==m_pWaterData.unRunFlg)
    {
        return true;
    }
    return false;
}

UINT32 CJbdCell::GetErrCode(void)
{
    //return m_pWaterData.unDevCode;
}

void CJbdCell::GetCtrlDevData(void* pDevData)
{
    if(m_bGetData == true)
    {
        m_bGetData = false;
	    //WatDevData* pWatDevData = (WatDevData*)pDevData;
		//memcpy(pWatDevData,(BYTE*)&m_pWaterData,sizeof(m_pWaterData));
    }
	else if(m_bAtvFlag == false)
	{
		//memset(&m_pWaterData,0,sizeof(m_pWaterData));
	    //WatDevData* pWatDevData = (WatDevData*)pDevData;
		//memcpy(pWatDevData,(BYTE*)&m_pWaterData,sizeof(m_pWaterData));
	}
}

void CJbdCell::GetClassName(QString& strClassName)
{
    strClassName = "CJbdCell";
}

