#ifndef POURCONFIGPANEL_H
#define POURCONFIGPANEL_H
#include "includes.h"
#include <QFrame>

//class QCheckBox;
//class QComboBox;
class PourConfigPanel : public QFrame
{
    Q_OBJECT
public:
    explicit PourConfigPanel(QWidget *parent = 0);
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
    QLineEdit* m_pPourUFlowA;
    QLineEdit* m_pPourLFlowA;

    QLineEdit* m_pPourUPresV;
	QLineEdit* m_pPourUSpeedV;
    QLineEdit* m_pPourUFlowV;
    QLineEdit* m_pPourLFlowV;

	QLineEdit* m_pPourUWatTmp;
	QLineEdit* m_pPourUWatLin;


    QWidget* m_pCurLineEdit;
};

#endif // BATGRPCONFIGPANEL_H
