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
    void HideLog(void);
private slots:
    void on_loadLastBut_clicked();

    void on_loadNextBut_clicked();

    void on_loadOkBut_clicked();

    void on_loseAllBut_clicked();

private:
    Ui::LoadHeadDialog *ui;
    void LoadingImg(unsigned char unStep);
	unsigned char m_unStep;
};

#endif // LOADHEADDIALOG_H
