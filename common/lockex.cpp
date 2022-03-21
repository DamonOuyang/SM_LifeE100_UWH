#include "lockex.h"

LockEx::LockEx(const char* name)
{
	m_lock=lock_alloc(name);
}

LockEx::~LockEx()
{
	lock_free(m_lock);
}

void LockEx::lock()
{
	::lock(m_lock);
}

void LockEx::unlock()
{
	::unlock(m_lock);
}
