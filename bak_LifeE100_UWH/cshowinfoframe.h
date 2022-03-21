#ifndef CSHOWINFOFRAME_H
#define CSHOWINFOFRAME_H

#include <QFrame>
#include "includes.h"

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
	void ShowString(void);

private:
    Ui::CShowInfoFrame *ui;
    ErrInfo  m_errInfo;
    bool m_bRcvFlag;

};

#endif // CSHOWINFOFRAME_H
