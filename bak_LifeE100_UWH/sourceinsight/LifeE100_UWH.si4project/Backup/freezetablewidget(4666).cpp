
#include "freezetablewidget.h"
#include "includes.h"
#include <QScrollBar>
#include <QHeaderView>

//! [constructor]
FreezeTableWidget::FreezeTableWidget(QAbstractItemModel * model)
{
      setModel(model);
      frozenTableView = new QTableView(this);

      init();
	  updateSectionWidth(0,0,220);
	  //updateSectionWidth(0,0,220);
      //connect(horizontalHeader(),&QHeaderView::sectionResized,this,&FreezeTableWidget::updateSectionWidth);
      connect(horizontalHeader(), SIGNAL(&QHeaderView::sectionResized(int,int,int)),this,SLOT(updateSectionWidth(int,int,int)));
      //connect(verticalHeader(),&QHeaderView::sectionResized, this,&FreezeTableWidget::updateSectionHeight);
      //connect(verticalHeader(), SIGNAL(QHeaderView::sectionResized(int,int,int)),this,SLOT(updateSectionHeight(int,int,int)));

//	  connect(frozenTableView->verticalScrollBar(), &QAbstractSlider::valueChanged,verticalScrollBar(), &QAbstractSlider::setValue);
      //connect(verticalScrollBar(), &QAbstractSlider::valueChanged,frozenTableView->verticalScrollBar(), &QAbstractSlider::setValue);
      //connect(verticalScrollBar(), SIGNAL(QAbstractSlider::valueChanged(int)),frozenTableView->verticalScrollBar(),SLOT(QAbstractSlider::setValue(int)));
}
//! [constructor]

FreezeTableWidget::~FreezeTableWidget()
{
      delete frozenTableView;
}

//! [init part1]
void FreezeTableWidget::init()
{
      frozenTableView->setModel(model());
      frozenTableView->setFocusPolicy(Qt::NoFocus);
      frozenTableView->verticalHeader()->hide();
      //frozenTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

      viewport()->stackUnder(frozenTableView);
//! [init part1]

//! [init part2]
      frozenTableView->setStyleSheet("QTableView { border: none;"
                                     "background-color: #8EDE21;"
                                     "selection-background-color: #999}"); //for demo purposes
      frozenTableView->setSelectionModel(selectionModel());
      for (int col = 1; col < model()->columnCount(); ++col)
            frozenTableView->setColumnHidden(col, true);

      frozenTableView->setColumnWidth(0, columnWidth(0) );

      frozenTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      frozenTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      frozenTableView->show();

      updateFrozenTableGeometry();

      setHorizontalScrollMode(ScrollPerPixel);
      setVerticalScrollMode(ScrollPerPixel);
      frozenTableView->setVerticalScrollMode(ScrollPerPixel);
}
//! [init part2]


//! [sections]
void FreezeTableWidget::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{
      printf("updateSectionWidth logicalIndex:%d newSize%d \r\n",logicalIndex,newSize);
      if(logicalIndex == 0)
      {
      printf("-------updateSectionWidth logicalIndex:%d newSize%d \r\n",logicalIndex,newSize);
            frozenTableView->setColumnWidth(0, newSize);
            updateFrozenTableGeometry();
      }
}

void FreezeTableWidget::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{
	printf("```````updateSectionHeight logicalIndex:%d newSize%d \r\n",logicalIndex,newSize);

      frozenTableView->setRowHeight(logicalIndex, newSize);
}
//! [sections]


//! [resize]
void FreezeTableWidget::resizeEvent(QResizeEvent * event)
{
      QTableView::resizeEvent(event);
      updateFrozenTableGeometry();
 }
//! [resize]


//! [navigate]
QModelIndex FreezeTableWidget::moveCursor(CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
      QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

      if (cursorAction == MoveLeft && current.column() > 0
              && visualRect(current).topLeft().x() < frozenTableView->columnWidth(0) ){
            const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                                 - frozenTableView->columnWidth(0);
            horizontalScrollBar()->setValue(newValue);
      }
      return current;
}
//! [navigate]

void FreezeTableWidget::scrollTo (const QModelIndex & index, ScrollHint hint){
    if (index.column() > 0)
        QTableView::scrollTo(index, hint);
}

//! [geometry]
void FreezeTableWidget::updateFrozenTableGeometry()
{
      frozenTableView->setGeometry(verticalHeader()->width() + frameWidth(),
                                   frameWidth(), columnWidth(0),
                                   viewport()->height()+horizontalHeader()->height());
}
//! [geometry]


