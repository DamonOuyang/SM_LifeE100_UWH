#include "includes.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "cuartsocketJBD.h"
#include "CDevCmdHandler.h"
#include "CCmdDataQueue.h"

CUARTSocketJBD::CUARTSocketJBD(CSocketHandler* pSktHandler) : CUARTSocket(pSktHandler)
{
    m_pCmdDataQueue = new CCmdDataQueue(50);
    m_pDevCmdHander =  NULL;
    ClearCmdData();
    ClearRecvDataBuf();
    memset(m_strComPort,0,sizeof(m_strComPort));
    //m_unMaxCmdTimer = CD_MAX_CMD_TIME_OUT_MS;
    m_RevSocket = -1;
}

CUARTSocketJBD::~CUARTSocketJBD()
{
    delete m_pCmdDataQueue;
    ResetPort();
}
/*
void CUARTSocketJBD::ResetPort()
{
}

void CUARTSocketJBD::WriteString(const char* pStrInfo)
{
}
*/
void CUARTSocketJBD::SendPktData(BYTE* pDataBuf,UINT32 unDataLen)
{
    UINT32 unSrcIndex = 0;
    UINT32 unDstIndex = 0;
    while(unSrcIndex < unDataLen)
    {
        m_pSndBuf[unDstIndex++] = pDataBuf[unSrcIndex++];
    }
    write(GetSocket(),m_pSndBuf,unDstIndex);
	CtrlRs485RvcSnd(0);
}
/*
void CUARTSocketJBD::ClearRecvDataBuf()
{
    memset(&m_uartDataBuf,0,sizeof(UartDataBuf));
    m_uartDataBuf.bLastChar  = 0;
    m_uartDataBuf.unDataPos  = 0;
    m_uartDataBuf.bRcvdFlag  = FALSE;
}

bool CUARTSocketJBD::OpenDev(char* pDevStr,UINT32 unBrdRate)
{
}
*/
void CUARTSocketJBD::RecvDataFrmUART(BYTE bValue)
{
    if(false == m_uartDataBuf.bRcvdFlag)
    {		
        if(0x00 == m_uartDataBuf.unDataPos)
        {
            //m_uartDataBuf.unDataPos = 0;
            //数据开始标记
            if(0xDD == bValue)
            {
                m_uartDataBuf.pDataBuf[0] = bValue;
                m_uartDataBuf.unDataPos++;
            }
			else
			{
			    printf("rev ------------%d-------------<2 \r\n",bValue);
				m_uartDataBuf.unDataPos = 0;
			}
        }
        else if(0xDD == m_uartDataBuf.pDataBuf[0] && m_uartDataBuf.unDataPos < MAX_RCV_BUF_SIZE-48)
        {
            if(0x77 == bValue)
            {
                //数据结束标记
                m_uartDataBuf.bRcvdFlag = true;
                m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos++] = bValue;
            }
			else
			{
				m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos++] = bValue;
			}
        }
        else
        {
			printf("unDataPos:%d > 2048 or DC_DEV_ID != pDataBuf[0]:%d-------\r\n",m_uartDataBuf.unDataPos,m_uartDataBuf.pDataBuf[0]);
			m_uartDataBuf.unDataPos   = 0;
            m_uartDataBuf.pDataBuf[0] = 0;
        }
    }
    m_uartDataBuf.bLastChar = bValue;

	if(m_uartDataBuf.unDataPos > 200)
	{
	    printf("m_uartDataBuf.unDataPos %d---unGetCmdLen --------------------%d\r\n",m_uartDataBuf.unDataPos,unGetCmdLen);
        ClearRecvDataBuf();
	}
}
/*
UINT32 CUARTSocketJBD::GetUARTBrd(UINT32 unBrdVal)
{
}

bool CUARTSocketJBD::SetUARTPortPrm(UINT32 unBaudRateVal)
{
}
*/
void CUARTSocketJBD::OnRead()
{
    int nRcv = read(GetSocket(),m_pRcvBuf, MAX_RCV_BUF_SIZE);
    if (nRcv > 0)
    {
        //BufToHexString(m_pRcvBuf,nRcv);
        m_RevSocket = GetSocket();
        UINT16 unFrmPos = 0;
        UINT16 unEndPos = nRcv;
        while(unFrmPos < unEndPos)
        {
            //printf("m_pRcvBuf[unFrmPos] -----%02x- \r\n",m_pRcvBuf[unFrmPos]);
            RecvDataFrmUART(m_pRcvBuf[unFrmPos]);
            unFrmPos++;
        }
		//printf(".bRcvdFlag = %d ---unDataPos = %d\r\n",m_uartDataBuf.bRcvdFlag,m_uartDataBuf.unDataPos);
        if(true == m_uartDataBuf.bRcvdFlag)
        {
            ProcessUARTRecvData(&(m_uartDataBuf.pDataBuf[0]),m_uartDataBuf.unDataPos - 1);
            ClearRecvDataBuf();
        }
    }
    else
    {
        ShowInfo("abnormal value from recv");
    }
}

