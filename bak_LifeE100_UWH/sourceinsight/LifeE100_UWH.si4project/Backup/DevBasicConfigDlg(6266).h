#ifndef DEVBASICCONFIGDLG_H
#define DEVBASICCONFIGDLG_H

#include <QDialog>

class QComboBox;
class QLineEdit;
class QTimer;
class DevBasicConfigDlg : public QDialog
{
    Q_OBJECT
public:
    explicit DevBasicConfigDlg(QWidget *parent = 0);
    
public slots:
    void OnClickOK(void);
    void OnClickCancel(void);
	void OnActiveTimer(void);

    void confirmString(QString strIn);
    void OnFocusChanged(QWidget*old,QWidget*now);
    void OnItemEdit(void);
private:
    QTimer*  m_pUpdTimer;

    QComboBox* m_pDevType;//设备类型
    QComboBox* m_pBloPumType;//血泵类型
    QComboBox* m_pArteryType;//动脉血泵类型
    QComboBox* m_pVeinType;   //静脉血泵类型
    QComboBox* m_pWatTRooType;   //水浴类型

	QLineEdit* m_pAPumCount;
	QLineEdit* m_pVPumCount;
	QLineEdit* m_pWatCount;

	QLineEdit* m_pMonSavCount;

    QLineEdit* m_pBrdRate[5];//通信速率
    QLineEdit* m_pComPort[5];

	QWidget*   m_pCurLineEdit;
};

#endif // DEVBASICCONFIGDLG_H
