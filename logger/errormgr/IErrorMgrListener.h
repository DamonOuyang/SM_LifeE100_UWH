#ifndef _IERROR_MGR_LISTENER_H_
#define _IERROR_MGR_LISTENER_H_

class IErrorMgrListener
{
public:
	virtual void onErrorUpdate()=0;

public:
	virtual ~IErrorMgrListener()=0;
};

inline IErrorMgrListener::~IErrorMgrListener()
{

}

#endif
