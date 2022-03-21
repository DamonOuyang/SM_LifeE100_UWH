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
    cswitchmodule.cpp \
    CSwitPump.cpp \
    CSwitWater.cpp \
    cbasicpourproc.cpp \
    cpourdevices.cpp \
    monLogframedlg.cpp \
    dataframedlg.cpp \
    qcustomplot.cpp \
    cpassworddlg.cpp \
    monThread.cpp \
    lockscreendialog.cpp \
    calprmdialog.cpp \
    freezetablewidget.cpp \
    QRoundProgressBar.cpp \
    BatteryLogManage.cpp \
    normalwindowdialog.cpp \
    unlockinfodialog.cpp \
    closepumwindialog.cpp \
    almshowdialog.cpp \
    CBQ40z50Battery.cpp \
    cuartsocketBQ40z50.cpp \
    systemsetdialog.cpp \
    cconfigpanel.cpp \
    configbasicframe.cpp \
    numbkeyboarddialog.cpp \
    configalmframe.cpp \
    configpourframe.cpp \
    configwatframe.cpp \
    configartframe.cpp \
    configveiframe.cpp \
    upchosedevdialog.cpp \
    updategoingdialog.cpp \
    loadheaddialog.cpp \
    configbatframe.cpp \
    passworddialog.cpp \
    cshowinfoframe.cpp \
    messageboxdialog.cpp

HEADERS += \
        mainwindow.h \
    includes.h \
    setvaldialog.h \
    myLineEdit.h \
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
    cswitchmodule.h \
    CSwitPump.h \
    CSwitWater.h \
    cbasicpourproc.h \
    cpourdevices.h \
    monLogframedlg.h \
    dataframedlg.h \
    qcustomplot.h \
    cpassworddlg.h \
    monThread.h \
    lockscreendialog.h \
    calprmdialog.h \
    freezetablewidget.h \
    QRoundProgressBar.h \
    BatteryLogManage.h \
    normalwindowdialog.h \
    unlockinfodialog.h \
    closepumwindialog.h \
    almshowdialog.h \
    CBQ40z50Battery.h \
    cuartsocketBQ40z50.h \
    systemsetdialog.h \
    myqproxystyle.h \
    cconfigpanel.h \
    configbasicframe.h \
    numbkeyboarddialog.h \
    configalmframe.h \
    configpourframe.h \
    configwatframe.h \
    configartframe.h \
    configveiframe.h \
    upchosedevdialog.h \
    updategoingdialog.h \
    loadheaddialog.h \
    configbatframe.h \
    passworddialog.h \
    cshowinfoframe.h \
    messageboxdialog.h

FORMS += \
        mainwindow.ui \
    setvaldialog.ui \
    LogFrame.ui \
    DataFrame.ui \
    lockscreendialog.ui \
    calprmdialog.ui \
    calprmdialog.ui \
    normalwindowdialog.ui \
    unlockinfodialog.ui \
    closepumwindialog.ui \
    almshowdialog.ui \
    systemsetdialog.ui \
    cconfigpanel.ui \
    configbasicframe.ui \
    numbkeyboarddialog.ui \
    configalmframe.ui \
    configpourframe.ui \
    configwatframe.ui \
    configartframe.ui \
    configveiframe.ui \
    upchosedevdialog.ui \
    updategoingdialog.ui \
    loadheaddialog.ui \
    configbatframe.ui \
    passworddialog.ui \
    cshowinfoframe.ui \
    messageboxdialog.ui
unix:DESTDIR += /home/damon/tmp_new_app/

RESOURCES += \
    image.qrc
