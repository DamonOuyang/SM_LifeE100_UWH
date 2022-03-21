/***************************************************************************
**
**  <SYSZUXpinyin 1.0 , a chinese input method based on Qt for Embedded linux>
**  Copyright (C) <2010> <Gemfield> <gemfield@civilnet.cn>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as published
**  by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**  If you have questions regarding the use of this file, please contact
**  Gemfield at gemfield@civilnet.cn or post your questions at
**  http://civilnet.cn/syszux/bbs
**
****************************************************************************/
#include "includes.h"
#include "syszuxpinyin.h"
#include <QtGui>
#include <QTextStream>

QString syszux_lower_letter[52]={"1","2","3","4","5","6","7","8","9","0","-","=","","q","w","e","r","t","y","u","i",
                            "o","p","[","]","\\","a","s","d","f","g","h","j","k","l",";","\'","","z","x","c","v",
                            "b","n","m",",",".","/","shift"," "};
QString syszux_upper_letter[52]={"!","@","#","$","%","^","&&","*","(",")","_","+","","Q","W","E","R","T","Y","U","I",
                            "O","P","{","}","|","A","S","D","F","G","H","J","K","L",":","\"","","Z","X","C","V",
                            "B","N","M","<",">","?","SHIFT"," "};
SyszuxPinyin::SyszuxPinyin(QWidget* im) :\
    QDialog(0,Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint),\
    button_group(new QButtonGroup(this)),\
    input_method(0),\
    lower_upper(0),\
    page_count(0)
{
    int ret=0;
    m_pEvent = NULL;
    setupUi(this);
    QWidget::setTabOrder(pushButton_hanzi_left, pushButton_hanzi_1);
    QWidget::setTabOrder(pushButton_hanzi_1, pushButton_hanzi_2);
    QWidget::setTabOrder(pushButton_hanzi_2, pushButton_hanzi_3);
    QWidget::setTabOrder(pushButton_hanzi_3, pushButton_hanzi_4);
    QWidget::setTabOrder(pushButton_hanzi_4, pushButton_hanzi_5);
    QWidget::setTabOrder(pushButton_hanzi_5, pushButton_hanzi_6);
    QWidget::setTabOrder(pushButton_hanzi_6, pushButton_hanzi_7);
    QWidget::setTabOrder(pushButton_hanzi_7, pushButton_hanzi_8);
    QWidget::setTabOrder(pushButton_hanzi_8, pushButton_hanzi_right);
    QWidget::setTabOrder(pushButton_hanzi_right, pushButton_n1);
    QWidget::setTabOrder(pushButton_n1, pushButton_n2);
    QWidget::setTabOrder(pushButton_n2, pushButton_n3);
    QWidget::setTabOrder(pushButton_n3, pushButton_n4);
    QWidget::setTabOrder(pushButton_n4, pushButton_n5);
    QWidget::setTabOrder(pushButton_n5, pushButton_n6);
    QWidget::setTabOrder(pushButton_n6, pushButton_n7);
    QWidget::setTabOrder(pushButton_n7, pushButton_n8);
    QWidget::setTabOrder(pushButton_n8, pushButton_n9);
    QWidget::setTabOrder(pushButton_n9, pushButton_n0);
    QWidget::setTabOrder(pushButton_n0, pushButton_gang);
    QWidget::setTabOrder(pushButton_gang, pushButton_deng);
    QWidget::setTabOrder(pushButton_deng, pushButton_backspace);
    QWidget::setTabOrder(pushButton_backspace, pushButton_q);
    QWidget::setTabOrder(pushButton_q, pushButton_w);
    QWidget::setTabOrder(pushButton_w, pushButton_e);
    QWidget::setTabOrder(pushButton_e, pushButton_r);
    QWidget::setTabOrder(pushButton_r, pushButton_t);
    QWidget::setTabOrder(pushButton_t, pushButton_y);
    QWidget::setTabOrder(pushButton_y, pushButton_u);
    QWidget::setTabOrder(pushButton_u, pushButton_i);
    QWidget::setTabOrder(pushButton_i, pushButton_o);
    QWidget::setTabOrder(pushButton_o, pushButton_p);
    QWidget::setTabOrder(pushButton_p, pushButton_zuokuo);
    QWidget::setTabOrder(pushButton_zuokuo, pushButton_youkuo);
    QWidget::setTabOrder(pushButton_youkuo, pushButton_backsplash);
    QWidget::setTabOrder(pushButton_backsplash, pushButton_a);
    QWidget::setTabOrder(pushButton_a, pushButton_s);
    QWidget::setTabOrder(pushButton_s, pushButton_d);
    QWidget::setTabOrder(pushButton_d, pushButton_f);
    QWidget::setTabOrder(pushButton_f, pushButton_g);
    QWidget::setTabOrder(pushButton_g, pushButton_h);
    QWidget::setTabOrder(pushButton_h, pushButton_j);
    QWidget::setTabOrder(pushButton_j, pushButton_k);
    QWidget::setTabOrder(pushButton_k, pushButton_l);
    QWidget::setTabOrder(pushButton_l, pushButton_semicolon);
    QWidget::setTabOrder(pushButton_semicolon, pushButton_quote);
    QWidget::setTabOrder(pushButton_quote, pushButton_enter);
    QWidget::setTabOrder(pushButton_enter, pushButton_z);
    QWidget::setTabOrder(pushButton_z, pushButton_x);
    QWidget::setTabOrder(pushButton_x, pushButton_c);
    QWidget::setTabOrder(pushButton_c, pushButton_v);
    QWidget::setTabOrder(pushButton_v, pushButton_b);
    QWidget::setTabOrder(pushButton_b, pushButton_n);
    QWidget::setTabOrder(pushButton_n, pushButton_m);
    QWidget::setTabOrder(pushButton_m, pushButton_comma);
    QWidget::setTabOrder(pushButton_comma, pushButton_period);
    QWidget::setTabOrder(pushButton_period, pushButton_splash);
    QWidget::setTabOrder(pushButton_splash, pushButton_shift);
    QWidget::setTabOrder(pushButton_shift, pushButton_whitespace);
    QWidget::setTabOrder(pushButton_whitespace, pushButton_is_hanzi);
    QWidget::setTabOrder(pushButton_is_hanzi, pushButton_ok);
    QWidget::setTabOrder(pushButton_ok, pushButton_left);
    QWidget::setTabOrder(pushButton_left, pushButton_down);
    QWidget::setTabOrder(pushButton_down, pushButton_right);
    QWidget::setTabOrder(pushButton_right, pushButton_up);
    QWidget::setTabOrder(pushButton_up, pushButton_Cancel);
    QWidget::setTabOrder(pushButton_Cancel,lineEdit_pinyin);
    QWidget::setTabOrder(lineEdit_pinyin, lineEdit_window);
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
SyszuxPinyin::~SyszuxPinyin()
{
}
void SyszuxPinyin::initGb()
{
    QPushButton *pushButton=new QPushButton(this);
    pushButton->hide();
    pushButton=pushButton_hanzi_left;
    QFont font("wenquanyi_zen_hei2",30,QFont::Bold);
    lineEdit_window->setFont(font);
    lineEdit_pinyin->setFont(font);
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
void SyszuxPinyin::buttonClickResponse(int gemfield)
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
        lineEdit_pinyin->clear();
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
    else if(gemfield>62&&gemfield<67)
    {
        if(NULL != m_pEvent)
        {
            delete m_pEvent;
        }
        switch(gemfield)
        {
        case 63:
            m_pEvent=new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            break;
        case 64:
            m_pEvent=new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
            break;
        case 65:
            m_pEvent=new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            break;
        case 66:
            m_pEvent=new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
            break;
        }
    }
    else
    {
        return;
    }
    if(input_method)
    {
        lineEdit_pinyin->setFocus();
        QApplication::sendEvent(focusWidget(),m_pEvent);
        matching(lineEdit_pinyin->text());
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
void SyszuxPinyin::matching(QString gemfield)
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

void SyszuxPinyin::selectHanziPre()
{
    changePage(--page_count);
}

void SyszuxPinyin::selectHanziNext()
{
    changePage(++page_count);
}
void SyszuxPinyin::clearString()
{
    int i=0;
    while(++i!=9)
        button_vector.at(i)->setText("");
}
void SyszuxPinyin::changeInputMethod()
{
    if(pushButton_shift->text()=="SHIFT")
        return;
   lineEdit_pinyin->clear();
   if(pushButton_is_hanzi->text()=="Abc")
       input_method=1,pushButton_is_hanzi->setText("中文");
   else
       input_method=0,pushButton_is_hanzi->setText("Abc");
}
void SyszuxPinyin::changeLowerUpper()
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
void SyszuxPinyin::deleteString()
{
    if(NULL != m_pEvent)
    {
        delete m_pEvent;
    }
    m_pEvent =new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    if(input_method)
    {
        lineEdit_pinyin->text().isEmpty()?lineEdit_window->setFocus():lineEdit_pinyin->setFocus();
        QApplication::sendEvent(focusWidget(),m_pEvent);
        matching(lineEdit_pinyin->text());
    }
    else
    {
        lineEdit_window->setFocus();
        QApplication::sendEvent(focusWidget(),m_pEvent);
        lineEdit_window->setFocus();
    }
}
void SyszuxPinyin::affirmString()
{
    emit sendPinyin(lineEdit_window->text());
    this->close();
}

void SyszuxPinyin::OnCancel()
{
    this->close();
}

void SyszuxPinyin::SetInputMask(QString strMsk)
{
    lineEdit_window->setInputMask(strMsk);
}

void SyszuxPinyin::SetDefaultVal(QString strDefVal)
{
    lineEdit_window->setText(strDefVal);
}



