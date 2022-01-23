#include "ErrorMgr.h"

#include "ErrorMgrDB.h"
#include "ISysLogger.h"
#include "isupervisorstatemgr.h"
#include "supervisorevents.h"

#include "ErrorMappingFactory.h"
#include "imachinemgr.h"
#include "MachineHelper.h"

#include "IErrorMgrListener.h"
#include "SysTime.h"

#include "LangMgr.h"
#include "ISysConfig.h"

#include "event_mgr.h"

#include "CoffeeMachineConfig.h"

#include "error_id_def.h"

#include <sstream>
#include <iomanip>
#include <cassert>
//#include "serverMsg/IMachineInfoListener.h"
#include "IVersionConfig.h"
using namespace std;

static const BYTE s_defaultValue=0xff;

IErrorMgr& IErrorMgr::getInstance()
{
    return singleton<ErrorMgr>::instance();
}

ErrorMgr::ErrorMgr()
{
    m_pListener=NULL;
}

ErrorMgr::~ErrorMgr()
{
}

bool ErrorMgr::init()
{
    ErrorMgrDB &db=singleton<ErrorMgrDB>::instance();
    bool ret=db.init(m_infos);
    return ret;
}

IErrorMgrListener* ErrorMgr::setListener(IErrorMgrListener *pListener)
{
    IErrorMgrListener* pOldListener = m_pListener;
    m_pListener=pListener;
    return pOldListener;
}

void ErrorMgr::addError(const ErrorKey_t &key, const ErrorInfo_t &info)
{
    singleton<EventMgr>::instance().malfunctionBegin(key.machineName,key.id);

    //return;
    ErrorMgrMap::const_iterator cit=m_infos.find(key);
    if (cit==m_infos.end())
    {
        ErrorInfo_t tempInfo(info);
        string &dateTime=tempInfo.dbInfo.dateTime;
        getErrorMgrDateTime(dateTime);

        if (info.isPersistent)
        {
            ErrorMgrDB &db=singleton<ErrorMgrDB>::instance();
            db.insert(key,tempInfo.dbInfo);
        }
        m_infos.insert(make_pair(key,tempInfo));

        LangMgr::LanguageType lang = singleton<ISysConfig>::getInstance().getCurrentlang();
        std::string text;
        singleton<LangMgr>::instance().getText( key.id, text ,lang );
        ostringstream s;
        s<<"("<<key.id<<")"<<text;
        ISysLogger::getInstance().addLog( s.str() );

        if (hasFatalError())
        {
            ISupervisorStateMgr::getInstance().postEvent(EvFatalError());
        }
    }
    return;
}

void ErrorMgr::removeError(const ErrorKey_t &key)
{
    singleton<EventMgr>::instance().malfunctionEnd(key.machineName,key.id);

    if (key.id==g_purificationErrorId)
    {
        singleton<CoffeeMachineConfig>::instance().setPurificationSafe(true);
    }

    bool oldHasFatalError=hasFatalError();
    ErrorMgrMap::const_iterator cit=m_infos.find(key);
    if (cit!=m_infos.end())
    {
        if ((*cit).second.isPersistent)
        {
            ErrorMgrDB &db=singleton<ErrorMgrDB>::instance();
            db.remove(key);
        }
        m_infos.erase(key);

        if (m_pListener!=NULL)
        {
            m_pListener->onErrorUpdate();
        }

        if (oldHasFatalError && !hasFatalError())
        {
            ISupervisorStateMgr::getInstance().postEvent(EvFatalErrorSolved());
        }
    }

    return;
}

void ErrorMgr::getErrorMgrDateTime(string &dateTime)
{
    string strFormat="%Y%m%d %H%M%S";
    dateTime=SystemTime::getLocalTime().format(strFormat.c_str());
    return;
}

