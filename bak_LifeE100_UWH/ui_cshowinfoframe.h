/********************************************************************************
** Form generated from reading UI file 'cshowinfoframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSHOWINFOFRAME_H
#define UI_CSHOWINFOFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CShowInfoFrame
{
public:
    QTextEdit *pShwInfo;
    QPushButton *pStopBut;
    QPushButton *pClearBut;

    void setupUi(QFrame *CShowInfoFrame)
    {
        if (CShowInfoFrame->objectName().isEmpty())
            CShowInfoFrame->setObjectName(QString::fromUtf8("CShowInfoFrame"));
        CShowInfoFrame->resize(1075, 655);
        pShwInfo = new QTextEdit(CShowInfoFrame);
        pShwInfo->setObjectName(QString::fromUtf8("pShwInfo"));
        pShwInfo->setGeometry(QRect(1, 1, 1074, 519));
        pShwInfo->setReadOnly(true);
        pStopBut = new QPushButton(CShowInfoFrame);
        pStopBut->setObjectName(QString::fromUtf8("pStopBut"));
        pStopBut->setGeometry(QRect(915, 555, 160, 60));
        pStopBut->setStyleSheet(QString::fromUtf8("\n"
"#pStopBut:focus{outline: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/stopBut_Bt.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/images/stopButDn_Bt.png"), QSize(), QIcon::Normal, QIcon::On);
        pStopBut->setIcon(icon);
        pStopBut->setIconSize(QSize(160, 60));
        pStopBut->setCheckable(true);
        pStopBut->setChecked(false);
        pStopBut->setFlat(true);
        pClearBut = new QPushButton(CShowInfoFrame);
        pClearBut->setObjectName(QString::fromUtf8("pClearBut"));
        pClearBut->setGeometry(QRect(737, 555, 160, 60));
        pClearBut->setStyleSheet(QString::fromUtf8("#pClearBut\n"
"{\n"
"background-image: url(:/images/clearBut_Bt.png);\n"
"}\n"
"#pClearBut:pressed\n"
"{\n"
"background-image: url(:/images/clearButDn_Bt.png);\n"
"}\n"
"#pClearBut:focus{outline: none;\n"
"}"));
        pClearBut->setIconSize(QSize(160, 60));

        retranslateUi(CShowInfoFrame);

        QMetaObject::connectSlotsByName(CShowInfoFrame);
    } // setupUi

    void retranslateUi(QFrame *CShowInfoFrame)
    {
        CShowInfoFrame->setWindowTitle(QApplication::translate("CShowInfoFrame", "Frame", 0, QApplication::UnicodeUTF8));
        pStopBut->setText(QString());
        pClearBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CShowInfoFrame: public Ui_CShowInfoFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSHOWINFOFRAME_H
