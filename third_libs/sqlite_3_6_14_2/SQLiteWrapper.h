#ifndef _SQLITE_WRAPPER_H_
#define _SQLITE_WRAPPER_H_

#include <string>
#include <vector>
using namespace std;

#include "sqlite3.h"

inline bool isTableExistedErrorCode(int errorCode)
{
	return SQLITE_ERROR==errorCode;
}

class SQLiteStatement
{
private:
	//SQLiteStatement's ctor only to be called by SQLiteWrapper
	friend class SQLiteWrapper;

	SQLiteStatement();
	bool init(const string &statement, sqlite3 *db, string &errMsg);

public:
	~SQLiteStatement();

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

	//returns the value as std::string.
    string valueString(int pos_zero_indexed);

	const void* valueBlob(int pos_zero_indexed);

    bool bind(int pos_zero_indexed, const string &value);
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

class SQLiteWrapper
{
public:
	SQLiteWrapper();
	~SQLiteWrapper();

	bool open(const string &db_file);

public:
	class ResultRecord
	{
    public:
        vector<string> m_fields;
    };

	class ResultTable
	{
		friend class SQLiteWrapper;

	public:
		ResultTable() : m_cur_record(0) {}

		ResultRecord* next()
		{
			if (m_cur_record<m_records.size())
			{
				return &m_records[m_cur_record++];
			}
			return NULL;
		}

	public:
		vector<ResultRecord> m_records;

	private:
		void reset()
		{
			m_records.clear();
			m_cur_record=0;
		}

	private:
		unsigned int m_cur_record;
	};

public:
	bool selectStmt(const string &stmt, ResultTable &res);

	//used to execute any SQL statement. NOT for select statement as the data won't be returned.
	bool directStatement(const string &stmt);

	SQLiteStatement* statement(const string &stmt, string &errMsg);

	int lastErrorCode();
    string lastError();

	sqlite3_int64 last_insert_rowid();

    // Transaction related
    bool begin();
    bool commit();
    bool rollback();

private:
    static int SelectCallback(void *p_data, int num_fields, char **p_fields, char **p_col_names);
    sqlite3* db_;
};

#endif
