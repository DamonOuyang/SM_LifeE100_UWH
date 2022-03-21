#include "calprmdialog.h"
#include "ui_calprmdialog.h"


calPrmDialog::calPrmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calPrmDialog)
{
    ui->setupUi(this);

	//ui->m_pModIndex->setMinimumHeight(25);
	ui->m_pModIndex->addItem(tr("动脉血泵"));
	ui->m_pModIndex->addItem(tr("水浴设备"));
	ui->m_pModIndex->addItem(tr("静脉血泵"));

	ui->m_pCalItemPat->addItem(tr("压力"));
	ui->m_pCalItemPat->addItem(tr("流量"));
	ui->m_pCalItemPat->addItem(tr("温度"));

	ui->m_pCalIndexPat->addItem(tr("校正零值"));
	ui->m_pCalIndexPat->addItem(tr("校正参考值"));

    m_pUpdTimer = new QTimer(this);
    connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnUpdData(void)));
	m_pUpdTimer->stop();

}

calPrmDialog::~calPrmDialog()
{
    delete ui;
}

void calPrmDialog::on_closeButton_clicked()
{
    m_pUpdTimer->stop();
	this->hide();
}

void calPrmDialog::on_setButton_clicked()
{
	printf("CalPrmShowDlg::OnSetCalPrm\r\n");
	UINT8 unModIndex = ui->m_pModIndex->currentIndex();
	
	g_setReadCalPrm[unModIndex].bstCalPrm.bCalItem = ui->m_pCalItemPat->currentIndex();
	g_setReadCalPrm[unModIndex].bstCalPrm.bCalIndex = ui->m_pCalIndexPat->currentIndex();
	//g_setReadCalPrm.bstCalPrm.unRefVal = RefValLineEdit->text().toFloat()*100;
	g_setReadCalPrm[unModIndex].calPrmFlag = CAL_SET;
	m_pUpdTimer->start(1000);
}

void calPrmDialog::OnUpdData(void)
{
	UINT8 unModIndex = ui->m_pModIndex->currentIndex();

	//RefValLineEdit->setText(ValueToString(g_setReadCalPrm[unModIndex].bstCalPrm.unRefVal,100,2));
	if(g_setReadCalPrm[unModIndex].calPrmFlag == CAL_SET_OK)
	{
	    g_setReadCalPrm[unModIndex].calPrmFlag = 0;
        QMessageBox  msgBox(this);
        ShowInfo(&msgBox,"设置成功！","校正",QMessageBox::Critical);
	}
	else if(g_setReadCalPrm[unModIndex].calPrmFlag == CAL_SET_FAL)
	{
	    g_setReadCalPrm[unModIndex].calPrmFlag = 0;
        QMessageBox  msgBox(this);
        ShowInfo(&msgBox,"设置失败！","校正",QMessageBox::Critical);	    
	}
	else if(g_setReadCalPrm[unModIndex].calPrmFlag == CAL_READ_OK)
	{
	    g_setReadCalPrm[unModIndex].calPrmFlag = 0;
        QMessageBox  msgBox(this);
        ShowInfo(&msgBox,"读取成功","读取",QMessageBox::Critical);
	}
}

