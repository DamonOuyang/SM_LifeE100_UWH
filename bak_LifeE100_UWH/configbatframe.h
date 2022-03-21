#ifndef CONFIGBATFRAME_H
#define CONFIGBATFRAME_H

#include <QFrame>
#include <QComboBox>
#include <QLineEdit>
#include "includes.h"


namespace Ui {
class configBatFrame;
}

class configBatFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configBatFrame(QWidget *parent = 0);
    ~configBatFrame();
	void OnUpdParams(BqBatBascInfo *batDevData);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);

private:
    Ui::configBatFrame *ui;
	QLineEdit* m_pDevID;
	QComboBox* m_pDevEnabled;

    QLineEdit* m_pBatSoc;
    QLineEdit* m_pBatVol;
    QLineEdit* m_pBatCur;
	QLineEdit* m_pBatTmp;
	QLineEdit* m_pDisChgNum;
};

#endif // CONFIGBATFRAME_H
