#ifndef CPORDLOGICAL_H
#define CPORDLOGICAL_H

#include <QObject>
class Message;
class CPordLogical : public QObject
{
    Q_OBJECT
public:
    explicit CPordLogical(QObject *parent = nullptr);
    ~CPordLogical();

public:
    //这里可以在UI里来直接调用
    QString get() const;

signals:
    //处理完的Msg发到界面上去显示
    void sig_SomethingComing(QString);

private slots:
    //接收下层来的msg
    void slot_onCommingMsg(const Message&);

public slots:

};

#endif // CPORDLOGICAL_H
