#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "includes.h"
#include <QMainWindow>
#include <QTimer>
#include <QLineEdit>
#include "myLineEdit.h"


namespace Ui {
class MainWindow;
}

class LoadHeadDialog;
//class OnLogDialog;
//class calPrmDialog;
class LockScreenDialog;
class MonThread;
class SystemSetDialog;
class CWorkThread;
class QRoundProgressBar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void OnMonTabChanged(void);
	void setValCanlce(void);
    void setValString(QString strIn);
    void SecTimer();
    void on_BPStrBtn_clicked(bool checked);
    void on_wtrRomOnOffBt_clicked(bool checked);

    void WtrTmpSetBtClick(void);

	//灌注调节压力
	void PourPressLEClick(void);
	//预灌注调节速度
	void PreSpeedLEClick(void);

    void on_sysSetBtn_clicked();

    //void on_sysSetBackBtn_pressed();

    void on_almShowBtn_clicked();

    void on_almOnOffBtn_clicked(bool checked);

    void on_unLockScreenBtn_clicked();
	void setLock(void);
    //静脉
    void on_BPStrBtnV_clicked(bool checked);
	void OnMonTabChangedV(void);
	//灌注调节压力
	void PourPressLEClickV(void);
	//预灌注调节速度
	void PreSpeedLEClickV(void);

    void on_calPrmButton_clicked();
	//关闭泵提示窗口返回
	void closePumWinBack(bool bState);

private:
    Ui::MainWindow *ui;
	SystemSetDialog *m_pSysSteDlg;
	//calPrmDialog *m_pCalPrmDialog;

	LockScreenDialog *m_pLockScreenDlg;
	
    QTimer *m_pSecTmer;
	QLineEdit*   m_pCurLineEdit;

	MyLineEdit *m_pPourPressLE;
	MyLineEdit *m_pPreSpeedLE;

	MyLineEdit *m_pPourPressLE_V;
	MyLineEdit *m_pPreSpeedLE_V;

	QPushButton *m_pWtrTmpSetBt;

	void SetDevHeadBg(bool bFlag, UINT8 unDev);
    void LoadConfigFile(void);
	void CreateAlmFile(void);

    //waterGageWg
    int m_unSliderVal;//
    int m_gageValLabelX;
    int m_gageValLabelY;

	bool m_bBPRunFlgA;//动脉血泵运行标识
	bool m_bBPRunFlgV;//静脉血泵运行标识
	
	bool m_bFlashFlg;
	bool m_bAlmBeepFlg;
	UINT8 m_unAlmLev;

	bool m_bSysReStrFlg;
	UINT8 m_unFlashMainWinS;//刷新主页面

	//刷新设置参数
	void OnUpdParams(void);

    //get system time
    void FlashSysTime(void);

    //灌注时长widget
    void StartPourTime(void);
	void SysAutoChangePress(UINT8 unPumType, UINT16 unPress);
	void CheckAutoPress(void);
	void SetBeepHour(void);
	bool m_bPourStrFlgA;//灌注开始标识
	bool m_bPourStrFlgV;//灌注开始标识

	bool m_bMonTabChgFlagA;
	bool m_bMonTabChgFlagV;
	
	UINT8 m_unPourChangRePourSceA;//动脉
	UINT8 m_unPourChangRePourSceV;//静脉
    bool  m_bHourBeepFlg;
	UINT8 m_unHourTimer;
	
    //水浴温度
    void InitWaterTmpWg(void);
	void CheckWtrRomOnOffBt(void);
	UINT8 m_unWatRunCheckSec;//检测水浴打开按钮延迟时间

    //初始化水浴-压力widget
    void InitWaterGageWg(QRoundProgressBar* bar);
	void FlashWaterRoomInfo(void);
	void CheckWatStop(void);
	//void connectToSlider(QRoundProgressBar* bar);
	UINT8 m_unWatRunState; //水浴运行状态
	QRoundProgressBar* m_pRPBar;

	//电池
	void InitBatteryLog(void);
	void FlashBattryInfo(void);
	void ShowBatteryLinkLog(bool bLinkFlg);
	void ShowACLinkLog(bool bLinkFlg);
	void ShowChgIcon(UINT8 unBatStat);
	UINT8 m_unBatStat;//电池状态

	//血泵
	void FlashPumpAInfo(void);
	void FlashPumpVInfo(void);
	void CheckPumpWaterState(void);
	void CheckPourStopA(void);//动脉
	void CheckPourStopV(void);//静脉
	void CheckPourPrmA(void);
	void CheckPourPrmV(void);
	void SetDefPumPrmA(UINT8 unSite, UINT8 unCfgItem, UINT16 unPress, UINT16 unSpeed);
	void SetDefPumPrmV(UINT8 unSite, UINT8 unCfgItem, UINT16 unPress, UINT16 unSpeed);
	UINT8 m_unPumpRunA; //泵运行状态
	UINT8 m_unPourStaA; //灌注状态
	UINT8 m_unClosePumDev;//关闭泵设备

	//静脉
	UINT8 m_unPumpRunV; //泵运行状态
	UINT8 m_unPourStaV; //灌注状态

	UINT16 m_unAPressSetVal;     //压力
    UINT16 m_unASpeedSetVal;     //转速
	UINT16 m_unVPressSetVal;     //压力
    UINT16 m_unVSpeedSetVal;     //转速

	//告警任务
	void TaskAlmPro(void);
	void CtrlBeep(UINT8 unCtrlLev, UINT8 checked);
	void CtrlBeepVolume(UINT8 unCtrlLev);
	bool HasAlarm(void);
	void CheckAlmBeep(UINT8 unNewAlmLev);
	void BeepRestart(void);
	bool  m_bCloseBeepFlag = true;
	UINT16 m_unBeepRestSec;
	bool  m_bAlmFlashFlg;
	UINT8 m_unFlashAlmSec;
	UINT8 m_unFlashHz = 5;

	//开机等待
    UINT8 m_unCheckStartDly;
	bool m_unStartCheckFlag;
	QMessageBox *pCheckMsgBox;
	QPushButton* pCheckBut;
	void CheckStartInit(void);
	void CheckStart(void);

//校准
	UINT8   m_unClickNum;
	UINT8   m_unEntrCalFlag;
	void CalCheckClicked(void);

//状态一致
    UINT32 unSetPumStateDlyA;
	UINT32 unSetPumStateDlyV;
	UINT32 unSetWatStateDly;
//锁
	void FlashMainWindowPrePourBg(bool bLock);
//开机log
    bool m_bOnLogFlg = false;
    //OnLogDialog *m_pOnLogDialog;
	QMovie *m_pMovie;
	void InitMovieLog(void);
//开机引导
    bool m_bLoadingFlg = false;
	LoadHeadDialog *m_pLoadHeadDialog;


};

extern CWorkThread*   g_pWorkThread;
extern MonThread*     g_pMonThread;

#endif // MAINWINDOW_H
