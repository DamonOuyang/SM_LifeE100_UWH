#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <QString>
#include <QDateTime>
#include <QMutex>
#include <sys/timeb.h>
#include "unistd.h"
#include <QLabel>
#include <QPushButton>
//#include <sys/types.h>
//#include <sys/stat.h>

class QFormLayout;
class QLineEdit;
class QMutex;
class QComboBox;
class CMonShareData;
class QGroupBox;
class QMessageBox;
class QBoxLayout;
class CAlarmDataFile;
class QAbstractItemView;

#include <QMessageBox>


#define CONFIG_FILE_NAME        "/Life100UWH.cfg"
#define CONFIG_FILE_NAME_BAK    "/Life100UWH_BAK.cfg"
#define DEV_TYPE_CFG_NAME       "/DevTypePrm.cfg"
#define PWD_CONFIG_FILE         "/PwdCfgInfo.cfg"
#define ALM_FILE_NAME           "/AlmData.dat"
#define ALM_UPD_POS_NAME        "/AlmUpdPos.dat"
#define MCU_UPD_FILE_PATH       "/DshUpdFiles/"


//保存操作日志文件
#define SAVE_FILE_INFO_NAME     "/SaveMonInfo.dat"
#define SAVE_MON_DATA_NAME      "/SaveMonData.dat"
#define OPER_LOG_INFO_NAME      "/OperLogInfoData.dat"

//下位机上传信息保存文件
#define SLAVE_UP_INFO_NAME      "/SlaveUpInfo.txt"


#define MAX_SRN_WIDTH   1280
#define MAX_SRN_HEIGHT  800

#define SAVE_BUT_NAME       "保存"
#define INPUT_BUT_NAME      "输入"
#define CANCEL_BUT_NAME     "取消"
#define CONFIRM_BUT_NAME    "确定"


#define FONT_NAME  "wenquanyi"//"simsun"//"arial"//"wenquanyi"

//操作日志个数
#define SAVE_OPER_LOG_NUM    1000

//
#define SAVE_MON_LOG_NUM     1000
//灌注存储数据个数
#define SAVE_POUR_DAT_NUM   1000

//灌注、预灌注每个文件存储最大条数
#define MAX_DATA_REC_COUNT  10000


//控件高度
#define MINI_HEIGHT 30



#define INVALID_DEV_ID     0xFF //子设备ID编号
#define INVALID_DEV_CMD_ID 0xFF //子设备命令ID

//用户血泵界面操作命令
#define USR_BP_CMD_STRT    0x00
#define USR_BP_CMD_STOP    0x01
#define USR_BP_CMD_NONE    0xFF

//最大血泵组
#define MAX_BP_GRP_COUNT  2
//串口设备ID长度
#define MAX_COMPORT_SIZE    30

//快速调节参数面板
#define SET_VAL_DLG_W       343 
#define SET_VAL_DLG_H       151 

//转速最大限值
#define SET_SPEED_LIMIT     10000//6000
#define SET_STEP_1          1
#define SET_SPEED_DEF       2000 //默认值
#define CHK_SPEED_STP       10000 //最高停止灌注转速

#define SET_PRESS_LIMIT_V   140
#define SET_PRESS_LIMIT     1200 //800
#define SET_STEP_5          5
#define SET_PRESS_STP       900 //最好停止灌注压力
#define SET_AUTO_PRESS      300 //设置压力回到默认值

#define SET_TMP_LIMIT     450

//设置安全值
#define SET_POUR_SPEED    2000
#define SET_POUR_PRESS    300
#define SET_POUR_VAL_TMT  10

#define SET_POUR_SPEED_V    2000
#define SET_POUR_PRESS_V    50


//通信设备ID
#define MAIN_DEV_BAS_ID     0x01 //主控设备ID
#define APUM_DEV_BAS_ID     0x10 //动脉泵设备ID
#define VPUM_DEV_BAS_ID     0x18 //静脉泵设备ID
#define WAT_DEV_BAS_ID      0x20 //水浴设备ID

//设备开关
#define DEV_ON  1
#define DEV_OFF 0

//预灌注、灌注
#define PRE_POUR  0 //预灌注
#define STR_POUR  1 //开始灌注


//机器设备类型
#define DEV_MAIN_TYPE   0  //上位机设备类型
#define DEV_APUMP_TYPE   1  //动脉血泵类型
#define DEV_WAT_TYPE    2  //水浴类型
#define DEV_VPUMP_TYPE   3  //静脉血泵类型

