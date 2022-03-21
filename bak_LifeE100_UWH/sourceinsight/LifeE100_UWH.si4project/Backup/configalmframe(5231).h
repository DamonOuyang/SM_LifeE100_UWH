#ifndef CONFIGALMFRAME_H
#define CONFIGALMFRAME_H

#include <QFrame>

namespace Ui {
class configAlmFrame;
}

class configAlmFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configAlmFrame(QWidget *parent = 0);
    ~configAlmFrame();

private:
    Ui::configAlmFrame *ui;
};

#endif // CONFIGALMFRAME_H
