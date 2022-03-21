#include "includes.h"
#include <QtGui>
#include <QTextStream>

#include "numbkeyboarddialog.h"
#include "ui_numbkeyboarddialog.h"



QString numb_lower_letter[52]={"1","2","3","4","5","6","7","8","9","0",".","-","=","","q","w","e","r","t","y","u","i",
                            "o","p","[","]","\\","a","s","d","f","g","h","j","k","l",";","\'","","z","x","c","v",
                            "b","n","m",",","/","shift"," "};

QString numb_upper_letter[52]={"!","@","#","$","%","^","&&","*","(",")","_","+","","Q","W","E","R","T","Y","U","I",
                            "O","P","{","}","|","A","S","D","F","G","H","J","K","L",":","\"","","Z","X","C","V",
                            "B","N","M","<",">","?","SHIFT"," "};


NumbKeyboardDialog::NumbKeyboardDialog(QWidget *parent) :
    QDialog(0,Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint),\
    ui(new Ui::NumbKeyboardDialog),\
	button_group(new QButtonGroup(this)),\
	input_method(0),\
	lower_upper(0),\
	page_count(0)
{
    ui->setupUi(this);

    int ret=0;
    m_pEvent = NULL;

    QWidget::setTabOrder(ui->pushButton_n1, ui->pushButton_n2);
    QWidget::setTabOrder(ui->pushButton_n2, ui->pushButton_n3);
    QWidget::setTabOrder(ui->pushButton_n3, ui->pushButton_n4);
    QWidget::setTabOrder(ui->pushButton_n4, ui->pushButton_n5);
    QWidget::setTabOrder(ui->pushButton_n5, ui->pushButton_n6);
    QWidget::setTabOrder(ui->pushButton_n6, ui->pushButton_n7);
    QWidget::setTabOrder(ui->pushButton_n7, ui->pushButton_n8);
    QWidget::setTabOrder(ui->pushButton_n8, ui->pushButton_n9);
	QWidget::setTabOrder(ui->pushButton_n9, ui->pushButton_n0);
	QWidget::setTabOrder(ui->pushButton_n0, ui->pushButton_period);
	QWidget::setTabOrder(ui->pushButton_period, ui->pushButton_backspace);
	QWidget::setTabOrder(ui->pushButton_backspace, ui->pushButton_Cancel);
	QWidget::setTabOrder(ui->pushButton_Cancel, ui->pushButton_ok);
	QWidget::setTabOrder(ui->pushButton_ok, ui->lineEdit_window);

    initGb();
    pinyin_file.setFileName(qApp->applicationDirPath()+QString("/syszuxpinyin"));

    if( !pinyin_file.open(QIODevice::ReadOnly) )
    {
        QMessageBox  msgBox(this);
        QPushButton* pNewBut;
        msgBox.setWindowTitle("错误");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("拼音字库文件不存在!");
        pNewBut = msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
        pNewBut->setMinimumSize(100,30);
        SetMessageBoxFont(&msgBox);
        //msgBox.setMinimumSize(400,100);
        msgBox.exec();
    }

    regExp.setCaseSensitivity(Qt::CaseSensitive);
    regExp.setPattern(QString("([a-z]+)"));

    QString strLine;
    QString strKey;
    QString strVal;
    QTextStream qStream(&pinyin_file);
    while(!qStream.atEnd())
    {
        strLine = qStream.readLine();
        ret = regExp.indexIn(strLine,0,QRegExp::CaretAtZero);
        strKey = regExp.cap(1);
        strVal = strLine.left(ret);
        //pinyin_map.insert(strKey,strVal);
    }
    connect(this,SIGNAL(sendPinyin(QString)),parent,SLOT(confirmString(QString)));
}
void NumbKeyboardDialog::initGb()
{
	QPushButton *pushButton=new QPushButton(this);
	pushButton->hide();
	pushButton=ui->pushButton_n1;
	QFont font("wenquanyi_zen_hei2",30,QFont::Bold);
	ui->lineEdit_window->setFont(font);
	//lineEdit_pinyin->setFont(font);
	ui->lineEdit_window->setFocus();
	for(int i=0;i<14;i++)
	{
		//pushButton->setFont(font);
		//button_vector.push_back(pushButton);
		button_group->addButton(pushButton,i);
		pushButton=qobject_cast<QPushButton *>(pushButton->nextInFocusChain());
	}
	connect(button_group,SIGNAL(buttonClicked(int)),SLOT(buttonClickResponse(int)));
}