//操作日志类型
//远程1/本地0/系统2
#define LOC_CTL 0
#define NET_CTL 1
#define SYS_CTL 2 //告警调整
#define SWT_CTL 3 //预灌注和灌注切换
#define WAT_TMP 4 //水过温
#define APUM_TMP 5 //A血过温
#define VPUM_TMP 6 //V血过温




//血泵最多设备
#define MAX_PUM_GRP_COUNT 4
//水浴最多设备
#define MAX_WAT_GRP_COUNT 2

//用户更新数据配置项定义
#define CFG_BASIC_ITEM          0x00    //基本配置界面

#define CFG_ARTERY_SPD_ITEM     0x01    //动脉血泵界面转速参数配置
#define CFG_ARTERY_PRS_ITEM     0x02    //动脉血泵界面压力参数配置
#define CFG_ARTERY_FLW_ITEM     0x03    //动脉血泵界面流量参数配置

#define CFG_VEIN_SPD_ITEM     0x04    //静脉血泵界面转速参数配置
#define CFG_VEIN_PRS_ITEM     0x05    //静脉血泵界面压力参数配置
#define CFG_VEIN_FLW_ITEM     0x06    //静脉血泵界面流量参数配置

#define CFG_WAT_ROOM_ITEM     0x07    //水浴配置界面
#define CFG_ALM_PRM_ITEM      0x08    //告警参数置界面

#define CFG_POUR_PRM_ITEM     0x09    //灌注参数置界面

#define CFG_PUL_PRM_ITEM     0x0A    //脉搏参数置界面



//数据告警内容：(告警ID: unAlmID)

#define MAX_ALM_REC_COUNT 6000         //系统最大支持告警记录条数
#define MAX_ALARM_INFO_COUNT   12      //告警数据个数
//动脉泵
#define ALM_ITEM_A_PRE_DN    0x01    //动脉泵-压力低
#define ALM_ITEM_A_PRE_UP    0x02    //动脉泵-压力高
#define ALM_ITEM_A_SPE_DN    0x03    //动脉泵-转速低
#define ALM_ITEM_A_SPE_UP    0x04    //动脉泵-转速高
#define ALM_ITEM_A_FLO_DN    0x05    //动脉泵-流量低
#define ALM_ITEM_A_FLO_UP    0x06    //动脉泵-流量高
#define ALM_ITEM_A_TMP_DN    0x07    //动脉泵-温度低
#define ALM_ITEM_A_TMP_UP    0x08    //动脉泵-温度高
#define ALM_ITEM_A_BUBBLE    0x11    //动脉泵-有气泡
#define ALM_ERROE_A_TMP      0x13    //动脉泵-温度异常



//静脉泵
#define ALM_ITEM_V_PRE_DN    0x09    //静脉泵-压力低
#define ALM_ITEM_V_PRE_UP    0x0A    //静脉泵-压力高
#define ALM_ITEM_V_SPE_DN    0x0B    //静脉泵-转速低
#define ALM_ITEM_V_SPE_UP    0x0C    //静脉泵-转速高
#define ALM_ITEM_V_FLO_DN    0x0D    //静脉泵-流量低
#define ALM_ITEM_V_FLO_UP    0x0E    //静脉泵-流量高
#define ALM_ITEM_V_TMP_DN    0x0F    //静脉泵-温度低
#define ALM_ITEM_V_TMP_UP    0x10    //静脉泵-温度高
#define ALM_ITEM_V_BUBBLE    0x12    //静脉泵-有气泡
#define ALM_ERROE_V_TMP      0x14    //静脉泵-温度异常


//水浴
#define ALM_ITEM_WAT_TMP_DN    0x20    //水浴-温度低
#define ALM_ITEM_WAT_TMP_UP    0x21    //水浴-温度高
#define ALM_ITEM_WAT_LIN_DN    0x22    //水浴-水位低
#define ALM_ITEM_WAT_LIN_UP    0x23    //水浴-水位高
#define ALM_ITEM_BLOOD_LIN_DN  0x24    //血液液位低



#define ALM_ITEM_SUB_DEV_TMT   0xF0    //主机与子设备通信超时

//告警消除值差
#define MAX_ALM_PRES_DIF_DN     20
#define MAX_ALM_PRES_DIF        50
#define MAX_ALM_FLOW_DIF        20
#define MAX_ALM_TMP_DIF         5

#define V_MAX_ALM_PRES_DIF_DN     10
#define V_MAX_ALM_PRES_DIF        20
#define V_MAX_ALM_FLOW_DIF        50
#define V_MAX_ALM_FLOW_DIF_DN     20

