#include "includes.h"
#include "cmonsharedata.h"

CMonShareData::CMonShareData(UINT32 unDataSize):CShareDataQueue(unDataSize)
{

}

bool CMonShareData::AddGrpData(UINT32 unGrpID,UINT32 unDataLen,BYTE* pDataBuf)
{
    ShareMonDataHead  shrMonDataHead;
    if(GetEmptySize()<unDataLen+sizeof(shrMonDataHead))
    {
        return false;
    }
    shrMonDataHead.unDataLen = unDataLen;
    shrMonDataHead.unGrpID = unGrpID;
    m_pMutex->lock();
    AddData(sizeof(shrMonDataHead),(BYTE*)&shrMonDataHead);
    AddData(unDataLen,pDataBuf);
    m_pMutex->unlock();
    return true;
}

bool CMonShareData::GetGrpData(UINT32& unGrpID,UINT32& unDataLen,BYTE* pDataBuf)
{
    ShareMonDataHead  shrMonDataHead;
    if(true==IsEmpty())
    {
        return false;
    }
    if(GetDataSize()<sizeof(ShareMonDataHead))
    {
        Clear();
        return false;
    }
    m_pMutex->lock();
    GetData(sizeof(ShareMonDataHead),(BYTE*)&shrMonDataHead);
    unGrpID   = shrMonDataHead.unGrpID;
    unDataLen = shrMonDataHead.unDataLen;
    GetData(shrMonDataHead.unDataLen,pDataBuf);
    m_pMutex->unlock();
    return true;
}
bool CMonShareData::GetItemInfo(UINT32& unGrpID,UINT32& unDataLen)
{
    ShareMonDataHead  shrMonDataHead;
    if(true==IsEmpty())
    {
        return false;
    }
    if(GetDataSize()<sizeof(ShareMonDataHead))
    {
        Clear();
        return false;
    }
    CopyData(sizeof(ShareMonDataHead),(BYTE*)&shrMonDataHead);
    unGrpID = shrMonDataHead.unGrpID;
    unDataLen = shrMonDataHead.unDataLen;
    return true;
}
