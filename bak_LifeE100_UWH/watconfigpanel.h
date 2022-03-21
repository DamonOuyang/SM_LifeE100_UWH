#ifndef WATCONFIGPANEL_H
#define WATCONFIGPANEL_H
#include "Includes.h"
#include <QFrame>

class QListWidget;
class QLineEdit;
class QComboBox;
class QListWidgetItem;
class QModelIndex;
class WatConfigPanel : public QFrame
{
	Q_OBJECT
public:
	explicit WatConfigPanel(QWidget *parent = 0);
	void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);
	void WatDevCurrentItemChanged(QListWidgetItem*pCurItem,\
								  QListWidgetItem*pPreItem);
	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);
private:
	QListWidget* m_pWatDevList;
	QLineEdit* m_pDevID;
	QLineEdit* m_pTmpVal;
	QComboBox* m_pDevEnabled;
	QLineEdit* m_pTmpValLimt;

	void CreateDevItems(void);
	void OnItemClick(QModelIndex  qModelIndex);
	void UpdateItem(long lDevItem);
	QWidget* m_pCurLineEdit;

};

#endif // BATGRPCONFIGPANEL_H
