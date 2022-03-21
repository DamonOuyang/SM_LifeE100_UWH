#include "includes.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "cuartsocketBQ40z50.h"
#include "CDevCmdHandler.h"
#include "CCmdDataQueue.h"

CUARTSocketBQ40Z50::CUARTSocketBQ40Z50(CSocketHandler* pSktHandler) : CUARTSocket(pSktHandler)
{
    m_pCmdDataQueue = new CCmdDataQueue(50);
    m_pDevCmdHander =  NULL;
    ClearCmdData();
    ClearRecvDataBuf();
    memset(m_strComPort,0,sizeof(m_strComPort));
    //m_unMaxCmdTimer = CD_MAX_CMD_TIME_OUT_MS;
    m_RevSocket = -1;
	TmpLen = 0;
}

CUARTSocketBQ40Z50::~CUARTSocketBQ40Z50()
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
void CUARTSocketBQ40Z50::SendPktData(BYTE* pDataBuf,UINT32 unDataLen)
{
    UINT32 unSrcIndex = 0;
    UINT32 unDstIndex = 0;
    while(unSrcIndex < unDataLen)
    {
        m_pSndBuf[unDstIndex++] = pDataBuf[unSrcIndex++];
    }
	//CtrlRs485RvcSnd(1);
	//for(UINT16 i = 0; i < 2000;i++);
    write(GetSocket(),m_pSndBuf,unDstIndex);
	//for(UINT16 i = 0; i < 2000;i++);
	//CtrlRs485RvcSnd(0);
	//for(UINT16 i = 0; i < 10000;i++);
	//system("echo 0 > /sys/class/gpio/gpio68/value");
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
void CUARTSocketBQ40Z50::RecvDataFrmUART(BYTE bValue)
{
    if(false == m_uartDataBuf.bRcvdFlag)
    {		
        if(0x00 == m_uartDataBuf.unDataPos)
        {
            //m_uartDataBuf.unDataPos = 0;
            //数据开始标记
            if(0x01 == bValue)
            {
                m_uartDataBuf.pDataBuf[0] = bValue;
                m_uartDataBuf.unDataPos++;
            }
			else
			{
			    //printf("rev ------------%02X-------------<2 \r\n",bValue);
				m_uartDataBuf.unDataPos = 0;
			}
        }
        else if(0x01 == m_uartDataBuf.pDataBuf[0] && m_uartDataBuf.unDataPos < MAX_RCV_BUF_SIZE)
        {
            if(0x0A == bValue)
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
			printf("unDataPos:%d > 8 or DC_DEV_ID != pDataBuf[0]:%d-------\r\n",m_uartDataBuf.unDataPos,m_uartDataBuf.pDataBuf[0]);
			m_uartDataBuf.unDataPos   = 0;
            m_uartDataBuf.pDataBuf[0] = 0;
        }
    }
    m_uartDataBuf.bLastChar = bValue;

	if(m_uartDataBuf.unDataPos > 8)
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
void CUARTSocketBQ40Z50::OnRead()
{
    int nRcv = read(GetSocket(),m_pRcvBuf, MAX_RCV_BUF_SIZE);

	/*
	printf("-nRcv:%d----m_pRcvBuf[0]:%02X-------------sock:%d------------------------------\r\n",nRcv,m_pRcvBuf[0],GetSocket());
		
    for(UINT8 i = 0; i < nRcv; i++)
    {
        printf("%02X ",m_pRcvBuf[i]);
    }
	printf("\r\n");*/	
	
    if (nRcv > 0)
    {	
        m_RevSocket = GetSocket();
        UINT16 unFrmPos = 0;
        UINT16 unEndPos = nRcv;
        while(unFrmPos < unEndPos)
        {
            RecvDataFrmUART(m_pRcvBuf[unFrmPos]);
            unFrmPos++;
        }
        if(true == m_uartDataBuf.bRcvdFlag)
        {
            TmpLen = 0;
            ProcessUARTRecvData(&(m_uartDataBuf.pDataBuf[0]),m_uartDataBuf.unDataPos);
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
void CUARTSocketBQ40Z50::SendCmdData(void)
{
    UINT32 unDataLen;
	UINT16 unCRC = 0;

	m_pCmdBuf[0] = m_cmdData.unDevID;
	m_pCmdBuf[1] = 0x17;//IIC地址
	m_pCmdBuf[2] = m_cmdData.unCmdID;
	m_pCmdBuf[3] = 0x02;
	m_unSndCmd = m_cmdData.unCmdID;
	
    unDataLen = 4 + m_cmdData.unCmdDataLen;


	/*
	for(UINT8 i = 0; i < unDataLen; i++)
	{
	    printf("%02x ",m_pCmdBuf[i]);
	}
	printf("\r\n");
	*/

    SendPktData(m_pCmdBuf,unDataLen);
    m_unMsTimer = 2000;
}
/*
void CUARTSocketJBD::SendNextCmd(void)
{
}
*/
void CUARTSocketBQ40Z50::ProcessUARTRecvData(BYTE* pDataBuf, UINT16 unDataSize)
{
    UINT16 unCheckSum;
    Bq40PacketHead*  pPktHead;// = (JbdPacketHead*)pDataBuf;
    pPktHead->unDevID = pDataBuf[0];
	pPktHead->unCmdID = m_unSndCmd;



    //分发数据包给子设备
    if(NULL != m_pDevCmdHander)
    {
        bool bReturn;

        bReturn = m_pDevCmdHander->DataParserByDev(m_RevSocket,\
                                pPktHead->unDevID,\
                                pPktHead->unCmdID,\
                                &pDataBuf[1],\
                                unDataSize-2);//减去返回字节01 0A
  
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

