#include "myTableview.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QScrollBar>
//#include <QDebug>

MyTableView::MyTableView(QWidget *parent) : QTableView(parent)
{
    m_model=new QStandardItemModel;

    QStringList headList;
    headList<<"bottomView col 1"<<"bottomView col 2"<<"bottomView col 3"
        <<"bottomView col 4"<<"bottomView col 5"<<"bottomView col 6"
        <<"bottomView col 7"<<"bottomView col 8"<<"bottomView col 9";

    m_model->setHorizontalHeaderLabels(headList);

    for(int i=0;i<100;i++){
        for(int j=0;j<9;j++){
            QStandardItem *newItem=new QStandardItem("row: "+QString::number(i+1)+"  col: "+QString::number(j+1));
            m_model->setItem(i,j,newItem);
        }
    }

    setModel(m_model);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    init();
    connect(m_topTableView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            m_topTableView->verticalScrollBar(), &QAbstractSlider::setValue);
}

void MyTableView::updateTopTableViewGeometry()
{
    m_topTableView->setGeometry(verticalHeader()->width()+frameWidth()
                                ,frameWidth()
                                ,columnWidth(0)
                                ,viewport()->height()+horizontalHeader()->height());
}

void MyTableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    updateTopTableViewGeometry();
}

void MyTableView::init()
{
    m_topTableView=new QTableView(this);
    m_topTableView->setFocusPolicy(Qt::NoFocus);
    m_topTableView->verticalHeader()->hide();
    m_topTableView->setModel(m_model);
    m_topTableView->setStyleSheet("QTableView { border: none;"
                                  "background-color: rgb(255,255,0);"
                                  "selection-background-color: rgb(0,255,255)}");
    m_topTableView->setSelectionModel(selectionModel());

    for(int i=1;i<m_model->columnCount();i++){
        m_topTableView->setColumnHidden(i,true);
    }

    m_topTableView->setColumnWidth(0,columnWidth(0));
    m_topTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_topTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateTopTableViewGeometry();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    m_topTableView->setVerticalScrollMode(ScrollPerPixel);
}
