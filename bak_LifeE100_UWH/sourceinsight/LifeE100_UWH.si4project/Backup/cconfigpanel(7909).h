#ifndef CCONFIGPANEL_H
#define CCONFIGPANEL_H

#include <QFrame>

namespace Ui {
class CConfigPanel;
}

class CConfigPanel : public QFrame
{
    Q_OBJECT

public:
    explicit CConfigPanel(QWidget *parent = 0);
    ~CConfigPanel();

private:
    Ui::CConfigPanel *ui;
};

#endif // CCONFIGPANEL_H
