#include "dataframedlg.h"
#include "ui_DataFrame.h"
#include "includes.h"
#include <QFileSystemModel>
#include "qcustomplot.h"

#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <QtGui>
#include <QTableView>

#define MAX_CHART_TICK_COUNT    16.0
DataFrameDlg::DataFrameDlg(QWidget *parent) :
    QFrame(parent)
{
    ui = new Ui_DataFrame;
    ui->setupUi(this);
	
	m_pPressCustomPlot = NULL;
	m_pSpeedCustomPlot = NULL;
	m_pFlowCustomPlot = NULL;
	m_pTmpCustomPlot = NULL;
	m_pWatTmpCustomPlot = NULL;

    for(long lItem = 1; lItem < MAX_DATA_ITEM_COUNT; lItem++)
    {
        m_bUpdFlags[lItem] = false;
    }
    m_lItemIndex = 0;
    m_lBatIndex  = 0;
    m_unOrderColIndex = 2;//时间排序
    memset(&m_PourInfo,0,sizeof(m_PourInfo));
    AddFilesTab();
}

DataFrameDlg::~DataFrameDlg()
{
    delete ui;
}

void DataFrameDlg::AddFilesTab(void)
{
    QVBoxLayout*  pMainLayout = new QVBoxLayout();
    m_pInfoView  = new QTableView(this);
    ui->tabFiles->setLayout(pMainLayout);

    QGroupBox* pUpGrpBox  = new QGroupBox();
    QGroupBox* pDnGrpBox  = new QGroupBox();
    pMainLayout->addWidget(pUpGrpBox);
    pMainLayout->addWidget(pDnGrpBox);
    QVBoxLayout* pUpLayout = new QVBoxLayout();
    pUpGrpBox->setLayout(pUpLayout);
    pUpLayout->addWidget(m_pInfoView);
    QObject::connect(ui->dataTabWidget, \
                    SIGNAL(currentChanged(int)),\
                    this,\
                    SLOT(OnTabChanged()));

    QDialogButtonBox*  pDlgLayout = new QDialogButtonBox(Qt::Horizontal);
    QPushButton* pOpenBut = new QPushButton(tr("打开"));
    QPushButton* pDelBut  = new QPushButton(tr("删除"));
    QPushButton* pExPortBut  = new QPushButton(tr("导出"));
    QPushButton* pRfshBut = new QPushButton(tr("刷新"));
	QPushButton* pDelAllBut = new QPushButton(tr("删除全部"));
    pOpenBut->setMinimumSize(120,35);
    pDelBut->setMinimumSize(120,35);
    pExPortBut->setMinimumSize(120,35);
    pRfshBut->setMinimumSize(120,35);
	pDelAllBut->setMinimumSize(120,35);
    //pDelBut->setDisabled(true);
    //pExPortBut->setDisabled(true);
    pDlgLayout->addButton(pOpenBut,QDialogButtonBox::ActionRole);
    pDlgLayout->addButton(pDelBut,QDialogButtonBox::ActionRole);
    pDlgLayout->addButton(pExPortBut,QDialogButtonBox::ActionRole);
    pDlgLayout->addButton(pRfshBut,QDialogButtonBox::ActionRole);
	pDlgLayout->addButton(pDelAllBut,QDialogButtonBox::ActionRole);
    pDlgLayout->setCenterButtons(true);

    QVBoxLayout* pDnLayout = new QVBoxLayout();
    pDnGrpBox->setLayout(pDnLayout);
    pDnLayout->addWidget(pDlgLayout);
    pDnGrpBox->setMinimumSize(200,25);
    QObject::connect(pOpenBut, \
                     SIGNAL(clicked()),\
                     this, \
                     SLOT(OnFileOpenEx()));
    QObject::connect(pRfshBut, \
                     SIGNAL(clicked()),\
                     this, \
                     SLOT(OnReflashFiles()));

    QObject::connect(pDelBut, \
                     SIGNAL(clicked()),\
                     this, \
                     SLOT(OnDelFiles()));
    QObject::connect(pExPortBut, \
                     SIGNAL(clicked()),\
                     this, \
                     SLOT(OnExportFiles()));
	
	QObject::connect(pDelAllBut, \
				  SIGNAL(clicked()),\
				  this, \
				  SLOT(OnDelAllFiles()));

    m_pInfoView->setColumnWidth(0,400);
    QStandardItemModel* pItemModel = new QStandardItemModel(this);
    m_pInfoView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pInfoView->setModel(pItemModel);
    m_pInfoView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pInfoView->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pInfoView->setSortingEnabled(true);
    //m_pInfoView->horizontalHeader()->setClickable(true);
    m_pInfoView->horizontalHeader()->setSortIndicatorShown(true);

    m_strColNames <<"文件名"<<"开始时间"<<"结束时间"<<"记录条数"<<"停机条件"<<"分钟"<<"ID号";

    m_lColSizes[0] = 300;
    m_lColSizes[1] = 220;
    m_lColSizes[2] = 220;
    m_lColSizes[3] = 80;
	m_lColSizes[4] = 180;
    m_lColSizes[5] = 80;
    m_lColSizes[6] = 80;

    pItemModel->setHorizontalHeaderLabels(m_strColNames);
    ListFileInfos();
}

