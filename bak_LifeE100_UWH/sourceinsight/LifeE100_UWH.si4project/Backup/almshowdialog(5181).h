#ifndef ALMSHOWDIALOG_H
#define ALMSHOWDIALOG_H

#include "Includes.h"
#include <QDialog>
#include <QCloseEvent>


namespace Ui {
class AlmShowDialog;
}

class QTableView;
class QDialogButtonBox;
class QTabWidget;
class QStandardItemModel;
class AlmShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlmShowDialog(QWidget *parent = 0);
    ~AlmShowDialog();
	void closeEvent(QCloseEvent *event);
public slots:
	void OnClickOK(void);


private:
    long m_lColSizes[6];
    QStringList m_strColNames;
    QTableView* m_pInfoView;
    QTableView* m_pRTAlmTabView;
    QStandardItemModel* m_pRTItemModel;
    QStandardItemModel* m_pAlmItemModel;

    bool m_bFreeFlag;


    long m_lFileDataPos;
    long m_lRowIndex;
    QString  m_strFilePath;

    //QTabWidget* m_pTabWidget;
    QDialogButtonBox *m_pButBox;
  
    //QWidget* m_pDataAlmTab;

    void AddDataAlarmTab(void);
    void AddRTAlarmTab(void);
    void ShowAlarmInfos(void);
    void ReadAlmFileInfo(void);
    void AddAlmItem(AlmItem* pAlmItem);
    //QString AlmIDToName(UINT8 unAlmID);
    //QString AlmFlagToString(UINT8 unAlmFlag);
	//QString AlmTmtIDToName(UINT8 unAlmObjID);
    void UpDateRTAlmInfos(void);
    void AddRLAlmItem(UINT32 unRowIndex,QString strItemName,QString strItemVal,QString strAlmVal);
    void ReleaseAll();	

private:
    Ui::AlmShowDialog *ui;
};

#endif // ALMSHOWDIALOG_H
