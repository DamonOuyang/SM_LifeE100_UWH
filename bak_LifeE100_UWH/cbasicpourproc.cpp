#include "includes.h"
#include "cbasicpourproc.h"
#include "cworkthread.h"
#include <QApplication>
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"

CBasicPourProc::CBasicPourProc()
{
    m_unSaveSecs = 0;       //保存数据时间周期(秒)
    m_unGetSaveSec = 60;
    m_bSaveFlag = false;    //数据保存标志位
    m_unMsTimer = 0;        //毫秒计数计
    m_bRunFlag[0]  = false;    //运行标志位
    m_bRunFlag[1]  = false;
    m_unStopCode  = 0xFF;
    m_fHandle = -1;
    m_bSecFlag    = false;
}
CBasicPourProc::~CBasicPourProc()
{

}

void CBasicPourProc::OnMsTimer(UINT32 unMsCount)
{
    if(m_unMsTimer)
    {
        if(m_unMsTimer>=unMsCount)
        {
            m_unMsTimer -= unMsCount;
        }
        else
        {
            m_unMsTimer = 0;
        }
    }
    else
    {
        m_bSecFlag  = true;
        m_unMsTimer = 1000;
        if(true==m_bRunFlag[0] || true == m_bRunFlag[1])
        {
            //处理存盘时间
            if(m_unSaveSecs)
            {
                m_unSaveSecs--;
            }
            else
            {
                m_bSaveFlag  = true;//保存采样数据
                m_unSaveSecs = m_unGetSaveSec;
            }
        }
    }
}

void CBasicPourProc::ProcTask(void)
{
    if(false == m_bSecFlag)
    {
        return ;
    }
    m_bSecFlag = false; //秒钟标志清零

    if(false == m_bRunFlag[0] && false == m_bRunFlag[1])
    {
        return;
    }
    //更新数据
    OnUpdData(false);

    g_pourTstData.tstInfo.unTotalTime++;
    GetDateTime(&g_pourTstData.tstInfo.dtEnd);
    memcpy(&(g_pourTstData.tstData.dtSample),&(g_pourTstData.tstInfo.dtEnd),sizeof(DateTime));

    if(true==m_bSaveFlag)
    {
        SaveTestData(false);
    }
}

bool CBasicPourProc::StartRun(UINT8    unPumDevType, UINT8 unIndex)
{
    QString strPathName;
    UINT32 unFileCount = 0;

	UINT8 unPumType = GetPumDevTypeIndex(unPumDevType);

    if(true==m_bRunFlag[unPumType])
    {
        m_strErrorInfo = "系统灌注正在进行中,不能重复启动";
        return false;
    }
    GetDataFileName(strPathName);
    if(false==CreateDataFile(strPathName))
    {
        return false;
    }
    m_bRunFlag[unPumType] = false;
    m_unSaveSecs = 0;	//保存数据时间(秒)
    m_unMsTimer  = 0;

    m_unStopCode = 0xFF;
    g_pourTstData.tstInfo.unStopType = m_unStopCode;   //停机类型(或停机方式)
    g_pourTstData.tstInfo.unSectorID = GetMaxTstInfoSctID(&unFileCount);

	printf("unSectorID:%lu unFileCount:%lu \r\n",g_pourTstData.tstInfo.unSectorID,unFileCount);
	if(g_pourTstData.tstInfo.unSectorID > SAVE_POUR_DAT_NUM)
	{
	    DelTestDataFile(g_pourTstData.tstInfo.unSectorID-SAVE_POUR_DAT_NUM);
	}
    if(unFileCount>0)
    {
        g_pourTstData.tstInfo.unSectorID++;
    }

    GetDateTime(&g_pourTstData.tstInfo.dtStart); //启动时间
    GetDateTime(&g_pourTstData.tstInfo.dtEnd);   //停止时间
    g_pourTstData.tstInfo.unRecords   = 0;       //记录条数
    g_pourTstData.tstInfo.unTotalTime = 0;       //灌注总时间，以秒为单位

    m_bRunFlag[unPumType]  = true;
    m_bSaveFlag = true; //保存记录数据
    return true;        //基类不能正常启动
}

