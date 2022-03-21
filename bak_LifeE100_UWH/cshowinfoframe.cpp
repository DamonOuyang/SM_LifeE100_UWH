#include "cshowinfoframe.h"
#include "ui_cshowinfoframe.h"

#include "includes.h"
//#include "CWorkThread.h"
#include "cworkthread.h"
#include <QtGui>
#include "mainwindow.h"
#include "cworkthread.h"

#define   MAX_SHOW_INFO_SIZE 5000

CShowInfoFrame::CShowInfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CShowInfoFrame)
{
    ui->setupUi(this);
    m_bRcvFlag = false;
	connect(g_pWorkThread, SIGNAL(ShowInfo()), this, SLOT(ShowString()));
}

CShowInfoFrame::~CShowInfoFrame()
{
    delete ui;
}


void CShowInfoFrame::ShowString(void)
{
    while(true==g_pWorkThread->GetInfoString(&m_errInfo))
    {
        if(DBG_SHOW==m_errInfo.unShowMode)
        {
            if(false==m_bRcvFlag)
            {
                if(ui->pShwInfo->toPlainText().length()>MAX_SHOW_INFO_SIZE)
                {
                    ui->pShwInfo->setText(m_errInfo.pString);
                }
                else
                {
                    ui->pShwInfo->append(m_errInfo.pString);
                }
            }
        }
        else
        {
        /*
            QMessageBox msgBox(this);
			msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
            if(ICON_ERROR==m_errInfo.unErrIcon)
            {
                ShowInfo(&msgBox,m_errInfo.pString,"错误",QMessageBox::Critical);

            }
            else
            {
                ShowInfo(&msgBox,m_errInfo.pString,"提示",QMessageBox::Information);
            }*/
			MessageBoxDialog msgBox(this, false);
			msgBox.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
			msgBox.SetMessLabelText(m_errInfo.pString);
			msgBox.exec();
        }
    }
}


void CShowInfoFrame::on_pClearBut_clicked()
{
	ui->pShwInfo->setText(tr(""));
}

void CShowInfoFrame::on_pStopBut_clicked(bool checked)
{
	m_bRcvFlag = checked;
}
