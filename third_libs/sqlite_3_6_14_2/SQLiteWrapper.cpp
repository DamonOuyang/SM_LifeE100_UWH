#include "SQLiteWrapper.h"

#include <assert.h>

#include <sstream>
using namespace std;

SQLiteWrapper::SQLiteWrapper() : db_(NULL)
{
}

SQLiteWrapper::~SQLiteWrapper()
{
	if (db_!=NULL)
	{
		sqlite3_close(db_);
	}
}

bool SQLiteWrapper::open(const string &db_file)
{
	if (sqlite3_open(db_file.c_str(), &db_) != SQLITE_OK)
	{
		return false;
	}

	return true;
}

bool SQLiteWrapper::selectStmt(const string &stmt, ResultTable &res)
{
	char *errmsg;
	int   ret;

	res.reset();

	ret = sqlite3_exec(db_, stmt.c_str(), SelectCallback, static_cast<void*> (&res), &errmsg);
	if (ret != SQLITE_OK)
	{
		return false;
	}
	return true;
}

SQLiteStatement* SQLiteWrapper::statement(const string &strStatement, string &errMsg)
{
	SQLiteStatement *stmt=NULL;
	stmt = new SQLiteStatement();
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

bool SQLiteWrapper::directStatement(const string &stmt) 
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

int SQLiteWrapper::lastErrorCode()
{
	return sqlite3_errcode(db_);
}

string SQLiteWrapper::lastError() 
{
	return sqlite3_errmsg(db_);
}

bool SQLiteWrapper::begin() 
{
	return directStatement("begin");
}

bool SQLiteWrapper::commit() 
{
	return directStatement("commit");
}

bool SQLiteWrapper::rollback() 
{
	return directStatement("rollback");
}

sqlite3_int64 SQLiteWrapper::last_insert_rowid()
{
	return sqlite3_last_insert_rowid(db_);
}

// TODO parameter p_col_names
int SQLiteWrapper::SelectCallback(void *p_data, int num_fields, char **p_fields, char** p_col_names)
{
	ResultTable* res = reinterpret_cast<ResultTable*>(p_data);

	ResultRecord record;

	//column names in the first row of res if res is empty
	if(res->m_records.size()==0)
	{
		ResultRecord col_names;

		for(int i=0; i < num_fields; i++) 
		{
			if(p_fields[i])
			{
				col_names.m_fields.push_back (p_col_names[i]);
			}
			else
			{
				col_names.m_fields.push_back("(null)"); 
			}
		}
		res->m_records.push_back(col_names);
	}

	for(int i=0; i < num_fields; i++) 
	{
		if (p_fields[i]) 
		{
			record.m_fields.push_back(p_fields[i]);
		}
		else   
		{
			record.m_fields.push_back("<null>");
		}
	}

	res->m_records.push_back(record);

	return 0;
}

SQLiteStatement::SQLiteStatement() : stmt_(NULL)
{
}

SQLiteStatement::~SQLiteStatement()
{
	// Prevent the database remaining locked after some statement.
	if(stmt_!=NULL)
	{
		sqlite3_finalize(stmt_);
	}
}

bool SQLiteStatement::init(const string &statement, sqlite3 *db, string &errMsg)
{
	errMsg="";

	if ( 
	  sqlite3_prepare(
		db, 
		statement.c_str(),  // stmt
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

SQLiteStatement::DataType SQLiteStatement::dataType(int pos_zero_indexed) 
{
	return DataType(sqlite3_column_type(stmt_, pos_zero_indexed));
}

int SQLiteStatement::valueInt(int pos_zero_indexed) 
{
	return sqlite3_column_int(stmt_, pos_zero_indexed);
}

string SQLiteStatement::valueString(int pos_zero_indexed)
{
	return std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt_, pos_zero_indexed)));
}

const void* SQLiteStatement::valueBlob(int pos_zero_indexed)
{
	return sqlite3_column_blob(stmt_, pos_zero_indexed);
}

bool SQLiteStatement::bind(int pos_zero_indexed, std::string const& value)
{
	if (
		sqlite3_bind_text (
			stmt_,
			pos_zero_indexed+1,  // Index of wildcard
			value.c_str(),
			static_cast<int>(value.length()),      // length of text
			SQLITE_TRANSIENT     // SQLITE_TRANSIENT: SQLite makes its own copy
		)!=SQLITE_OK)
	{
		return false;
	}
	return true;
}

bool SQLiteStatement::bind(int pos_zero_indexed, double value) 
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

bool SQLiteStatement::bind(int pos_zero_indexed, int value) 
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

bool SQLiteStatement::bind(int pos_zero_indexed, const void *value, int valueLen)
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

bool SQLiteStatement::bindNull(int pos_zero_indexed) 
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

bool SQLiteStatement::execute(string &errMsg)
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

bool SQLiteStatement::nextRow(string &errMsg) 
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

bool SQLiteStatement::reset() 
{
	int rc = sqlite3_step(stmt_);

	sqlite3_reset(stmt_);

	if (rc == SQLITE_ROW)
	{
		return true;
	}
	return false;
}

bool SQLiteStatement::restartSelect() 
{
	sqlite3_reset(stmt_);
	return true;
}

