#ifndef CBQ40Z50Battery_H
#define CBQ40Z50Battery_H

#include "cswitchmodule.h"

//#pragma pack(1)
//#pragma pack()


//单个--开关模块类
class CBq40z50Bat: public CSwitModule
{
public:
    CBq40z50Bat();
    virtual void ProcTask(void);
    virtual bool IsRun(void);
	virtual void OnCmdRsp(UINT8 unCmdID);
    virtual void DataParser(BYTE* pDataBuf,UINT32 unCmdID,UINT32 unDataLen);
    virtual UINT32 GetErrCode(void);
    virtual void  GetClassName(QString& strClassName);
    virtual void GetCtrlDevData(void* pDevData);

private:
    //BatBascInfo m_pBatData;
	bool m_bGetData;
	bool m_unGetVerFlg;
	UINT8 m_unChkCmd[5];
	UINT8 m_unCmdFlg;
	UINT16 m_unBatTmp;
	UINT16 m_unBatVol;
	INT16  m_unBatCur;
	UINT8  m_unBatSoc;
	UINT16 m_unCycNum;

	UINT8  m_unSocNum;
};

#endif //
