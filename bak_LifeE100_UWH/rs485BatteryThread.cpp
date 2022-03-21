//#include "Includes.h"
#include "rs485BatteryThread.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <linux/fb.h>
#include <malloc.h>
#include <sys/mman.h>
#include <termio.h>
#include <pthread.h>
#define COM_DEV	"/dev/ttyAMA5"
#define COM_RATE	B9600
static int comfd = -1;
unsigned char sdata[]={0xDD,0xA5,0x03,0x00,0xFF,0xFD,0x77};


#define MON_HT_TMT   30 //s
#define  RCV_FLG     1
#define  SND_FLG     0

QTimer *m_pSecTmer;


Rs485BatteryThread::Rs485BatteryThread(QObject *parent) :
    QThread(parent)
{
	CtrlRs485RvcSnd(0);
	Rs485BatComInit();
	m_bSndOrRcvFlg = RCV_FLG;
	m_unSndDlySec = 0;
	m_unMsTimer = 0;
	
    m_pSecTmer = new QTimer();
    m_pSecTmer->start(3000);
    connect(m_pSecTmer, SIGNAL(timeout()), this, SLOT(SecTimer(void)));	
}

void Rs485BatteryThread::PrintfBufDebug(char* data,int len)
{
	for(UINT8 i = 0; i < len; i++)
	{
		printf("0x%x ",data[i]);
	}
	printf("\r\n");
}

void Rs485BatteryThread::Rs485BatComInit(void)
{
	struct termios cfg;
    comfd = open(COM_DEV, O_RDWR);
    if(comfd < 0)
	{
        printf("Cannot open %s\n",COM_DEV);
        return;
    }

    if(tcgetattr(comfd, &cfg))
	{
        printf("tcgetattr() failed\n");
        close(comfd);
        return;
    }

    cfmakeraw(&cfg);
    cfsetispeed(&cfg, COM_RATE);
    cfsetospeed(&cfg, COM_RATE);
    if(tcsetattr(comfd, TCSANOW, &cfg))
	{
        printf("tcsetattr() failed\n");
        close(comfd);
        return;
    }
}

void Rs485BatteryThread::ReadDataRcv(void)
{
	char rdata[256];
	int nread = 0;
	if((nread = read(comfd, rdata, 64)) > 0) 
	{
		printf("recv size:%d\n",nread);
		PrintfBufDebug(rdata,nread);
	}
}

void Rs485BatteryThread::WriteDataSnd(void)
{
	int cmd;

	printf("send size:%d\n",sizeof(sdata));
	CtrlRs485RvcSnd(1);
	write(comfd,sdata,sizeof(sdata));
	//CtrlRs485RvcSnd(0);
	system("echo 0 > /sys/class/gpio/gpio68/value");
}

void Rs485BatteryThread::SecTimer(void)
{
    WriteDataSnd();
    printf("---------------------------------------------------------------------12\r\n");
}


void Rs485BatteryThread::run()
{
    UINT32 unMsTimer;
    bool m_bQuitFlag = false;
	ftime(&m_timeb);
    while(false == m_bQuitFlag)
    {
        if(m_bSndOrRcvFlg == RCV_FLG)
        {
            ReadDataRcv();
        }
		/*
        unMsTimer = GetMsTimer(&m_timeb);		
		if(unMsTimer > 0)
		{
		    OnMsTimer(unMsTimer);
		}
		
		if(m_unSndDlySec == 0)
		{
		    m_bSndOrRcvFlg == SND_FLG;
		    WriteDataSnd();
			m_bSndOrRcvFlg == RCV_FLG;
			m_unSndDlySec = 3;
		}*/
		
		//printf("1---------------m_unSndDlySec:%u-----------------------------\r\n",m_unSndDlySec);
    }
}

void Rs485BatteryThread::OnMsTimer(UINT32 unMsCount)
{
    if(m_unMsTimer)
    {
        if(m_unMsTimer >= unMsCount)
        {
            m_unMsTimer -= unMsCount;
        }
        else
        {
            m_unMsTimer = 0;
        }
    }
    else
    {
        m_unMsTimer = 1000;
		printf("---------------m_unSndDlySec:%u-----------------------------\r\n",m_unSndDlySec);
        if(m_unSndDlySec)
        {
            m_unSndDlySec--;
        }
    }
}

