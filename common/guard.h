#ifndef _GUARD_H_
#define _GUARD_H_

class LockEx;
class Guard
{
public:
	Guard(LockEx& l);
	~Guard();

private:
	Guard(const Guard&);
	Guard& operator=(const Guard&);

	LockEx& m_lock;
};

#endif
