#ifndef MONLOGFRAME_H
#define MONLOGFRAME_H

#include <QFrame>
#include <QLineEdit>
#include "includes.h"

namespace Ui {
class MonLogFrame;
}

class MonLogFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MonLogFrame(QWidget *parent = 0);
    ~MonLogFrame();

private:
    Ui::MonLogFrame *ui;

	//QTableView*  m_pTblViewTestDetail;
    //QComboBox*    m_pLogComboBox;
    UINT32      m_unOrderColIndex;
    char       m_readLogData[100];
    bool       m_OpenOperLogFlag;
    UINT8      m_unWidgetFlag;
    UINT16     m_unLogMovFlag;
    UINT16     m_unLogNum;
    UINT16     m_unCurPar;

	//基本配置日志
	QWidget*   m_wBascWidget[2];
	QLineEdit* m_pLatBascSite;
	QLineEdit* m_pLatBascType;
	QLineEdit* m_pBascTime;
	
	QLineEdit* m_pBascAlm[2];
	QLineEdit* m_pBascSavTmt[2];
	QLineEdit* m_pSysTime[2];
	//void CreateBascLogWidget(void);
	//void ShowBascLogWidget(bool tFlag);

};

#endif // MONLOGFRAME_H
