//#include "includes.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "cuartsocket.h"
#include "cdevcmdhandler.h"
#include "ccmddataqueue.h"

CUARTSocket::CUARTSocket(CSocketHandler* pSktHandler) : CSocket(pSktHandler)
{
    m_pCmdDataQueue = new CCmdDataQueue(50);
    m_pDevCmdHander =  NULL;
    ClearCmdData();
    ClearRecvDataBuf();
    memset(m_strComPort,0,sizeof(m_strComPort));
    m_unMaxCmdTimer = MAX_CMD_TIME_OUT_MS;
	m_RevSocket = -1;
}

CUARTSocket::~CUARTSocket()
{
    delete m_pCmdDataQueue;
    ResetPort();
}

void CUARTSocket::ResetPort()
{
    if(GetSocket()!=INVALID_SOCKET)
    {
        tcsetattr(GetSocket(), TCSAFLUSH, &m_oldTermios);
    }
}

void CUARTSocket::WriteString(const char* pStrInfo)
{
    if(-1==write(GetSocket(),pStrInfo,strlen(pStrInfo)))
    {
        if(EAGAIN!=Errno&&EWOULDBLOCK!=Errno)
        {
            ShowInfo("Write RS485 Data Error");
        }
    }
}

void CUARTSocket::SendPktData(BYTE* pDataBuf,UINT32 unDataLen)
{
    UINT32 unSrcIndex = 0;
    UINT32 unDstIndex = 0;
    m_pSndBuf[unDstIndex++] = 0xFF;
    m_pSndBuf[unDstIndex++] = 0xFF;
    while(unSrcIndex < unDataLen)
    {
        if(pDataBuf[unSrcIndex]>=0xFD)
        {
            m_pSndBuf[unDstIndex++] = 0xFD;
            m_pSndBuf[unDstIndex++] = 0xFF-pDataBuf[unSrcIndex++];
        }
        else
        {
            m_pSndBuf[unDstIndex++] = pDataBuf[unSrcIndex++];
        }
    }
    m_pSndBuf[unDstIndex++] = 0xFE;
    m_pSndBuf[unDstIndex++] = 0xFE;
    write(GetSocket(),m_pSndBuf,unDstIndex);
/**/
	printf("-nSnd-----------------------------------------------\r\n");
    for(UINT16 i = 0; i < unDstIndex; i++)
    {
        printf("%02x ",m_pSndBuf[i]);
    }
	printf("\r\n");

}

void CUARTSocket::ClearRecvDataBuf()
{
    memset(&m_uartDataBuf,0,sizeof(UartDataBuf));
    m_uartDataBuf.bLastChar  = 0;
    m_uartDataBuf.unDataPos  = 0;
    m_uartDataBuf.bRcvdFlag  = false;
}

bool CUARTSocket::OpenDev(char* pDevStr,UINT32 unBrdRate)
{
    if(INVALID_SOCKET!=GetSocket())
    {
        Close();
    }
    m_socket = open(pDevStr, O_RDWR|O_NOCTTY|O_NONBLOCK);
    if(m_socket < 0)
    {
        LogError(Errno, StrError(Errno),"open in UARTScoekt");
        return false;
    }
    if(strlen(pDevStr)<MAX_COMPORT_SIZE)
    {
        strcpy((char*)m_strComPort,pDevStr);
    }
    else
    {
        printf("Comport String to long!-->%s\r\n",pDevStr);
    }
    return SetUARTPortPrm(GetUARTBrd(unBrdRate));
}
void CUARTSocket::RecvDataFrmUART(BYTE bValue)
{
    if(false == m_uartDataBuf.bRcvdFlag)
    {
        if(0xFF == bValue||0x00 == m_uartDataBuf.unDataPos)
        {
            m_uartDataBuf.unDataPos = 0;
            //数据开始标记
            if(0xFF == bValue)
            {
                m_uartDataBuf.pDataBuf[0] = bValue;
                m_uartDataBuf.unDataPos++;
            }
        }
        else if(0xFF == m_uartDataBuf.pDataBuf[0] && m_uartDataBuf.unDataPos < MAX_RCV_BUF_SIZE)
        {
            if(0xFE == bValue)
            {
                //数据结束标记
                m_uartDataBuf.bRcvdFlag = true;
                m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos++] = bValue;
            }
            else
            {
                if(m_uartDataBuf.unDataPos > 1 && 0xFD == m_uartDataBuf.bLastChar)
                {
                    if(0x00 == bValue)
                    {
                        m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos - 1] = 0xFF;
                    }
                    else if(0x01 == bValue)
                    {
                        m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos - 1] = 0xFE;
                    }
                    else if(0x02 == bValue)
                    {
                        m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos - 1] = 0xFD;
                    }
                    else
                    {
                        m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos++] = bValue;
                    }
                }
                else
                {
                    m_uartDataBuf.pDataBuf[m_uartDataBuf.unDataPos++] = bValue;
                }
            }
        }
        else
        {
            m_uartDataBuf.unDataPos   = 0;
            m_uartDataBuf.pDataBuf[0] = 0;
        }
    }
    m_uartDataBuf.bLastChar = bValue;
}

