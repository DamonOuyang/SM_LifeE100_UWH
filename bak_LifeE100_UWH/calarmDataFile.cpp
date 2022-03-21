#include "includes.h"
#include "CAlarmDataFile.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <QtGui>
#define MAX_ALM_UPD_REC_COUNT 1000L
CAlarmDataFile::CAlarmDataFile(UINT32 unUnitLen,UINT32 unMaxRecCount):CCircularFile(unUnitLen,unMaxRecCount)
{
    m_unAlmCount = 0;
    m_unUpdCount = 0;
}
bool CAlarmDataFile::WriteAlmData(AlmItemEx* pAlmItemEx,UINT32 unAlmCount)
{
    bool bReturn  = WriteData((BYTE*)pAlmItemEx,unAlmCount*sizeof(AlmItemEx));
	/*
    if(true==bReturn)
    {
        if(m_unAlmCount<m_unMaxRecCount)
        {
            //上传告警记录数，递增，需要保存
            m_unAlmCount++;
            WriteAlmUpdPos();
        }
    }
    */
    return bReturn;
}
bool CAlarmDataFile::ReadAlmData(UINT32 unFrmRecID,AlmItemEx* pAlmItemEx,UINT32& unAlmCount)
{
    UINT32 unDataLen = unAlmCount*sizeof(AlmItemEx);
    bool bReturn = ReadData(unFrmRecID,(BYTE*)pAlmItemEx,unDataLen);
    if(true==bReturn)
    {
        unAlmCount = unDataLen/sizeof(AlmItemEx);
    }
    else
    {
        unAlmCount = 0;
    }
    return bReturn;
}

bool CAlarmDataFile::ReadUpdAlmData(BYTE* pDataBuf,UINT32& unDataLen)
{
    UINT32 unRecSeqID;
    AlmItemEx  almItemEx;
    UINT32 unReadPos  = 0;
    UINT32 unDataPos  = 0;
    if(0==m_unAlmCount)
    {
        unDataLen = 0;
        return false;
    }
    if(m_unWritePos>=m_unAlmCount)
    {
        unReadPos = m_unWritePos-m_unAlmCount;
    }
    else
    {
        unReadPos = (m_unMaxRecCount - m_unAlmCount)+m_unWritePos;
    }
    if(false==SetFilePos(unReadPos*m_unRecLen))
    {
        printf("SetFilePos ERROR In AlarmLog!\r\n");
        return false;
    }
    /*
    printf("UploadAlmCount:%lu AlmFrmPos:%lu StartPos:%lu WritePos:%lu\r\n",\
           m_unAlmCount,unReadPos,m_unStartPos,m_unWritePos);*/
    m_unUpdCount = 0;
    unRecSeqID   = 0;
    do
    {
        //记录ID
        if(sizeof(unRecSeqID)!=read(m_hFile,(BYTE*)&unRecSeqID,sizeof(unRecSeqID)))
        {
            printf("Read Circular File Error!in RecSeqID\r\n");
            unDataLen = unDataPos;
            return true;
        }
        //记录数据
        if(sizeof(almItemEx)!=read(m_hFile,(BYTE*)&almItemEx,sizeof(almItemEx)))
        {
            printf("Read Circular File Error!in ReadData\r\n");
            unDataLen = unDataPos;
            return true;
        }
        memcpy(&pDataBuf[unDataPos],&almItemEx.almItem,sizeof(AlmItem));
        unDataPos += sizeof(AlmItem);
        unReadPos++;
        m_unUpdCount++;
        if(unReadPos>=m_unMaxRecCount)
        {
            //循环文件回头
            unReadPos = 0;
            if(false==SetFilePos(unReadPos*m_unRecLen))
            {
                printf("SetFilePos ERROR In AlarmLog!\r\n");
                return false;
            }
        }

    }while(unDataPos<unDataLen&&unReadPos!=m_unWritePos);
    unDataLen = unDataPos;
    /*
    printf("Upload AlmItem----:%lu  ReadPos:%lu WritePos:%lu\r\n",\
           m_unUpdCount,unReadPos,m_unWritePos);
           */
    return true;
}

