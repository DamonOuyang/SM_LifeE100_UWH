#include "lockscreendialog.h"
#include "ui_lockscreendialog.h"
#include "normalwindowdialog.h"
#include "unlockinfodialog.h"

#include <QtGui>
LockScreenDialog::LockScreenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LockScreenDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);


	connect(this,SIGNAL(sendLock(void)),parent,SLOT(setLock(void)));//
}

LockScreenDialog::~LockScreenDialog()
{
    //m_pUpdTimer->stop();
	//delete m_pUpdTimer;
    delete ui;
}



void LockScreenDialog::on_boxButton_clicked()
{
    on_LockScreenBtn_clicked();
}

void LockScreenDialog::on_boxButton2_clicked()
{
	on_LockScreenBtn_clicked();
}

void LockScreenDialog::on_LockScreenBtn_clicked()
{
	unlockInfoDialog  unlockDialog(this);
	unlockDialog.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
	//norWinDialog.SetDefaultVal(ui->pourPressSetLE->text(),ART_PRE_SET_TITLE);
	unlockDialog.setWindowModality(Qt::ApplicationModal);
	unlockDialog.exec();
}

void LockScreenDialog::setUnlockOk(void)
{
	this->hide();
	emit sendLock();    
}