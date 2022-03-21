#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QComboBox>



UpDateDialog::UpDateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpDateDialog)
{
    ui->setupUi(this);

    ui->upMcuBar->hide();
	comboBox = CreateComboBox(this);//设备类型
	comboBox->setGeometry(QRect(130, 60, 160, 40));
    comboBox->addItem(tr("上位机APP"));
    comboBox->addItem(tr("动脉血泵"));
    comboBox->addItem(tr("水浴设备"));
	comboBox->addItem(tr("静脉血泵"));
	comboBox->setMaximumWidth(150);

    connect(this,SIGNAL(sendChooseType(UINT8)),parent,SLOT(UpChooseType(UINT8)));//
    connect(this,SIGNAL(sendCanlceUp(void)),parent,SLOT(UpCanlce(void)));//

	m_bSndUpTypeFlg = false;
	m_bUpdateFlag = false;
	m_unUpDevType = 0;
}

UpDateDialog::~UpDateDialog()
{
    delete ui;
}

void UpDateDialog::closeEvent(QCloseEvent *event)
{
	on_cancelButton_clicked();
	printf("Entr UpDateDialog::closeEvent \r\n");
}


void UpDateDialog::SetDevType(UINT8 unType)
{
    m_unUpDevType = unType;
	comboBox->setCurrentIndex(m_unUpDevType);
}

void UpDateDialog::on_cancelButton_clicked()
{
	emit sendCanlceUp();
	//done(QDialog::Rejected);
	this->hide();
}

void UpDateDialog::on_okButton_clicked()
{
    if(m_bSndUpTypeFlg == false)
    {
	    m_unUpDevType = comboBox->currentIndex();
		emit sendChooseType(m_unUpDevType);
		comboBox->hide();
		ui->upMcuBar->show();

	    ui->cancelButton->setEnabled(false);
	    ui->okButton->setEnabled(false);
		printf("--------UpDateDialog::on_okButton_clicked-----------------------m_bSndUpTypeFlg == false\r\n");
    }
	if(m_bUpdateFlag == true)
	{
	    ui->label->setText(ShowUpdateState(0xFF));
        ui->upMcuBar->setValue(0);
	
		comboBox->show();
		ui->upMcuBar->hide();

	    ui->cancelButton->setEnabled(true);
	    ui->okButton->setEnabled(true);
		m_bUpdateFlag = false;
		m_bSndUpTypeFlg = false;

		emit sendCanlceUp();
		this->hide();
		printf("--------UpDateDialog::on_okButton_clicked------------------m_bUpdateFlag == true\r\n");
	}
}

void UpDateDialog::SetUpMcuBar(UINT8 unPre, UINT8 unUpStat)
{
    printf("Entr UpDateDialog::SetUpMcuBar unPre:%u unUpStat:%u \r\n",unPre,unUpStat);
    if(unUpStat == UpdDoing)
    {
        m_bSndUpTypeFlg = true;
		//printf("-----------------------------------------------UpdDoing\r\n");
    }
	
	ui->label->setText(ShowUpdateState(unUpStat));
    ui->upMcuBar->setValue(unPre);
	if(unPre == 100 || unUpStat > UpdSuccess)
	{
		ui->okButton->setEnabled(true);
		m_bUpdateFlag = true;
		m_bSndUpTypeFlg = true;
		//comboBox->setItemData(m_unUpDevType, 0, Qt::UserRole - 1);
		printf("-----------------------------------------unPre == 100 || unUpStat > UpdSuccess \r\n");
	}
}

QString UpDateDialog::ShowUpdateState(UINT8 unUpStat)
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
