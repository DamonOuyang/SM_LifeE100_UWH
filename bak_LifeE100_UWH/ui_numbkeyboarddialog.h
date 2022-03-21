/********************************************************************************
** Form generated from reading UI file 'numbkeyboarddialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMBKEYBOARDDIALOG_H
#define UI_NUMBKEYBOARDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NumbKeyboardDialog
{
public:
    QFrame *entrFrame;
    QPushButton *pushButton_n4;
    QPushButton *pushButton_n5;
    QPushButton *pushButton_n6;
    QPushButton *pushButton_n1;
    QPushButton *pushButton_n2;
    QPushButton *pushButton_n3;
    QPushButton *pushButton_n7;
    QPushButton *pushButton_n8;
    QPushButton *pushButton_n9;
    QPushButton *pushButton_n0;
    QPushButton *pushButton_period;
    QPushButton *pushButton_backspace;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_ok;
    QLineEdit *lineEdit_window;

    void setupUi(QDialog *NumbKeyboardDialog)
    {
        if (NumbKeyboardDialog->objectName().isEmpty())
            NumbKeyboardDialog->setObjectName(QString::fromUtf8("NumbKeyboardDialog"));
        NumbKeyboardDialog->resize(1280, 760);
        NumbKeyboardDialog->setStyleSheet(QString::fromUtf8("#NumbKeyboardDialog\n"
"{\n"
"background-image: url(:/images/Keyboard/keyboardWindowBg.png);\n"
"}"));
        entrFrame = new QFrame(NumbKeyboardDialog);
        entrFrame->setObjectName(QString::fromUtf8("entrFrame"));
        entrFrame->setGeometry(QRect(445, 123, 390, 514));
        entrFrame->setStyleSheet(QString::fromUtf8("#entrFrame\n"
"{\n"
"background-image: url(:/images/Keyboard/keyEntr_Bg.png);\n"
"}"));
        entrFrame->setFrameShape(QFrame::NoFrame);
        entrFrame->setFrameShadow(QFrame::Raised);
        pushButton_n4 = new QPushButton(entrFrame);
        pushButton_n4->setObjectName(QString::fromUtf8("pushButton_n4"));
        pushButton_n4->setGeometry(QRect(13, 170, 120, 85));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pushButton_n4->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Keyboard/4up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/images/Keyboard/4dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n4->setIcon(icon);
        pushButton_n4->setIconSize(QSize(120, 85));
        pushButton_n5 = new QPushButton(entrFrame);
        pushButton_n5->setObjectName(QString::fromUtf8("pushButton_n5"));
        pushButton_n5->setGeometry(QRect(135, 170, 120, 85));
        pushButton_n5->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Keyboard/5up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/images/Keyboard/5dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n5->setIcon(icon1);
        pushButton_n5->setIconSize(QSize(120, 85));
        pushButton_n6 = new QPushButton(entrFrame);
        pushButton_n6->setObjectName(QString::fromUtf8("pushButton_n6"));
        pushButton_n6->setGeometry(QRect(257, 170, 120, 85));
        pushButton_n6->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Keyboard/6up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/images/Keyboard/6dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n6->setIcon(icon2);
        pushButton_n6->setIconSize(QSize(120, 85));
        pushButton_n1 = new QPushButton(entrFrame);
        pushButton_n1->setObjectName(QString::fromUtf8("pushButton_n1"));
        pushButton_n1->setGeometry(QRect(13, 85, 120, 85));
        pushButton_n1->setFont(font);
        pushButton_n1->setFocusPolicy(Qt::ClickFocus);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/Keyboard/1up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/images/Keyboard/1dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n1->setIcon(icon3);
        pushButton_n1->setIconSize(QSize(120, 85));
        pushButton_n2 = new QPushButton(entrFrame);
        pushButton_n2->setObjectName(QString::fromUtf8("pushButton_n2"));
        pushButton_n2->setGeometry(QRect(135, 85, 120, 85));
        pushButton_n2->setFont(font);
        pushButton_n2->setFocusPolicy(Qt::ClickFocus);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/Keyboard/2up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/images/Keyboard/2dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n2->setIcon(icon4);
        pushButton_n2->setIconSize(QSize(120, 85));
        pushButton_n3 = new QPushButton(entrFrame);
        pushButton_n3->setObjectName(QString::fromUtf8("pushButton_n3"));
        pushButton_n3->setGeometry(QRect(257, 85, 120, 85));
        pushButton_n3->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/Keyboard/3up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/images/Keyboard/3dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n3->setIcon(icon5);
        pushButton_n3->setIconSize(QSize(120, 85));
        pushButton_n7 = new QPushButton(entrFrame);
        pushButton_n7->setObjectName(QString::fromUtf8("pushButton_n7"));
        pushButton_n7->setGeometry(QRect(13, 255, 120, 85));
        pushButton_n7->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/Keyboard/7up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/images/Keyboard/7dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n7->setIcon(icon6);
        pushButton_n7->setIconSize(QSize(120, 85));
        pushButton_n8 = new QPushButton(entrFrame);
        pushButton_n8->setObjectName(QString::fromUtf8("pushButton_n8"));
        pushButton_n8->setGeometry(QRect(135, 255, 120, 85));
        pushButton_n8->setFont(font);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/Keyboard/8up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/images/Keyboard/8dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n8->setIcon(icon7);
        pushButton_n8->setIconSize(QSize(120, 85));
        pushButton_n9 = new QPushButton(entrFrame);
        pushButton_n9->setObjectName(QString::fromUtf8("pushButton_n9"));
        pushButton_n9->setGeometry(QRect(257, 255, 120, 85));
        pushButton_n9->setFont(font);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/Keyboard/9up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/images/Keyboard/9dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n9->setIcon(icon8);
        pushButton_n9->setIconSize(QSize(120, 85));
        pushButton_n0 = new QPushButton(entrFrame);
        pushButton_n0->setObjectName(QString::fromUtf8("pushButton_n0"));
        pushButton_n0->setGeometry(QRect(13, 340, 120, 85));
        pushButton_n0->setFont(font);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/Keyboard/0up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/images/Keyboard/0dn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_n0->setIcon(icon9);
        pushButton_n0->setIconSize(QSize(120, 85));
        pushButton_period = new QPushButton(entrFrame);
        pushButton_period->setObjectName(QString::fromUtf8("pushButton_period"));
        pushButton_period->setGeometry(QRect(135, 340, 120, 85));
        pushButton_period->setFont(font);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/Keyboard/dotup.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon10.addFile(QString::fromUtf8(":/images/Keyboard/dotdn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_period->setIcon(icon10);
        pushButton_period->setIconSize(QSize(120, 85));
        pushButton_backspace = new QPushButton(entrFrame);
        pushButton_backspace->setObjectName(QString::fromUtf8("pushButton_backspace"));
        pushButton_backspace->setGeometry(QRect(257, 340, 120, 85));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_backspace->setFont(font1);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/Keyboard/delup.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon11.addFile(QString::fromUtf8(":/images/Keyboard/deldn.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_backspace->setIcon(icon11);
        pushButton_backspace->setIconSize(QSize(120, 85));
        pushButton_Cancel = new QPushButton(entrFrame);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(1, 434, 195, 80));
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(118, 116, 108, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        pushButton_Cancel->setPalette(palette);
        pushButton_Cancel->setAutoFillBackground(false);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/images/Keyboard/entrCal.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Cancel->setIcon(icon12);
        pushButton_Cancel->setIconSize(QSize(195, 80));
        pushButton_ok = new QPushButton(entrFrame);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(194, 434, 195, 80));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        pushButton_ok->setPalette(palette1);
        pushButton_ok->setAutoFillBackground(false);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/Keyboard/entrOk.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_ok->setIcon(icon13);
        pushButton_ok->setIconSize(QSize(195, 80));
        pushButton_ok->setAutoDefault(true);
        lineEdit_window = new QLineEdit(entrFrame);
        lineEdit_window->setObjectName(QString::fromUtf8("lineEdit_window"));
        lineEdit_window->setGeometry(QRect(10, 10, 370, 70));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_window->sizePolicy().hasHeightForWidth());
        lineEdit_window->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("simhei"));
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        lineEdit_window->setFont(font2);
        lineEdit_window->setStyleSheet(QString::fromUtf8("#lineEdit_window\n"
"{\n"
"background: transparent;\n"
"color: rgb(128, 192, 255);\n"
"font-family:simhei;\n"
"font:bold;\n"
"font:36px;\n"
"\n"
"}"));
        lineEdit_window->setFrame(false);
        lineEdit_window->setCursorPosition(0);

        retranslateUi(NumbKeyboardDialog);

        QMetaObject::connectSlotsByName(NumbKeyboardDialog);
    } // setupUi

    void retranslateUi(QDialog *NumbKeyboardDialog)
    {
        NumbKeyboardDialog->setWindowTitle(QApplication::translate("NumbKeyboardDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton_n4->setText(QString());
        pushButton_n5->setText(QString());
        pushButton_n6->setText(QString());
        pushButton_n1->setText(QString());
        pushButton_n2->setText(QString());
        pushButton_n3->setText(QString());
        pushButton_n7->setText(QString());
        pushButton_n8->setText(QString());
        pushButton_n9->setText(QString());
        pushButton_n0->setText(QString());
        pushButton_period->setText(QString());
        pushButton_backspace->setText(QString());
        pushButton_Cancel->setText(QString());
        pushButton_ok->setText(QString());
        lineEdit_window->setInputMask(QString());
        lineEdit_window->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NumbKeyboardDialog: public Ui_NumbKeyboardDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMBKEYBOARDDIALOG_H
