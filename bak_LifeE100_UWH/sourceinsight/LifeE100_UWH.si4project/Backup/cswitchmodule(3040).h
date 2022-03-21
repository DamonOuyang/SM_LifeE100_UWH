#ifndef CSWITCHMODULE_H
#define CSWITCHMODULE_H

#include "includes.h"
#include "cbasicdevice.h"

#define SND_MAX_GET_DATA_MS  800L

#define DEV_RUN_OFF  0
#define DEV_RUN_ON   1

#define CMD_SET_DEV_UP         0x70   //设备准备升级
#define CMD_SUB_DEV_UP_ACK     0xF0   //设备准备升级应答

#define CMD_PACK_DEV_UP         0x71   //设备升级包发送
#define CMD_PACK_DEV_UP_ACK     0xF1   //设备升级包发送应答

#pragma pack(1)
//接收升级包应答信息
typedef struct UP_PACK_ACK
{
    UINT16 unPkgIndex;   //升级数据包ID
    UINT8 McuUpdResult;  //升级包发送返回结果
}UpPackAck;

#pragma pack()



//单个--开关模块类
class CSwitModule : public CBasicDevice
{
public:
    CSwitModule();
    virtual void ProcTask(void);
    virtual bool IsRun(void);
    virtual void DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen);
    virtual void  OnCmdTimeOut(void);
    virtual void  GetClassName(QString& strClassName);
    virtual bool SetDevParam(SetDevPrm* pDevPrmCfg);
    virtual bool CtrlDevRun(UINT8 unCode);
    virtual void SendDevPrm(void);
	virtual void GetDevVer(void);
    virtual void GetCtrlDevData(void* pDevData);
	virtual void GetMcuVersion(McuUpdateState* pMcuVer, UINT8 unType);

	//升级
	virtual void SetDevUpdate(char* pUpdatePath);
	virtual void SndStrUpdateSet(void);
	virtual void BuildUpadteMcuCmd(void);
	virtual bool InitDevUpdate(void);
	virtual bool RedDevUpdate(UINT32 unReadPos,BYTE* pDataBuf,UINT32 unDataLen);
	virtual bool SetNextUpPack(UpPackAck* pUpPackAck);
	virtual void GetDevUpdateInfo(void* pDevUpInfo);
	virtual void CloseDevUpdate();
	
protected:
    bool    m_bSetPrmFlag;
	bool    m_unGetVerEn;
    SetDevPrm m_devParam;           //设备参数
    McuUpdateState m_McuStatInfo;   //
    //升级
	bool    m_bUpDveFlag; //升级设备标识
	bool    m_bUpInitFlag;//升级初始化标识
	bool    m_bSndUpStrFlag;//发送升级标识
	bool    m_bSndUpPackFlag; //发送升级包
	bool    m_unWatingStrUp;  //等开始升级标识
	int     m_fdUpdate;
	char    m_cMcuUpdatePath[128]; //ARM的单片机升级文件路径
	UINT32  m_unTotalSize;
	UINT16  m_unTotalPkg;
	UINT16  m_unLastPkgSize;
	UINT8   m_unDevUpSate;
	UINT8   m_unUpFailNum; //失败次数
	UpdateMcu m_pUpdateMcu;
	UINT16  m_unUpPackLen;
};

#endif // 
