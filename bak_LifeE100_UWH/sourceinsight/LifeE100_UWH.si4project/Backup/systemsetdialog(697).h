#ifndef SYSTEMSETDIALOG_H
#define SYSTEMSETDIALOG_H

#include <QDialog>
#include "includes.h"

namespace Ui {
class SystemSetDialog;
}

class MonLogFrameDlg;;
class CConfigPanel;
class DataFrameDlg;
class UpDateDialog;
class QTextEdit;
class QTimer;
class SystemSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SystemSetDialog(QWidget *parent = 0);
    ~SystemSetDialog();
	void FlashCfgDevPrm(void);
private:
	void InitPourTestData(void);
	void AddDataFrmUI(void);
	void GetSystemTime(DateTime& dateTime);
	void AddOperSetFrmUI(void);
	

	DataFrameDlg* m_pDataFrmDlg;
    CConfigPanel* m_pCfgPanel;
	MonLogFrameDlg* m_pMonLogFrmDlg;

	UpDateDialog* m_pUpDateDialog;
	bool m_bUpdateFlg;
	UINT8 m_unTestUpSce;
	bool m_ShowUpDateDlgFlg;

private:
    Ui::SystemSetDialog *ui;
};

#endif // SYSTEMSETDIALOG_H
