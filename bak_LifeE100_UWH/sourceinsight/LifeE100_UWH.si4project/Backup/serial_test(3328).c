/*************************************

NAME:serial_test.c

*************************************/

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
#include <signal.h>
#include <sys/time.h>


#define COM_DEV	"/dev/ttyAMA5"
#define COM_RATE	B9600
static int comfd = -1;
unsigned char sdata[]={0xDD,0xA5,0x03,0x00,0xFF,0xFD,0x77};
//unsigned char sdata[]="12";

void debug(char* data,int len)
{
	int i = 0;
	for(i = 0;i<len;i++) {
		printf("0x%x ",data[i]);
		if(i != 0)
			if((i%16)==0)
				printf("\n");
	}
	printf("\n");
}

void DeCtrl(int val)
{
	if(val)
		system("echo 1 > /sys/class/gpio/gpio68/value");
	else
		system("echo 0 > /sys/class/gpio/gpio68/value");
}

void *readthread(void)
{
	char rdata[4096];
	int nread = 0;
	while(1) 
	{
		if((nread = read(comfd,rdata,64))>0) 
		{
			printf("recv size:%d\n",nread);
			debug(rdata,nread);
			rdata[nread] = '\0';
			printf("recv data:%s\n",rdata);
		}
	}
}

void *writethread(void)
{
	char readline[4096];
	int cmd;
	while(1) 
	{
		fgets(readline, sizeof(readline), stdin);
		cmd = strtol(readline,NULL,16);
		printf("read cmd:0x%x\n",cmd);
		if(cmd == 0)
			continue;
		printf("send size:%d\n",sizeof(sdata));
		DeCtrl(1);
		write(comfd,sdata,sizeof(sdata));
		DeCtrl(0);
	}
}

void cominit()
{
	struct termios cfg;
    comfd = open(COM_DEV, O_RDWR);
    if (comfd < 0) {
        printf("Cannot open %s\n",COM_DEV);
        return;
    }

    if (tcgetattr(comfd, &cfg)) {
        printf("tcgetattr() failed\n");
        close(comfd);
        return;
    }

    cfmakeraw(&cfg);
    cfsetispeed(&cfg, COM_RATE);
    cfsetospeed(&cfg, COM_RATE);
    if (tcsetattr(comfd, TCSANOW, &cfg)) {
        printf("tcsetattr() failed\n");
        close(comfd);
        return;
    }
}

void signal_timer_handler(int signo)
{
    switch (signo)
	{
        case SIGALRM:
			
            printf("timer count! \n");
            break;
   }
}
int initTimer(void)
{
    timeval   new_value;
	timeval  old_value;
    signal(SIGALRM, signal_timer_handler);
    new_value.it_value.tv_sec = 0;
    new_value.it_value.tv_usec = 1;//²»ÄÜÎª0 
    new_value.it_interval.tv_sec = 3;
    new_value.it_interval.tv_usec = 0;//10ms
    setitimer(ITIMER_REAL, &new_value, &old_value);
}


int main(int argc, char* argv[])
{
    pthread_t readid,writeid;
	int ret;
	DeCtrl(0);
	cominit();
    initTimer();
	

	if(comfd < 0)
		return -1;
    ret = pthread_create(&readid, NULL, (void*)readthread, NULL);
    if(ret) 
	{
        printf("Create readid pthread error!\n");
        return ret;
    }
   
    ret = pthread_create(&writeid, NULL, (void*)writethread, NULL);
    if(ret) 
	{
        printf("Create writeid pthread error!\n");
        return ret;
    }
    
	pthread_join(readid, NULL);
    pthread_join(writeid, NULL);
    
    return 0;
}
