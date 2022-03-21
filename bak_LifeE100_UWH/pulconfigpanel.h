#ifndef PULCONFIGPANEL_H
#define PULCONFIGPANEL_H
#include "Includes.h"
#include <QFrame>

class QListWidget;
class QLineEdit;
class QComboBox;
class QListWidgetItem;
class QModelIndex;
class PulConfigPanel : public QFrame
{
	Q_OBJECT
public:
	explicit PulConfigPanel(QWidget *parent = 0);
	void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);
	void PulDevCurrentItemChanged(QListWidgetItem*pCurItem,\
								  QListWidgetItem*pPreItem);
	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);
private:
	QListWidget* m_pPulDevList;
	QLineEdit* m_pPulVal;
	QLineEdit* m_pPulFreq;
	QComboBox* m_pDevEnabled;

	void CreateDevItems(void);
	void OnItemClick(QModelIndex  qModelIndex);
	void UpdateItem(long lDevItem);
	QWidget* m_pCurLineEdit;

};

#endif // BATGRPCONFIGPANEL_H