void DataFrameDlg::ListFileInfos(void)
{
    DIR *pDir;
    struct dirent *pFile;
    struct stat stFile;
    QString strPath;
    QString strFilePath;
    PourInfo pourInfo;
    QStandardItem* pNewItem;
    QStandardItemModel* pItemModel;
    long lRowIndex;
    long lColIndex;
    strPath  = qApp->applicationDirPath()+"/";
    strPath += g_devConfigInfo.basicCfgInfo.strDataPath;
    strPath += "/";
    if(!(pDir = opendir(strPath.toStdString().c_str())))
    {
        printf("Error open dir <%s>!!!\r\n",strPath.toStdString().c_str());
        return ;
    }

    pItemModel = (QStandardItemModel*)m_pInfoView->model();

    pItemModel->clear();
    pItemModel->setHorizontalHeaderLabels(m_strColNames);
    lRowIndex  = 0;
    while(NULL!=(pFile=readdir(pDir)))
    {
        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        if(0==strcmp(pFile->d_name,".")||0==strcmp(pFile->d_name,".."))
        {
            continue;
        }
        if(QString(pFile->d_name).right(4)!=QString(".DAT"))
        {
            continue;
        }
        strFilePath = strPath+QString(pFile->d_name);
        //printf("FILE:%s\r\n",strFilePath.toStdString().c_str());
        //判断该文件是否是目录，及是否已搜索了三层，这里我定义只搜索了三层目录，太深就不搜了，省得搜出太多文件
        if(stat(strFilePath.toStdString().c_str(), &stFile)>=0&&S_ISREG(stFile.st_mode))
        {
            //printf("Is TestData File!<%s>\r\n",strFilePath.toStdString().c_str());
            if(true==ReadTestInfo(strFilePath.toStdString().c_str(),&pourInfo))
            {
                lColIndex = 0;
                pNewItem = new QStandardItem(QString(pFile->d_name));
                pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

                pNewItem = new QStandardItem(DateTimeToString(&pourInfo.dtStart));
                pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

                pNewItem = new QStandardItem(DateTimeToString(&pourInfo.dtEnd));
                pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

                pNewItem = new QStandardItem(QString("%1").arg(pourInfo.unRecords));
                pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

                pNewItem = new QStandardItem(StopCodeToString(pourInfo.unStopType));
                pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

                pNewItem = new QStandardItem(QString("%1").arg(pourInfo.unTotalTime/60));
                pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

                pNewItem = new QStandardItem(QString("%1").arg(pourInfo.unSectorID));
                pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

                lRowIndex++;
            }
        }
    }
    closedir(pDir);
    for(lColIndex = 0; lColIndex < (long)pItemModel->columnCount();lColIndex++)
    {
        //lColSize = ((QAbstractItemView*)m_pInfoView)->sizeHintForColumn(lColIndex);
        m_pInfoView->setColumnWidth(lColIndex,m_lColSizes[lColIndex]);
    }
    sortByColumn(m_unOrderColIndex);
}