void ErrorMgr::clear()
{
    ErrorMgrMap alls;
    getAllErrAndWarning(alls);
    for (ErrorMgrMap::const_iterator cit=alls.begin(); cit!=alls.end(); ++cit)
    {
        if ((*cit).second.isPersistent)
        {
            removeError((*cit).first);
        }
    }
    return;
}

void ErrorMgr::clearAllError()
{
    ErrorMgrMap allErrors;
    getAllErrors(allErrors);
    for (ErrorMgrMap::const_iterator cit=allErrors.begin(); cit!=allErrors.end(); ++cit)
    {
        if ((*cit).second.isPersistent)
        {
            removeError((*cit).first);
        }
    }
    return;
}

void ErrorMgr::clearAllWarning()
{
    ErrorMgrMap allWarnings;
    getAllWarnings(allWarnings);
    for (ErrorMgrMap::const_iterator cit=allWarnings.begin(); cit!=allWarnings.end(); ++cit)
    {
        if ((*cit).second.isPersistent)
        {
            removeError((*cit).first);
        }
    }
    return;
}

bool ErrorMgr::hasFatalError() const
{
    bool ret;

    //check system fatal error
    ret=hasSystemFatalError();
    if (ret)
    {
        return true;
    }

    //check all machines fatal error
    map<string,Machine*> machines;
    machines=IMachineMgr::getInstance().getMachines();
    if (machines.empty())
    {
        return false;
    }
    for (map<string,Machine*>::const_iterator cit=machines.begin(); cit!=machines.end(); ++cit)
    {
        if (!hasMachineFatalError((*cit).first))
        {
            //there will be one machine has no fatal error.
            return false;
        }
    }

    //all machines will have fatal error.
    return true;
}

bool ErrorMgr::hasSystemFatalError() const
{
    return hasMachineFatalError("");
}

bool ErrorMgr::hasPersistent(const ErrorMgrMap &all)
{
    string machineName=MachineHelper::getMachineName();
    for (ErrorMgrMap::const_iterator cit=all.begin(); cit!=all.end(); ++cit)
    {
        if ((*cit).second.isPersistent)
        {
            const string &name=(*cit).first.machineName;
            if (""==name || machineName==name)
            {
                return true;
            }
        }
    }
    return false;
}

bool ErrorMgr::hasPersistentError() const
{
    ErrorMgrMap allErrors;
    getAllErrors(allErrors);
    return hasPersistent(allErrors);
}

bool ErrorMgr::hasPersistentWarning() const
{
    ErrorMgrMap allWarnings;
    getAllWarnings(allWarnings);
    return hasPersistent(allWarnings);
}

bool ErrorMgr::hasMachineFatalError(const string &machineName) const
{
    for (ErrorMgrMap::const_iterator cit=m_infos.begin(); cit!=m_infos.end(); ++cit)
    {
        const EErrorType &type=(*cit).second.dbInfo.type;
        const bool &isFatal=(*cit).second.dbInfo.isFatal;
        if ((machineName==(*cit).first.machineName) && (eError==type) && isFatal)
        {
            return true;
        }
    }
    return false;
}

bool ErrorMgr::hasWarning() const
{
    return !m_infos.empty();
}



void ErrorMgr::getAllErrorsByType(EErrorType type, ErrorMgrMap &infos) const
{
    infos.clear();
    for (ErrorMgrMap::const_iterator cit=m_infos.begin(); cit!=m_infos.end(); ++cit)
    {
        if (type==(*cit).second.dbInfo.type)
        {
            infos.insert(make_pair((*cit).first,(*cit).second));
        }
    }
    return;
}

void ErrorMgr::getAllErrAndWarning(ErrorMgrMap &all) const
{
    all.clear();
    for (ErrorMgrMap::const_iterator cit=m_infos.begin(); cit!=m_infos.end(); ++cit)
    {
        all.insert(make_pair((*cit).first,(*cit).second));
    }
    return;
}

void ErrorMgr::getAllErrors(ErrorMgrMap &allErrors) const
{
    getAllErrorsByType(eError,allErrors);
    return;
}

