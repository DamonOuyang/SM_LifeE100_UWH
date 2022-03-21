#include "numbkeyboarddialog.h"
#include "ui_numbkeyboarddialog.h"



QString syszux_lower_letter[52]={"1","2","3","4","5","6","7","8","9","0","-","=","","q","w","e","r","t","y","u","i",
                            "o","p","[","]","\\","a","s","d","f","g","h","j","k","l",";","\'","","z","x","c","v",
                            "b","n","m",",",".","/","shift"," "};

QString syszux_upper_letter[52]={"!","@","#","$","%","^","&&","*","(",")","_","+","","Q","W","E","R","T","Y","U","I",
                            "O","P","{","}","|","A","S","D","F","G","H","J","K","L",":","\"","","Z","X","C","V",
                            "B","N","M","<",">","?","SHIFT"," "};

NumbKeyboardDialog::NumbKeyboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumbKeyboardDialog),\
	button_group(new QButtonGroup(this)),\
	input_method(0),\
	lower_upper(0),\
	page_count(0)
{
    ui->setupUi(this);

    int ret=0;
    m_pEvent = NULL;

    QWidget::setTabOrder(pushButton_n1, pushButton_n2);
    QWidget::setTabOrder(pushButton_n2, pushButton_n3);
    QWidget::setTabOrder(pushButton_n3, pushButton_n4);
    QWidget::setTabOrder(pushButton_n4, pushButton_n5);
    QWidget::setTabOrder(pushButton_n5, pushButton_n6);
    QWidget::setTabOrder(pushButton_n6, pushButton_n7);
    QWidget::setTabOrder(pushButton_n7, pushButton_n8);
    QWidget::setTabOrder(pushButton_n8, pushButton_n9);
	QWidget::setTabOrder(pushButton_n9, pushButton_n0);
	QWidget::setTabOrder(pushButton_n0, pushButton_period);
	QWidget::setTabOrder(pushButton_period, pushButton_backspace);
	QWidget::setTabOrder(pushButton_backspace, pushButton_Cancel);
	QWidget::setTabOrder(pushButton_Cancel, pushButton_ok);
	QWidget::setTabOrder(pushButton_ok, lineEdit_window);
	
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
        pinyin_map.insert(strKey,strVal);
    }
    connect(this,SIGNAL(sendPinyin(QString)),im,SLOT(confirmString(QString)));

}
void NumbKeyboardDialog::initGb()
{
	QPushButton *pushButton=new QPushButton(this);
	pushButton->hide();
	pushButton=pushButton_hanzi_left;
	QFont font("wenquanyi_zen_hei2",30,QFont::Bold);
	lineEdit_window->setFont(font);
	//lineEdit_pinyin->setFont(font);
	lineEdit_window->setFocus();
	for(int i=1;i<68;i++)
	{
		pushButton->setFont(font);
		button_vector.push_back(pushButton);
		button_group->addButton(pushButton,i);
		pushButton=qobject_cast<QPushButton *>(pushButton->nextInFocusChain());
	}
	connect(button_group,SIGNAL(buttonClicked(int)),SLOT(buttonClickResponse(int)));
}

void NumbKeyboardDialog::buttonClickResponse(int gemfield)
{
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
        lineEdit_window->insert(button_vector.at(gemfield-1)->text());
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
    else if(gemfield>10 && gemfield<=60)
    {
        if(NULL != m_pEvent)
        {
            delete m_pEvent;
        }
        if(lower_upper)
            m_pEvent =new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,syszux_upper_letter[gemfield-11]);
        else
            m_pEvent =new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,syszux_lower_letter[gemfield-11]);
    }
    else if(gemfield==61)
    {
        changeInputMethod();
        return;
    }
    else if(gemfield==62)
    {
        affirmString();
        return;
    }
    else if(gemfield==67)
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
        lineEdit_window->setFocus();
        if(gemfield>10 && gemfield<=60)
        {
            if(lower_upper)
            {
                lineEdit_window->insert(syszux_upper_letter[gemfield-11]);
            }
            else
            {
                lineEdit_window->insert(syszux_lower_letter[gemfield-11]);
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
    pinyin_list = pinyin_map.values(gemfield);
    changePage(0);
    page_count=0;
}

void SyszuxPinyin::changePage(int index)
{
    int count = pinyin_list.size();
    int i=index*8,j=0;
    while(++j != 9 )
    {
        //button_vector.at(j)->setText(tr(pinyin_list.value(count-(++i)).toAscii()));
        button_vector.at(j)->setText(tr(pinyin_list.value(count-(++i)).toLatin1()));
    }
    if(index==0)
        pushButton_hanzi_left->setEnabled(false);
    else
        pushButton_hanzi_left->setEnabled(true);
    if(pinyin_list.size()>(index*8+8))
        pushButton_hanzi_right->setEnabled(true);
    else
        pushButton_hanzi_right->setEnabled(false);
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
    if(pushButton_shift->text()=="SHIFT")
        return;
   //lineEdit_pinyin->clear();
   if(pushButton_is_hanzi->text()=="Abc")
       input_method=1,pushButton_is_hanzi->setText("中文");
   else
       input_method=0,pushButton_is_hanzi->setText("Abc");
}
void NumbKeyboardDialog::changeLowerUpper()
{
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
    }
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
        lineEdit_window->setFocus();
        QApplication::sendEvent(focusWidget(),m_pEvent);
        lineEdit_window->setFocus();
    }
}
void NumbKeyboardDialog::affirmString()
{
    emit sendPinyin(lineEdit_window->text());
    this->close();
}

void NumbKeyboardDialog::OnCancel()
{
    this->close();
}

void NumbKeyboardDialog::SetInputMask(QString strMsk)
{
    lineEdit_window->setInputMask(strMsk);
}

void NumbKeyboardDialog::SetDefaultVal(QString strDefVal)
{
    lineEdit_window->setText(strDefVal);
}


NumbKeyboardDialog::~NumbKeyboardDialog()
{
    delete ui;
}
