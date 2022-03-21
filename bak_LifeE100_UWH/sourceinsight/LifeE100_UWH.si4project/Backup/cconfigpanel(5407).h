#ifndef CCONFIGPANEL_H
#define CCONFIGPANEL_H

#include <QFrame>

namespace Ui {
class CConfigPanel;
}
class BasicConfigPanel;
class CConfigPanel : public QFrame
{
    Q_OBJECT

public:
    explicit CConfigPanel(QWidget *parent = 0);
    ~CConfigPanel();
private:
	void AddBasicCfgUI(void);

private:
    Ui::CConfigPanel *ui;
	BasicConfigPanel * m_pBasicConfig;
};

#endif // CCONFIGPANEL_H
