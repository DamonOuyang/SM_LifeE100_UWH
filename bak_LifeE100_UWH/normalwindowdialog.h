#ifndef NORMALWINDOWDIALOG_H
#define NORMALWINDOWDIALOG_H

#include <QDialog>

namespace Ui {
class NormalWindowDialog;
}

class NormalWindowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NormalWindowDialog(QWidget *parent = 0);
    ~NormalWindowDialog();

private slots:
    void on_lockBoxBackBt_clicked();

private:
    Ui::NormalWindowDialog *ui;
};

#endif // NORMALWINDOWDIALOG_H
