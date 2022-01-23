#ifndef CBRIDGE_H
#define CBRIDGE_H

#include <QObject>

class CPordLogical;
class CPort;
class Message;
class CBridge : public QObject
{
    Q_OBJECT
public:
    explicit CBridge(QObject *parent = 0);
    ~CBridge();
    //这里可以得到所有的实例
    CPordLogical *getCpordLogical() const;
    CPort *getCPort()const;
signals:
    //这里可以转发信号
    void sig_SomethingComing(QString);

public slots:

private:
    CPordLogical *m_pCpordLogical;
    CPort *m_pPort;
};

#endif // CBRIDGE_H