#define MAX_ALM_WAT_TMP_DIF     5 //告警消除水温差
#define MAX_ALM_WAT_LIN_DIF     2 //告警消除水位差
#define MAX_ALM_BLOOD_LIN_DIF   2 //告警消除血位差

#define SET_MAX_ALM_TMP_DIF     30 //血温和水温设置差值


//泵止错误代码
#define STP_ERR_USR_CNL_ERR		0x00	//用户手动取消
#define STP_ERR_DEV_TMT_ERR		0x01	//设备应答超时
#define STP_ERR_SUB_STP_ERR		0x02	//子设备主动停止
#define STP_ERR_WAT_TMP_ERR		0x03	//水温告警主动停止

//校正参数
#define CAL_SET      0x01
#define CAL_SET_SND  0x81
#define CAL_SET_FAL  0x91


#define CAL_READ     0x02
#define CAL_SET_OK   0x03
#define CAL_READ_OK  0x04

#define RUN_ARM_LINUX 1

#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef INT8
#define INT8 signed char
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef INT16
#define INT16 signed short
#endif

#ifndef INT32
#define INT32 signed int
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif

#ifndef BYTE
#define BYTE   unsigned char
#endif

#ifndef BOOL
#define BOOL	UINT8
#endif


/*
#ifndef _WIN32
    #ifndef UINT32
    #define UINT32 unsigned long
    #endif

    #ifndef BYTE
    #define BYTE   unsigned char
    #endif

    #ifndef BOOL
    #define BOOL    UINT8
    #endif
#endif
#ifdef _WIN32
    #include <windef.h>
#endif
*/
#pragma pack(1)

typedef struct TIME_INFO
{
    UINT8 unYear;	//年份加上2000
    UINT8 unMonth;	//月份(1-12)
    UINT8 unDay;	//日(1-31)
    UINT8 unHour;	//小时(0 - 23)
    UINT8 unMinute;	//小时(0 - 59)
    UINT8 unSecond;	//小时(0 - 59)
}DateTime;

typedef struct DEV_UPD_FLAGS
{
    bool bBasicFlag;    //基本参数更新
    bool bArteryFlag;   //动脉参数更新
    bool bVeinFlag;     //静脉参数更新
    bool bWtrRoomFlag;  //水箱参数更新
    bool bAlmSetFlag;   //告警配置更新
    bool bPourSetFlag;   //告警配置更新
    bool bPulSetFlag;    //脉搏配置更新
}DevUpdFlags;

//基本配置
#define MAX_PATH_SIZE       100
typedef struct BASIC_CONFIG_INFO
{
    char strDataPath[MAX_PATH_SIZE];    //历史数据保存路径
    char strLogPath[MAX_PATH_SIZE];     //日志文件保存路径

    UINT8  unAPumCount; //动脉血泵数量
    UINT8  unVPumCount; //静脉血泵数量
    UINT8  unWatCount;  //水浴数量
    
    UINT8  unAlmEnFlag;//告警功能启用或禁用
    UINT32 unMonSavTmt;//监控存储时间（秒）
}BasicCofnigInfo;

//血泵参数配置
typedef struct BLOOD_PUMN_PARAM
{
    UINT8  unDevID;     //设备通信ID
    UINT8  unEnFlag;    //是否启用
    
    UINT16 unPress;     //压力
    UINT16 unSpeed;     //转速
    UINT16 unFlow;      //流量
    //UINT8  unSetVal[3];
}BloodPumnParam;

//设置设备参数
typedef struct SET_DEV_PARAM
{
    UINT8  unIndex;       //参数项
    UINT16 unPrmVald;     //参数值
}SetDevPrm;

//设置脉搏参数
typedef struct SET_PUL_PARAM
{
    UINT8  unPumType;      //泵状态
    UINT8  unPulFreq;      //脉搏频率
    UINT16 unPulVal;       //搏动范围
}SetPulPrm;


//水浴参数配置
typedef struct WARTER_ROOM_PARAM
{
    UINT8  unDevID;     //设备通信ID
    UINT8  unEnFlag;     //是否启用
    UINT16 unTmpVal;     //温度设置
}WatRooParam;

