#ifndef UPDATEGOINGDIALOG_H
#define UPDATEGOINGDIALOG_H
#include "includes.h"

#include <QDialog>

namespace Ui {
class UpdateGoingDialog;
}
class QRoundProgressBar;
class UpdateGoingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateGoingDialog(QWidget *parent = 0);
    ~UpdateGoingDialog();

	void SetUpMcuBar(UINT8 unPre, UINT8 unUpStat);
	QString ShowUpdateState(UINT8 unUpStat);

private slots:
    void on_closeButton_clicked();

private:
    Ui::UpdateGoingDialog *ui;
    void InitUpdateBar(QRoundProgressBar* bar);

	QRoundProgressBar* m_pUpdateBar;

};

#endif // UPDATEGOINGDIALOG_H