void DataFrameDlg::OnFileOpenEx(void)
{
    QItemSelectionModel* pSelModel = m_pInfoView->selectionModel();
    QModelIndexList listModelIndex = pSelModel->selection().indexes();
    QModelIndex selItem;
    for(long lItem = 0; lItem < listModelIndex.count();lItem++)
    {
        selItem = listModelIndex.at(lItem);
        OnFileOpen(selItem);
        break;
    }
}
void DataFrameDlg::OnReflashFiles(void)
{
    ListFileInfos();
}

void DataFrameDlg::OnDelFiles(void)
{
    QItemSelectionModel* pSelModel = m_pInfoView->selectionModel();
    QModelIndexList listModelIndex = pSelModel->selection().indexes();
    QStandardItemModel* pItemModel = (QStandardItemModel*)m_pInfoView->model();
    QModelIndex selItem;
    QStandardItem* pSelItem;
    QString strPathName;
    QString strDelCmd;
    QPushButton* pNewBut;
    QMessageBox  msgBox(this);

    for(long lItem = 0; lItem < listModelIndex.count();lItem++)
    {
        selItem  = listModelIndex.at(lItem);
        pSelItem = pItemModel->item(selItem.row(),0);

		strPathName = qApp->applicationDirPath();
		strPathName += "/";
        strPathName += g_devConfigInfo.basicCfgInfo.strDataPath;
        strPathName += "/";
        strPathName += pSelItem->text();
        msgBox.setWindowTitle("提示");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QString("是否要删除<%1>?").arg(pSelItem->text()));
        pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
        pNewBut->setMinimumSize(100,30);
        pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
        pNewBut->setMinimumSize(100,30);
        //msgBox.setMinimumSize(400,100);
        SetMessageBoxFont(&msgBox);
        if(QMessageBox::AcceptRole == msgBox.exec())
        {
            strDelCmd = QString("rm -r %1").arg(strPathName);
            SystemEx(strDelCmd.toStdString().c_str());
            ListFileInfos();
        }
        break;
    }
}

void DataFrameDlg::OnDelAllFiles(void)
{

    QString strPathName,strDelCmd;
    QPushButton* pNewBut;
    QMessageBox  msgBox(this);
	
	strPathName = qApp->applicationDirPath();
	strPathName += "/";
	strPathName += g_devConfigInfo.basicCfgInfo.strDataPath;

    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("是否想删除所有数据?");
    pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(100,30);
    pNewBut = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
    pNewBut->setMinimumSize(100,30);
    //msgBox.setMinimumSize(400,100);
    SetMessageBoxFont(&msgBox);
    if(QMessageBox::AcceptRole == msgBox.exec())
    {
        strDelCmd = QString("rm -r %1/*").arg(strPathName);
        SystemEx(strDelCmd.toStdString().c_str());
        ListFileInfos();
    }	
}