void NumbKeyboardDialog::buttonClickResponse(int gemfield)
{
/*
    if(gemfield==1)
    {
        selectHanziPre();
        return;
    }
    else if(gemfield==10)
    {
        selectHanziNext();
        return;
    }
    else if(gemfield<10)
    {
        ui->lineEdit_window->insert(button_vector.at(gemfield-1)->text());
        //lineEdit_pinyin->clear();
        clearString();
        return;
    }
    else if(gemfield==23)
    {
        deleteString();
        return;
    }
    else if(gemfield==59)
    {
         changeLowerUpper();
         return;
    }
    */
    if(gemfield >= 0 && gemfield<=10)
    {
        if(NULL != m_pEvent)
        {
            delete m_pEvent;
        }
        if(lower_upper)
            m_pEvent =new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,numb_upper_letter[gemfield]);
        else
            m_pEvent =new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,numb_lower_letter[gemfield]);
    }
    else if(gemfield==11)
    {
        deleteString();
        return;
    }
    else if(gemfield==13)
    {
        affirmString();
        return;
    }
    else if(gemfield==12)
    {
        OnCancel();
        return;
    }

    else
    {
        return;
    }
    if(input_method)
    {
        //lineEdit_pinyin->setFocus();
        //QApplication::sendEvent(focusWidget(),m_pEvent);
       // matching(lineEdit_pinyin->text());
    }
    else
    {
        ui->lineEdit_window->setFocus();
        if(gemfield>0 && gemfield<=10)
        {
            if(lower_upper)
            {
                ui->lineEdit_window->insert(numb_upper_letter[gemfield]);
            }
            else
            {
                ui->lineEdit_window->insert(numb_lower_letter[gemfield]);
            }
            m_pEvent->accept();
        }
        else
        {
            QApplication::sendEvent(focusWidget(),m_pEvent);
        }
    }
}

void NumbKeyboardDialog::matching(QString gemfield)
{
    //pinyin_list = pinyin_map.values(gemfield);
    changePage(0);
    page_count=0;
}

void NumbKeyboardDialog::changePage(int index)
{
    int count = pinyin_list.size();
    int i=index*8,j=0;
    while(++j != 9 )
    {
        //button_vector.at(j)->setText(tr(pinyin_list.value(count-(++i)).toAscii()));
        button_vector.at(j)->setText(tr(pinyin_list.value(count-(++i)).toLatin1()));
    }
	/*
    if(index==0)
        pushButton_hanzi_left->setEnabled(false);
    else
        pushButton_hanzi_left->setEnabled(true);
    if(pinyin_list.size()>(index*8+8))
        pushButton_hanzi_right->setEnabled(true);
    else
        pushButton_hanzi_right->setEnabled(false);*/
}

void NumbKeyboardDialog::selectHanziPre()
{
    changePage(--page_count);
}

void NumbKeyboardDialog::selectHanziNext()
{
    changePage(++page_count);
}
void NumbKeyboardDialog::clearString()
{
    int i=0;
    while(++i!=9)
        button_vector.at(i)->setText("");
}
void NumbKeyboardDialog::changeInputMethod()
{
/*
    if(pushButton_shift->text()=="SHIFT")
        return;
   lineEdit_pinyin->clear();
   if(pushButton_is_hanzi->text()=="Abc")
       input_method=1,pushButton_is_hanzi->setText("中文");
   else
       input_method=0,pushButton_is_hanzi->setText("Abc");*/
}
void NumbKeyboardDialog::changeLowerUpper()
{
/*
    if(pushButton_shift->text()=="shift")
    {
        lower_upper=1,pushButton_shift->setText("SHIFT");
        input_method=0,pushButton_is_hanzi->setText("Abc");
        int i=9;
        while(++i!=59)
            button_vector.at(i)->setText(syszux_upper_letter[i-10]);
    }
    else
    {
        lower_upper=0,pushButton_shift->setText("shift");
        int i=9;
        while(++i!=59)
            button_vector.at(i)->setText(syszux_lower_letter[i-10]);
    }*/
}
void NumbKeyboardDialog::deleteString()
{
    if(NULL != m_pEvent)
    {
        delete m_pEvent;
    }
    m_pEvent =new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    if(input_method)
    {
        //lineEdit_pinyin->text().isEmpty()?lineEdit_window->setFocus():lineEdit_pinyin->setFocus();
        //QApplication::sendEvent(focusWidget(),m_pEvent);
        //matching(lineEdit_pinyin->text());
    }
    else
    {
        ui->lineEdit_window->setFocus();
        QApplication::sendEvent(focusWidget(),m_pEvent);
        ui->lineEdit_window->setFocus();
    }
}
void NumbKeyboardDialog::affirmString()
{
    emit sendPinyin(ui->lineEdit_window->text());
    this->close();
}

void NumbKeyboardDialog::OnCancel()
{
    this->close();
}

void NumbKeyboardDialog::SetInputMask(QString strMsk)
{
    ui->lineEdit_window->setInputMask(strMsk);
}

void NumbKeyboardDialog::SetDefaultVal(QString strDefVal)
{
    ui->lineEdit_window->setText(strDefVal);
}


NumbKeyboardDialog::~NumbKeyboardDialog()
{
    delete ui;
}
