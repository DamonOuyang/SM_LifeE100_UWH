#ifndef CSWITWATER_H
#define CSWITWATER_H

#include "cswitchmodule.h"


//单个--开关模块类
class CSwitWater: public CSwitModule
{
public:
    CSwitWater();
    virtual void ProcTask(void);
    virtual bool IsRun(void);
    virtual void DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen);
    virtual UINT32 GetErrCode(void);
    virtual void  GetClassName(QString& strClassName);
    virtual void GetCtrlDevData(void* pDevData);

private:
    WatDevData m_pWaterData;
	bool m_bGetData;
	bool m_unGetVerFlg;
};

#endif //
