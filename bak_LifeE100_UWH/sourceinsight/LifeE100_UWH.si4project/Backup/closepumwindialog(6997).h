#ifndef CLOSEPUMWINDIALOG_H
#define CLOSEPUMWINDIALOG_H

#include <QDialog>

namespace Ui {
class ClosePumWinDialog;
}

class ClosePumWinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClosePumWinDialog(QWidget *parent = 0);
    ~ClosePumWinDialog();

private slots:
    void on_cancelPumButton_clicked();

private:
    Ui::ClosePumWinDialog *ui;
};

#endif // CLOSEPUMWINDIALOG_H
