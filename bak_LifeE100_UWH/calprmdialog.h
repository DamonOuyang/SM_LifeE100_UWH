#ifndef CALPRMDIALOG_H
#define CALPRMDIALOG_H

#include <QDialog>
#include "includes.h"
#include <QTimer>

namespace Ui {
class calPrmDialog;
}


class QTimer;
class calPrmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit calPrmDialog(QWidget *parent = 0);
    ~calPrmDialog();
public slots:
	void OnUpdData(void);

private slots:
    void on_closeButton_clicked();
    void on_setButton_clicked();

private:
    Ui::calPrmDialog *ui;
	QTimer*  m_pUpdTimer;
};

#endif // CALPRMDIALOG_H
