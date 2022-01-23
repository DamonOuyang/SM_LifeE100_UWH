#include "cpordlogical.h"

CPordLogical::CPordLogical(QObject *parent)
    : QObject(parent)
{

}

CPordLogical::~CPordLogical()
{

}

QString CPordLogical::get() const
{

}

void CPordLogical::slot_onCommingMsg(const Message & msg)
{
    Q_UNUSED(msg);
    //这里可以对收到的msg进行处理
    emit sig_SomethingComing("sss");
}
