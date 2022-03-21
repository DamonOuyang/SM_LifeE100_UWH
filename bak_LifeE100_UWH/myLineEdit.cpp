/************************************************************************************
*
* 文件：myLineEdit.cpp
* 功能：构建图片按钮，
* 创建：linmi
* 日期：20180420
*
*************************************************************************************/
#include <qpainter.h>
#include <qtimer.h>
#include "myLineEdit.h"
//#include "global.h"

MyLineEdit::MyLineEdit(QWidget *parent)//进
	: QLineEdit(parent)
{
	
}

MyLineEdit::~MyLineEdit()
{
	
}

void MyLineEdit::mousePressEvent(QMouseEvent * evt)
{
	emit pressed();
	QLineEdit::mousePressEvent(evt);
}

void MyLineEdit::mouseReleaseEvent(QMouseEvent * evt)
{
	emit clicked();
	QLineEdit::mouseReleaseEvent(evt);
}














