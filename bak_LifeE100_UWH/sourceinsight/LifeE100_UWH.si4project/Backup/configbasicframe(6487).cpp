#pragma execution_character_set("utf-8")

#include "QtGui"
#include "configbasicframe.h"
#include "ui_configbasicframe.h"
#include "CMonShareData.h"
#include "cpassworddlg.h"
#include "numbkeyboarddialog.h"


ConfigBasicFrame::ConfigBasicFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConfigBasicFrame)
{
    ui->setupUi(this);

    m_pDataPath  = new QLineEdit(this);
	m_pDataPath->setReadOnly(true);
	m_pDataPath->setGeometry(QRect(155, 85, 100, 36));

    m_pAlarmPath = new QLineEdit(this);
	m_pAlarmPath->setReadOnly(true);
	m_pAlarmPath->setGeometry(QRect(155, 155, 100, 36));

	m_pDataTimeEdit = new QLineEdit(this);
	m_pDataTimeEdit->setGeometry(QRect(155, 225, 200, 36));

	m_pAPumCount = new QLineEdit(this);
	m_pAPumCount->setReadOnly(true);
	m_pAPumCount->setGeometry(QRect(496, 85, 100, 36));

	m_pVPumCount = new QLineEdit(this);
	m_pVPumCount->setReadOnly(true);
	m_pVPumCount->setGeometry(QRect(496, 155, 100, 36));
	
	m_pWatCount  = new QLineEdit(this);
	m_pWatCount->setReadOnly(true);
	m_pWatCount->setGeometry(QRect(496, 225, 100, 36));

	m_pMonSavTmt	=  new QLineEdit(this);
	m_pMonSavTmt->setGeometry(QRect(838, 85, 100, 36));

    m_pAlmEnFlag    = CreateComboBox(this);
	m_pAlmEnFlag->setGeometry(QRect(838, 155, 100, 36));
    m_pAlmEnFlag->addItem("禁用");
    m_pAlmEnFlag->addItem("启用");

    connect(ui->bOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(ui->bCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(ui->bEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(ui->bModPwd,SIGNAL(clicked()),this,SLOT(OnPwdModEdit()));
    connect(ui->bExitPwd,SIGNAL(clicked()),this,SLOT(OnExitLogin()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));

    QObject::connect(this,SIGNAL(exitLoginFlg(void)),parent,SLOT(ExitLoginFun(void)));
	
    OnUpdParams();

    m_pUpdTimer = new QTimer(this);
    connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnUpdDateTime(void)));
    m_pUpdTimer->start(1000);
	m_bChangeSysTmtFlag = false;
}

ConfigBasicFrame::~ConfigBasicFrame()
{
    delete ui;
}

void ConfigBasicFrame::OnClickOK(void)
{
	OperLogBasic operLogBasic;
	
	operLogBasic.unType = OPER_LOG_TYPE_BAS;
	operLogBasic.unSite = 0;
	GetDateTime(&operLogBasic.dtCreate);
	operLogBasic.unAlmEnFlag[0] = g_devConfigInfo_Edt.basicCfgInfo.unAlmEnFlag;
	operLogBasic.unAlmEnFlag[1] = m_pAlmEnFlag->currentIndex();
	
	operLogBasic.unMonSavTmt[0] = g_devConfigInfo_Edt.basicCfgInfo.unMonSavTmt;
	operLogBasic.unMonSavTmt[1] = m_pMonSavTmt->text().toInt();
	
	if(m_bChangeSysTmtFlag == true)
	{
		memcpy(&operLogBasic.dtSystem[0],&ChgedSystem[0],sizeof(DateTime));
		memcpy(&operLogBasic.dtSystem[1],&ChgedSystem[1],sizeof(DateTime));
		m_bChangeSysTmtFlag = false;
	}
	else
	{
		memcpy(&operLogBasic.dtSystem[0],&operLogBasic.dtCreate,sizeof(DateTime));
		memcpy(&operLogBasic.dtSystem[1],&operLogBasic.dtCreate,sizeof(DateTime));
	}
	SaveOperLogData((const char*)&operLogBasic, sizeof(OperLogBasic));
	SaveOperLogInfo();
	
	
	g_devConfigInfo_Edt.basicCfgInfo.unAlmEnFlag = m_pAlmEnFlag->currentIndex();
	g_devConfigInfo_Edt.basicCfgInfo.unMonSavTmt = m_pMonSavTmt->text().toInt();
	

    g_devConfigInfo_Edt.basicCfgInfo.unAlmEnFlag = m_pAlmEnFlag->currentIndex();
	g_devConfigInfo_Edt.basicCfgInfo.unMonSavTmt = m_pMonSavTmt->text().toInt();
    g_pCfgDataUI->AddGrpData(CFG_BASIC_ITEM,\
                                sizeof(g_devConfigInfo_Edt.basicCfgInfo),\
                                (BYTE*)&g_devConfigInfo_Edt.basicCfgInfo);
}
void ConfigBasicFrame::OnClickCancel(void)
{
	OnUpdParams();
}

void ConfigBasicFrame::OnClickAlarmPath(void)
{

}
void ConfigBasicFrame::OnClickDatePath(void)
{

}

void ConfigBasicFrame::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)//&&m_pCurLineEdit==m_pDataTimeEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
		
        if(m_pCurLineEdit==m_pDataTimeEdit)
        {
            GetDateTime(&ChgedSystem[0]);
            //DateTime dtCurDateTime;
            QString strDate = QString("date -s \"%1\"").arg(strIn);
            SystemEx(strDate.toStdString().c_str());
            SystemEx("hwclock -w");//
			GetDateTime(&ChgedSystem[1]);
			m_bChangeSysTmtFlag = true;
        }
    }
}
void ConfigBasicFrame::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit && m_pCurLineEdit!=m_pAlmEnFlag)//&&m_pCurLineEdit==m_pDataTimeEdit)
    {
        //SyszuxPinyin dlgInputPanel(this);
        NumbKeyboardDialog dlgInputPanel(this);
        if(m_pCurLineEdit==m_pDataTimeEdit)
        {
            dlgInputPanel.SetInputMask(QString("9999-99-99 99:99:99"));
        }
		/**/
		else if(m_pCurLineEdit==m_pMonSavTmt)
		{
		    dlgInputPanel.SetInputMask(QString("999"));
		}
        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void ConfigBasicFrame::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pDataTimeEdit == old ||\
	   m_pMonSavTmt == old)
    {
        m_pCurLineEdit = old;
    }
}

