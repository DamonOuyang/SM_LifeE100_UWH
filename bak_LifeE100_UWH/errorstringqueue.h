#ifndef ERRORSTRINGQUEUE_H
#define ERRORSTRINGQUEUE_H
#include "includes.h"

class CErrorStringQueue
{
public:
    CErrorStringQueue();

    bool  GetErrInfo(ErrInfo* pErrInfo);
    bool  AddErrInfo(const char* pErrInfo,unsigned unShowMode,unsigned char unErrIcon);
    long  GetErrInfoCount(void);
private:
    long m_lReadPos;
    long m_lWritePos;
    bool m_bEmptyFlag;
    ErrInfo m_errInfo[MAX_ERR_COUNT];
    QMutex m_mutexLock;
};

#endif // ERRORSTRINGQUEUE_H
