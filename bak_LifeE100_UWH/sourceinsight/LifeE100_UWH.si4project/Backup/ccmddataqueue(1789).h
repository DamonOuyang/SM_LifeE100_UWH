#ifndef CCMDDATAQUEUE_H
#define CCMDDATAQUEUE_H
#include "includes.h"
#include "cbasicdevice.h"

class CCmdDataQueue
{
public:
    CCmdDataQueue(UINT32 unMaxCmdCount=MAX_CMD_COUNT);
    virtual ~CCmdDataQueue();
    CmdData* m_pCmdData;
    ulong m_ulReadPos;
    ulong m_ulWritePos;
    //bool m_bEmptyFlag;
    UINT32 m_unMaxCmdCount;
    bool AddCmdData(CmdData* pCmdData);
    bool GetCmdData(CmdData* pCmdData);
    void ClearQueue(void);
    bool IsEmpty(void);
    UINT8 GetCount(void);
    bool FindCmd(UINT8 unCmdID);
    bool FindDevCmd(UINT32 unDevID);
private:
	bool m_bEmptyFlag;

};

#endif // CCMDDATAQUEUE_H
