﻿#include "cconfigpanel.h"
#include "ui_cconfigpanel.h"
#include "MyQProxyStyle.h"
//#include "basicconfigpanel.h"
#include "configbasicframe.h"
#include "configalmframe.h"
#include "configpourframe.h"
#include "configwatframe.h"
#include "configartframe.h"
#include "configveiframe.h"
#include "cshowinfopanel.h"


#define BSC_TAB_INDEX  0x00
#define ALM_TAB_INDEX  0x01
#define POUR_TAB_INDEX  0x02
#define WAT_DEV_TAB_INDEX   0x03
#define APUM_DEV_TAB_INDEX  0x04
#define VPUM_DEV_TAB_INDEX  0x05
//#define PUL_PRM_TAB_INDEX   0x06

#define INFO_PANEL_INDEX    0x06

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
	AddShowInfo();
}

CConfigPanel::~CConfigPanel()
{
    delete ui;
}

void CConfigPanel::AddBasicCfgUI(void)
{
    m_pBasicConfig = new ConfigBasicFrame(ui->cfgTabWidget->widget(BSC_TAB_INDEX));
    ui->cfgTabWidget->widget(BSC_TAB_INDEX)->setLayout(m_pBasicConfig->layout());
}

void CConfigPanel::AddAlmCfgUI(void)
{
    m_pAlmConfig = new configAlmFrame(ui->cfgTabWidget->widget(ALM_TAB_INDEX));
    ui->cfgTabWidget->widget(ALM_TAB_INDEX)->setLayout(m_pAlmConfig->layout());
}

void CConfigPanel::AddPourCfgUI(void)
{
    m_pPourConfig = new configPourFrame(ui->cfgTabWidget->widget(POUR_TAB_INDEX));
    ui->cfgTabWidget->widget(ALM_TAB_INDEX)->setLayout(m_pPourConfig->layout());
}

void CConfigPanel::AddWatCfgUI(void)
{
    m_pWatConfig = new configWatFrame(ui->cfgTabWidget->widget(WAT_DEV_TAB_INDEX));
    ui->cfgTabWidget->widget(WAT_DEV_TAB_INDEX)->setLayout(m_pWatConfig->layout());
}

void CConfigPanel::AddArtCfgUI(void)
{
    m_pArtConfig = new configArtFrame(ui->cfgTabWidget->widget(APUM_DEV_TAB_INDEX));
    ui->cfgTabWidget->widget(APUM_DEV_TAB_INDEX)->setLayout(m_pArtConfig->layout());
}

void CConfigPanel::AddVeiCfgUI(void)
{
    m_pVeiConfig = new configVeiFrame(ui->cfgTabWidget->widget(VPUM_DEV_TAB_INDEX));
    ui->cfgTabWidget->widget(VPUM_DEV_TAB_INDEX)->setLayout(m_pVeiConfig->layout());
}
void CConfigPanel::AddShowInfo(void)
{
    m_pShowInfo = new CShowInfoPanel(ui->cfgTabWidget->widget(INFO_PANEL_INDEX));
    ui->cfgTabWidget->widget(INFO_PANEL_INDEX)->setLayout(m_pShowInfo->layout());
}

