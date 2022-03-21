#include "includes.h"
#include "cswitchmodule.h"
#include "cworkthread.h"
#include <arpa/inet.h>
#include "fcntl.h"
#include <sys/stat.h>



CSwitModule::CSwitModule()
{
    memset(&m_devParam,0,sizeof(SetDevPrm));
	memset(&m_McuStatInfo,0,sizeof(McuUpdateState));
	memset(&m_pUpdateMcu,0,sizeof(UpdateMcu));
	memset(&m_pSetDevSta,0,sizeof(m_pSetDevSta));
	memset(&m_pDevUpErrInfo,0,sizeof(m_pDevUpErrInfo));
    m_bSetPrmFlag = false;
	m_unGetVerEn = false;
	m_unTotalSize = 0;
	m_unTotalPkg = 0;
	m_unLastPkgSize = 0;

	m_bUpInitFlag = false;
	m_bSndUpStrFlag = false;
	m_bUpDveFlag = false;
	m_unUpPackLen = 0;
	m_unDevUpSate = UpdNotStart;
	m_bAtvFlag = true;
	m_unWatingStrUp = false;
	m_bCalZeroFlag = false;
	m_unCalZeroBak = 0;
}

void CSwitModule::ProcTask(void)
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
                if(m_bUpDveFlag == false)
                {
	                if(true == m_bSetPrmFlag)
	                {
	                	SendDevPrm();
	                }
					else if(m_unGetVerEn == true)
					{
						GetDevVer();
						m_unGetVerEn = false;
					}
					else if(true == m_bCalZeroFlag)
					{
						SndCalZero();
						m_bCalZeroFlag = false;
					}
					else if(true == m_bSetDevSta)
					{
					    SendDevStateSync();
						m_bSetDevSta = false;
					}
					else if(true == m_bSndUpStrFlag)
					{
					    SndStrUpdateSet();
						m_bSndUpStrFlag = false;
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

/**/
bool CSwitModule::IsRun(void)
{
    printf("---here--------------------------------------CSwitModule::IsRun \r\n");
    return false;
}


bool CSwitModule::SetDevParam(SetDevPrm* pDevPrmCfg)
{
    printf("entr CSwitModule::SetDevParam unDevID:%lu unPrmVald:%d\r\n",m_unDevID,pDevPrmCfg->unPrmVald);
    memcpy(&m_devParam,pDevPrmCfg,sizeof(pDevPrmCfg));//设备控制参数
    m_bSetPrmFlag = true;
    return true;
}

bool CSwitModule::CtrlDevRun(UINT8 unCode) 
{
    printf("entr CSwitModule::CtrlDevRun unDevID:%lu \r\n",m_unDevID);
    if(false==BuillCmdData((BYTE*)&unCode,sizeof(unCode),CMD_SUB_DEV_RUN))
    {
        ClearCmds();
        BuillCmdData((BYTE*)&unCode,sizeof(unCode),CMD_SUB_DEV_RUN);
    }
    SetCmdCtrlStat(CTRL_DEV_RUN_SND,CMD_ST_SND);
	m_unSartStatDlySec = DEV_SRT_STAT_DLY_SEC;
    return true;
}

void CSwitModule::DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen)
{
	if(unCmdID != CMD_DEV_IP_ERR_INFO)
	{
    	OnCmdRsp(unCmdID&0x7F);
	}
    switch(unCmdID)
    {
    case CMD_SUB_DEV_RUN_ACK:
       SetCmdCtrlStat(CTRL_DEV_RUN_SND,CMD_ST_CFM);

       break;
    case CMD_SUB_DEV_DATA_ACK:
        SetCmdCtrlStat(CTRL_DEV_DATA_SND,CMD_ST_CFM);

        break;
    case CMD_SUB_DEV_PRM_SET_ACK:
        SetCmdCtrlStat(CTRL_DEV_PRM_SND,CMD_ST_CFM);
        //m_bSetPrmFlag = false;
		break;

   default:
        break;
    }
}

void CSwitModule::OnCmdTimeOut(void)
{
    CBasicDevice::OnCmdTimeOut();
}

void CSwitModule::GetCtrlDevData(void* pDevData)
{

}

void CSwitModule::GetClassName(QString& strClassName)
{
    strClassName = "CSwitModule";
}

void CSwitModule::SendDevPrm(void)
{
    printf("CSwitModule::SendDevPrm devID:%lu SndID:%lu\r\n",m_unDevID,m_unSndID);
	
    m_devParam.unPrmVald = htons(m_devParam.unPrmVald);
    BuillCmdData((BYTE*)&m_devParam,sizeof(m_devParam),CMD_SUB_DEV_PRM_SET);
    SetCmdCtrlStat(CTRL_DEV_PRM_SND,CMD_ST_SND);
    m_bSetPrmFlag = false;
}

void CSwitModule::GetDevVer(void)
{
    //printf("CSwitModule::GetDevVer devID:%d SndID:%d\r\n",m_unDevID,m_unSndID);
	
    BuillCmdData((BYTE*)&m_devParam,sizeof(m_devParam),CMD_SUB_DEV_VER);
    SetCmdCtrlStat(CTRL_DEV_VER_SND,CMD_ST_SND);
    m_unGetVerEn = false;
}


void CSwitModule::GetMcuVersion(McuUpdateState* pMcuVer, UINT8 unType)
{
    memcpy(pMcuVer, &m_McuStatInfo,sizeof(m_McuStatInfo));
}

bool CSwitModule::SetDevStateSync(SetDevStaSync* pPumSta)
{
	printf("entr SetDevStateSync unDevID:%lu unCevSat:%u unPourSta:%u unDevVal:%u\r\n",\
	        m_unDevID,pPumSta->unDevSat,pPumSta->unPourSta,pPumSta->unDevVal);

	memcpy(&m_pSetDevSta,pPumSta,sizeof(pPumSta));
	m_bSetDevSta = true;
	return true;
}

void CSwitModule::SendDevStateSync(void)
{
    printf("SendDevStateSync devID:%lu SndID:%lu\r\n",m_unDevID,m_unSndID);
    m_pSetDevSta.unDevVal = htons(m_pSetDevSta.unDevVal);
    BuillCmdData((BYTE*)&m_pSetDevSta,sizeof(m_pSetDevSta),CMD_SND_DEV_STA);
    SetCmdCtrlStat(CTRL_DEV_STA_SND,CMD_ST_SND);
}


//--------------------------------升级---------------------------------
void CSwitModule::SetDevUpdate(char* pUpdatePath)
{
	memset(&m_cMcuUpdatePath,0,sizeof(m_cMcuUpdatePath));
    strcpy((char*)&m_cMcuUpdatePath,pUpdatePath);
    printf("m_cMcuUpdatePath : %s\r\n",m_cMcuUpdatePath);
	
	memset(&m_McuStatInfo,0,sizeof(McuUpdateState));
	memset(&m_pUpdateMcu,0,sizeof(UpdateMcu));
	m_unDevUpSate = 0;
    m_bUpDveFlag = false;
	m_bSndUpStrFlag = true;
	ClearCmds();
}

void CSwitModule::SndStrUpdateSet(void)
{
    printf("Entr CSwitModule::SndStrUpdateSet DevId:%d \r\n",m_unDevID);
    BuillCmdData(NULL,0,CMD_SET_DEV_UP);
	SetCmdCtrlStat(CTRL_UP_SET_SND,CMD_ST_SND);
}

void CSwitModule::BuildUpadteMcuCmd(void)
{
    UpdateMcu updateMcu;
    UINT16 unDataLen;

	memcpy(&updateMcu, &m_pUpdateMcu,sizeof(m_pUpdateMcu));
	
    unDataLen = offsetof(UpdateMcu,unSendData);
    unDataLen += m_unUpPackLen;

	//printf("BuildUpadteMcuCmd---ID:%lu unTotalPkg:%u unPkgIndex:%u \r\n",m_unDevID,updateMcu.unTotalPkg,updateMcu.unPkgIndex);

    updateMcu.unTotalPkg = ntohs(updateMcu.unTotalPkg);
    updateMcu.unPkgIndex = ntohs(updateMcu.unPkgIndex);

    if(false==BuillCmdData((BYTE*)&updateMcu,unDataLen,CMD_PACK_DEV_UP))
    {
        ClearCmds();
        BuillCmdData((BYTE*)&updateMcu,unDataLen,CMD_PACK_DEV_UP);
    }
	SetCmdCtrlStat(CTRL_UP_PACK_SND,CMD_ST_SND);
}


bool CSwitModule::InitDevUpdate(void)
{
    UINT32 unFileSize;
    m_fdUpdate = -1;
    bool bReturn = true;
	
	m_unTotalPkg = 0;
	m_pUpdateMcu.unPkgIndex = 0;
	m_pUpdateMcu.unTotalPkg = 0;
	m_unDevUpSate = 0;
	
    if(-1==(m_fdUpdate=open(m_cMcuUpdatePath,O_RDONLY)))
    {
        printf("Open <%s> File Fail!\r\n",m_cMcuUpdatePath);
		m_unDevUpSate = UpdFileOpenErr;
        return false;
    }

    struct stat fdStat;
    if(-1==fstat(m_fdUpdate,&fdStat))
    {
        close(m_fdUpdate);
        printf("fstat():%s Fail!\r\n",m_cMcuUpdatePath);
		m_unDevUpSate = UpdFileChkErr;
        return false;
    }
    unFileSize = fdStat.st_size;
    m_unTotalSize = unFileSize;
    m_unTotalPkg = m_unTotalSize / MAX_UPD_SND_DATA_LEN_EX;
    m_unLastPkgSize = unFileSize % MAX_UPD_SND_DATA_LEN_EX;
	if(m_unLastPkgSize)
	{
		m_unTotalPkg+=1;
	}
	m_pUpdateMcu.unTotalPkg = m_unTotalPkg;
    printf("InitDevUpdate---TotalSize:%lu TotalPkg:%u LastPkgSize:%u\r\n",m_unTotalSize,m_unTotalPkg,m_unLastPkgSize);
    return bReturn;
}

bool CSwitModule::RedDevUpdate(UINT32 unReadPos,BYTE* pDataBuf,UINT32 unDataLen)
{
    bool bReturn = true;
    if(-1==lseek(m_fdUpdate,unReadPos,SEEK_SET))
    {
        printf("LSeek DevUpdata Fail!\r\n");
		m_unDevUpSate = UpdFileReadChkErr;
        return false;
    }
    if((ssize_t)unDataLen!=read(m_fdUpdate,pDataBuf,unDataLen))
    {
        printf("Read TestData Fail!\r\n");
		m_unDevUpSate = UpdFileReadErr;
        bReturn = false;
    }
	fsync(m_fdUpdate);
	return bReturn;
}

bool CSwitModule::SetNextUpPack(UpPackAck* pUpPackAck)
{
    UINT16 unDataLen;

	//printf("McuUpdResult:%u unPkgIndex:%u \r\n",pUpPackAck->McuUpdResult,pUpPackAck->unPkgIndex);
	if(pUpPackAck->McuUpdResult == 0)
	{
        UINT32 unReadPos;
        unReadPos = pUpPackAck->unPkgIndex*MAX_UPD_SND_DATA_LEN_EX;
        unDataLen = MAX_UPD_SND_DATA_LEN_EX;
        if(pUpPackAck->unPkgIndex < m_unTotalPkg)
        {
            if(pUpPackAck->unPkgIndex==(m_unTotalPkg-1)&&0!=m_unLastPkgSize)//最后一包
            {
                unDataLen = m_unLastPkgSize;
            }
            if(false==RedDevUpdate(unReadPos, m_pUpdateMcu.unSendData,unDataLen))
            {
                printf("RedDevUpdate():%s Fail!\r\n",m_cMcuUpdatePath);
				m_bUpDveFlag = false;
				//m_unDevUpSate = 0;
				CloseDevUpdate();
                return false;
            }
/*
			for(UINT16 i = 0; i < unDataLen; i++)
			{
			    printf("%02x ",m_pUpdateMcu.unSendData[i]);
			}
			printf("\r\n");
*/			
			m_unUpPackLen = unDataLen;
			m_pUpdateMcu.unPkgIndex = pUpPackAck->unPkgIndex;
			m_bSndUpPackFlag = true;
			m_unUpFailNum = 0;
            return true;
        }
        else
        {
           printf("----Err----PktIndex:%u > TotalPkg:%u !\r\n",pUpPackAck->unPkgIndex,m_unTotalPkg);
        }

	}
	else
	{
		if(m_unUpFailNum < 3)
		{
			//重发上一包
			m_bSndUpPackFlag = true;
		}
		else
		{
			//退出整个升级任务
			m_bUpDveFlag = false;
			m_unUpFailNum = 0;
			m_unDevUpSate = UpdSndPackErr;
			CloseDevUpdate();
		}
	}
    return false;
}

void CSwitModule::GetDevUpdateInfo(void* pDevUpInfo)
{
    if(m_unDevUpSate >= UpdDoing)
    {
	    McuUpdateInfo* pMcuUpInfo = (McuUpdateInfo*)pDevUpInfo;
		pMcuUpInfo->unTotalPkg = m_unTotalPkg;
		pMcuUpInfo->unPkgIndex = m_pUpdateMcu.unPkgIndex;
		pMcuUpInfo->unMcuUpdState = m_unDevUpSate;
		if(m_unDevUpSate >= UpdSuccess || false==m_bAtvFlag)
		{
		    m_unTotalPkg = 0;
			m_pUpdateMcu.unPkgIndex = 0;
			m_pUpdateMcu.unTotalPkg = 0;
			m_unDevUpSate = 0;
			if(false==m_bAtvFlag)
			{
			    m_unDevUpSate = UpdSndPackErr;
			}
		}
    }
}

void CSwitModule::CloseDevUpdate(void)
{
    m_pUpdateMcu.unPkgIndex++;
    close(m_fdUpdate);
}

void CSwitModule::SetCalZeroCmd(UINT8 unCalItem)
{
    printf("---------CSwitModule::SetCalZeroCmd-----DevId:%d unCalItem:%u\r\n",m_unDevID,unCalItem);
	m_bCalZeroFlag = true;
	m_unCalItem = unCalItem;
}

void CSwitModule::SndCalZero(void)
{
    printf("Entr CSwitModule::SndCalZero DevId:%d \r\n",m_unDevID);
    //BuillCmdData(NULL,0,CMD_CAL_ZERO_DEV);
    BuillCmdData((BYTE*)&m_unCalItem,sizeof(m_unCalItem),CMD_CAL_ZERO_DEV);
	SetCmdCtrlStat(CTRL_CAL_ZERO_SND,CMD_ST_SND);
}

UINT8 CSwitModule::GetCalZreoBak(void)
{
    return m_unCalZeroBak;
}

void CSwitModule::UpDevErrorInfo(void* pDevErrInfo)
{
    if(m_pDevUpErrInfo.unInfoLen)
    {
	    DevUpErrInfo* pUpDevErrInfo = (DevUpErrInfo*)pDevErrInfo;
		memcpy(pUpDevErrInfo,(BYTE*)&m_pDevUpErrInfo,sizeof(m_pDevUpErrInfo));
		memset(&m_pDevUpErrInfo,0,sizeof(m_pDevUpErrInfo));
    }
}

#define SLAVE_INFO_SIZE 2097152//1024*1024*2
void CSwitModule::RevDevErrorInfo(char *pRevBuf)
{
    //printf("CSwitModule::RevDevErrorInfo DevId:%d \r\n",m_unDevID);
    if(pRevBuf[0] < MAX_INFO_SIZE)
    {
        DateTime dtCreate;
		UINT8 unTimeLen = 0;
		UINT8 unCurrLen = 0;
		char unSaveBuf[255];
		FILE *SlaveInfoFile;
		int unSlaveSize = 0;
		
		GetDateTime(&dtCreate);
		QString strDateTime = DateTimeToString(&dtCreate, true);
		unTimeLen = strDateTime.length();
		strcpy(unSaveBuf, (char*)strDateTime.toStdString().c_str());
		unSaveBuf[unTimeLen] = ' ';
		unCurrLen = strlen(unSaveBuf);
		pRevBuf[pRevBuf[0]+1] = '\n';
        strcpy(unSaveBuf+unCurrLen,pRevBuf);
		SlaveInfoFile = fopen("/home/SlaveInfo/SlaveFile.txt","a+");
		unCurrLen = strlen(unSaveBuf);
		unSaveBuf[unCurrLen] = '\n';
		fprintf(SlaveInfoFile,"%s",unSaveBuf);
		fflush(SlaveInfoFile);
		fseek(SlaveInfoFile, 0L, SEEK_END);
		unSlaveSize = ftell(SlaveInfoFile);
		fclose(SlaveInfoFile);
		//printf("----------------unSlaveSize:%d-------------\r\n",unSlaveSize);

		if(unSlaveSize >= SLAVE_INFO_SIZE)//2097152
		{
		    SystemEx("mv /home/SlaveInfo/SlaveFile.txt /home/SlaveInfo/SlaveFile_old.txt");
			//SystemEx("rm -r /home/SlaveInfo/SlaveFile.txt");
		}
		
		
        //GetDateTime(&m_pDevUpErrInfo.dtSave);
		//memcpy(&m_pDevUpErrInfo.pDevErrInfo, pRevBuf+1,pRevBuf[0]);
		//m_pDevUpErrInfo.unInfoLen = pRevBuf[0];
    }
	else
	{
	    printf("Err-------devID:%d unInfoLen:%d \r\n",m_unDevID, pRevBuf[0]);
	}

}

