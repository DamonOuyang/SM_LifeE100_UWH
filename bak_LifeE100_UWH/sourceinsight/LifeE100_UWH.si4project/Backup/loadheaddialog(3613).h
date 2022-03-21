#ifndef LOADHEADDIALOG_H
#define LOADHEADDIALOG_H

#include <QDialog>

namespace Ui {
class LoadHeadDialog;
}

class LoadHeadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadHeadDialog(QWidget *parent = 0);
    ~LoadHeadDialog();

private slots:
    void on_loadLastBut_clicked();

    void on_loadNextBut_clicked();

private:
    Ui::LoadHeadDialog *ui;
};

#endif // LOADHEADDIALOG_H
