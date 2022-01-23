#ifndef _SYS_LOGGER_H_
#define _SYS_LOGGER_H_

#include "ISysLogger.h"

#include "singleton.h"
#include "lockex.h"

#include <boost/noncopyable.hpp>

class SysLogger : public ISysLogger, boost::noncopyable
{
	friend class singleton<SysLogger>;

public: //implement ISysLogger interface
	virtual void getAllLogs(vector<SysLogInfo> &logs);
	virtual void clear();
	virtual void addLog(const wstring &logText);
	virtual void addLog(const string &logText);

private:
	SysLogger();
	~SysLogger();

	void init();

private:
	LockEx m_lock;
};

#endif
