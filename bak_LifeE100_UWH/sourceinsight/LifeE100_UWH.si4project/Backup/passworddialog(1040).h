#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = 0,bool bModPwdFlag = false);
    ~PasswordDialog();

private slots:
    void on_pwdCancel_clicked();

    void on_pwdOk_clicked();

    void on_pwdEdit_clicked();

private:
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
