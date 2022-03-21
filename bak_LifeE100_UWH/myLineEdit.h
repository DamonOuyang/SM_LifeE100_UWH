/************************************************************************************
*
* 文件：mylineedit.h
* 功能：图片按钮的类定义
* 创建：linmi
* 日期：20180420
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

