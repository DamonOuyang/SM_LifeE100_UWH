/********************************************************************************
** Form generated from reading UI file 'calprmdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALPRMDIALOG_H
#define UI_CALPRMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_calPrmDialog
{
public:
    QPushButton *setButton;
    QPushButton *readButton;
    QComboBox *m_pCalItemPat;
    QComboBox *m_pModIndex;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *closeButton;
    QLabel *label_5;
    QLabel *label;
    QComboBox *m_pCalIndexPat;
    QLabel *label_4;

    void setupUi(QDialog *calPrmDialog)
    {
        if (calPrmDialog->objectName().isEmpty())
            calPrmDialog->setObjectName(QString::fromUtf8("calPrmDialog"));
        calPrmDialog->resize(1280, 740);
        setButton = new QPushButton(calPrmDialog);
        setButton->setObjectName(QString::fromUtf8("setButton"));
        setButton->setGeometry(QRect(450, 410, 120, 60));
        setButton->setStyleSheet(QString::fromUtf8("   font-family:simhei;\n"
"   color: rgb(86,93,113);\n"
"   font:bold;\n"
"   font:30px;"));
        readButton = new QPushButton(calPrmDialog);
        readButton->setObjectName(QString::fromUtf8("readButton"));
        readButton->setGeometry(QRect(720, 410, 120, 60));
        readButton->setStyleSheet(QString::fromUtf8("   font-family:simhei;\n"
"   color: rgb(86,93,113);\n"
"   font:bold;\n"
"   font:30px;"));
        m_pCalItemPat = new QComboBox(calPrmDialog);
        m_pCalItemPat->setObjectName(QString::fromUtf8("m_pCalItemPat"));
        m_pCalItemPat->setGeometry(QRect(450, 204, 130, 40));
        m_pModIndex = new QComboBox(calPrmDialog);
        m_pModIndex->setObjectName(QString::fromUtf8("m_pModIndex"));
        m_pModIndex->setGeometry(QRect(200, 204, 130, 40));
        label_2 = new QLabel(calPrmDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(710, 150, 130, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(16);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(calPrmDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(950, 150, 130, 50));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        closeButton = new QPushButton(calPrmDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(1110, 630, 120, 60));
        closeButton->setStyleSheet(QString::fromUtf8("   font-family:simhei;\n"
"   color: rgb(86,93,113);\n"
"   font:bold;\n"
"   font:30px;"));
        label_5 = new QLabel(calPrmDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 150, 130, 50));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        label = new QLabel(calPrmDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(450, 150, 130, 50));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        m_pCalIndexPat = new QComboBox(calPrmDialog);
        m_pCalIndexPat->setObjectName(QString::fromUtf8("m_pCalIndexPat"));
        m_pCalIndexPat->setGeometry(QRect(710, 204, 130, 40));
        label_4 = new QLabel(calPrmDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(580, 20, 121, 61));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        retranslateUi(calPrmDialog);

        QMetaObject::connectSlotsByName(calPrmDialog);
    } // setupUi

    void retranslateUi(QDialog *calPrmDialog)
    {
        calPrmDialog->setWindowTitle(QApplication::translate("calPrmDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        setButton->setText(QApplication::translate("calPrmDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        readButton->setText(QApplication::translate("calPrmDialog", "\350\257\273\345\217\226", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("calPrmDialog", "\346\240\241\346\255\243\345\200\274:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("calPrmDialog", "\345\217\202\350\200\203\345\200\274:", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("calPrmDialog", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("calPrmDialog", "\346\250\241\345\235\227\351\200\211\351\241\271:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("calPrmDialog", "\346\240\241\346\255\243\351\200\211\351\241\271:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("calPrmDialog", "\345\217\202\346\225\260\346\240\241\345\207\206", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class calPrmDialog: public Ui_calPrmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALPRMDIALOG_H
