#include "includes.h"
#include <fcntl.h>
#include <unistd.h>
#include "ccircularfile.h"
#include <QtGui>
#include <sys/stat.h>

CCircularFile::CCircularFile(UINT32 unUnitLen,UINT32 unMaxRecCount)
{
    m_hFile = -1;
    m_unFileSeqID = 0; //写文件次数流水号,ID最大为最后一次数据更新
    m_unStartPos  = 0;  //文件数据开始位置
    m_unWritePos  = 0;  //文件数据结束位置
    m_unMaxRecCount = unMaxRecCount;
    m_unUnitLen = unUnitLen;
    m_unRecLen  = m_unUnitLen+sizeof(m_unFileSeqID);
    if(m_unMaxRecCount>MAX_FILE_REC_COUNT)
    {
        m_unMaxRecCount = MAX_FILE_REC_COUNT;
    }
    if(m_unUnitLen>MAX_UNIT_LEN)
    {
        m_unUnitLen = MAX_UNIT_LEN;
    }
    m_pUnitDataBuf = (UnitDataInfo*)malloc(m_unUnitLen+sizeof(m_unFileSeqID));
    m_bFullFlag = false;
}

CCircularFile::~CCircularFile()
{
    free(m_pUnitDataBuf);
    CloseFile();
}

void CCircularFile::IncreaseWritePos(bool bSetWritePos)
{
    //写文件位置更新
    m_unWritePos++;
    if(m_unWritePos>=m_unMaxRecCount)
    {
        m_unWritePos = 0;
        m_bFullFlag  = true;
        //重新定位写文件位置
        if(true==bSetWritePos)
        {
            printf("ResetWritePos !\r\n");
            SetWritePos();
        }
    }
    if(true==m_bFullFlag)
    {
        //数据已经写满,覆盖写，每写一条记录，就覆盖最前产生的一条记录
        m_unStartPos = m_unWritePos;
    }
}

bool CCircularFile::WriteData(BYTE* pDataBuf,UINT32 unDataLen)
{
    UINT32 unDataPos;
    if(-1==m_hFile)
    {
        return false;
    }
    if(0!=(unDataLen%m_unUnitLen))
    {
        //数据不等长记录
        return false;
    }
    unDataPos = 0;
    //写指针定位
    if(false==SetWritePos())
    {
        return false;
    }
    while(unDataPos<unDataLen)
    {
        //记录ID
        if(sizeof(m_unFileSeqID)!=write(m_hFile,(BYTE*)&m_unFileSeqID,sizeof(m_unFileSeqID)))
        {
            printf("Write CircularFile Error!\r\n");
            return false;
        }
        //记录数据
        if((long)m_unUnitLen!=write(m_hFile,(BYTE*)&pDataBuf[unDataPos],m_unUnitLen))
        {
            printf("Write CircularFile Error!\r\n");
            return false;
        }
        m_unFileSeqID++;
        unDataPos += m_unUnitLen;
        //写指针修改
        IncreaseWritePos(true);
    }
    fsync(m_hFile);
    //文件记录数递增
    /*
    printf("ReadPos:%lu WritrePos:%lu FullFlag:%u MaxRecCount:%lu SeqID:%lu\r\n",\
           m_unStartPos,m_unWritePos,m_bFullFlag,m_unMaxRecCount,\
           m_unFileSeqID);
           */
    return true;
}

bool CCircularFile::ReadData(UINT32 unFrmRecID,BYTE* pDataBuf,UINT32& unDataLen)
{
    UINT32 unRecSeqID;
    UINT32 unReadStartPos;
    UINT32 unRecIndex = 0;
    UINT32 unDataPos;
    //文件定位
    unReadStartPos = m_unStartPos;
    while(unRecIndex < unFrmRecID)
    {
        unRecIndex++;
        unReadStartPos++;
        if(unReadStartPos>=m_unMaxRecCount)
        {
            unReadStartPos = 0;
        }
        if(unReadStartPos==m_unWritePos)
        {
            //已经到文件末了
            unDataLen = 0;
            return false;
        }
    }
    //文件读取
    printf("ReadData FrmRecID:%lu RecPos:%lu StartPos:%lu\r\n",unFrmRecID,unReadStartPos,m_unStartPos);
    if(false==SetFilePos(unReadStartPos*m_unRecLen))
    {
        printf("SetFilePos Error IN:%lu\r\n",unReadStartPos*m_unRecLen);
        return false;
    }
    unDataPos = 0;
    while(unDataPos < unDataLen)
    {
        //记录ID
        if(sizeof(unRecSeqID)!=read(m_hFile,(BYTE*)&unRecSeqID,sizeof(unRecSeqID)))
        {
            printf("Read Circular File Error!in RecSeqID\r\n");
            unDataLen = unDataPos;
            return true;
        }
        //记录数据
        if((long)m_unUnitLen!=read(m_hFile,(BYTE*)&pDataBuf[unDataPos],m_unUnitLen))
        {
            printf("Read Circular File Error!in ReadData\r\n");
            unDataLen = unDataPos;
            return true;
        }
        //printf("SeqID:%lu ReadData:%lu\r\n",unRecSeqID,*((UINT32*)&pDataBuf[unDataPos]));
        unDataPos += m_unUnitLen;
        unReadStartPos++;
        if(unReadStartPos>=m_unMaxRecCount)
        {
            unReadStartPos = 0;
            SetFilePos(unReadStartPos*m_unRecLen);
        }
        if(unReadStartPos==m_unWritePos)
        {
            //已经到文件读完了
            unDataLen = unDataPos;
            return true;
        }
    }
    return true;
}

