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
	ui->m_pCalItemPat->addItem(tr("温度"));

	ui->m_pCalIndexPat->addItem(tr("校正零值"));
	ui->m_pCalIndexPat->addItem(tr("校正参考值"));

}

calPrmDialog::~calPrmDialog()
{
    delete ui;
}

void calPrmDialog::on_closeButton_clicked()
{
	this->hide();
}

void calPrmDialog::on_setButton_clicked()
{

}
