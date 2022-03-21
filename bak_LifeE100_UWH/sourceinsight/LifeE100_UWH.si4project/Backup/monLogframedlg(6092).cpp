#include "MonLogFrameDlg.h"
#include "Ui_LogFrame.h"
#include "includes.h"
#include <QFileSystemModel>
#include "qcustomplot.h"

#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <QtGui>
//#include <QHostAddress>


#define MAX_CHART_TICK_COUNT    16.0
MonLogFrameDlg::MonLogFrameDlg(QWidget *parent) :
    QFrame(parent)
{

    ui = new Ui_LogFrame;
    ui->setupUi(this);

	m_unOrderColIndex = 0;//记录时间排序
	m_OpenOperLogFlag = false;
	m_unWidgetFlag = 0;
	m_unCurPar = 0;

    m_pTblViewTestDetail = NULL;  //add by bing

	
	CreateBascLogWidget();
	ShowBascLogWidget(false);
	
	CreateAlmLogWidget();
	ShowAlmLogWidget(false);
	
	CreatePourLogWidget();
	ShowPourLogWidget(false);
	
	CreateWatLogWidget();
	ShowWatLogWidget(false);

	CreatePumLogWidget();
	ShowPumLogWidget(false);

	
	CreateCtlLogWidg();
	ShowCtlLogWidg(false);
	/**/
	//ShowTestDetail();
	ShowOperLog();

    QObject::connect(ui->goFirstButton,SIGNAL(clicked()),this,SLOT(OnOpenFirst()));
    QObject::connect(ui->goLastButton,SIGNAL(clicked()),this,SLOT(OnOpenLast()));
    QObject::connect(ui->goNextButton,SIGNAL(clicked()),this,SLOT(OnOpenNext()));
	QObject::connect(ui->goEndButton,SIGNAL(clicked()),this,SLOT(OnOpenEnd()));
	QObject::connect(ui->delAllButton,SIGNAL(clicked()),this,SLOT(OnDelAllFile()));

    m_pUpdTimer = new QTimer(this);
    connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(FlashMonLogData(void)));
    m_pUpdTimer->start(1000);

}

MonLogFrameDlg::~MonLogFrameDlg()
{
    delete ui;
}

void MonLogFrameDlg::OnDelAllFile(void)
{
    QString strPathName,strDelCmd;
    QPushButton* pNewBut;
    QMessageBox  msgBox(this);
	
    strPathName  = g_devConfigInfo.basicCfgInfo.strDataPath;

    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("是否要清除所有日志?清除后会自动重启系统!");
    pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(100,30);
    pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
    pNewBut->setMinimumSize(100,30);
    //msgBox.setMinimumSize(400,100);
    SetMessageBoxFont(&msgBox);
    if(QMessageBox::AcceptRole == msgBox.exec())
    {
        //清除操作日志
		strPathName  = qApp->applicationDirPath()+"/";
		strPathName += "OperLog/";
		strDelCmd = QString("rm -r %1/*").arg(strPathName);
        SystemEx(strDelCmd.toStdString().c_str());

		//清除监控日志
		strPathName  = qApp->applicationDirPath()+"/";
		strPathName += "MonLog/";
		strDelCmd = QString("rm -r %1/*").arg(strPathName);
		
		g_operLogInfo.unOperLogCurrPar = 0;
		g_operLogInfo.unOperLogFileNum = 0;
	    SystemEx("reboot -f");
    }	

}

void MonLogFrameDlg::OnOpenFirst(void)
{
/**/
    if(m_unLogMovFlag == g_operLogInfo.unOperLogCurrPar)
    {
        return ;
    }
	
	m_unLogMovFlag = g_operLogInfo.unOperLogCurrPar;
	m_unLogNum = 1;
	ReadOperLogData((char*)&m_readLogData, 100, m_unLogMovFlag);
	ShowOperLogData();

	ShowSite(m_unLogNum);
	
}
void MonLogFrameDlg::OnOpenLast(void)
{
/**/
    if(m_unLogMovFlag == g_operLogInfo.unOperLogCurrPar)
    {
        return ;
    }
	
	if(g_operLogInfo.unOperLogFileNum >= SAVE_OPER_LOG_NUM)
    {
        if(m_unLogMovFlag == g_operLogInfo.unOperLogFileNum)
        {
            m_unLogMovFlag = 1;
        }
		else
		{
		    m_unLogMovFlag += 1;
		}
    }
	else
	{
	    m_unLogMovFlag += 1;
	}
	
	ReadOperLogData((char*)&m_readLogData, 100, m_unLogMovFlag);
	ShowOperLogData();
	m_unLogNum--;
	ShowSite(m_unLogNum);
}

void MonLogFrameDlg::OnOpenNext(void)
{/**/
    if(g_operLogInfo.unOperLogFileNum < SAVE_OPER_LOG_NUM)
    {
	    if(m_unLogMovFlag <= 1)
	    {
	        return ;
	    }
		m_unLogMovFlag -= 1;
    }
	else
	{
	    if(g_operLogInfo.unOperLogCurrPar == SAVE_OPER_LOG_NUM)
	    {
			if(m_unLogMovFlag <= 1)
			{
				return ;
			}
			m_unLogMovFlag -= 1;
	    }
		else
		{
		    if(m_unLogMovFlag-1 == g_operLogInfo.unOperLogCurrPar)
		    {
		        return ;
		    }
			
		    if(m_unLogMovFlag == 1)
		    {
		        m_unLogMovFlag = g_operLogInfo.unOperLogFileNum;
		    }
			else
			{
			    m_unLogMovFlag -= 1;
			}
		}
	}
	
	ReadOperLogData((char*)&m_readLogData, 100, m_unLogMovFlag);
	ShowOperLogData();
    m_unLogNum++;
	ShowSite(m_unLogNum);
}

void MonLogFrameDlg::OnOpenEnd(void)
{/**/
    if(g_operLogInfo.unOperLogFileNum < SAVE_OPER_LOG_NUM)
    {
        if(m_unLogMovFlag == 1)
        {
            return ;
        }
        m_unLogMovFlag = 1;
    }
	else
	{
	    if(g_operLogInfo.unOperLogCurrPar == SAVE_OPER_LOG_NUM)
	    {
			if(m_unLogMovFlag == 1)
			{
				return ;
			}
	        m_unLogMovFlag = 1;
	    }
		else
		{
			if(m_unLogMovFlag == g_operLogInfo.unOperLogCurrPar+1)
			{
				return ;
			}

		    m_unLogMovFlag = g_operLogInfo.unOperLogCurrPar+1;
		}
	}
	
	ReadOperLogData((char*)&m_readLogData, 100, m_unLogMovFlag);
	ShowOperLogData();
	m_unLogNum = g_operLogInfo.unOperLogFileNum;
	ShowSite(m_unLogNum);

}

