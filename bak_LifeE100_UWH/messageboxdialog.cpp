#include "messageboxdialog.h"
#include "ui_messageboxdialog.h"

MessageBoxDialog::MessageBoxDialog(QWidget *parent, bool cancelBt) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::MessageBoxDialog)
{
    ui->setupUi(this);
	SetCancelBt(cancelBt);

}

MessageBoxDialog::~MessageBoxDialog()
{
    delete ui;
}

void MessageBoxDialog::SetCancelBt(bool bcancel)
{
	if(bcancel == true)
	{
	    ui->okButton1->hide();
	    ui->cancelButton->show();
		ui->okButton->show();
	}
	else
	{
	    ui->cancelButton->hide();
		ui->okButton->hide();
		ui->okButton1->show();
	}
}
void MessageBoxDialog::SetMessLabelText(QString labelText)
{
    ui->label->setText(labelText);
}
void MessageBoxDialog::on_cancelButton_clicked()
{
    done(QDialog::Rejected);
}

void MessageBoxDialog::on_okButton_clicked()
{
    done(QDialog::Accepted);
}

void MessageBoxDialog::on_okButton1_clicked()
{
	done(QDialog::Accepted);
}
