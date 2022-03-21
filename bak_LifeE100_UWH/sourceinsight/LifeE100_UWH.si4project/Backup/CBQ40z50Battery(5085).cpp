#include "includes.h"
#include "CBQ40Z50Battery.h"
#include "cworkthread.h"
#include <arpa/inet.h>

#define CMD_TMP        0x08	//
#define CMD_VOL        0x09
#define CMD_CUR        0x0A
#define CMD_SOC        0x0D
#define CMD_NUM        0x17


CBq40z50Bat::CBq40z50Bat()
{
    //memset(&m_pBatData,0,sizeof(m_pBatData));
    m_bGetData = false;
	m_unGetVerFlg = false;
	m_unChkCmd[0] = CMD_TMP;m_unChkCmd[1] = CMD_VOL;
	m_unChkCmd[2] = CMD_CUR;m_unChkCmd[3] = CMD_SOC;
	m_unChkCmd[4] = CMD_NUM;
	m_unCmdFlg = 3;
	m_unBatTmp = 0;
	m_unBatVol = 0;
	m_unBatCur = 0;
	m_unBatSoc = 0;
	m_unCycNum = 0;

	m_unSocNum = 0;
}

void CBq40z50Bat::ProcTask(void)
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
            BuillCmdData(NULL,0,m_unChkCmd[m_unCmdFlg]);
        }
		//SetMsTimer(2000);
    }
}


void CBq40z50Bat::OnCmdRsp(UINT8 unCmdID)
{
    CBasicDevice::OnCmdRsp(unCmdID);
    m_curCmdData.unCmdID = INVALID_DEV_CMD_ID;
    m_curCmdData.unCmdDataLen = 0;
}


void CBq40z50Bat::DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen)
{
    OnCmdRsp(unCmdID);
    switch(unCmdID)
    {
	    case CMD_TMP:
			m_unBatTmp = ((pDataBuf[1]<<8)&0xff00)+pDataBuf[0];
			//printf("----------------------------------Tmp:%u-----------------\r\n",m_unBatTmp);
		    m_unCmdFlg = 1;
		break;
	    case CMD_VOL:
			m_unBatVol = ((pDataBuf[1]<<8)&0xff00)+pDataBuf[0];
			//printf("----------------------------------VOL:%u-----------------\r\n",m_unBatVol);
		    m_unCmdFlg = 2;
		break;
	    case CMD_CUR:
			m_unBatCur = ((pDataBuf[1]<<8)&0xff00)+pDataBuf[0];
			//printf("----------------------------------Cur:%d-----------------\r\n",m_unBatCur);
		    m_unCmdFlg = 3;
		break;
	    case CMD_SOC:
			if(pDataBuf[0] < 20 || pDataBuf[0] == 0)
			{
			    m_unSocNum++;
				if(m_unSocNum >= 3)
				{
				    m_unBatSoc = pDataBuf[0];
					m_unSocNum = 0;
				}
			}
			else
			{
				m_unBatSoc = pDataBuf[0];
				m_unSocNum = 0;
			}
			//printf("----------------------------------Soc:%u-----------------\r\n",m_unBatSoc);
		    m_unCmdFlg = 4;
			m_bGetData = true;
		break; 
	    case CMD_NUM:
			m_unCycNum = ((pDataBuf[1]<<8)&0xff00)+pDataBuf[0];
			//printf("----------------------------------CycNum:%u-----------------\r\n",m_unCycNum);
		    m_unCmdFlg = 0;
			m_bGetData = true;
		break; 

		default:break;
    }
}

bool CBq40z50Bat::IsRun(void)
{
    if(true==m_bAtvFlag)// && DEV_RUN_ON==m_pWaterData.unRunFlg)
    {
        return true;
    }
    return false;
}

UINT32 CBq40z50Bat::GetErrCode(void)
{
    //return m_pWaterData.unDevCode;
}

void CBq40z50Bat::GetCtrlDevData(void* pDevData)
{
    if(m_bGetData == true)
    {
        m_bGetData = false;
	    BqBatBascInfo* pBatDevData = (BqBatBascInfo*)pDevData;
		pBatDevData->unBatTmp = m_unBatTmp;
		pBatDevData->unBatVol = m_unBatVol;
		pBatDevData->unBatCur = m_unBatCur;
		pBatDevData->unBatSoc = m_unBatSoc;
		pBatDevData->unCycNum = m_unCycNum;
    }
	else if(m_bAtvFlag == false)
	{
		//memset(&m_pWaterData,0,sizeof(m_pWaterData));
	    //WatDevData* pWatDevData = (WatDevData*)pDevData;
		//memcpy(pWatDevData,(BYTE*)&m_pWaterData,sizeof(m_pWaterData));
	}
}

void CBq40z50Bat::GetClassName(QString& strClassName)
{
    strClassName = "CBq40z50Bat";
}