//告警阈值
typedef struct DEV_ALM_PARAM
{
    INT16 unAlmUPresA;   //动脉压力上限告警
    //INT16 unAlmLPresA;  //压力下限告警
    INT16 unAlmUTmpA;    //动血温上限告警
    //UINT16 unAlmUSpee; //转速上限告警
    //UINT16 unAlmLSpee; //转速下限告警
    INT16  unAlmUFlowA;  //动脉流量过高告警
    INT16  unAlmLFlowA;  //动脉流量低高告警
    INT16  unAlmBubbleA; //动脉气泡告警值

    INT16  unAlmUPresV;  //静脉压力上限告警
    //INT16  unAlmLPresV;  //静脉压力下限告警
    INT16 unAlmUTmpV;    //静血温上限告警
    INT16  unAlmUFlowV;  //静脉流量过高告警
    INT16  unAlmLFlowV;  //静脉流量低高告警
    INT16  unAlmBubbleV; //静脉气泡告警值
    
    INT16  unAlmUWatTmp; //水浴水温告警
    INT16  unAlmUWatLin;  //水位高告警阈值
    INT16  unAlmLWatLin;  //水位低告警阈值
    UINT8  unAlmBloodLin;//血位告警
    
}DevAlmParam;

typedef struct DEV_POUR_PARAM
{
    UINT16 unPourUPresA;  //动脉压力上限停止
    //UINT16 unPourLPres;  //压力下限停止
    UINT16 unPourUSpeeA;  //转速上限停止
    INT16  unPourUTmpA;   //血温上限安全值
    INT16  unPourUFlowA;  //动脉流量过高停止
    INT16  unPourLFlowA;  //动脉流量低高停止

    UINT16 unPourUPresV;  //静脉压力上限停止
    UINT16 unPourUSpeeV;
	INT16  unPourUTmpV;   //血温上限安全值
    INT16  unPourUFlowV;  //静脉流量过高停止
    INT16  unPourLFlowV;  //静脉流量低高停止
    
    INT16  unPourUWatTmp; //水浴水温停止
    INT16  unPourWatLin;  //水位停止

}DevPourParam;


typedef struct DEV_CONFIG_INFO
{
    UINT16 unCheckSum;  //数据校验
    UINT32 unVersion;   //版本号
    UINT16 unInitFlag;  //初始化标志
    UINT8  unDevType;   //设备类型
    UINT8  unBloPumType; //血泵类型
    UINT8  unArteryType; //动脉血泵类型
    UINT8  unVeinType;   //静脉血泵类型
    UINT8  unWatTRooType; //水浴类型
    BasicCofnigInfo basicCfgInfo;   //基本配置参数
    BloodPumnParam  arteryParm;    //动脉血泵参数
    BloodPumnParam  veinParm;      //静脉血泵参数
    WatRooParam     watRooParam;   //水浴参数设置
    DevAlmParam     devAlmParam;   //设备告警参数
    DevPourParam    devPourParam;  //灌注配置参数
}DevCofnigInfo;//设备的所有配置信息

//血泵组告警
typedef struct PUM_GRP_ALM_BITS
{
    BYTE bPressUBits:1; //压力过高告警
    BYTE bPressLBits:1; //压力过低告警
    //BYTE bSpeedUBits:1; //转速过高告警
    //BYTE bSpeedLBits:1; //转速低高告警
    BYTE bFlowUBits:1;  //流量过高告警
    BYTE bFlowLBits:1;  //流量低高告警
	BYTE bBubblBits:1;	//血泵气泡告警
	BYTE bTmpUBits:1;	//血温过高告警
	BYTE bTmpErrBits:1;	//血温异常告警

    BYTE  bUndefBits:1;
}PumGrpAlmBits;

//血泵组告警
typedef struct WAT_GRP_ALM_BITS
{
    BYTE bTmpUBits:1; //水浴温度过高告警
    BYTE bTmpLBits:1; //水浴温度过低告警
    BYTE bLinUBits:1; //水浴水位过高告警
    BYTE bLinLBits:1; //水浴水位低高告警
    BYTE bBloodBit:1; //血位告警
    BYTE  bUndefBits:3;
}WatGrpAlmBits;


typedef struct DEV_ALM_BITS
{
    DateTime dtCreate;
	PumGrpAlmBits ApumGrpAlm[MAX_PUM_GRP_COUNT]; //动脉血泵
	PumGrpAlmBits VpumGrpAlm[MAX_PUM_GRP_COUNT]; //动脉血泵
	WatGrpAlmBits watGrpAlm[MAX_WAT_GRP_COUNT];  //水浴
	UINT32 unAPumModBits:4; //动脉泵设备
	UINT32 unVPumModBits:4; //静脉泵设备
	UINT32 unWatModBits:2;  //水浴设备
    UINT32 unSysRestartBit:1; //设备重新启动
    UINT32 unUndefBits:21;
    UINT32 unDevAlm1;      //预留
    UINT32 unDevAlm2;      //预留
}DevAlmBits;


