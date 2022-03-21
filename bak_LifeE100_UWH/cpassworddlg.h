#ifndef CPASSWORDDLG_H
#define CPASSWORDDLG_H

#include <QDialog>

class QLineEdit;
class QWidget;
class QComboBox;
class CPasswordDlg : public QDialog
{
    Q_OBJECT
public:
    explicit CPasswordDlg(QWidget *parent = 0,bool bModPwdFlag = false);
    
signals:
    
public slots:
    void OnClickOK(void);
    void OnClickCancel(void);
    void OnItemEdit(void);
    void OnFocusChanged(QWidget * old, QWidget * now);
    void confirmString(QString strIn);
private:
	void ReleaseAll(void);
    QLineEdit*  m_pInputPwd;
    QLineEdit*  m_pNewPassword;
    QLineEdit*  m_pCfmPassword;
    QComboBox*  m_pPwdEnable;
    QWidget*    m_pCurLineEdit;
    bool m_bModPwdFlag;
};

#endif // CPASSWORDDLG_H
