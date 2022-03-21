#ifndef SETVALDIALOG_H
#define SETVALDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class SetValDialog;
}

class QTimer;
class SetValDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetValDialog(QWidget *parent = 0);//
    ~SetValDialog();

    void SetDefaultVal(QString strDefVal,unsigned char onTitle);
	void SetValLimit(unsigned int unMinLimit, unsigned int unLimitVal, unsigned char unStep, \
		                 int lFactScale,int lDotNum,unsigned char unTmtStep);//long
    QString GetSetValTitle(unsigned char onTitle);
private slots:
    void on_reduceButton_pressed();
    void on_reduceButton_released();
    void OnReduceTimer();

    void on_addButton_pressed();
    void on_addButton_released();
    void OnAddButtonTimer();
    void on_okButton_clicked();

    void on_cancelButton_clicked();
signals:
    void sendSetNumber(QString gemfield);
	void sendSetCanlce(void);

private:
    Ui::SetValDialog *ui;
    QTimer *m_reduceTimer;
    QTimer *m_addValTimer;
	signed long m_unLimitVal; //设置限值
	signed long m_unMinLimitVal; //最小设置限值
	signed char  m_unStep;    //设置步长
	signed int  m_lFactScale;   //数值倍数
	signed int  m_lDotNum;      //数值小数点个数(整数为0)
	signed char m_unTmtStep;  //长按调节步长倍数(剩步长)
};

#endif // SETVALDIALOG_H

