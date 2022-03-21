#ifndef CONFIGWATFRAME_H
#define CONFIGWATFRAME_H

#include <QFrame>

namespace Ui {
class configWatFrame;
}

class configWatFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configWatFrame(QWidget *parent = 0);
    ~configWatFrame();

private:
    Ui::configWatFrame *ui;
};

#endif // CONFIGWATFRAME_H
