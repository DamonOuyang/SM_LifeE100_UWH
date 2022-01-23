#include "sqlite_us16_wrapper.h"

#include <assert.h>

#include <sstream>
using namespace std;

SQLiteUS16Wrapper::SQLiteUS16Wrapper() : db_(NULL)
{
}

SQLiteUS16Wrapper::~SQLiteUS16Wrapper()
{
	if (db_!=NULL)
	{
		sqlite3_close(db_);
	}
}

bool SQLiteUS16Wrapper::open(const wstring &db_file)
{
	us_string usstr=SqliteFuncs::wstring_to_us_string(db_file);
	if (sqlite3_open16(usstr.c_str(), &db_) != SQLITE_OK)
	{
		return false;
	}

	return true;
}

bool SQLiteUS16Wrapper::directStatement(const string &stmt) //???
{
	char *errmsg;
	int   ret;
	ret = sqlite3_exec(db_, stmt.c_str(), 0, 0, &errmsg);

	if(ret != SQLITE_OK) 
	{
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}

int SQLiteUS16Wrapper::lastErrorCode()
{
	return sqlite3_errcode(db_);
}

wstring SQLiteUS16Wrapper::lastError() 
{
	us_string usstr=reinterpret_cast<const unsigned short *>(sqlite3_errmsg16(db_));
	wstring wstr=SqliteFuncs::us_string_to_wstring(usstr);
	return wstr;
}

bool SQLiteUS16Wrapper::begin() 
{
	return directStatement("begin");
}

bool SQLiteUS16Wrapper::commit() 
{
	return directStatement("commit");
}

bool SQLiteUS16Wrapper::rollback() 
{
	return directStatement("rollback");
}

sqlite3_int64 SQLiteUS16Wrapper::last_insert_rowid()
{
	return sqlite3_last_insert_rowid(db_);
}

SQLiteUS16Statement* SQLiteUS16Wrapper::statement(const wstring &strStatement, string &errMsg)
{
	SQLiteUS16Statement *stmt=NULL;
	stmt = new SQLiteUS16Statement();
	if (stmt!=NULL)
	{
		bool ret=stmt->init(strStatement, db_, errMsg);
		if (!ret)
		{
			delete stmt;
			stmt=NULL;
		}
	}
	return stmt;
}

bool SQLiteUS16Statement::init(const wstring &statement, sqlite3* db, string &errMsg)
{
	us_string usstr=SqliteFuncs::wstring_to_us_string(statement);
	if ( 
		sqlite3_prepare16(
		db, 
		usstr.c_str(),  // stmt
		-1,                  // If than zero, then stmt is read up to the first nul terminator
		&stmt_,
		0                   // Pointer to unused portion of stmt
		) != SQLITE_OK) 
	{
		errMsg=sqlite3_errmsg(db);
		return false;
	}

	if (!stmt_) 
	{
		errMsg="stmt_ is 0";
		return false;
	}
	return true;
}

SQLiteUS16Statement::SQLiteUS16Statement() : stmt_(NULL)
{
}

SQLiteUS16Statement::~SQLiteUS16Statement()
{
	// Prevent the database remaining locked after some statement.
	if(stmt_!=NULL)
	{
		sqlite3_finalize(stmt_);
	}
}

SQLiteUS16Statement::DataType SQLiteUS16Statement::dataType(int pos_zero_indexed) 
{
	return DataType(sqlite3_column_type(stmt_, pos_zero_indexed));
}

int SQLiteUS16Statement::valueInt(int pos_zero_indexed)
{
	return sqlite3_column_int(stmt_, pos_zero_indexed);
}

wstring SQLiteUS16Statement::valueWstring(int pos_zero_indexed)
{
	us_string usstr=reinterpret_cast<const unsigned short *>(sqlite3_column_text16(stmt_, pos_zero_indexed));
	wstring wstr=SqliteFuncs::us_string_to_wstring(usstr);
	return wstr;
}

const void* SQLiteUS16Statement::valueBlob(int pos_zero_indexed)
{
	return sqlite3_column_blob(stmt_, pos_zero_indexed);
}

bool SQLiteUS16Statement::bind(int pos_zero_indexed, const wstring &value)
{
	us_string usstr=SqliteFuncs::wstring_to_us_string(value);
	if (
		sqlite3_bind_text16 (
		stmt_,
		pos_zero_indexed+1,  // Index of wildcard
		usstr.c_str(),
		static_cast<int>(value.length()*sizeof(unsigned short)),   // length of text
		SQLITE_TRANSIENT     // SQLITE_TRANSIENT: SQLite makes its own copy
		)!=SQLITE_OK)
	{
		return false;
	}
	return true;
}

bool SQLiteUS16Statement::bind(int pos_zero_indexed, double value) 
{
	if (
		sqlite3_bind_double(
		stmt_,
		pos_zero_indexed+1,  // Index of wildcard
		value
		)!=SQLITE_OK) 
	{
		return false;
	}
	return true;
}

bool SQLiteUS16Statement::bind(int pos_zero_indexed, int value) 
{
	if (
		sqlite3_bind_int(
		stmt_,
		pos_zero_indexed+1,  // Index of wildcard
		value 
		)!=SQLITE_OK) 
	{
		return false;
	}
	return true;
}

bool SQLiteUS16Statement::bind(int pos_zero_indexed, const void *value, int valueLen)
{
	if (
		sqlite3_bind_blob(
		stmt_,
		pos_zero_indexed+1,  // Index of wildcard
		value,
		valueLen,
		SQLITE_TRANSIENT
		)!=SQLITE_OK)
	{
		return false;
	}

	return true;
}

bool SQLiteUS16Statement::bindNull(int pos_zero_indexed) 
{
	if (
		sqlite3_bind_null(
		stmt_,
		pos_zero_indexed+1  // Index of wildcard
		)!=SQLITE_OK) 
	{
		return false;
	}
	return true;
}

bool SQLiteUS16Statement::execute(string &errMsg)
{
	int rc = sqlite3_step(stmt_);
	if (rc == SQLITE_BUSY)
	{
		errMsg="SQLITE_BUSY";
		return false;
	}

	if (rc == SQLITE_ERROR) 
	{
		errMsg="SQLITE_ERROR";
		return false;
	}

	if (rc == SQLITE_MISUSE)
	{
		errMsg="SQLITE_ERROR";
		return false;
	}

	if (rc != SQLITE_DONE) 
	{
		return false;
	}
	sqlite3_reset(stmt_);
	return true;
}

bool SQLiteUS16Statement::nextRow(string &errMsg) 
{
	int rc = sqlite3_step(stmt_);

	if (rc == SQLITE_ROW   )
	{
		return true;
	}

	if (rc == SQLITE_DONE  ) 
	{
		sqlite3_reset(stmt_);
		return false;
	} 
	else if (rc == SQLITE_MISUSE) 
	{
		errMsg="SQLiteStatement::NextRow SQLITE_MISUSE";
	} 
	else if (rc == SQLITE_BUSY  ) 
	{
		errMsg="SQLiteStatement::NextRow SQLITE_BUSY";
	} 
	else if (rc == SQLITE_ERROR ) 
	{
		errMsg="SQLiteStatement::NextRow SQLITE_ERROR";
	}
	return false;
}

bool SQLiteUS16Statement::reset() 
{
	int rc = sqlite3_step(stmt_);

	sqlite3_reset(stmt_);

	if (rc == SQLITE_ROW)
	{
		return true;
	}
	return false;
}

bool SQLiteUS16Statement::restartSelect() 
{
	sqlite3_reset(stmt_);
	return true;
}
