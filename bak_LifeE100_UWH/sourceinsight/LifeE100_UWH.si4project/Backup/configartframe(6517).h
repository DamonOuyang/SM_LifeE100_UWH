#ifndef CONFIGARTFRAME_H
#define CONFIGARTFRAME_H

#include <QFrame>

namespace Ui {
class configArtFrame;
}

class configArtFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configArtFrame(QWidget *parent = 0);
    ~configArtFrame();

private:
    Ui::configArtFrame *ui;
};

#endif // CONFIGARTFRAME_H
