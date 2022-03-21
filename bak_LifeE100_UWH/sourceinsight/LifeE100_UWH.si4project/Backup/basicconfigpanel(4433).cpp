//#include "includes.h"
#include "basicconfigpanel.h"
#include "CMonShareData.h"
#include "SyszuxPinyin.h"
#include "cpassworddlg.h"
#include "QtGui"
#include <QFormLayout>
#include <QComboBox>
#include <QDialogButtonBox>

BasicConfigPanel::BasicConfigPanel(QWidget *parent) :
    QFrame(parent)
{
    m_pCurLineEdit = NULL;
    QHBoxLayout* pMainLayout = new QHBoxLayout();
    setLayout(pMainLayout);

    QGroupBox* pLeftGrpBox  = new QGroupBox();
    QGroupBox* pRightGrpBox = new QGroupBox();
    pRightGrpBox->setMinimumWidth(100);

    pMainLayout->addWidget(pLeftGrpBox);
    pMainLayout->addWidget(pRightGrpBox);

    long lEditWidth = 180;
    QFormLayout *formLayout = new QFormLayout;

    m_pDataPath  = new QLineEdit(this);

    QFrame* pFrame = new QFrame();
    pFrame->setFrameStyle(QFrame::NoFrame);
    pFrame->setMaximumWidth(lEditWidth+60);
    QHBoxLayout* pLine = new QHBoxLayout();
    pFrame->setLayout(pLine);
    QPushButton* pDatePathBut = new QPushButton(tr(">>"));
    pLine->addWidget(m_pDataPath);
    pLine->addWidget(pDatePathBut);
    pLine->setMargin(0);
    formLayout->addRow(tr("数据目录:"), pFrame);
    formLayout->setAlignment(Qt::AlignLeft);
    pDatePathBut->setMinimumWidth(50);
    pDatePathBut->setMinimumHeight(MINI_HEIGHT);

    m_pAlarmPath       = new QLineEdit(this);
    pFrame = new QFrame();
    pFrame->setFrameStyle(QFrame::NoFrame);
    pFrame->setMaximumWidth(lEditWidth+60);
    pLine = new QHBoxLayout();
    pFrame->setLayout(pLine);
    QPushButton* pAlarmBut = new QPushButton(tr(">>"));
    pLine->addWidget(m_pAlarmPath);
    pLine->addWidget(pAlarmBut);
    pLine->setMargin(0);
    formLayout->addRow(tr("日志目录:"), pFrame);
    formLayout->setAlignment(Qt::AlignLeft);
    pAlarmBut->setMinimumWidth(50);
    pAlarmBut->setMinimumHeight(MINI_HEIGHT);

    m_pAlmEnFlag    = CreateComboBox(this);
	m_pMonSavTmt    =  new QLineEdit(this);

    m_pDataTimeEdit = new QLineEdit(this);

    m_pDataPath->setReadOnly(true);
    m_pAlarmPath->setReadOnly(true);
    m_pAlmEnFlag->addItem("禁用");
    m_pAlmEnFlag->addItem("启用");
	
	m_pAPumCount = new QLineEdit(this);
	m_pVPumCount = new QLineEdit(this);
	m_pWatCount  = new QLineEdit(this);
    m_pAPumCount->setReadOnly(true);
    m_pVPumCount->setReadOnly(true);
	m_pWatCount->setReadOnly(true);

    m_pDataPath->setMaximumWidth(lEditWidth);
    m_pAlarmPath->setMaximumWidth(lEditWidth);

    m_pDataTimeEdit->setMaximumWidth(lEditWidth+60);
    lEditWidth = 100;
    m_pAlmEnFlag->setMaximumWidth(lEditWidth);
	m_pMonSavTmt->setMaximumWidth(lEditWidth);
    m_pAPumCount->setMaximumWidth(lEditWidth);
    m_pVPumCount->setMaximumWidth(lEditWidth);
    m_pWatCount->setMaximumWidth(lEditWidth);
	
    formLayout->addRow(tr("设备时间:"), m_pDataTimeEdit);
	formLayout->addRow(tr("告警状态:"), m_pAlmEnFlag);
	formLayout->addRow(tr("动泵数量:"), m_pAPumCount);
	formLayout->addRow(tr("静泵数量:"), m_pVPumCount);
	formLayout->addRow(tr("水浴数量:"), m_pWatCount);
    AddItem(formLayout,m_pMonSavTmt,tr("监控存储:"),tr("(秒)"),lEditWidth+60);

    pLeftGrpBox->setLayout(formLayout);

    QHBoxLayout* pButLayout = new QHBoxLayout();
    QDialogButtonBox* pButs = new QDialogButtonBox(Qt::Vertical);
    pButLayout->addWidget(pButs);
    QPushButton* pOkBut = new QPushButton(tr(SAVE_BUT_NAME));
    pOkBut->setMinimumSize(120,50);
    QPushButton* pCancelBut = new QPushButton(tr(CANCEL_BUT_NAME));
    pCancelBut->setMinimumSize(120,50);
    QPushButton* pEditBut = new QPushButton(tr(INPUT_BUT_NAME));
    pEditBut->setMinimumSize(120,50);

    pButs->addButton(pOkBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pCancelBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pEditBut,QDialogButtonBox::ActionRole);

    QPushButton* pModPwd = new QPushButton(tr("密码设置"));
    pModPwd->setMinimumSize(120,50);
    pButs->addButton(pModPwd,QDialogButtonBox::ActionRole);

    QPushButton* pExitPwd = new QPushButton(tr("退出登录"));
    pExitPwd->setMinimumSize(120,50);
    pButs->addButton(pExitPwd,QDialogButtonBox::ActionRole);

    pButs->setMinimumSize(140,200);
    pRightGrpBox->setLayout(pButLayout);

    setLayout(pMainLayout);

    connect(pAlarmBut,SIGNAL(clicked()),this,SLOT(OnClickAlarmPath()));
    connect(pDatePathBut,SIGNAL(clicked()),this,SLOT(OnClickDatePath()));
    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    connect(pModPwd,SIGNAL(clicked()),this,SLOT(OnPwdModEdit()));
    connect(pExitPwd,SIGNAL(clicked()),this,SLOT(OnExitLogin()));
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));

    connect(this,SIGNAL(exitLoginFlg(void)),parent,SLOT(ExitLoginFun(void)));
	
    OnUpdParams();

    m_pUpdTimer = new QTimer(this);
    connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnUpdDateTime(void)));
    m_pUpdTimer->start(1000);
	m_bChangeSysTmtFlag = false;

}