/*
bool CUARTSocketJBD::IsEmptyCmd(void)
{
}
*/
void CUARTSocketJBD::SendCmdData(void)
{
    UINT32 unDataLen;
	UINT16 unCRC = 0;

	m_pCmdBuf[0] = m_cmdData.unDevID;
	m_pCmdBuf[1] = 0xA5;
	m_pCmdBuf[2] = m_cmdData.unCmdID;
	m_pCmdBuf[3] = m_cmdData.unCmdDataLen;
	
    printf("1-------------------------SendCmdID:%u DevID:%u \r\n",m_cmdData.unCmdID,m_cmdData.unDevID);
    //if(m_cmdData.unCmdDataLen > 0)
    //{
        //memcpy(&m_pCmdBuf[sizeof(JbdPacketHead)],m_cmdData.pCmdData,m_cmdData.unCmdDataLen);
    //}
    unDataLen = 4 + m_cmdData.unCmdDataLen;
	unCRC = CreateJBDCheckSum(m_pCmdBuf+2, 2);
	unDataLen += 2;
	m_pCmdBuf[unDataLen-2] = (unCRC >> 8) & 0xFF;
	m_pCmdBuf[unDataLen-1] = unCRC & 0xFF;
	m_pCmdBuf[unDataLen++] = 0x77;

	/**/
	for(UINT8 i = 0; i < unDataLen; i++)
	{
	    printf("%02x ",m_pCmdBuf[i]);
	}
	printf("\r\n");
	

    SendPktData(m_pCmdBuf,unDataLen);
    m_unMsTimer = CD_MAX_CMD_TIME_OUT_MS;
}
/*
void CUARTSocketJBD::SendNextCmd(void)
{
}
*/
void CUARTSocketJBD::ProcessUARTRecvData(BYTE* pDataBuf, UINT16 unDataSize)
{
    //char   dt[100];
    //UINT16 unIndex;
    UINT16 unCheckSum;
    UINT16 unDataPos = sizeof(JbdPacketHead);
    JbdPacketHead*  pPktHead = (JbdPacketHead*)pDataBuf;
    //UINT16 unDataLen = pDataBuf[2];

/*
    if(unDataLen != unDataSize||unDataSize<sizeof(UartPacketHead))
    {
        struct tm tp;
        time_t t = time(NULL);
        localtime_r(&t, &tp);
        printf(dt, "\r\n---->%d-%02d-%02d %02d:%02d:%02d\r\n",
            tp.tm_year + 1900,
            tp.tm_mon + 1,
            tp.tm_mday,
            tp.tm_hour,tp.tm_min,tp.tm_sec);
        for(unIndex = 0; unIndex < unDataSize; unIndex++)
        {
            printf("%02X ",pDataBuf[unIndex]);
        }
        printf("\r\n");
        printf("Packet Size Error:DataSize=%u DataLen:%u\r\n",unDataSize,unDataLen);
        return;
    }*/
    
    unCheckSum = (pDataBuf[unDataSize-2] << 8);
	unCheckSum += pDataBuf[unDataSize-1];
    //unCheckSum = ntohs(unCheckSum);
    if(unCheckSum != CreateJBDCheckSum(pDataBuf+2,unDataSize-4))
    {
        printf("CheckSum Error :unCheckSum=%u\r\n",unCheckSum);
		
        ShowInfo("CheckSum Error");
        return;
    }
    //分发数据包给子设备
    if(NULL != m_pDevCmdHander)
    {
        bool bReturn;

        unDataSize -= unDataPos;
        bReturn = m_pDevCmdHander->DataParserByDev(m_RevSocket,\
                                pPktHead->unStrID,\
                                pPktHead->unCmdID,\
                                &pDataBuf[unDataPos],\
                                unDataSize-2);//减去校验字节
        /*
        printf("UART:CmdID:%u DevID:%u RSP:CmdID:%u DevID:%u DataSize:%u\n",\
               m_cmdData.unCmdID,m_cmdData.unDevID,\
               pPktHead->unCmdID,pPktHead->unDevID,\
               unDataSize);*/
               /*
        if(true==bReturn&&\
           (pPktHead->unCmdID>0x7F)&&\
           (m_cmdData.unCmdID==(0x7F&pPktHead->unCmdID))&&\
           (m_cmdData.unDevID==pPktHead->unDevID))*/
        if(true==bReturn)
        {
            ClearCmdData();
            //SendNextCmd();
        }
        else
        {
            //数据没有对象接收，命令超时
            OnMsTimer(m_unMaxCmdTimer);
        }
    }
}
/*
void CUARTSocketJBD::AddCmdData(CmdData* pCmdData)
{
}


void CUARTSocketJBD::OnMsTimer(UINT32 unMsCount)
{
    CUARTSocket::OnMsTimer(unMsCount);
	//printf("CUARTSocketJBD::OnMsTimer====================\r\n");
}*/
/*


void CUARTSocketJBD::SetDevCmdHander(CDevCmdHandler* pDevCmdHander)
{
}

void CUARTSocketJBD::ClearCmdData(void)
{
}

bool CUARTSocketJBD::IsSamePort(char* pstrComPort)
{

}

void CUARTSocketJBD::SetMaxCmdTimer(UINT32 unMsCount)
{
}
*/
