#ifndef CDEVCMDHANDLER_H
#define CDEVCMDHANDLER_H

#include <QMap>

class CBasicDevice;
class CDevCmdHandler
{
public:
    CDevCmdHandler();
    virtual ~CDevCmdHandler();
    void OnProcTask(void);
    void OnMsTimer(UINT32 unMsCount);
    void AddSubDevice(CBasicDevice* pSubDev);
    void DeleteAllDevs(void);
    bool DataParserByDev(int unRcvSoc, UINT32 unDevID,UINT32 unCmdID,BYTE* pDataBuf,UINT32 unDataLen);
    void OnCmdTimeout(UINT32 unDevID);
private:
    QMap<UINT32,CBasicDevice*>m_mapSubDevs;
};

#endif // CDEVCMDHANDLER_H