void CAlarmDataFile::WriteAlmUpdPos(void)
{
    struct stat  fdStat;
    QString strFilePath;
    strFilePath  = qApp->applicationDirPath()+"/";
    strFilePath += g_devConfigInfo.basicCfgInfo.strLogPath;
    strFilePath += ALM_UPD_POS_NAME;
    //printf("SaveUpdPos:%lu\r\n",m_unAlmUpdPos);
    int fd = open(strFilePath.toStdString().c_str() ,O_WRONLY|O_CREAT,0666);
    if (-1==fd)
    {
        printf("open func ERR!:%s\r\n",strFilePath.toStdString().c_str());
        return ;
    }

    if(-1==fstat(fd,&fdStat))
    {
        //printf("fstat Func ERR!:%s\r\n",strFilePath.toStdString().c_str());
        close(fd);
        return ;
    }
    if(fdStat.st_size/sizeof(m_unAlmCount)>=MAX_ALM_UPD_REC_COUNT)
    {
        //文件太长了，重新写
        close(fd);
        int fd = open(strFilePath.toStdString().c_str() ,O_WRONLY|O_TRUNC,0666);
        if (-1==fd)
        {
            printf("open func ERR!:%s\r\n",strFilePath.toStdString().c_str());
            return ;
        }
    }
    else
    {
        if(-1==lseek(fd,0L,SEEK_END))
        {
            printf("lseek Func ERR!:%s\r\n",strFilePath.toStdString().c_str());
            close(fd);
            return ;
        }
    }
    if(sizeof(m_unAlmCount)!=write(fd,(char*)&m_unAlmCount,sizeof(m_unAlmCount)))
    {
        printf("write func ERR!:%s\r\n",strFilePath.toStdString().c_str());
    }
    else
    {
        fsync(fd);
    }
    close(fd);
    return ;
}

void CAlarmDataFile::ReadAlmUpdPos(void)
{
    bool   bReadFlag   = false;
    UINT32 unDataPos   = 0;
    UINT32 unAlmCount = 0;
    QString strFilePath;
    strFilePath  = qApp->applicationDirPath()+"/";
    strFilePath += g_devConfigInfo.basicCfgInfo.strLogPath;
    strFilePath += ALM_UPD_POS_NAME;
    struct stat  fdStat;
    int fd = open(strFilePath.toStdString().c_str() ,O_RDONLY);
    if (-1==fd)
    {
        //printf("Open Func ERR!:%s\r\n",strFilePath.toStdString().c_str());
        return ;
    }
    if(-1==fstat(fd,&fdStat))
    {
        //printf("fstat Func ERR!:%s\r\n",strFilePath.toStdString().c_str());
        close(fd);
        return ;
    }
    if(-1==lseek(fd,0L,SEEK_SET))
    {
        //printf("lseek Func ERR!:%s\r\n",strFilePath.toStdString().c_str());
        close(fd);
        return ;
    }
    while((off_t)unDataPos < fdStat.st_size)
    {
        if(sizeof(unAlmCount) != (UINT32)read(fd,(char*)&unAlmCount,sizeof(unAlmCount)))
        {
            break;
        }
        else
        {
            bReadFlag = true;
        }
    }
    close(fd);
    if(true==bReadFlag)
    {
        m_unAlmCount = unAlmCount;
    }
    else
    {
        m_unAlmCount = 0;
    }
    //printf("AlmUpdPos:--------------%lu\r\n",m_unAlmUpdPos);
}

void CAlarmDataFile::AlmUploadACK(void)
{
    //printf("Upload Alarm Data ACK!UpdPos:%lu Count:%lu\r\n",m_unAlmUpdPos,m_unAlmUpdCount);
    if(m_unAlmCount>m_unUpdCount)
    {
        m_unAlmCount -= m_unUpdCount;
    }
    else
    {
        m_unAlmCount = 0;
    }
    m_unUpdCount  = 0;
    WriteAlmUpdPos();
}

bool CAlarmDataFile::CreateFile(QString strFilePath)
{
    bool bReturn = CCircularFile::CreateFile(strFilePath);
    if(true==bReturn)
    {
        ReadAlmUpdPos();
    }
    return bReturn;
}
bool CAlarmDataFile::Delete(void)
{
    bool bReturn = CCircularFile::Delete();
    m_unAlmCount = 0;
    WriteAlmUpdPos();
    return bReturn;
}
