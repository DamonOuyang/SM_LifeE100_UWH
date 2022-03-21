#ifndef RS485BATTERYTHREAD_H
#define RS485BATTERYTHREAD_H
//#include <sys/timeb.h>
#include <QThread>
//#include <QMutex>
#include <QTimer>
#include "Includes.h"



class Rs485BatteryThread : public QThread
{
    Q_OBJECT
public:
    explicit Rs485BatteryThread(QObject *parent = 0);
	void PrintfBufDebug(char* data,int len);
	void Rs485BatComInit(void);
	void ReadDataRcv(void);
	void WriteDataSnd(void);
	void OnMsTimer(UINT32 unMsCount);
signals:
	void ShowInfo(void);//通知界面线程,刷新错误信息
protected:
    void run();
private slots:
	void SecTimer(void);

private:
	bool   m_bSndOrRcvFlg;
	UINT8  m_unSndDlySec;
	UINT32  m_unMsTimer;
	timeb   m_timeb;
	QTimer *m_pSecTmer;
};

#endif // CWORKTHREAD_H
