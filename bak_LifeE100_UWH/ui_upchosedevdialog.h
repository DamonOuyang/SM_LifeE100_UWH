/********************************************************************************
** Form generated from reading UI file 'upchosedevdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPCHOSEDEVDIALOG_H
#define UI_UPCHOSEDEVDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UpChoseDevDialog
{
public:
    QFrame *devChoseframe;
    QGroupBox *groupBox;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton3;
    QPushButton *pushButton4;
    QPushButton *upCancel;
    QPushButton *upOk;

    void setupUi(QDialog *UpChoseDevDialog)
    {
        if (UpChoseDevDialog->objectName().isEmpty())
            UpChoseDevDialog->setObjectName(QString::fromUtf8("UpChoseDevDialog"));
        UpChoseDevDialog->resize(1280, 760);
        UpChoseDevDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/images/Update/updateChoseDev_Bg.png);"));
        devChoseframe = new QFrame(UpChoseDevDialog);
        devChoseframe->setObjectName(QString::fromUtf8("devChoseframe"));
        devChoseframe->setGeometry(QRect(445, 100, 390, 560));
        devChoseframe->setStyleSheet(QString::fromUtf8("#devChoseframe\n"
"{\n"
"background-image: url(:/images/Update/ChoseFrom_Bg.png);\n"
"}"));
        devChoseframe->setFrameShape(QFrame::NoFrame);
        devChoseframe->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(devChoseframe);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 120, 350, 320));
        groupBox->setAlignment(Qt::AlignCenter);
        pushButton1 = new QPushButton(groupBox);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        pushButton1->setGeometry(QRect(0, 0, 350, 80));
        pushButton1->setStyleSheet(QString::fromUtf8("#pushButton1\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#pushButton1:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Update/dev01.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/images/Update/dev02.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton1->setIcon(icon);
        pushButton1->setIconSize(QSize(350, 80));
        pushButton1->setCheckable(true);
        pushButton1->setChecked(true);
        pushButton1->setAutoExclusive(true);
        pushButton2 = new QPushButton(groupBox);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setGeometry(QRect(0, 80, 350, 80));
        pushButton2->setStyleSheet(QString::fromUtf8("#pushButton2\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#pushButton2:focus{outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Update/dev11.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/images/Update/dev12.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton2->setIcon(icon1);
        pushButton2->setIconSize(QSize(350, 80));
        pushButton2->setCheckable(true);
        pushButton2->setAutoExclusive(true);
        pushButton3 = new QPushButton(groupBox);
        pushButton3->setObjectName(QString::fromUtf8("pushButton3"));
        pushButton3->setGeometry(QRect(0, 240, 350, 80));
        pushButton3->setStyleSheet(QString::fromUtf8("#pushButton3\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#pushButton3:focus{outline: none;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Update/dev21.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/images/Update/dev22.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton3->setIcon(icon2);
        pushButton3->setIconSize(QSize(350, 80));
        pushButton3->setCheckable(true);
        pushButton3->setAutoExclusive(true);
        pushButton4 = new QPushButton(groupBox);
        pushButton4->setObjectName(QString::fromUtf8("pushButton4"));
        pushButton4->setGeometry(QRect(0, 160, 350, 80));
        pushButton4->setStyleSheet(QString::fromUtf8("#pushButton4\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#pushButton4:focus{outline: none;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/Update/dev31.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/images/Update/dev32.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton4->setIcon(icon3);
        pushButton4->setIconSize(QSize(350, 80));
        pushButton4->setCheckable(true);
        pushButton4->setAutoExclusive(true);
        upCancel = new QPushButton(devChoseframe);
        upCancel->setObjectName(QString::fromUtf8("upCancel"));
        upCancel->setGeometry(QRect(0, 480, 195, 80));
        upCancel->setStyleSheet(QString::fromUtf8("#upCancel\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#upCancel:focus{outline: none;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/Update/upCancel_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        upCancel->setIcon(icon4);
        upCancel->setIconSize(QSize(195, 80));
        upOk = new QPushButton(devChoseframe);
        upOk->setObjectName(QString::fromUtf8("upOk"));
        upOk->setGeometry(QRect(195, 480, 195, 80));
        upOk->setStyleSheet(QString::fromUtf8("#upOk\n"
"{\n"
"background: transparent;\n"
"border-width:-1px;\n"
"padding:-1px;\n"
"}\n"
"\n"
"#upOk:focus{outline: none;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/Update/upOK_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        upOk->setIcon(icon5);
        upOk->setIconSize(QSize(195, 80));

        retranslateUi(UpChoseDevDialog);

        QMetaObject::connectSlotsByName(UpChoseDevDialog);
    } // setupUi

    void retranslateUi(QDialog *UpChoseDevDialog)
    {
        UpChoseDevDialog->setWindowTitle(QApplication::translate("UpChoseDevDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        pushButton1->setText(QString());
        pushButton2->setText(QString());
        pushButton3->setText(QString());
        pushButton4->setText(QString());
        upCancel->setText(QString());
        upOk->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UpChoseDevDialog: public Ui_UpChoseDevDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPCHOSEDEVDIALOG_H
