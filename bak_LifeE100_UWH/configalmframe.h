#ifndef CONFIGALMFRAME_H
#define CONFIGALMFRAME_H
#include "includes.h"
#include <QFrame>
#include <QLineEdit>

namespace Ui {
class configAlmFrame;
}

class configAlmFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configAlmFrame(QWidget *parent = 0);
    ~configAlmFrame();
		void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);
	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);
private:

	QLineEdit* m_pAlmUPresA;
	QLineEdit* m_pAlmLPresA;
	QLineEdit* m_pAlmUTmpA;
	QLineEdit* m_pAlmUFlowA;
	QLineEdit* m_pAlmLFlowA;
	QLineEdit* m_pAlmBubblA;

	QLineEdit* m_pAlmUPresV;
	QLineEdit* m_pAlmLPresV;
	QLineEdit* m_pAlmUTmpV;
	QLineEdit* m_pAlmUFlowV;
	QLineEdit* m_pAlmLFlowV;
	QLineEdit* m_pAlmBubblV;

	QLineEdit* m_pAlmUWatTmp;
	QLineEdit* m_pAlmUWatLin;
	QLineEdit* m_pAlmLWatLin;
	QLineEdit* m_pAlmLBloodLin;


	QWidget* m_pCurLineEdit;

private:
    Ui::configAlmFrame *ui;
};

#endif // CONFIGALMFRAME_H
