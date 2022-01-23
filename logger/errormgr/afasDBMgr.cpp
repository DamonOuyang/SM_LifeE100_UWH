#include "afasDBMgr.h"
#include "filetools.h"
#include "SQLiteWrapper.h"
#include "DirMgr.h"

static const string afasDBFile = "afas.db";

afasDBMgr::afasDBMgr(void)
:m_isInit(false)
,m_currentLang("String_English")
{
	getRunningPath(m_fullPathName);
	m_fullPathName += DirMgr::getMachineConfigDirName();
	m_fullPathName += "/";
	m_fullPathName+= afasDBFile;
}

afasDBMgr::~afasDBMgr(void)
{
}

afasDBMgr& afasDBMgr::getInstance()
{
	return singleton<afasDBMgr>::instance();
}

bool afasDBMgr::init(const string &fullPathFileName)
{
	bool b = true;
	if(!fullPathFileName.empty())
	{
		m_fullPathName = fullPathFileName;
	}
	bool ret = m_sqlite.open(m_fullPathName);
	if (!ret)
	{
		b = false;
	}
	m_isInit = true;
	return b;
}

string afasDBMgr::makeSelectString( string itemCode , string strTable , string strTab)
{
	string str = "select * from ";
	str+= strTable;
	str+= " ";
	str+= "where ";
	str+= strTab;
	str+= " = ";
	str+= "\"";
	str+= itemCode;
	str+= "\"";
	return str;
}

bool afasDBMgr::selectItemsFromTable( string itemCode , string strTable , string strTab ,SQLiteWrapper::ResultTable& retTable)
{
	if(!m_isInit)
	{
		if(!init())
			return false;
	}
	string selectString = makeSelectString(itemCode , strTable , strTab);
	return m_sqlite.selectStmt(selectString, retTable);
}

bool afasDBMgr::getCauseFromErrorCode( string e_code , vector<struct_cause>& causes )
{
	SQLiteWrapper::ResultTable retTable;
	bool ret=selectItemsFromTable(e_code , "Cause" , "Error_id" , retTable);
	if (ret)
	{
		for (size_t i = 1; i< retTable.m_records.size();++i)
		{
			SQLiteWrapper::ResultRecord record=retTable.m_records[i];
			struct_cause cause_info;
			cause_info.error_code = record.m_fields[CAUSE_ERROR];
			cause_info.cause_id   = record.m_fields[CAUSE_ID];
			cause_info.cause_level = static_cast<int>(atoi(record.m_fields[CAUSE_LEVEL].c_str()));
			cause_info.cause_string_nr = record.m_fields[CAUSE_STRING_NR];
			cause_info.cause_options = record.m_fields[CAUSE_OPTIONS];
			
			SQLiteWrapper::ResultTable causeRetTable;
			

			bool causeRet = selectItemsFromTable(cause_info.cause_string_nr ,m_currentLang ,"String_ID" ,causeRetTable);
			if (causeRet && !causeRetTable.m_records.empty())
			{
				SQLiteWrapper::ResultRecord causeRecord=causeRetTable.m_records[1];
				cause_info.cause_string = causeRecord.m_fields[STRING_TEXT];
			}
			else
			{
				cause_info.cause_string = "";
			}
			causes.push_back(cause_info);
		}
	}
	return ret;
}

bool afasDBMgr::getSolutionFromErrorCode( string e_code , vector<struct_solution>& solutions )
{
	SQLiteWrapper::ResultTable retTable;
	bool ret=selectItemsFromTable(e_code , "Solution" , "Error_id" , retTable);
	if (ret)
	{
		for (size_t i = 1; i< retTable.m_records.size();++i)
		{
			SQLiteWrapper::ResultRecord record=retTable.m_records[i];
			struct_solution solution_info;
			solution_info.error_code = record.m_fields[SOLUTION_ERROR];
			solution_info.cause_id   = record.m_fields[SOLUTION_CAUSE];
			solution_info.solution_index = record.m_fields[SOLUTION_SOLUTION];
			solution_info.solution_level = static_cast<int>(atoi(record.m_fields[SOLUTION_LEVEL].c_str()));
			solution_info.solution_string_nr = record.m_fields[SOLUTION_STRING_NR];
			solution_info.solution_options = record.m_fields[SOLUTION_OPTIONS];
			
			SQLiteWrapper::ResultTable solutionRetTable;
			bool causeRet = selectItemsFromTable(solution_info.solution_string_nr ,m_currentLang ,"String_ID" ,solutionRetTable);
			if (causeRet && !solutionRetTable.m_records.empty())
			{
				SQLiteWrapper::ResultRecord solutionRecord=solutionRetTable.m_records[1];
				solution_info.solution_string = solutionRecord.m_fields[STRING_TEXT];
			}
			else
			{
				solution_info.solution_string = "";
			}
			solutions.push_back(solution_info);
		}
	}
	return ret;
}

bool afasDBMgr::getCauseAndSolutionFromErrorCode( string e_code , vector<struct_cause>& causes , vector<struct_solution>& solutions )
{
	return getCauseFromErrorCode(e_code , causes) && getSolutionFromErrorCode(e_code , solutions);
}


void afasDBMgr::make_afas( string e_code , vector<afas_struct>& afases)
{
	vector<struct_cause> causes ;
	vector<struct_solution> solutions;
	getCauseAndSolutionFromErrorCode(e_code , causes , solutions);
	if (causes.empty() || solutions.empty())
		return;

	vector<struct_cause>::iterator it = causes.begin();
	for ( ; it != causes.end() ; ++it)
	{
		afas_struct afas_info;
		afas_info.error_code = it->error_code;
		afas_info.cause  = it->cause_string;
		afas_info.level  = it->cause_level;
		string cause_id   = it->cause_id;
		vector<string> str_solution;
		vector<struct_solution>::iterator sit = solutions.begin();
		for ( ; sit != solutions.end(); ++sit)
		{
			if ( cause_id == sit->cause_id)
			{
				solution_group sgroup;
				sgroup.level = sit->solution_level;
				sgroup.str_solution = sit->solution_string;
				afas_info.solutions.push_back(sgroup);
			}	
		}

		if (!afas_info.solutions.empty())
		{
			afases.push_back(afas_info);
		}
	}
}

void afasDBMgr::setLangTableFromLangID( string lang_id )
{
	SQLiteWrapper::ResultTable retTable;
	bool ret=selectItemsFromTable(lang_id , "lang_group" , "lang_id" , retTable);
	if (ret)
	{	
		if (retTable.m_records.size() > 1)
		{
			SQLiteWrapper::ResultRecord record=retTable.m_records[1]; //get the first one
			m_currentLang = record.m_fields[0];
		}
	}

	//??? Only support english now.
	m_currentLang = "String_English";
}

bool afasDBMgr::is_has_afas( string e_code)
{
	vector<struct_cause> causes;
	getCauseFromErrorCode(e_code , causes);
	return !causes.empty();
}
