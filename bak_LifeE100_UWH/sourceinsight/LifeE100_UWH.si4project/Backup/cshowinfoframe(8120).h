#ifndef CSHOWINFOFRAME_H
#define CSHOWINFOFRAME_H

#include <QFrame>

namespace Ui {
class CShowInfoFrame;
}

class CShowInfoFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CShowInfoFrame(QWidget *parent = 0);
    ~CShowInfoFrame();

private slots:
    void on_pClearBut_clicked();

    void on_pStopBut_clicked(bool checked);

private:
    Ui::CShowInfoFrame *ui;
};

#endif // CSHOWINFOFRAME_H
