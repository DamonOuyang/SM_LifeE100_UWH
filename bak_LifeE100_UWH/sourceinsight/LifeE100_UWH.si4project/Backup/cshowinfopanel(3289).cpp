#include "Includes.h"
#include "cshowinfopanel.h"
#include "CWorkThread.h"
#include <QtGui>
#include "mainwindow.h"
#include "cworkthread.h"
//#include "CPasswordDlg.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QTextEdit>

#define   MAX_SHOW_INFO_SIZE 5000


CShowInfoPanel::CShowInfoPanel(QWidget *parent) :
    QFrame(parent)
{
    m_bRcvFlag = true;
    QVBoxLayout* pMainLayout = new QVBoxLayout();
    setLayout(pMainLayout);


    //QDialogButtonBox*  pDlgLayout1 = new QDialogButtonBox(Qt::Horizontal);
    //QPushButton* pExitBut = new QPushButton(tr("退出程序"));
    //pDlgLayout1->addButton(pExitBut,QDialogButtonBox::ActionRole);
    //pExitBut->setMinimumSize(160,30);

    m_pShwInfo = new QTextEdit();
    m_pShwInfo->setReadOnly(true);
    pMainLayout->addWidget(m_pShwInfo);
	
    QDialogButtonBox*  pDlgLayout = new QDialogButtonBox(Qt::Horizontal);
    QPushButton* pClearBut = new QPushButton(tr("清除"));
    m_pStopBut  = new QPushButton(tr("停止接收"));

    pClearBut->setMinimumSize(100,35);
    m_pStopBut->setMinimumSize(100,35);
    pDlgLayout->addButton(pClearBut,QDialogButtonBox::ActionRole);
    pDlgLayout->addButton(m_pStopBut,QDialogButtonBox::ActionRole);
    //pDlgLayout->setCenterButtons(true);
    pMainLayout->addWidget(pDlgLayout);

    //pMainLayout->addWidget(pDlgLayout1);

    connect(g_pWorkThread, SIGNAL(ShowInfo()), this, SLOT(ShowString()));

    connect(pClearBut, SIGNAL(clicked()),this, SLOT(OnClearInfo()));
    connect(m_pStopBut, SIGNAL(clicked()),this,SLOT(OnStopRecv()));
    //connect(pExitBut, SIGNAL(clicked()),this, SLOT(OnExit(void)));
}

void CShowInfoPanel::ShowString(void)
{
    while(true==g_pWorkThread->GetInfoString(&m_errInfo))
    {
        if(DBG_SHOW==m_errInfo.unShowMode)
        {
            if(true==m_bRcvFlag)
            {
                if(m_pShwInfo->toPlainText().length()>MAX_SHOW_INFO_SIZE)
                {
                    m_pShwInfo->setText(m_errInfo.pString);
                }
                else
                {
                    m_pShwInfo->append(m_errInfo.pString);
                }
            }
        }
        else
        {
            QMessageBox msgBox(this);
			//msgBox.setWindowFlags(Qt::Drawer);
            if(ICON_ERROR==m_errInfo.unErrIcon)
            {
                ShowInfo(&msgBox,m_errInfo.pString,"错误",QMessageBox::Critical);

            }
            else
            {
                ShowInfo(&msgBox,m_errInfo.pString,"提示",QMessageBox::Information);
            }
        }
    }
}


void CShowInfoPanel::OnClearInfo(void)
{
    m_pShwInfo->setText(tr(""));
}

void CShowInfoPanel::OnStopRecv(void)
{
    if(false==m_bRcvFlag)
    {
        m_bRcvFlag = true;
        m_pStopBut->setText(tr("停止接收"));
    }
    else
    {
        m_bRcvFlag = false;
        m_pStopBut->setText(tr("开始接收"));
    }
}

void CShowInfoPanel::OnExit(void)
{
    QPushButton* pNewBut;
    QMessageBox  msgBox(this);

    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("你是否想退出并更新程序?");
    pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(100,30);
    pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
    pNewBut->setMinimumSize(100,30);
    SetMessageBoxFont(&msgBox);
    if(QMessageBox::AcceptRole == msgBox.exec())
    {
        fclose(stdout);
        qApp->quit();
    }
}

