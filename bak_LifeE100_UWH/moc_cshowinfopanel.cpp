/****************************************************************************
** Meta object code from reading C++ file 'cshowinfopanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cshowinfopanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cshowinfopanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CShowInfoPanel_t {
    QByteArrayData data[6];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CShowInfoPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CShowInfoPanel_t qt_meta_stringdata_CShowInfoPanel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CShowInfoPanel"
QT_MOC_LITERAL(1, 15, 10), // "ShowString"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "OnClearInfo"
QT_MOC_LITERAL(4, 39, 6), // "OnExit"
QT_MOC_LITERAL(5, 46, 10) // "OnStopRecv"

    },
    "CShowInfoPanel\0ShowString\0\0OnClearInfo\0"
    "OnExit\0OnStopRecv"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CShowInfoPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CShowInfoPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CShowInfoPanel *_t = static_cast<CShowInfoPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ShowString(); break;
        case 1: _t->OnClearInfo(); break;
        case 2: _t->OnExit(); break;
        case 3: _t->OnStopRecv(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CShowInfoPanel::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CShowInfoPanel.data,
      qt_meta_data_CShowInfoPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CShowInfoPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CShowInfoPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CShowInfoPanel.stringdata0))
        return static_cast<void*>(const_cast< CShowInfoPanel*>(this));
    return QFrame::qt_metacast(_clname);
}

int CShowInfoPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
