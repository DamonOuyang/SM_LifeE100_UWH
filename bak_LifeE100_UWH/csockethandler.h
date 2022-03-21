#ifndef CSOCKETHANDLER_H
#define CSOCKETHANDLER_H
#include "csocket.h"
#include <list>

class CSocket;
class CSocketHandler
{
public:
    CSocketHandler();
    int  GetCount();
    size_t MaxCount() {return FD_SETSIZE;}
    int  Select(long sec,long usec);
    void AddSocket(CSocket* pNewSkt);
    void DelSocket(CSocket* pDelSkt);
    void SetSelect(CSocket *p,bool bRead,bool bWrite);
private:
    SOCKET m_maxsock; ///< Highest file descriptor + 1 in active sockets list
    fd_set m_rfds; ///< file descriptor set monitored for read events
    fd_set m_wfds; ///< file descriptor set monitored for write events
    fd_set m_efds; ///< file descriptor set monitored for exceptions
    std::list<CSocket*> m_sockets;
    int  Sockets_Select(struct timeval *tsel);
    void RebuildFdset();
    bool  m_bDelFlag;
};

#endif // CSOCKETHANDLER_H
