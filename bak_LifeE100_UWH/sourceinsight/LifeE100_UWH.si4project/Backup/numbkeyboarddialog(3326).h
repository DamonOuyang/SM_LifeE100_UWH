#ifndef NUMBKEYBOARDDIALOG_H
#define NUMBKEYBOARDDIALOG_H

#include <QDialog>

namespace Ui {
class NumbKeyboardDialog;
}

class NumbKeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NumbKeyboardDialog(QWidget *parent = 0);
    ~NumbKeyboardDialog();

private:
    Ui::NumbKeyboardDialog *ui;
};

#endif // NUMBKEYBOARDDIALOG_H
