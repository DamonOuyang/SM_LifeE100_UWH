#ifndef CONFIGVEIFRAME_H
#define CONFIGVEIFRAME_H

#include <QFrame>

namespace Ui {
class configVeiFrame;
}

class configVeiFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configVeiFrame(QWidget *parent = 0);
    ~configVeiFrame();

private:
    Ui::configVeiFrame *ui;
};

#endif // CONFIGVEIFRAME_H
