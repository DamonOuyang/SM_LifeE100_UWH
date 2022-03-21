
#include "includes.h"
#include "fcntl.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <QtGui>
#include <QFile>
#include <QComboBox>
#include <QListView>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>

#define VERSION_INFO        "V1.1.0.0"
#define DEV_INIT_FLAG       0xAA55
#define FILE_LAST_VER_NUM   0x00010000
#define MAX_CO_INFO_SIZE    2000



QString ValueToString(int lValue,int lFactScale,int lDotNum)
{
    QString strInt;
    QString strFrt;
    int tmpVal = 0;
    if(lValue >= 0)
    {
        if(0==lDotNum)
        {
            strInt = QString("%1").arg(lValue/lFactScale);
        }
        else
        {
            strInt = QString("%1.").arg(lValue/lFactScale);
            strFrt = QString("%1").arg(lValue%lFactScale,lDotNum,10,QLatin1Char('0'));
        }
    }
    else
    {
        tmpVal = abs(lValue);
        if(0==lDotNum)
        {
            strInt = QString("-%1").arg(tmpVal/lFactScale);
        }
        else
        {
            strInt = QString("-%1.").arg(tmpVal/lFactScale);
            strFrt = QString("%1").arg(tmpVal%lFactScale,lDotNum,10,QLatin1Char('0'));
        }
    }
    return QString(strInt+strFrt);
}

QDateTime DateTimeToQDateTime(DateTime* pdtValue,bool bTimeFlag)
{
    QDateTime  qDateTime;
    if(true== bTimeFlag)
    {
        qDateTime = QDateTime(QDate((int)(pdtValue->unYear+2000),\
                               (int)pdtValue->unMonth,\
                               (int)pdtValue->unDay),\
                         QTime((int)pdtValue->unHour,\
                               (int)pdtValue->unMinute,\
                               (int)pdtValue->unSecond));
    }
    else
    {
        qDateTime = QDateTime(QDate((int)(pdtValue->unYear+2000),\
                           (int)pdtValue->unMonth,\
                           (int)pdtValue->unDay),\
                     QTime(8,0,0));
    }

    return qDateTime;
}
QString DateTimeToString(DateTime* pDateTime,bool bTimeFlag)
{
    QString strDateTime;
    strDateTime = QString("%1-").arg(pDateTime->unYear+2000);
    strDateTime+= QString("%1-").arg(pDateTime->unMonth,2,10,QLatin1Char('0'));
    strDateTime+= QString("%1").arg(pDateTime->unDay,2,10,QLatin1Char('0'));
    if(true==bTimeFlag)
    {
        strDateTime+= QString(" %1:").arg(pDateTime->unHour,2,10,QLatin1Char('0'));
        strDateTime+= QString("%1:").arg(pDateTime->unMinute,2,10,QLatin1Char('0'));
        strDateTime+= QString("%1").arg(pDateTime->unSecond,2,10,QLatin1Char('0'));
    }
    return strDateTime;
}

void StringToDateTime(DateTime* pDateTime,QString strDateTime)
{
    QDateTime  qDateTime = QDateTime::fromString (strDateTime,QString("yyyy-MM-dd hh:mm:ss"));
    pDateTime->unYear  = qDateTime.date().year()-2000;
    pDateTime->unMonth = qDateTime.date().month();
    pDateTime->unDay   = qDateTime.date().day();
    pDateTime->unHour  = qDateTime.time().hour();
    pDateTime->unMinute= qDateTime.time().minute();
    pDateTime->unSecond= qDateTime.time().second();
}

