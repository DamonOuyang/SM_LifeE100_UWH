#ifndef CONFIGBATFRAME_H
#define CONFIGBATFRAME_H

#include <QFrame>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class configBatFrame;
}

class configBatFrame : public QFrame
{
    Q_OBJECT

public:
    explicit configBatFrame(QWidget *parent = 0);
    ~configBatFrame();
	void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);

private:
    Ui::configBatFrame *ui;
	QLineEdit* m_pDevID;
	QComboBox* m_pDevEnabled;	
};

#endif // CONFIGBATFRAME_H
