#ifndef ONLOGDIALOG_H
#define ONLOGDIALOG_H

#include <QDialog>

namespace Ui {
class OnLogDialog;
}

class OnLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnLogDialog(QWidget *parent = 0);
    ~OnLogDialog();

private:
    Ui::OnLogDialog *ui;
};

#endif // ONLOGDIALOG_H
