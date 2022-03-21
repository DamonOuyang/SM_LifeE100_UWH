#include "CSocket.h"
#include "CErrInfo.h"
#include "CSocketHandler.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "CWorkThread.h"


CSocket::CSocket(CSocketHandler* pSktHandler)
    :m_pSktHandler(pSktHandler)
    ,m_pWrkThread(NULL)
    ,m_pErrInfo(NULL)
    ,m_socket(INVALID_SOCKET)
{
    m_pErrInfo = new CErrInfo();
}

CSocket::~CSocket()
{
    if (INVALID_SOCKET!=m_socket)
    {
        Close();
    }
    if(NULL == m_pErrInfo)
    {
        delete m_pErrInfo;
    }
}
void CSocket::Close(void)
{
    if (INVALID_SOCKET==m_socket)
    {
        return ;
    }
    m_pSktHandler->DelSocket(this);
    if (-1 == close(m_socket))
    {
        LogError(Errno, StrError(Errno));
    }
    m_socket = INVALID_SOCKET;
}

void CSocket::LogError(int nErrno, const char* pErrInfo,const char* pUsrInfo)
{
    if(NULL!=m_pErrInfo)
    {
        m_pErrInfo->ShowInfo(pUsrInfo,nErrno,pErrInfo);
    }
}

void CSocket::SetWorkThread(CWorkThread* pWrkThread)
{
    m_pWrkThread = pWrkThread;
}

CSocketHandler* CSocket::GetHandler(void)
{
    return m_pSktHandler;
}

bool CSocket::CreateSocket(void)
{
    Close();
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET==m_socket)
    {
        LogError(Errno, StrError(Errno),"socket");
        return false;
    }
    return true;
}

bool CSocket::CreateUdpSocket(void)
{
    Close();
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (INVALID_SOCKET==m_socket)
    {
        LogError(Errno, StrError(Errno),"socket");
        return false;
    }
    return true;
}
SOCKET CSocket::GetSocket(void)
{
    return m_socket;
}

bool CSocket::SetNonblocking(void)
{
    int nflags = fcntl (m_socket, F_GETFL, 0);
    if(nflags<0)
    {
        LogError(Errno, StrError(Errno),"SetNonblocking");
        return false;
    }
    nflags |= O_NONBLOCK;
    if (fcntl(m_socket, F_SETFL, nflags)<0)
    {
        LogError(Errno, StrError(Errno),"SetNonblocking");
        return false;
    }
    return true;
}

void CSocket::BufToHexString(unsigned char* pBuf, unsigned int unDataLen)//long
{
    unsigned int unIndex;
    char strInfo[10];
    for(unIndex = 0; unIndex < unDataLen; unIndex++)
    {
        sprintf(strInfo,"%02X ",pBuf[unIndex]);
        ShowInfo(strInfo);
    }
}

bool CSocket::IsConnected(void)
{
    return false;
}

void CSocket::OnRead(void)
{

}

void CSocket::OnWrite(void)
{

}

void CSocket::OnException(void)
{

}

void CSocket::OnMsTimer(unsigned int unMsCount)//long
{
    if(0==unMsCount)
    {
        unMsCount = 0;
    }
}

void CSocket::OnSelectTimeout(void)
{

}

int CSocket::SendBuf(BYTE *pDataBuf,unsigned int ulBufSize)//long
{
    int nSndCount = 0;
    if(INVALID_SOCKET==m_socket)
    {
        return -1;
    }
    nSndCount = send(m_socket, pDataBuf, (int)ulBufSize, MSG_NOSIGNAL);
	//m_unSndRcvLen += ulBufSize; //debug
    if (-1 == nSndCount)
    {
        if (Errno != EWOULDBLOCK)
        {
            LogError(Errno, StrError(Errno),"send");
            OnDisConnect();
			//printf("-OnDisconnect-----------------------------------2\r\n");
            Close();
            return -1;
        }
        else
        {
            //数据没有发完
            //printf("Send not completed!\r\n");
            m_pSktHandler->SetSelect(this,true,true);
            return 0;
        }
    }
    else
    {
        if((unsigned int)nSndCount==ulBufSize)//long
        {
            //数据已经发完
            //printf("Send completed!\r\n");
            m_pSktHandler->SetSelect(this,true,false);
        }
        else
        {
            //数据没有发完
            printf("Send not completed!\r\n");
            m_pSktHandler->SetSelect(this,true,true);
        }
        return nSndCount;
    }
}

void CSocket::ShowInfo(std::string strInfo)
{
    if(NULL != m_pWrkThread)
    {
        m_pWrkThread->ShowStringInfo(strInfo.c_str());
    }
    else
    {
        printf("%s",strInfo.c_str());
    }
}
void CSocket::OnDisConnect(void)
{

}
