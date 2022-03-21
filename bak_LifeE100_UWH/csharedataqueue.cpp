#include "includes.h"
#include "csharedataqueue.h"
#include <QMutex>

CShareDataQueue::CShareDataQueue(UINT32 unMaxBufSize)
{
    m_unMaxBufSize = unMaxBufSize;
    m_pDataBuf = new BYTE[m_unMaxBufSize];
    m_unReadPos  = 0;
    m_unWritePos = 0;
    m_bEmpty = true;
    m_pMutex = new QMutex(QMutex::Recursive);
}

CShareDataQueue::~CShareDataQueue()
{
    delete []m_pDataBuf;
    delete m_pMutex;
}
bool CShareDataQueue::AddData(UINT32 unDataLen,BYTE* pDataBuf)
{
    UINT32 unDataPos;
    if(GetEmptySize()<unDataLen)
    {
        return false;
    }
    m_pMutex->lock();
    /*
    for(unDataPos = 0; unDataPos < 4; unDataPos++)
    {
        m_pDataBuf[m_unWritePos] = UINT8(unTmpDataLen&0xFF);
        m_unWritePos++;
        if(m_unWritePos>=m_unMaxBufSize)
        {
            m_unWritePos = 0;
        }
        unTmpDataLen = unTmpDataLen>>8;
    }
    */
    for(unDataPos = 0; unDataPos < unDataLen; unDataPos++)
    {
        m_pDataBuf[m_unWritePos] = pDataBuf[unDataPos];
        m_unWritePos++;
        if(m_unWritePos>=m_unMaxBufSize)
        {
            m_unWritePos = 0;
        }
    }
    m_bEmpty = false;
    m_pMutex->unlock();
    return true;
}
UINT32 CShareDataQueue::GetEmptySize()
{
    UINT32 unDataSize = m_unMaxBufSize;
    m_pMutex->lock();
    if(false==m_bEmpty)
    {
        if(m_unWritePos>m_unReadPos)
        {
            unDataSize  = m_unMaxBufSize;
            unDataSize -= m_unWritePos;
            unDataSize += m_unReadPos;
        }
        else
        {
            unDataSize = m_unReadPos-m_unWritePos;
        }
    }
    else
    {
        unDataSize = m_unMaxBufSize;
    }
    m_pMutex->unlock();
    return unDataSize;
}
UINT32 CShareDataQueue::GetDataSize(void)
{
    UINT32 unDataSize = GetEmptySize();
    unDataSize = m_unMaxBufSize-unDataSize;
    return unDataSize;
}

bool CShareDataQueue::GetData(UINT32 unDataLen,BYTE* pDataBuf)
{
    UINT32 unDataPos;
    if(true==IsEmpty())
    {
        return false;
    }
    if(unDataLen>GetDataSize())
    {
        return false;
    }
    m_pMutex->lock();
    /*
    unDataLen = 0;
    for(unDataPos = 0; unDataPos < 4; unDataPos++)
    {
        unDataLen  = unDataLen<<8;
        unDataLen += m_pDataBuf[m_unReadPos];
        m_unReadPos++;
        if(m_unReadPos>=m_unMaxBufSize)
        {
            m_unReadPos = 0;
        }
    }
    */
    for(unDataPos = 0; unDataPos < unDataLen; unDataPos++)
    {
        pDataBuf[unDataPos] = m_pDataBuf[m_unReadPos];
        m_unReadPos++;
        if(m_unReadPos>=m_unMaxBufSize)
        {
            m_unReadPos = 0;
        }
    }
    if(m_unReadPos==m_unWritePos)
    {
        m_bEmpty = true;
    }
    m_pMutex->unlock();
    return true;
}


bool CShareDataQueue::CopyData(UINT32 unDataLen,BYTE* pDataBuf)
{
    UINT32 unDataPos;
    UINT32 unReadPos = m_unReadPos;
    if(true==IsEmpty())
    {
        return false;
    }
    if(unDataLen>GetDataSize())
    {
        return false;
    }
    m_pMutex->lock();

    for(unDataPos = 0; unDataPos < unDataLen; unDataPos++)
    {
        pDataBuf[unDataPos] = m_pDataBuf[unReadPos];
        unReadPos++;
        if(unReadPos>=m_unMaxBufSize)
        {
            unReadPos = 0;
        }
    }
    m_pMutex->unlock();
    return true;
}

bool CShareDataQueue::IsEmpty()
{
    bool bEmpty;
    m_pMutex->lock();
    bEmpty = m_bEmpty;
    m_pMutex->unlock();
    return bEmpty;
}

void CShareDataQueue::Clear(void)
{
    m_pMutex->lock();
    m_unReadPos  = 0;
    m_unWritePos = 0;
    m_bEmpty = true;
    m_pMutex->unlock();
}

