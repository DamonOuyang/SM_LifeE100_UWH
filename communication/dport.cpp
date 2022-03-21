#include "cport.h"
#include "cusmessage.h"
#include <QDebug>
#include "guard.h"
#include "lockex.h"
CPort::CPort(QObject *parent)
    : QObject(parent)
    , m_port(NULL)
    , m_worker(0)
    , m_parseTimer(NULL)
    , m_pollTimer(NULL)
    , m_data(0)
    , m_lock("bus_lock")

{
    m_port = new QSerialPort(this);
    m_port->setPortName("/dev/ttyS0");
    m_port->setBaudRate(QSerialPort::Baud115200);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::EvenParity);
    m_port->setStopBits(QSerialPort::OneStop);

    connect(m_port,SIGNAL(readyRead()),this,SLOT(slot_onReadData()));
    if(!m_port->open(QIODevice::ReadWrite))
    {
        qDebug() << "Port Can't open";
    }

    m_parseTimer = new QTimer(this);
    m_parseTimer->setInterval(1000);
    connect(m_parseTimer,SIGNAL(timeout()),SLOT(slot_onParse()));
    m_parseTimer->start();

    m_pollTimer = new QTimer(this);
    m_pollTimer->setInterval(500);
    connect(m_pollTimer,SIGNAL(timeout()),SLOT(slot_onPollMsg()));
    m_pollTimer->start();

    this->moveToThread(&m_worker);
    m_worker.start(QThread::HighPriority);
}

CPort::~CPort()
{

}

void CPort::slot_onDownwardMsg(const CusMessage & msg) //
{
    Q_UNUSED(msg);
    qDebug()<< " ---- onDownwardMsg " << "1";
    // 向下发送指令 协议封装在 protocal msg.content
    QByteArray array("");
    switch (1) {
    case 1:
        array.append("1");
        break;
    default:
        array.append("2");
        break;
    }

    // lock ?
    Guard g(m_lock);
    m_port->write(array);

}

void CPort::slot_onPollMsg()
{
    CusMessage msg;
    slot_onDownwardMsg(msg);
}

void CPort::slot_onReadData()
{
    m_data.append(m_port->readAll());
}

void CPort::slot_onParse()
{
    qDebug()<< " ---- onParse " << m_data;
    for(int i = 0;i < m_data.size(); i++) //Byte one by one
    {
        // 协议解析后得到 message 同时写库
    }
    CusMessage msg;
    //emit sig_upward_msg(msg);
    emit sig_upward_msg("hello");
}