void ErrorMgr::getAllWarnings(ErrorMgrMap &allWarnings) const
{
    getAllErrorsByType(eWarning,allWarnings);
    return;
}

void ErrorMgr::getAllFatalErrors(ErrorMgrMap &allFatalErrors) const
{
    allFatalErrors.clear();

    ErrorMgrMap allErrors;
    getAllErrors(allErrors);
    for (ErrorMgrMap::const_iterator cit=allErrors.begin(); cit!=allErrors.end(); ++cit)
    {
        if ((*cit).second.dbInfo.isFatal)
        {
            allFatalErrors.insert(make_pair((*cit).first,(*cit).second));
        }
    }

    return;
}

void ErrorMgr::addBoardError(const string &machineName, BYTE boardId, const string &id,
                             EErrorType type, bool isFatal, bool isPersistent)
{
    ErrorKey_t key;
    key.machineName=machineName;
    key.boardId=boardId;
    key.id=id;

    ErrorInfo_t info;
    info.isPersistent=isPersistent;
    ErrorDBInfo_t &dbInfo=info.dbInfo;
    dbInfo.type=type;
    dbInfo.isFatal=isFatal;
    dbInfo.compIndex=s_defaultValue;

    addError(key,info);
    return;
}

void ErrorMgr::removeBoardError(const string &machineName, BYTE boardId,const string &id)
{
    ErrorKey_t key;
    key.machineName=machineName;
    key.boardId=boardId;
    key.id=id;

    removeError(key);
    return;
}

void ErrorMgr::addMachineError(const string &machineName, const string &id,
                               EErrorType type, bool isFatal, bool isPersistent)
{
    ErrorKey_t key;
    key.machineName=machineName;
    key.boardId=s_defaultValue;
    key.id=id;

    ErrorInfo_t info;
    info.isPersistent=isPersistent;
    ErrorDBInfo_t &dbInfo=info.dbInfo;
    dbInfo.type=type;
    dbInfo.isFatal=isFatal;
    dbInfo.compIndex=s_defaultValue;

    addError(key,info);
    return;
}

void ErrorMgr::removeMachineError(const string &machineName, const string &id)
{
    ErrorKey_t key;
    key.machineName=machineName;
    key.boardId=s_defaultValue;
    key.id=id;

    removeError(key);
    return;
}

void ErrorMgr::addGeneralError(const string &id, EErrorType type, bool isFatal, bool isPersistent)
{
    ErrorKey_t key;
    key.machineName="";
    key.boardId=s_defaultValue;
    key.id=id;

    ErrorInfo_t info;
    info.isPersistent=isPersistent;
    ErrorDBInfo_t &dbInfo=info.dbInfo;
    dbInfo.type=type;
    dbInfo.isFatal=isFatal;
    dbInfo.compIndex=s_defaultValue;

    addError(key,info);
    return;
}

void ErrorMgr::removeGeneralError(const string &id)
{
    ErrorKey_t key;
    key.machineName="";
    key.boardId=s_defaultValue;
    key.id=id;

    removeError(key);
    return;
}

void ErrorMgr::addAdmError(EAdmErrorCode err)
{
    const EErrorType type=eError;
    const bool isFatal=true;
    const bool isPersistent=false;
    string id=ErrorMappingFactory::mappingAdmErrorCode(err);
    addGeneralError(id,type,isFatal,isPersistent);
    return;
}

void ErrorMgr::removeAdmError(EAdmErrorCode err)
{
    string id=ErrorMappingFactory::mappingAdmErrorCode(err);
    removeGeneralError(id);
    return;
}

void ErrorMgr::addSysError(ESysErrorCode err)
{
    const EErrorType type=eError;
    const bool isFatal=true;
    const bool isPersistent=false;
    string id=ErrorMappingFactory::mappingSysErrorCode(err);
    addGeneralError(id,type,isFatal,isPersistent);
    return;
}

