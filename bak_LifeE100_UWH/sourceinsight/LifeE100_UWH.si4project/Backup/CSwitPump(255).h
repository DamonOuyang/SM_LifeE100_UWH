#ifndef CSWITPUMP_H
#define CSWITPUMP_H

#include "cswitchmodule.h"

#define CMD_SND_POUR_STA         0x05    //发送灌注状态
#define CMD_SND_POUR_STA_ACK     0x85    //发送灌注状态应答
#define CMD_SND_PUL_PRM         0x06    //发送脉搏参数
#define CMD_SND_PUL_PRM_ACK     0x86    //发送脉搏参数应答
#define CMD_SND_PUM_STA         0x08    //发送血泵状态与上位机同步
#define CMD_SND_PUM_STA_ACK     0x88    //发送血泵状态与上位机同步应答


//单个--开关模块类
class CSwitPump : public CSwitModule
{
public:
    CSwitPump();
    virtual void ProcTask(void);
    virtual bool IsRun(void);
    virtual void DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen);
    virtual UINT32 GetErrCode(void);
    virtual void  GetClassName(QString& strClassName);
    virtual bool SetDevParam(SetDevPrm* pDevPrmCfg);
    virtual void GetCtrlDevData(void* pDevData);

    bool SndPourState(void);
	void SetPourState(UINT8 unStat);
	bool SetPulseParam(SetPulPrm* pPluPrm);
	void SendPulsePrm(void);
	bool SetPumpState(SetPumSta* pPumSta);
	void SendPumpState(void);
private:
    QMutex m_lckMutex;
    PumpDevData m_pPumpData;
	bool m_bGetData;
	bool m_unGetVerFlg;
	bool m_bSndPourFlg;
	UINT8 m_unPourState;
	bool  m_bStrInitFlg; //初始化标识
	//脉搏
	SetPulPrm m_pSetPulPrm;
	bool  m_bSetPulFlag;
	bool  m_bSetPumSta;//设置血泵状态与上位机一致
	SetPumSta m_pSetPumSta;
};

#endif // 
