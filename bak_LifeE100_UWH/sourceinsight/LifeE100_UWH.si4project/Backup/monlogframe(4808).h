#ifndef MONLOGFRAME_H
#define MONLOGFRAME_H

#include <QFrame>

namespace Ui {
class MonLogFrame;
}

class MonLogFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MonLogFrame(QWidget *parent = 0);
    ~MonLogFrame();

private:
    Ui::MonLogFrame *ui;
};

#endif // MONLOGFRAME_H
