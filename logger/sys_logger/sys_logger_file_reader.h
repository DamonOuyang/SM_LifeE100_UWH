#ifndef _SYS_LOGGER_FILE_READER_H_
#define _SYS_LOGGER_FILE_READER_H_

#include "singleton.h"
#include "sys_logger_def.h"
#include "ISysLogger.h"

#include "WinDateTime.h"

#include <boost/noncopyable.hpp>

#include <vector>

class SysLoggerFileReader : boost::noncopyable
{
	friend class singleton<SysLoggerFileReader>;

public: 
	void getAllLogs(vector<SysLogInfo> &logs);

private:
	enum 
	{
		MAX_LOG_STRING_SIZE=100,   // max length of the log string
	};

#pragma pack(1)
	typedef struct 
	{
		unsigned short current;
	} SysLogFileHeader_t;

	typedef struct 
	{
		char dateTime[STR_DATE_TIME_LEN];
		wchar_t aInfos[MAX_LOG_STRING_SIZE];
	} SysLogFileRecord_t;

	typedef struct 
	{
		SysLogFileHeader_t header;
		SysLogFileRecord_t aRecords[SYS_LOG_MAX_RECORD_NUM];
	} SysLogFileInfo_t;
#pragma pack()

private:
	bool load(SysLogFileInfo_t &fileInfo) const;

private:
	SysLoggerFileReader();
	~SysLoggerFileReader();

private:
	string m_fullPathName;
};

#endif
