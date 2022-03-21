#include "includes.h"
#include "CJbdCellCheck.h"
#include "cworkthread.h"
#include <arpa/inet.h>

#define CMD_BAS_INFO_DATA        0x03	//主机发送读取基本信息 0x03 指令
#define NTC_TMP                  2731

CJbdCell::CJbdCell()
{
    memset(&m_pBatData,0,sizeof(m_pBatData));
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
            BuillCmdData(NULL,0,CMD_BAS_INFO_DATA);
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
		if(unDataLen <= sizeof(BatBascInfo))
		{
			//数据上传
			BatBascInfo* pDevData = (BatBascInfo*)&pDataBuf[unDataPos];
			m_pBatData.unBatVol = ntohs(pDevData->unBatVol);
			m_pBatData.unBatCur = ntohs(pDevData->unBatCur);  
			m_pBatData.unLeftCap = ntohs(pDevData->unLeftCap); 
    		m_pBatData.unRatedCap = ntohs(pDevData->unRatedCap);
			m_pBatData.unDshChgNum = ntohs(pDevData->unDshChgNum);
			m_pBatData.unMadDate = ntohs(pDevData->unMadDate);  
    		m_pBatData.unCllBln = ntohs(pDevData->unCllBln);
			m_pBatData.unCllBln_H = ntohs(pDevData->unCllBln_H);
			m_pBatData.unSafeStat = ntohs(pDevData->unSafeStat);
			//printf("unBatVol:%u unBatCur:%d unLeftCap:%u unRatedCap:%u \r\n",m_pBatData.unBatVol,\
				   //m_pBatData.unBatCur,m_pBatData.unLeftCap,m_pBatData.unRatedCap);
			m_pBatData.unVer = pDevData->unVer;
			m_pBatData.unRSOC = pDevData->unRSOC;
			m_pBatData.unFETMOS = pDevData->unFETMOS;  
			m_pBatData.unCllNum = pDevData->unCllNum;
			m_pBatData.unNTCNum = pDevData->unNTCNum;
			m_pBatData.unNTCTmp[0] = ntohs(pDevData->unNTCTmp[0]) - NTC_TMP;
			m_pBatData.unNTCTmp[1] = ntohs(pDevData->unNTCTmp[1]) - NTC_TMP;
			//printf("unRSOC:%u unFETMOS:%u unCllNum:%u unNTCTmp[0]:%u unNTCTmp[1]:%u\r\n",m_pBatData.unRSOC,m_pBatData.unFETMOS,\
				   //m_pBatData.unCllNum,m_pBatData.unNTCTmp[0],m_pBatData.unNTCTmp[1]);
			m_bGetData = true;
		}
		else
		{
			printf("DataLen:%lu DataSize:%d PktSize Err! --m_pBatData\r\n",unDataLen,sizeof(BatBascInfo));
		}
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
	    BatBascInfo* pBatDevData = (BatBascInfo*)pDevData;
		memcpy(pBatDevData,(BYTE*)&m_pBatData,sizeof(m_pBatData));
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

