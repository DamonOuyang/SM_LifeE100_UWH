#ifndef CSHOWINFOPANEL_H
#define CSHOWINFOPANEL_H
#include <QFrame>
#include <QMessageBox>
#include "Includes.h"
class QTextEdit;
class CShowInfoPanel : public QFrame
{
    Q_OBJECT
public:
    explicit CShowInfoPanel(QWidget *parent = 0);
    
signals:
    
public slots:
    void ShowString(void);
    void OnClearInfo(void);
    void OnExit(void);
    void OnStopRecv(void);
private:
    QTextEdit* m_pShwInfo;
    ErrInfo  m_errInfo;
    bool m_bRcvFlag;
    QPushButton* m_pStopBut;
};

#endif // CSHOWINFOPANEL_H
