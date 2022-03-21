/********************************************************************************
** Form generated from reading UI file 'DataFrame.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAFRAME_H
#define UI_DATAFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataFrame
{
public:
    QTabWidget *dataTabWidget;
    QWidget *tabFiles;
    QWidget *fileWidget;
    QPushButton *pOpenBut;
    QPushButton *pExPortBut;
    QPushButton *pRfshBut;
    QPushButton *pDelBut;
    QPushButton *pDelAllBut;
    QWidget *tabPress;
    QWidget *tabSpeed;
    QWidget *tabFlow;
    QWidget *tabPumTmp;
    QWidget *tabWatTmp;
    QWidget *tabDetail;

    void setupUi(QFrame *DataFrame)
    {
        if (DataFrame->objectName().isEmpty())
            DataFrame->setObjectName(QString::fromUtf8("DataFrame"));
        DataFrame->resize(1280, 680);
        DataFrame->setStyleSheet(QString::fromUtf8(""));
        DataFrame->setFrameShape(QFrame::NoFrame);
        DataFrame->setFrameShadow(QFrame::Raised);
        DataFrame->setLineWidth(0);
        dataTabWidget = new QTabWidget(DataFrame);
        dataTabWidget->setObjectName(QString::fromUtf8("dataTabWidget"));
        dataTabWidget->setGeometry(QRect(0, 0, 1200, 655));
        dataTabWidget->setAutoFillBackground(false);
        dataTabWidget->setStyleSheet(QString::fromUtf8(""));
        dataTabWidget->setTabPosition(QTabWidget::West);
        dataTabWidget->setUsesScrollButtons(false);
        tabFiles = new QWidget();
        tabFiles->setObjectName(QString::fromUtf8("tabFiles"));
        tabFiles->setStyleSheet(QString::fromUtf8("#tabFiles\n"
"{\n"
"	\n"
"}"));
        fileWidget = new QWidget(tabFiles);
        fileWidget->setObjectName(QString::fromUtf8("fileWidget"));
        fileWidget->setGeometry(QRect(0, 0, 1075, 520));
        fileWidget->setStyleSheet(QString::fromUtf8("#fileWidget\n"
"{\n"
"background-color: rgb(64, 64, 71);\n"
"}"));
        pOpenBut = new QPushButton(tabFiles);
        pOpenBut->setObjectName(QString::fromUtf8("pOpenBut"));
        pOpenBut->setGeometry(QRect(195, 555, 160, 60));
        pOpenBut->setStyleSheet(QString::fromUtf8("#pOpenBut\n"
"{\n"
"background-image: url(:/images/dOpenBut_Icon.png);\n"
"}\n"
"#pOpenBut:pressed\n"
"{\n"
"background-image: url(:/images/dOpenButDn_Icon.png);\n"
"}\n"
"#pOpenBut:focus{outline: none;\n"
"}"));
        pOpenBut->setIconSize(QSize(160, 60));
        pExPortBut = new QPushButton(tabFiles);
        pExPortBut->setObjectName(QString::fromUtf8("pExPortBut"));
        pExPortBut->setGeometry(QRect(375, 555, 160, 60));
        pExPortBut->setStyleSheet(QString::fromUtf8("#pExPortBut\n"
"{\n"
"background-image: url(:/images/dExPortBut_Icon.png);\n"
"}\n"
"#pExPortBut:pressed\n"
"{\n"
"background-image: url(:/images/dExPortButDn_Icon.png);\n"
"}\n"
"#pExPortBut:focus{outline: none;\n"
"}"));
        pExPortBut->setIconSize(QSize(160, 60));
        pRfshBut = new QPushButton(tabFiles);
        pRfshBut->setObjectName(QString::fromUtf8("pRfshBut"));
        pRfshBut->setGeometry(QRect(555, 555, 160, 60));
        pRfshBut->setStyleSheet(QString::fromUtf8("#pRfshBut\n"
"{\n"
"background-image: url(:/images/dRfshBut_Icon.png);\n"
"}\n"
"#pRfshBut:pressed\n"
"{\n"
"background-image: url(:/images/dRfshButDn_Icon.png);\n"
"}\n"
"#pRfshBut:focus{outline: none;\n"
"}"));
        pRfshBut->setIconSize(QSize(160, 60));
        pDelBut = new QPushButton(tabFiles);
        pDelBut->setObjectName(QString::fromUtf8("pDelBut"));
        pDelBut->setGeometry(QRect(737, 555, 160, 60));
        pDelBut->setStyleSheet(QString::fromUtf8("#pDelBut\n"
"{\n"
"background-image: url(:/images/dDelBut_Icon.png);\n"
"}\n"
"#pDelBut:pressed\n"
"{\n"
"background-image: url(:/images/dDelButDn_Icon.png);\n"
"}\n"
"#pDelBut:focus{outline: none;\n"
"}"));
        pDelBut->setIconSize(QSize(160, 60));
        pDelAllBut = new QPushButton(tabFiles);
        pDelAllBut->setObjectName(QString::fromUtf8("pDelAllBut"));
        pDelAllBut->setGeometry(QRect(915, 555, 160, 60));
        pDelAllBut->setStyleSheet(QString::fromUtf8("#pDelAllBut\n"
"{\n"
"background-image: url(:/images/dDelAllBut_Icon.png);\n"
"}\n"
"#pDelAllBut:pressed\n"
"{\n"
"background-image: url(:/images/dDelAllButDn_Icon.png);\n"
"}\n"
"#pDelAllBut:focus{outline: none;\n"
"}"));
        pDelAllBut->setIconSize(QSize(160, 60));
        dataTabWidget->addTab(tabFiles, QString());
        tabPress = new QWidget();
        tabPress->setObjectName(QString::fromUtf8("tabPress"));
        dataTabWidget->addTab(tabPress, QString());
        tabSpeed = new QWidget();
        tabSpeed->setObjectName(QString::fromUtf8("tabSpeed"));
        dataTabWidget->addTab(tabSpeed, QString());
        tabFlow = new QWidget();
        tabFlow->setObjectName(QString::fromUtf8("tabFlow"));
        dataTabWidget->addTab(tabFlow, QString());
        tabPumTmp = new QWidget();
        tabPumTmp->setObjectName(QString::fromUtf8("tabPumTmp"));
        dataTabWidget->addTab(tabPumTmp, QString());
        tabWatTmp = new QWidget();
        tabWatTmp->setObjectName(QString::fromUtf8("tabWatTmp"));
        dataTabWidget->addTab(tabWatTmp, QString());
        tabDetail = new QWidget();
        tabDetail->setObjectName(QString::fromUtf8("tabDetail"));
        tabDetail->setStyleSheet(QString::fromUtf8("#tabDetail\n"
"{\n"
"background-color: rgb(64, 64, 71);\n"
"}"));
        dataTabWidget->addTab(tabDetail, QString());

        retranslateUi(DataFrame);

        dataTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DataFrame);
    } // setupUi

    void retranslateUi(QFrame *DataFrame)
    {
        DataFrame->setWindowTitle(QApplication::translate("DataFrame", "Frame", 0, QApplication::UnicodeUTF8));
        pOpenBut->setText(QString());
        pExPortBut->setText(QString());
        pRfshBut->setText(QString());
        pDelBut->setText(QString());
        pDelAllBut->setText(QString());
        dataTabWidget->setTabText(dataTabWidget->indexOf(tabFiles), QApplication::translate("DataFrame", "\347\201\214\346\263\250\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tabPress), QApplication::translate("DataFrame", "\345\216\213\345\212\233\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tabSpeed), QApplication::translate("DataFrame", "\350\275\254\351\200\237\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tabFlow), QApplication::translate("DataFrame", "\346\265\201\351\207\217\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tabPumTmp), QApplication::translate("DataFrame", "\346\270\251\345\272\246\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tabWatTmp), QApplication::translate("DataFrame", "\346\260\264\346\265\264\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tabDetail), QApplication::translate("DataFrame", "\350\257\246\347\273\206\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DataFrame: public Ui_DataFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAFRAME_H