//告警数据结构：
typedef struct ALM_ITEM
{
    DateTime dtCreate;	//告警时间生成时间
    UINT8 unAlmID;	 	//告警类别ID
    UINT8 unAlmObjID;	//告警对象ID
    UINT8 unAlmSubObjID;//告警子对象ID
    UINT8 unAlmFlag;    //告警状态:０表示清除告警，１表示产生告警
    INT32 unAlmVal;	//告警时，当前值(长整型)，精度会根据不同类型(unAlmID)而不同
}AlmItem;

typedef struct ALM_ITEM_EX
{
    UINT8 unUpdFlag;
    AlmItem almItem;
}AlmItemEx;

//动静脉控制设备信息
typedef struct PUMP_DEV_DATA
{
    UINT8  unRunFlg;    //工作状态
    UINT8  unPourSta;   //灌注状态
    INT16  unTmpVal;	//温度(℃)
	INT16  unFlowVal;	//流量(ml)
    INT16  unPrssVal;	//压力(mmHg)
    INT16  unSpeeVal;	//转速(RPM)
    UINT8  unBubbVal;    //气泡(mm)
    UINT32 unDevCode;   //设备状态码
}PumpDevData;

//水浴控制设备信息
typedef struct WAT_DEV_DATA
{
    UINT8  unRunFlg;    //工作状态
    UINT16 unTmpVal;	//温度(℃)
	UINT16 unWatLine;	//水位
	UINT8  unBloodSta; //血位状态(0:无告警,1:告警)
    UINT32 unDevCode;   //设备状态码
}WatDevData;

//预灌注、灌注信息
typedef struct POUR_INFO
{
    UINT8 unStopType;	//停止类型
    DateTime dtStart;	//启动时间
    DateTime dtEnd;		//停止时间
    UINT32 unRecords;	//记录条数
    UINT32 unSectorID;	//扇区ID
    UINT32 unTotalTime; //开始总时间，以秒为单位
}PourInfo;

//灌注数据
typedef struct POUR_DATA
{
    //动脉
    UINT8  unADataType;  //动脉数据类型
    UINT16 unASpeeSet;	 //动脉转速(RPM)设定值
    UINT16 unAPrssSet;	 //动脉压力(mmHg)设定值

    INT16  unATmpVal;	//温度(℃)
    INT16  unAFlowVal;	//流量(ml)
    INT16  unAPrssVal;	//压力(mmHg)
    INT16  unASpeeVal;	//转速(RPM)
    //水浴
	INT16  unWatTmpSet; //水浴温度设定值
	INT16  unWatTmpVal; //水浴值(℃)
	INT16  unWatLine;	//水位
    //静脉
    UINT8  unVDataType;   //静脉数据类型
    UINT16 unVSpeeSet;	  //静脉转速(RPM)设定值
    UINT16 unVPrssSet;	  //静脉压力(mmHg)设定值
    
    INT16  unVTmpVal;	//温度(℃)
    INT16  unVFlowVal;	//流量(ml)
    INT16  unVPrssVal;	//压力(mmHg)
    INT16  unVSpeeVal;	//转速(RPM)
    
    DateTime dtSample;	//采样时间
}PourData;

//灌注完整数据
typedef struct POUR_TST_DATA
{
    PourInfo	tstInfo;	//灌注概要数据
    PourData	tstData;	//灌注测试数据
}PourTstData;

//校正参数linmi20180502
//bCalIndex---表示校正零值或参考值，
//0x00----校正零值, 后面的<unRefVal>项没有用
//0x01----校正参考值, 后面的<unRefVal>表示参考值
typedef struct CAL_PRM
{
	UINT8  bCalItem;        //0-->压力1-->温度
	UINT8  bCalIndex;      
	UINT32 unRefVal;
}CalPrm;


typedef struct SET_READ_CAL_PRM
{
    CalPrm bstCalPrm;
	UINT8  calPrmFlag;// 1:设置成功，2:读取成功
}SetReadCalPrm;


//设置下位机状态与上位机一致
typedef struct SET_DEV_STA_SYNC
{
    UINT8  unDevSat;       //设备状态
    UINT8  unPourSta;      //灌注状态
    INT16  unDevVal;       //设备参数
}SetDevStaSync;


#define MAX_PWD_SIZE    10
typedef struct PWD_PARAM_INFO
{
    UINT8 bPwdEnFlg;
    char  pAdminStrPwd[MAX_PWD_SIZE];
    char  pUserStrPwd[MAX_PWD_SIZE];
}PwdParamInfo;

//下位上传信息
#define MAX_INFO_SIZE    250
typedef struct DEV_UP_ERROE_INFO
{
    DateTime dtSave;	//采集时间
    UINT8 unInfoLen;
    char  pDevErrInfo[MAX_INFO_SIZE];
}DevUpErrInfo;

