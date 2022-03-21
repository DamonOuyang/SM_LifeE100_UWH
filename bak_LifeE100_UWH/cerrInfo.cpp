#include "includes.h"
#include "CErrInfo.h"

CErrInfo::CErrInfo()
{
}

void CErrInfo::ShowInfo(const char* strUsrInfo,int nErrCode,const char* strSysErr)
{
    char dt[40];
    struct tm tp;
    time_t t = time(NULL);
    localtime_r(&t, &tp);
    sprintf(dt, "%d-%02d-%02d %02d:%02d:%02d",
        tp.tm_year + 1900,
        tp.tm_mon + 1,
        tp.tm_mday,
        tp.tm_hour,tp.tm_min,tp.tm_sec);
    if(NULL!=strUsrInfo)
    {
        printf("%s :: ErrCode:%d %s :: (%s)\n",
            dt,
            nErrCode,
            strUsrInfo,strSysErr);
    }
    else
    {
        printf("%s :: ErrCode:%d Unkown :: (%s)\n",
            dt,
            nErrCode,strSysErr);
    }
}
