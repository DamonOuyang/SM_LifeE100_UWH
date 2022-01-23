#include "sys_logger_db.h"

#include "filetools.h"
#include "DirMgr.h"
#include "ace_wchar.h"

#include "sqlite_us16_wrapper.h"
#include "SQLiteWrapper.h"

#include "sys_logger_file_reader.h"

#include <sstream>
#include <cassert>
#include <memory>

#include <boost/foreach.hpp>
using namespace boost;

static const string s_db_file="sys_logger.db";

SysLoggerDB::SysLoggerDB()
{
	string name;
	getRunningPath(name);
	name += DirMgr::getMachineConfigDirName();
	name += "/";
	name+=s_db_file;

	m_fullPathName=ACE_TEXT_CHAR_TO_WCHAR(name.c_str());
}

SysLoggerDB::~SysLoggerDB()
{

}

bool SysLoggerDB::init()
{
	bool isSync=false;

	vector<SysLogInfo> logs;
	bool isFileExist=::myFileExists(m_fullPathName);
	if (!isFileExist)
	{
		SysLoggerFileReader &reader=singleton<SysLoggerFileReader>::instance();
		reader.getAllLogs(logs);
		if (!logs.empty())
		{
			isSync=true;
		}
	}

	bool ret=initSysLoggerTable();
	if (!ret)
	{
		return false;
	}

	if (isSync)
	{
		vector<SysLoggerInfo_t> insertLogs;
		insertLogs.clear();

		BOOST_FOREACH(const SysLogInfo &log, logs)
		{
			SysLoggerInfo_t info;
			info.dateTime=log.dateTime;
			info.info=log.logText;
			info.reserved="";
			insertLogs.push_back(info);
		}
		insertBatchSysLogger(insertLogs);
	}

	return true;
}

bool SysLoggerDB::sysLoggerInsert(const SysLoggerInfo_t &info, unsigned long &id)
{
	bool ret;

	SQLiteUS16Wrapper sqlite;
	ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		return false;
	}

	ret=doInsertSysLogger(sqlite,info,id);
	return ret;
}


bool SysLoggerDB::initSysLoggerTable()
{
	SQLiteUS16Wrapper sqlite;
	bool ret=sqlite.open(m_fullPathName.c_str());
	if (!ret)
	{
		return false;
	}

	//table SysLogger
	string statement = "create table SysLogger(id INTEGER PRIMARY KEY AUTOINCREMENT,dateTime,info,reserved);";
	ret=sqlite.directStatement(statement.c_str());
	if (ret)
	{
        ::syncCache();
		return true;
	}

	int errorCode=sqlite.lastErrorCode();
	if (!::isTableExistedErrorCode(errorCode))
	{
		return false;
	}
	return true;
}

bool SysLoggerDB::sysLoggerDelete(unsigned long id)
{
	bool ret;

	SQLiteUS16Wrapper sqlite;
	ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		return false;
	}

	ret=doDeleteSysLogger(sqlite,id);
	return ret;
}

bool SysLoggerDB::doInsertSysLogger(SQLiteUS16Wrapper &sqlite, const SysLoggerInfo_t &info, unsigned long &id)
{
	string errMsg;
	auto_ptr<SQLiteUS16Statement> stmt(sqlite.statement(ACE_TEXT_CHAR_TO_WCHAR("insert into SysLogger values(null,?,?,?)"),errMsg));
	if (NULL==stmt.get())
	{
		return false;
	}

	stmt->bind(0,ACE_TEXT_CHAR_TO_WCHAR(info.dateTime.c_str()));
	stmt->bind(1,info.info);
	stmt->bind(2,ACE_TEXT_CHAR_TO_WCHAR(info.reserved.c_str()));

	bool ret=stmt->execute(errMsg);
	if (ret)
	{
		id=static_cast<unsigned long>(sqlite.last_insert_rowid());
	}
    ::syncCache();
	return ret;
}

