#include "sys_logger.h"

#include "sys_logger_db.h"
#include "guard.h"

#include "WinDateTime.h"

#include "ace_wchar.h"

#include <boost/foreach.hpp>
using namespace boost;

#include <algorithm>

ISysLogger& ISysLogger::getInstance()
{
	return singleton<SysLogger>::instance();
}

SysLogger::SysLogger()
{
	init();
}

SysLogger::~SysLogger()
{

}

void SysLogger::init()
{
	Guard g(m_lock);

	singleton<SysLoggerDB>::instance().init();
	return;
}

void SysLogger::getAllLogs(vector<SysLogInfo> &logs)
{
    return;
	Guard g(m_lock);

	SysLoggerMap loggers;
	singleton<SysLoggerDB>::instance().getAllSysLogs(loggers);

	logs.clear();
	BOOST_FOREACH(const SysLoggerPair_t &logger, loggers)
	{
		SysLogInfo info;
		info.dateTime=logger.second.dateTime;
		info.logText=logger.second.info;
		logs.push_back(info);
	}

	if (!logs.empty())
	{
		reverse(logs.begin(), logs.end());
	}

	return;
}

void SysLogger::clear()
{
    return;
	Guard g(m_lock);

	singleton<SysLoggerDB>::instance().empty();
	return;
}

void SysLogger::addLog(const wstring &logText)
{
    return;
	Guard g(m_lock);

	SysLoggerDB &db=singleton<SysLoggerDB>::instance();

	SysLoggerMap loggers;
	db.getAllSysLogs(loggers);

	bool ret;
	SysLoggerInfo_t info;
	info.dateTime=WinDateTime::currentDateTimeString();
	info.info=logText;
	info.reserved="";

	set<unsigned long> deleteIds;
	deleteIds.clear();
	if (loggers.size()>=SYS_LOG_MAX_RECORD_NUM)
	{
		unsigned long deleteId;
		ret=SysLoggerDB::getOldestLogId(loggers,deleteId);
		if (ret)
		{
			deleteIds.insert(deleteId);
		}
	}
	db.insertDeleteSysLogger(info,deleteIds);
	return;
}

void SysLogger::addLog(const string &logText)
{
    return;
	addLog(wstring(ACE_TEXT_CHAR_TO_WCHAR(logText.c_str())));
	return;
}
