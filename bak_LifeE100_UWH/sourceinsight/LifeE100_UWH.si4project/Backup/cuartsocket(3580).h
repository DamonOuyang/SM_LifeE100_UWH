#ifndef CUARTSOCKET_H
#define CUARTSOCKET_H

#include "includes.h"
#include <termios.h>
#include "cbasicdevice.h"
#include "CSocket.h"

#define MAX_SND_BUF_SIZE        4096
#define MAX_RCV_BUF_SIZE        2048

#define  MAX_CMD_TIME_OUT_MS    500
#define  CMD_RMT_DEV_EXE        0x34


#pragma pack(push,1)
typedef struct PACKET_HEAD
{
    UINT8   unDevID;
	UINT8   unSndID;
    UINT16  unDataLen;
    UINT16  unCRC;
    UINT8   unCmdID;
}UartPacketHead;
#pragma pack(pop)

typedef struct UART_DATA_BUF
{
    BYTE pDataBuf[MAX_RCV_BUF_SIZE];
    UINT16 unDataPos;
    BOOL bRcvdFlag;
    BYTE bLastChar;
}UartDataBuf;

class CCmdDataQueue;
class CDevCmdHandler;
class CUARTSocket:public CSocket
{
public:
    CUARTSocket(CSocketHandler* pSktHandler);
    virtual ~CUARTSocket();
    void SendNextCmd(void);
    bool IsEmptyCmd(void);

    void SetMaxCmdTimer(UINT32 unMsCount);


    bool OpenDev(char* pDevStr,UINT32 unBrdRate);
    void AddCmdData(CmdData* pCmdData);
    void OnMsTimer(UINT32 unMsCount);
    void SetDevCmdHander(CDevCmdHandler* pDevCmdHander);
    void WriteString(const char* pStrInfo);
    bool IsSamePort(char* pstrComPort);
    bool FindDevCmd(UINT32 unDevID);

    virtual void SendPktData(BYTE* pDataBuf,UINT32 unDataLen);
    virtual void RecvDataFrmUART(BYTE bValue);
    virtual void OnRead();
    virtual void SendCmdData(void);
    virtual void ProcessUARTRecvData(BYTE* pDataBuf,UINT16 unDataSize);
protected:
    struct termios  m_oldTermios;		 //place for old port settings for serial port
    BYTE  m_pSndBuf[MAX_SND_BUF_SIZE];
    BYTE  m_pCmdBuf[MAX_SND_BUF_SIZE];
    BYTE  m_pRcvBuf[MAX_RCV_BUF_SIZE];
    UartDataBuf  m_uartDataBuf;
    CCmdDataQueue*  m_pCmdDataQueue;
    CDevCmdHandler* m_pDevCmdHander;
    CmdData  m_cmdData;
    UINT32   m_unMsTimer;
    UINT32   m_unMaxCmdTimer;
    void ClearRecvDataBuf();
    void ResetPort();
    bool SetUARTPortPrm(UINT32 unBaudRateVal);
    UINT32 GetUARTBrd(UINT32 unBrdVal);
    void ClearCmdData(void);
    char  m_strComPort[MAX_COMPORT_SIZE];
	int   m_RevSocket;
};

#endif // CUARTSOCKET_H
