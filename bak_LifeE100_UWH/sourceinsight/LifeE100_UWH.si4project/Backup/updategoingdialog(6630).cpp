#include "updategoingdialog.h"
#include "ui_updategoingdialog.h"


#if RUN_ARM_LINUX
UpdateGoingDialog::UpdateGoingDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::UpdateGoingDialog)    
#else
UpdateGoingDialog::UpdateGoingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateGoingDialog)
#endif    
{
    ui->setupUi(this);

	ui->UpdRoundBar->setDecimals(0);
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
    m_pUpdateBar->setRange(0, 100);
    m_pUpdateBar->setValue(0);

	//connectToSlider(ui->WatRoundBar);
}

void UpdateGoingDialog::SetUpMcuBar(UINT8 unPre, UINT8 unUpStat)
{
    printf("Entr UpDateDialog::SetUpMcuBar unPre:%u unUpStat:%u \r\n",unPre,unUpStat);
	
	ui->label->setText(ShowUpdateState(unUpStat));
    ui->UpdRoundBar->setValue(unPre);
	if(unPre == 100 || unUpStat > UpdSuccess)
	{
		this->hide();
		printf("-----------------------------------------unPre == 100 || unUpStat > UpdSuccess \r\n");
	}
}

QString UpdateGoingDialog::ShowUpdateState(UINT8 unUpStat)
{
    QString stateText = "��ѡ�������豸����";
	
    switch(unUpStat)
    {
        case UpdNotStart:
			stateText = "δ��ʼ����";
			break;
		case UpdDoing:
			stateText = "�����С�����������";
			break;
		case UpdSuccess:
			stateText = "MCU�����ɹ�";
			break;
		case UpdFileOpenErr:
			stateText = "�������ļ�ʧ��";
			break;
		case UpdFileChkErr:
			stateText = "�����ļ����ʧ��";
			break;
		case UpdFileReadChkErr:
			stateText = "�����ļ������ʧ��";
			break;
		case UpdFileReadErr:
			stateText = "�����ļ���ʧ��";
			break;
		case UpdSndPackErr:
			stateText = "��������ʧ��3��";
			break;
		case UpdFindFileErr:
			stateText = "�����ļ��Ҳ���";
			break;
		default:break;
	}
	return stateText;
}

