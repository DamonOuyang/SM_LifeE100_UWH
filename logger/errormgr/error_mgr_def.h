#ifndef _ERROR_MGR_DEF_H_
#define _ERROR_MGR_DEF_H_

#include "common.h"

#include <string>
#include <map>
using namespace std;

typedef struct  
{
	string machineName;
	BYTE boardId;
	string id;
} ErrorKey_t;

//Error type
typedef enum 
{
	eError=0,
	eWarning,
} EErrorType;

typedef struct 
{
	EErrorType type;
	bool isFatal;
	unsigned short compIndex;//component id
	string dateTime;
} ErrorDBInfo_t;

typedef struct  
{
	ErrorDBInfo_t dbInfo;
	bool isPersistent;
} ErrorInfo_t;

inline bool operator<(const ErrorKey_t &lhs, const ErrorKey_t &rhs)
{
	if (lhs.machineName!=rhs.machineName)
	{
		return lhs.machineName<rhs.machineName;
	}

	if (lhs.boardId!=rhs.boardId)
	{
		return lhs.boardId<rhs.boardId;
	}

	if (lhs.id!=rhs.id)
	{
		return lhs.id<rhs.id;
	}

	return false;
}

typedef map<ErrorKey_t, ErrorInfo_t> ErrorMgrMap;
typedef pair<ErrorKey_t, ErrorInfo_t> ErrorPair_t;

#endif
