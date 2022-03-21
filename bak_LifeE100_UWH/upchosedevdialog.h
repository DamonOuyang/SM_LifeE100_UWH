#ifndef UPCHOSEDEVDIALOG_H
#define UPCHOSEDEVDIALOG_H

#include <QDialog>


namespace Ui {
class UpChoseDevDialog;
}
class UpChoseDevDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpChoseDevDialog(QWidget *parent = 0);
    ~UpChoseDevDialog();

private slots:
    void on_pushButton1_clicked(bool checked);

    void on_pushButton2_clicked(bool checked);

    void on_pushButton3_clicked(bool checked);

    void on_pushButton4_clicked(bool checked);

    void on_upCancel_clicked();

    void on_upOk_clicked();
signals:
	void sendChooseDev(unsigned char);
	void sendCanlceUp(void);

private:
    Ui::UpChoseDevDialog *ui;
	
	unsigned char m_unUpDevType;
};

#endif // UPCHOSEDEVDIALOG_H
