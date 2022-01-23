#include "ErrorMgrDB.h"

#include "SQLiteWrapper.h"

#include "filetools.h"
#include "DirMgr.h"

#include "ISysLogger.h"

#include <sstream>
#include <memory>

static const string s_db_file="error.db";

ErrorMgrDB::ErrorMgrDB()
{
	m_errorCode=0;

	getRunningPath(m_fullPathName);
	m_fullPathName += DirMgr::getMachineConfigDirName();
        m_fullPathName += "/";
	m_fullPathName+=s_db_file;
}

ErrorMgrDB::~ErrorMgrDB()
{

}

bool ErrorMgrDB::init(ErrorMgrMap &infos)
{
	infos.clear();

	bool ret;
	SQLiteWrapper sqlite;
	ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		addLog(sqlite,"open Error DB file error!");
		return false;
	}

	ret=sqlite.directStatement("create table error(machineName,boardId,id,type,isFatal,compIndex,dateTime,PRIMARY KEY(machineName,boardId,id))");
	if (ret)
	{
        ::syncCache();
		return true;
	}

	m_errorCode=sqlite.lastErrorCode();
	if (!::isTableExistedErrorCode(m_errorCode))
	{
		addLog(sqlite,"create table error failed!");
		return false;
	}

	string strStatement="select * from error";
	ret=sqlite.directStatement(strStatement.c_str());
	if (!ret)
	{
		addLog(sqlite,"select table error failed!");
		return false;
	}

	string errMsg;
	auto_ptr<SQLiteStatement> stmt(sqlite.statement(strStatement.c_str(),errMsg));
	if (NULL==stmt.get())
	{
		addLog(sqlite,errMsg);
		return false;
	}

	while (stmt->nextRow(errMsg))
	{
		ErrorKey_t key;
		key.machineName=stmt->valueString(0);
		key.boardId=static_cast<BYTE>(stmt->valueInt(1));
		key.id=stmt->valueString(2);

		ErrorInfo_t info;
		info.isPersistent=true;
		ErrorDBInfo_t &dbInfo=info.dbInfo;
		dbInfo.type=static_cast<EErrorType>(stmt->valueInt(3));
		int fatal=stmt->valueInt(4);
		if (0==fatal)
		{
			dbInfo.isFatal=false;
		}
		else
		{
			dbInfo.isFatal=true;
		}
		dbInfo.compIndex=static_cast<unsigned short>(stmt->valueInt(5));
		dbInfo.dateTime=stmt->valueString(6);

		infos.insert(make_pair(key,info));
	}

	return true;
}

bool ErrorMgrDB::insert(const ErrorKey_t &key, const ErrorDBInfo_t &dbInfo)
{
	bool ret;

	SQLiteWrapper sqlite;
	ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		addLog(sqlite,"open Error DB file error!");
		return false;
	}

	string errMsg;
	auto_ptr<SQLiteStatement> stmt(sqlite.statement("insert into error values(?,?,?,?,?,?,?)",errMsg));
	if (NULL==stmt.get())
	{
		addLog(sqlite,errMsg);
		return false;
	}

	stmt->bind(0,key.machineName);
	stmt->bind(1,static_cast<int>(key.boardId));
	stmt->bind(2,key.id);
	stmt->bind(3,static_cast<int>(dbInfo.type));
	int fatal=0;
	if (dbInfo.isFatal)
	{
		fatal=1;
	}
	stmt->bind(4,fatal);
	stmt->bind(5,static_cast<int>(dbInfo.compIndex));
	stmt->bind(6,dbInfo.dateTime);

	ret=stmt->execute(errMsg);
	if (!ret)
	{
		addLog(sqlite,"insert table error failed!");
		return false;
	}

    ::syncCache();
	return true;
}

bool ErrorMgrDB::remove(const ErrorKey_t &key)
{
	bool ret;

	SQLiteWrapper sqlite;
	ret=sqlite.open(m_fullPathName);
	if (!ret)
	{
		addLog(sqlite,"open Error DB file error!");
		return false;
	}

	ostringstream os;
	os << "delete from error where machineName=\""
		<< key.machineName << "\""
		<< " and boardId=" << static_cast<int>(key.boardId)
		<< " and id=\"" << key.id << "\""
		<< ";" << endl;
	string str=os.str();
	ret=sqlite.directStatement(os.str().c_str());
	if (!ret)
	{
		addLog(sqlite,"delete table error failed!");
		return false;
	}

    ::syncCache();
	return true;
}

void ErrorMgrDB::addLog(SQLiteWrapper &sqlite, const string &errMsg)
{
	m_errorCode=sqlite.lastErrorCode();
	ostringstream os;
	os << errMsg.c_str() << "ErrorCode:" << m_errorCode;
	ISysLogger::getInstance().addLog(os.str());
	return;
}
