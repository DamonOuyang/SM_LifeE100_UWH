#ifndef MESSAGEBOXDIALOG_H
#define MESSAGEBOXDIALOG_H

#include <QDialog>

namespace Ui {
class MessageBoxDialog;
}

class MessageBoxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageBoxDialog(QWidget *parent = 0,bool cancelBt = false);
    ~MessageBoxDialog();
	void SetMessLabelText(QString labelText);
	void SetCancelBt(bool bcancel);

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_okButton1_clicked();

private:
    Ui::MessageBoxDialog *ui;
};

#endif // MESSAGEBOXDIALOG_H
