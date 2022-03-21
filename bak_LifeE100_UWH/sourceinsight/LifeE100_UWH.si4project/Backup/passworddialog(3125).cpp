#include "Includes.h"
#include "passworddialog.h"
#include "ui_passworddialog.h"
#include "numbkeyboarddialog.h"

#include <QMessageBox>
PasswordDialog::PasswordDialog(QWidget *parent,bool bModPwdFlag) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);

    m_pCurLineEdit = NULL;
    m_pNewPassword = NULL;
    m_pInputPwd    = NULL;
    m_pCfmPassword = NULL;
    m_pPwdEnable   = NULL;

    //QImage img;
	
    m_bModPwdFlag = bModPwdFlag;
    if(false==bModPwdFlag)
    {
        //img.load(":/images/Password/pwdEnter_Bg.png"); 
		ui->pwdWidget->setStyleSheet(QString::fromUtf8("#pwdWidget\n"
		"{\n"
		"background-image: url(:/images/Password/pwdEnter_Bg.png);\n"
		"}"));
        m_pInputPwd    = new QLineEdit(ui->pwdWidget);
		m_pInputPwd->setGeometry(QRect(140, 57, 200, 36));
        m_pInputPwd->setEchoMode(QLineEdit::Password);
    }
    else
    {
        //img.load(":/images/Password/pwdSet_Bg.png"); 
		ui->pwdWidget->setStyleSheet(QString::fromUtf8("#pwdWidget\n"
		"{\n"
		"background-image: url(:/images/Password/pwdSet_Bg.png);\n"
		"}"));	
        m_pPwdEnable   = CreateComboBox(ui->pwdWidget);
		m_pPwdEnable->setGeometry(QRect(140, 57, 200, 36));
        m_pPwdEnable->addItem(tr("禁用"));
        m_pPwdEnable->addItem(tr("启用"));
		m_pPwdEnable->setCurrentIndex(g_pwdCfgInfo.bPwdEnFlg);
		
        m_pNewPassword = new QLineEdit(ui->pwdWidget);
		m_pNewPassword->setGeometry(QRect(140, 127, 200, 36));
		m_pNewPassword->setEchoMode(QLineEdit::Password);
		
        m_pCfmPassword = new QLineEdit(ui->pwdWidget);
		m_pCfmPassword->setGeometry(QRect(140, 197, 200, 36));
		m_pCfmPassword->setEchoMode(QLineEdit::Password);
    }

    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
}

PasswordDialog::~PasswordDialog()
{
	m_pCurLineEdit = NULL;
	delete m_pCurLineEdit;
    delete ui;
}



void PasswordDialog::on_pwdCancel_clicked()
{
	done(QDialog::Rejected);
}

void PasswordDialog::on_pwdOk_clicked()
{
	QMessageBox msgBox;
	msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");

    if(true==m_bModPwdFlag)
    {
        //QMessageBox msgBox;
		//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
        QString strError;
        QString strNewPwd = m_pNewPassword->text();
        QString strCfmPwd = m_pCfmPassword->text();
        if(true==m_pPwdEnable->currentIndex())
        {
            if(strCfmPwd!=strNewPwd)
            {
                //QMessageBox msgBox;
				//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)")
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
		//ReleaseAll();
    }
    else
    {
        //QMessageBox msgBox;
		//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)")
        QString strPwd = m_pInputPwd->text();
        if(0!=strcmp(strPwd.toStdString().c_str(),g_pwdCfgInfo.pUserStrPwd)&&\
           0!=strcmp(strPwd.toStdString().c_str(),g_pwdCfgInfo.pAdminStrPwd))
        {
            ShowInfo(&msgBox,"密码不对！","错误",QMessageBox::Critical);
            return;
        }
        done(QDialog::Accepted);
		//ReleaseAll();
    }

}

void PasswordDialog::on_pwdEdit_clicked()
{
    if(NULL!=m_pCurLineEdit)
    {
        NumbKeyboardDialog dlgInputPanel(this);

        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void PasswordDialog::OnFocusChanged(QWidget * old, QWidget * now)
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
void PasswordDialog::confirmString(QString strIn)
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

