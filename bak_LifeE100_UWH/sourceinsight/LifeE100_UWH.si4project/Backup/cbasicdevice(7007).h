#ifndef CBASICDEVICE_H
#define CBASICDEVICE_H

#include "includes.h"
#include <QString>

#define MAX_CMD_DATA            4096 //500
#define MAX_CMD_COUNT           10
#define CMD_ST_IDLE				0x00
#define CMD_ST_WAIT_SND			0x01
#define CMD_ST_WAIT_RSP			0x02

typedef struct CMD_DATA
{
    UINT8 unDevID;
	UINT8 unSndID;
    UINT8 unCmdID;
    BYTE  pCmdData[MAX_CMD_DATA];
    UINT16 unCmdDataLen;
}CmdData;

#pragma pack(1)
typedef struct URT_PACKET_HEAD
{
    UINT8  unDevID;
	UINT8  unSndID;
    UINT16 unDataLen;
    UINT16 unCRC;
    UINT8  unCmdID;
}URTPacketHead;
#pragma pack()

//控制设备命令定义
#define CMD_SUB_DEV_DATA        0x01	//查询子设备实时数据
#define CMD_SUB_DEV_DATA_ACK    0x81	//查询子设备实时数据应答

#define CMD_SUB_DEV_PRM_SET     0x02    //子设备配置参数
#define CMD_SUB_DEV_PRM_SET_ACK 0x82    //子设备配置参数应答

#define CMD_SUB_DEV_RUN         0x03    //启动开关
#define CMD_SUB_DEV_RUN_ACK     0x83    //启动开关应答

#define CMD_SUB_DEV_VER         0x04    //查询设备版本
#define CMD_SUB_DEV_VER_ACK     0x84    //查询设备版本应答

#define MAX_CMD_TYPE_COUNT      10      //最大命令类型个数

#define CMD_ST_IDL              0       //命令空闲
#define CMD_ST_SND              1       //命令发送
#define CMD_ST_CFM              2       //命令确认

//命令序号ID
#define  CTRL_DEV_DATA_SND      0x01
#define  CTRL_DEV_PRM_SND       0x02
#define  CTRL_DEV_RUN_SND       0x03
#define  CTRL_DEV_VER_SND       0x04
#define  CTRL_POUR_STA_SND      0x05 //灌注状态
#define  CTRL_UP_SET_SND        0x06 //设置升级开始
#define  CTRL_UP_PACK_SND       0x07 //正在发送升级包
#define  CTRL_PUL_PRM_SND       0x08 //脉搏参数




class CUARTSocket;
class CWorkThread;
class CCmdDataQueue;
class CBasicDevice
{
public:
    CBasicDevice();
    virtual ~CBasicDevice();
    virtual void ProcTask(void);
    virtual void DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen) = 0;
    virtual void OnMsTimer(UINT32 unMsCount);
    virtual void OnCmdRsp(UINT8 unCmdID);
    virtual void OnCmdTimeOut(void);
    virtual bool IsActive(void);
    virtual bool IsEnabled(void);
    //virtual bool IsRun(void);
    virtual void SetEnable(bool bEnFlag);
    virtual UINT32 GetErrCode(void);
    virtual void GetErrorInfo(QString& strError);
    virtual void GetClassName(QString& strClassName);
    void  SetCmdCtrlStat(UINT8 unCmdIndex,UINT8 unCmdStat);

    void SetDevID(UINT32 unDevID);
	void SetSndID(UINT32 unSndID);
    UINT32 GetDevID(void);
    void SetUARTSocket(CUARTSocket*  pUARTSocket);
    void SetWorkThread(CWorkThread*  pWorkThread);
    void ShowInfo(const char* pStrInfo);
    bool GetCmdConfirm(UINT8 unCmdIndex);
	int  GetSubDevSocket(void);
protected:
    void  SetMsTimer(UINT32 unMsCount);
    bool  BuillCmdData(BYTE* pDataBuf,long lDataLen,long lCmdID);
    void  SendData();
    bool  GetNextCmdData(void);

    bool  HasCmdSnd(void);
    virtual void  ClearCmds(void);
    void  SetDevTmt(UINT16 unTmtCount);
    UINT32  m_unDevID;      //通信设备ID
    UINT32  m_unSndID;      //发送设备ID
    UINT32  m_unCmdMsTimer; //命令超时
    UINT8   m_unCmdStat;	//当前命令状态
    bool    m_bAtvFlag;     //设备状态
    bool    m_bEnabled;     //设备是否启用

    UINT32  m_unTmtCount;           //命令当前超时次数
    UINT32  m_unMaxTmtCount;        //命令最大超时次数
    UINT32  m_unCmdWaitRspMaxMs;    //命令等待应答最长时间
    CmdData m_curCmdData;           //当前发送命令
    CCmdDataQueue* m_pCmdDataQueue; //设备命令数据
    UINT8 m_unCmdCtrlStat[MAX_CMD_TYPE_COUNT]; //命令控制状态

    QString m_strErrorInfo;
    CUARTSocket* m_pUARTSkt;
    CWorkThread* m_pWorkThread;
};

#endif // CBASICDEVICE_H