void DataFrameDlg::OnExportFiles(void)
{
    QString strPathName;
    QString strExportCmd;
    QPushButton* pNewBut;
    QMessageBox  msgBox(this);

    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(QString("拷贝数据成功"));
    pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(100,30);

    QFileInfo  dir("/udisk/Data");
    if(!dir.isDir())
    {
        msgBox.setWindowTitle("提示");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("未发现U盘中Data文件夹，请检查U盘!");
        SetMessageBoxFont(&msgBox);
        msgBox.exec();
        return;
    }
    g_bDataCopyFlag = true;
    //灌注数据路劲
	strPathName = qApp->applicationDirPath();
	strPathName += "/";
    strPathName += g_devConfigInfo.basicCfgInfo.strDataPath;
    strPathName += "/*";

    strExportCmd = QString("cp -r %1 /udisk/Data/").arg(strPathName);
    SystemEx(strExportCmd.toStdString().c_str());
	SystemEx("sync");

    //告警数据路劲
	strPathName = qApp->applicationDirPath();
	strPathName += "/";
    strPathName += "Log";
    strPathName += "/*";
    strExportCmd = QString("cp -r %1 /udisk/Log/").arg(strPathName);
    SystemEx(strExportCmd.toStdString().c_str());
	SystemEx("sync");

    //操作日志数据路劲
	strPathName = qApp->applicationDirPath();
	strPathName += "/";
    strPathName += "OperLog";
    strPathName += "/*";
    strExportCmd = QString("cp -r %1 /udisk/OperLog/").arg(strPathName);
    SystemEx(strExportCmd.toStdString().c_str());
	SystemEx("sync");

    //监控日志数据路劲
	strPathName = qApp->applicationDirPath();
	strPathName += "/";
    strPathName += "MonLog";
    strPathName += "/*";
    strExportCmd = QString("cp -r %1 /udisk/MonLog/").arg(strPathName);
    SystemEx(strExportCmd.toStdString().c_str());
	SystemEx("sync");

	//下位机日志数据路劲
	strPathName = qApp->applicationDirPath();
	strPathName += "/";
    strPathName += "SlaveInfo";
    strPathName += "/*";
    strExportCmd = QString("cp -r %1 /udisk/SlaveInfo/").arg(strPathName);
    SystemEx(strExportCmd.toStdString().c_str());
	SystemEx("sync");
	//sleep(30);
    g_bDataCopyFlag = false;
	SetMessageBoxFont(&msgBox);
    msgBox.exec();
}


