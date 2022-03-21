#ifndef CONFIGARTFRAME_H
#define CONFIGARTFRAME_H
#include "includes.h"
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>


namespace Ui {
class configArtFrame;
}

class configArtFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configArtFrame(QWidget *parent = 0);
    ~configArtFrame();
	void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);

	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);

private:
    Ui::configArtFrame *ui;
	
	QLineEdit* m_pDevID;
	QLineEdit* m_pPress;
	QLineEdit* m_pSpeed;
	QComboBox* m_pDevEnabled;

	QLineEdit* m_pPressLimt;
	QLineEdit* m_pSpeedLimt;

	QWidget* m_pCurLineEdit;
};

#endif // CONFIGARTFRAME_H
