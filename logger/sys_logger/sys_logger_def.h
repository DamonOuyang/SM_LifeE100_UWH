#ifndef _SYS_LOGGER_DEF_H_
#define _SYS_LOGGER_DEF_H_

#include <map>
#include <string>
using namespace std;

enum 
{
	SYS_LOG_MAX_RECORD_NUM=500,  //max log record number
};

//table SysLogger
typedef struct 
{
	string dateTime;
	wstring info;
	string reserved;
} SysLoggerInfo_t;

typedef map<unsigned long, SysLoggerInfo_t> SysLoggerMap;
typedef pair<unsigned long, SysLoggerInfo_t> SysLoggerPair_t;

#endif