bool IsValidDateTime(DateTime* pDateTime)
{
    if(pDateTime->unYear<=50)
    {
        if(pDateTime->unMonth>=1&&pDateTime->unMonth<=12)
        {
            if(pDateTime->unDay>=1&&pDateTime->unDay<=31)
            {
                if(pDateTime->unHour<=23)
                {
                    if(pDateTime->unMinute<=59)
                    {
                        if(pDateTime->unSecond<=59)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void GetDateTime(DateTime* pDateTime)
{
    QDateTime  dt = QDateTime::currentDateTime();
    pDateTime->unYear   = dt.date().year()-2000;
    pDateTime->unMonth  = dt.date().month();
    pDateTime->unDay    = dt.date().day();
    pDateTime->unHour   = dt.time().hour();
    pDateTime->unMinute = dt.time().minute();
    pDateTime->unSecond = dt.time().second();
}
/*
INT8 DateTimeCmp(DateTime* pDateTime1, DateTime* pDateTime2)
{
    if(pDateTime1->unYear < pDateTime2->unYear)
    {
        return -1;
    }
	else if(pDateTime1->unYear == pDateTime2->unYear)
	{
	   return 0;
	}
    QString strDateTime;
    strDateTime = QString("%1-").arg(pDateTime->unYear+2000);
    strDateTime+= QString("%1-").arg(pDateTime->unMonth,2,10,QLatin1Char('0'));
    strDateTime+= QString("%1").arg(pDateTime->unDay,2,10,QLatin1Char('0'));
    if(true==bTimeFlag)
    {
        strDateTime+= QString(" %1:").arg(pDateTime->unHour,2,10,QLatin1Char('0'));
        strDateTime+= QString("%1:").arg(pDateTime->unMinute,2,10,QLatin1Char('0'));
        strDateTime+= QString("%1").arg(pDateTime->unSecond,2,10,QLatin1Char('0'));
    }
    return strDateTime;
}
*/

UINT16 CreateCRCCheckSum(BYTE* pDataBuf,UINT32 unDataLen)
{
    UINT16 unCheckSum = 0;
    UINT16 unDataPos;
    while(unDataLen--)
    {
        for(unDataPos = 0x80; 0 != unDataPos; unDataPos = unDataPos >> 1)
        {
            if(0 != (unCheckSum & 0x8000))
            {
                /* 余式CRC 乘以2 再求CRC */
                unCheckSum = unCheckSum << 1;
                unCheckSum ^= 0x1021;
            }
            else
            {
                unCheckSum = unCheckSum << 1;
            }
            if(0 != (*pDataBuf & unDataPos))
            {
                unCheckSum ^= 0x1021; /* 再加上本位的CRC */
            }
        }
        pDataBuf++;
    }
    return unCheckSum;
}

UINT16 CreateJBDCheckSum(BYTE* pDataBuf, UINT32 unDataLen)
{
    UINT16 unCheckSum = 0;
    UINT16 unDataPos;
    while(unDataLen--)
    {
        //printf("%02x ",*pDataBuf);
        unCheckSum += *pDataBuf;
        pDataBuf++;
    }
	//printf("\r\n");
	unCheckSum = ~unCheckSum;
	unCheckSum += 1;
    return unCheckSum;
}
//串口5控制485收发控制开关
void CtrlRs485RvcSnd(UINT8 unCtrl)
{
	//QString strPathName = QString("echo %1 > /sys/class/gpio/gpio68/value").arg(unCtrl);
	//SystemEx(strPathName.toStdString().c_str());
	if(unCtrl)
		system("echo 1 > /sys/class/gpio/gpio68/value");
	else
		system("echo 0 > /sys/class/gpio/gpio68/value");	
}


UINT32 GetMsTimer(timeb* pOldTimeb)
{
    UINT32 unMsTimer;
    timeb  newTimeb;
    ftime(&newTimeb);
    unMsTimer  = (newTimeb.time-pOldTimeb->time)*1000L;
    unMsTimer += newTimeb.millitm;
    unMsTimer -= pOldTimeb->millitm;
    if(unMsTimer)
    {
        ftime(pOldTimeb);
    }
    return unMsTimer;
}

bool LoadDevTypeParam(QString& strError)
{
    int fd;
    struct stat  fdStat;
    UINT32 unReadLen;
    QString strPathName = qApp->applicationDirPath()+DEV_TYPE_CFG_NAME;
    strError = "";
    if (-1==(fd=open(strPathName.toStdString().c_str(),O_RDONLY)))
    {
        strError = QString("配置文件打开错误!文件名:")+strPathName;
        return false;
    }
    if(-1==fstat(fd,&fdStat))
    {
        strError = QString("读取文件信息状态错误!文件名:")+strPathName;
        close(fd);
        return false;
    }
    if((off_t)sizeof(g_devBasicPrmCfg)!=fdStat.st_size)
    {
        strError = QString("配置文件数据大小错误!文件名:")+strPathName;
        close(fd);
        printf("FileSizeError FileSize:%lu ",(UINT32)fdStat.st_size);
        printf("CfgSize:%lu\r\n",(UINT32)sizeof(g_devBasicPrmCfg));
        return false;
    }
    unReadLen = sizeof(g_devBasicPrmCfg);
    unReadLen = read(fd,(char*)&g_devBasicPrmCfg,sizeof(g_devBasicPrmCfg));
    if(unReadLen != sizeof(g_devBasicPrmCfg))
    {
        printf("Read DevType Config File Error!\r\n");
        printf("ReadLen:%lu!\r\n",unReadLen);
        close(fd);
        return false;
    }
    UINT16 unCheckSum = g_devBasicPrmCfg.unCheckSum;
    g_devBasicPrmCfg.unCheckSum = 0;
    if(unCheckSum != CreateCRCCheckSum((BYTE*)&g_devBasicPrmCfg,\
                                       sizeof(g_devBasicPrmCfg)))
    {
        strError = QString("配置文件数据校验错误!文件名:")+strPathName;
        close(fd);
        return false;
    }
    close(fd);
    return true;
}

bool SaveDevTypeParam(QString& strError)
{
    struct stat  fdStat;
    bool bReturn  = false;
    QString strCfgFilePath = qApp->applicationDirPath() + DEV_TYPE_CFG_NAME;
    strError = "";
    int fd = open(strCfgFilePath.toStdString().c_str() ,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if (-1==fd)
    {
        strError = QString("创建配置文件失败!文件名:")+strCfgFilePath;
        return bReturn;
    }
    if(-1==fstat(fd,&fdStat))
    {
        strError = QString("读取文件信息状态错误!文件名:")+strCfgFilePath;
        close(fd);
        return false;
    }
    g_devBasicPrmCfg.unCheckSum = 0;
    g_devBasicPrmCfg.unVersion  = FILE_LAST_VER_NUM;
    g_devBasicPrmCfg.unCheckSum = CreateCRCCheckSum((BYTE*)&g_devBasicPrmCfg,sizeof(g_devBasicPrmCfg));
    lseek(fd,0L,SEEK_SET);
    if(sizeof(g_devBasicPrmCfg)!=write(fd,(char*)&g_devBasicPrmCfg,sizeof(g_devBasicPrmCfg)))
    {
        strError = QString("写配置文件失败!")+strCfgFilePath;
        printf("Save DevType Config File Fail!\r\n");
    }
    else
    {
        bReturn = true;
        fsync(fd);
    }
    close(fd);
    return bReturn;
}



bool LoadConfigInfo(QString strPathName,QString& strError)
{
    int fd;
    struct stat  fdStat;
    UINT32 unReadLen;
    strError = "";
    if (-1==(fd=open(strPathName.toStdString().c_str(),O_RDONLY)))
    {
        strError = QString("配置文件打开错误!文件名:")+strPathName;
        return false;
    }
    if(-1==fstat(fd,&fdStat))
    {
        strError = QString("读取文件信息状态错误!文件名:")+strPathName;
        close(fd);
        return false;
    }
    if((off_t)sizeof(g_devConfigInfo)>fdStat.st_size)
    {
        strError = QString("配置文件数据大小错误!文件名:")+strPathName;
        printf("FileSizeError FileSize:%lu ",(UINT32)fdStat.st_size);
        printf("CfgSize:%lu\r\n",(UINT32)sizeof(g_devConfigInfo));
        close(fd);
        return false;
    }
    unReadLen = read(fd,(char*)&g_devConfigInfo,sizeof(g_devConfigInfo));
    if(unReadLen != sizeof(g_devConfigInfo))
    {
        printf("Read Config File Error!\r\n");
        printf("ReadLen:%lu!\r\n",unReadLen);
        close(fd);
        return false;
    }
    UINT16 unCheckSum = g_devConfigInfo.unCheckSum;
    g_devConfigInfo.unCheckSum = 0;
    if(unCheckSum != CreateCRCCheckSum((BYTE*)&g_devConfigInfo,\
                                       sizeof(g_devConfigInfo)))
    {
        strError = QString("配置文件数据校验错误!文件名:")+strPathName;
        close(fd);
        return false;
    }
    if(FILE_LAST_VER_NUM != g_devConfigInfo.unVersion)
    {
        strError = QString("配置文件数据版本号不对!文件名:")+strPathName;
        close(fd);
        return false;
    }
    close(fd);
    if(DEV_INIT_FLAG!=g_devConfigInfo.unInitFlag)
    {
        strError = QString("初始化标志位不对!文件名:")+strPathName;
        return false;
    }
    return true;
}

bool SaveConfigInfo(QString& strError)
{
    struct stat  fdStat;
    bool bReturn  = false;
    QString strCfgFilePath = qApp->applicationDirPath()+CONFIG_FILE_NAME;
    strError = "";
    int fd = open(strCfgFilePath.toStdString().c_str() ,O_WRONLY|O_CREAT,0666);
    if (-1==fd)
    {
        strError = QString("创建配置文件失败!文件名:")+strCfgFilePath;
        return bReturn;
    }
    if(-1==fstat(fd,&fdStat))
    {
        strError = QString("读取文件信息状态错误!文件名:")+strCfgFilePath;
        close(fd);
        return false;
    }
    g_devConfigInfo.unCheckSum = 0;
    g_devConfigInfo.unInitFlag = DEV_INIT_FLAG;
    g_devConfigInfo.unVersion  = FILE_LAST_VER_NUM;
    g_devConfigInfo.unCheckSum = CreateCRCCheckSum((BYTE*)&g_devConfigInfo,sizeof(g_devConfigInfo));
    lseek(fd,0L,SEEK_SET);
    if(sizeof(g_devConfigInfo)!=write(fd,(char*)&g_devConfigInfo,sizeof(g_devConfigInfo)))
    {
        strError = QString("写配置文件失败!")+strCfgFilePath;
        printf("Save Config File Fail!\r\n");
    }
    else
    {
        bReturn = true;
        ftruncate(fd,sizeof(g_devConfigInfo));
        fsync(fd);
    }
    close(fd);
    return bReturn;
}


void InitDefParam(void)
{
    g_devConfigInfo.unDevType = g_devBasicPrmCfg.unDevType; //设备类型
    g_devConfigInfo.unBloPumType = g_devBasicPrmCfg.unBloPumType; //血泵类型
    g_devConfigInfo.unArteryType = g_devBasicPrmCfg.unArteryType; //动脉血泵类型
    g_devConfigInfo.unVeinType = g_devBasicPrmCfg.unVeinType;   //静脉血泵类型
    g_devConfigInfo.unWatTRooType = g_devBasicPrmCfg.unWatTRooType; //水浴类型

    g_devConfigInfo.basicCfgInfo.unAPumCount = g_devBasicPrmCfg.unAPumCount;
	g_devConfigInfo.basicCfgInfo.unVPumCount = g_devBasicPrmCfg.unVPumCount;
	g_devConfigInfo.basicCfgInfo.unWatCount = g_devBasicPrmCfg.unWatCount;
	
    g_devConfigInfo.basicCfgInfo.unMonSavTmt = 60;
    g_devConfigInfo.basicCfgInfo.unAlmEnFlag = false;
    strcpy(g_devConfigInfo.basicCfgInfo.strDataPath,"Data");
    strcpy(g_devConfigInfo.basicCfgInfo.strLogPath,"Log");
    //strcpy(g_devConfigInfo.basicCfgInfo.strCmmPort0,g_devBasicPrmCfg.strComPort0);//"/dev/ttyO2");
    //strcpy(g_devConfigInfo.basicCfgInfo.strCmmPort1,g_devBasicPrmCfg.strComPort1);//"/dev/ttyO5");//大字字母O
    //strcpy(g_devConfigInfo.basicCfgInfo.strCmmPort2,g_devBasicPrmCfg.strComPort2);//"/dev/ttyO3");//大字字母O

	g_devConfigInfo.arteryParm.unDevID = APUM_DEV_BAS_ID;
    g_devConfigInfo.arteryParm.unEnFlag = true;
    g_devConfigInfo.arteryParm.unPress = 300;
    g_devConfigInfo.arteryParm.unSpeed = SET_SPEED_DEF;
    g_devConfigInfo.arteryParm.unFlow = 0;
    g_devConfigInfo.arteryParm.unPressLimt = SET_PRESS_LIMIT;
    g_devConfigInfo.arteryParm.unSpeedLimt = SET_SPEED_LIMIT;
    g_devConfigInfo.arteryParm.unFlowLimt = 0;	

    g_devConfigInfo.veinParm.unDevID = VPUM_DEV_BAS_ID;
    g_devConfigInfo.veinParm.unEnFlag = true;
    g_devConfigInfo.veinParm.unPress = 50;
    g_devConfigInfo.veinParm.unSpeed = SET_SPEED_DEF;
    g_devConfigInfo.veinParm.unFlow = 0;
	
    g_devConfigInfo.veinParm.unPressLimt = SET_PRESS_LIMIT_V;
    g_devConfigInfo.veinParm.unSpeedLimt = SET_SPEED_LIMIT_V;
    g_devConfigInfo.veinParm.unFlowLimt = 0;

    g_devConfigInfo.watRooParam.unDevID = WAT_DEV_BAS_ID;
    g_devConfigInfo.watRooParam.unEnFlag = true;
    g_devConfigInfo.watRooParam.unTmpVal = 370;
	g_devConfigInfo.watRooParam.unTmpValLimt = SET_TMP_LIMIT;

    g_devConfigInfo.batParam.unDevID = BAT_DEV_BAS_ID;
    g_devConfigInfo.batParam.unEnFlag = true;

    g_devConfigInfo.devAlmParam.unAlmUPresA = 850;
	g_devConfigInfo.devAlmParam.unAlmUTmpA  = 380;
    g_devConfigInfo.devAlmParam.unAlmUFlowA = 300;
	g_devConfigInfo.devAlmParam.unAlmLFlowA = 0;
	g_devConfigInfo.devAlmParam.unAlmBubbleA = 0;
	g_devConfigInfo.devAlmParam.unAlmUSpeeA  = 8000;
	
    g_devConfigInfo.devAlmParam.unAlmUPresV = 160;
	g_devConfigInfo.devAlmParam.unAlmUTmpV  = 380;
    g_devConfigInfo.devAlmParam.unAlmUFlowV = 1500;
	g_devConfigInfo.devAlmParam.unAlmLFlowV = 0;
	g_devConfigInfo.devAlmParam.unAlmBubbleV = 0;
	g_devConfigInfo.devAlmParam.unAlmUSpeeV  = 8000;
	
    g_devConfigInfo.devAlmParam.unAlmUWatTmp = 395;
	g_devConfigInfo.devAlmParam.unAlmUWatLin = 101;
	g_devConfigInfo.devAlmParam.unAlmLWatLin = 60;
	g_devConfigInfo.devAlmParam.unAlmBloodLin = 101;

    g_devConfigInfo.devPourParam.unPourUPresA = 1000;
	g_devConfigInfo.devPourParam.unPourUSpeeA = 10000;
	g_devConfigInfo.devPourParam.unPourUTmpA = 390;
    g_devConfigInfo.devPourParam.unPourUFlowA = 800;
	g_devConfigInfo.devPourParam.unPourLFlowA = 0;
	
    g_devConfigInfo.devPourParam.unPourUPresV = 200;
	g_devConfigInfo.devPourParam.unPourUSpeeV = 10000;
	g_devConfigInfo.devPourParam.unPourUTmpV = 390;
    g_devConfigInfo.devPourParam.unPourUFlowV = 2500;
	g_devConfigInfo.devPourParam.unPourLFlowV = 0;
	
    g_devConfigInfo.devPourParam.unPourUWatTmp = 410;
	g_devConfigInfo.devPourParam.unPourWatLin = 60;	

}

/*

bool LoadPwdInfo(QString strPathName,QString& strError)
{
    int fd;
    struct stat  fdStat;
    UINT32 unReadLen;
    strError = "";
    if (-1==(fd=open(strPathName.toStdString().c_str(),O_RDONLY)))
    {
        strError = QString("文件打开错误!文件名:")+strPathName;
        return false;
    }
    if(-1==fstat(fd,&fdStat))
    {
        strError = QString("读取文件状态错误!文件名:")+strPathName;
        close(fd);
        return false;
    }

    if((off_t)sizeof(g_pwdCfgInfo)>fdStat.st_size)
    {
        strError = QString("文件大小错误!文件名:")+strPathName;
        close(fd);
        return false;
    }
    unReadLen = read(fd,(char*)&g_pwdCfgInfo,sizeof(g_pwdCfgInfo));
    if(unReadLen != sizeof(g_pwdCfgInfo))
    {
        strError = QString("Read Pwd File Error!\r\n");
        close(fd);
        return false;
    }

    close(fd);
    return true;
}
*/

int SystemEx(const char *cmdstring)
{
    printf("----------SystemCall-------------:%s\r\n",cmdstring);
    if (cmdstring == NULL)
        return(1);

    char pCmdBuf[200];
    sprintf(pCmdBuf,"exec %s",cmdstring);
    return system(pCmdBuf);
}

QComboBox*  CreateComboBox(QWidget * parent)
{
    QComboBox* pNewComboBox = new QComboBox(parent);
    pNewComboBox->setView(new QListView(parent));
    pNewComboBox->setMinimumWidth(100);
    pNewComboBox->setMinimumHeight(MINI_HEIGHT);
    return pNewComboBox;
}

void SetMessageBoxFont(QMessageBox* pMsgBox, int w, int h)
{
    QObjectList objChildList = pMsgBox->children();
    for (int i = 0; i < objChildList.size(); i++)
    {
        QObject *pObj= objChildList.at(i);
        if(0==strcmp("QLabel",pObj->metaObject()->className()))
        {
            QLabel* pLable = qobject_cast<QLabel *>(pObj);
            if(0==strcmp("qt_msgbox_label",pLable->objectName().toStdString().c_str()))
            {
                pLable->setMinimumSize(pLable->sizeHint().width()+w,pLable->sizeHint().height()+h);
                //pLable->setStyleSheet("font-family:simsun;font:16px;");
            }
        }
    }
}

void ShowInfo(QMessageBox* pMsgBox,QString strInfo,QString strTitle,enum QMessageBox::Icon icon)
{
    QPushButton* pNewBut;
    pMsgBox->setWindowTitle(strTitle);//(strTitle);
    pMsgBox->setIcon(icon);
    pMsgBox->setText(strInfo);
	
	//pNewBut->setStyleSheet("font-family:wenquanyi;font:16px;");
    pNewBut = pMsgBox->addButton("确定", QMessageBox::AcceptRole);
    pNewBut->setMinimumSize(120,50);
    SetMessageBoxFont(pMsgBox);
    pMsgBox->exec();
}

void AddRowItem(QBoxLayout* pBoxLayout,QWidget* pInputItem,QString strLabel)
{
    QFormLayout* pFrmLayout = new QFormLayout;
    pFrmLayout->addRow(strLabel, pInputItem);
    pBoxLayout->addLayout(pFrmLayout);
}

void AddItem(QFormLayout* pParentForm,QLineEdit* pEditInput,QString strLabel,QString strUnit,long lEditWidth)
{
    QFrame* pFrame = new QFrame();
    pFrame->setFrameStyle(QFrame::NoFrame);
    pFrame->setMaximumWidth(lEditWidth);
    QHBoxLayout* pLine = new QHBoxLayout();
    pFrame->setLayout(pLine);
    QLabel* pLabel = new QLabel(strUnit);
    pLine->addWidget(pEditInput);
    pLine->addWidget(pLabel);
    pLine->setMargin(0);
    pParentForm->addRow(strLabel, pFrame);
    pParentForm->setAlignment(Qt::AlignLeft);
}

ulong GetItemValue(QLineEdit* pLineEdit,long lScale)
{
    return ulong(pLineEdit->text().toDouble()*lScale);
}


UINT32  GetMaxTstInfoSctID(UINT32* punFileCount)//取测试数据目录最大SectorID
{
    DIR *pDir;
    struct dirent *pFile;
    struct stat stFile;
    QString strPath;
    QString strFilePath;
    PourInfo pourInfo;
    UINT32 unMaxSectorID = 0;
    UINT32 unFileCount   = 0;
    strPath  = qApp->applicationDirPath()+"/";
    strPath += g_devConfigInfo.basicCfgInfo.strDataPath;
    strPath += "/";
    *punFileCount = unFileCount;
    //printf("%s\r\n",strPath.toStdString().c_str());
    if(!(pDir = opendir(strPath.toStdString().c_str())))
    {
        printf("Error opendir %s!!!\r\n",strPath.toStdString().c_str());
        return 0;
    }
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
                unFileCount++;
                if(unMaxSectorID < pourInfo.unSectorID)
                {
                    unMaxSectorID = pourInfo.unSectorID;
                }
            }
        }
    }
    closedir(pDir);
    *punFileCount = unFileCount;
    return unMaxSectorID;
}
bool ReadTestInfoEx(UINT32 unSectorID,PourInfo* pTestInfo)
{
    DIR *pDir;
    struct dirent *pFile;
    struct stat stFile;
    QString strPath;
    QString strFilePath;
    bool bReturn = false;
    strPath  = qApp->applicationDirPath()+"/";
    strPath += g_devConfigInfo.basicCfgInfo.strDataPath;
    strPath += "/";
    if(!(pDir = opendir(strPath.toStdString().c_str())))
    {
        printf("Errpr opendir %s!!!/n",strPath.toStdString().c_str());
        return 0;
    }
    while(NULL!=(pFile=readdir(pDir)))
    {
        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        if(0==strcmp(pFile->d_name, ".")||0==strcmp(pFile->d_name, ".."))
        {
            continue;
        }
        if(QString(pFile->d_name).right(4)!=QString(".DAT"))
        {
            continue;
        }
        strFilePath = strPath+QString(pFile->d_name);
        //printf("File:%s\r\n",strFilePath.toStdString().c_str());
        //判断该文件是否是目录，及是否已搜索了三层，这里我定义只搜索了三层目录，太深就不搜了，省得搜出太多文件
        if(stat(strFilePath.toStdString().c_str(), &stFile)>=0&&S_ISREG(stFile.st_mode))
        {
            //printf("Is TestData File!<%s>\r\n",strFilePath.toStdString().c_str());
            if(true==ReadTestInfo(strFilePath.toStdString().c_str(),pTestInfo))
            {
                if(unSectorID == pTestInfo->unSectorID)
                {
                    bReturn = true;
                    break;
                }
            }
        }
    }
    closedir(pDir);
    return bReturn;
}

bool ReadTestInfo(const char* pFileName,PourInfo* pTestInfo)
{
    int  fd;
    bool bReturn = true;
    if(-1==(fd = open(pFileName,O_RDONLY)))
    {
        printf("ReadTestInfo Fail!<%s>\r\n",pFileName);
        return false;
    }
    if(sizeof(PourInfo)!=read(fd,pTestInfo,sizeof(PourInfo)))
    {
        bReturn = false;
    }
    close(fd);
    return bReturn;
}

bool ReadTestData(char* pFileName,UINT32 unReadPos,BYTE* pDataBuf,UINT32 unDataLen)
{
    int  fd;
    bool bReturn = true;
    if(-1==(fd=open(pFileName,O_RDONLY)))
    {
        printf("Open <%s> File Fail!\r\n",pFileName);
        return false;
    }
    if(-1==lseek(fd,unReadPos,SEEK_SET))
    {
        printf("LSeek TestData Fail!\r\n");
        return false;
    }
    if((ssize_t)unDataLen!=read(fd,pDataBuf,unDataLen))
    {
        printf("Read TestData Fail!\r\n");
        bReturn = false;
    }
    close(fd);
    return bReturn;
}

bool GetTestDataFile(UINT32 unSectorID,char* pFileName)
{
    DIR *pDir;
    struct dirent *pFile;
    struct stat stFile;
    QString strPath;
    QString strFilePath;
    PourInfo pourInfo;
    bool bReturn = false;
    strPath  = qApp->applicationDirPath()+"/";
    strPath += g_devConfigInfo.basicCfgInfo.strDataPath;
    strPath += "/";
    if(!(pDir = opendir(strPath.toStdString().c_str())))
    {
        printf("Error opendir %s!!!/n",strPath.toStdString().c_str());
        return 0;
    }
    while(NULL!=(pFile=readdir(pDir)))
    {
        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        if(0==strcmp(pFile->d_name, ".")||0==strcmp(pFile->d_name, ".."))
        {
            continue;
        }
        if(QString(pFile->d_name).right(4)!=QString(".DAT"))
        {
            continue;
        }
        strFilePath = strPath+QString(pFile->d_name);
        //printf("File:%s\r\n",strFilePath.toStdString().c_str());
        //判断该文件是否是目录，及是否已搜索了三层，这里我定义只搜索了三层目录，太深就不搜了，省得搜出太多文件
        if(stat(strFilePath.toStdString().c_str(), &stFile)>=0&&S_ISREG(stFile.st_mode))
        {
            //printf("Is TestData File!<%s>\r\n",strFilePath.toStdString().c_str());
            if(true==ReadTestInfo(strFilePath.toStdString().c_str(),&pourInfo))
            {
                if(unSectorID == pourInfo.unSectorID)
                {
                    strcpy(pFileName,strFilePath.toStdString().c_str());
                    bReturn = true;
                    break;
                }
            }
        }
    }
    closedir(pDir);
    return bReturn;
}

//删除文件
bool DelTestDataFile(UINT32 unSectorID)
{
    DIR *pDir;
    struct dirent *pFile;
    struct stat stFile;
    QString strPath;
    QString strFilePath;
	QString strDelCmd;
    PourInfo pourInfo;
    bool bReturn = false;
    strPath  = qApp->applicationDirPath()+"/";
    strPath += g_devConfigInfo.basicCfgInfo.strDataPath;
    strPath += "/";
    if(!(pDir = opendir(strPath.toStdString().c_str())))
    {
        printf("Error opendir %s!!!/n",strPath.toStdString().c_str());
        return 0;
    }
    while(NULL!=(pFile=readdir(pDir)))
    {
        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        if(0==strcmp(pFile->d_name, ".")||0==strcmp(pFile->d_name, ".."))
        {
            continue;
        }
        if(QString(pFile->d_name).right(4)!=QString(".DAT"))
        {
            continue;
        }
        strFilePath = strPath+QString(pFile->d_name);
        //printf("File:%s\r\n",strFilePath.toStdString().c_str());
        //判断该文件是否是目录，及是否已搜索了三层，这里我定义只搜索了三层目录，太深就不搜了，省得搜出太多文件
        if(stat(strFilePath.toStdString().c_str(), &stFile)>=0&&S_ISREG(stFile.st_mode))
        {
            //printf("Is TestData File!<%s>\r\n",strFilePath.toStdString().c_str());
            if(true==ReadTestInfo(strFilePath.toStdString().c_str(),&pourInfo))
            {
                if(unSectorID == pourInfo.unSectorID)
                {
                    //strcpy(pFileName,strFilePath.toStdString().c_str());
					//SystemEx("rm -r "+strFilePath.toStdString().c_str());
                    printf("delete----%s \r\n",strFilePath.toStdString().c_str());
					strDelCmd = QString("rm -r %1").arg(strFilePath);
					SystemEx(strDelCmd.toStdString().c_str());
                    bReturn = true;
                    break;
                }
            }
        }
    }
    closedir(pDir);
    return bReturn;
}

QString DataTypeToString(UINT8 unDataType)
{
    if(0 == unDataType)
    {
        return QString("预灌注");
    }
    return QString("灌注");
}

QString StopCodeToString(UINT32 unStopCode)
{
    QString strErrorInfo;
    QString strError;
    strErrorInfo = QString("未知错误:%1!").arg(unStopCode);

    switch(unStopCode)
    {
    	case STP_ERR_USR_CNL_ERR:
            strErrorInfo = "用户手动停止!";
            break;
    	case STP_ERR_DEV_TMT_ERR:
            strErrorInfo = "设备超时停止!";
            break;	
    	case STP_ERR_SUB_STP_ERR:
            strErrorInfo = "泵设备停止!";
            break;
	    case STP_ERR_WAT_TMP_ERR:
            strErrorInfo = "温度告警停止!";
            break;	
        default:break;
	}
    strError = strErrorInfo;
    return strError;
}

UINT32  DoMsTimer(UINT32 unTimer,UINT32 unMsCount)
{
    if(unTimer&&0xFFFFFFFF!=unTimer)
    {
        if(unTimer>=unMsCount)
        {
            unTimer -= unMsCount;
        }
        else
        {
            unTimer = 0;
        }
    }
    return unTimer;
}

QGroupBox* CreateGroupBox(QWidget * parent)
{
    QGroupBox* pGroupBox = new QGroupBox(parent);
    /*
    pGroupBox->setStyleSheet("\
        QGroupBox {\
            background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                              stop: 0 #E0E0E0, stop: 1 #FFFFFF);\
            border: 2px solid gray;\
            border-radius: 5px;\
            margin-top: 3ex;\
        };\
        QGroupBox::title {\
        subcontrol-origin: margin;\
        subcontrol-position: top center;\
        padding: 0 3px;\
        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                          stop: 0 #FFOECE, stop: 1 #FFFFFF);\
    }");
    */
    return pGroupBox;
}

void LoadCompanyInfo(QString& strCoInfo)
{
    int  fd;
    QString strVersion  = QString("  系统版本：%1").arg(VERSION_INFO);
    QString strCoInfoPath = qApp->applicationDirPath()+"/CompanyInfo.txt";
    if(-1==(fd=open(strCoInfoPath.toStdString().c_str(),O_RDONLY)))
    {
        QString strProdName = "肝脏灌注系统Life-X100";
        QString strAddrName = "地址:广州市增城区宁西街香山大道2号";
        QString strCnnPhone = "电话:020-82856838";
        QString strDesigner = "奇点医疗科技(广州)有限公司设计";
        strCoInfo = QString("%1\r\n").arg(strProdName);
        strCoInfo+= QString("%1\r\n").arg(strAddrName);
        strCoInfo+= QString("%1\r\n").arg(strCnnPhone);
        strCoInfo+= QString("%1\r\n").arg(strDesigner);
        strCoInfo+= QString("%1\r\n").arg(strVersion);
    }
    else
    {
        struct stat  fdStat;
        char strCoInfoEx[MAX_CO_INFO_SIZE];
        UINT32 unFileSize;
        memset(strCoInfoEx,0,sizeof(strCoInfoEx));
        if(-1==fstat(fd,&fdStat))
        {
            close(fd);
            return;
        }
        unFileSize = fdStat.st_size;
        if(unFileSize>=MAX_CO_INFO_SIZE)
        {
            unFileSize = MAX_CO_INFO_SIZE-1;
        }
        read(fd,strCoInfoEx,unFileSize);
        close(fd);
        strCoInfoEx[unFileSize] = 0;
        strCoInfo = QString((const char*)strCoInfoEx)+"\r\n";
        strCoInfo+= QString("%1\r\n").arg(strVersion);
    }
}

QString AlmIDToName(UINT8 unAlmID)
{
    QString strAlmName = "";
    switch(unAlmID)
    {
    case H_P_ALM_ITEM_V_PRE_UP:
        strAlmName = "门脉压力高";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_P_ALM_ITEM_A_PRE_UP:
        strAlmName = "动脉压力高";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_P_ALM_ITEM_V_PRE_DN:
        strAlmName = "门脉压力传感器异常";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_T_ALM_ITEM_A_PRE_DN:
        strAlmName = "动脉压力传感器异常";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_T_ALM_ITEM_V_PRE_SEN:
        strAlmName = "门脉传感器异常";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_T_ALM_ITEM_A_PRE_SEN:
        strAlmName = "动脉传感器异常";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_P_ALM_ITEM_V_TMP_UP:
        strAlmName = "门脉血液温度高";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_P_ALM_ITEM_A_TMP_UP:
        strAlmName = "动脉血液温度高";
		//unGetLevel = ALM_LEV_H;
        break;
    case H_P_ALM_ITEM_V_FLO_DN:
        strAlmName = "门脉流量低";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_P_ALM_ITEM_A_FLO_DN:
        strAlmName = "动脉流量低";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_T_ALM_ITEM_WAT_TMP_UP:
        strAlmName = "水浴温度高";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_P_ALM_ITEM_V_FLO_UP:
        strAlmName = "门脉流量高";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_P_ALM_ITEM_A_FLO_UP:
        strAlmName = "动脉流量高";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_T_ALM_ITEM_WAT_PPRE_UP:
        strAlmName = "变温系统压力超限值";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_T_ALM_ITEM_V_DEV_TMT:
		strAlmName = "门脉控制模块失联";
		//unGetLevel = ALM_LEV_H;
		break;
	case H_T_ALM_ITEM_A_DEV_TMT:
		strAlmName = "动脉控制模块失联";
		//unGetLevel = ALM_LEV_H;
		break;
	case H_T_ALM_ITEM_V_PUM_TMT:
		strAlmName = "门脉泵未连接";
		//unGetLevel = ALM_LEV_H;
		break;
	case H_T_ALM_ITEM_A_PUM_TMT:
		strAlmName = "动脉泵未连接";
		//unGetLevel = ALM_LEV_H;
		break;
    case H_T_ALM_ITEM_V_PUM_ERR:
		strAlmName = "门脉泵异常";
		//unGetLevel = ALM_LEV_H;
		break;
	case H_T_ALM_ITEM_A_PUM_ERR:
		strAlmName = "动脉泵异常";
		//unGetLevel = ALM_LEV_H;
		break;
	case H_T_ALM_ITEM_WAT_TMP_SEN:
		strAlmName = "水浴温度传感器异常";
		//unGetLevel = ALM_LEV_H;
		break;
	case H_T_ALM_ITEM_WAT_DEV_TMT:
		strAlmName = "水温控制模块失联";
		//unGetLevel = ALM_LEV_H;
		break;
    case H_P_ALM_ITEM_V_BUBBLE:
        strAlmName = "门脉管路有气泡";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_P_ALM_ITEM_A_BUBBLE:
        strAlmName = "动脉管路有气泡";
		//unGetLevel = ALM_LEV_H;
        break;
	case H_T_ALM_ITEM_BAT_VOL_DN:
        strAlmName = "电池电量低";
		//unGetLevel = ALM_LEV_H;
        break;
	case M_T_ALM_ITEM_A_PRE_TMT:
        strAlmName = "动脉压力传感器线缆未连接";
		//unGetLevel = ALM_LEV_M;
        break;
	case M_T_ALM_ITEM_V_PRE_TMT:
        strAlmName = "门脉压力传感器线缆未连接";
		//unGetLevel = ALM_LEV_M;
        break;
	case M_T_ALM_ITEM_A_PRE_DEV_TMT:
        strAlmName = "动脉压力监测模块失联";
		//unGetLevel = ALM_LEV_M;
        break;	
	case M_T_ALM_ITEM_V_PRE_DEV_TMT:
		strAlmName = "门脉压力监测模块失联";
		//unGetLevel = ALM_LEV_M;
		break;
	case M_T_ALM_ITEM_A_FLO_TMT:
		strAlmName = "动脉流量传感器未连接";
		//unGetLevel = ALM_LEV_M;
		break;
	case M_T_ALM_ITEM_V_FLO_TMT:
		strAlmName = "门脉流量传感器未连接";
		//unGetLevel = ALM_LEV_M;
		break;
	case M_T_ALM_ITEM_A_PRE_UP:
		strAlmName = "动脉泵转速高";
		//unGetLevel = ALM_LEV_M;
		break;
	case M_T_ALM_ITEM_V_PRE_UP:
	    strAlmName = "门脉转速高";
		//unGetLevel = ALM_LEV_M;
	    break;	
	case M_T_ALM_ITEM_WAT_LIN_DN:
		strAlmName = "水箱液位低";
		//unGetLevel = ALM_LEV_M;
		break;
	case M_T_ALM_ITEM_BAT_DEV_TMT:
		strAlmName = "未检测到电池";
		//unGetLevel = ALM_LEV_M;
		break;
	case M_T_ALM_ITEM_BAT_TMP_UP:
		strAlmName = "电池超温";
		//unGetLevel = ALM_LEV_M;
		break;	
    case M_T_ALM_ITEM_WAT_FAN_ERR:
        strAlmName = "系统风扇故障";
		//unGetLevel = ALM_LEV_M;
        break;
    case M_T_ALM_ITEM_A_FLO_SEN:
        strAlmName = "动脉流量传感器异常";
		//unGetLevel = ALM_LEV_M;
        break;
    case M_T_ALM_ITEM_V_FLO_SEN:
        strAlmName = "门脉流量传感器异常";
		//unGetLevel = ALM_LEV_M;
        break;
    case M_T_ALM_ITEM_AC_LOS:
        strAlmName = "电源线未连接";
		//unGetLevel = ALM_LEV_M;
        break;
    case M_T_ALM_ITEM_BAT_DIS:
        strAlmName = "电池需要维护保养";
		//unGetLevel = ALM_LEV_M;
        break;
    case L_T_ALM_ITEM_WAT_LIN_UP:
        strAlmName = "水箱液位高";
		//unGetLevel = ALM_LEV_L;
        break;
    case L_T_ALM_ITEM_A_TMP_TMT:
        strAlmName = "动脉血温传感器未连接";
		//unGetLevel = ALM_LEV_L;
        break;
    case L_T_ALM_ITEM_V_TMP_TMT:
        strAlmName = "门脉血温传感器未连接";
		//unGetLevel = ALM_LEV_L;
        break;
    case L_T_ALM_ITEM_A_TMP_SEN:
        strAlmName = "动脉血温传感器异常";
		//unGetLevel = ALM_LEV_L;
        break;
    case L_T_ALM_ITEM_V_TMP_SEN:
        strAlmName = "门脉血温传感器异常";
		//unGetLevel = ALM_LEV_L;
        break;
    default:
        break;
    }
    return strAlmName;
}

QString  AlmFlagToString(UINT8 unAlmFlag)
{
    QString strAlmFlag;
    if(0==unAlmFlag)
    {
        strAlmFlag = "清除";
    }
    else
    {
        strAlmFlag = "发生";
    }
    return strAlmFlag;
}

QString AlmTmtIDToName(UINT8 unAlmObjID)
{
    QString strAlmName = "上位机与下位机设备通信超时";
    if(unAlmObjID >= APUM_DEV_BAS_ID && unAlmObjID < APUM_DEV_BAS_ID+MAX_PUM_GRP_COUNT)
    {
       strAlmName = QString("动脉血泵模块<%1>---通信超时").arg(unAlmObjID - APUM_DEV_BAS_ID+1);
    }
    else if(unAlmObjID >= VPUM_DEV_BAS_ID && unAlmObjID < VPUM_DEV_BAS_ID+MAX_PUM_GRP_COUNT)
    {
       strAlmName = QString("静脉血泵模块<%1>---通信超时").arg(unAlmObjID - VPUM_DEV_BAS_ID+1);
    }
    else if(unAlmObjID >= WAT_DEV_BAS_ID && unAlmObjID < WAT_DEV_BAS_ID+MAX_WAT_GRP_COUNT)
    {
       strAlmName = QString("水浴模块<%1>---通信超时").arg(unAlmObjID - WAT_DEV_BAS_ID+1);
    }
    return strAlmName;
}


//读取当前一条告警
QString CheckOneAlmShow(UINT8 *unGetLevel)
{
    QString  strAlmItem = " ";
	//UINT8* unBckLev = (UINT8*)unGetLevel;
	
	if(g_devAlmBits.VpumGrpAlm.bPressUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉压力高";
		return strAlmItem;
	}
	if(g_devAlmBits.ApumGrpAlm.bPressUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉压力高";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bPressLBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉压力低";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bPressLBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉压力低";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bPressErrBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉压力传感器异常";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bPressErrBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉压力传感器异常";
		return strAlmItem;
	}
	if(g_devAlmBits.VpumGrpAlm.bTmpUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉血液温度高";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bTmpUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉血液温度高";
		return strAlmItem;
	}
	if(g_devAlmBits.VpumGrpAlm.bFlowLBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉流量低";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bFlowLBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉流量低";
		return strAlmItem;
	}
	if(g_devAlmBits.watGrpAlm.bTmpUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "水浴温度高";
		return strAlmItem;
	}
	if(g_devAlmBits.VpumGrpAlm.bFlowUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉流量高";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bFlowUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉流量高";
		return strAlmItem;
	}
	if(g_devAlmBits.watGrpAlm.bWatPreUBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "变温系统压力超限值";
		return strAlmItem;
	}
	if(g_devAlmBits.VpumGrpAlm.bPumTmtBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉控制模块失联";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bPumTmtBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉控制模块失联";
		return strAlmItem;
	}
	if(g_devAlmBits.unVPumModBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉泵未连接";
		return strAlmItem;
	}	
	if(g_devAlmBits.unAPumModBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉泵未连接";
		return strAlmItem;
	}
	if(g_devAlmBits.VpumGrpAlm.bPumErrBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉泵异常";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bPumErrBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉泵异常";
		return strAlmItem;
	}
	if(g_devAlmBits.watGrpAlm.bTmpSensorBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "水浴温度传感器异常";
		return strAlmItem;
	}
	if(g_devAlmBits.unWatModBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "水温控制模块失联";
		return strAlmItem;
	}
	if(g_devAlmBits.VpumGrpAlm.bBubblBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "门脉管路有气泡";
		return strAlmItem;
	}	
	if(g_devAlmBits.ApumGrpAlm.bBubblBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "动脉管路有气泡";
		return strAlmItem;
	}
	if(g_devAlmBits.BatAlm.bBatSocBits)
	{
	    *unGetLevel = ALM_LEV_H;
		strAlmItem = "电池电量低";
		return strAlmItem;
	}		
	if(g_devAlmBits.ApumGrpAlm.bPreLinBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "动脉压力传感器线缆未连接";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bPreLinBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "门脉压力传感器线缆未连接";
		return strAlmItem;
	}
	if(g_devAlmBits.ApumGrpAlm.bPreTmtBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "动脉压力监测模块失联";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bPreTmtBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "门脉压力监测模块失联";
		return strAlmItem;
	}
	if(g_devAlmBits.ApumGrpAlm.bFloTmtBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "动脉流量传感器未连接";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bFloTmtBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "门脉流量传感器未连接";
		return strAlmItem;
	}
	if(g_devAlmBits.ApumGrpAlm.bSpeedUBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "动脉泵转速高";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bSpeedUBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "门脉转速高";
		return strAlmItem;
	}
	if(g_devAlmBits.watGrpAlm.bLinLBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "水箱液位低";
		return strAlmItem;
	}
	if(g_devAlmBits.unWatModBits)
	{
	    *unGetLevel = ALM_LEV_M;
		strAlmItem = "未检测到电池";
		return strAlmItem;
	}
	if(g_devAlmBits.BatAlm.bBatTmpBits)
	{
	    *unGetLevel = ALM_LEV_M;
		strAlmItem = "电池超温";
		return strAlmItem;
	}
	if(g_devAlmBits.watGrpAlm.bFanBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "系统风扇故障";
		return strAlmItem;
	}
	if(g_devAlmBits.ApumGrpAlm.bFlowSensorBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "动脉流量传感器异常";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bFlowSensorBits)
	{
		*unGetLevel = ALM_LEV_M;
		strAlmItem = "门脉流量传感器异常";
		return strAlmItem;
	}	
	if(g_devAlmBits.BatAlm.bACLosBits)
	{
	    *unGetLevel = ALM_LEV_M;
		strAlmItem = "电源线未连接";
		return strAlmItem;
	}
	if(g_devAlmBits.BatAlm.bBatChkBits)
	{
	    *unGetLevel = ALM_LEV_M;
		strAlmItem = "电池需要维护保养";
		return strAlmItem;
	}

	if(g_devAlmBits.watGrpAlm.bLinUBits)
	{
		*unGetLevel = ALM_LEV_L;
		strAlmItem = "水箱液位高";
		return strAlmItem;
	}
	if(g_devAlmBits.ApumGrpAlm.bFlowSensorBits)
	{
		*unGetLevel = ALM_LEV_L;
		strAlmItem = "动脉血温传感器未连接";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bFlowSensorBits)
	{
		*unGetLevel = ALM_LEV_L;
		strAlmItem = "门脉血温传感器未连接";
		return strAlmItem;
	}
	if(g_devAlmBits.ApumGrpAlm.bTmpTmtBits)
	{
		*unGetLevel = ALM_LEV_L;
		strAlmItem = "动脉血温传感器异常";
		return strAlmItem;
	}	
	if(g_devAlmBits.VpumGrpAlm.bTmpTmtBits)
	{
		*unGetLevel = ALM_LEV_L;
		strAlmItem = "门脉血温传感器异常";
		return strAlmItem;
	}
		
	return strAlmItem;
}


void InitWatchdog(void)
{
	g_fWtchDog = open("/dev/watchdog", O_WRONLY);
	if(g_fWtchDog == -1) 
	{
		perror("watchdog");
		exit(EXIT_FAILURE);
	}
}

void SetWatchdog(void)
{
	if(1 != write(g_fWtchDog, "\0", 1)) 
	{
		printf("Write failed\n");
		close(g_fWtchDog);
	}
}

bool SaveOperLogData(const char* saveBuf, int bufLen)
{
    int fd = -1;
	QString m_LogStrPathName;
	QString m_strErrorInfo;

	if(g_operLogInfo.unOperLogCurrPar >= SAVE_OPER_LOG_NUM)
	{
	    g_operLogInfo.unOperLogCurrPar = 1;
	}
	else
	{
	    g_operLogInfo.unOperLogCurrPar++;
	}
	if(g_operLogInfo.unOperLogFileNum < SAVE_OPER_LOG_NUM)
	{
	    g_operLogInfo.unOperLogFileNum++;
	}

	m_LogStrPathName  = qApp->applicationDirPath()+"/";
	m_LogStrPathName += "OperLog/";
	m_LogStrPathName += QString("%1.DAT").arg(g_operLogInfo.unOperLogCurrPar);

    if(-1==(fd=open(m_LogStrPathName.toStdString().c_str(),O_WRONLY|O_CREAT,0666)))
    {
        m_strErrorInfo =QString("打开文件:<%1>失败,\r\n错误原因--<%2>\r\n").arg(m_LogStrPathName)\
                .arg(strerror(errno));
        return false;
    }

    lseek(fd,0L,SEEK_SET);
    write(fd, saveBuf, bufLen);
    close(fd);

    return true;
}

bool ReadOperLogData(char* readBuf, int bufLen, UINT16 logCerrPar)
{
    //printf("enter ReadOperLogData ----\r\n");
    int fd = -1;
	QString pFileName;

	pFileName  = qApp->applicationDirPath()+"/";
	pFileName += "OperLog/";
	pFileName += QString("%1.DAT").arg(logCerrPar);

    if(-1==(fd = open(pFileName.toStdString().c_str(),O_RDONLY)))
    {
        printf("ReadTestInfo Fail!<%s>\r\n",pFileName.toStdString().c_str());
        return false;
    }
	lseek(fd,0L,SEEK_SET);
    read(fd, readBuf, bufLen);
    close(fd);
    return true;
}

void OPenOperLogInfoFile(void)
{
    QString operLogStrPathName;
	
	operLogStrPathName  = qApp->applicationDirPath() + "/OperLog";
	operLogStrPathName += OPER_LOG_INFO_NAME;
	ReadOperLogInfo(operLogStrPathName);

	//printf("------------get unOperLogFileNum = %d \r\n",g_operLogInfo.unOperLogFileNum);
	//printf("------------get unOperLogCurrPar = %d \r\n",g_operLogInfo.unOperLogCurrPar);
}

bool ReadOperLogInfo(QString pFileName)
{
    QString m_strErrorInfo;
    bool bReturn = true;

    g_fdOperLogFle = open(pFileName.toStdString().c_str() ,O_RDWR|O_CREAT,0666);
    if(g_fdOperLogFle == -1)
    {
        m_strErrorInfo =QString("打开文件:<%1>失败,\r\n错误原因--<%2>\r\n").arg(pFileName)\
                .arg(strerror(errno));

        return false;
    }
    lseek(g_fdOperLogFle,0L,SEEK_SET);
    read(g_fdOperLogFle,(char*)&(g_operLogInfo),sizeof(OperLogInfo));

    return bReturn;
}

bool SaveOperLogInfo(void)
{
    if(-1==g_fdOperLogFle)
    {
        return false;
    }
    lseek(g_fdOperLogFle,0L,SEEK_SET);
    write(g_fdOperLogFle,(const char*)&(g_operLogInfo),sizeof(OperLogInfo));

    return true;
}

bool LoadPwdInfo(QString strPathName,QString& strError)
{
    int fd;
    struct stat  fdStat;
    UINT32 unReadLen;
    strError = "";
    if (-1==(fd=open(strPathName.toStdString().c_str(),O_RDONLY)))
    {
        strError = QString("文件打开错误!文件名:")+strPathName;
        return false;
    }
    if(-1==fstat(fd,&fdStat))
    {
        strError = QString("读取文件状态错误!文件名:")+strPathName;
        close(fd);
        return false;
    }
    if((off_t)sizeof(g_pwdCfgInfo)>fdStat.st_size)
    {
        strError = QString("文件大小错误!文件名:")+strPathName;
        close(fd);
        return false;
    }
    unReadLen = read(fd,(char*)&g_pwdCfgInfo,sizeof(g_pwdCfgInfo));
    if(unReadLen != sizeof(g_pwdCfgInfo))
    {
        strError = QString("Read Pwd File Error!\r\n");
        close(fd);
        return false;
    }
    close(fd);
    return true;
}

bool SavePwdInfo(QString& strError)
{
    struct stat  fdStat;
    bool bReturn  = false;
    QString strPwdFilePath = qApp->applicationDirPath()+"/PwdCfgInfo.cfg";
    strError = "";
    int fd = open(strPwdFilePath.toStdString().c_str() ,O_WRONLY|O_CREAT,0666);
    if (-1==fd)
    {
        strError = QString("创建文件失败!文件名:")+strPwdFilePath;
        return bReturn;
    }
    if(-1==fstat(fd,&fdStat))
    {
        strError = QString("读取文件状态错误!文件名:")+strPwdFilePath;
        close(fd);
        return false;
    }
    lseek(fd,0L,SEEK_SET);
    if(sizeof(g_pwdCfgInfo)!=write(fd,(char*)&g_pwdCfgInfo,sizeof(g_pwdCfgInfo)))
    {
        strError = QString("写文件失败!文件名:")+strPwdFilePath;
    }
    else
    {
        fsync(fd);
        bReturn = true;
    }
    close(fd);
    return bReturn;
}

int FindMCUSoftwareFile(char* fileName, char* devType, char* ver , unsigned char unType)
{
    struct dirent *dp;
    char UpdateFilePath[128] = {0};
    DIR *dfd;

    QString strPath;
    strPath  = qApp->applicationDirPath()+"/";
    if(DEV_APUMP_TYPE == unType)
    {
        strPath += "McuSoft/Artery/";
    }
    else if(DEV_VPUMP_TYPE == unType)
    {
        strPath += "McuSoft/Vein/";
    }
    else if(DEV_WAT_TYPE == unType)
    {
        strPath += "McuSoft/Water/";
    }
    else
    {
        //LOG_D("File not exist.  %s \n", strPath.toStdString().c_str());
        return UpdFindFileErr;    //没有这路径
    }

    strcpy(UpdateFilePath, strPath.toUtf8());

    if ((dfd = opendir(UpdateFilePath)) == NULL)
    {
        printf("Open dir failed! dir: %s \r\n", UpdateFilePath);
        return 1;
    }

    for(dp = readdir(dfd); NULL != dp; dp = readdir(dfd))
    {
        //尝试查找对应的单片机软件.bin文件
        if(strstr(dp->d_name, ".bin") != NULL || \
		   strstr(dp->d_name, ".hex") != NULL)
        {
            //sprintf(fileName, "%s", UpdateFilePath);//, dp->d_name);
            sprintf(fileName, "%s%s", UpdateFilePath, dp->d_name);
            printf("Found MCU software.File Path is [%s]\r\n", fileName);
			//printf("Found MCU software.File name is [%s]\r\n", dp->d_name);
            closedir(dfd);
            return 0;
        }
    }

    closedir(dfd);
    printf("File not exist.  %s \r\n", strPath.toStdString().c_str());
    return UpdFindFileErr;
}


