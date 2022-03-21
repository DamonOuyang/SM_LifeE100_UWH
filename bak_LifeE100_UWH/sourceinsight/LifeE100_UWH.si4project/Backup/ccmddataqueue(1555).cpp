#include "includes.h"
#include "ccmddataqueue.h"

CCmdDataQueue::CCmdDataQueue(UINT32 unMaxCmdCount)
{
    m_ulReadPos  = 0;
    m_ulWritePos = 0;
    m_bEmptyFlag = true;

    m_unMaxCmdCount = unMaxCmdCount;
    m_pCmdData = new CmdData[m_unMaxCmdCount];
}
CCmdDataQueue::~CCmdDataQueue()
{
    delete []m_pCmdData;
}

bool CCmdDataQueue::AddCmdData(CmdData* pCmdData)
{
    if(false==m_bEmptyFlag&&m_ulWritePos==m_ulReadPos)
    {
        return false;
    }
    if(pCmdData->unCmdDataLen>=MAX_CMD_DATA)
    {
        return false;
    }
    if(pCmdData->unCmdDataLen>0)
    {
        memcpy(m_pCmdData[m_ulWritePos].pCmdData,pCmdData->pCmdData,pCmdData->unCmdDataLen);
    }
    m_pCmdData[m_ulWritePos].unCmdDataLen = pCmdData->unCmdDataLen;
    m_pCmdData[m_ulWritePos].unCmdID = pCmdData->unCmdID;
    m_pCmdData[m_ulWritePos].unDevID = pCmdData->unDevID;
	m_pCmdData[m_ulWritePos].unSndID = pCmdData->unSndID;
    m_ulWritePos++;
    if(m_ulWritePos>=m_unMaxCmdCount)
    {
        m_ulWritePos = 0;
    }
    m_bEmptyFlag = false;
    //printf("Add_CmdID:%u DevID:%u Wr:%lu Rd:%lu\r\n",pCmdData->unCmdID,pCmdData->unDevID,m_ulWritePos,m_ulReadPos);
    return true;
}

bool CCmdDataQueue::GetCmdData(CmdData* pCmdData)
{
    if(true==m_bEmptyFlag)
    {
        return false;
    }
    if(m_pCmdData[m_ulReadPos].unCmdDataLen>0)
    {
        memcpy(pCmdData->pCmdData,m_pCmdData[m_ulReadPos].pCmdData,m_pCmdData[m_ulReadPos].unCmdDataLen);
    }
    pCmdData->unCmdDataLen = m_pCmdData[m_ulReadPos].unCmdDataLen;
    pCmdData->unCmdID = m_pCmdData[m_ulReadPos].unCmdID;
    pCmdData->unDevID = m_pCmdData[m_ulReadPos].unDevID;
	pCmdData->unSndID = m_pCmdData[m_ulReadPos].unSndID;
    m_ulReadPos++;
    if(m_ulReadPos>=m_unMaxCmdCount)
    {
        m_ulReadPos = 0;
    }
    if(m_ulReadPos==m_ulWritePos)
    {
        m_bEmptyFlag = true;
    }
    //printf("GetCmdID:%u DevID:%u\r\n",pCmdData->unCmdID,pCmdData->unDevID);
    return true;
}

bool CCmdDataQueue::IsEmpty(void)
{
    return m_bEmptyFlag;
}
void CCmdDataQueue::ClearQueue(void)
{
    m_ulReadPos  = 0;
    m_ulWritePos = 0;
    m_bEmptyFlag = true;
}

UINT8 CCmdDataQueue::GetCount(void)
{
    if(true==m_bEmptyFlag)
    {
        return 0;
    }
    if(m_ulWritePos>m_ulReadPos)
    {
        return m_ulWritePos - m_ulReadPos;
    }
    else
    {
        return m_unMaxCmdCount - (m_ulReadPos-m_ulWritePos);
    }
}
bool CCmdDataQueue::FindCmd(UINT8 unCmdID)
{
    if(true==m_bEmptyFlag)
    {
        return false;
    }
    UINT32 unDataPos = m_ulReadPos;
    while(unDataPos!=m_ulWritePos)
    {
        if(unCmdID==m_pCmdData[unDataPos].unCmdID)
        {
            return true;
        }
        unDataPos++;
        if(unDataPos>=m_unMaxCmdCount)
        {
            unDataPos = 0;
        }
    }
    return false;
}

bool CCmdDataQueue::FindDevCmd(UINT32 unDevID)
{
    if(true==m_bEmptyFlag)
    {
        return false;
    }
    UINT32 unDataPos = m_ulReadPos;
    while(unDataPos!=m_ulWritePos)
    {
        if(unDevID==(UINT32)m_pCmdData[unDataPos].unDevID)
        {
            return true;
        }
        unDataPos++;
        if(unDataPos>=m_unMaxCmdCount)
        {
            unDataPos = 0;
        }
    }
    return false;
}
