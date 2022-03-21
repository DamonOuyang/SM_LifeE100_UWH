//#include "Includes.h"
#include "monThread.h"

#include "unistd.h"
#include <stdio.h>

#define MON_HT_TMT   30 //s

MonThread::MonThread(QObject *parent) :
    QThread(parent)
{
	m_unMainWindRunT = 0;
	m_unWorkThRunT = 0;
	m_unNetIpThRunT = 0;
    //InitWatchdog();
    m_unSetWatchdogSec = 0;
}

void MonThread::CloseWatchdog(void)
{
	close(g_fWtchDog);
	SystemEx("sync");
}

void MonThread::run()
{
    UINT32 unMsTimer;
    bool m_bQuitFlag = false;
    InitWatchdog();
    while(false == m_bQuitFlag)
    {
        sleep(1);
        OnSecTimer();
    }
    SystemEx("reboot -f");
}

void MonThread::OnSecTimer(void)
{
    bool unRebootSys = false;

    if(g_bMainWindRunFlg == false)
    {
        if(m_unMainWindRunT < MON_HT_TMT)
        {
            m_unMainWindRunT++;
        }
		else
		{
		    unRebootSys = true;
			printf("MainWindThread Defunct System Restart Flag True \r\n");
		}
    }
    else
    {
        g_bMainWindRunFlg = false;
		m_unMainWindRunT = 0;
    }

    if(g_bWorkThRunRunFlg == false)
    {
        if(m_unWorkThRunT < MON_HT_TMT)
        {
            m_unWorkThRunT++;
        }
		else
		{
		    unRebootSys = true;
			printf("MainWindThread Defunct System Restart Flag True \r\n");
		}
    }
    else
    {
        g_bWorkThRunRunFlg = false;
		m_unWorkThRunT = 0;
    }
	
    if(unRebootSys)
    {
        SystemEx("reboot -f");
    }
	else
	{
	    //喂狗
	    if(m_unSetWatchdogSec >= 5)
	    {
			SetWatchdog();
			m_unSetWatchdogSec = 0;
	    }
		else
		{
		    m_unSetWatchdogSec++;
		}
	}

	if(m_unPrintThRunT)
	{
	    m_unPrintThRunT--;
	}
	else
	{
		//printf("MonThread Running\r\n");
		m_unPrintThRunT = MON_HT_TMT;
	}

}