void ConfigBasicFrame::OnUpdParams(void)
{
    m_pDataPath->setText(g_devConfigInfo_Edt.basicCfgInfo.strDataPath);
    m_pAlarmPath->setText(g_devConfigInfo_Edt.basicCfgInfo.strLogPath);
    m_pAlmEnFlag->setCurrentIndex(g_devConfigInfo_Edt.basicCfgInfo.unAlmEnFlag);
	m_pMonSavTmt->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unMonSavTmt));

	m_pAPumCount->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unAPumCount));
	m_pVPumCount->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unVPumCount));
	m_pWatCount->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unWatCount));

}

void ConfigBasicFrame::OnUpdDateTime(void)
{
    DateTime dtCurDateTime;
    GetDateTime(&dtCurDateTime);
    m_pDataTimeEdit->setText(DateTimeToString(&dtCurDateTime,true));
}

void ConfigBasicFrame::OnPwdModEdit(void)
{
    m_pUpdTimer->stop();
    CPasswordDlg  pwdDlg(this,true);
    pwdDlg.exec();
}
void ConfigBasicFrame::OnExitLogin(void)
{
    if(true==g_pwdCfgInfo.bPwdEnFlg)
    {
		QPushButton* pNewBut;
		QMessageBox  msgBox(this);

		msgBox.setWindowTitle("提示");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText("是否要退出密码验证?退出后需要重新验证!");
		pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
		pNewBut->setMinimumSize(100,30);
		pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
		pNewBut->setMinimumSize(100,30);
		SetMessageBoxFont(&msgBox);
		if(QMessageBox::AcceptRole == msgBox.exec())
		{
		    //退出密码验证
		    g_bLoginFlag = true;
			emit exitLoginFlg();
		}	
    }
    else
    {
        QMessageBox msgBox;
        ShowInfo(&msgBox,"密码还没有启用，请进入密码设置界面设置后才能启用!","错误",QMessageBox::Critical);
    }
}