void DataFrameDlg::OnFileOpen(const QModelIndex& modelIndex)
{
    QStandardItemModel* pItemModel = (QStandardItemModel*)m_pInfoView->model();
    QStandardItem* pSelItem = pItemModel->item(modelIndex.row(),0);

	m_strFilePath = qApp->applicationDirPath();
	m_strFilePath += "/";
    m_strFilePath += g_devConfigInfo.basicCfgInfo.strDataPath;
    m_strFilePath += "/";
    m_strFilePath += pSelItem->text();
    if(ReadDataFrmFile()>0)
    {
        for(long lItem = 1; lItem < MAX_DATA_ITEM_COUNT; lItem++)
        {
            m_bUpdFlags[lItem] = true;
        }
        m_lItemIndex = 0;
        ui->dataTabWidget->setCurrentWidget(ui->tabPress);
        //OnTabChanged();
    }
}
QCustomPlot* DataFrameDlg::AddGraphs(QCustomPlot* pCustomPlot,QWidget* pParentWin,long lTabIndex)
{
    double dbTickStep = 100;
    if(NULL==pCustomPlot)
    {
        pCustomPlot = new QCustomPlot();
        QHBoxLayout*  mainLayout = new QHBoxLayout();
        mainLayout->addWidget(pCustomPlot);
        pParentWin->setLayout(mainLayout);

        if(0==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("泵压力(mmHg)");
        }
        else if(1==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("泵转速(RPM)");
        }
        else if(2==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("泵流量(ml)");
        }		
        else if(3==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("血温度(℃)");
        }
        else if(4==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("水温度(℃)");
        }
        pCustomPlot->addGraph();
        QPen qPen(QColor(255,0,0));
        qPen.setWidth(3);
        pCustomPlot->graph(0)->setPen(qPen);

        pCustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        pCustomPlot->xAxis->setDateTimeFormat("hh:mm:ss");
        pCustomPlot->xAxis->setTickLabelRotation(90);
        pCustomPlot->xAxis->setAutoTickStep(false);
        pCustomPlot->xAxis->setTickStep(dbTickStep);
        pCustomPlot->axisRect()->setupFullAxesBox();
    }
    else
    {
        pCustomPlot->graph(0)->clearData();
    }

    QDateTime preDateTime;
    QDateTime curDateTime;

    unsigned int lItemIndex;//long
    double dbMaxStrVol = 0;
    double dbMinStrVol = 10000.0;
    double dbTmpVal = 0;
    QVector<double> x(m_PourInfo.unRecords), y(m_PourInfo.unRecords);
    lItemIndex = 0;

    while(lItemIndex<m_PourInfo.unRecords)
    {
        curDateTime = DateTimeToQDateTime(&m_DataTests[lItemIndex].dtSample,true);
        curDateTime = curDateTime.toLocalTime();
        if(0 == lItemIndex)
        {
            preDateTime = DateTimeToQDateTime(&m_DataTests[lItemIndex].dtSample,true);
            //preDateTime = preDateTime.toLocalTime();
        }
        x[lItemIndex] = (curDateTime.toMSecsSinceEpoch()-preDateTime.toMSecsSinceEpoch())/1000.0;
		if(0==lTabIndex)
        {
            dbTmpVal = abs(m_DataTests[lItemIndex].unAPrssVal);
            dbTmpVal = dbTmpVal/10.0;
        }
        else if(1 == lTabIndex)
        {
            dbTmpVal = abs(m_DataTests[lItemIndex].unASpeeVal);
        }
        else if(2 == lTabIndex)
        {
            dbTmpVal = m_DataTests[lItemIndex].unAFlowVal;
        }
        else if(3==lTabIndex)
        {
            dbTmpVal = m_DataTests[lItemIndex].unATmpVal;
            dbTmpVal = dbTmpVal/10.0;
        }
        else if(4==lTabIndex)
        {
            dbTmpVal = m_DataTests[lItemIndex].unWatTmpVal;
            dbTmpVal = dbTmpVal/10.0;
        }

        y[lItemIndex] = dbTmpVal;
		
        if(dbMaxStrVol<dbTmpVal)
        {
            dbMaxStrVol = dbTmpVal;
        }
        if(dbMinStrVol >dbTmpVal)
        {
            dbMinStrVol = dbTmpVal;
        }
        
		lItemIndex++;
    }
    if(m_PourInfo.unRecords>=1)
    {
        dbTickStep = 1;
        while((x[lItemIndex-1]/dbTickStep)>MAX_CHART_TICK_COUNT)
        {
            dbTickStep++;
        }
    }
	//pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    pCustomPlot->xAxis->setTickStep(dbTickStep);
    pCustomPlot->graph(0)->setData(x, y);
    pCustomPlot->xAxis->setRange(x[0], x[lItemIndex-1]+dbTickStep);
    pCustomPlot->yAxis->setRange(dbMinStrVol-10, dbMaxStrVol+10);
    pCustomPlot->replot();
    return pCustomPlot;
}

