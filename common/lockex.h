#ifndef _LOCKEX_H_
#define _LOCKEX_H_

#include "lock.h"

class LockEx
{
public:
     LockEx(const char* name=0);
	~LockEx();
	void lock();
	void unlock();
private:
	LOCK m_lock;
};

#endif
