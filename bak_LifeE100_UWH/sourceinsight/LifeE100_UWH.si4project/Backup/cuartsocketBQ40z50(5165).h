#ifndef CUARTSOCKETBQ40Z50_H
#define CUARTSOCKETBQ40Z50_H

#include "Includes.h"
#include <termios.h>
//#include "cbasicdevice.h"
//#include "CSocket.h"
#include "cuartsocket.h"


#define MAX_SND_BUF_SIZE        64
#define MAX_RCV_BUF_SIZE        8


#pragma pack(push,1)
typedef struct BQ40_PACKET_HEAD
{
    UINT8   unDevID;//起始字节
    UINT8   unCmdID;//命令
}Bq40PacketHead;
#pragma pack(pop)


class CUARTSocketBQ40Z50 : public CUARTSocket
{
public:
    CUARTSocketBQ40Z50(CSocketHandler* pSktHandler);
    virtual ~CUARTSocketBQ40Z50();
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
	UINT16 unGetCmdLen;
	UINT8  m_unSndCmd;
};

#endif // CUARTSOCKET_H
