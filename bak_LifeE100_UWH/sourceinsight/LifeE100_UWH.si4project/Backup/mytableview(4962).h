#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>

QT_BEGIN_NAMESPACE
class QStandardItemModel;
QT_END_NAMESPACE

class MyTableView : public QTableView
{
    Q_OBJECT
public:
    MyTableView(QWidget *parent = 0);

protected:
    void updateTopTableViewGeometry();
    void resizeEvent(QResizeEvent *event)Q_DECL_OVERRIDE;

private:
    void init();
    QTableView *m_topTableView;
    QStandardItemModel *m_model;

};

#endif // MYTABLEVIEW_H
