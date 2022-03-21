#ifndef CONFIGVEIFRAME_H
#define CONFIGVEIFRAME_H
#include "includes.h"
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>


namespace Ui {
class configVeiFrame;
}

class configVeiFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configVeiFrame(QWidget *parent = 0);
    ~configVeiFrame();
	void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);

	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);

private:
    Ui::configVeiFrame *ui;
	
	QLineEdit* m_pDevID;
	QLineEdit* m_pPress;
	QLineEdit* m_pSpeed;
	QComboBox* m_pDevEnabled;

	QLineEdit* m_pPressLimt;
	QLineEdit* m_pSpeedLimt;

	QWidget* m_pCurLineEdit;	
};

#endif // CONFIGVEIFRAME_H
