#ifndef _SYS_LOGGER_DB_H_
#define _SYS_LOGGER_DB_H_

#include "singleton.h"
#include "sys_logger_def.h"

#include <string>
#include <vector>
#include <set>
using namespace std;

#include <boost/noncopyable.hpp>
using namespace boost;

class SQLiteUS16Wrapper;

class SysLoggerDB : noncopyable
{
	friend class singleton<SysLoggerDB>;

public:
	bool init();

public:
	void getAllSysLogs(SysLoggerMap &logs);
	bool empty();

public:
	static bool getOldestLogId(const SysLoggerMap &logs, unsigned long &id);

public:
	bool insertDeleteSysLogger(const SysLoggerInfo_t &insertInfo, const set<unsigned long> &deleteInfoIds);

public: //only for test
	bool sysLoggerInsert(const SysLoggerInfo_t &info, unsigned long &id);
	bool sysLoggerDelete(unsigned long id);

private:
	bool transactionDB(const vector<SysLoggerInfo_t> &insertLogs, const set<unsigned long> &deleteLogs);
	bool insertBatchSysLogger(const vector<SysLoggerInfo_t> &insertLogs);

	bool initSysLoggerTable();

private:
	static bool doInsertSysLogger(SQLiteUS16Wrapper &sqlite, const SysLoggerInfo_t &info, unsigned long &id);
	static bool doDeleteSysLogger(SQLiteUS16Wrapper &sqlite, unsigned long id);

private:
	SysLoggerDB();
	~SysLoggerDB();

private:
	wstring m_fullPathName;
};

#endif
