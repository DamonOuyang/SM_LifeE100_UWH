#include "includes.h"
//#include "syszuxpinyin.h"
#include "numbkeyboarddialog.h"
#include "DevBasicConfigDlg.h"
#include <QtGui>
#include <QComboBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QGroupBox>

DevBasicConfigDlg::DevBasicConfigDlg(QWidget *parent) :
    QDialog(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint);	   //去掉标题栏

    m_pCurLineEdit = NULL;
    QHBoxLayout* pMainDlgLayout = new QHBoxLayout();
    setLayout(pMainDlgLayout);
    QGroupBox* pFormGrpBox = new QGroupBox();
    pMainDlgLayout->addWidget(pFormGrpBox);
    pFormGrpBox->setMinimumWidth(500);

    m_pDevType    = CreateComboBox(this);//设备类型
    m_pBloPumType = CreateComboBox(this);//血泵类型
    m_pArteryType = CreateComboBox(this);//动脉血泵类型
    m_pVeinType   = CreateComboBox(this);//静脉血泵类型
    m_pWatTRooType= CreateComboBox(this);//水浴类型

    for(UINT8 i = 0; i < 5; i++)
    {
	    m_pComPort[i]   = new QLineEdit(this);
		m_pBrdRate[i] = new QLineEdit(this);
    }

	m_pAPumCount = new QLineEdit(this);
	m_pVPumCount = new QLineEdit(this);
	m_pWatCount  = new QLineEdit(this);

    m_pDevType->addItem(tr("教学机"));
    m_pDevType->addItem(tr("科研机"));
    m_pDevType->addItem(tr("2"));

    m_pBloPumType->addItem(tr("1对1"));
    m_pBloPumType->addItem(tr("1对2"));

    m_pArteryType->addItem(tr("1类"));
    m_pArteryType->addItem(tr("2类"));

    m_pVeinType->addItem(tr("1类"));
    m_pVeinType->addItem(tr("2类"));

    m_pWatTRooType->addItem(tr("1类"));
    m_pWatTRooType->addItem(tr("2类"));


    long  lEditWidth = 100;
    m_pDevType->setMaximumWidth(lEditWidth);
    m_pBloPumType->setMaximumWidth(lEditWidth);
    m_pArteryType->setMaximumWidth(lEditWidth);
    m_pVeinType->setMaximumWidth(lEditWidth);
    m_pWatTRooType->setMaximumWidth(lEditWidth);
    m_pAPumCount->setMaximumWidth(lEditWidth);
    m_pVPumCount->setMaximumWidth(lEditWidth);
    m_pWatCount->setMaximumWidth(lEditWidth);

    lEditWidth+=20;
    m_pComPort[0]->setMaximumWidth(lEditWidth);
	m_pComPort[1]->setMaximumWidth(lEditWidth);
	m_pComPort[2]->setMaximumWidth(lEditWidth);
	m_pComPort[3]->setMaximumWidth(lEditWidth);
	m_pComPort[4]->setMaximumWidth(lEditWidth);
	
	m_pBrdRate[0]->setMaximumWidth(lEditWidth);
	m_pBrdRate[1]->setMaximumWidth(lEditWidth);
	m_pBrdRate[2]->setMaximumWidth(lEditWidth);
	m_pBrdRate[3]->setMaximumWidth(lEditWidth);
	m_pBrdRate[4]->setMaximumWidth(lEditWidth);


    QFormLayout *formLayout = new QFormLayout;
    QHBoxLayout* pFirstRow  = new QHBoxLayout();
    AddRowItem(pFirstRow,m_pDevType,tr("设备类型:"));
    AddRowItem(pFirstRow,m_pBloPumType,tr("血泵类型:"));
    AddRowItem(pFirstRow,m_pArteryType,tr("动脉类型:"));
    AddRowItem(pFirstRow,m_pVeinType,tr("静脉类型:"));
    AddRowItem(pFirstRow,m_pWatTRooType,tr("水浴类型:"));
    formLayout->addRow(pFirstRow);

    pFirstRow  = new QHBoxLayout();
    AddRowItem(pFirstRow,m_pAPumCount,tr("动泵数量:"));
	AddRowItem(pFirstRow,m_pVPumCount,tr("静泵数量:"));
    AddRowItem(pFirstRow,m_pWatCount,tr("水浴数量:"));
    formLayout->addRow(pFirstRow);


    QLabel *pLabel = new QLabel(tr("--设备号配置--"));
    pLabel->setMinimumSize(100,30);
    formLayout->addRow(tr(""),pLabel);
	
    pFirstRow  = new QHBoxLayout();
    AddRowItem(pFirstRow,m_pComPort[0],tr("串口 0:"));
	AddRowItem(pFirstRow,m_pComPort[1],tr("串口 1:"));
    AddRowItem(pFirstRow,m_pComPort[2],tr("串口 2:"));
	AddRowItem(pFirstRow,m_pComPort[3],tr("串口 3:"));
	AddRowItem(pFirstRow,m_pComPort[4],tr("串口 4:"));
    formLayout->addRow(pFirstRow);

    pFirstRow  = new QHBoxLayout();
    AddRowItem(pFirstRow,m_pBrdRate[0],tr("波特率:"));
	AddRowItem(pFirstRow,m_pBrdRate[1],tr("波特率:"));
    AddRowItem(pFirstRow,m_pBrdRate[2],tr("波特率:"));
	AddRowItem(pFirstRow,m_pBrdRate[3],tr("波特率:"));
	AddRowItem(pFirstRow,m_pBrdRate[4],tr("波特率:"));
    formLayout->addRow(pFirstRow);


    pFormGrpBox->setLayout(formLayout);

    QGroupBox* pButGrpBox = new QGroupBox();
    pMainDlgLayout->addWidget(pButGrpBox);
    pButGrpBox->setMinimumWidth(150);

    QHBoxLayout* pButLayout = new QHBoxLayout();
    QDialogButtonBox* pButs = new QDialogButtonBox(Qt::Vertical);
    pButLayout->addWidget(pButs);
    pButGrpBox->setLayout(pButLayout);

    QPushButton* pOkBut = new QPushButton(tr("确定"));
    pOkBut->setMinimumSize(100,30);
    QPushButton* pCancelBut = new QPushButton(tr("取消"));
    pCancelBut->setMinimumSize(100,30);
    QPushButton* pEditBut = new QPushButton(tr(INPUT_BUT_NAME));
    pEditBut->setMinimumSize(100,30);

    pButs->addButton(pOkBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pCancelBut,QDialogButtonBox::ActionRole);
    pButs->addButton(pEditBut,QDialogButtonBox::ActionRole);

    connect(pOkBut,SIGNAL(clicked()),this,SLOT(OnClickOK()));
    connect(pCancelBut,SIGNAL(clicked()),this,SLOT(OnClickCancel()));

    connect(pEditBut,SIGNAL(clicked()),this,SLOT(OnItemEdit()));

	//InitWatchdog();
    //m_pUpdTimer = new QTimer(this);
    //connect(m_pUpdTimer, SIGNAL(timeout()), this, SLOT(OnActiveTimer(void)));
    //m_pUpdTimer->start(10000);
    connect(qApp,SIGNAL(focusChanged(QWidget*, QWidget*)),this,SLOT(OnFocusChanged(QWidget*, QWidget*)));
    setWindowTitle("设备基本参数配置");


    QString strError;
    if(false==LoadDevTypeParam(strError))
    {
        //QMessageBox  msgBox(this);
		//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
        //ShowInfo(&msgBox,strError,"错误",QMessageBox::Critical);
		MessageBoxDialog msgBox(this, false);
		msgBox.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
        msgBox.SetMessLabelText(strError);
        msgBox.exec();

		
        printf("Default DevType Config\r\n");
        g_devBasicPrmCfg.unDevType = 0;//
        g_devBasicPrmCfg.unBloPumType = 0;//
        g_devBasicPrmCfg.unArteryType = 0;//
        g_devBasicPrmCfg.unVeinType = 0;   //
        g_devBasicPrmCfg.unWatTRooType  = 0;//

		g_devBasicPrmCfg.unMonSavCount = 5000;
		g_devBasicPrmCfg.unAPumCount = 1; //动脉血泵数量
		g_devBasicPrmCfg.unVPumCount = 0; //静脉血泵数量
		g_devBasicPrmCfg.unWatCount = 1;	//水浴数量
		

		strcpy(g_devBasicPrmCfg.strComPort[0],"/dev/ttyAMA1");
        strcpy(g_devBasicPrmCfg.strComPort[1],"/dev/ttyAMA2");
		strcpy(g_devBasicPrmCfg.strComPort[2],"/dev/ttyAMA3");
        strcpy(g_devBasicPrmCfg.strComPort[3],"/dev/ttyAMA4");
		strcpy(g_devBasicPrmCfg.strComPort[4],"/dev/ttyAMA5");
		g_devBasicPrmCfg.lComBrdVal[0] = 115200;
		g_devBasicPrmCfg.lComBrdVal[1] = 115200;
		g_devBasicPrmCfg.lComBrdVal[2] = 115200;
		g_devBasicPrmCfg.lComBrdVal[3] = 115200;
		g_devBasicPrmCfg.lComBrdVal[4] = 115200;		
		
    }

    m_pDevType->setCurrentIndex(g_devBasicPrmCfg.unDevType);
    m_pBloPumType->setCurrentIndex(g_devBasicPrmCfg.unBloPumType);
    m_pArteryType->setCurrentIndex(g_devBasicPrmCfg.unArteryType);
    m_pVeinType->setCurrentIndex(g_devBasicPrmCfg.unVeinType);
    m_pWatTRooType->setCurrentIndex(g_devBasicPrmCfg.unWatTRooType);
    //m_pMonSavCount->setText(QString("%1").arg(g_devBasicPrmCfg.unMonSavCount));
    m_pAPumCount->setText(QString("%1").arg(g_devBasicPrmCfg.unAPumCount));
	m_pVPumCount->setText(QString("%1").arg(g_devBasicPrmCfg.unVPumCount));
	m_pWatCount->setText(QString("%1").arg(g_devBasicPrmCfg.unWatCount));


    for(UINT8 i = 0; i < 5; i++)
    {
	    m_pComPort[i]->setText(g_devBasicPrmCfg.strComPort[i]);
		m_pBrdRate[i]->setText(QString("%1").arg(g_devBasicPrmCfg.lComBrdVal[i]));
    }

}