bool CCircularFile::CreateFile(QString strFilePath)
{
    if(-1!=m_hFile)
    {
        CloseFile();
    }
    m_hFile = open(strFilePath.toStdString().c_str() ,O_RDWR|O_CREAT,0666);
    if (-1==m_hFile)
    {
        printf("CreateAlmFileError!<%s>",strFilePath.toStdString().c_str());
        return false;
    }
    GetFileInfo();
    printf("WPos:%lu StPos:%lu SeqID:%lu \r\n",m_unWritePos,m_unStartPos,m_unFileSeqID);
    return true;
}

bool CCircularFile::CloseFile(void)
{
    if(-1!=m_hFile)
    {
        fsync(m_hFile);
        close(m_hFile);
    }
    return true;
}


bool CCircularFile::SetWritePos(void)
{
    UINT32 unWritePos = m_unWritePos;
    unWritePos *= (m_unUnitLen+sizeof(m_unFileSeqID));
    return SetFilePos(unWritePos);
}

bool CCircularFile::SetFilePos(UINT32 unFilePos)
{
    if(-1==m_hFile)
        return false;
    if(-1==lseek(m_hFile,unFilePos,SEEK_SET))
    {
        printf("lseek Func ERR! in SetFilePos\r\n");
        CloseFile();
        return false;
    }
    return true;
}

bool CCircularFile::GetFileInfo(void)
{
    struct stat  fStat;
    UINT32 unMinSeqIDPos = 0;
    UINT32 unMaxSeqIDPos = 0;
    UINT32 unMinSeqID = 0;
    UINT32 unMaxSeqID = 0;
    UINT32 unRecIndex = 0;
    if(-1==m_hFile)
    {
        return false;
    }
    if(-1==fstat(m_hFile,&fStat))
    {
        printf("fstat in Circular File Error!\r\n");
        return false;
    }
    if(fStat.st_size<(long)m_unRecLen)
    {
        //空文件或新创建文件
        return true;
    }
    if(false==SetFilePos(unRecIndex*m_unRecLen))
    {
        return false;
    }
    while(unRecIndex<m_unMaxRecCount)
    {
        if((long)m_unRecLen!=read(m_hFile,(BYTE*)m_pUnitDataBuf,m_unRecLen))
        {
            break;
        }
        if(0==unRecIndex)
        {
            unMinSeqID = m_pUnitDataBuf->unRecSeqID;
            unMaxSeqID = m_pUnitDataBuf->unRecSeqID;
        }
        else
        {
            if(unMinSeqID>m_pUnitDataBuf->unRecSeqID)
            {
                unMinSeqID = m_pUnitDataBuf->unRecSeqID;
                unMinSeqIDPos = unRecIndex;
            }
            if(unMaxSeqID<m_pUnitDataBuf->unRecSeqID)
            {
                unMaxSeqID = m_pUnitDataBuf->unRecSeqID;
                unMaxSeqIDPos = unRecIndex;
            }
        }
        unRecIndex++;
    }
    if(m_unMaxRecCount==unRecIndex)
    {
        if(unMaxSeqID-unMinSeqID<m_unMaxRecCount)
        {
            m_unWritePos  = unMaxSeqIDPos;
            m_unStartPos  = unMinSeqIDPos;
            m_unFileSeqID = unMaxSeqID;
        }
        else
        {
            m_unWritePos = unMinSeqIDPos;
            m_unStartPos = unMaxSeqIDPos;
            m_unFileSeqID= unMinSeqID;
        }
        m_unFileSeqID++;
        m_bFullFlag = true;
        IncreaseWritePos(false);
    }
    else
    {
        m_unStartPos  = 0;
        m_unWritePos  = unRecIndex;
        m_unFileSeqID = unMaxSeqIDPos;
        m_unFileSeqID++;
        m_bFullFlag = false;
    }
    return true;
}


UINT32 CCircularFile::GetRecCount(void)
{
    if(true==m_bFullFlag)
    {
        return m_unMaxRecCount;
    }
    else
    {
        return m_unWritePos;
    }
}

bool CCircularFile::Delete(void)
{
    QString strAlmFile;
    QString strAlmPosFile;
    QString strAlmFilePath;
    strAlmFilePath  = qApp->applicationDirPath()+"/"+g_devConfigInfo.basicCfgInfo.strLogPath;
    strAlmFile = strAlmFilePath+ALM_FILE_NAME;
    strAlmPosFile = strAlmFilePath+ALM_UPD_POS_NAME;
    if(-1!=m_hFile)
    {
        CloseFile();
        m_hFile = -1;
    }
    remove(strAlmFile.toStdString().c_str());
    remove(strAlmPosFile.toStdString().c_str());
    SystemEx("sync");
    m_unStartPos  = 0;   //文件数据开始位置
    m_unWritePos  = 0;   //文件数据结束位置
    m_unFileSeqID = 0;
    m_bFullFlag = false;
    return true;
}
