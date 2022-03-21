#ifndef CCIRCULARFILE_H
#define CCIRCULARFILE_H

#define MAX_UNIT_LEN        1024
#define MAX_FILE_REC_COUNT  6000L

typedef struct UNIT_DATA_INFO
{
    UINT32 unRecSeqID;
    BYTE   pDataBuf[1];
}UnitDataInfo;

class QString;
class CCircularFile
{
public:
    CCircularFile(UINT32 unUnitLen,UINT32 unMaxRecCount);
    ~CCircularFile();
    bool CloseFile(void);
    UINT32 GetRecCount(void);
    virtual bool CreateFile(QString strFilePath);
    virtual bool Delete(void);
protected:
    bool WriteData(BYTE* pDataBuf,UINT32 unDataLen);
    bool ReadData(UINT32 unFrmRecID,BYTE* pDataBuf,UINT32& unDataLen);
    UnitDataInfo* m_pUnitDataBuf;
    int     m_hFile;        //文件句柄
    bool    m_bFullFlag;    //文件记录已经满
    UINT32  m_unFileSeqID;  //写文件次数流水号,ID最大为最后一次数据更新
    UINT32  m_unStartPos;   //文件数据开始位置
    UINT32  m_unWritePos;   //文件数据结束位置
    UINT32  m_unMaxRecCount;//文件最大记录数
    UINT32  m_unUnitLen;    //数据单长度
    UINT32  m_unRecLen;     //每条记录大小
    bool    GetFileInfo(void); //获取文件信息
    bool    SetWritePos(void);
    bool    SetFilePos(UINT32 unFilePos);
    void    IncreaseWritePos(bool bSetWritePos);
};

#endif // CCIRCULARFILE_H
