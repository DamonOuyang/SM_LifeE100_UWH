#ifndef CBASICPOURPROC_H
#define CBASICPOURPROC_H
#include "includes.h"


#define MAX_ADJUST_CUR_TIMER	2000
#define MAX_CHRG_TIMER		(24*3600)
#define MIN_CHRG_TIMER		(12*3600)

#include <QFile>

class CWorkThread;
class CBasicPourProc
{
public:
    CBasicPourProc();
    ~CBasicPourProc();
    virtual void OnMsTimer(UINT32 unMsCount);
    virtual bool StartRun(UINT8    unPumDevType, UINT8 unIndex);
    virtual bool StopRun(UINT8    unPumDevType);
    virtual void ProcTask(void);
    virtual void SetSavePrd(UINT32 unSaveSecs)  = 0;
    virtual void OnUpdData(bool bUpdFlag) = 0;
    virtual void DeleteAllMods(void);
    virtual void GetStopErrorInfo(QString& strError);
    const char* GetErrorInfo();
    bool IsRun(UINT8 unPumType);
    void SetWorkThread(CWorkThread* pWorkThread);
	UINT8 GetPumDevTypeIndex(UINT8 unPumDevType);
protected:
    bool SaveTestData(bool bCloseFlag);
    void GetDataFileName(QString& strFileName);
    bool CreateDataFile(QString& strPathName);

    QString m_strErrorInfo;
    UINT32  m_unStopCode;   //停止运行错误码
protected:
    int m_fHandle;
	CWorkThread* m_pWorkThread;

    UINT32  m_unSaveSecs;	//保存数据时间周期(秒)
    UINT32  m_unGetSaveSec; //获取保存周期(秒)
    bool    m_bSaveFlag;    //数据保存标志位

    UINT32  m_unMsTimer;    //毫秒计数计
    bool    m_bRunFlag[2];  //0动脉血泵运行标志位;1:静脉
    bool    m_bSecFlag;
};

#endif //
