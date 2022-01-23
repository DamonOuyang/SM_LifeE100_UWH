#ifndef CUSMESSAGE_H
#define CUSMESSAGE_H

#include <QObject>

class CusMessage : public QObject
{
    Q_OBJECT
public:
    explicit CusMessage(QObject *parent = nullptr);
    ~CusMessage();

signals:

public slots:

};

#endif // MESSAGE_H
