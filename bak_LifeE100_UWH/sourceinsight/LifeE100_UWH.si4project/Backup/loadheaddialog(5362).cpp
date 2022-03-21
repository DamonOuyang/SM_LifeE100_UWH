#include "loadheaddialog.h"
#include "ui_loadheaddialog.h"

LoadHeadDialog::LoadHeadDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::LoadHeadDialog)
{
    ui->setupUi(this);

    ui->loadOkBut->hide();
	m_unStep = 1;
	LoadingImg(m_unStep);
}

LoadHeadDialog::~LoadHeadDialog()
{
    delete ui;
}

void LoadHeadDialog::LoadingImg(unsigned char unStep)
{
	QPixmap pixmap;
    switch(unStep)
    {
        case 1:
			pixmap = QPixmap(":/images/Head/step1_img.png");
			break;
        case 2:
			pixmap = QPixmap(":/images/Head/step2_img.png");
			break;
        case 3:
			pixmap = QPixmap(":/images/Head/step3_img.png");
			break;
        case 4:
			pixmap = QPixmap(":/images/Head/step4_img.png");
			break;
        case 5:
			pixmap = QPixmap(":/images/Head/step5_img.png");
			break;
		default:
			pixmap = QPixmap(":/images/Head/step1_img.png");
			break;
    }
	QPalette palette;//创建一个调色板对象
	palette.setBrush(ui->imgWidget->backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到IndexTab.backgroundRole()这个背景上
	ui->imgWidget->setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联

}
void LoadHeadDialog::on_loadLastBut_clicked()
{
	if(m_unStep > 1)
	{
	    m_unStep--;
		LoadingImg(m_unStep);
	}
}

void LoadHeadDialog::on_loadNextBut_clicked()
{

}

void LoadHeadDialog::on_loadOkBut_clicked()
{

}
