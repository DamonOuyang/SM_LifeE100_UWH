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
//class UpDateDialog;
class UpChoseDevDialog;
class UpdateGoingDialog;
class QTimer;
class SystemSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SystemSetDialog(QWidget *parent = 0);
    ~SystemSetDialog();
	void FlashCfgDevPrm(void);
public slots:
    void BackButtonClicked(void);
    void OnClickUpdate(void);
    void OnFirtActiveTimer(void);

	void UpChooseDev(unsigned char unTpye);
	void UpCanlce(void);
	void UpdateFail(UINT8 unPre, UINT8 unFailType);	
private:
	void InitPourTestData(void);
	void AddDataFrmUI(void);
	void GetSystemTime(DateTime& dateTime);
	void AddOperSetFrmUI(void);
	void AddConfigFrmUI(void);
	void FlashCompanyInfo(void);
    QTimer*  m_pUpdTimer;	

	DataFrameDlg* m_pDataFrmDlg;
    CConfigPanel* m_pCfgPanel;
	MonLogFrameDlg* m_pMonLogFrmDlg;

	//UpDateDialog* m_pUpDateDialog;
	UpChoseDevDialog * m_pUpChoseDev;
	UpdateGoingDialog* m_pUpGoing;
	bool m_bUpdateFlg;
	UINT8 m_unTestUpSce;
	bool m_ShowUpDateDlgFlg;

	UINT8   m_unClickNum;
	UINT8   m_unReSetPrmFlag;
	UINT8   m_unCheckUpdateSec;
	UINT8   m_unRunState;
	bool    m_bFlashPicFlg;
	UINT8   m_unDlyFlashInfoSce;
	bool    m_bFlashInfoFlag;
	UINT8   m_unUpDevType;

private:
    Ui::SystemSetDialog *ui;
};

#endif // SYSTEMSETDIALOG_H
