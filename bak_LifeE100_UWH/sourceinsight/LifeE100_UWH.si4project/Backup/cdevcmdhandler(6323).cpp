#include "includes.h"
#include "cdevcmdhandler.h"
#include "cbasicdevice.h"
#include "cworkthread.h"
#include "cuartsocket.h"

CDevCmdHandler::CDevCmdHandler()
{

}
CDevCmdHandler::~CDevCmdHandler()
{
    DeleteAllDevs();
}

void CDevCmdHandler::OnProcTask(void)
{
    int lIndex;
    CBasicDevice*  pSubDev;
    QList<CBasicDevice*>pListDevs = m_mapSubDevs.values(); //遍历QMap
    for(lIndex = 0; lIndex < pListDevs.count(); lIndex++)
    {
        pSubDev = (CBasicDevice*)pListDevs.at(lIndex);
        if(NULL!=pSubDev&&true==pSubDev->IsEnabled())
        {
            pSubDev->ProcTask();
			
			//printf("------------------------ID:%d---------------\r\n",pSubDev->GetDevID());
        }
		//printf("------------------------lIndex:%d---------------\r\n",lIndex);
    }
}


void CDevCmdHandler::OnMsTimer(UINT32 unMsCount)
{
    int lIndex;
    CBasicDevice*  pSubDev;
    QList<CBasicDevice*>pListDevs = m_mapSubDevs.values(); //遍历QMap
    for ( lIndex = 0; lIndex < pListDevs.count(); lIndex++)
    {
        pSubDev = (CBasicDevice*)pListDevs.at(lIndex);
        if(NULL!=pSubDev&&true==pSubDev->IsEnabled())
        {
            pSubDev->OnMsTimer(unMsCount);
        }
    }
}

void CDevCmdHandler::AddSubDevice(CBasicDevice* pSubDev)
{
    m_mapSubDevs.insert(pSubDev->GetDevID(),pSubDev);
}

void CDevCmdHandler::DeleteAllDevs(void)
{
    long lIndex;
    CBasicDevice*  pSubDev;
    QList<CBasicDevice*>pListDevs = m_mapSubDevs.values(); //遍历QMap
    for ( lIndex = 0; lIndex < pListDevs.count(); lIndex++)
    {
        pSubDev = (CBasicDevice*)pListDevs.at(lIndex);
        if(NULL!=pSubDev)
        {
            delete pSubDev;
        }
    }
    m_mapSubDevs.clear();
}

bool CDevCmdHandler::DataParserByDev(int unRcvSoc, UINT32 unDevID,UINT32 unCmdID,BYTE* pDataBuf,UINT32 unDataLen)
{
    CBasicDevice* pSubDev;
	
    pSubDev = m_mapSubDevs.value(unDevID);	
    if(NULL != pSubDev && unRcvSoc == pSubDev->GetSubDevSocket())
    {
        pSubDev->DataParser(pDataBuf,unCmdID,unDataLen);
        return true;
    }
    return false;
}
void CDevCmdHandler::OnCmdTimeout(UINT32 unDevID)
{
    CBasicDevice* pSubDev;
    pSubDev = m_mapSubDevs.value(unDevID);
    if(NULL != pSubDev)
    {
        pSubDev->OnCmdTimeOut();
    }
}
