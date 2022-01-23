#pragma once
#include <string>
using namespace std;

typedef struct  
{
	string error_code;
	string cause_id;
	int    cause_level;
	string cause_string_nr;
	string cause_options;
	string cause_string;
}struct_cause;

typedef enum
{
	CAUSE_ERROR = 0,
	CAUSE_ID,
	CAUSE_LEVEL,
	CAUSE_STRING_NR,
	CAUSE_OPTIONS,
};

typedef enum
{
	STRING_ID = 0,
	STRING_TEXT,
};

typedef struct
{
	string error_code;
	string cause_id;
	string solution_index;
	int    solution_level;
	string solution_string_nr;
	string solution_options;
	string solution_string;
}struct_solution;

typedef enum
{
	SOLUTION_ERROR,
	SOLUTION_CAUSE,
	SOLUTION_SOLUTION,
	SOLUTION_LEVEL,
	SOLUTION_STRING_NR,
	SOLUTION_OPTIONS,
};

typedef struct 
{
	int level;
	string str_solution;
}solution_group;

typedef struct  
{
	string error_code;
	int    level;
	string cause;
	vector<solution_group> solutions;
}afas_struct;
