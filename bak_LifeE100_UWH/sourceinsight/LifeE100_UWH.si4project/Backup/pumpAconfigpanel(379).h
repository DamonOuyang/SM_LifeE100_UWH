﻿#ifndef PUMPACONFIGPANEL_H
#define PUMPACONFIGPANEL_H
#include "Includes.h"
#include <QFrame>

class QListWidget;
class QLineEdit;
class QComboBox;
class QListWidgetItem;
class QModelIndex;
class PumAConfigPanel : public QFrame
{
	Q_OBJECT
public:
	explicit PumAConfigPanel(QWidget *parent = 0);
	void OnUpdParams(void);
signals:
	
public slots:
	void OnClickOK(void);
	void OnClickCancel(void);
	void PumDevCurrentItemChanged(QListWidgetItem*pCurItem,\
								  QListWidgetItem*pPreItem);
	void confirmString(QString strIn);
	void OnFocusChanged(QWidget*old,QWidget*now);
	void OnItemEdit(void);
private:
	QListWidget* m_pPumADevList;
	QLineEdit* m_pDevID;
	QLineEdit* m_pPress;
	QLineEdit* m_pSpeed;
	QComboBox* m_pDevEnabled;

	void CreateDevItems(void);
	void OnItemClick(QModelIndex  qModelIndex);
	void UpdateItem(long lDevItem);
	QWidget* m_pCurLineEdit;

};

#endif // BATGRPCONFIGPANEL_H