bool SysLoggerDB::doDeleteSysLogger(SQLiteUS16Wrapper &sqlite, unsigned long id)
{
	ostringstream os;
	os << "delete from SysLogger"
		<< " where id=" << id << ";" << endl;

	string str=os.str();
	bool ret=sqlite.directStatement(str.c_str());
    ::syncCache();
	return ret;
}

void SysLoggerDB::getAllSysLogs(SysLoggerMap &logs)
{
	logs.clear();

	SQLiteUS16Wrapper sqlite;
	bool ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		return;
	}

	string errMsg;
	auto_ptr<SQLiteUS16Statement> stmt(sqlite.statement(L"select * from SysLogger",errMsg));
	assert(stmt.get()!=NULL);
	while (stmt->nextRow(errMsg))
	{
		unsigned long id=atol(ACE_TEXT_WCHAR_TO_CHAR(stmt->valueWstring(0).c_str()));

		SysLoggerInfo_t info;
		info.dateTime=ACE_TEXT_WCHAR_TO_CHAR(stmt->valueWstring(1).c_str());
		info.info=stmt->valueWstring(2).c_str();
		info.reserved=ACE_TEXT_WCHAR_TO_CHAR(stmt->valueWstring(3).c_str());

		logs.insert(make_pair(id,info));
	}
	return;
}

bool SysLoggerDB::getOldestLogId(const SysLoggerMap &logs, unsigned long &id)
{
	if (logs.empty())
	{
		return false;
	}

	BOOST_FOREACH(const SysLoggerPair_t &log, logs)
	{
		id=log.first;
		break;
	}
	return true;
}

bool SysLoggerDB::transactionDB(const vector<SysLoggerInfo_t> &insertLogs, const set<unsigned long> &deleteLogs)
{
	bool ret;

	SQLiteUS16Wrapper sqlite;
	ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		return false;
	}

	ret=sqlite.begin();
	if (!ret)
	{
		return false;
	}

	BOOST_FOREACH(const SysLoggerInfo_t &insertLog, insertLogs)
	{
		unsigned long id;
		ret = doInsertSysLogger(sqlite, insertLog, id);
		if (!ret)
		{
			sqlite.rollback();
            ::syncCache();
			return false;
		}
	}

	BOOST_FOREACH(const unsigned long &deleteLog, deleteLogs)
	{
		ret = doDeleteSysLogger(sqlite, deleteLog);
		if (!ret)
		{
			sqlite.rollback();
            ::syncCache();
			return false;
		}
	}

	ret=sqlite.commit();
	if (!ret)
	{
		sqlite.rollback();
        ::syncCache();
		return false;
	}

    ::syncCache();
	return true;
}

bool SysLoggerDB::insertDeleteSysLogger(const SysLoggerInfo_t &insertInfo, const set<unsigned long> &deleteInfoIds)
{
	vector<SysLoggerInfo_t> insertLogs;
	set<unsigned long> deleteLogs;

	insertLogs.clear();
	deleteLogs.clear();

	assert(deleteInfoIds.size()<=1);

	insertLogs.push_back(insertInfo);
	BOOST_FOREACH(const unsigned long &id, deleteInfoIds)
	{
		deleteLogs.insert(id);
	}

	return transactionDB(insertLogs,deleteLogs);
}

bool SysLoggerDB::insertBatchSysLogger(const vector<SysLoggerInfo_t> &insertLogs)
{
	set<unsigned long> deleteLogs;
	deleteLogs.clear();

	return transactionDB(insertLogs,deleteLogs);
}

bool SysLoggerDB::empty()
{
	bool ret;

	SQLiteUS16Wrapper sqlite;
	ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		return false;
	}

	ret=sqlite.begin();
	if (!ret)
	{
		return false;
	}

	ret=sqlite.directStatement("delete from SysLogger");
	if (!ret)
	{
		sqlite.rollback();
        ::syncCache();
		return false;
	}

	ret=sqlite.commit();
	if (!ret)
	{
		sqlite.rollback();
        ::syncCache();
		return false;
	}

    ::syncCache();
	return true;
}
