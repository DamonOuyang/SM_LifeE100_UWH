#ifndef MONTHREAD_H
#define MONTHREAD_H
//#include <sys/timeb.h>
#include <QThread>
//#include <QMutex>
//#include <QString>
//#include "Includes.h"
#include "includes.h"



class MonThread : public QThread
{
    Q_OBJECT
public:
    explicit MonThread(QObject *parent = 0);
	void CloseWatchdog(void);
signals:
	void ShowInfo(void);//通知界面线程,刷新错误信息
protected:
    void run();

private:
	UINT8  m_unMainWindRunT;
	UINT8  m_unWorkThRunT;
	UINT8  m_unNetIpThRunT;
	UINT8  m_unPrintThRunT;
	UINT8  m_unSetWatchdogSec;
	
    void OnSecTimer(void);
};

#endif // CWORKTHREAD_H
