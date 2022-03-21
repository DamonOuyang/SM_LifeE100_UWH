#ifndef CCONFIGPANEL_H
#define CCONFIGPANEL_H

#include <QFrame>

namespace Ui {
class CConfigPanel;
}
class ConfigBasicFrame;
class configAlmFrame;
class configPourFrame;
class configWatFrame;
class configArtFrame;
class configVeiFrame;
class CConfigPanel : public QFrame
{
    Q_OBJECT

public:
    explicit CConfigPanel(QWidget *parent = 0);
    ~CConfigPanel();
private:
	void AddBasicCfgUI(void);
	void AddAlmCfgUI(void);
	void AddPourCfgUI(void);
	void AddWatCfgUI(void);
	void AddArtCfgUI(void);
	void AddVeiCfgUI(void);

private:
    Ui::CConfigPanel *ui;
	ConfigBasicFrame * m_pBasicConfig;
	configAlmFrame   * m_pAlmConfig;
	configPourFrame  * m_pPourConfig;
	configWatFrame   * m_pWatConfig;
	configArtFrame   * m_pArtConfig;
	configVeiFrame   * m_pVeiConfig;
};

#endif // CCONFIGPANEL_H
