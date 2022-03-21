#include "cconfigpanel.h"
#include "ui_cconfigpanel.h"
#include "MyQProxyStyle.h"
#include "basicconfigpanel.h"



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
}

CConfigPanel::~CConfigPanel()
{
    delete ui;
}

void CConfigPanel::AddBasicCfgUI(void)
{
    m_pBasicConfig = new BasicConfigPanel(ui->cfgTabWidget->widget(BSC_TAB_INDEX),ui);
    ui->cfgTabWidget->widget(BSC_TAB_INDEX)->setLayout(m_pBasicConfig->layout());
}