void BasicConfigPanel::OnClickOK(void)
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
void BasicConfigPanel::OnClickCancel(void)
{

}

void BasicConfigPanel::OnClickAlarmPath(void)
{

}
void BasicConfigPanel::OnClickDatePath(void)
{

}

void BasicConfigPanel::confirmString(QString strIn)
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
			SystemEx("hwclock -w");//新核心板，新系统使用

			GetDateTime(&ChgedSystem[1]);
			m_bChangeSysTmtFlag = true;
        }
    }
}
void BasicConfigPanel::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit && m_pCurLineEdit!=m_pAlmEnFlag)//&&m_pCurLineEdit==m_pDataTimeEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
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

void BasicConfigPanel::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pDataTimeEdit == old ||\
	   m_pMonSavTmt == old)
    {
        m_pCurLineEdit = old;
    }
}

void BasicConfigPanel::OnUpdParams(void)
{
    m_pDataPath->setText(g_devConfigInfo_Edt.basicCfgInfo.strDataPath);
    m_pAlarmPath->setText(g_devConfigInfo_Edt.basicCfgInfo.strLogPath);
    m_pAlmEnFlag->setCurrentIndex(g_devConfigInfo_Edt.basicCfgInfo.unAlmEnFlag);
	m_pMonSavTmt->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unMonSavTmt));

	m_pAPumCount->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unAPumCount));
	m_pVPumCount->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unVPumCount));
	m_pWatCount->setText(QString("%1").arg(g_devConfigInfo_Edt.basicCfgInfo.unWatCount));

}

void BasicConfigPanel::OnUpdDateTime(void)
{
    DateTime dtCurDateTime;
    GetDateTime(&dtCurDateTime);
    m_pDataTimeEdit->setText(DateTimeToString(&dtCurDateTime,true));
}

void BasicConfigPanel::OnPwdModEdit(void)
{
    m_pUpdTimer->stop();
    CPasswordDlg  pwdDlg(this,true);
    pwdDlg.exec();
}
void BasicConfigPanel::OnExitLogin(void)
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

