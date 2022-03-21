#include "cshowinfoframe.h"
#include "ui_cshowinfoframe.h"

CShowInfoFrame::CShowInfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CShowInfoFrame)
{
    ui->setupUi(this);

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
			msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
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


void CShowInfoFrame::OnClearInfo(void)
{
    m_pShwInfo->setText(tr(""));
}

void CShowInfoFrame::OnStopRecv(void)
{
    if(false==m_bRcvFlag)
    {
        m_bRcvFlag = true;
        //m_pStopBut->setText(tr("停止接收"));
    }
    else
    {
        m_bRcvFlag = false;
        //m_pStopBut->setText(tr("开始接收"));
    }
}


void CShowInfoFrame::on_pClearBut_clicked()
{

}

void CShowInfoFrame::on_pStopBut_clicked(bool checked)
{

}
