#ifndef _SQLITE_US16_WRAPPER_H_
#define _SQLITE_US16_WRAPPER_H_

//this SQLiteUS16Wrapper is for us_string to replace SQLiteUWrapper

#include <string>
using namespace std;

#include "sqlite3.h"
#include "sqlite_funcs.h"

class SQLiteUS16Statement
{
private:
	//SQLiteUS16Statement's ctor only to be called by SQLiteUS16Wrapper
	friend class SQLiteUS16Wrapper;

	SQLiteUS16Statement();
	bool init(const wstring &statement, sqlite3 *db, string &errMsg);

public:
	~SQLiteUS16Statement();

	enum DataType
	{
		INT=SQLITE_INTEGER,
		FLT=SQLITE_FLOAT,
		TXT=SQLITE_TEXT,
		BLB=SQLITE_BLOB,
		NUL=SQLITE_NULL,
	};

	//returns the datatype for the passed column
	DataType dataType(int pos_zero_indexed);

	int    valueInt(int pos_zero_indexed);

	//returns the value as std::wstring.
    wstring valueWstring(int pos_zero_indexed);

	const void* valueBlob(int pos_zero_indexed);

    bool bind(int pos_zero_indexed, const wstring &value);
    bool bind(int pos_zero_indexed, double value);
    bool bind(int pos_zero_indexed, int value);
	bool bind(int pos_zero_indexed, const void *value, int valueLen);
    bool bindNull(int pos_zero_indexed);

    bool execute(string &errMsg);

	//returns true as long as there are still records to be fetched. 
    bool nextRow(string &errMsg);

    /*   Call Reset if not depending on the NextRow cleaning up.
         For example for select count(*) statements*/
    bool reset();

    bool restartSelect();

  private:
    sqlite3_stmt* stmt_;
};

class SQLiteUS16Wrapper
{
public:
	SQLiteUS16Wrapper();
	~SQLiteUS16Wrapper();

	bool open(const wstring &db_file);

public:
	//used to execute any SQL statement. NOT for select statement as the data won't be returned.
	bool directStatement(const string &stmt);

	SQLiteUS16Statement* statement(const wstring &strStatement, string &errMsg);

	int lastErrorCode();
    wstring lastError();

	sqlite3_int64 last_insert_rowid();

    // Transaction related
    bool begin();
    bool commit();
    bool rollback();

private:
    sqlite3* db_;
};

#endif