void MonLogFrameDlg::FlashMonLogData(void)
{/**/
	if(m_OpenOperLogFlag == false)
	{
		if(g_operLogInfo.unOperLogFileNum > 0)
		{   
		    m_OpenOperLogFlag = true;
			ReadOperLogData((char*)&m_readLogData, 100, g_operLogInfo.unOperLogCurrPar);
			ShowOperLogData();
			m_unLogMovFlag = g_operLogInfo.unOperLogCurrPar;
			m_unCurPar = g_operLogInfo.unOperLogCurrPar;
			m_unLogNum = 1;
			ShowSite(m_unLogNum);

		}
	}
	if(m_unCurPar != g_operLogInfo.unOperLogCurrPar)
	{
		if(g_operLogInfo.unOperLogCurrPar == m_unLogMovFlag)
		{
		    m_unLogNum = 1;
		}
		else
		{
		    m_unLogNum++;
		}
		m_unCurPar = g_operLogInfo.unOperLogCurrPar;
		ShowSite(m_unLogNum);
	}
}

void MonLogFrameDlg::ShowSite(UINT16 site)
{/**/
	QString strNum;
    QString strPar;
    strNum = QString("%1/").arg(g_operLogInfo.unOperLogFileNum);
	strPar = QString("%1").arg(site);

    ui->label->setText(QString(strNum+strPar));
}

void MonLogFrameDlg::ShowOperLog(void)
{/**/
    //printf("enter MonLogFrameDlg::ShowOperLog \r\n");

	m_pLogComboBox = CreateComboBox(ui->tabOperLog);
	m_pLogComboBox->setGeometry(QRect(610, 345, 90, 30));
	m_pLogComboBox->hide();

	if(g_operLogInfo.unOperLogFileNum > 0)
	{
	    m_OpenOperLogFlag = true;
	    ReadOperLogData((char*)&m_readLogData, 100, g_operLogInfo.unOperLogCurrPar);
        ShowOperLogData();
		m_unLogNum = 1;
		m_unLogMovFlag = g_operLogInfo.unOperLogCurrPar;
		m_unCurPar = g_operLogInfo.unOperLogCurrPar;
	}
	ShowSite(m_unLogNum);
}

void MonLogFrameDlg::CreateBascLogWidget(void)
{
    int lEditWidth = 220;
    //QFormLayout *BeformLayout = new QFormLayout;
	//QFormLayout *LaformLayout = new QFormLayout;

    QFormLayout *formLayout[2];
	formLayout[0] = new QFormLayout;
	formLayout[1] = new QFormLayout;	
	
	m_wBascWidget[0] = new QWidget(ui->beforeGroupBox);
	m_wBascWidget[0]->setGeometry(QRect(0, 15, 630, 500));

    QHBoxLayout* pFirstRow  = new QHBoxLayout();

    QLabel *pLabel = new QLabel(m_wBascWidget[0]);
    pLabel->setMinimumSize(10,10);
    formLayout[0]->addRow(tr(" "),pLabel);

	
	m_pBascTime = new QLineEdit(m_wBascWidget[0]);
	m_pBascTime->setReadOnly(true);
	m_pBascTime->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("操作时间:"), m_pBascTime);

	m_pSysTime[0] = new QLineEdit(m_wBascWidget[0]);
	m_pSysTime[0]->setReadOnly(true);
	m_pSysTime[0]->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("设备时间:"), m_pSysTime[0]);

    lEditWidth = 60;
	m_pBascAlm[0] = new QLineEdit(m_wBascWidget[0]);
	m_pBascAlm[0]->setReadOnly(true);
	m_pBascAlm[0]->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("告警使能:"), m_pBascAlm[0]);

	m_pBascSavTmt[0] = new QLineEdit(m_wBascWidget[0]);
	m_pBascSavTmt[0]->setReadOnly(true);
	m_pBascSavTmt[0]->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("监控存储:"), m_pBascSavTmt[0]);
	m_wBascWidget[0]->setLayout(formLayout[0]);
	 

	m_wBascWidget[1] = new QWidget(ui->laterGroupBox);
	//m_wBascLater->setObjectName(QString::fromUtf8("widget2"));
	m_wBascWidget[1]->setGeometry(QRect(0, 15, 630, 500));

    pLabel = new QLabel(m_wBascWidget[1]);
    pLabel->setMinimumSize(10,10);
    formLayout[1]->addRow(tr(" "),pLabel);

	lEditWidth = 220;
	m_pSysTime[1] = new QLineEdit(m_wBascWidget[1]);
	m_pSysTime[1]->setReadOnly(true);
	m_pSysTime[1]->setMaximumWidth(lEditWidth);
	
	lEditWidth = 60;
	m_pBascAlm[1] = new QLineEdit(m_wBascWidget[1]);
	m_pBascAlm[1]->setReadOnly(true);
	m_pBascAlm[1]->setMaximumWidth(lEditWidth);

	m_pBascSavTmt[1] = new QLineEdit(m_wBascWidget[1]);
	m_pBascSavTmt[1]->setReadOnly(true);
	m_pBascSavTmt[1]->setMaximumWidth(lEditWidth);
	
    pFirstRow  = new QHBoxLayout();
	m_pLatBascSite = new QLineEdit(m_wBascWidget[1]);
	m_pLatBascSite->setMaximumWidth(lEditWidth);
	m_pLatBascSite->setReadOnly(true);
	m_pLatBascType = new QLineEdit(m_wBascWidget[1]);
	m_pLatBascType->setMaximumWidth(lEditWidth+40);
	m_pLatBascType->setReadOnly(true);
	
    AddRowItem(pFirstRow,m_pLatBascSite,tr("远程/本地:"));
    AddRowItem(pFirstRow,m_pLatBascType,tr("操作项目:"));
    formLayout[1]->addRow(pFirstRow);

    formLayout[1]->addRow(tr("设备时间:"), m_pSysTime[1]);
	formLayout[1]->addRow(tr("告警使能:"), m_pBascAlm[1]);
	formLayout[1]->addRow(tr("监控存储:"), m_pBascSavTmt[1]);
    m_wBascWidget[1]->setLayout(formLayout[1]);
}
void MonLogFrameDlg::ShowBascLogWidget(bool tFlag)
{
    if(tFlag == true)
    {
		m_wBascWidget[0]->show();
		m_wBascWidget[1]->show();
    }
	else
	{
		m_wBascWidget[0]->hide();
		m_wBascWidget[1]->hide();
	}
}

