#ifndef CSWITCHMODULE_H
#define CSWITCHMODULE_H

#include "includes.h"
#include "cbasicdevice.h"

#define SND_MAX_GET_DATA_MS  800L
#define DEV_SRT_STAT_DLY_SEC    25      //发送间隔800ms*25=20s


#define DEV_RUN_OFF  0
#define DEV_RUN_ON   1

#define CMD_SND_DEV_STA         0x08    //发送血泵状态与上位机同步
#define CMD_SND_DEV_STA_ACK     0x88    //发送血泵状态与上位机同步应答

#define CMD_CAL_ZERO_DEV         0x09   //设备校正零值
#define CMD_CAL_ZERO_DEV_ACK     0x89   //设备校正零值应答

#define CMD_DEV_IP_ERR_INFO     0x8A   //设备主动上传信息

#define CMD_SND_BAT_STA         0x0C    //发送电池状态与上位机同步
#define CMD_SND_BAT_STA_ACK     0x8C    //发送电池状态与上位机同步应答

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
	virtual bool SetDevStateSync(SetDevStaSync* pPumSta);
	virtual void SendDevStateSync(void);

	//升级
	virtual void SetDevUpdate(char* pUpdatePath);
	virtual void SndStrUpdateSet(void);
	virtual void BuildUpadteMcuCmd(void);
	virtual bool InitDevUpdate(void);
	virtual bool RedDevUpdate(UINT32 unReadPos,BYTE* pDataBuf,UINT32 unDataLen);
	virtual bool SetNextUpPack(UpPackAck* pUpPackAck);
	virtual void GetDevUpdateInfo(void* pDevUpInfo);
	virtual void CloseDevUpdate();
	virtual void SetCalZeroCmd(UINT8 unCalItem);
	virtual void SndCalZero(void);
	virtual UINT8 GetCalZreoBak(void);
	//接收下位机记录信息
	virtual void UpDevErrorInfo(void* pDevErrInfo);
	virtual void RevDevErrorInfo(char *pRevBuf);
	virtual void SetBatState(UINT8 unBatSta);
	virtual bool SndBatState(void);
	virtual bool GetErrInfiFlag(void);
	virtual void GetErrInfo(char *pGetBuf);
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
	//电池状态
	UINT8 m_unBatState = 0;
	bool m_bSndBatFlg = false;

	UINT8 m_unSartStatDlySec; //启动延迟判断下位机状态
	bool  m_bCalZeroFlag;
	UINT8 m_unCalItem;
	UINT8 m_unCalZeroBak;
	bool  m_bSetDevSta;//设置下位机状态与上位机一致
	SetDevStaSync m_pSetDevSta;
	//下位机主动回写信息
	DevUpErrInfo  m_pDevUpErrInfo;
	bool m_bErrInfoFlg = false;
	char m_pDevErrInfo[MAX_INFO_SIZE];
	QMutex m_lckMutexUpInfo;
};

#endif // 
