#include "cconfigpanel.h"
#include "ui_cconfigpanel.h"
#include "MyQProxyStyle.h"
//#include "basicconfigpanel.h"
#include "configbasicframe.h"
#include "configalmframe.h"
#include "configpourframe.h"
#include "configwatframe.h"
#include "configartframe.h"
#include "configveiframe.h"
#include "configbatframe.h"
#include "cshowinfopanel.h"
#include "passworddialog.h"


#define BSC_TAB_INDEX  0x00
#define ALM_TAB_INDEX  0x01
#define POUR_TAB_INDEX  0x02
#define WAT_DEV_TAB_INDEX   0x03
#define APUM_DEV_TAB_INDEX  0x04
#define VPUM_DEV_TAB_INDEX  0x05
#define BAT_PRM_TAB_INDEX   0x06

#define INFO_PANEL_INDEX    0x07

CConfigPanel::CConfigPanel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CConfigPanel)
{
    ui->setupUi(this);
	
    MyQProxyStyle *myQProxyStyle = new MyQProxyStyle();
    myQProxyStyle->SetTabWidth(125);
    myQProxyStyle->SetTabHeigth(65);
    myQProxyStyle->SetFontB(12);
    ui->cfgTabWidget->tabBar()->setStyle(myQProxyStyle);

	AddBasicCfgUI();
	AddAlmCfgUI();
	AddPourCfgUI();
	AddWatCfgUI();
	AddArtCfgUI();
	AddVeiCfgUI();
	AddBatCfgUI();
	AddShowInfo();

	QObject::connect(ui->cfgTabWidget, SIGNAL(currentChanged(int)),this,SLOT(OnItemChanged(int)));
}

CConfigPanel::~CConfigPanel()
{
	delete m_pBasicConfig;
	delete m_pAlmConfig;
	delete m_pPourConfig;
	delete m_pWatConfig;
	delete m_pArtConfig;
	delete m_pVeiConfig;
	delete m_pShowInfo;

    delete ui;
}

void CConfigPanel::AddBasicCfgUI(void)
{
    m_pBasicConfig = new ConfigBasicFrame(ui->basicCfgTab,this);
}

void CConfigPanel::AddAlmCfgUI(void)
{
    m_pAlmConfig = new configAlmFrame(ui->almCfgTab);
}

void CConfigPanel::AddPourCfgUI(void)
{
    m_pPourConfig = new configPourFrame(ui->PourCfgTab);
}

void CConfigPanel::AddWatCfgUI(void)
{
    m_pWatConfig = new configWatFrame(ui->watModTab);
}

void CConfigPanel::AddArtCfgUI(void)
{
	m_pArtConfig = new configArtFrame(ui->artModTab);
}

void CConfigPanel::AddVeiCfgUI(void)
{
	m_pVeiConfig = new configVeiFrame(ui->veiModTab);
}

void CConfigPanel::AddBatCfgUI(void)//电池配置
{
	m_pBatConfig = new configBatFrame(ui->batModTab);
}

void CConfigPanel::AddShowInfo(void)
{
	m_pShowInfo = new CShowInfoPanel(ui->testTab);
    ui->testTab->setLayout(m_pShowInfo->layout());
}
/**/
void CConfigPanel::OnItemChanged(int index )
{
	if(INFO_PANEL_INDEX != index)
	{
		if(true==g_pwdCfgInfo.bPwdEnFlg&&true==g_bLoginFlag)
		{
			g_bLoginFlag = false;
			PasswordDialog  pwdDlg(this,false);
			if(QDialog::Rejected==pwdDlg.exec())
			{
			    ui->cfgTabWidget->setCurrentIndex(INFO_PANEL_INDEX);
				g_bLoginFlag = true;
			}
		}
	}
}
void CConfigPanel::ExitLoginPwd(void)
{
    printf("entr CConfigPanel::ExitLogin \r\n");
	ui->cfgTabWidget->setCurrentIndex(INFO_PANEL_INDEX);
}


void CConfigPanel::OnUpdData(BqBatBascInfo *batDevData)
{

    m_pBasicConfig->OnUpdParams();
    m_pAlmConfig->OnUpdParams();
    m_pPourConfig->OnUpdParams();
    m_pWatConfig->OnUpdParams();
    m_pArtConfig->OnUpdParams();
	m_pVeiConfig->OnUpdParams();
    m_pBatConfig->OnUpdParams(batDevData);
}

void CConfigPanel::FlashSubDevPrm(BqBatBascInfo *batDevData)
{
    OnUpdData(batDevData);
}

