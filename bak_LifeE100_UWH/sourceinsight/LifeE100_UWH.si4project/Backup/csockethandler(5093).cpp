#include "CSocketHandler.h"
#include "CSocket.h"

CSocketHandler::CSocketHandler()
{
    m_maxsock = 0;
    FD_ZERO(&m_rfds);
    FD_ZERO(&m_wfds);
    FD_ZERO(&m_efds);
}

int CSocketHandler::GetCount()
{
    return m_sockets.size();
}

int CSocketHandler::Select(long sec,long usec)
{
    struct timeval tv;
    tv.tv_sec  = sec;
    tv.tv_usec = usec;
    return Sockets_Select(&tv);
}

void CSocketHandler::AddSocket(CSocket* pNewSkt)
{
    CSocket* pSkt;
    std::list<CSocket*>::iterator it;
    SetSelect(pNewSkt,true,false);
    for(it = m_sockets.begin(); it != m_sockets.end(); ++it)
    {
        pSkt = *it;
        if (pSkt==pNewSkt)
        {
            //已经存在
            return;
        }
    }
    m_sockets.push_back(pNewSkt);
}

void CSocketHandler::SetSelect(CSocket *p,bool bRead,bool bWrite)
{
    SOCKET s = p ->GetSocket();
    if (s >= 0)
    {
        bool bException = true;
        if (bRead)
        {
            if (!FD_ISSET(s, &m_rfds))
            {
                FD_SET(s, &m_rfds);
            }
        }
        else
        {
            FD_CLR(s, &m_rfds);
        }
        if (bWrite)
        {
            if (!FD_ISSET(s, &m_wfds))
            {
                FD_SET(s, &m_wfds);
            }
        }
        else
        {
            FD_CLR(s, &m_wfds);
        }
        if (bException)
        {
            if (!FD_ISSET(s, &m_efds))
            {
                FD_SET(s, &m_efds);
            }
        }
        else
        {
            FD_CLR(s, &m_efds);
        }
    }
    m_maxsock = (s > m_maxsock) ? s : m_maxsock;
}

int CSocketHandler::Sockets_Select(struct timeval *tsel)
{
    fd_set rfds = m_rfds;
    fd_set wfds = m_wfds;
    fd_set efds = m_efds;
    int nReturn = select((int)(m_maxsock+1),&rfds,&wfds,&efds,tsel);
    if (-1==nReturn) // error on select
    {
        int err = Errno;
        switch (err)
        {
        case EBADF:
            RebuildFdset();
            break;
        case EINTR:
            break;
        case EINVAL:
            break;
        case ENOMEM:
            break;
        }
        printf("error on select(): %d %s\n", Errno, StrError(err));
    }
    else if (0==nReturn)
    {
        // timeout
        std::list<CSocket*>::iterator it;
        CSocket* pSkt;
        for (it = m_sockets.begin(); it != m_sockets.end(); ++it)
        {
            pSkt = *it;
            pSkt->OnSelectTimeout();
        }
    }
    else if (nReturn > 0)
    {
        std::list<CSocket*>::iterator it;
        CSocket* pSkt;
        m_bDelFlag = false;
        it = m_sockets.begin();
        while(it != m_sockets.end())
        {
            pSkt = *it;
            if (FD_ISSET(pSkt->GetSocket(), &rfds))
            {
                pSkt -> OnRead();
            }
            if (FD_ISSET(pSkt->GetSocket(), &wfds))
            {
                pSkt -> OnWrite();
            }
            if (FD_ISSET(pSkt->GetSocket(), &efds))
            {
                pSkt -> OnException();
            }
            if(false==m_bDelFlag)
            {
                ++it;
            }
            else
            {
                //事件触发后，有对象被清除
                it = m_sockets.begin();
                m_bDelFlag = false;
            }
        }
    }
    return nReturn;
}

void CSocketHandler::DelSocket(CSocket* pDelSkt)
{
    CSocket *pSkt;
    std::list<CSocket*>::iterator it;
    SetSelect(pDelSkt,false,false);
    for(it = m_sockets.begin(); it != m_sockets.end(); ++it)
    {
        pSkt = *it;
        if (pSkt==pDelSkt)
        {
            printf("Remove Select Socket\r\n");
            m_sockets.erase(it);
            m_bDelFlag = true;
            break;
        }
    }
    if(true==m_bDelFlag)
    {
        RebuildFdset();
    }
}

void CSocketHandler::RebuildFdset()
{
    std::list<CSocket*>::iterator it;
    CSocket *pSkt;
    fd_set rfds;
    fd_set wfds;
    fd_set efds;
    // rebuild fd_set's from active sockets list (m_sockets) here
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_ZERO(&efds);
    for (it = m_sockets.begin(); it != m_sockets.end(); ++it)
    {
        pSkt = *it;
        if(INVALID_SOCKET!=pSkt-> GetSocket())
        {
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(pSkt->GetSocket(),&fds);
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            int n = select((int)pSkt->GetSocket() + 1, &fds, NULL, NULL, &tv);
            if (n == -1 && Errno == EBADF)
            {
                printf("Bad fd in fd_set(2)");
                m_sockets.erase(it);
            }
            else
            {
                if (FD_ISSET(pSkt->GetSocket(), &m_rfds))
                    FD_SET(pSkt->GetSocket(), &rfds);
                if (FD_ISSET(pSkt->GetSocket(), &m_wfds))
                    FD_SET(pSkt->GetSocket(), &wfds);
                if (FD_ISSET(pSkt->GetSocket(), &m_efds))
                    FD_SET(pSkt->GetSocket(), &efds);
            }
        }
        else
        {
            // %! mismatch
            m_sockets.erase(it);
        }
    }
    m_rfds = rfds;
    m_wfds = wfds;
    m_efds = efds;
}
