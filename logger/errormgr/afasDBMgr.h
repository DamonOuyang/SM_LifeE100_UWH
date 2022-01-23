#pragma once
#include "singleton.h"
#include "SQLiteWrapper.h"
#include "asaf_def.h"

class afasDBMgr
{
	friend class singleton<afasDBMgr>;
private:
	afasDBMgr(void);
	~afasDBMgr(void);

	string m_fullPathName;
	bool m_isInit;
	SQLiteWrapper m_sqlite;
	string m_currentLang;
public:
	static afasDBMgr& getInstance();
	bool   init(const string &fullPathFileName = "");
	void   setLangTableFromLangID(string lang_id);
	void   make_afas( string e_code , vector<afas_struct>& afases);
	bool   is_has_afas(string e_code);
private:
	bool   getCauseFromErrorCode(string e_code , vector<struct_cause>& causes);
	bool   getSolutionFromErrorCode(string e_code , vector<struct_solution>& solutions);
	bool   getCauseAndSolutionFromErrorCode(string e_code , vector<struct_cause>& causes ,  vector<struct_solution>& solutions);
	string makeSelectString(string itemCode , string strTable , string strTab);
	bool   selectItemsFromTable(string itemCode , string strTable , string strTab ,SQLiteWrapper::ResultTable& retTable);
};
