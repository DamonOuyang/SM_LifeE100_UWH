#ifndef CMONSHAREDATA_H
#define CMONSHAREDATA_H
#include "csharedataqueue.h"

typedef struct SHARE_MON_DATA_HEAD
{
    UINT32 unDataLen;
    UINT32 unGrpID;
}ShareMonDataHead;

class CMonShareData : public CShareDataQueue
{
public:
    CMonShareData(UINT32 unDataSize);
    bool AddGrpData(UINT32 unGrpID,UINT32 unDataLen,BYTE* pDataBuf);
    bool GetGrpData(UINT32& unGrpID,UINT32& unDataLen,BYTE* pDataBuf);
    bool GetItemInfo(UINT32& unGrpID,UINT32& unDataLen);
};

#endif // CMONSHAREDATA_H
