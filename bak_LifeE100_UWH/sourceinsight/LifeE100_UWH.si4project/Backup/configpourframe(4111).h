#ifndef CONFIGPOURFRAME_H
#define CONFIGPOURFRAME_H

#include <QFrame>

namespace Ui {
class configPourFrame;
}

class configPourFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configPourFrame(QWidget *parent = 0);
    ~configPourFrame();

private:
    Ui::configPourFrame *ui;
};

#endif // CONFIGPOURFRAME_H
