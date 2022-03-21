#ifndef CONFIGBATFRAME_H
#define CONFIGBATFRAME_H

#include <QFrame>

namespace Ui {
class configBatFrame;
}

class configBatFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configBatFrame(QWidget *parent = 0);
    ~configBatFrame();

private:
    Ui::configBatFrame *ui;
};

#endif // CONFIGBATFRAME_H
