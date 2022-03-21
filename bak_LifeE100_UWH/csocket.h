#ifndef CSOCKET_H
#define CSOCKET_H

#include <ctype.h>
#include <memory>
#include <map>
#include <string>
#include <cstring>
#include <errno.h>
#include <arpa/inet.h>
#include "includes.h"


typedef int SOCKET;
#define Errno errno
#define StrError strerror

#define INVALID_SOCKET  -1
#define SOCKET_ERROR    -1

class CErrInfo;
class CSocketHandler;
class SocketAddress;
class CWorkThread;

class CSocket
{
public:
    CSocket(CSocketHandler*pSktHandler);
    virtual ~CSocket();
    void SetWorkThread(CWorkThread* pWrkThread);
    CSocketHandler* GetHandler(void);
    bool   CreateSocket(void);
    bool CreateUdpSocket(void);
    SOCKET GetSocket(void);
    bool SetNonblocking(void);
    void BufToHexString(unsigned char* pBuf, unsigned int unDataLen);//long
    virtual bool IsConnected(void);
    virtual void OnMsTimer(unsigned int unMsCount);//long
    virtual void OnSelectTimeout(void);
    virtual void OnRead(void);
    virtual void OnWrite(void);
    virtual void OnException(void);
    virtual void OnDisConnect(void);
public:
    virtual void Close();
    virtual int  SendBuf(BYTE *pDataBuf,unsigned int ulBufSize);//long
    void ShowInfo(std::string strInfo);
    void LogError(int nErrno, const char* pErrInfo,const char* pUsrInfo = NULL);
protected:
    CSocketHandler* m_pSktHandler;
    CWorkThread* m_pWrkThread;
    CErrInfo* m_pErrInfo;
    SOCKET m_socket;
	//UINT32 m_unSndRcvLen;//debug
};

#endif // CSOCKET_H
