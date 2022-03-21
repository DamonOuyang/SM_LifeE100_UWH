#include "updategoingdialog.h"
#include "ui_updategoingdialog.h"


UpdateGoingDialog::UpdateGoingDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::UpdateGoingDialog)       
{
    ui->setupUi(this);

	ui->closeButton->hide();
	InitUpdateBar(ui->UpdRoundBar);

}

UpdateGoingDialog::~UpdateGoingDialog()
{
    delete ui;
}

void UpdateGoingDialog::InitUpdateBar(QRoundProgressBar* bar)
{
    //m_unSliderVal = 0;
    m_pUpdateBar = bar;

	QGradientStop stop1;
	stop1.first = 0;
	stop1.second = QColor(128, 192, 255);
	QGradientStops s;
	s.append(stop1);
	m_pUpdateBar->setDataColors(s);
    m_pUpdateBar->setDecimals(0);
    m_pUpdateBar->setRange(0, 100);
    m_pUpdateBar->setValue(0);
	m_pUpdateBar->setTextColor(QColor(128, 192, 255));
}

void UpdateGoingDialog::SetUpMcuBar(UINT8 unPre, UINT8 unUpStat)
{
    //printf("Entr UpDateDialog::SetUpMcuBar unPre:%u unUpStat:%u \r\n",unPre,unUpStat);
	
	ui->label->setText(ShowUpdateState(unUpStat));
    ui->UpdRoundBar->setValue(unPre);
	if(unPre == 100 || unUpStat >= UpdSuccess)
	{
		//this->hide();
		ui->closeButton->show();
		printf("-----------------------------------------unPre == 100 || unUpStat > UpdSuccess \r\n");
	}
}

QString UpdateGoingDialog::ShowUpdateState(UINT8 unUpStat)
{
    QString stateText = "请选择升级设备类型";
	
    switch(unUpStat)
    {
        case UpdNotStart:
			stateText = "未开始升级";
			break;
		case UpdDoing:
			stateText = "升级中······";
			break;
		case UpdSuccess:
			stateText = "MCU升级成功";
			break;
		case UpdFileOpenErr:
			stateText = "打开升级文件失败";
			break;
		case UpdFileChkErr:
			stateText = "升级文件检测失败";
			break;
		case UpdFileReadChkErr:
			stateText = "升级文件读检测失败";
			break;
		case UpdFileReadErr:
			stateText = "升级文件读失败";
			break;
		case UpdSndPackErr:
			stateText = "连续升级失败3次";
			break;
		case UpdFindFileErr:
			stateText = "升级文件找不到";
			break;
		default:break;
	}
	return stateText;
}


void UpdateGoingDialog::on_closeButton_clicked()
{
	ui->closeButton->hide();
	this->hide();
}
