#ifndef CCONFIGPANEL_H
#define CCONFIGPANEL_H

#include <QFrame>
#include <QModelIndex>

class QListView;
class QStackedWidget;
class QTimer;
class CConfigPanel : public QFrame
{
    Q_OBJECT
public:
    explicit CConfigPanel(QWidget *parent = 0);
	void FlashSubDevPrm(void);
    QListView*  m_pListView;
signals:
    //void exitLoginFlg(void);
    
public slots:
    void OnItemChanged(const QModelIndex & index );
    void OnUpdData(void);
	void ExitLoginFun(void);
private:
    QStackedWidget* m_pPagesWidget;
    QTimer*  m_pUpdTimer;
};

#endif // CCONFIGPANEL_H
