#ifndef SYSTEMSETDIALOG_H
#define SYSTEMSETDIALOG_H
#include "includes.h"
#include <QDialog>
#include <QTextEdit>

namespace Ui {
class SysSetDialog;
}


class MonLogFrameDlg;;
class CConfigPanel;
class DataFrameDlg;
class UpDateDialog;
class QTextEdit;
class QTimer;
class  SystemSetDialog: public QDialog
{
    Q_OBJECT
    
public:
    explicit SystemSetDialog(QWidget *parent = 0);
    ~SystemSetDialog();

	void FlashCfgDevPrm(void);
public slots:
    void OnClickUpdate(void);
    void OnClickRestart(void);
    void OnFirtActiveTimer(void);
	void OnClickSetSysPrm(void);
	void BackButtonClicked(void);

	void UpChooseType(UINT8 unTpye);
	void UpCanlce(void);
private:  
    Ui::SysSetDialog *ui;

	DataFrameDlg* m_pDataFrmDlg;
    CConfigPanel* m_pCfgPanel;
	MonLogFrameDlg* m_pMonLogFrmDlg;

	UpDateDialog* m_pUpDateDialog;
	bool m_bUpdateFlg;
	UINT8 m_unTestUpSce;
	bool m_ShowUpDateDlgFlg;
	
    void AddDataFrmUI(void);
	void AddOperSetFrmUI(void);
    void AddConfigFrmUI(void);
    void InitPourTestData(void);
    void GetSystemTime(DateTime& dateTime);
	void FlashCompanyInfo(void);
    QTextEdit*  m_pTextEdit;
    QTimer*  m_pUpdTimer;
	QPushButton *backButton;

	UINT8   m_unClickNum;
	UINT8   m_unReSetPrmFlag;
	UINT8   m_unCheckNetNum;
	UINT8   m_unRunState;
	bool    m_bFlashPicFlg;
	UINT8   m_unDlyFlashInfoSce;
	bool    m_bFlashInfoFlag;
};

#endif // MAINDIALOG_H