void DevBasicConfigDlg::OnClickOK(void)
{
    g_devBasicPrmCfg.unDevType = m_pDevType->currentIndex();
    g_devBasicPrmCfg.unBloPumType = m_pBloPumType->currentIndex();
    g_devBasicPrmCfg.unArteryType = m_pArteryType->currentIndex();
    g_devBasicPrmCfg.unVeinType   = m_pVeinType->currentIndex();
    g_devBasicPrmCfg.unWatTRooType    = m_pWatTRooType->currentIndex();
    //g_devBasicPrmCfg.unMonSavCount   = m_pMonSavCount->currentIndex();
    g_devBasicPrmCfg.unAPumCount = m_pAPumCount->text().toInt();
	if(g_devBasicPrmCfg.unAPumCount > 4)
	{
	    g_devBasicPrmCfg.unAPumCount = 4;
	}
	g_devBasicPrmCfg.unVPumCount = m_pVPumCount->text().toInt();
	if(g_devBasicPrmCfg.unVPumCount > 4)
	{
	    g_devBasicPrmCfg.unVPumCount = 4;
	}	
	g_devBasicPrmCfg.unWatCount = m_pWatCount->text().toInt();
	if(g_devBasicPrmCfg.unWatCount > 2)
	{
	    g_devBasicPrmCfg.unWatCount = 2;
	}

	/*
	g_devBasicPrmCfg.unMonSavCount = m_pMonSavCount->text().toInt();
	if(g_devBasicPrmCfg.unMonSavCount > 20000)
	{
	    g_devBasicPrmCfg.unMonSavCount = 20000;
	}
	else if(g_devBasicPrmCfg.unMonSavCount < 10)
	{
	    g_devBasicPrmCfg.unMonSavCount = 10;
	}*/

	for(UINT8 i = 0; i < 5; i++)
	{
	    strcpy(g_devBasicPrmCfg.strComPort[i],m_pComPort[i]->text().toStdString().c_str());
		g_devBasicPrmCfg.lComBrdVal[i] = m_pBrdRate[i]->text().toInt();
	}

    InitDefParam();
    QString strError;
    if(false== SaveConfigInfo(strError))
    {
        //QMessageBox  msgBox(this);
		//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
        //ShowInfo(&msgBox,strError,"错误",QMessageBox::Critical);
		MessageBoxDialog msgBox(this, false);
		msgBox.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
        msgBox.SetMessLabelText(strError);
        msgBox.exec();
    }
    else
    {
        if(false== SaveDevTypeParam(strError))
        {
            //QMessageBox  msgBox(this);
			//msgBox.setStyleSheet("background-color: rgb(38, 38, 44)");
            //ShowInfo(&msgBox,strError,"错误",QMessageBox::Critical);
			MessageBoxDialog msgBox(this, false);
			msgBox.setGeometry(QRect(0, 40, SET_VAL_DLG_W, SET_VAL_DLG_H));
	        msgBox.SetMessLabelText(strError);
	        msgBox.exec();            
        }
    }
    done(QDialog::Accepted);

	//SystemEx("sh /mnt/PowerSystemMon/InitDef.sh");
}
void DevBasicConfigDlg::OnClickCancel(void)
{
    done(QDialog::Rejected);
}


