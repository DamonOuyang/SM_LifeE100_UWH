#ifndef CONFIGBASICFRAME_H
#define CONFIGBASICFRAME_H
#include "includes.h"
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class ConfigBasicFrame;
}

class ConfigBasicFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ConfigBasicFrame(QWidget *parent = 0);
    ~ConfigBasicFrame();

	void OnUpdParams(void);
signals:
	  void exitLoginFlg(void);
	  
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);
	void OnClickAlarmPath(void);
	void OnClickDatePath(void);
	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);
	void OnUpdDateTime(void);
	void OnPwdModEdit(void);
	void OnExitLogin(void);

private:
    Ui::ConfigBasicFrame *ui;

	QLineEdit* m_pDataPath;
	QLineEdit* m_pAlarmPath;

	QLineEdit* m_pDataTimeEdit;
	QLineEdit* m_pMonSavTmt;
	QComboBox* m_pAlmEnFlag;
	
	QLineEdit* m_pAPumCount;
	QLineEdit* m_pVPumCount;
	QLineEdit* m_pWatCount;

    QTimer* m_pUpdTimer;
    QWidget* m_pCurLineEdit;
	bool  m_bChangeSysTmtFlag;
	DateTime ChgedSystem[2]; //修改系统时间
};

#endif // CONFIGBASICFRAME_H
