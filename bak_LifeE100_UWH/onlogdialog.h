#ifndef ONLOGDIALOG_H
#define ONLOGDIALOG_H

#include <QDialog>

namespace Ui {
class OnLogDialog;
}

class OnLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnLogDialog(QWidget *parent = 0);
    ~OnLogDialog();
    void StopLogMovie(void);
	void StartLogMovie(void);
private:
    Ui::OnLogDialog *ui;
	QMovie *m_pMovie;
};

#endif // ONLOGDIALOG_H