QCustomPlot* DataFrameDlg::AddGraphsEx(QCustomPlot* pCustomPlot,QWidget* pParentWin,long lTabIndex)
{
    double dbTickStep = 100;
    if(NULL==pCustomPlot)
    {
        pCustomPlot = new QCustomPlot();
        QHBoxLayout*  mainLayout = new QHBoxLayout();
        mainLayout->addWidget(pCustomPlot);
        pParentWin->setLayout(mainLayout);

        if(0==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("泵压力(mmHg)");
        }
        else if(1==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("泵转速(RPM)");
        }
        else if(2==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("泵流量(ml)");
        }		
        else if(3==lTabIndex)
        {
            pCustomPlot->yAxis->setLabel("血温度(℃)");
        }
        pCustomPlot->addGraph();
		pCustomPlot->addGraph();
        QPen qPen(QColor(255,0,0));
        qPen.setWidth(3);
        pCustomPlot->graph(0)->setPen(qPen);
	    qPen.setColor(QColor(0,0,255));
	    pCustomPlot->graph(1)->setPen(qPen);

        pCustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        pCustomPlot->xAxis->setDateTimeFormat("hh:mm:ss");
        pCustomPlot->xAxis->setTickLabelRotation(90);
        pCustomPlot->xAxis->setAutoTickStep(false);
        pCustomPlot->xAxis->setTickStep(dbTickStep);
        pCustomPlot->axisRect()->setupFullAxesBox();
    }
    else
    {
        pCustomPlot->graph(0)->clearData();
		pCustomPlot->graph(1)->clearData();
    }

    QDateTime preDateTime;
    QDateTime curDateTime;

    unsigned int lItemIndex;//long
    double dbMaxStrVol = 0;
    double dbMinStrVol = 10000.0;
    double dbTmpValA = 0;
	double dbTmpValV = 0;
	
	double dbMaxVal = 0;//纵坐标高
	double dbMinValV = 0;

    QVector<double> x(m_PourInfo.unRecords), y(m_PourInfo.unRecords), z(m_PourInfo.unRecords);
    lItemIndex = 0;

    while(lItemIndex<m_PourInfo.unRecords)
    {
        curDateTime = DateTimeToQDateTime(&m_DataTests[lItemIndex].dtSample,true);
        curDateTime = curDateTime.toLocalTime();
        if(0 == lItemIndex)
        {
            preDateTime = DateTimeToQDateTime(&m_DataTests[lItemIndex].dtSample,true);
            //preDateTime = preDateTime.toLocalTime();
        }
        x[lItemIndex] = (curDateTime.toMSecsSinceEpoch()-preDateTime.toMSecsSinceEpoch())/1000.0;
		if(0==lTabIndex)
        {
            dbTmpValA = abs(m_DataTests[lItemIndex].unAPrssVal);
            dbTmpValA = dbTmpValA/10.0;
            dbTmpValV = abs(m_DataTests[lItemIndex].unVPrssVal);
            dbTmpValV = dbTmpValV/10.0;
            //dbTmpValV = dbTmpValA+1.5;
        }
        else if(1 == lTabIndex)
        {
            dbTmpValA = abs(m_DataTests[lItemIndex].unASpeeVal);
			dbTmpValV = abs(m_DataTests[lItemIndex].unVSpeeVal);
			//dbTmpValV = dbTmpValA+100;
        }
        else if(2 == lTabIndex)
        {
            dbTmpValA = m_DataTests[lItemIndex].unAFlowVal;
			dbTmpValV = m_DataTests[lItemIndex].unVFlowVal;
			//dbTmpValV = dbTmpValA+1;
        }
        else if(3==lTabIndex)
        {
            dbTmpValA = m_DataTests[lItemIndex].unATmpVal;
            dbTmpValA = dbTmpValA/10.0;
            dbTmpValV = m_DataTests[lItemIndex].unVTmpVal;
            dbTmpValV = dbTmpValV/10.0;
            //dbTmpValV = dbTmpValA+1.8;
        }

        y[lItemIndex] = dbTmpValA;
		z[lItemIndex] = dbTmpValV;

		
		if(dbTmpValA >= dbTmpValV)
			dbMaxVal = dbTmpValA;
		else
			dbMaxVal = dbTmpValV;
		
        if(dbMaxStrVol<dbMaxVal)
        {
            dbMaxStrVol = dbMaxVal;
        }

		if(dbTmpValA < dbTmpValV)
			dbMaxVal = dbTmpValA;
		else
			dbMaxVal = dbTmpValV;
        if(dbMinStrVol >dbMaxVal)
        {
            dbMinStrVol = dbMaxVal;
        }
        
		lItemIndex++;
    }
    if(m_PourInfo.unRecords>=1)
    {
        dbTickStep = 1;
        while((x[lItemIndex-1]/dbTickStep)>MAX_CHART_TICK_COUNT)
        {
            dbTickStep++;
        }
    }
	//pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    pCustomPlot->xAxis->setTickStep(dbTickStep);
    pCustomPlot->graph(0)->setData(x, y);
	pCustomPlot->graph(1)->setData(x, z);
    pCustomPlot->xAxis->setRange(x[0], x[lItemIndex-1]+dbTickStep);
    pCustomPlot->yAxis->setRange(dbMinStrVol-10, dbMaxStrVol+10);
    pCustomPlot->replot();
    return pCustomPlot;
}


