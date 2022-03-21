#ifndef DATAFRAMEDLG_H
#define DATAFRAMEDLG_H

#define  MAX_DATA_ITEM_COUNT 7

#define  REAL_CAP_TYPE      0x00//实际容量
#define  LEFT_CAP_TYPE      0x01//剩余容量
#define  PRNT_CAP_TYPE      0x02//百分比容量

#include "includes.h"
#include <QFrame>
#include <QModelIndex>
#include <QString>
#include "qcustomplot.h"

#define FILE_COL_ITEMS      19

class Ui_DataFrame;
class QFileSystemModel;
class QCustomPlot;
class QScrollBar;
class QLabel;
class QComboBox;
class QTableView;
class QStringClass;
class DataFrameDlg : public QFrame
{
    Q_OBJECT
public:
    explicit DataFrameDlg(QWidget *parent = 0);
    ~DataFrameDlg();
	void ListFileInfos(void);
signals:
    
private slots:
	void OnExportFiles(void);
    void OnFileOpen(const QModelIndex& index);
    void OnFileOpenEx(void);
    void OnReflashFiles(void);
    void OnDelFiles(void);
	void OnDelAllFiles(void);
    void OnTabChanged(void);

private:
   QCustomPlot* m_pPressCustomPlot;
   QCustomPlot* m_pSpeedCustomPlot;
   QCustomPlot* m_pFlowCustomPlot;
   QCustomPlot* m_pTmpCustomPlot;
   QCustomPlot* m_pWatTmpCustomPlot;


   QTableView*  m_pTblViewTestDetail;
   Ui_DataFrame* ui;

   QTableView*   m_pInfoView;

   PourData   m_DataTests[MAX_DATA_REC_COUNT+1000];
   PourInfo   m_PourInfo;
   ulong m_lItemIndex;
   ulong m_lBatIndex;

   QString m_strFilePath;
   bool    m_bUpdFlags[MAX_DATA_ITEM_COUNT];

   QStringList m_strColNames;
   long m_lColSizes[FILE_COL_ITEMS];

   //容量估算
   UINT32      m_unOrderColIndex;


   QCustomPlot* AddGraphs(QCustomPlot* pCustomPlot,QWidget* pParentWin,long lItemIndex);
   QCustomPlot* AddGraphsEx(QCustomPlot* pCustomPlot,QWidget* pParentWin,long lTabIndex);
   long ReadDataFrmFile(void);
   void ShowTestDetail(void);
   void AddFilesTab(void);
   void sortByColumn(int column);
};

#endif // DATAFRAMEDLG_H