bool CBasicPourProc::StopRun(UINT8    unPumDevType)
{
    UINT8 unPumType = GetPumDevTypeIndex(unPumDevType);
	
    if(false==m_bRunFlag[unPumType])
    {
        m_strErrorInfo = "系统不在进行中,不需要停止";
        return false;
    }
	m_bRunFlag[unPumType] = false;
	if(false == m_bRunFlag[0] && \
	   false == m_bRunFlag[1])
	{
	    g_pourTstData.tstInfo.unStopType = m_unStopCode;
	    OnUpdData(true);        //更新实际数据
	    SaveTestData(true);
	}
    
    if(NULL!=m_pWorkThread)
    {
        m_pWorkThread->OnPumStop(unPumType);
    }

    return true;
}

bool CBasicPourProc::SaveTestData(bool bCloseFlag)
{
    //printf("entr CBasicPourProc::SaveTestData \r\n");
    UINT32 unDataPos;
    UINT32 unTestDataLen;
    if(-1==m_fHandle)
    {
        return false;
    }
    //printf("Save TestData...\r\n");
    unDataPos  = g_pourTstData.tstInfo.unRecords;
    g_pourTstData.tstInfo.unRecords++;
    lseek(m_fHandle,0L,SEEK_SET);
    write(m_fHandle,(const char*)&(g_pourTstData.tstInfo),sizeof(PourInfo));

    //单个测试数据长度
    unTestDataLen = sizeof(PourData);
    unDataPos *= unTestDataLen;
    unDataPos += sizeof(PourInfo);
    if(unDataPos != (UINT32)lseek(m_fHandle,unDataPos,SEEK_SET))
    {
        printf("LSEEK Func Error DatwaPos:%lu\r\n",unDataPos);
    }
    //printf("WritePos:%lu\r\n",unDataPos);
    if(unTestDataLen!=(UINT32)write(m_fHandle,(const char*)&(g_pourTstData.tstData),unTestDataLen))
    {
        printf("WriteFile Error DataPos:%lu\r\n",unDataPos);
    }
    else
    {
        fsync(m_fHandle);
    }
    m_bSaveFlag = false; //保存记录数据
    if(true==bCloseFlag)
    {
        close(m_fHandle);
        printf("CloseFile\r\n");
        m_fHandle = -1;
    }

    return true;
}

void CBasicPourProc::DeleteAllMods(void)
{

}

void CBasicPourProc::SetWorkThread(CWorkThread* pWorkThread)
{
    printf("entr CBasicPourProc::SetWorkThread \r\n");
    m_pWorkThread = pWorkThread;
}


void CBasicPourProc::GetDataFileName(QString& strPathFileName)
{
    DateTime dtCurrent;
    GetDateTime(&dtCurrent);
    strPathFileName  = qApp->applicationDirPath()+"/";
    strPathFileName += g_devConfigInfo.basicCfgInfo.strDataPath;
    strPathFileName += "/Data_";
    strPathFileName += DateTimeToString(&dtCurrent);
    strPathFileName += ".DAT";

    strPathFileName.replace(QString(" "), QString("_"));
    strPathFileName.replace(QString("-"), QString("_"));
    strPathFileName.replace(QString(":"), QString("_"));
}
bool CBasicPourProc::CreateDataFile(QString& strPathName)
{
    if(-1 != m_fHandle)
    {
        close(m_fHandle);
    }
    if(-1==(m_fHandle=open(strPathName.toStdString().c_str(),O_WRONLY|O_CREAT,0666)))
    {
        m_strErrorInfo =QString("打开文件:<%1>失败,\r\n错误原因--<%2>\r\n").arg(strPathName)\
                .arg(strerror(errno));
        return false;
    }
    return true;
}

const char* CBasicPourProc::GetErrorInfo()
{
    return m_strErrorInfo.toStdString().c_str();
}

bool CBasicPourProc::IsRun(UINT8 unPumType)
{
    return m_bRunFlag[unPumType];
}
void CBasicPourProc::GetStopErrorInfo(QString& strError)
{
    strError = "";
}

//获取泵类型下标编号 0：动脉血泵；1：静脉血泵
UINT8 CBasicPourProc::GetPumDevTypeIndex(UINT8 unPumDevType)
{
    UINT8 unPumType = 0;
	if(unPumDevType == DEV_APUMP_TYPE)
	{
	    unPumType = 0;//unPumDevType - DEV_APUMP_TYPE;
	}
	else if(unPumDevType == DEV_VPUMP_TYPE)
	{
	    unPumType = 1;//unPumDevType - DEV_VPUMP_TYPE+1;
	}
	return unPumType;
}