long  DataFrameDlg::ReadDataFrmFile(void)
{
    QFile qFile(m_strFilePath);
    qFile.open(QIODevice::ReadOnly);
    QDataStream readStream(&qFile);

    long   lTestDataSize;
    ulong  lItemIndex;
    lTestDataSize = sizeof(PourInfo);
    readStream.readRawData((char*)&m_PourInfo,sizeof(PourInfo));
    lItemIndex = 0;
	/*
	printf("Open File----%s \r\n",m_strFilePath.toStdString().c_str());
    printf("Recs:%lu\r\n",m_PourInfo.unRecords);
    printf("StopCode:%u\r\n",m_PourInfo.unStopType);
   */
    if(m_PourInfo.unRecords>MAX_DATA_REC_COUNT+1000)
    {
        m_PourInfo.unRecords = MAX_DATA_REC_COUNT+1000;
        QMessageBox msgBox(this);
        ShowInfo(&msgBox,"灌注记录太多，目前只支持10000记录显示","提示",QMessageBox::Information);
    }
    while(!readStream.atEnd()&&lItemIndex<m_PourInfo.unRecords)
    {
        lTestDataSize = sizeof(PourData);
        readStream.readRawData((char*)&m_DataTests[lItemIndex],lTestDataSize);
        lItemIndex++;
    }
    return lItemIndex;
}


void DataFrameDlg::OnTabChanged(void)
{
    if(m_PourInfo.unRecords>0)
    {
        if(false==m_bUpdFlags[ui->dataTabWidget->currentIndex()])
        {
            return;
        }
        m_bUpdFlags[ui->dataTabWidget->currentIndex()] = false;
        if(1==ui->dataTabWidget->currentIndex())
        {
			m_pPressCustomPlot = AddGraphsEx(m_pPressCustomPlot,ui->tabPress,0);
        }
        else if(2==ui->dataTabWidget->currentIndex())
        {
			m_pSpeedCustomPlot = AddGraphsEx(m_pSpeedCustomPlot,ui->tabSpeed,1);
        }
        else if(3==ui->dataTabWidget->currentIndex())//流量曲线
        {
            m_pFlowCustomPlot = AddGraphsEx(m_pFlowCustomPlot,ui->tabFlow,2);
        }		
        else if(4==ui->dataTabWidget->currentIndex())
        {
            m_pTmpCustomPlot = AddGraphsEx(m_pTmpCustomPlot,ui->tabPumTmp,3);
        }
        else if(5==ui->dataTabWidget->currentIndex())
        {
			m_pWatTmpCustomPlot = AddGraphs(m_pWatTmpCustomPlot,ui->tabWatTmp,4);
        }
        else if(6==ui->dataTabWidget->currentIndex())
        {
            ShowTestDetail();
        }
    }
}