void DevBasicConfigDlg::confirmString(QString strIn)
{
    if(NULL != m_pCurLineEdit)
    {
        ((QLineEdit*)m_pCurLineEdit)->setText(strIn);
    }
}
void DevBasicConfigDlg::OnItemEdit(void)
{
    if(m_pCurLineEdit==m_pBrdRate[0]||\
	   m_pCurLineEdit==m_pBrdRate[1]||\
	   m_pCurLineEdit==m_pBrdRate[2]||\
	   m_pCurLineEdit==m_pBrdRate[3]||\
	   m_pCurLineEdit==m_pBrdRate[4]||\
	   m_pCurLineEdit==m_pAPumCount ||\
	   m_pCurLineEdit==m_pVPumCount ||\
	   m_pCurLineEdit==m_pWatCount)
    {
        //SyszuxPinyin dlgInputPanel(this);
        NumbKeyboardDialog dlgInputPanel(this);

        dlgInputPanel.SetDefaultVal(((QLineEdit*)m_pCurLineEdit)->text());
        dlgInputPanel.setWindowModality(Qt::ApplicationModal);
        dlgInputPanel.exec();
    }
}

void DevBasicConfigDlg::OnFocusChanged(QWidget * old, QWidget * now)
{
    if(m_pBrdRate[0] == old ||\
       m_pBrdRate[1] == old ||\
       m_pBrdRate[2] == old ||\
       m_pBrdRate[3] == old ||\
       m_pBrdRate[4] == old ||\
       m_pAPumCount  == old ||\
       m_pVPumCount  == old ||\
       m_pWatCount   == old )
    {
        m_pCurLineEdit = old;
    }
}

void DevBasicConfigDlg::OnActiveTimer(void)
{
    //SetWatchdog();
}


