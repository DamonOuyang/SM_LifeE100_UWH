#ifndef CONFIGBASICFRAME_H
#define CONFIGBASICFRAME_H

#include <QFrame>

namespace Ui {
class ConfigBasicFrame;
}

class ConfigBasicFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ConfigBasicFrame(QWidget *parent = 0);
    ~ConfigBasicFrame();

private:
    Ui::ConfigBasicFrame *ui;
};

#endif // CONFIGBASICFRAME_H
