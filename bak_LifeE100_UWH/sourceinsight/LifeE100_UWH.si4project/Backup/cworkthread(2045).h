#ifndef CWORKTHREAD_H
#define CWORKTHREAD_H
#include <sys/timeb.h>
#include <QThread>
#include <QMutex>
#include <QString>
#include "includes.h"
#include "cpourdevices.h"

class CPourDevices;
class CSwitWater;
class CSwitPump;
class CSocket;
class CSocketHandler;
class CDevCmdHandler;
class CUARTSocket;
class CErrorStringQueue;
class CWorkThread : public QThread
{
    Q_OBJECT
public:
    explicit CWorkThread(QObject *parent = 0);
    ~CWorkThread();

    void StopRun(void);
    bool IsRunEnd(void);
	void SetDataType(UINT8      unPumType, UINT8 unDataType);
    void ShowStringInfo(const char* strInfo,unsigned char unShowMode = DBG_SHOW ,unsigned char unErrIcon = ICON_INFO);

    bool GetInfoString(ErrInfo* pErrInfo);
    void StartBloodPump(UINT8 unBpGrpID);
	void StopBloodPump(void);	
    unsigned int GetBloodPumpGrpID(void);//long
    void ShowDiff(void);
    bool SetAlmItem(UINT8 unPreAlmFlag,\
                    UINT8 unAlmID,\
                    UINT8 unAlmObjID,\
                    UINT8 unAlmSubObjID,\
                    INT32 unAlmVal,\
                    UINT8 unAlmFlag);
	bool SetWindowShowAlm(UINT8 unPreAlmFlag,UINT8 unAlmID,UINT8 unAlmObjID,
						        UINT8 unAlmSubObjID,INT32 unAlmVal,UINT8 unAlmFlag);


    void OnPumStop(void);
    bool IsPumpRuning(void);

	void setOpenWatRoom(UINT8 unIndex, UINT8 unOpenFlg);
    UINT32 GetDevData(UINT8      untype, UINT8 unIndex, BYTE* pDataBuf,UINT32 unBufSize);
	void CtrlBeep(UINT8 unCtrl);
    void GetAllMcuVer(UINT8* pDataBuf);
	//升级
	void ProMcuUpTask(void);
	McuUpdateInfo GetDevUpdateInfo(void);//(McuUpdateInfo *mcuUpInfo);
	void SetUpdateMcu(UINT8 unType);
	UINT8 CheckUpdateFileType(UINT8 unType);
signals:
	void ShowInfo(void);
	void UpdateConfigInfo(void);

public slots:

protected:
    void run();

private:
    bool m_bBpRunFlag;
    bool m_bRunEnd;
    bool m_bQuitFlag;
    bool m_bInitFlag;

	unsigned int  m_unUsrBpCmd;//用户血泵操作命令//long
	UINT8 m_unBpGrpID;

    QMutex m_lckMutex;
	QMutex m_lckUpStat;
    QList<CSocket*>      m_listCmmSkts;
    CErrorStringQueue*  m_pErrStrQueue;
    CSocketHandler* m_pSktHandler;  //通信对象处理器
    CDevCmdHandler* m_pDevCmdHander;//子设备对象处理器
    CUARTSocket*    m_pUARTSkt0;//子设备通信串口０
    CUARTSocket*    m_pUARTSkt1;//子设备通信串口1
    CUARTSocket*    m_pUARTSkt2;//子设备通信串口2

    QList<CSwitPump*>m_listAPumMods;
	QList<CSwitPump*>m_listVPumMods;
	QList<CSwitWater*>m_listWatMods;
    CPourDevices m_procPour;

    
	int m_fdMonInfoFle;
	int m_fdMonData;
    timeb   m_timeb;
    UINT32  m_unMsTimer;
    UINT32  m_unAlmDlySec;
	UINT8   m_unDataType;//预灌注或灌注类型


	UINT8 m_unArteryPrmIndex;//动脉血泵参数编号
	UINT8 m_unVeinPrmIndex;  //静脉血泵参数编号
	UINT8 m_unWaterPrmIndex;  //水浴参数编号

	UINT8 m_unAlmFlowDlySec; //流量告警等待

	UINT32 m_unMonDlySec;    //监控存储时间
	bool   m_bOpenMonFile;   //打开监控日志文件
	QString m_strErrorInfo;

	//升级
	bool m_bMcuUpEn;
	UINT8 m_unMcuType;
	UINT8 m_unMcuUpState;
	bool  m_bGetUpInfoFlg;
	McuUpdateInfo m_pMcuUpInfo;

    void OnCmmTimeout(UINT32);
    void AddCmmObject(CSocket* pCmmSkt);

    void ProcUsrSrtCmd(void);   //处理用户命令

    void InitThread(void);
	void SetArteryParam(void);
	void SetVeinParam(void);
    void ProcInitConfig(void);

    bool ReadMonDataInfo(QString pFileName);
	void OpenMonDataInfo(void);
	bool SaveMonDataInfo(void);
	void OpenMonDataFile(void);
	void ProcMonInfo(void);

    void SetUsrBPCmd(unsigned int unUsrBpCmd);//long
    UINT32 GetUsrBPCmd(void);
	void SetPourState(UINT8      unPumType, UINT8 unIndex);
    bool GetUpdConfigInfo(void);

    void CreateArteryMods(void);//动脉对应设备
    void CreateVeinMods(void);//静脉对应设备
    void CreateWaterMods(void);//水箱对应设备


    void ProcAlmInfo(void);
    UINT32 DifVal(UINT32 unVal0,UINT32 unVal1);
    void OnMsTimer(UINT32 unMsCount);
	void SajParGrpStat(void);
    void InvParGrpStat(void);
};

#endif // CWORKTHREAD_H
