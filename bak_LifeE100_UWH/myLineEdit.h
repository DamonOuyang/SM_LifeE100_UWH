/************************************************************************************
*
* �ļ���mylineedit.h
* ���ܣ�ͼƬ��ť���ඨ��
* ������linmi
* ���ڣ�20180420
*
*************************************************************************************/

#ifndef MY_LINEEDIT_H
#define MY_LINEEDIT_H


#include <QMouseEvent>
#include <qlineedit.h>

class MyLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	MyLineEdit(QWidget *parent=0);
	~MyLineEdit();

protected:
	void mousePressEvent(QMouseEvent * );
	void mouseReleaseEvent(QMouseEvent * evt);
signals:
	void pressed();
	void released();
	void clicked();

	
};


#endif // MY_LINEEDIT_H

