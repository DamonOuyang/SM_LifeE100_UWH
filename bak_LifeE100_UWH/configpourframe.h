#ifndef CONFIGPOURFRAME_H
#define CONFIGPOURFRAME_H
#include "includes.h"
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class configPourFrame;
}

class configPourFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configPourFrame(QWidget *parent = 0);
    ~configPourFrame();
		void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);
	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);
private:

	QLineEdit* m_pPourUPresA;
	QLineEdit* m_pPourUSpeedA;
	QLineEdit* m_pPourUTmpA;
	QLineEdit* m_pPourUFlowA;
	QLineEdit* m_pPourLFlowA;

	QLineEdit* m_pPourUPresV;
	QLineEdit* m_pPourUSpeedV;
	QLineEdit* m_pPourUTmpV;
	QLineEdit* m_pPourUFlowV;
	QLineEdit* m_pPourLFlowV;

	QLineEdit* m_pPourUWatTmp;
	QLineEdit* m_pPourUWatLin;


	QWidget* m_pCurLineEdit;

private:
    Ui::configPourFrame *ui;
};

#endif // CONFIGPOURFRAME_H
