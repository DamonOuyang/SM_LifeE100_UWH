#ifndef ALMSHOWDIALOG_H
#define ALMSHOWDIALOG_H

#include <QDialog>

namespace Ui {
class AlmShowDialog;
}

class AlmShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlmShowDialog(QWidget *parent = 0);
    ~AlmShowDialog();

private:
    Ui::AlmShowDialog *ui;
};

#endif // ALMSHOWDIALOG_H
