#-------------------------------------------------
#
# Project created by QtCreator 2020-11-23T19:19:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Life100_UWH
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    commonfuncs.cpp \
    setvaldialog.cpp \
    myLineEdit.cpp \
    syszuxpinyin.cpp \
    errorstringqueue.cpp \
    cworkthread.cpp \
    cuartsocket.cpp \
    csockethandler.cpp \
    csocket.cpp \
    csharedataqueue.cpp \
    cmonsharedata.cpp \
    cerrInfo.cpp \
    cdevcmdhandler.cpp \
    ccmddataqueue.cpp \
    ccircularfile.cpp \
    cbasicdevice.cpp \
    calarmDataFile.cpp \
    DevBasicConfigDlg.cpp \
    systemsetdialog.cpp \
    cswitchmodule.cpp \
    CSwitPump.cpp \
    CSwitWater.cpp \
    cbasicpourproc.cpp \
    cpourdevices.cpp \
    cconfigpanel.cpp \
    basicconfigpanel.cpp \
    almconfigpanel.cpp \
    watconfigpanel.cpp \
    pumpAconfigpanel.cpp \
    cshowinfopanel.cpp \
    monLogframedlg.cpp \
    pourconfigpanel.cpp \
    dataframedlg.cpp \
    qcustomplot.cpp \
    cpassworddlg.cpp \
    monThread.cpp \
    lockscreendialog.cpp \
    updatedialog.cpp \
    pumpVconfigpanel.cpp \
    pulconfigpanel.cpp \
    calprmdialog.cpp \
    freezetablewidget.cpp \
    CJbdCellCheck.cpp \
    cuartsocketJBD.cpp \
    QRoundProgressBar.cpp \
    BatteryLogManage.cpp \
    normalwindowdialog.cpp \
    unlockinfodialog.cpp \
    closepumwindialog.cpp \
    almshowdialog.cpp \
    CBQ40z50Battery.cpp \
    cuartsocketBQ40z50.cpp \
    systemsetdialog.cpp

HEADERS += \
        mainwindow.h \
    includes.h \
    setvaldialog.h \
    myLineEdit.h \
    syszuxpinyin.h \
    errorstringqueue.h \
    cworkthread.h \
    cuartsocket.h \
    csockethandler.h \
    csocket.h \
    csharedataqueue.h \
    cmonsharedata.h \
    cerrInfo.h \
    cdevcmdhandler.h \
    ccmddataqueue.h \
    ccircularfile.h \
    cbasicdevice.h \
    calarmDataFile.h \
    DevBasicConfigDlg.h \
    systemsetdialog.h \
    cswitchmodule.h \
    CSwitPump.h \
    CSwitWater.h \
    cbasicpourproc.h \
    cpourdevices.h \
    cconfigpanel.h \
    basicconfigpanel.h \
    almconfigpanel.h \
    watconfigpanel.h \
    pumpAconfigpanel.h \
    cshowinfopanel.h \
    monLogframedlg.h \
    pourconfigpanel.h \
    dataframedlg.h \
    qcustomplot.h \
    cpassworddlg.h \
    monThread.h \
    lockscreendialog.h \
    updatedialog.h \
    pumpVconfigpanel.h \
    pulconfigpanel.h \
    calprmdialog.h \
    freezetablewidget.h \
    CJbdCellCheck.h \
    cuartsocketJBD.h \
    QRoundProgressBar.h \
    BatteryLogManage.h \
    normalwindowdialog.h \
    unlockinfodialog.h \
    closepumwindialog.h \
    almshowdialog.h \
    CBQ40z50Battery.h \
    cuartsocketBQ40z50.h \
    systemsetdialog.h \
    myqproxystyle.h

FORMS += \
        mainwindow.ui \
    setvaldialog.ui \
    syszuxpinyin.ui \
    systemsetdialog.ui \
    LogFrame.ui \
    DataFrame.ui \
    lockscreendialog.ui \
    updatedialog.ui \
    calprmdialog.ui \
    calprmdialog.ui \
    normalwindowdialog.ui \
    unlockinfodialog.ui \
    closepumwindialog.ui \
    almshowdialog.ui \
    systemsetdialog.ui
unix:DESTDIR += /home/HH_Work/qt_project/newApp/LifeE100_UWH/

RESOURCES += \
    image.qrc
