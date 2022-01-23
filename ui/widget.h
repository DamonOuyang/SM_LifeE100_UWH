#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class CBridge;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(CBridge* bridge,QWidget *parent = 0);
    ~Widget();

public slots:
    void slot_onComing(QString content);

private:
    Ui::Widget * ui;
    CBridge * m_cbridge;
};

#endif // WIDGET_H