void DataFrameDlg::ShowTestDetail(void)
{
    QStandardItemModel* pItemModel;
    QStandardItem* pNewItem;
    QStringList strColNames;
    ulong lColIndex;
    ulong lRowIndex;
	//ulong lRowIndexV;
	//ulong lRowIndexA;
	long unlColSizes[FILE_COL_ITEMS];

    ui->dataTabWidget->setCursor(Qt::WaitCursor);
    strColNames <<"采样时间"<<"A类型"<<"A压力设值"<<"A压力"<<"A转速设值"<<"A转速"<<"A流量"<<"A温度" \
		                    <<"V类型"<<"V压力设值"<<"V压力"<<"V转速设值"<<"V转速"<<"V流量"<<"V温度"\
		                    <<"水温设值"<<"水温"<<"水位";

	unlColSizes[0] = 220;
	unlColSizes[1]   = 80;unlColSizes[2] = 90;unlColSizes[3]  = 60;
	unlColSizes[4]   = 90;unlColSizes[5] = 80;unlColSizes[6]  = 60;unlColSizes[7] = 60;
    unlColSizes[8]   = 80;unlColSizes[9] = 90;unlColSizes[10] = 60;
	unlColSizes[11] = 90;unlColSizes[12] = 80;unlColSizes[13] = 60;unlColSizes[14] = 60;
	unlColSizes[15] = 80;unlColSizes[16] = 60;unlColSizes[17] = 60;

	if(NULL == m_pTblViewTestDetail)
    {
        m_pTblViewTestDetail = new QTableView(this);
        m_pTblViewTestDetail->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QGridLayout* pGridLayout = new QGridLayout();
        pGridLayout->addWidget(m_pTblViewTestDetail,0,0);
        ui->tabDetail->setLayout(pGridLayout);
        pItemModel = new QStandardItemModel(this);
        m_pTblViewTestDetail->setModel(pItemModel);
		
    }
    else
    {
        pItemModel = (QStandardItemModel*)m_pTblViewTestDetail->model();
    }
    pItemModel->clear();
	/*
    long lMaxColCount = 1;
    //pItemModel->setColumnCount(lMaxColCount);
    for(long lColItem = 0; lColItem < lMaxColCount; lColItem++)
    {
        strColNames.append(QString("%1").arg(lColItem+1,3,10,QLatin1Char('0')));
    }*/

    pItemModel->setHorizontalHeaderLabels(strColNames);
	
    for(lRowIndex = 0; lRowIndex < m_PourInfo.unRecords; lRowIndex++)
    {
        lColIndex = 0;
		//lRowIndexV = lRowIndex*2+1;
		//lRowIndexA = lRowIndex*2;
        pNewItem = new QStandardItem(DateTimeToString(&m_DataTests[lRowIndex].dtSample));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
		
        pNewItem = new QStandardItem(DataTypeToString(m_DataTests[lRowIndex].unADataType));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unAPrssSet,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unAPrssVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unASpeeSet,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unASpeeVal,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unAFlowVal,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unATmpVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

        pNewItem = new QStandardItem(DataTypeToString(m_DataTests[lRowIndex].unVDataType));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);		
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unVPrssSet,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
	    pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unVPrssVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);	
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unVSpeeSet,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
	    pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unVSpeeVal,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);	
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unVFlowVal,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);	
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unVTmpVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unWatTmpSet,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);
        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unWatTmpVal,10,1));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

        pNewItem = new QStandardItem(ValueToString(m_DataTests[lRowIndex].unWatLine,1,0));
        pItemModel->setItem(lRowIndex ,lColIndex++, pNewItem);

    }
    //ulong lColSize;
    
    for(lColIndex = 0; lColIndex < (unsigned int)pItemModel->columnCount();lColIndex++)//long
    {
        //lColSize = ((QAbstractItemView*)m_pTblViewTestDetail)->sizeHintForColumn(lColIndex);
        m_pTblViewTestDetail->setColumnWidth(lColIndex,unlColSizes[lColIndex]);
		//printf("--------------------%lu------------------\r\n",lColIndex);
    }
    ui->dataTabWidget->setCursor(Qt::ArrowCursor);
}

void DataFrameDlg::sortByColumn(int column)
{
    QStandardItemModel* pItemModel = (QStandardItemModel*)m_pInfoView->model();
    bool ascending = (m_pInfoView->horizontalHeader()->sortIndicatorSection()==column&& m_pInfoView->horizontalHeader()->sortIndicatorOrder()==Qt::DescendingOrder);
    Qt::SortOrder order = ascending ? Qt::AscendingOrder : Qt::DescendingOrder;
    m_pInfoView->horizontalHeader()->setSortIndicator(column, order);
    pItemModel->sort(column, order);
}