void MonLogFrameDlg::CreateAlmLogWidget(void)
{
    int lEditWidth = 220;//long
    QFormLayout *formLayout[2];
	formLayout[0] = new QFormLayout;
	formLayout[1] = new QFormLayout;

	//formLayout[0]->setHorizontalSpacing(20);
	//formLayout[1]->setHorizontalSpacing(20);
	
	m_wAlmWidget[0] = new QWidget(ui->beforeGroupBox);
	m_wAlmWidget[0]->setGeometry(QRect(0, 15, 630, 500));

	QLabel *pLabel[2];
	pLabel[0] = new QLabel(m_wAlmWidget[0]);//
	pLabel[0]->setMinimumSize(10,30);
	formLayout[0]->addRow(tr(""),pLabel[0]);

	m_pBefAlmTime = new QLineEdit(m_wAlmWidget[0]);
	m_pBefAlmTime->setReadOnly(true);
	m_pBefAlmTime->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("操作时间:"), m_pBefAlmTime);

    lEditWidth = 60;
	m_wAlmWidget[1] = new QWidget(ui->laterGroupBox);
	m_wAlmWidget[1]->setGeometry(QRect(0, 15, 630, 500));
    QHBoxLayout* pFirstRow  = new QHBoxLayout();

	pLabel[1] = new QLabel(m_wAlmWidget[1]);//
	pLabel[1]->setMinimumSize(10,30);
	formLayout[1]->addRow(tr(""),pLabel[1]);

	m_pLatAlmSite = new QLineEdit(m_wAlmWidget[1]);
	m_pLatAlmSite->setMaximumWidth(lEditWidth);
	m_pLatAlmSite->setReadOnly(true);
	m_pLatAlmType = new QLineEdit(m_wAlmWidget[1]);
	m_pLatAlmType->setMaximumWidth(lEditWidth+40);
	m_pLatAlmType->setReadOnly(true);
    AddRowItem(pFirstRow,m_pLatAlmSite,tr("远程/本地:"));
    AddRowItem(pFirstRow,m_pLatAlmType,tr("操作项目:"));
    formLayout[1]->addRow(pFirstRow);

    
    for(UINT8 i = 0; i < 2; i++)
    {
        pLabel[i] = new QLabel(m_wAlmWidget[i]);//
        pLabel[i]->setMinimumSize(300,30);
        pLabel[i]->setText(tr("--动脉泵告警配置--"));
        formLayout[i]->addRow(tr(""),pLabel[i]);
	
	    lEditWidth = 100;
		m_pAlmUPresA[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmUPresA[i]->setReadOnly(true);
		m_pAlmUPresA[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("压力上限:"), m_pAlmUPresA[i]);
		
		m_pAlmUFlowA[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmUFlowA[i]->setReadOnly(true);
		m_pAlmUFlowA[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("流量上限:"), m_pAlmUFlowA[i]);
		m_pAlmLFlowA[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmLFlowA[i]->setReadOnly(true);
		m_pAlmLFlowA[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("流量下限:"), m_pAlmLFlowA[i]);
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pAlmUFlowA[i],tr("流量上限:"));
		AddRowItem(pFirstRow,m_pAlmLFlowA[i],tr("流量下限:"));
		formLayout[i]->addRow(pFirstRow);

        pLabel[i] = new QLabel(m_wAlmWidget[i]);//
        pLabel[i]->setMinimumSize(300,30);
        pLabel[i]->setText(tr("--静脉泵告警配置--"));
        formLayout[i]->addRow(tr(""),pLabel[i]);
		
		m_pAlmUPresV[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmUPresV[i]->setReadOnly(true);
		m_pAlmUPresV[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("压力上限:"), m_pAlmUPresV[i]);
		
		m_pAlmUFlowV[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmUFlowV[i]->setReadOnly(true);
		m_pAlmUFlowV[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("流量上限:"), m_pAlmUFlowV[i]);
		m_pAlmLFlowV[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmLFlowV[i]->setReadOnly(true);
		m_pAlmLFlowV[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("流量下限:"), m_pAlmLFlowV[i]);
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pAlmUFlowV[i],tr("流量上限:"));
		AddRowItem(pFirstRow,m_pAlmLFlowV[i],tr("流量下限:"));
		formLayout[i]->addRow(pFirstRow);

        pLabel[i] = new QLabel(m_wAlmWidget[i]);//
        pLabel[i]->setMinimumSize(300,30);
        pLabel[i]->setText(tr("--水浴告警配置--"));
        formLayout[i]->addRow(tr(""),pLabel[i]);
		
		m_pAlmUWatTmp[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmUWatTmp[i]->setReadOnly(true);
		m_pAlmUWatTmp[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("温度上限:"), m_pAlmUWatTmp[i]);
		m_pAlmUWatLin[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmUWatLin[i]->setReadOnly(true);
		m_pAlmUWatLin[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("水位上限:"), m_pAlmUWatLin[i]);
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pAlmUWatTmp[i],tr("温度上限:"));
		AddRowItem(pFirstRow,m_pAlmUWatLin[i],tr("水位上限:"));
		formLayout[i]->addRow(pFirstRow);

		m_pAlmLWatLin[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmLWatLin[i]->setReadOnly(true);
		m_pAlmLWatLin[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("水位下限:"), m_pAlmLWatLin[i]);
		m_pAlmLBloodLin[i] = new QLineEdit(m_wAlmWidget[i]);
		m_pAlmLBloodLin[i]->setReadOnly(true);
		m_pAlmLBloodLin[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("血位下限:"), m_pAlmLBloodLin[i]);
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pAlmLBloodLin[i],tr("血位下限:"));
		AddRowItem(pFirstRow,m_pAlmLWatLin[i],tr("水位下限:"));
		formLayout[i]->addRow(pFirstRow);
		
		m_wAlmWidget[i]->setLayout(formLayout[i]);
    }
}
void MonLogFrameDlg::ShowAlmLogWidget(bool tFlag)
{
    if(tFlag == true)
    {
		m_wAlmWidget[0]->show();
		m_wAlmWidget[1]->show();
    }
	else
	{
		m_wAlmWidget[0]->hide();
		m_wAlmWidget[1]->hide();
	}
}

void MonLogFrameDlg::CreatePourLogWidget(void)
{
    int lEditWidth = 220;//long
    QFormLayout *formLayout[2];
	formLayout[0] = new QFormLayout;
	formLayout[1] = new QFormLayout;
	
	//formLayout[0]->setHorizontalSpacing(20);
	//formLayout[1]->setHorizontalSpacing(20);
	
	m_wPourWidget[0] = new QWidget(ui->beforeGroupBox);
	m_wPourWidget[0]->setGeometry(QRect(0, 15, 630, 500));

	QLabel *pLabel[2];
	pLabel[0] = new QLabel(m_wPourWidget[0]);//
	pLabel[0]->setMinimumSize(10,30);
	formLayout[0]->addRow(tr(""),pLabel[0]);

	m_pBefPourTime = new QLineEdit(m_wPourWidget[0]);
	m_pBefPourTime->setReadOnly(true);
	m_pBefPourTime->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("操作时间:"), m_pBefPourTime);

    lEditWidth = 60;
	m_wPourWidget[1] = new QWidget(ui->laterGroupBox);
	m_wPourWidget[1]->setGeometry(QRect(0, 15, 630, 500));
	
	QHBoxLayout* pFirstRow  = new QHBoxLayout();
	
	pLabel[1] = new QLabel(m_wPourWidget[1]);//
	pLabel[1]->setMinimumSize(10,30);
	formLayout[1]->addRow(tr(""),pLabel[1]);

	m_pLatPourSite = new QLineEdit(m_wPourWidget[1]);
	m_pLatPourSite->setMaximumWidth(lEditWidth);
	m_pLatPourSite->setReadOnly(true);
	
	m_pLatPourType = new QLineEdit(m_wPourWidget[1]);
	m_pLatPourType->setMaximumWidth(lEditWidth+40);
	m_pLatPourType->setReadOnly(true);
    AddRowItem(pFirstRow,m_pLatPourSite,tr("远程/本地:"));
    AddRowItem(pFirstRow,m_pLatPourType,tr("操作项目:"));
    formLayout[1]->addRow(pFirstRow);

   
    //QHBoxLayout* pFirstRow1[2];//  = new QHBoxLayout();
    for(UINT8 i = 0; i < 2; i++)
    {
        pLabel[i] = new QLabel(m_wPourWidget[i]);//
        pLabel[i]->setMinimumSize(300,30);
        pLabel[i]->setText(tr("--动脉泵安全配置--"));
        formLayout[i]->addRow(tr(""),pLabel[i]);
		
	    lEditWidth = 100;
		m_pPourUPresA[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUPresA[i]->setReadOnly(true);
		m_pPourUPresA[i]->setMaximumWidth(lEditWidth);

		m_pPourUSpeeA[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUSpeeA[i]->setReadOnly(true);
		m_pPourUSpeeA[i]->setMaximumWidth(lEditWidth);
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pPourUPresA[i],tr("压力上限:"));
		AddRowItem(pFirstRow,m_pPourUSpeeA[i],tr("转速上限:"));
		formLayout[i]->addRow(pFirstRow);
		
		m_pPourUFlowA[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUFlowA[i]->setReadOnly(true);
		m_pPourUFlowA[i]->setMaximumWidth(lEditWidth);
		
		m_pPourLFlowA[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourLFlowA[i]->setReadOnly(true);
		m_pPourLFlowA[i]->setMaximumWidth(lEditWidth);

		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pPourUFlowA[i],tr("流量上限:"));
		AddRowItem(pFirstRow,m_pPourLFlowA[i],tr("流量下限:"));
		formLayout[i]->addRow(pFirstRow);
		
        pLabel[i] = new QLabel(m_wPourWidget[i]);//
        pLabel[i]->setMinimumSize(300,30);
        pLabel[i]->setText(tr("--静脉泵安全配置--"));
        formLayout[i]->addRow(tr(""),pLabel[i]);
		
		m_pPourUPresV[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUPresV[i]->setReadOnly(true);
		m_pPourUPresV[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("压力上限:"), m_pPourUPresV[i]);
		m_pPourUSpeeV[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUSpeeV[i]->setReadOnly(true);
		m_pPourUSpeeV[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("转速上限:"), m_pPourUSpeeV[i]);		
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pPourUPresV[i],tr("压力上限:"));
		AddRowItem(pFirstRow,m_pPourUSpeeV[i],tr("转速上限:"));
		formLayout[i]->addRow(pFirstRow);

		m_pPourUFlowV[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUFlowV[i]->setReadOnly(true);
		m_pPourUFlowV[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("流量上限:"), m_pPourUFlowV[i]);
		m_pPourLFlowV[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourLFlowV[i]->setReadOnly(true);
		m_pPourLFlowV[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("流量下限:"), m_pPourLFlowV[i]);
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pPourUFlowV[i],tr("流量上限:"));
		AddRowItem(pFirstRow,m_pPourLFlowV[i],tr("流量下限:"));
		formLayout[i]->addRow(pFirstRow);

        pLabel[i] = new QLabel(m_wPourWidget[i]);//
        pLabel[i]->setMinimumSize(300,30);
        pLabel[i]->setText(tr("--水浴安全配置--"));
        formLayout[i]->addRow(tr(""),pLabel[i]);
		
		m_pPourUWatTmp[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUWatTmp[i]->setReadOnly(true);
		m_pPourUWatTmp[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("温度上限:"), m_pPourUWatTmp[i]);		
		m_pPourUWatLin[i] = new QLineEdit(m_wPourWidget[i]);
		m_pPourUWatLin[i]->setReadOnly(true);
		m_pPourUWatLin[i]->setMaximumWidth(lEditWidth);
		//formLayout[i]->addRow(tr("水位下限:"), m_pPourUWatLin[i]);
		pFirstRow  = new QHBoxLayout();
		AddRowItem(pFirstRow,m_pPourUWatTmp[i],tr("温度上限:"));
		AddRowItem(pFirstRow,m_pPourUWatLin[i],tr("水位下限:"));
		formLayout[i]->addRow(pFirstRow);

		m_wPourWidget[i]->setLayout(formLayout[i]);
    }
}
void MonLogFrameDlg::ShowPourLogWidget(bool tFlag)
{
    if(tFlag == true)
    {
		m_wPourWidget[0]->show();
		m_wPourWidget[1]->show();
    }
	else
	{
		m_wPourWidget[0]->hide();
		m_wPourWidget[1]->hide();
	}
}


void MonLogFrameDlg::CreateWatLogWidget(void)
{
    int lEditWidth = 220;//long
    QFormLayout *formLayout[2];
	formLayout[0] = new QFormLayout;
	formLayout[1] = new QFormLayout;
		
	m_wWatWidget[0] = new QWidget(ui->beforeGroupBox);
	m_wWatWidget[0]->setGeometry(QRect(0, 15, 630, 500));

	QLabel *pLabel[2];
	pLabel[0] = new QLabel(m_wWatWidget[0]);//
	pLabel[0]->setMinimumSize(10,30);
	formLayout[0]->addRow(tr(""),pLabel[0]);

	m_pBefWatTime = new QLineEdit(m_wWatWidget[0]);
	m_pBefWatTime->setReadOnly(true);
	m_pBefWatTime->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("操作时间:"), m_pBefWatTime);

    lEditWidth = 60;
	m_wWatWidget[1] = new QWidget(ui->laterGroupBox);
	m_wWatWidget[1]->setGeometry(QRect(0, 15, 630, 500));
	
	QHBoxLayout* pFirstRow  = new QHBoxLayout();
	
	pLabel[1] = new QLabel(m_wWatWidget[1]);//
	pLabel[1]->setMinimumSize(10,30);
	formLayout[1]->addRow(tr(""),pLabel[1]);

	m_pLatWatSite = new QLineEdit(m_wWatWidget[1]);
	m_pLatWatSite->setMaximumWidth(lEditWidth);
	m_pLatWatSite->setReadOnly(true);
	
	m_pLatWatType = new QLineEdit(m_wWatWidget[1]);
	m_pLatWatType->setMaximumWidth(lEditWidth+40);
	m_pLatWatType->setReadOnly(true);
    AddRowItem(pFirstRow,m_pLatWatSite,tr("远程/本地:"));
    AddRowItem(pFirstRow,m_pLatWatType,tr("操作项目:"));
    formLayout[1]->addRow(pFirstRow);


    for(int i = 0; i < 2; i++)
    {
	    lEditWidth = 100;

		m_pWatEnFlag[i] = new QLineEdit(m_wWatWidget[i]);
		m_pWatEnFlag[i]->setReadOnly(true);
		m_pWatEnFlag[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("使用状态:"), m_pWatEnFlag[i]);
		m_pWatTmpVal[i] = new QLineEdit(m_wWatWidget[i]);
		m_pWatTmpVal[i]->setReadOnly(true);
		m_pWatTmpVal[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("水浴温度:"), m_pWatTmpVal[i]);

		m_wWatWidget[i]->setLayout(formLayout[i]);
    }
}
void MonLogFrameDlg::ShowWatLogWidget(bool tFlag)
{
    if(tFlag == true)
    {
		m_wWatWidget[0]->show();
		m_wWatWidget[1]->show();
    }
	else
	{
		m_wWatWidget[0]->hide();
		m_wWatWidget[1]->hide();
	}
}

void MonLogFrameDlg::CreatePumLogWidget(void)
{
    int lEditWidth = 220;//long
    QFormLayout *formLayout[2];
	formLayout[0] = new QFormLayout;
	formLayout[1] = new QFormLayout;
		
	m_wPumWidget[0] = new QWidget(ui->beforeGroupBox);
	m_wPumWidget[0]->setGeometry(QRect(0, 15, 630, 500));

	QLabel *pLabel[2];
	pLabel[0] = new QLabel(m_wPumWidget[0]);//
	pLabel[0]->setMinimumSize(10,30);
	formLayout[0]->addRow(tr(""),pLabel[0]);

	m_pBefPumTime = new QLineEdit(m_wPumWidget[0]);
	m_pBefPumTime->setReadOnly(true);
	m_pBefPumTime->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("操作时间:"), m_pBefPumTime);

    lEditWidth = 60;
	m_wPumWidget[1] = new QWidget(ui->laterGroupBox);
	m_wPumWidget[1]->setGeometry(QRect(0, 15, 630, 500));
	
	QHBoxLayout* pFirstRow  = new QHBoxLayout();
	
	pLabel[1] = new QLabel(m_wPumWidget[1]);//
	pLabel[1]->setMinimumSize(10,30);
	formLayout[1]->addRow(tr(""),pLabel[1]);

	m_pLatPumSite = new QLineEdit(m_wPumWidget[1]);
	m_pLatPumSite->setMaximumWidth(lEditWidth);
	m_pLatPumSite->setReadOnly(true);
	
	m_pLatPumType = new QLineEdit(m_wPumWidget[1]);
	m_pLatPumType->setMaximumWidth(lEditWidth+40);
	m_pLatPumType->setReadOnly(true);
    AddRowItem(pFirstRow,m_pLatPumSite,tr("远程/本地:"));
    AddRowItem(pFirstRow,m_pLatPumType,tr("操作项目:"));
    formLayout[1]->addRow(pFirstRow);


    for(int i = 0; i < 2; i++)
    {
	    lEditWidth = 100;

		m_pPumEnFlag[i] = new QLineEdit(m_wPumWidget[i]);
		m_pPumEnFlag[i]->setReadOnly(true);
		m_pPumEnFlag[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("使用状态:"), m_pPumEnFlag[i]);
		
		m_pPumPreeVal[i] = new QLineEdit(m_wPumWidget[i]);
		m_pPumPreeVal[i]->setReadOnly(true);
		m_pPumPreeVal[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("血泵压力:"), m_pPumPreeVal[i]);

		m_pPumSpeeVal[i] = new QLineEdit(m_wPumWidget[i]);
		m_pPumSpeeVal[i]->setReadOnly(true);
		m_pPumSpeeVal[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("血泵转速:"), m_pPumSpeeVal[i]);

		m_wPumWidget[i]->setLayout(formLayout[i]);
    }
}
void MonLogFrameDlg::ShowPumLogWidget(bool tFlag)
{
    if(tFlag == true)
    {
		m_wPumWidget[0]->show();
		m_wPumWidget[1]->show();
    }
	else
	{
		m_wPumWidget[0]->hide();
		m_wPumWidget[1]->hide();
	}
}


void MonLogFrameDlg::CreateCtlLogWidg(void)
{
    int lEditWidth = 220;//long
    QFormLayout *formLayout[2];
	formLayout[0] = new QFormLayout;
	formLayout[1] = new QFormLayout;
	
	m_wCtlWidget[0] = new QWidget(ui->beforeGroupBox);
	m_wCtlWidget[0]->setGeometry(QRect(0, 15, 630, 500));

	QLabel *pLabel[2];
	pLabel[0] = new QLabel(m_wPumWidget[0]);//
	pLabel[0]->setMinimumSize(10,30);
	formLayout[0]->addRow(tr(""),pLabel[0]);
	
	m_pBefCtlTime = new QLineEdit(m_wCtlWidget[0]);
	m_pBefCtlTime->setReadOnly(true);
	m_pBefCtlTime->setMaximumWidth(lEditWidth);
	formLayout[0]->addRow(tr("操作时间:"), m_pBefCtlTime);

    lEditWidth = 60;
	m_wCtlWidget[1] = new QWidget(ui->laterGroupBox);
	m_wCtlWidget[1]->setGeometry(QRect(0, 15, 390, 321));
    QHBoxLayout* pFirstRow  = new QHBoxLayout();

	pLabel[1] = new QLabel(m_wPumWidget[1]);//
	pLabel[1]->setMinimumSize(10,30);
	formLayout[1]->addRow(tr(""),pLabel[1]);
	
	m_pLatCtlSite = new QLineEdit(m_wCtlWidget[1]);
	m_pLatCtlSite->setMaximumWidth(lEditWidth);
	m_pLatCtlSite->setReadOnly(true);
	m_pLatCtlType = new QLineEdit(m_wCtlWidget[1]);
	m_pLatCtlType->setMaximumWidth(lEditWidth+40);
	m_pLatCtlType->setReadOnly(true);
    AddRowItem(pFirstRow,m_pLatCtlSite,tr("远程/本地:"));
    AddRowItem(pFirstRow,m_pLatCtlType,tr("操作项目:"));
    formLayout[1]->addRow(pFirstRow);

    for(int i = 0; i < 2; i++)
    {
	    lEditWidth = 100;

		m_pOperType[i] = new QLineEdit(m_wCtlWidget[i]);
		m_pOperType[i]->setReadOnly(true);
		m_pOperType[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("状态/启停:"), m_pOperType[i]);
		m_pResult[i] = new QLineEdit(m_wCtlWidget[i]);
		m_pResult[i]->setReadOnly(true);
		m_pResult[i]->setMaximumWidth(lEditWidth);
		formLayout[i]->addRow(tr("成功/失败:"), m_pResult[i]);

		m_wCtlWidget[i]->setLayout(formLayout[i]);
    }
}
void MonLogFrameDlg::ShowCtlLogWidg(bool tFlag)
{
    if(tFlag == true)
    {
		m_wCtlWidget[0]->show();
		m_wCtlWidget[1]->show();
    }
	else
	{
		m_wCtlWidget[0]->hide();
		m_wCtlWidget[1]->hide();
	}
}




QString MonLogFrameDlg::GetEnFlag(UINT8 enFlag)
{
    QString reString = "启用";

	if(enFlag == 0)
	{
	    reString = "禁用";
	}
	
	return reString;
}


QString MonLogFrameDlg::GetStite(UINT8 stite)
{
    QString reString = "远程";

	if(stite == 0)
	{
	    reString = "本地";
	}
	else if(stite == 2)
	{
		reString = "系统";
	}

	return reString;
}


QString MonLogFrameDlg::GetIpFlag(UINT8 IpFlag)
{
    QString reString = "静态分配";

	if(IpFlag == 0)
	{
	    reString = "动态分配";
	}
	
	return reString;
}

QString MonLogFrameDlg::GetOperResult(UINT8 result)
{
    QString reString = "成功";

	if(result == 2)
	{
	    reString = "失败";
	}
	else if(result == 0)
	{
	    reString = "无操作";
	}

	
	return reString;
}

QString MonLogFrameDlg::GetOperType(UINT8 type, UINT8 unLogType)
{
    QString reString;
	
    if(unLogType == OPER_CTRL_TYPE_POUR)
    {
        reString = "灌注";
		if(type == 0)
		{
		    reString = "预灌注";
		}
    }
    else
    {
        reString = "启动";
		if(type == 0)
		{
		    reString = "停止";
		}
    }

	return reString;
}

void MonLogFrameDlg::HideOrShowWidget(bool tFlag)
{

	switch(m_unWidgetFlag)
	{
	    case OPER_LOG_TYPE_BAS:
			ShowBascLogWidget(tFlag);
			break;
	    case OPER_LOG_TYPE_ALM:
			ShowAlmLogWidget(tFlag);
			break;
		case OPER_LOG_TYPE_POUR:
			ShowPourLogWidget(tFlag);
			break;
		case OPER_LOG_TYPE_WAT:
			ShowWatLogWidget(tFlag);
			break;
		case OPER_LOG_TYPE_PUM:
			ShowPumLogWidget(tFlag);
			break;	
		case OPER_CTRL_TYPE_PUM:
		case OPER_CTRL_TYPE_WAT:
		case OPER_CTRL_TYPE_POUR:
		case OPER_SYS_TYPE_REST:
			ShowCtlLogWidg(tFlag);
			break;

		default:break;
	}

}


void MonLogFrameDlg::ShowOperLogData(void)
{
    UINT8 logType = m_readLogData[0];
    //QHostAddress qHostAddr;
	QString tmpStr;

	if(m_unWidgetFlag != logType)
	{
	    HideOrShowWidget(false);
		m_unWidgetFlag = logType;
		HideOrShowWidget(true);
	}
	switch(logType)
	{
	    case OPER_LOG_TYPE_BAS:
			OperLogBasic *operLogBasic;
			operLogBasic = (OperLogBasic*)m_readLogData;
            m_pBascTime->setText(DateTimeToString(&operLogBasic->dtCreate,true));
			m_pLatBascSite->setText(GetStite(operLogBasic->unSite));
            m_pLatBascType->setText("基本配置");

            for(UINT8 i = 0; i < 2; i++)
            {
				m_pBascAlm[i]->setText(GetEnFlag(operLogBasic->unAlmEnFlag[i]));
				SetTextShowColor(m_pBascAlm[i], (UINT32)operLogBasic->unAlmEnFlag[0],\
					                            (UINT32)operLogBasic->unAlmEnFlag[1]);

				m_pBascSavTmt[i]->setText(QString("%1").arg(operLogBasic->unMonSavTmt[i]));
				SetTextShowColor(m_pBascSavTmt[i], (UINT32)operLogBasic->unMonSavTmt[0],\
					                            (UINT32)operLogBasic->unMonSavTmt[1]);

				m_pSysTime[i]->setText(DateTimeToString(&operLogBasic->dtSystem[i],true));
				/**/
				QDateTime dateTime1;
    			QDateTime dateTime2;
				dateTime1 = DateTimeToQDateTime(&operLogBasic->dtSystem[0],true);
				dateTime2 = DateTimeToQDateTime(&operLogBasic->dtSystem[1],true);
				SetTextShowColor(m_pSysTime[i], (UINT32)dateTime1.toMSecsSinceEpoch(),\
	                            (UINT32)dateTime2.toMSecsSinceEpoch());
            }
			break;
			
	    case OPER_LOG_TYPE_ALM:
			OperLogAlm *operLogAlm;
			
			operLogAlm = (OperLogAlm*)m_readLogData;
			m_pBefAlmTime->setText(DateTimeToString(&operLogAlm->dtCreate,true));
			m_pLatAlmSite->setText(GetStite(operLogAlm->unSite));
			m_pLatAlmType->setText("告警配置");
            for(int i = 0; i < 2; i++)
            {
                m_pAlmUPresA[i]->setText(ValueToString(operLogAlm->unAlmUPresA[i],10,1));
				SetTextShowColor(m_pAlmUPresA[i], (UINT32)operLogAlm->unAlmUPresA[0],\
					                              (UINT32)operLogAlm->unAlmUPresA[1]);

				m_pAlmUFlowA[i]->setText(QString("%1").arg(operLogAlm->unAlmUFlowA[i]));
				SetTextShowColor(m_pAlmUFlowA[i], (UINT32)operLogAlm->unAlmUFlowA[0],\
					                              (UINT32)operLogAlm->unAlmUFlowA[1]);

				m_pAlmLFlowA[i]->setText(QString("%1").arg(operLogAlm->unAlmLFlowA[i]));
				SetTextShowColor(m_pAlmLFlowA[i], (UINT32)operLogAlm->unAlmLFlowA[0],\
					                              (UINT32)operLogAlm->unAlmLFlowA[1]);

				
				m_pAlmUPresV[i]->setText(ValueToString(operLogAlm->unAlmUPresV[i],10,1));
				SetTextShowColor(m_pAlmUPresV[i], (UINT32)operLogAlm->unAlmUPresV[0],\
					                              (UINT32)operLogAlm->unAlmUPresV[1]);

				m_pAlmUFlowV[i]->setText(QString("%1").arg(operLogAlm->unAlmUFlowV[i]));
				SetTextShowColor(m_pAlmUFlowV[i], (UINT32)operLogAlm->unAlmUFlowV[0],\
					                              (UINT32)operLogAlm->unAlmUFlowV[1]);

				m_pAlmLFlowV[i]->setText(QString("%1").arg(operLogAlm->unAlmLFlowV[i]));
				SetTextShowColor(m_pAlmLFlowV[i], (UINT32)operLogAlm->unAlmLFlowV[0],\
					                              (UINT32)operLogAlm->unAlmLFlowV[1]);

				m_pAlmUWatTmp[i]->setText(ValueToString(operLogAlm->unAlmUWatTmp[i],10,1));
				SetTextShowColor(m_pAlmUWatTmp[i], (UINT32)operLogAlm->unAlmUWatTmp[0],\
					                              (UINT32)operLogAlm->unAlmUWatTmp[1]);

				m_pAlmUWatLin[i]->setText(QString("%1").arg(operLogAlm->unAlmUWatLin[i]));
				SetTextShowColor(m_pAlmUWatLin[i], (UINT32)operLogAlm->unAlmUWatLin[0],\
					                              (UINT32)operLogAlm->unAlmUWatLin[1]);

				m_pAlmLWatLin[i]->setText(QString("%1").arg(operLogAlm->unAlmLWatLin[i]));
				SetTextShowColor(m_pAlmLWatLin[i], (UINT32)operLogAlm->unAlmLWatLin[0],\
					                              (UINT32)operLogAlm->unAlmLWatLin[1]);

				m_pAlmLBloodLin[i]->setText(QString("%1").arg(operLogAlm->unAlmBloodLin[i]));
				SetTextShowColor(m_pAlmLBloodLin[i], (UINT32)operLogAlm->unAlmBloodLin[0],\
					                              (UINT32)operLogAlm->unAlmBloodLin[1]);
            }
			break;
			
		case OPER_LOG_TYPE_POUR:
			OperLogPour *operLogPour;
			
			operLogPour = (OperLogPour*)m_readLogData;
			m_pBefPourTime->setText(DateTimeToString(&operLogPour->dtCreate,true));
			m_pLatPourSite->setText(GetStite(operLogPour->unSite));
			m_pLatPourType->setText("安全配置");
            for(int i = 0; i < 2; i++)
            {
                m_pPourUPresA[i]->setText(ValueToString(operLogPour->unPourUPresA[i],10,1));
				SetTextShowColor(m_pPourUPresA[i], (UINT32)operLogPour->unPourUPresA[0],\
					                              (UINT32)operLogPour->unPourUPresA[1]);

				m_pPourUSpeeA[i]->setText(QString("%1").arg(operLogPour->unPourUSpeeA[i]));
				SetTextShowColor(m_pPourUSpeeA[i], (UINT32)operLogPour->unPourUSpeeA[0],\
					                              (UINT32)operLogPour->unPourUSpeeA[1]);

				m_pPourUFlowA[i]->setText(QString("%1").arg(operLogPour->unPourUFlowA[i]));
				SetTextShowColor(m_pPourUFlowA[i], (UINT32)operLogPour->unPourUFlowA[0],\
					                              (UINT32)operLogPour->unPourUFlowA[1]);

				m_pPourLFlowA[i]->setText(QString("%1").arg(operLogPour->unPourLFlowA[i]));
				SetTextShowColor(m_pPourLFlowA[i], (UINT32)operLogPour->unPourLFlowA[0],\
					                              (UINT32)operLogPour->unPourLFlowA[1]);

				m_pPourUPresV[i]->setText(ValueToString(operLogPour->unPourUPresV[i],10,1));
				SetTextShowColor(m_pPourUPresV[i], (UINT32)operLogPour->unPourUPresV[0],\
					                              (UINT32)operLogPour->unPourUPresV[1]);

				m_pPourUSpeeV[i]->setText(QString("%1").arg(operLogPour->unPourUSpeeA[i]));
				SetTextShowColor(m_pPourUSpeeV[i], (UINT32)operLogPour->unPourUSpeeA[0],\
					                              (UINT32)operLogPour->unPourUSpeeA[1]);

				m_pPourUFlowV[i]->setText(QString("%1").arg(operLogPour->unPourUFlowV[i]));
				SetTextShowColor(m_pPourUFlowV[i], (UINT32)operLogPour->unPourUFlowV[0],\
					                              (UINT32)operLogPour->unPourUFlowV[1]);

				m_pPourLFlowV[i]->setText(QString("%1").arg(operLogPour->unPourLFlowV[i]));
				SetTextShowColor(m_pPourLFlowV[i], (UINT32)operLogPour->unPourLFlowV[0],\
					                              (UINT32)operLogPour->unPourLFlowV[1]);


				m_pPourUWatTmp[i]->setText(ValueToString(operLogPour->unPourUWatTmp[i],10,1));
				SetTextShowColor(m_pPourUWatTmp[i], (UINT32)operLogPour->unPourUWatTmp[0],\
					                              (UINT32)operLogPour->unPourUWatTmp[1]);

				m_pPourUWatLin[i]->setText(QString("%1").arg(operLogPour->unPourWatLin[i]));
				SetTextShowColor(m_pPourUWatLin[i], (UINT32)operLogPour->unPourWatLin[0],\
					                              (UINT32)operLogPour->unPourWatLin[1]);
            }
			break;
			
		case OPER_LOG_TYPE_WAT:
			OperLogWatDev *operLogWatDev;			
			operLogWatDev = (OperLogWatDev*)m_readLogData;
			m_pBefWatTime->setText(DateTimeToString(&operLogWatDev->dtCreate,true));
			m_pLatWatSite->setText(GetStite(operLogWatDev->unSite));
			m_pLatWatType->setText("水浴模块");
			for(int i = 0; i < 2; i ++)
			{
				m_pWatEnFlag[i]->setText(GetEnFlag(operLogWatDev->unEnFlag[i]));		//使用状态
				SetTextShowColor(m_pWatEnFlag[i], (UINT32)operLogWatDev->unEnFlag[0],\
					                              (UINT32)operLogWatDev->unEnFlag[1]);
				m_pWatTmpVal[i]->setText(ValueToString(operLogWatDev->unTmpVal[i],10,1));
				SetTextShowColor(m_pWatTmpVal[i], (UINT32)operLogWatDev->unTmpVal[0],\
					                              (UINT32)operLogWatDev->unTmpVal[1]);
			}
			break;

		case OPER_LOG_TYPE_PUM:
			OperLogPumDev *operLogPumDev;			
			operLogPumDev = (OperLogPumDev*)m_readLogData;
			m_pBefPumTime->setText(DateTimeToString(&operLogPumDev->dtCreate,true));
			m_pLatPumSite->setText(GetStite(operLogPumDev->unSite));
			m_pLatPumType->setText("血泵模块");
			for(int i = 0; i < 2; i ++)
			{
				m_pPumEnFlag[i]->setText(GetEnFlag(operLogPumDev->unEnFlag[i]));		//使用状态
				SetTextShowColor(m_pPumEnFlag[i], (UINT32)operLogPumDev->unEnFlag[0],\
					                              (UINT32)operLogPumDev->unEnFlag[1]);
				
				m_pPumPreeVal[i]->setText(ValueToString(operLogPumDev->unPress[i],10,1));
				SetTextShowColor(m_pPumPreeVal[i], (UINT32)operLogPumDev->unPress[0],\
					                              (UINT32)operLogPumDev->unPress[1]);
				
				m_pPumSpeeVal[i]->setText(QString("%1").arg(operLogPumDev->unSpeed[i]));
				SetTextShowColor(m_pPumSpeeVal[i], (UINT32)operLogPumDev->unSpeed[0],\
					                              (UINT32)operLogPumDev->unSpeed[1]);
			}
			break;
			/**/
		case OPER_CTRL_TYPE_PUM:
		case OPER_CTRL_TYPE_WAT:
		case OPER_CTRL_TYPE_POUR:
		case OPER_SYS_TYPE_REST:
			OperLogCtl *operLogCtl; 
		
			operLogCtl = (OperLogCtl*)m_readLogData;
			m_pBefCtlTime->setText(DateTimeToString(&operLogCtl->dtCreate,true));
			m_pLatCtlSite->setText(GetStite(operLogCtl->unSite));

			if(OPER_CTRL_TYPE_PUM == logType)
			{
			    tmpStr = "血泵开关";
			}
			else if(OPER_CTRL_TYPE_WAT == logType)
			{
			    tmpStr = "水浴开关";
			}
			else if(OPER_CTRL_TYPE_POUR == logType)
			{
			    tmpStr = "灌注模式";
			}
			else if(OPER_SYS_TYPE_REST == logType)
			{
			    tmpStr = "系统重启";
			}			
			m_pLatCtlType->setText(tmpStr);

            for(int i = 0; i < 2; i++)
            {
				m_pOperType[i]->setText(GetOperType(operLogCtl->unOperType[i],logType));
				SetTextShowColor(m_pOperType[i], (UINT32)operLogCtl->unOperType[0],\
					                             (UINT32)operLogCtl->unOperType[1]);
				
				m_pResult[i]->setText(GetOperResult(operLogCtl->unResult[i]));
				SetTextShowColor(m_pResult[i], (UINT32)operLogCtl->unResult[0],\
					                            (UINT32)operLogCtl->unResult[1]);
            }
			break;
		default:break;
	}
}

//设置显示底色
void MonLogFrameDlg::SetTextShowColor(QLineEdit* pLineEdit, UINT32 unNmb1, UINT32 unNmb2)
{
	if(unNmb1 != unNmb2)
	{
		pLineEdit->setStyleSheet("background-color:rgb(255,255,0)");
	}
	else
	{
	   pLineEdit->setStyleSheet("background-color:lightblue");
	}
}

void MonLogFrameDlg::ShowTestDetail(void)
{
    //printf("enter ===MonLogFrameDlg::ShowTestDetail\r\n");
    QStandardItemModel* pItemModel;
    QStandardItem* pNewItem;
    QStringList strColNames;
    ulong lColIndex;
    ulong lRowIndex;
	int unlColSizes[FILE_COL_ITEMS];//long

    ui->logTabWidget->setCursor(Qt::WaitCursor);

    strColNames <<"采样时间"<<"类型"<<"压力设值"<<"压力"<<"转速设值"<<"转速"<<"流量"<<"温度"<<"水温设值"<<"水温"<<"水位";

	unlColSizes[0] = 220;unlColSizes[1] = 80;unlColSizes[2] = 80;unlColSizes[3] = 80;
	unlColSizes[4] = 80;unlColSizes[5] = 80;unlColSizes[6] = 80;unlColSizes[7] = 80;
	unlColSizes[8] = 80;unlColSizes[9] = 80;unlColSizes[10] = 80;

	if(NULL == m_pTblViewTestDetail)
    {
        m_pTblViewTestDetail = new QTableView(this);
        m_pTblViewTestDetail->setEditTriggers(QAbstractItemView::NoEditTriggers);
		//m_pTblViewTestDetail->verticalScrollBar()->setStyleSheet("QScrollBar{width:40px;background:#FAFAFA;margin:0px 0px 40px 0px;padding-top:40px;padding-bottom:40px;}");
		
        QGridLayout* pGridLayout = new QGridLayout();
        pGridLayout->addWidget(m_pTblViewTestDetail,0,0);
        ui->tabMonData->setLayout(pGridLayout);
        pItemModel = new QStandardItemModel(this);
        m_pTblViewTestDetail->setModel(pItemModel);		

    }
    else
    {
        pItemModel = (QStandardItemModel*)m_pTblViewTestDetail->model();
    }
    pItemModel->clear();
    pItemModel->setHorizontalHeaderLabels(strColNames);
	
    for(lRowIndex = 0; lRowIndex < g_MonSaveInfo.unMonDataNum; lRowIndex++)
    {
        lColIndex = 0;
        pNewItem = new QStandardItem(DateTimeToString(&g_DataTests[lRowIndex].dtSample));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(DataTypeToString(g_DataTests[lRowIndex].unDataType));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unAPrssSet,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unAPrssVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
		
        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unASpeeSet,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unASpeeVal,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
		
        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unAFlowVal,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
		
        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unATmpVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unWatTmpSet,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unWatTmpVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

        pNewItem = new QStandardItem(ValueToString(g_DataTests[lRowIndex].unWatLine,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

    }
    //ulong lColSize;
    for(lColIndex = 0; lColIndex < (unsigned int)pItemModel->columnCount();lColIndex++)//long
    {
        //lColSize = ((QAbstractItemView*)m_pTblViewTestDetail)->sizeHintForColumn(lColIndex);
        m_pTblViewTestDetail->setColumnWidth(lColIndex,unlColSizes[lColIndex]);
    }

    ui->logTabWidget->setCursor(Qt::ArrowCursor);
}


void MonLogFrameDlg::sortByColumn(int column)
{
    QStandardItemModel* pItemModel = (QStandardItemModel*)m_pTblViewTestDetail->model();
    bool ascending = (m_pTblViewTestDetail->horizontalHeader()->sortIndicatorSection()==column&& m_pTblViewTestDetail->horizontalHeader()->sortIndicatorOrder()==Qt::DescendingOrder);
    Qt::SortOrder order = ascending ? Qt::AscendingOrder : Qt::DescendingOrder;
    m_pTblViewTestDetail->horizontalHeader()->setSortIndicator(column, order);
    pItemModel->sort(column, order);
}


