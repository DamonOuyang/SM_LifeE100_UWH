#ifndef CPOURDEVICES_H
#define CPOURDEVICES_H
#include "includes.h"
#include "cbasicpourproc.h"
#include <QList>
#include <QString>

#define MAX_UPD_DATA_MS                 1000 //更新数据频率（毫秒）
#define MAX_STEP_COUNT                  40  //

class CSwitPump;
class CSwitWater;
//多个--模块类
class CPourDevices : public CBasicPourProc
{
public:
    CPourDevices();
    virtual ~CPourDevices();
    virtual void StopPump(   UINT8 unPumDevType, UINT8 unStopCode);
    virtual bool StartRun(UINT8 unPumDevType, UINT8 unIndex);
    virtual bool StopRun(   UINT8 unPumDevType);
    virtual void ProcTask(void);
    virtual void OnMsTimer(UINT32 unMsCount);
    virtual void OnUpdData(bool bUpdFlag);
    virtual void SetSavePrd(UINT32 unSaveSecs);
    virtual void DeleteAllMods(void);
    virtual void GetStopErrorInfo(QString& strError);

    void AddAPumMod(CSwitPump* pPumModule);
    void RmvAPumMod(CSwitPump* pPumModule);
    void AddVPumMod(CSwitPump* pPumModule);
    void RmvVPumMod(CSwitPump* pPumModule);
	void AddWaterMod(CSwitWater* pWatModule);
	void RmvWaterMod(CSwitWater* pWatModule);

    void SetGrpID(UINT32 unGrpID);
    UINT32 GetPumpData(UINT8 unType, UINT8 unIndex, BYTE* pDataBuf,UINT32& unBufSize);
	UINT32 GetWatRoomData(UINT8 unIndex, BYTE* pDataBuf,UINT32& unBufSize);
    void GetMucVerInfo(BYTE* pDataBuf);
	UINT8 GetWatBloodState(void);
	UINT8 GetBubbleVal(UINT8 unPunType);
	UINT8 GetSensorState(UINT8 unPunType, UINT32 unSenType);
protected:
    QList<CSwitPump*>m_listAPumModules;
	QList<CSwitPump*>m_listVPumModules;
	QList<CSwitWater*>m_listWatModules;

	PumpDevData m_pumADevData;//动脉泵
	PumpDevData m_pumVDevData;//静脉泵
	WatDevData m_watDevData;

	McuUpdateState m_unMcuStateInfo[10];//最大支持 10个 设备

    UINT32  m_unBatGrpID;
    UINT32  m_unUpdDataMs;
    UINT32  m_unStrDlyMs;       //两次启动之间的最大延迟(毫秒)
    UINT32  m_unAlmDlyMs;       //告警命令延迟

    bool  SndPourDevRunCmd(UINT8 unPumDevType, UINT8 unIndex, UINT8 unCode);
    void  ProcPourTask(void);
    bool IsAllActive(void);
	void TaskDevCalZero(     void);

	bool  m_bCalTaskFlg;
	UINT8 m_unCalDevIndex;
	UINT32 m_unBakDlyMs;

private:
};

#endif // CDISCHARGEDEVICES_H