void ErrorMgr::removeSysError(ESysErrorCode err)
{
    string id=ErrorMappingFactory::mappingSysErrorCode(err);
    removeGeneralError(id);
    return;
}

void ErrorMgr::addBoardError(const string &machineName, unsigned char boardId)
{
    const EErrorType type=eError;
    const bool isFatal=true;
    const bool isPersistent=false;
    string id=ErrorMappingFactory::mappingBoardErrorCode(boardId);
    addBoardError(machineName,boardId,id,type,isFatal,isPersistent);
    return;
}

void ErrorMgr::removeBoardError(const string &machineName, unsigned char boardId)
{
    string id=ErrorMappingFactory::mappingBoardErrorCode(boardId);
    removeBoardError(machineName,boardId,id);
    return;
}

void ErrorMgr::addComponentError(const string &machineName, unsigned char boardId,
                                 const string& errorCode, unsigned short componentId,
                                 bool isFatal, bool isPersistent )
{
    ErrorKey_t key;
    key.machineName=machineName;
    key.boardId=boardId;
    key.id=errorCode;

    ErrorInfo_t info;
    info.isPersistent=isPersistent;
    info.dbInfo.compIndex=componentId;
    //datetime is filled in addError()
    info.dbInfo.isFatal=isFatal;
    info.dbInfo.type=eError;

    //no mapping, errorCode is EVA event Code
    addError(key,info);
    return;
}

void ErrorMgr::removeComponentError(const string &machineName, unsigned char boardId,
                          const string& errorCode)
{
    ErrorKey_t key;
    key.machineName=machineName;
    key.boardId=boardId;
    key.id=errorCode;

    removeError(key);
    return;
}

void ErrorMgr::addPaymentError(ErrorPaymentType_t paymentType, unsigned char errIndex, bool isFatal, bool isPersistent)
{
    if(!isFatal)
        return;
    string id=ErrorMappingFactory::mappingPaymentErrorCode(paymentType, errIndex);
    const EErrorType errorType=eError;
    addGeneralError(id,errorType,isFatal,isPersistent);
    return;
}

void ErrorMgr::removePaymentError(ErrorPaymentType_t paymentType, unsigned char errIndex)
{
    //return;//???
    string id=ErrorMappingFactory::mappingPaymentErrorCode(paymentType, errIndex);
    removeGeneralError(id);
    return;
}

void ErrorMgr::addGeneralEvaError(const string &id, bool isFatal, bool isPersistent)
{
    const EErrorType errorType=eError;
    addGeneralError(id,errorType,isFatal,isPersistent);
    return;
}

void ErrorMgr::removeGeneralEvaError(const string &id)
{
    removeGeneralError(id);
    return;
}

void ErrorMgr::addStatWarning(const string &machineName, EStatWarning warning, bool isFatal)
{
    string id=ErrorMappingFactory::mappingStatWarning(warning);
    const EErrorType type=eWarning;
    const bool isPersistent=true;
    addMachineError(machineName,id,type,isFatal,isPersistent);
    return;
}

void ErrorMgr::removeStatWarning(const string &machineName, EStatWarning warning)
{
    string id=ErrorMappingFactory::mappingStatWarning(warning);
    removeMachineError(machineName,id);
    return;
}

void ErrorMgr::addGfvSvMachineError(const string &machineName, const string &id, bool isFatal)
{
    addMachineError(machineName,id,eError,isFatal,false);
    return;
}

void ErrorMgr::removeGfvSvMachineError(const string &machineName, const string &id)
{
    removeMachineError(machineName,id);
    return;
}

void ErrorMgr::addSLMachineError(const string &machineName , const string &id,bool isFatal, bool isPersistent)
{
    addMachineError(machineName,id,eError,isFatal,isPersistent);
    return;
}

void ErrorMgr::removeSLMachineError(const string &machineName, const string &id)
{
    removeMachineError(machineName,id);
    return;
}