typedef struct DEV_UP_ERROE_SAVE
{
    DateTime dtSave;	//保存时间
    DevUpErrInfo devUpErrInfo;
}DevUpErrSave;


//监控日志信息
typedef struct MON_SAVE_INFO
{
    UINT32   unMonDataNum;   //监控数据条数
    UINT32   unMonCurrPar;   //监控数据当前指针位置
}MonSaveInfo;


//操作日志类型
#define OPER_LOG_TYPE_BAS  1  //基本配置
#define OPER_LOG_TYPE_ALM  2  //告警配置
#define OPER_LOG_TYPE_POUR 3  //灌注配置
#define OPER_LOG_TYPE_WAT  4  //水浴模块配置
#define OPER_LOG_TYPE_APUM  5  //动脉血泵模块配置
#define OPER_LOG_TYPE_VPUM  6  //静脉血泵模块配置

#define OPER_CTRL_TYPE_WAT  7  //水浴启停

//#define OPER_CTRL_TYPE_POUR 8  //灌注和预灌注切换

#define OPER_SYS_TYPE_REST  9  //重启系统

#define OPER_LOG_TYPE_PUL  0x0A  //血泵模块脉搏配置


#define OPER_CTRL_TYPE_APUM  0x10  //动脉泵启停
#define OPER_CTRL_TYPE_VPUM  0x20  //静脉泵启停

#define OPER_CTRL_TYPE_APOUR  0x30  //动脉灌注和预灌注切换
#define OPER_CTRL_TYPE_VPOUR  0x40  //静脉灌注和预灌注切换

#define OPER_CTRL_REST_APOUR  0x50  //动脉下位机复位
#define OPER_CTRL_REST_VPOUR  0x60  //静脉下位机复位
#define OPER_CTRL_REST_WATER  0x70  //水浴下位机复位



//操作日志文件存储信息
typedef struct OPER_LOG_INFO
{
    UINT16   unOperLogFileNum;   //操作日志文件个数
    UINT16   unOperLogCurrPar;   //操作日志文件当前指针位置
}OperLogInfo;

//操作日志
typedef struct OPER_LOG_BSC  //基本配置
{
    UINT8 unType;   //操作类型
    UINT8 unSite;   //远程/本地/系统2
    DateTime dtCreate;  //操作时间
    
    UINT8  unAlmEnFlag[2]; //告警使能
    UINT32 unMonSavTmt[2]; //验证使能
    DateTime dtSystem[2];
}OperLogBasic;

typedef struct OPER_LOG_ALM  //告警配置
{
    UINT8 unType;   //操作类型
    UINT8 unSite;   //远程/本地/系统2
    DateTime dtCreate;  //操作时间

    INT16 unAlmUPresA[2];   //动脉压力上限告警值
    //INT16 unAlmLPresA[2];   //动脉压力下限告警值
    INT16 unAlmUTmpA[2];   //动脉血泵血温上限告警值
	INT16 unAlmUFlowA[2];    //流量上限告警值
	INT16 unAlmLFlowA[2];    //流量下限告警值
	INT16 unAlmBubbleA[2];    //气泡告警值
	
    INT16 unAlmUPresV[2];   //静脉压力上限告警值
    //INT16 unAlmLPresV[2];   //静脉压力下限告警值
    INT16 unAlmUTmpV[2];   //静脉血泵血温上限告警值
	INT16 unAlmUFlowV[2];    //流量上限告警值
	INT16 unAlmLFlowV[2];    //流量下限告警值
	INT16 unAlmBubbleV[2];	 //气泡告警值

    INT16 unAlmUWatTmp[2];      //水浴温度上限告警
    INT16 unAlmUWatLin[2];       //水浴水位高告警
    INT16 unAlmLWatLin[2];       //水浴水位低告警
    UINT8 unAlmBloodLin[2];       //水浴血位告警
}OperLogAlm;

typedef struct OPER_LOG_POUR  //灌注配置
{
    UINT8 unType;   //操作类型
    UINT8 unSite;   //远程/本地/系统2
    DateTime dtCreate;  //操作时间

    INT16 unPourUPresA[2];   //动脉压力上限停止值
    INT16 unPourUSpeeA[2];   //动脉转速上限停止值
    INT16 unPourUTmpA[2];    //动脉血温上限停止值
	INT16 unPourUFlowA[2];    //流量上限停止值
	INT16 unPourLFlowA[2];    //流量下限停止值
	
    INT16 unPourUPresV[2];   //静脉压力上限停止值
    INT16 unPourUSpeeV[2];   //静脉转速上限停止值
    INT16 unPourUTmpV[2];    //静脉血温上限停止值
	INT16 unPourUFlowV[2];    //流量上限停止值
	INT16 unPourLFlowV[2];    //流量下限停止值

    INT16 unPourUWatTmp[2];      //水浴温度上限停止
    INT16 unPourWatLin[2];       //水浴水位停止
}OperLogPour;

