#ifndef _IERRORMGR_H_
#define _IERRORMGR_H_

#include "error_mgr_def.h"

#include "adm_err.h"
#include "sys_err.h"
#include "paymenterror.h"
#include "stat_warning.h"

class IErrorMgrListener;

class IErrorMgr
{
public:
	static IErrorMgr& getInstance();

public:
	virtual ~IErrorMgr() {}

public:
	virtual bool init()=0;
	virtual IErrorMgrListener*  setListener(IErrorMgrListener *pListener)=0; 

public:
	virtual bool hasFatalError() const=0;
	virtual bool hasWarning() const=0;

	virtual bool hasPersistentError() const=0;
	virtual bool hasPersistentWarning() const=0;

	virtual void getAllErrAndWarning(ErrorMgrMap &all) const=0;
	virtual void getAllErrors(ErrorMgrMap &allErrors) const=0;
	virtual void getAllFatalErrors(ErrorMgrMap &allFatalErrors) const=0;

	virtual void getAllWarnings(ErrorMgrMap &allWarnings) const=0;

	virtual void clear()=0;
	virtual void clearAllError()=0;
	virtual void clearAllWarning()=0;

public:  //layer 3(business layer)
	virtual void addAdmError(EAdmErrorCode err)=0;
	virtual void removeAdmError(EAdmErrorCode err)=0;

	virtual void addSysError(ESysErrorCode err)=0;
	virtual void removeSysError(ESysErrorCode err)=0;

	virtual void addBoardError(const string &machineName, unsigned char boardId)=0;
	virtual void removeBoardError(const string &machineName, unsigned char boardId)=0;

	virtual void addComponentError(const string &machineName, unsigned char boardId, 
		const string& errorCode, unsigned short componentId, 
		bool isFatal, bool isPersistent = false	)=0;
	virtual void removeComponentError(const string &machineName, unsigned char boardId, 
		const string& errorCode)=0;

	virtual void addPaymentError(ErrorPaymentType_t paymentType, unsigned char errIndex, bool isFatal, bool isPersistent)=0;
	virtual void removePaymentError(ErrorPaymentType_t paymentType, unsigned char errIndex)=0;

	virtual void addGeneralEvaError(const string &id, bool isFatal, bool isPersistent)=0;
	virtual void removeGeneralEvaError(const string &id)=0;

	virtual void addStatWarning(const string &machineName, EStatWarning warning, bool isFatal)=0;
	virtual void removeStatWarning(const string &machineName, EStatWarning warning)=0;

	//gfv_sv machine
	virtual void addGfvSvMachineError(const string &machineName, const string &id, bool isFatal)=0;
	virtual void removeGfvSvMachineError(const string &machineName, const string &id)=0;

	//psl nsl machine
	virtual void addSLMachineError(const string &machineName , const string &id,bool isFatal, bool isPersistent=false)=0;
	virtual void removeSLMachineError(const string &machineName, const string &id)=0;

};

#endif
