#ifndef UNLOCKINFODIALOG_H
#define UNLOCKINFODIALOG_H

#include <QDialog>

namespace Ui {
class unlockInfoDialog;
}

class unlockInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit unlockInfoDialog(QWidget *parent = 0);
    ~unlockInfoDialog();

private slots:
    void on_cancelButton_clicked();

    void on_unlockButton_clicked();

private:
    Ui::unlockInfoDialog *ui;
};

#endif // UNLOCKINFODIALOG_H
