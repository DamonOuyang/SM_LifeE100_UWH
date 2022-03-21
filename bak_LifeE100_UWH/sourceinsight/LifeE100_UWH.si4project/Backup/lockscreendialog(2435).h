#ifndef LOCKSCREENDIALOG_H
#define LOCKSCREENDIALOG_H

#include <QDialog>
#include "includes.h"

namespace Ui {
class LockScreenDialog;
}

class QTimer;
class LockScreenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LockScreenDialog(QWidget *parent = 0);
    ~LockScreenDialog();
signals:
	void sendLock(void);

private slots:
	void OnFirtActiveTimer(void);
    //void on_LockScreenBtn_pressed();
    //void on_LockScreenBtn_released();

    void on_boxButton_clicked();

    void on_boxButton2_clicked();

    void on_LockScreenBtn_clicked();

private:
    Ui::LockScreenDialog *ui;
	QTimer*  m_pUpdTimer;
	UINT8    m_unPressedSec;
	bool     m_bPressedFlag;
};

#endif // LOCKSCREENDIALOG_H
