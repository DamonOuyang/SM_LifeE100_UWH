/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      27,   11,   11,   11, 0x08,
      45,   11,   11,   11, 0x08,
      66,   60,   11,   11, 0x08,
      88,   11,   11,   11, 0x08,
     107,   99,   11,   11, 0x08,
     133,   99,   11,   11, 0x08,
     164,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     202,   11,   11,   11, 0x08,
     220,   11,   11,   11, 0x08,
     243,   11,   11,   11, 0x08,
     267,   99,   11,   11, 0x08,
     296,   11,   11,   11, 0x08,
     325,   11,   11,   11, 0x08,
     335,   99,   11,   11, 0x08,
     362,   11,   11,   11, 0x08,
     381,   11,   11,   11, 0x08,
     401,   11,   11,   11, 0x08,
     427,  420,   11,   11, 0x08,
     455,  449,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0RevCloseHead()\0OnMonTabChanged()\0"
    "setValCanlce()\0strIn\0setValString(QString)\0"
    "SecTimer()\0checked\0on_BPStrBtn_clicked(bool)\0"
    "on_wtrRomOnOffBt_clicked(bool)\0"
    "WtrTmpSetBtClick()\0PourPressLEClick()\0"
    "PreSpeedLEClick()\0on_sysSetBtn_clicked()\0"
    "on_almShowBtn_clicked()\0"
    "on_almOnOffBtn_clicked(bool)\0"
    "on_unLockScreenBtn_clicked()\0setLock()\0"
    "on_BPStrBtnV_clicked(bool)\0"
    "OnMonTabChangedV()\0PourPressLEClickV()\0"
    "PreSpeedLEClickV()\0bState\0"
    "closePumWinBack(bool)\0index\0"
    "on_monTabWidget_currentChanged(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->RevCloseHead(); break;
        case 1: _t->OnMonTabChanged(); break;
        case 2: _t->setValCanlce(); break;
        case 3: _t->setValString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SecTimer(); break;
        case 5: _t->on_BPStrBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_wtrRomOnOffBt_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->WtrTmpSetBtClick(); break;
        case 8: _t->PourPressLEClick(); break;
        case 9: _t->PreSpeedLEClick(); break;
        case 10: _t->on_sysSetBtn_clicked(); break;
        case 11: _t->on_almShowBtn_clicked(); break;
        case 12: _t->on_almOnOffBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_unLockScreenBtn_clicked(); break;
        case 14: _t->setLock(); break;
        case 15: _t->on_BPStrBtnV_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->OnMonTabChangedV(); break;
        case 17: _t->PourPressLEClickV(); break;
        case 18: _t->PreSpeedLEClickV(); break;
        case 19: _t->closePumWinBack((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_monTabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
