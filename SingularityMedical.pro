#-------------------------------------------------
#
# Project created by QtCreator 2022-01-16T00:12:13
#
#-------------------------------------------------
PRO_ROOT = $$PWD
QT      += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtAppArchitecture
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

CONFIG += c++11
#model
include($$PRO_ROOT/bridge/bridge.pri)
include($$PRO_ROOT/common/common.pri)
include($$PRO_ROOT/communication/communication.pri)
include($$PRO_ROOT/logical/logical.pri)
include($$PRO_ROOT/ui/ui.pri)
include($$PRO_ROOT/main/main.pri)
include($$PRO_ROOT/logger/logger.pri)
include($$PRO_ROOT/protocal/protocal.pri)

