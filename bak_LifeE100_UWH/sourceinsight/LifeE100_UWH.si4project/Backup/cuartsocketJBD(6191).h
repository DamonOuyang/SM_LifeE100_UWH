#ifndef CUARTSOCKETJBD_H
#define CUARTSOCKETJBD_H

#include "Includes.h"
#include <termios.h>
//#include "cbasicdevice.h"
//#include "CSocket.h"
#include "cuartsocket.h"


#define MAX_SND_BUF_SIZE        2048
#define MAX_RCV_BUF_SIZE        2048

#define  CD_MAX_CMD_TIME_OUT_MS 2000
#define  CMD_RMT_DEV_EXE        0x34

#define DC_DEV_ID                0x01
//#define MODBUS_READ_CMD         0x03 //读命令
//#define MODBUS_WRITE_CMD        0x10 //写命令



#pragma pack(push,1)
typedef struct JBD_PACKET_HEAD
{
    UINT8   unStrID;//起始字节
    UINT8   unCmdID;//命令
	UINT8   unCmdStat;//回复状态
	UINT8   unCmdDatLen;//数据长度
}JbdPacketHead;
#pragma pack(pop)

typedef struct JBD_DATA_BUF
{
    BYTE pDataBuf[MAX_RCV_BUF_SIZE];
    UINT16 unDataPos;
    BOOL bRcvdFlag;
    BYTE bLastChar;
}JbdDataBuf;

//class CCmdDataQueue;
//class CDevCmdHandler;
//class DCDevice : public CBasicDevice

class CUARTSocketJBD : public CUARTSocket
{
public:
    CUARTSocketJBD(CSocketHandler* pSktHandler);
    virtual ~CUARTSocketJBD();
	//virtual void ResetPort();
	//virtual void WriteString(const char* pStrInfo);
	virtual void SendPktData(BYTE* pDataBuf,UINT32 unDataLen);
	//virtual void ClearRecvDataBuf();
	//virtual bool OpenDev(char* pDevStr,UINT32 unBrdRate);
	virtual void RecvDataFrmUART(BYTE bValue);
	//virtual UINT32 GetUARTBrd(UINT32 unBrdVal);
	//virtual bool SetUARTPortPrm(UINT32 unBaudRateVal);
	virtual void OnRead();
	//virtual bool IsEmptyCmd(void);
	virtual void SendCmdData(void);
	//virtual void SendNextCmd(void);
	virtual void ProcessUARTRecvData(BYTE* pDataBuf,UINT16 unDataSize);
	//virtual void AddCmdData(CmdData* pCmdData);	
	//virtual void OnMsTimer(UINT32 unMsCount);
	//virtual void SetDevCmdHander(CDevCmdHandler* pDevCmdHander);	
	//virtual void ClearCmdData(void);
	//virtual bool IsSamePort(char* pstrComPort);
	//virtual void SetMaxCmdTimer(UINT32 unMsCount);

private:
		/*
    struct termios  m_oldTermios;		 //place for old port settings for serial port
    BYTE  m_pSndBuf[MAX_SND_BUF_SIZE];
    BYTE  m_pCmdBuf[MAX_SND_BUF_SIZE];
    BYTE  m_pRcvBuf[MAX_RCV_BUF_SIZE];
    ModbusDataBuf  m_uartDataBuf;
    CCmdDataQueue*  m_pCmdDataQueue;
    CDevCmdHandler* m_pDevCmdHander;
    CmdData  m_cmdData;
    UINT32   m_unMsTimer;

    UINT32   m_unMaxCmdTimer; 
    
    char  m_strComPort[MAX_COMPORT_SIZE];*/

	UINT16 unGetCmdLen;
};

#endif // CUARTSOCKET_H
