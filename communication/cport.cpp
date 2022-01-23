#include "cport.h"
#include "cusmessage.h"
#include <QDebug>

CPort::CPort(QObject *parent)
    : QObject(parent)
    , m_port(NULL)
    , m_worker(0)
    , m_timer(NULL)
    , m_data(0)

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

    m_timer = new QTimer(this);
    m_timer->setInterval(10000);
    connect(m_timer,SIGNAL(timeout()),SLOT(slot_onParse()));
    m_timer->start();

    this->moveToThread(&m_worker);
    m_worker.start(QThread::HighPriority);
}

CPort::~CPort()
{

}

void CPort::slot_onDownwardMsg(const CusMessage & msg)
{
    // 向下发送指令 协议封装在 protocal msg.content
    QByteArray array("");
    m_port->write(array);
}

void CPort::slot_onReadData()
{
    m_data.append(m_port->readAll());
}

void CPort::slot_onParse()
{

    for(int i = 0;i < m_data.size(); i++)
    {
        // 协议解析后得到 message 同时写库
    }
    CusMessage msg;
    //emit sig_upward_msg(msg);
    emit sig_upward_msg("hello");
}