typedef struct OPER_LOG_WAT_DEV  //水浴设备配置
{
    UINT8 unType;   //操作类型
    UINT8 unSite;   //远程/本地/系统2
    DateTime dtCreate;  //操作时间

    UINT8  unEnFlag[2];   //使用状态
    UINT16 unTmpVal[2];   //设置水浴温度
}OperLogWatDev;

typedef struct OPER_LOG_PUM_DEV  //血泵设备配置
{
    UINT8 unType;   //操作类型
    UINT8 unSite;   //远程1/本地0/系统2
    DateTime dtCreate;  //操作时间

    UINT8  unEnFlag[2];   //使用状态
    UINT16 unPress[2];    //设置血泵压力
    UINT16 unSpeed[2];    //设置血泵转速
}OperLogPumDev; 

typedef struct OPER_LOG_CTL  //控制操作(启动/停止泵，启动/停止水浴、灌注状态切换、参数设置)
{
    UINT8 unType;   //控制类型
    UINT8 unSite;   //远程/本地/系统2
    DateTime dtCreate;  //操作时间
    
	UINT8  unOperType[2];    //操作类型 1启动，0停止
	UINT8  unResult[2];      //操作结果 1成功，2失败 0无
}OperLogCtl;


typedef struct MCU_VER_INFO
{
    char McuVer[15];
    char McuSn[16];
}McuVerInfo;

typedef struct MCU_UPD_STATE
{
    UINT8 McuUpdResult;
	McuVerInfo mcuVerInfo;
}McuUpdateState;

#define MAX_UPD_SND_DATA_LEN_EX 2048
typedef struct UPDATE_MCU
{
    UINT16  unTotalPkg;     //总数据包
    UINT16  unPkgIndex;     //数据包序号
    UINT8   unSendData[MAX_UPD_SND_DATA_LEN_EX];
}UpdateMcu;

typedef struct MCU_UPD_INFO
{
    UINT8  unMcuUpdState;
	UINT16 unTotalPkg;
	UINT16 unPkgIndex;     //数据包序号
}McuUpdateInfo;


//升级状态码表
typedef enum
{
    UpdNotStart = 0x00,         //表示未开始升级
    UpdDoing = 0x01,            //表示升级中
    UpdSuccess = 0x02,          //表示单片机固件升级成功
    
    UpdFileOpenErr = 0x03,      //表示打开升级文件失败
    UpdFileChkErr  = 0x04,      //表示升级文件检测失败
    UpdFileReadChkErr = 0x05,   //表示升级文件读检测失败
    UpdFileReadErr = 0x06,      //表示升级文件读失败
    UpdSndPackErr  = 0x07,      //表示升级失败3次
    UpdFindFileErr = 0x08       //表示升级文件找不到
    
}McuUpdEnum;


#pragma pack()


//错误显示类结构定义
#define MAX_STR_LEN   200
#define MAX_ERR_COUNT 10
#define DBG_SHOW      0
#define DLG_SHOW      1
#define ICON_INFO     0
#define ICON_ERROR    1

typedef struct ERR_INFO
{
    unsigned char unShowMode;
    unsigned char unErrIcon;
    char pString[MAX_STR_LEN];
}ErrInfo;

typedef struct DEV_BASIC_PARAM_CFG
{
    UINT16 unCheckSum;  //数据校验
    UINT32 unVersion;   //版本号

    UINT8  unDevType;   //设备类型
    UINT8  unBloPumType; //血泵类型
    UINT8  unArteryType; //动脉血泵类型
    UINT8  unVeinType;   //静脉血泵类型
    UINT8  unWatTRooType; //水浴类型

    UINT8  unAPumCount; //动脉血泵数量
    UINT8  unVPumCount; //静脉血泵数量
    UINT8  unWatCount;  //水浴数量	

	UINT32 unMonSavCount; //监控存储条数
	UINT32 lComBrdVal[5];
	char   strComPort[5][MAX_COMPORT_SIZE];
	
}DevBasicParamCfg;



