//#include "Includes.h"
#include "ErrorStringQueue.h"

CErrorStringQueue::CErrorStringQueue()
{
    m_lReadPos  = 0;
    m_lWritePos = 0;
    m_bEmptyFlag = true;
}


bool  CErrorStringQueue::GetErrInfo(ErrInfo* pErrInfo)
{
    m_mutexLock.lock();
    if(true==m_bEmptyFlag)
    {
        m_mutexLock.unlock();
        return false;
    }
    if(m_lReadPos>=MAX_ERR_COUNT)
    {
        m_lReadPos = 0;
    }
    pErrInfo->unShowMode = m_errInfo[m_lReadPos].unShowMode;
    strcpy(pErrInfo->pString,m_errInfo[m_lReadPos].pString);
    m_lReadPos++;
    if(m_lReadPos>=MAX_ERR_COUNT)
    {
        m_lReadPos = 0;
    }
    if(m_lReadPos==m_lWritePos)
    {
        m_bEmptyFlag = true;
    }
    m_mutexLock.unlock();
    return true;
}

bool  CErrorStringQueue::AddErrInfo(const char* pErrInfo, unsigned unShowMode, unsigned char unErrIcon)
{
    m_mutexLock.lock();
    if(false==m_bEmptyFlag&&m_lReadPos==m_lWritePos)
    {
        //队列已经满了
        m_mutexLock.unlock();
        return false;
    }
    if(strlen(pErrInfo)>=MAX_STR_LEN)
    {
        m_mutexLock.unlock();
        return false;
    }
    if(m_lWritePos>=MAX_ERR_COUNT)
    {
        m_lWritePos = 0;
    }
    m_errInfo[m_lWritePos].unShowMode = unShowMode;
    m_errInfo[m_lWritePos].unErrIcon  = unErrIcon;
    strcpy(m_errInfo[m_lWritePos].pString,pErrInfo);
    m_lWritePos++;
    if(m_lWritePos>=MAX_ERR_COUNT)
    {
        m_lWritePos = 0;
    }
    m_bEmptyFlag = false;
    m_mutexLock.unlock();
    return true;
}

long  CErrorStringQueue::GetErrInfoCount(void)
{
    long lCount = 0;
    m_mutexLock.lock();
    if(true==m_bEmptyFlag)
    {
        m_mutexLock.unlock();
        return lCount;
    }
    if(m_lWritePos>m_lReadPos)
    {
        lCount = m_lWritePos-m_lReadPos;
    }
    else
    {
        lCount = MAX_ERR_COUNT - abs(m_lWritePos-m_lReadPos);
    }
    m_mutexLock.unlock();
    return lCount;
}
