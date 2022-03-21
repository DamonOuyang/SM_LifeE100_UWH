#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H
#include "includes.h"

#include <QDialog>

namespace Ui {
class UpDateDialog;
}

class QComboBox;
class UpDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpDateDialog(QWidget *parent = 0);
    ~UpDateDialog();

    void SetDevType(UINT8 unType);
	void SetUpMcuBar(UINT8 unPre, UINT8 unUpStat);

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();
signals:
	void sendChooseType(UINT8);
	void sendCanlceUp(void);

private:
	QString ShowUpdateState(UINT8 unUpStat);
	
    Ui::UpDateDialog *ui;
	QComboBox *comboBox;
	bool m_bSndUpTypeFlg;
	bool m_bUpdateFlag;
	UINT8 m_unUpDevType;
	//unsigned char m_unUpDevType;
};

#endif // UPDATEDIALOG_H