UINT32 CUARTSocket::GetUARTBrd(UINT32 unBrdVal)
{
    UINT32 unReturnVal;
    if(115200==unBrdVal)
    {
        unReturnVal = B115200;
    }
    else if(57600==unBrdVal)
    {
        unReturnVal = B57600;
    }
    else if(38400==unBrdVal)
    {
        unReturnVal = B38400;
    }
    else if(19200==unBrdVal)
    {
        unReturnVal = B19200;
    }
    else if(9600==unBrdVal)
    {
        unReturnVal = B9600;
    }
    else if(4800==unBrdVal)
    {
        unReturnVal = B4800;
    }
    else if(2400==unBrdVal)
    {
        unReturnVal = B2400;
    }
    else if(1200==unBrdVal)
    {
        unReturnVal = B1200;
    }
    else
    {
        unReturnVal = B115200;
    }
    return unReturnVal;
}

bool CUARTSocket::SetUARTPortPrm(UINT32 unBaudRateVal)
{
    struct termios	buf;
    if (tcgetattr(GetSocket(), &buf) < 0)
    {
        ShowInfo("Get UART Param Error");
        return(false);
    }
    m_oldTermios = buf; /* structure copy */

    cfsetispeed(&buf, unBaudRateVal);    // set baud rates
    cfsetospeed(&buf, unBaudRateVal);
    /*
     * Echo off, canonical mode off, extended input
     * processing off, signal chars off.
     */
    buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    /*
     * No SIGINT on BREAK, CR-to-NL off, input parity
     * check off, don't strip 8th bit on input, output
     * flow control off.
     */
    buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    /*
     * Clear size bits, parity checking off.
     */
    buf.c_cflag &= ~(CSIZE | PARENB);

    /*
     * Set 8 bits/char.
     */
    buf.c_cflag |= CS8;
    buf.c_cflag |=CREAD;
    buf.c_cflag |=CLOCAL;

    /*
     * Output processing off.
     */
    buf.c_oflag &= ~(OCRNL | ONLCR | ONLRET |ONOCR | OFILL | OLCUC | OPOST);
    /*
     * Case B: 1 byte at a time, no timer.
     */
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 100;
    if (tcsetattr(GetSocket(), TCSAFLUSH, &buf) < 0)
    {
        ShowInfo("Set UART Param Error");
        return(false);
    }

    /*
     * Verify that the changes stuck. tcsetattr can return 0 on
     * partial success.
     */
    if (tcgetattr(GetSocket(), &buf) < 0)
    {
        ShowInfo("Check UART Param Error");
        tcsetattr(GetSocket(), TCSAFLUSH, &m_oldTermios);
        return(false);
    }
    /*
    if ((buf.c_lflag & (ECHO | ICANON | IEXTEN | ISIG)) ||
        (buf.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON)) ||
        (buf.c_cflag & (CSIZE | PARENB | CS8)) != CS8 ||
        (buf.c_oflag & OPOST) || buf.c_cc[VMIN] != 1 ||
        buf.c_cc[VTIME] != 0)
    {
        ShowInfo("Open Error4");
        tcsetattr(GetSocket(), TCSAFLUSH, &m_oldTermios);
        return(false);
    }
    */
    return (true);
}

void CUARTSocket::OnRead()
{
    
    int nRcv = read(GetSocket(),m_pRcvBuf, MAX_RCV_BUF_SIZE);

	/**/
	printf("-nRcv:%d-----------------------------------------------\r\n",nRcv);

    for(UINT8 i = 0; i < nRcv; i++)
    {
        printf("%02x ",m_pRcvBuf[i]);
    }
	printf("\r\n");
	
    if (nRcv > 0)
    {
        //BufToHexString(m_pRcvBuf,nRcv);
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
            ProcessUARTRecvData(&(m_uartDataBuf.pDataBuf[1]),m_uartDataBuf.unDataPos - 2);
            ClearRecvDataBuf();
        }
    }
    else
    {
        ShowInfo("abnormal value from recv");
    }
}

bool CUARTSocket::IsEmptyCmd(void)
{
    return m_pCmdDataQueue->IsEmpty();
}

void CUARTSocket::SendCmdData(void)
{
    UINT32 unDataLen;
    UartPacketHead*  pUartPktHead = (UartPacketHead*)m_pCmdBuf;
    pUartPktHead->unCmdID 	= m_cmdData.unCmdID;
    pUartPktHead->unDevID 	= m_cmdData.unDevID;
	pUartPktHead->unSndID 	= m_cmdData.unSndID;

	//if(pUartPktHead->unCmdID == 0x70)
        //printf("SendCmdID:%u DevID:%u unSndID:%u \r\n",m_cmdData.unCmdID,m_cmdData.unDevID,m_cmdData.unSndID);
    if(m_cmdData.unCmdDataLen>0)
    {
        memcpy(&m_pCmdBuf[sizeof(UartPacketHead)],m_cmdData.pCmdData,m_cmdData.unCmdDataLen);
    }
    unDataLen = sizeof(UartPacketHead)+m_cmdData.unCmdDataLen;
    pUartPktHead->unDataLen = ntohs(unDataLen);
    pUartPktHead->unCRC = 0;
    pUartPktHead->unCRC = ntohs(CreateCRCCheckSum(m_pCmdBuf,unDataLen));
    SendPktData(m_pCmdBuf,unDataLen);
    m_unMsTimer = m_unMaxCmdTimer;
}

