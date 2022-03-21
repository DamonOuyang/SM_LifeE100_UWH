#ifndef CPORT_H
#define CPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QThread>
#include <QTimer>
#include "lockex.h"

class CusMessage; // 当然这个结构体得自己定义并注册，这里使用了前置申明

class CPort : public QObject
{
    Q_OBJECT
public:
    explicit CPort(QObject *parent = nullptr);
    ~CPort();

signals:
    //向上层传送消息
    //void sig_upward_msg(const CusMessage&);
    void sig_upward_msg(const QString&);

public slots:
    //上层传过来的消息发送到串口
    void slot_onDownwardMsg(const CusMessage&);
    void slot_onPollMsg();

    //读串口数据
    void slot_onReadData();

    //定时解析接收到的数据
    void slot_onParse();

private:
    QSerialPort * m_port;
    QThread m_worker;
    QTimer * m_parseTimer;
    QTimer * m_pollTimer;
    QByteArray m_data;
    LockEx m_lock;
};

#endif // CPORT_H
