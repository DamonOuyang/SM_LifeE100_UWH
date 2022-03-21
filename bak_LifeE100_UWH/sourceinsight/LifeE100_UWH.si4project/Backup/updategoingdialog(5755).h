#ifndef UPDATEGOINGDIALOG_H
#define UPDATEGOINGDIALOG_H

#include <QDialog>

namespace Ui {
class UpdateGoingDialog;
}

class UpdateGoingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateGoingDialog(QWidget *parent = 0);
    ~UpdateGoingDialog();

private:
    Ui::UpdateGoingDialog *ui;
};

#endif // UPDATEGOINGDIALOG_H