//全局通用函数接口
QString ValueToString(int lValue,int lFactScale,int lDotNum);
QDateTime DateTimeToQDateTime(DateTime* pdtValue,bool bTimeFlag);
QString DateTimeToString(DateTime* pDateTime,bool bTimeFlag = true);
void StringToDateTime(DateTime* pDateTime,QString strDateTime);
bool IsValidDateTime(DateTime* pDateTime);
void GetDateTime(DateTime* pDateTime);
UINT16 CreateCRCCheckSum(BYTE* pDataBuf,UINT32 unDataLen);
UINT32 GetMsTimer(timeb* pOldTimeb);

bool LoadDevTypeParam(QString& strError);
bool SaveDevTypeParam(QString& strError);
bool LoadConfigInfo(QString strPathName,QString& strError);
bool SaveConfigInfo(QString& strError);
void InitDefParam(void);
//extern bool LoadPwdInfo(QString strPathName,QString& strError);
int SystemEx(const char *cmdstring);
void SetMessageBoxFont(QMessageBox* pMsgBox, int w = 80, int h = 0);
void ShowInfo(QMessageBox* pMsgBox,QString strInfo,QString strTitle,enum QMessageBox::Icon icon);
void AddRowItem(QBoxLayout* pBoxLayout,QWidget* pInputItem,QString strLabel);
void AddItem(QFormLayout* pParentForm,QLineEdit* pEditInput,QString strLabel,QString strUnit,long lEditWidth);
ulong GetItemValue(QLineEdit* pLineEdit,long lScale = 1000);

UINT32  GetMaxTstInfoSctID(UINT32* punFileCount);//取测试数据目录最大SectorID
bool ReadTestInfoEx(UINT32 unSectorID,PourInfo* pTestInfo);
bool ReadTestInfo(const char* pFileName,PourInfo* pTestInfo);
bool ReadTestData(char* pFileName,UINT32 unReadPos,BYTE* pDataBuf,UINT32 unDataLen);
bool GetTestDataFile(UINT32 unSectorID,char* pFileName);
bool DelTestDataFile(UINT32 unSectorID);
QString StopCodeToString(UINT32 unStopCode);
QString DataTypeToString(UINT8 unDataType);

UINT32  DoMsTimer(UINT32 unTimer,UINT32 unMsCount);
QComboBox*  CreateComboBox(QWidget * parent = 0);
QGroupBox*  CreateGroupBox(QWidget * parent = 0);
void LoadCompanyInfo(QString& strCoInfo);
QString AlmIDToName(UINT8 unAlmID);
QString  AlmFlagToString(UINT8 unAlmFlag);
QString AlmTmtIDToName(UINT8 unAlmObjID);
QString CheckOneAlmShow(void);

void InitWatchdog(void);
void SetWatchdog(void);
//监控日志操作接口
bool SaveOperLogData(const char* saveBuf, int bufLen);
bool ReadOperLogData(char* readBuf, int bufLen, UINT16 logCerrPar);
void OPenOperLogInfoFile(void);
bool ReadOperLogInfo(QString pFileName);
bool SaveOperLogInfo(void);
bool LoadPwdInfo(QString strPathName,QString& strError);
bool SavePwdInfo(QString& strError);
int FindMCUSoftwareFile(char* fileName, char* devType, \
	                            char* ver , unsigned char unType);




//全局通用变量接口
extern DevCofnigInfo   g_devConfigInfo;
extern DevCofnigInfo   g_devConfigInfo_Edt;//用户编辑
extern DevBasicParamCfg   g_devBasicPrmCfg;//设备基本配置参数

extern SetPulPrm       g_setPulPrm;


extern CAlarmDataFile* g_pAlmFile;
extern DevAlmBits g_devAlmBits;
extern PourData   g_DataAlarm;//当前告警发生是数值



extern CMonShareData*   g_pCfgDataUI;   //界面更新数据
extern CMonShareData*   g_pCfgDataNwk;

extern DevUpdFlags      g_devUpdFlags;  //设备配置更新标志位

extern PourTstData      g_pourTstData;
extern AlmItemEx        g_almItemEx;
extern OperLogInfo      g_operLogInfo;
extern int  g_fdOperLogFle;//操作日志存储信息
//监控日志
extern PourData         g_DataTests[SAVE_MON_LOG_NUM+10];//监控数据
extern MonSaveInfo      g_MonSaveInfo;
extern PwdParamInfo    g_pwdCfgInfo;
extern bool    g_bLoginFlag;

extern int g_fWtchDog;
extern bool g_bMainWindRunFlg;//主窗口线程正常标识
extern bool g_bWorkThRunRunFlg;//工作线程正常标识

extern SetReadCalPrm   g_setReadCalPrm[3];




#endif // INCLUDES_H
