#include "QtGui"
#include "configbasicframe.h"
#include "ui_configbasicframe.h"

ConfigBasicFrame::ConfigBasicFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConfigBasicFrame)
{
    ui->setupUi(this);

    m_pDataPath  = new QLineEdit(this);
	m_pDataPath->setReadOnly(true);
	m_pDataPath->setGeometry(QRect(155, 85, 100, 36));

    m_pAlarmPath = new QLineEdit(this);
	m_pAlarmPath->setReadOnly(true);
	m_pAlarmPath->setGeometry(QRect(155, 155, 100, 36));

	m_pDataTimeEdit = new QLineEdit(this);
	m_pDataTimeEdit->setGeometry(QRect(155, 225, 180, 36));

	m_pAPumCount = new QLineEdit(this);
	m_pAPumCount->setReadOnly(true);
	m_pAPumCount->setGeometry(QRect(496, 85, 100, 36));

	m_pVPumCount = new QLineEdit(this);
	m_pVPumCount->setReadOnly(true);
	m_pVPumCount->setGeometry(QRect(496, 155, 100, 36));
	
	m_pWatCount  = new QLineEdit(this);
	m_pWatCount->setReadOnly(true);
	m_pWatCount->setGeometry(QRect(496, 225, 100, 36));

	m_pMonSavTmt	=  new QLineEdit(this);
	m_pMonSavTmt->setGeometry(QRect(838, 85, 100, 36));

	
    m_pAlmEnFlag    = CreateComboBox(this);
	m_pAlmEnFlag->setGeometry(QRect(838, 155, 100, 36));
    m_pAlmEnFlag->addItem("禁用");
    m_pAlmEnFlag->addItem("启用");

}

ConfigBasicFrame::~ConfigBasicFrame()
{
    delete ui;
}
