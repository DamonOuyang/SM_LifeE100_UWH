#ifndef MONLOGFRAMEDLG_H
#define MONLOGFRAMEDLG_H

//#define  MAX_DATA_ITEM_COUNT 2


#define  REAL_CAP_TYPE      0x00//实际容量
#define  LEFT_CAP_TYPE      0x01//剩余容量
#define  PRNT_CAP_TYPE      0x02//百分比容量

#include "Includes.h"
#include <QFrame>
#include <QModelIndex>
#include <QString>
#include "qcustomplot.h"

#define FILE_COL_ITEMS      19

class Ui_LogFrame;
class QFileSystemModel;
class QCustomPlot;
class QScrollBar;
class QLabel;
class QComboBox;
class QTableView;
class QStringClass;
class MonLogFrameDlg : public QFrame
{
    Q_OBJECT
public:
    explicit MonLogFrameDlg(QWidget *parent = 0);
    ~MonLogFrameDlg();
	void ShowTestDetail(void);
signals:
    
private slots:
	void FlashMonLogData(void);

    void OnOpenFirst(void);
    void OnOpenLast(void);
    void OnOpenNext(void);
    void OnOpenEnd(void);
	void OnDelAllFile(void);
private:
   QTableView*  m_pTblViewTestDetail;
   Ui_LogFrame* ui;

   QComboBox*    m_pLogComboBox;
   
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
   

   //告警配置日志
   QWidget*   m_wAlmWidget[2];
   QLineEdit* m_pBefAlmTime;
   QLineEdit* m_pLatAlmSite;
   QLineEdit* m_pLatAlmType;

   QLineEdit* m_pAlmUPresA[2];
   QLineEdit* m_pAlmUTmpA[2];
   QLineEdit* m_pAlmUFlowA[2];
   QLineEdit* m_pAlmLFlowA[2];
   QLineEdit* m_pAlmBubblA[2];
   
   QLineEdit* m_pAlmUPresV[2];
   QLineEdit* m_pAlmUTmpV[2];
   QLineEdit* m_pAlmUFlowV[2];
   QLineEdit* m_pAlmLFlowV[2];
   QLineEdit* m_pAlmBubblV[2];
   
   QLineEdit* m_pAlmUWatTmp[2];
   QLineEdit* m_pAlmUWatLin[2];
   QLineEdit* m_pAlmLWatLin[2];
   QLineEdit* m_pAlmLBloodLin[2];


   //灌注配置日志
   QWidget*   m_wPourWidget[2];
   QLineEdit* m_pBefPourTime;
   QLineEdit* m_pLatPourSite;
   QLineEdit* m_pLatPourType;

   QLineEdit* m_pPourUPresA[2];
   QLineEdit* m_pPourUSpeeA[2];
   QLineEdit* m_pPourUFlowA[2];
   QLineEdit* m_pPourLFlowA[2];
   QLineEdit* m_pPourUTmpA[2];
   
   QLineEdit* m_pPourUPresV[2];
   QLineEdit* m_pPourUSpeeV[2];
   QLineEdit* m_pPourUFlowV[2];
   QLineEdit* m_pPourLFlowV[2];
   QLineEdit* m_pPourUTmpV[2];
   
   QLineEdit* m_pPourUWatTmp[2];
   QLineEdit* m_pPourUWatLin[2];


   //水浴模块配置日志
   QWidget*   m_wWatWidget[2];
   QLineEdit* m_pBefWatTime;
   QLineEdit* m_pLatWatSite;
   QLineEdit* m_pLatWatType;

   QLineEdit* m_pWatEnFlag[2];  //使用状态
   QLineEdit* m_pWatTmpVal[2];	//设置温度

   //泵模块配置日志
   QWidget*   m_wPumWidget[2];
   QLineEdit* m_pBefPumTime;
   QLineEdit* m_pLatPumSite;
   QLineEdit* m_pLatPumType;

   QLineEdit* m_pPumEnFlag[2];  //使用状态
   QLineEdit* m_pPumPreeVal[2];	//设置泵压力
   QLineEdit* m_pPumSpeeVal[2];	//设置泵转速


   //遥控操作日志
   QWidget*   m_wCtlWidget[2];
   QLineEdit* m_pBefCtlTime;
   QLineEdit* m_pLatCtlSite;
   QLineEdit* m_pLatCtlType;

   QLineEdit* m_pOperType[2];	//操作类型 1启动，0停止
   QLineEdit* m_pResult[2];		//操作结果 1成功，2失败 0无


   QTimer*  m_pUpdTimer;


   void ShowOperLog(void);
   void sortByColumn(int column);
   void ShowOperLogData(void);
   void SetTextShowColor(QLineEdit* pLineEdit, UINT32 unNmb1, UINT32 unNmb2);
   QString GetEnFlag(UINT8 enFlag);
   QString GetStite(UINT8 stite);
   QString GetIpFlag(UINT8 IpFlag);
   void HideOrShowWidget(bool tFlag);
   void ShowSite(UINT16 site);
   QString GetOperResult(UINT8 result, UINT8 unLogType);
   QString GetOperType(UINT8 type, UINT8 unLogType);
   
   void CreateBascLogWidget(void);
   void ShowBascLogWidget(bool tFlag);
   
   void CreateAlmLogWidget(void);
   void ShowAlmLogWidget(bool tFlag);

   void CreatePourLogWidget(void);
   void ShowPourLogWidget(bool tFlag);

   void CreateWatLogWidget(void);
   void ShowWatLogWidget(bool tFlag);

   void CreatePumLogWidget(void);
   void ShowPumLogWidget(bool tFlag);

   void CreateCtlLogWidg(void);
   void ShowCtlLogWidg(bool tFlag);
};

#endif // DATAFRAMEDLG_H
