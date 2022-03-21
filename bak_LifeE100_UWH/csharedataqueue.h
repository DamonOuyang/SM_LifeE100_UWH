#ifndef CSHAREDATAQUEUE_H
#define CSHAREDATAQUEUE_H

class QMutext;
class CShareDataQueue
{
public:
    CShareDataQueue(UINT32 unMaxDataSize);
    ~CShareDataQueue();

    bool AddData(UINT32  unDataLen,BYTE* pDataBuf);
    bool GetData(UINT32  unDataLen,BYTE* pDataBuf);
    bool CopyData(UINT32 unDataLen,BYTE* pDataBuf);
    bool IsEmpty();
    UINT32 GetEmptySize(void);
    UINT32 GetDataSize(void);
protected:
    UINT32 m_unReadPos;
    UINT32 m_unWritePos;
    UINT32 m_unMaxBufSize;
    bool   m_bEmpty;
    BYTE*  m_pDataBuf;
    QMutex* m_pMutex;
    void Clear(void);
};

#endif // CSHAREDATAQUEUE_H
