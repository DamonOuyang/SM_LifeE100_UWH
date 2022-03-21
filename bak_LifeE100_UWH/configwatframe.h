#ifndef CONFIGWATFRAME_H
#define CONFIGWATFRAME_H
#include "includes.h"
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>


namespace Ui {
class configWatFrame;
}

class configWatFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configWatFrame(QWidget *parent = 0);
    ~configWatFrame();
	void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);

	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);
private:
	QLineEdit* m_pDevID;
	QLineEdit* m_pTmpVal;
	QComboBox* m_pDevEnabled;
	QLineEdit* m_pTmpValLimt;

	QWidget* m_pCurLineEdit;

private:
    Ui::configWatFrame *ui;
};

#endif // CONFIGWATFRAME_H
