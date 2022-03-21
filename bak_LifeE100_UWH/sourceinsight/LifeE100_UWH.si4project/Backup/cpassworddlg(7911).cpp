#include "Includes.h"
#include "cpassworddlg.h"
#include "SyszuxPinyin.h"
#include <QtGui>
#include <QComboBox>
#include <QFormLayout>
#include <QDialogButtonBox>

CPasswordDlg::CPasswordDlg(QWidget *parent,bool bModPwdFlag) :
    QDialog(parent)
{
    m_pCurLineEdit = NULL;
    m_pNewPassword = NULL;
    m_pInputPwd    = NULL;
    m_pCfmPassword = NULL;
    m_pPwdEnable   = NULL;
    QHBoxLayout* pMainLayout = new QHBoxLayout();
    setLayout(pMainLayout);

    QGroupBox* pLeftGrpBox  = new QGroupBox();
    QGroupBox* pRightGrpBox = new QGroupBox();
    pRightGrpBox->setMinimumWidth(130);

    pMainLayout->addWidget(pLeftGrpBox);
    pMainLayout->addWidget(pRightGrpBox);

    long lEditWidth = 180;
    QFormLayout *pFormLayout    = new QFormLayout;
    //QVBoxLayout* pUpMainLayout  = new QVBoxLayout();
    m_bModPwdFlag = bModPwdFlag;
    if(false==bModPwdFlag)
    {
        m_pInputPwd    = new QLineEdit(this);
        pFormLayout->addRow(tr("设备密码:"), m_pInputPwd);
        m_pInputPwd->setMaximumWidth(lEditWidth);
        m_pInputPwd->setEchoMode(QLineEdit::Password);
        setWindowTitle("密码验证");
    }
    else
    {
        m_pNewPassword = new QLineEdit(this);
        m_pCfmPassword = new QLineEdit(this);
        m_pPwdEnable   = CreateComboBox(this);
        m_pPwdEnable->addItem(tr("禁用"));
        m_pPwdEnable->addItem(tr("启用"));
        m_pPwdEnable->setStyleSheet("height: 25px;");

        m_pNewPassword->setMaximumWidth(lEditWidth);
        m_pCfmPassword->setMaximumWidth(lEditWidth);
        m_pPwdEnable->setMaximumWidth(lEditWidth);
        m_pPwdEnable->setCurrentIndex(g_pwdCfgInfo.bPwdEnFlg);
        pFormLayout->addRow(tr("密码功能:"), m_pPwdEnable);
        pFormLayout->addRow(tr("密码输入:"), m_pNewPassword);
        pFormLayout->addRow(tr("密码确认:"), m_pCfmPassword);
        m_pNewPassword->setEchoMode(QLineEdit::Password);
        m_pCfmPassword->setEchoMode(QLineEdit::Password);
        setWindowTitle("密码设置");
    }
    //pUpMainLayout->addWidget(pFormLayout);
    pFormLayout->setAlignment(Qt::AlignLeft);
    pLeftGrpBox->setLayout(pFormLayout);

    QHBoxLayout* pButLayout = new QHBoxLayout();
    QDialogButtonBox* pButs = new QDialogButtonBox(Qt::Vertical);
    pButLayout->addWidget(pButs);
    QPushButton* pOkBut = new QPushButton(tr(CONFIRM_BUT_NAME));
    pOkBut->setMinimumSize(100,30);
    QPushButton* pCancelBut = new QPushButton(tr(CANCEL_BUT_NAME));
    pCancelBut->setMinimumSize(100,30);
    QPushButton* pEditBut = new QPushButton(tr(INPUT_BUT_NAME));
    pEditBut->setMinimumSize(100,30);

    pButs->addButton(pOkBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pCancelBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pEditBut,QDialogButtonBox::ActionRole);

    pButs->setMinimumSize(100,120);
    pRightGrpBox->setLayout(pButLayout);

    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));
    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));
    setMaximumSize(450,200);
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
}

void CPasswordDlg::OnClickOK(void)
{
    if(true==m_bModPwdFlag)
    {
        QMessageBox msgBox;
        QString strError;
        QString strNewPwd = m_pNewPassword->text();
        QString strCfmPwd = m_pCfmPassword->text();
        if(true==m_pPwdEnable->currentIndex())
        {
            if(strCfmPwd!=strNewPwd)
            {
                QMessageBox msgBox;
                ShowInfo(&msgBox,"密码不一致！","错误",QMessageBox::Critical);
                return;
            }
            if(strCfmPwd.isEmpty())
            {
                ShowInfo(&msgBox,"密码不能为空！","错误",QMessageBox::Critical);
                return;
            }
            strcpy(g_pwdCfgInfo.pUserStrPwd,strNewPwd.toStdString().c_str());
        }
        g_pwdCfgInfo.bPwdEnFlg = m_pPwdEnable->currentIndex();
        if(false==SavePwdInfo(strError))
        {
            ShowInfo(&msgBox,"保存密码失败！原因："+strError,"错误",QMessageBox::Critical);
            return;
        }
        done(QDialog::Accepted);
		ReleaseAll();
    }
    else
    {
        QMessageBox msgBox;
        QString strPwd = m_pInputPwd->text();
        if(0!=strcmp(strPwd.toStdString().c_str(),g_pwdCfgInfo.pUserStrPwd)&&\
           0!=strcmp(strPwd.toStdString().c_str(),g_pwdCfgInfo.pAdminStrPwd))
        {
            ShowInfo(&msgBox,"密码不对！","错误",QMessageBox::Critical);
            return;
        }
        done(QDialog::Accepted);
		ReleaseAll();
    }
}

void CPasswordDlg::ReleaseAll(void)
{
    //delete m_pInputPwd;
    //delete m_pNewPassword;
    //delete m_pCfmPassword;
    //delete m_pPwdEnable;
    m_pCurLineEdit = NULL;
	delete m_pCurLineEdit;
}


void CPasswordDlg::OnClickCancel(void)
{
    done(QDialog::Rejected);
    ReleaseAll();
}

void CPasswordDlg::OnItemEdit(void)
{
    if(NULL!=m_pCurLineEdit)
    {
        SyszuxPinyin dlgInputPanel(this);
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void CPasswordDlg::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(NULL!=old)
    {
        if( m_pInputPwd == old)
        {
            m_pCurLineEdit = old;
        }
        else if(m_pNewPassword == old)
        {
            m_pCurLineEdit = old;
        }
        else if(m_pCfmPassword == old)
        {
            m_pCurLineEdit = old;
        }
    }
}


void CPasswordDlg::confirmString(QString strIn)
{
    if(false==m_bModPwdFlag)
    {
        m_pInputPwd->setText(strIn);
    }
    else
    {
        if(NULL != m_pCurLineEdit)
        {
            ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
        }
    }
}
