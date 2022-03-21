#ifndef CCONFIGPANEL_H
#define CCONFIGPANEL_H

#include <QFrame>
#include "includes.h"


namespace Ui {
class CConfigPanel;
}
class ConfigBasicFrame;
class configAlmFrame;
class configPourFrame;
class configWatFrame;
class configArtFrame;
class configVeiFrame;
class configBatFrame;
class CShowInfoFrame;
class CConfigPanel : public QFrame
{
    Q_OBJECT

public:
    explicit CConfigPanel(QWidget *parent = 0);
    ~CConfigPanel();
	
	void FlashSubDevPrm(BqBatBascInfo *batDevData);
	
public slots:
	void ExitLoginPwd(void);
	void OnItemChanged(int index);
	
private:
	void AddBasicCfgUI(void);
	void AddAlmCfgUI(void);
	void AddPourCfgUI(void);
	void AddWatCfgUI(void);
	void AddArtCfgUI(void);
	void AddVeiCfgUI(void);
	void AddBatCfgUI(void);
	void AddShowInfo(void);
	void OnUpdData(BqBatBascInfo *batDevData);

private:
    Ui::CConfigPanel *ui;
	ConfigBasicFrame * m_pBasicConfig;
	configAlmFrame   * m_pAlmConfig;
	configPourFrame  * m_pPourConfig;
	configWatFrame   * m_pWatConfig;
	configArtFrame   * m_pArtConfig;
	configVeiFrame   * m_pVeiConfig;
	configBatFrame   * m_pBatConfig;
	//CShowInfoPanel   * m_pShowInfo;
	CShowInfoFrame   * m_pShowInfo;
};

#endif // CCONFIGPANEL_H
