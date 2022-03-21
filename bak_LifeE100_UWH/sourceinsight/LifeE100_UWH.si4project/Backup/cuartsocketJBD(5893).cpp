#include "includes.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "CModbusSocket.h"
#include "CDevCmdHandler.h"
#include "CCmdDataQueue.h"

CModbusSocket::CModbusSocket(CSocketHandler* pSktHandler) : CUARTSocket(pSktHandler)
{
    m_pCmdDataQueue = new CCmdDataQueue(50);
    m_pDevCmdHander =  NULL;
    ClearCmdData();
    ClearRecvDataBuf();
    memset(m_strComPort,0,sizeof(m_strComPort));
    //m_unMaxCmdTimer = CD_MAX_CMD_TIME_OUT_MS;
    m_RevSocket = -1;
}

CModbusSocket::~CModbusSocket()
{
    delete m_pCmdDataQueue;
    ResetPort();
}
/*
void CModbusSocket::ResetPort()
{
}

void CModbusSocket::WriteString(const char* pStrInfo)
{
}
*/
void CModbusSocket::SendPktData(BYTE* pDataBuf,UINT32 unDataLen)
{
    UINT32 unSrcIndex = 0;
    UINT32 unDstIndex = 0;
    while(unSrcIndex < unDataLen)
    {
        m_pSndBuf[unDstIndex++] = pDataBuf[unSrcIndex++];
    }
    write(GetSocket(),m_pSndBuf,unDstIndex);
}
/*
void CModbusSocket::ClearRecvDataBuf()
{
    memset(&m_uartDataBuf,0,sizeof(UartDataBuf));
    m_uartDataBuf.bLastChar  = 0;
    m_uartDataBuf.unDataPos  = 0;
    m_uartDataBuf.bRcvdFlag  = FALSE;
}

bool CModbusSocket::OpenDev(char* pDevStr,UINT32 unBrdRate)
{
}
*/
void CModbusSocket::RecvDataFrmUART(BYTE bValue)
{
    if(FALSE == m_uartDataBuf.bRcvdFlag)
    {		
        if(0x00 == m_uartDataBuf.unDataPos)
        {
            //m_uartDataBuf.unDataPos = 0;
            //数据开始标记
            if(DC_DEV_ID == bValue)
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
        else if(DC_DEV_ID == m_uartDataBuf.pDataBuf[0] && m_uartDataBuf.unDataPos < MAX_RCV_BUF_SIZE-48)
        {
            m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos++] = bValue;
			
            if(m_uartDataBuf.pDataBuf[1] == MODBUS_READ_CODE)//读命令 ack
            {
           // printf("rev -------------------------0x03 \r\n");
				if(m_uartDataBuf.unDataPos == 3)
				{
					unGetCmdLen = m_uartDataBuf.pDataBuf[2];
				}

				if((unGetCmdLen+5) == m_uartDataBuf.unDataPos)
				{
				    m_uartDataBuf.bRcvdFlag = TRUE;
				}
            }
			else if(m_uartDataBuf.pDataBuf[1] == MODBUS_WRITE_CODE)//写命令ack
			{
			//printf("rev -------------------------0x10 \r\n");
				if(8 == m_uartDataBuf.unDataPos)
				{
				    m_uartDataBuf.bRcvdFlag = TRUE;
				}
			}
			else if(m_uartDataBuf.pDataBuf[1] == MODBUS_CTRL_CODE)//功能命令ack
			{
			    //printf("rev -------------------------0x05 \r\n");
				if(8 == m_uartDataBuf.unDataPos)
				{
				    m_uartDataBuf.bRcvdFlag = TRUE;
				}
			}
			else if(m_uartDataBuf.pDataBuf[1]&0x80)//命令异常ack
			{
			    //printf("rev -------------------------0x80 \r\n");
				if(5 == m_uartDataBuf.unDataPos)
				{
				    m_uartDataBuf.bRcvdFlag = TRUE;
				}
			}
			else
			{
			    printf("rev ------pDataBuf[1]:%d---------- \r\n",m_uartDataBuf.pDataBuf[1]);
				ClearRecvDataBuf();
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
UINT32 CModbusSocket::GetUARTBrd(UINT32 unBrdVal)
{
}

bool CModbusSocket::SetUARTPortPrm(UINT32 unBaudRateVal)
{
}
*/
void CModbusSocket::OnRead()
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
        if(TRUE == m_uartDataBuf.bRcvdFlag)
        {
            ProcessUARTRecvData(&(m_uartDataBuf.pDataBuf[0]),m_uartDataBuf.unDataPos);
            ClearRecvDataBuf();
        }
    }
    else
    {
        ShowInfo("abnormal value from recv");
    }
}

void CModbusSocket::SndCmdPkt(BYTE* pDataBuf,UINT32 unDataLen,UINT32 unDevID)
{
    //执行服务器发来的命令;
   UINT16 unCRC = 0;

    //执行服务器发来的命令;
    ModbusPacketHead*  pUartPktHead = (ModbusPacketHead*)m_pCmdBuf;
    pUartPktHead->unCmdID 	= MODBUS_READ_CODE;
    pUartPktHead->unDevID 	= (UINT8)unDevID;
    if((unDataLen+sizeof(ModbusPacketHead))<MAX_SND_BUF_SIZE)
    {
        memcpy(&m_pCmdBuf[sizeof(ModbusPacketHead)],pDataBuf,unDataLen);
        unDataLen += sizeof(ModbusPacketHead);
		unCRC = ntohs(CreateCRCCheckSum(m_pCmdBuf,unDataLen));
		unDataLen+=2;
		m_pCmdBuf[unDataLen-2] = (unCRC >> 8) & 0xFF;
		m_pCmdBuf[unDataLen-1] = unCRC & 0xFF;
        SendPktData(m_pCmdBuf,unDataLen);
    }
    else
    {
        printf("Send Packet size over send buffer!!!\r\n");
    }

}
/*
bool CModbusSocket::IsEmptyCmd(void)
{
}
*/
void CModbusSocket::SendCmdData(void)
{
    UINT32 unDataLen;
	UINT16 unCRC = 0;
    ModbusPacketHead*  pUartPktHead = (ModbusPacketHead*)m_pCmdBuf;
    pUartPktHead->unCmdID 	= m_cmdData.unCmdID;
    pUartPktHead->unDevID 	= (UINT8)m_cmdData.unDevID;
    //printf("1-------------------------SendCmdID:%u DevID:%u \r\n",m_cmdData.unCmdID,m_cmdData.unDevID);
    if(m_cmdData.unCmdDataLen>0)
    {
        memcpy(&m_pCmdBuf[sizeof(ModbusPacketHead)],m_cmdData.pCmdData,m_cmdData.unCmdDataLen);
    }
    unDataLen = sizeof(ModbusPacketHead)+m_cmdData.unCmdDataLen;
	unCRC = ntohs(CalculateCRC16(m_pCmdBuf,unDataLen));
	unDataLen+=2;
	m_pCmdBuf[unDataLen-2] = (unCRC >> 8) & 0xFF;
	m_pCmdBuf[unDataLen-1] = unCRC & 0xFF;

	/*
	for(UINT8 i = 0; i < unDataLen; i++)
	{
	    printf("%02x ",m_pCmdBuf[i]);
	}
	printf("\r\n");*/
	

    SendPktData(m_pCmdBuf,unDataLen);
    m_unMsTimer = CD_MAX_CMD_TIME_OUT_MS;
}
/*
void CModbusSocket::SendNextCmd(void)
{
}
*/
void CModbusSocket::ProcessUARTRecvData(BYTE* pDataBuf,UINT16 unDataSize)
{
    //char   dt[100];
    //UINT16 unIndex;
    UINT16 unCheckSum;
    UINT16 unDataPos = sizeof(ModbusPacketHead);
    ModbusPacketHead*  pPktHead = (ModbusPacketHead*)pDataBuf;
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
    unCheckSum = ntohs(unCheckSum);
    if(	unCheckSum != CalculateCRC16(pDataBuf,unDataSize-2))
    {
        printf("CheckSum Error :unCheckSum=%u\r\n",unCheckSum);
		
        ShowInfo("CheckSum Error");
        return;
    }
    //分发数据包给子设备
    if(NULL != m_pDevCmdHander)
    {
        bool bReturn;
		if(unDataSize > 5 && (pDataBuf[0]&0x80) == 0)
		{
	        unDataSize -= unDataPos;
	        bReturn = m_pDevCmdHander->DataParserByDev(m_RevSocket,\
	                                pPktHead->unDevID,\
	                                pPktHead->unCmdID,\
	                                &pDataBuf[unDataPos],\
	                                unDataSize-2);
		}
		else//命令异常
		{
	        bReturn = m_pDevCmdHander->DataParserByDev(m_RevSocket,\
	                                pPktHead->unDevID,\
	                                pPktHead->unCmdID,\
	                                &pDataBuf[0],\
	                                unDataSize-2); 
		}
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
void CModbusSocket::AddCmdData(CmdData* pCmdData)
{
}


void CModbusSocket::OnMsTimer(UINT32 unMsCount)
{
    CUARTSocket::OnMsTimer(unMsCount);
	//printf("CModbusSocket::OnMsTimer====================\r\n");
}*/
/*


void CModbusSocket::SetDevCmdHander(CDevCmdHandler* pDevCmdHander)
{
}

void CModbusSocket::ClearCmdData(void)
{
}

bool CModbusSocket::IsSamePort(char* pstrComPort)
{

}

void CModbusSocket::SetMaxCmdTimer(UINT32 unMsCount)
{
}
*/
