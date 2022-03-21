#ifndef NUMBKEYBOARDDIALOG_H
#define NUMBKEYBOARDDIALOG_H
#include <QFile>
#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class NumbKeyboardDialog;
}

class NumbKeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NumbKeyboardDialog(QWidget *parent = 0);
    ~NumbKeyboardDialog();
    void changePage(int index);
    void matching(QString gemfield);
    void initGb();
    void selectHanziPre();
    void selectHanziNext();
    void changeInputMethod();
    void changeLowerUpper();
    void clearString();
    void affirmString();
    void deleteString();
    void OnCancel();
    void SetInputMask(QString strMsk);
    void SetDefaultVal(QString strDefVal);	
public slots:
	void buttonClickResponse(int gemfield);
signals:
	void sendPinyin(QString gemfield);

private:
    Ui::NumbKeyboardDialog *ui;

    QFile pinyin_file;
    QKeyEvent *m_pEvent;
    QRegExp regExp;
    QButtonGroup *button_group;
    //QMultiMap<QString,QString> pinyin_map;
    QList<QString> pinyin_list;
    QVector<QPushButton*> button_vector;
    int input_method,lower_upper,page_count;
};

#endif // NUMBKEYBOARDDIALOG_H
