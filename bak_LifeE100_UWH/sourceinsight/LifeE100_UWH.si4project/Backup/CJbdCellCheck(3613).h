#ifndef CJBDCELLCHECK_H
#define CJBDCELLCHECK_H

#include "cswitchmodule.h"

#pragma pack(1)

//BatteryBascInfo
typedef struct BAT_BASC_INFO
{
	UINT16 unBatVol; //总电压  2BYTE,单位 10mV，高字节在前，下同
	INT16  unBatCur;//电流  2BYTE，单位 10mA  通过电流判断电池充放电状态，充电为正，放电为负。
	UINT16 unLeftCap;//剩余容量  2BYTE，单位 10mAh 
    UINT16 unRatedCap;//标称容量  2BYTE，单位 10mAh 
	UINT16 unDshChgNum;//循环充放电次数  2BYTE 
//生产日期  2BYTE  采用 2 个字节传送比如 0x2068,其中日期为最低 5 为：0x2028&0x1f = 8 表示日期;月份（0x2068>>5）&0x0f=
//0x03 表示 3 月;年份就为 2000+ (0x2068>>9) = 2000 + 0x10 =2016;
//均衡状态  2BYTE  每一个 bit 则表示每一串均衡，0 为关闭，1 为打开 表示 1~16 串
//均衡状态_高  2BYTE  每一个 bit 则表示每一串均衡，0 为关闭，1 为打开 表示 17~32 串，最高支持 32 串 V0 版基础上增加
//保护状态  2BYTE  每一个 bit 表示一种保护状态，0 为未保护，1 发生保护 详见注 1：
//软件版本  1byte  0x10 表示 1.0 版本
//RSOC  1byte  表示剩余容量百分比
//FET 控制状态  1byte  MOS 指示状态，bit0 表示充电，bit1 表示放电，0 表示 MOS 关闭，1 表示打开
//电池串数  1byte  电池串数
//NTC 个数 N  1byte  NTC 个数
}BatBascInfo;


#pragma pack()


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
    //WatDevData m_pWaterData;
	bool m_bGetData;
	bool m_unGetVerFlg;
};

#endif //
