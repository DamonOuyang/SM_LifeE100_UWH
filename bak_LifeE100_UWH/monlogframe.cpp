#include "monlogframe.h"
#include "ui_monlogframe.h"
#include "MyQProxyStyle.h"
#include <QFormLayout>

MonLogFrame::MonLogFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MonLogFrame)
{
    ui->setupUi(this);

    MyQProxyStyle *myQProxyStyle = new MyQProxyStyle();
    myQProxyStyle->SetTabWidth(125);
    myQProxyStyle->SetTabHeigth(65);
    myQProxyStyle->SetFontB(12);
    ui->logTabWidget->tabBar()->setStyle(myQProxyStyle);

	m_unOrderColIndex = 0;//记录时间排序
	m_OpenOperLogFlag = false;
	m_unWidgetFlag = 0;
	m_unCurPar = 0;

    //m_pTblViewTestDetail = NULL;
	
	//CreateBascLogWidget();
	//ShowBascLogWidget(false);
	/*
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

	//ShowTestDetail();
	ShowOperLog();

    QObject::connect(ui->goFirstButton,SIGNAL(clicked()),this,SLOT(OnOpenFirst()));
    QObject::connect(ui->goLastButton,SIGNAL(clicked()),this,SLOT(OnOpenLast()));
    QObject::connect(ui->goNextButton,SIGNAL(clicked()),this,SLOT(OnOpenNext()));
	QObject::connect(ui->goEndButton,SIGNAL(clicked()),this,SLOT(OnOpenEnd()));
	QObject::connect(ui->delAllButton,SIGNAL(clicked()),this,SLOT(OnDelAllFile()));
	//QObject::connect(ui->delCurrButton,SIGNAL(clicked()),this,SLOT(OnDelCurrFile()));
	ui->delCurrButton->hide();

    m_pUpdTimer = new QTimer(this);
    connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(FlashMonLogData(void)));
    m_pUpdTimer->start(1000);*/	
}
/*
void MonLogFrame::CreateBascLogWidget(void)
{
	int lEditWidth = 220;

	QFormLayout *formLayout[2];
	formLayout[0] = new QFormLayout;
	formLayout[1] = new QFormLayout;	
	
	m_wBascWidget[0] = new QWidget(ui->beforeGroupBox);
	m_wBascWidget[0]->setGeometry(QRect(0, 0, 537, 460));
	m_wBascWidget[0]->setStyleSheet("background: transparent;");

	QHBoxLayout* pFirstRow	= new QHBoxLayout();

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

	lEditWidth = 100;
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
	m_wBascWidget[1]->setGeometry(QRect(0, 0, 537, 460));
	m_wBascWidget[1]->setStyleSheet("background: transparent;");

	pLabel = new QLabel(m_wBascWidget[1]);
	pLabel->setMinimumSize(10,10);
	formLayout[1]->addRow(tr(" "),pLabel);

	lEditWidth = 220;
	m_pSysTime[1] = new QLineEdit(m_wBascWidget[1]);
	m_pSysTime[1]->setReadOnly(true);
	m_pSysTime[1]->setMaximumWidth(lEditWidth);
	
	lEditWidth = 100;
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
void MonLogFrame::ShowBascLogWidget(bool tFlag)
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
*/

MonLogFrame::~MonLogFrame()
{
    //m_pTblViewTestDetail = NULL;
	//delete m_pTblViewTestDetail;

    delete ui;
}
