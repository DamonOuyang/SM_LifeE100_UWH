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

class calPrmDialog;
class LockScreenDialog;
class MonThread;
class SystemSetDialog;
class CWorkThread;
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
    void on_gageSlider_valueChanged(int value);
    void SecTimer();
    void on_BPStrBtn_clicked(bool checked);
    void on_wtrRomOnOffBt_clicked(bool checked);

    void on_wtrTmpSetBt_clicked();

	//灌注调节压力
	void PourPressLEClick(void);
	//预灌注调节速度
	void PreSpeedLEClick(void);

    void on_sysSetBtn_clicked();

    void on_sysSetBackBtn_pressed();

    void on_almShowBtn_clicked();

    void on_almOnOffBtn_clicked(bool checked);

    void on_unLockScreenBtn_clicked();
    //静脉
    void on_BPStrBtnV_clicked(bool checked);
	void OnMonTabChangedV(void);
	//灌注调节压力
	void PourPressLEClickV(void);
	//预灌注调节速度
	void PreSpeedLEClickV(void);

    void on_calPrmButton_clicked();

private:
    Ui::MainWindow *ui;
	SystemSetDialog *m_pSysSteDlg;
	calPrmDialog *m_pCalPrmDialog;

	LockScreenDialog *m_pLockScreenDlg;
	
    QTimer *m_pSecTmer;
	QLineEdit*   m_pCurLineEdit;

	MyLineEdit *m_pPourPressLE;
	MyLineEdit *m_pPreSpeedLE;

	MyLineEdit *m_pPourPressLE_V;
	MyLineEdit *m_pPreSpeedLE_V;


    void LoadConfigFile(void);
	void CreateAlmFile(void);

    //waterGageWg
    int m_unSliderVal;//
    int m_gageValLabelX;
    int m_gageValLabelY;

	bool m_bBPRunFlgA;//动脉血泵运行标识
	bool m_bBPRunFlgV;//静脉血泵运行标识
	
	bool m_bFlashAlmBtFlg;
	bool m_bFlashFlg;
	bool m_bAlmBeepFlg;

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
    void InitWaterGageWg(void);
	void FlashWaterRoomInfo(void);
	void CheckWatStop(void);
	UINT8 m_unWatRunState; //水浴运行状态

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

	//静脉
	UINT8 m_unPumpRunV; //泵运行状态
	UINT8 m_unPourStaV; //灌注状态

	UINT16 m_unAPressSetVal;     //压力
    UINT16 m_unASpeedSetVal;     //转速
	UINT16 m_unVPressSetVal;     //压力
    UINT16 m_unVSpeedSetVal;     //转速

	//告警按钮
	void FlashAlmBt(void);
	bool HasAlarm(void);
	void CheckAlmBeep(void);
	bool  m_bCloseBeepFlag;

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
};

extern CWorkThread*   g_pWorkThread;
extern MonThread*     g_pMonThread;

#endif // MAINWINDOW_H
