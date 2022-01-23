#include "CBridge.h"
#include "CPort.h"
#include "cpordlogical.h".h"

CBridge::CBridge(QObject *parent) : QObject(parent)
{
    m_pCpordLogical  = new CPordLogical(this);
    m_pPort = new CPort();//这里的实例化得注意了
   //通信层与业务层的通信
    connect(m_pPort,SIGNAL(sig_upward_msg(QString)),m_pCpordLogical,SIGNAL(sig_SomethingComing(QString)));
}

CBridge::~CBridge()
{

}

CPordLogical *CBridge::getCpordLogical() const
{
    return m_pCpordLogical;
}

CPort *CBridge::getCPort() const
{
    return m_pPort;
}
