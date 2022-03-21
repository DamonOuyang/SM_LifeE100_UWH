#ifndef SYSTEMSETDIALOG_H
#define SYSTEMSETDIALOG_H

#include <QDialog>

namespace Ui {
class SystemSetDialog;
}

class SystemSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SystemSetDialog(QWidget *parent = 0);
    ~SystemSetDialog();

private:
    Ui::SystemSetDialog *ui;
};

#endif // SYSTEMSETDIALOG_H
