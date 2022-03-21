#ifndef CALPRMDIALOG_H
#define CALPRMDIALOG_H

#include <QDialog>

namespace Ui {
class calPrmDialog;
}

class calPrmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit calPrmDialog(QWidget *parent = 0);
    ~calPrmDialog();

private slots:
    void on_closeButton_clicked();

    void on_setButton_clicked();

private:
    Ui::calPrmDialog *ui;
};

#endif // CALPRMDIALOG_H
