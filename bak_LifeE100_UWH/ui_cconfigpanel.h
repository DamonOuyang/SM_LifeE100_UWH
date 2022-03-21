/********************************************************************************
** Form generated from reading UI file 'cconfigpanel.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCONFIGPANEL_H
#define UI_CCONFIGPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CConfigPanel
{
public:
    QTabWidget *cfgTabWidget;
    QWidget *basicCfgTab;
    QWidget *almCfgTab;
    QWidget *PourCfgTab;
    QWidget *watModTab;
    QWidget *artModTab;
    QWidget *veiModTab;
    QWidget *batModTab;
    QWidget *testTab;

    void setupUi(QFrame *CConfigPanel)
    {
        if (CConfigPanel->objectName().isEmpty())
            CConfigPanel->setObjectName(QString::fromUtf8("CConfigPanel"));
        CConfigPanel->resize(1200, 680);
        cfgTabWidget = new QTabWidget(CConfigPanel);
        cfgTabWidget->setObjectName(QString::fromUtf8("cfgTabWidget"));
        cfgTabWidget->setGeometry(QRect(0, 0, 1200, 655));
        cfgTabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        cfgTabWidget->setAutoFillBackground(false);
        cfgTabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane\n"
"{\n"
"top:0px;\n"
"}"));
        cfgTabWidget->setTabPosition(QTabWidget::West);
        cfgTabWidget->setTabShape(QTabWidget::Rounded);
        cfgTabWidget->setIconSize(QSize(125, 65));
        cfgTabWidget->setElideMode(Qt::ElideNone);
        cfgTabWidget->setUsesScrollButtons(false);
        cfgTabWidget->setDocumentMode(false);
        cfgTabWidget->setTabsClosable(false);
        basicCfgTab = new QWidget();
        basicCfgTab->setObjectName(QString::fromUtf8("basicCfgTab"));
        basicCfgTab->setStyleSheet(QString::fromUtf8("#basicCfgTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(basicCfgTab, QString());
        almCfgTab = new QWidget();
        almCfgTab->setObjectName(QString::fromUtf8("almCfgTab"));
        almCfgTab->setStyleSheet(QString::fromUtf8("#almCfgTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(almCfgTab, QString());
        PourCfgTab = new QWidget();
        PourCfgTab->setObjectName(QString::fromUtf8("PourCfgTab"));
        PourCfgTab->setStyleSheet(QString::fromUtf8("#PourCfgTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(PourCfgTab, QString());
        watModTab = new QWidget();
        watModTab->setObjectName(QString::fromUtf8("watModTab"));
        watModTab->setStyleSheet(QString::fromUtf8("#watModTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(watModTab, QString());
        artModTab = new QWidget();
        artModTab->setObjectName(QString::fromUtf8("artModTab"));
        artModTab->setStyleSheet(QString::fromUtf8("#artModTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(artModTab, QString());
        veiModTab = new QWidget();
        veiModTab->setObjectName(QString::fromUtf8("veiModTab"));
        veiModTab->setStyleSheet(QString::fromUtf8("#veiModTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(veiModTab, QString());
        batModTab = new QWidget();
        batModTab->setObjectName(QString::fromUtf8("batModTab"));
        batModTab->setStyleSheet(QString::fromUtf8("#batModTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(batModTab, QString());
        testTab = new QWidget();
        testTab->setObjectName(QString::fromUtf8("testTab"));
        testTab->setStyleSheet(QString::fromUtf8("#testTab\n"
"{\n"
"background-color: rgb(38, 38, 44);\n"
"}"));
        cfgTabWidget->addTab(testTab, QString());

        retranslateUi(CConfigPanel);

        cfgTabWidget->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(CConfigPanel);
    } // setupUi

    void retranslateUi(QFrame *CConfigPanel)
    {
        CConfigPanel->setWindowTitle(QApplication::translate("CConfigPanel", "Frame", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(basicCfgTab), QApplication::translate("CConfigPanel", "\345\237\272\346\234\254\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(almCfgTab), QApplication::translate("CConfigPanel", "\345\221\212\350\255\246\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(PourCfgTab), QApplication::translate("CConfigPanel", "\347\201\214\346\263\250\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(watModTab), QApplication::translate("CConfigPanel", "\346\260\264\346\265\264\346\250\241\345\235\227", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(artModTab), QApplication::translate("CConfigPanel", "\350\241\200\346\263\265\345\212\250\350\204\211", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(veiModTab), QApplication::translate("CConfigPanel", "\350\241\200\346\263\265\351\227\250\350\204\211", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(batModTab), QApplication::translate("CConfigPanel", "\347\224\265\346\261\240\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        cfgTabWidget->setTabText(cfgTabWidget->indexOf(testTab), QApplication::translate("CConfigPanel", "\350\260\203\350\257\225\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CConfigPanel: public Ui_CConfigPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCONFIGPANEL_H
