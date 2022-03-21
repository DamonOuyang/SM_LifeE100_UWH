#include "loadheaddialog.h"
#include "ui_loadheaddialog.h"
#include "Includes.h"

LoadHeadDialog::LoadHeadDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::LoadHeadDialog)
{
    ui->setupUi(this);

    ui->loadOkBut->hide();
	m_unStep = 1;
	//LoadingImg(m_unStep);
}

LoadHeadDialog::~LoadHeadDialog()
{
    delete ui;
}

void LoadHeadDialog::LoadingImg(unsigned char unStep)
{
    switch(unStep)
    {
        case 1:
	        ui->imgWidget->setStyleSheet(QString::fromUtf8("#imgWidget\n"
			"{\n"
			"background: transparent;\n"
			"	border-image: url(:/images/Head/step1_img.png);\n"
			"}"));
			break;
        case 2:
	        ui->imgWidget->setStyleSheet(QString::fromUtf8("#imgWidget\n"
			"{\n"
			"background: transparent;\n"
			"	border-image: url(:/images/Head/step2_img.png);\n"
			"}"));
			break;
        case 3:
	        ui->imgWidget->setStyleSheet(QString::fromUtf8("#imgWidget\n"
			"{\n"
			"background: transparent;\n"
			"	border-image: url(:/images/Head/step3_img.png);\n"
			"}"));
			break;
        case 4:
	        ui->imgWidget->setStyleSheet(QString::fromUtf8("#imgWidget\n"
			"{\n"
			"background: transparent;\n"
			"	border-image: url(:/images/Head/step4_img.png);\n"
			"}"));
			break;
        case 5:
	        ui->imgWidget->setStyleSheet(QString::fromUtf8("#imgWidget\n"
			"{\n"
			"background: transparent;\n"
			"	border-image: url(:/images/Head/step5_img.png);\n"
			"}"));
			g_setReadCalPrm[0].bstCalPrm.bCalItem = 0;//动脉压力
			g_setReadCalPrm[0].bstCalPrm.bCalIndex = 0;//校零
			g_setReadCalPrm[0].calPrmFlag = CAL_SET;
			
			g_setReadCalPrm[1].bstCalPrm.bCalItem = 0;//静脉压力
			g_setReadCalPrm[1].bstCalPrm.bCalIndex = 0;//校零
			g_setReadCalPrm[1].calPrmFlag = CAL_SET;			
			break;
		default:
	        ui->imgWidget->setStyleSheet(QString::fromUtf8("#imgWidget\n"
			"{\n"
			"background: transparent;\n"
			"	border-image: url(:/images/Head/step1_img.png);\n"
			"}"));
			break;
    }

}
void LoadHeadDialog::on_loadLastBut_clicked()
{
	if(m_unStep == 5)
	{
		ui->loadOkBut->hide();
		ui->loadNextBut->show();
	}
	if(m_unStep > 1)
	{
	    m_unStep--;
		LoadingImg(m_unStep);
	}
}

void LoadHeadDialog::on_loadNextBut_clicked()
{
	if(m_unStep < 5)
	{
	    m_unStep++;
		LoadingImg(m_unStep);
		if(m_unStep == 5)
		{
		    ui->loadOkBut->show();
			ui->loadNextBut->hide();
		}
	}
}

void LoadHeadDialog::on_loadOkBut_clicked()
{
	this->close();
}
