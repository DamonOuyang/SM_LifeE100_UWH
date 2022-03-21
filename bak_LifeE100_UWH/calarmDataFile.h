#ifndef CALARMDATAFILE_H
#define CALARMDATAFILE_H
#include "ccircularfile.h"

class CAlarmDataFile : public CCircularFile
{
public:
    CAlarmDataFile(UINT32 unUnitLen,UINT32 unMaxRecCount);
    bool WriteAlmData(AlmItemEx* pAlmItemEx,UINT32 unAlmCount);
    bool ReadAlmData(UINT32 unFrmRecID,AlmItemEx* pAlmItemEx,UINT32& unAlmCount);
    void AlmUploadACK(void);
    bool ReadUpdAlmData(BYTE* pDataBuf,UINT32& unDataLen);
    bool CreateFile(QString strFilePath);
    bool Delete(void);
private:
    UINT32  m_unAlmCount;//告警上传个数，主要是考虑还要重复写一个位置，以免文件损坏
    UINT32  m_unUpdCount;//当前上传的记录数
    void WriteAlmUpdPos(void);
    void ReadAlmUpdPos(void);
};

#endif // CALARMDATAFILE_H
