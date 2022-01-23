#include "machinestatusmgr.h"
#include "ErrorMgr.h"
#include "payOnline/networkmgr.h"
#include "IVersionConfig.h"
#include "animatesleep.h"
MachineStatusMgr::MachineStatusMgr(QObject *parent)
    : QObject(parent)
    , m_checkErrorTimer(NULL)
    , m_checkStatusTimer(NULL)
    , m_isNeedSendClearError(false)
{
    networkMgr& mgr = singleton<networkMgr>::instance();
    connect(&mgr , SIGNAL(sig_need_resend_errorinfo()) , this , SLOT(sendErrorToServer()));
}

MachineStatusMgr::~MachineStatusMgr()
{
    m_checkErrorTimer->stop();
}

void MachineStatusMgr::init()
{
    m_errorMap.clear();
    ErrorMgr &errorMgr = singleton<ErrorMgr>::instance();
    errorMgr.getAllErrAndWarning( m_errorMap );

    if(m_checkErrorTimer == NULL)
    {
        m_checkErrorTimer = new QTimer(this);
    }
    connect(m_checkErrorTimer , SIGNAL(timeout()) , this , SLOT(slot_checkError()));
    m_checkErrorTimer->start(2 * 1000 * 60);

    if(m_checkStatusTimer == NULL)
    {
        m_checkStatusTimer = new QTimer(this);
    }
    connect(m_checkStatusTimer , SIGNAL(timeout()) , this , SLOT(checkMachinePauseServer()));
    m_checkStatusTimer->start(3 * 1000 * 60);

}

//typedef map<ErrorKey_t, ErrorInfo_t> ErrorMgrMap;
//typedef pair<ErrorKey_t, ErrorInfo_t> ErrorPair_t;

//socket
//if (IVersionConfig::getInstance().getOnlineSupport())
//    IMachineInfoListener::getInstance().updateErrorInfo(make_pair(key,tempInfo),true);
void MachineStatusMgr::slot_checkError()
{
    ErrorMgr &errorMgr = singleton<ErrorMgr>::instance();
    ErrorMgrMap newErrorMap;
    errorMgr.getAllErrAndWarning( newErrorMap );

    bool isNewErrorChange = false;
    if(!m_errorMap.empty())
    {
        // need send clearError
        if(newErrorMap.empty())
        {
            m_isNeedSendClearError = true;
            sendMsgToClearError();
            m_errorMap.clear();
            m_isNeedSendClearError = false;
        }
        else
        {
            if(newErrorMap.size() != m_errorMap.size())
            {
                isNewErrorChange = true;
                m_errorMap.clear();
                m_errorMap = newErrorMap;
            }
            else
            {
                ErrorMgrMap::iterator it = newErrorMap.begin();
                for( ; it != newErrorMap.end(); ++it)
                {//add
                    if(m_errorMap.find(it->first) == m_errorMap.end())
                    {
                       m_errorMap.clear();
                       m_errorMap = newErrorMap;
                       isNewErrorChange = true;
                       break;
                   }
                }

                it = m_errorMap.begin();
                for( ; it != m_errorMap.end(); ++it)
                {//reduce
                    if(newErrorMap.find(it->first) == newErrorMap.end())
                    {
                        m_errorMap.clear();
                        m_errorMap = newErrorMap;
                        isNewErrorChange = true;
                        break;
                    }
                }
            }

            if(isNewErrorChange)
            {
                m_isNeedSendClearError = true;
                sendMsgToClearError();
                //m_errorMap.clear();
                m_isNeedSendClearError = false;

                ErrorMgrMap::iterator it = newErrorMap.begin();
                for( ; it != newErrorMap.end(); ++it)
                {
                    if (IVersionConfig::getInstance().getOnlineSupport())
                    {
                        singleton<networkMgr>::instance().sendErrorInfo(*it,true);
                        AnimateSleep::msleep(3000);
                    }
                }
                if (IVersionConfig::getInstance().getOnlineSupport())
                {
                    singleton<networkMgr>::instance().startErrorTimer();
                }

                isNewErrorChange = false;
            }
        }
    }
    else//old is empty
    {
        if(!newErrorMap.empty())//new is !empty
        {
            ErrorMgrMap::iterator it = newErrorMap.begin();
            for( ; it != newErrorMap.end(); ++it)
            {
                m_errorMap.insert(*it);
                if (IVersionConfig::getInstance().getOnlineSupport())
                {
                    singleton<networkMgr>::instance().sendErrorInfo(*it,true);
                    AnimateSleep::msleep(3000);
                }
            }
            if (IVersionConfig::getInstance().getOnlineSupport())
            {
                singleton<networkMgr>::instance().startErrorTimer();
            }
            m_isNeedSendClearError = false;
        }
    }
}

void MachineStatusMgr::sendMsgToClearError()
{
    singleton<networkMgr>::instance().sendErrorEmpty();
}

void MachineStatusMgr::sendErrorToServer()
{
    ErrorMgr &errorMgr = singleton<ErrorMgr>::instance();
    ErrorMgrMap newErrorMap;
    errorMgr.getAllErrAndWarning( newErrorMap );
    if(!newErrorMap.empty())//new is !empty
    {
        ErrorMgrMap::iterator it = newErrorMap.begin();
        for( ; it != newErrorMap.end(); ++it)
        {
            m_errorMap.insert(*it);
            if (IVersionConfig::getInstance().getOnlineSupport())
            {
                singleton<networkMgr>::instance().sendErrorInfo(*it,true);
                AnimateSleep::msleep(3000);
            }
        }
    }
    else
    {
        if (IVersionConfig::getInstance().getOnlineSupport())
        {
            singleton<networkMgr>::instance().stopErrorTimer();
        }
    }
}

void MachineStatusMgr::checkMachinePauseServer()
{
    bool b = true;
    ErrorMgr &errorMgr = singleton<ErrorMgr>::instance();
    if(errorMgr.hasFatalError())
        b= false;

    networkMgr::getInstance().setMachineStaus(b);
}

void MachineStatusMgr::clearOlderrorMap()
{
    if(!m_errorMap.empty())
    {
        m_errorMap.clear();
    }
}