void CUARTSocket::SendNextCmd(void)
{
    if(true==m_pCmdDataQueue->GetCmdData(&m_cmdData))
    {
        SendCmdData();
		printf("-------entr CUARTSocket::SendNextCmd 11\r\n");
    }
}
void CUARTSocket::ProcessUARTRecvData(BYTE* pDataBuf,UINT16 unDataSize)
{
    UINT16 unIndex;
    UINT16 unCheckSum;
    UINT16 unDataPos = sizeof(UartPacketHead);
    UartPacketHead*  pPktHead = (UartPacketHead*)pDataBuf;
    UINT16 unDataLen = ntohs(pPktHead->unDataLen);
    if(unDataLen != unDataSize||unDataSize<sizeof(UartPacketHead))
    {
        struct tm tp;
        time_t t = time(NULL);
        localtime_r(&t, &tp);
        printf("\r\n---->%d-%02d-%02d %02d:%02d:%02d\r\n",
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
    }
    unCheckSum = htons(pPktHead->unCRC);
    pPktHead->unCRC = 0;
	/*
	for(UINT16 i = 0; i < unDataSize; i++)
		printf("%02X ",pDataBuf[i]);
	printf("\r\n");*/
	
	UINT16 unRvcSum = CreateCRCCheckSum(pDataBuf,unDataSize);
    //if(unCheckSum != CreateCRCCheckSum(pDataBuf,unDataSize))
    if(unCheckSum != unRvcSum)
    {
        printf("CheckSum Error unCheckSum:%d unRvcSum:%d \r\n",unCheckSum,unRvcSum);
        ShowInfo("CheckSum Error");
        return;
    }
    //分发数据包给子设备
    if(NULL != m_pDevCmdHander)
    {
        bool bReturn;
        unDataSize -= unDataPos;
        //printf("Rcv Data!\n");
        bReturn = m_pDevCmdHander->DataParserByDev(m_RevSocket,\
                                pPktHead->unDevID,\
                                pPktHead->unCmdID,\
                                &pDataBuf[unDataPos],\
                                unDataSize);
        /*
        printf("UART:CmdID:%u DevID:%u RSP:CmdID:%u DevID:%u DataSize:%u\n",\
               m_cmdData.unCmdID,m_cmdData.unDevID,\
               pPktHead->unCmdID,pPktHead->unDevID,\
               unDataSize);*/
        if(true==bReturn&&\
           (pPktHead->unCmdID>0x7F)&&\
           (m_cmdData.unCmdID==(0x7F&pPktHead->unCmdID))&&\
           (m_cmdData.unDevID==pPktHead->unDevID))
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

void CUARTSocket::AddCmdData(CmdData* pCmdData)
{
    m_pCmdDataQueue->AddCmdData(pCmdData);
}

void CUARTSocket::OnMsTimer(UINT32 unMsCount)
{
    if(m_unMsTimer > unMsCount)
    {
        m_unMsTimer -= unMsCount;
    }
    else
    {
        m_unMsTimer = 0;
    }
    if(0==m_unMsTimer)
    {
        //处理命令超时
        if(NULL != m_pDevCmdHander)
        {
            if(INVALID_DEV_CMD_ID != m_cmdData.unCmdID)
            {
                printf("-------------------------------Cmd Tmt! DevID:%u\n",m_cmdData.unDevID);
                m_pDevCmdHander->OnCmdTimeout(m_cmdData.unDevID);
                m_cmdData.unCmdID = INVALID_DEV_CMD_ID;
            }
			else
			{
				//printf("---------------------------------unCmdID:%d------\r\n",m_cmdData.unCmdID);
			}
        }
		else
		{
		    printf("---------------------------------NULL != m_pDevCmdHander------\r\n");
		}
        //发送下一条命令
        SendNextCmd();
    }
}

void CUARTSocket::SetDevCmdHander(CDevCmdHandler* pDevCmdHander)
{
    m_pDevCmdHander = pDevCmdHander;
}

void CUARTSocket::ClearCmdData(void)
{
    //printf("Clear CmdID\n");
    m_cmdData.unCmdID = INVALID_DEV_CMD_ID;
    m_cmdData.unDevID = INVALID_DEV_ID;
	m_cmdData.unSndID = INVALID_DEV_ID;
    m_cmdData.unCmdDataLen = 0;
}

bool CUARTSocket::IsSamePort(char* pstrComPort)
{
    if(0==strcmp(m_strComPort,pstrComPort))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CUARTSocket::SetMaxCmdTimer(UINT32 unMsCount)
{
    m_unMaxCmdTimer = unMsCount;
}

bool CUARTSocket::FindDevCmd(UINT32 unDevID)
{
    return m_pCmdDataQueue->FindDevCmd(unDevID);
}
