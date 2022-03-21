#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

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

    void OnFocusChanged(QWidget * old, QWidget * now);
    void confirmString(QString strIn);

private:
    Ui::PasswordDialog *ui;

    QLineEdit*  m_pInputPwd;
    QLineEdit*  m_pNewPassword;
    QLineEdit*  m_pCfmPassword;
    QComboBox*  m_pPwdEnable;
    QWidget*    m_pCurLineEdit;
    bool m_bModPwdFlag;
};

#endif // PASSWORDDIALOG_H
