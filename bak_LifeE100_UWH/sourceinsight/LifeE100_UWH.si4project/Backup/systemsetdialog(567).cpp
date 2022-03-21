#include "systemsetdialog.h"
#include "ui_systemsetdialog.h"
#include "MyQProxyStyle.h"

#include "CConfigPanel.h"
#include "monLogframedlg.h"
#include "dataframedlg.h"
#include "cworkthread.h"
#include "updatedialog.h"

#define  TST_DATA_INDEX     0
#define  OPER_LOG_INDEX     1
#define  CFG_PARAM_INDEX    2
#define  ABOUT_INDEX        3

extern CWorkThread*   g_pWorkThread;


#if RUN_ARM_LINUX
SystemSetDialog::SystemSetDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::SystemSetDialog)
#else
SystemSetDialog::SystemSetDialog(QWidget *parent) :
    ui(new Ui::SystemSetDialog)
#endif    
{
    ui->setupUi(this);

    MyQProxyStyle *myQProxyStyle = new MyQProxyStyle();
	myQProxyStyle->SetTabWidth(160);
	myQProxyStyle->SetTabHeigth(65);
	myQProxyStyle->SetFontB(18);
    //ui->tabWidget_2->setTabPosition(QTabWidget::West);
    ui->setTabWidget->tabBar()->setStyle(myQProxyStyle);
    MyQProxyStyle *myQProxyStyle2 = new MyQProxyStyle();
    myQProxyStyle2->SetTabWidth(125);
    myQProxyStyle2->SetTabHeigth(65);
    myQProxyStyle2->SetFontB(12);
    ui->cfgTabWidget->tabBar()->setStyle(myQProxyStyle2);

	InitPourTestData();
	AddDataFrmUI();
}

SystemSetDialog::~SystemSetDialog()
{
    delete ui;
}

void SystemSetDialog::InitPourTestData(void)
{
    memset(&g_pourTstData,0,sizeof(PourTstData));

    g_pourTstData.tstInfo.unStopType = 0xFF;

    GetSystemTime(g_pourTstData.tstInfo.dtStart);	//启动时间
    GetSystemTime(g_pourTstData.tstInfo.dtEnd);     //停止时间
    g_pourTstData.tstInfo.unRecords     = 0;     //记录条数
    g_pourTstData.tstInfo.unSectorID    = 0;     //扇区ID
    g_pourTstData.tstInfo.unTotalTime   = 0;     //启动总时间，以秒为单位

	//动脉
    g_pourTstData.tstData.unADataType = 0;   //数据类型
    g_pourTstData.tstData.unASpeeSet = 0;	//转速(RPM)设定值
    g_pourTstData.tstData.unAPrssSet = 0;	//压力(mmHg)设定值
    
    g_pourTstData.tstData.unATmpVal = 0;	//温度(℃)
    g_pourTstData.tstData.unAFlowVal = 0;	//流量(ml)
    g_pourTstData.tstData.unAPrssVal = 0;	//压力(mmHg)
    g_pourTstData.tstData.unASpeeVal = 0;	//转速(RPM)
    //水浴
	g_pourTstData.tstData.unWatTmpSet = 0; //水浴温度设定值
	g_pourTstData.tstData.unWatTmpVal = 0; //水浴值(℃)
	g_pourTstData.tstData.unWatLine   = 0; //水浴水位

	//静脉
	/**/
    g_pourTstData.tstData.unVDataType = 0;   //数据类型
    g_pourTstData.tstData.unVSpeeSet = 0;	//转速(RPM)设定值
    g_pourTstData.tstData.unVPrssSet = 0;	//压力(mmHg)设定值
    
    g_pourTstData.tstData.unVTmpVal = 0;	//温度(℃)
    g_pourTstData.tstData.unVFlowVal = 0;	//流量(ml)
    g_pourTstData.tstData.unVPrssVal = 0;	//压力(mmHg)
    g_pourTstData.tstData.unVSpeeVal = 0;	//转速(RPM)
    
    GetSystemTime(g_pourTstData.tstData.dtSample);	//采样时间
}
void SystemSetDialog::GetSystemTime(DateTime& dateTime)
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    dateTime.unYear = curDateTime.date().year()-2000;
    dateTime.unMonth = curDateTime.date().month();
    dateTime.unDay  =  curDateTime.date().day();
    dateTime.unHour =  curDateTime.time().hour();
    dateTime.unMinute = curDateTime.time().minute();
    dateTime.unSecond = curDateTime.time().second();
}

void SystemSetDialog::AddDataFrmUI(void)
{
    m_pDataFrmDlg = new DataFrameDlg(ui->setTabWidget->widget(TST_DATA_INDEX));
    m_pDataFrmDlg->setGeometry(QRect(0, 20, 1200, 520));
    ui->setTabWidget->widget(TST_DATA_INDEX)->setLayout(m_pDataFrmDlg->layout());
    //灌注文件 压力曲线 转速曲线 流量曲线 温度曲线 水浴温度 详细数据
}


