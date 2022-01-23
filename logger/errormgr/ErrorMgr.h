#ifndef _ERROR_MGR_H_
#define _ERROR_MGR_H_

#include "singleton.h"
#include "IErrorMgr.h"

class ErrorMgr : public IErrorMgr
{
	friend class singleton<ErrorMgr>;

public:
	virtual bool init();
	virtual IErrorMgrListener*  setListener(IErrorMgrListener *pListener); 

public:
	virtual bool hasFatalError() const;
	virtual bool hasWarning() const;

	virtual bool hasPersistentError() const;
	virtual bool hasPersistentWarning() const;

	virtual void getAllErrAndWarning(ErrorMgrMap &all) const;
	virtual void getAllErrors(ErrorMgrMap &allErrors) const;
	virtual void getAllFatalErrors(ErrorMgrMap &allFatalErrors) const;

	virtual void getAllWarnings(ErrorMgrMap &allWarnings) const;

	virtual void clear();
	virtual void clearAllError();
	virtual void clearAllWarning();

public:  //layer 3(business layer)
	virtual void addAdmError(EAdmErrorCode err);
	virtual void removeAdmError(EAdmErrorCode err);

	virtual void addSysError(ESysErrorCode err);
	virtual void removeSysError(ESysErrorCode err);

	virtual void addBoardError(const string &machineName, unsigned char boardId);
	virtual void removeBoardError(const string &machineName, unsigned char boardId);

	virtual void addComponentError(const string &machineName, unsigned char boardId, 
		const string& errorCode, unsigned short componentId, 
		bool isFatal, bool isPersistent = false	);
	virtual void removeComponentError(const string &machineName, unsigned char boardId, 
		const string& errorCode);

	virtual void addPaymentError(ErrorPaymentType_t paymentType, unsigned char errIndex, bool isFatal, bool isPersistent);
	virtual void removePaymentError(ErrorPaymentType_t paymentType, unsigned char errIndex);

	virtual void addGeneralEvaError(const string &id, bool isFatal, bool isPersistent);
	virtual void removeGeneralEvaError(const string &id);

	virtual void addStatWarning(const string &machineName, EStatWarning warning, bool isFatal);
	virtual void removeStatWarning(const string &machineName, EStatWarning warning);

	//gfv_sv machine
	virtual void addGfvSvMachineError(const string &machineName, const string &id, bool isFatal);
	virtual void removeGfvSvMachineError(const string &machineName, const string &id);

	//psl nsl machine
	virtual void addSLMachineError(const string &machineName , const string &id,bool isFatal, bool isPersistent=false);
	virtual void removeSLMachineError(const string &machineName, const string &id);

private:  //layer 2

	void addBoardError(const string &machineName, BYTE boardId, const string &id,
		               EErrorType type, bool isFatal, bool isPersistent);
	void removeBoardError(const string &machineName, BYTE boardId,const string &id);

	void addMachineError(const string &machineName, const string &id,
		               EErrorType type, bool isFatal, bool isPersistent);
	void removeMachineError(const string &machineName, const string &id);


	void addGeneralError(const string &id, EErrorType type, bool isFatal, bool isPersistent);
	void removeGeneralError(const string &id);

private: //layer 1
	void addError(const ErrorKey_t &key, const ErrorInfo_t &info);
	void removeError(const ErrorKey_t &key);

private:
	void getAllErrorsByType(EErrorType type, ErrorMgrMap &infos) const;
	bool hasSystemFatalError() const;
	bool hasMachineFatalError(const string &machineName) const;

private:
	static void getErrorMgrDateTime(string &dateTime);
	static bool hasPersistent(const ErrorMgrMap &all);

private:
	ErrorMgr();
	~ErrorMgr();

private:
	ErrorMgrMap m_infos;

private:
	IErrorMgrListener *m_pListener;

private:
	ErrorMgr(const ErrorMgr &rhs);
	ErrorMgr& operator=(const ErrorMgr &rhs);
};

#endif
