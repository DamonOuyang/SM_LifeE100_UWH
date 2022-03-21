#pragma execution_character_set("utf-8")

#include <QTextCodec>
#include <QFont>
#include <QMutex>
#include <QtGui>
#include <stdlib.h>



#include "includes.h"
#include "mainwindow.h"
#include <QApplication>
#include "cmonsharedata.h"
#include "calarmDataFile.h"
#include "csharedataqueue.h"
#include "DevBasicConfigDlg.h"
#include "cworkthread.h"

#if RUN_ARM_LINUX
#include <QWSServer>
#endif


DevCofnigInfo   g_devConfigInfo;
DevCofnigInfo   g_devConfigInfo_Edt;//用户编辑

SetPulPrm       g_setPulPrm;//设置脉搏


CWorkThread*    g_pWorkThread;


DevBasicParamCfg   g_devBasicPrmCfg;//设备基本配置参数


CAlarmDataFile* g_pAlmFile;
DevAlmBits g_devAlmBits;


CMonShareData*   g_pCfgDataUI; //界面更新数据
CMonShareData*   g_pCfgDataNwk;//网络更新数据

DevUpdFlags      g_devUpdFlags;//设备配置更新标志位

PourTstData      g_pourTstData;
PourData         g_DataTests[SAVE_MON_LOG_NUM+10];//监控数据
MonSaveInfo      g_MonSaveInfo;//监控文件管理
PourData         g_DataAlarm;//当前告警发生是数值


PwdParamInfo     g_pwdCfgInfo;
bool    g_bLoginFlag;


AlmItemEx        g_almItemEx;  //当前告警（温度优先）

OperLogInfo     g_operLogInfo;
int     g_fdOperLogFle;//操作日志存储信息

MonThread*       g_pMonThread;
int g_fWtchDog;
bool g_bMainWindRunFlg;//主窗口线程正常标识
bool g_bDataCopyFlag;  //数据拷贝标识
bool g_bWorkThRunRunFlg;//工作线程正常标识

SetReadCalPrm   g_setReadCalPrm[3];//设置、读取校正参数


void LoadStyleFile(QString strFilePathName)
{
    QFile styleSheet(strFilePathName);
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        //qWarning(strFilePathName.toAscii()+":样式文件不存在!");
        qWarning(strFilePathName.toLatin1()+":样式文件不存在!");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll());
}

int main(int argc, char *argv[])
{
    int nReturn = 0;
	#if RUN_ARM_LINUX
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));//可以了
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));      //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));//支持中文文件名显示
    #endif
	
	QFont font(FONT_NAME,14);
    QApplication a(argc, argv);
    a.setFont(font);
    LoadStyleFile(qApp->applicationDirPath()+QString("/blue.qss"));

	g_pCfgDataUI      = new CMonShareData(1000);
    g_pCfgDataNwk     = new CMonShareData(1000);

    g_pAlmFile = new CAlarmDataFile(sizeof(AlmItemEx),MAX_ALM_REC_COUNT);
	memset(&g_almItemEx,0,sizeof(g_almItemEx));
	memset(&g_DataAlarm,0,sizeof(g_DataAlarm));
	g_bLoginFlag = true;
    g_bMainWindRunFlg = false;//主窗口线程正常标识
    g_bDataCopyFlag   = false;
    g_bWorkThRunRunFlg = false;//工作线程正常标识
    if(argc>=2&&(0==strcmp(argv[1],"cfg")||0==strcmp(argv[1],"-cfg")))
    {
        DevBasicConfigDlg  cfgDlg;
        cfgDlg.resize(MAX_SRN_WIDTH, MAX_SRN_HEIGHT);
        cfgDlg.show();
        QFile styleSheet(qApp->applicationDirPath()+QString("/blue.qss"));
        if (!styleSheet.open(QIODevice::ReadOnly))
        {
            qWarning(":样式文件不存在!");
        }
        else
        {
            cfgDlg.setStyleSheet(styleSheet.readAll());
            nReturn = cfgDlg.exec();
        }
    }
    else
    {
        MainWindow w;
		#if RUN_ARM_LINUX
        QWSServer::setCursorVisible(false);
		#endif
        w.show();
        //w.showFullScreen();
        nReturn = a.exec();
    }

	
    //w.show();

    delete g_pCfgDataUI;
    delete g_pCfgDataNwk;
	return nReturn;
    //return a.exec();
}
