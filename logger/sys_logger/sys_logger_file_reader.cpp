#include "sys_logger_file_reader.h"

#include "filetools.h"
#include "DirMgr.h"
#include "fileWrapper.h"

static string s_sysLogFileName="SysLogger.dat";

SysLoggerFileReader::SysLoggerFileReader()
{
	getRunningPath(m_fullPathName);
	m_fullPathName += DirMgr::getMachineConfigDirName();
	m_fullPathName += "/";
	m_fullPathName+=s_sysLogFileName;
}

SysLoggerFileReader::~SysLoggerFileReader()
{
}

void SysLoggerFileReader::getAllLogs(vector<SysLogInfo> &logs)
{
	logs.clear();

	bool ret;
	SysLogFileInfo_t fileInfo;
	ret=load(fileInfo);
	if (!ret)
	{
		return;
	}

	int current=fileInfo.header.current;
	bool isUsed=true;
	if (0==fileInfo.aRecords[current].dateTime[0])
	{
		isUsed=false;
	}

	SysLogInfo logInfo;
	if (!isUsed)
	{
		for (int i=0;i<current;++i)
		{
			logInfo.dateTime=string(fileInfo.aRecords[i].dateTime,0,STR_DATE_TIME_LEN);

			const size_t size=MAX_LOG_STRING_SIZE+1;
			wchar_t wbuf[size];
			wmemset(&wbuf[0],0,size);
			SWPRINTF(wbuf, size, fileInfo.aRecords[i].aInfos);

			logInfo.logText=wbuf;
			logs.push_back(logInfo);
		}
	}
	else
	{
		int count=0;
		while(count<SYS_LOG_MAX_RECORD_NUM)
		{
			int index=(current+count)%SYS_LOG_MAX_RECORD_NUM;

			logInfo.dateTime=string(fileInfo.aRecords[index].dateTime,0,STR_DATE_TIME_LEN);

			const size_t size=MAX_LOG_STRING_SIZE+1;
			wchar_t wbuf[size];
			wmemset(&wbuf[0],0,size);
			SWPRINTF(wbuf, size, fileInfo.aRecords[index].aInfos);

			logInfo.logText=wbuf;
			logs.push_back(logInfo);

			count++;
		}
	}
	return;
}

bool SysLoggerFileReader::load(SysLogFileInfo_t &fileInfo) const
{
	FILE *file=NULL;
	file=fopen(m_fullPathName.c_str(),"rb");  //read only
	if (file!=NULL)
	{
		FileWrapper fileWrapper(file);

		//check file len valid
		unsigned long fileLen;
		fseek(file,0L,SEEK_END);
		fileLen=ftell(file); 
		fseek(file,0L,SEEK_SET);

		if (fileLen!=sizeof(SysLogFileInfo_t))
		{
			return false;
		}

		fread(&fileInfo,sizeof(fileInfo),1,file);

		//check file header info valid
		if (fileInfo.header.current<SYS_LOG_MAX_RECORD_NUM)
		{
			return true;
		}
	}

	return false;
}
