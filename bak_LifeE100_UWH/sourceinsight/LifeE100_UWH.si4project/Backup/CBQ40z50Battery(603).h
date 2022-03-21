﻿#ifndef CJBDCELLCHECK_H
#define CJBDCELLCHECK_H

#include "cswitchmodule.h"

//#pragma pack(1)
//#pragma pack()


//单个--开关模块类
class CJbdCell: public CSwitModule
{
public:
    CJbdCell();
    virtual void ProcTask(void);
    virtual bool IsRun(void);
	virtual void OnCmdRsp(UINT8 unCmdID);
    virtual void DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen);
    virtual UINT32 GetErrCode(void);
    virtual void  GetClassName(QString& strClassName);
    virtual void GetCtrlDevData(void* pDevData);

private:
    BatBascInfo m_pBatData;
	bool m_bGetData;
	bool m_unGetVerFlg;
};

#endif //
