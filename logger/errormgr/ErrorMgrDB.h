#ifndef _ERROR_MGR_DB_H_
#define _ERROR_MGR_DB_H_

#include "singleton.h"
#include "error_mgr_def.h"

class SQLiteWrapper;

class ErrorMgrDB
{
	friend class singleton<ErrorMgrDB>;

public:
	bool init(ErrorMgrMap &infos);
	bool insert(const ErrorKey_t &key, const ErrorDBInfo_t &dbInfo);
	bool remove(const ErrorKey_t &key);

public:
	int getErrorCode() const { return m_errorCode;}

private:
	void addLog(SQLiteWrapper &sqlite, const string &errMsg);

private:
	ErrorMgrDB();
	~ErrorMgrDB();

private:
	int m_errorCode;
	string m_fullPathName;

private:
	ErrorMgrDB(const ErrorMgrDB &rhs);
	ErrorMgrDB& operator=(const ErrorMgrDB &rhs);
};

#endif
