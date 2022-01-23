#include "widget.h"
#include "ui_widget.h"
#include "cbridge.h"
#include "cpordlogical.h"
Widget::Widget(CBridge* bridge,QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::Widget)
    , m_cbridge(bridge)
{
    ui->setupUi(this);

    //这里完成业务层与UI层的通信
    connect(m_cbridge->getCpordLogical(), SIGNAL(sig_SomethingComing(QString)), this, SLOT(slot_onComing(QString)) );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_onComing(QString content)
{
    Q_UNUSED(content);
    //SHOW ON UI
}
