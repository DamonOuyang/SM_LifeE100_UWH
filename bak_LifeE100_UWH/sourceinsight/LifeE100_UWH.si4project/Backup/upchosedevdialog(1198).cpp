#include "upchosedevdialog.h"
#include "ui_upchosedevdialog.h"
#include "includes.h"

#if RUN_ARM_LINUX
UpChoseDevDialog::UpChoseDevDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::UpChoseDevDialog)    
#else
UpChoseDevDialog::UpChoseDevDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpChoseDevDialog)
#endif
{
    ui->setupUi(this);

    m_unUpDevType = 0;
    connect(this,SIGNAL(sendChooseDev(unsigned char)),parent,SLOT(UpChooseDev(unsigned char)));//
    connect(this,SIGNAL(sendCanlceUp(void)),parent,SLOT(UpCanlce(void)));//
}

UpChoseDevDialog::~UpChoseDevDialog()
{
    delete ui;
}

void UpChoseDevDialog::on_pushButton1_clicked(bool checked)
{
	if(checked == true)
	{
	    m_unUpDevType = 0;
	}
}

void UpChoseDevDialog::on_pushButton2_clicked(bool checked)
{
	if(checked == true)
	{
	    m_unUpDevType = 1;
	}
}

void UpChoseDevDialog::on_pushButton3_clicked(bool checked)
{
	if(checked == true)
	{
	    m_unUpDevType = 2;
	}
}

void UpChoseDevDialog::on_pushButton4_clicked(bool checked)
{
	if(checked == true)
	{
	    m_unUpDevType = 3;
	}
}

void UpChoseDevDialog::on_upCancel_clicked()
{
	emit sendCanlceUp();
	this->hide();
}

void UpChoseDevDialog::on_upOk_clicked()
{
    unsigned char unSndType = m_unUpDevType;
	emit sendChooseDev(unSndType);
	printf("------------------------------------%u:------------------\r\n",m_unUpDevType);
	this->hide();
}
