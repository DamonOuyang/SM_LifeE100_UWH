#ifndef MACHINESTATUSMGR_H
#define MACHINESTATUSMGR_H

#include <QObject>
#include "error_mgr_def.h"
#include <QTimer>
class MachineStatusMgr : public QObject
{
    Q_OBJECT
public:
    explicit MachineStatusMgr(QObject *parent = 0);
    ~MachineStatusMgr();

    void init();
    void sendMsgToClearError();
    void clearOlderrorMap();
private:
    QTimer* m_checkErrorTimer;
    QTimer* m_checkStatusTimer;
    bool    m_isNeedSendClearError;


    ErrorMgrMap  m_errorMap;

signals:

public slots:
    void slot_checkError();
    void sendErrorToServer();
    void checkMachinePauseServer();
};

#endif // MACHINESTATUSMGR_H
