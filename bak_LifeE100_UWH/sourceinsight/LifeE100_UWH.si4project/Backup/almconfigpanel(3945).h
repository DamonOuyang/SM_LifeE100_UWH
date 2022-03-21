#ifndef ALMCONFIGPANEL_H
#define ALMCONFIGPANEL_H
#include "includes.h"
#include <QFrame>

//class QCheckBox;
//class QComboBox;
class AlmConfigPanel : public QFrame
{
    Q_OBJECT
public:
    explicit AlmConfigPanel(QWidget *parent = 0);
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
    QLineEdit* m_pAlmUFlowA;
    QLineEdit* m_pAlmLFlowA;
	QLineEdit* m_pAlmBubblA;

    QLineEdit* m_pAlmUPresV;
    QLineEdit* m_pAlmUFlowV;
    QLineEdit* m_pAlmLFlowV;
	QLineEdit* m_pAlmBubblV;

	QLineEdit* m_pAlmUWatTmp;
	QLineEdit* m_pAlmUWatLin;
	QLineEdit* m_pAlmLWatLin;
	QLineEdit* m_pAlmLBloodLin;


    QWidget* m_pCurLineEdit;
};

#endif // BATGRPCONFIGPANEL_H
