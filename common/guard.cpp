#include "guard.h"
#include "lockex.h"

Guard::Guard(LockEx& l):m_lock(l)
{
	m_lock.lock();
}

Guard::~Guard()
{
	m_lock.unlock();
}
