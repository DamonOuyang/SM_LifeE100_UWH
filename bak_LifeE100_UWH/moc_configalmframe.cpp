/****************************************************************************
** Meta object code from reading C++ file 'configalmframe.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "configalmframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configalmframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_configAlmFrame[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      28,   15,   15,   15, 0x0a,
      50,   44,   15,   15, 0x0a,
      81,   73,   15,   15, 0x0a,
     115,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_configAlmFrame[] = {
    "configAlmFrame\0\0OnClickOK()\0OnClickCancel()\0"
    "strIn\0confirmString(QString)\0old,now\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "OnItemEdit()\0"
};

void configAlmFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        configAlmFrame *_t = static_cast<configAlmFrame *>(_o);
        switch (_id) {
        case 0: _t->OnClickOK(); break;
        case 1: _t->OnClickCancel(); break;
        case 2: _t->confirmString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 4: _t->OnItemEdit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData configAlmFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject configAlmFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_configAlmFrame,
      qt_meta_data_configAlmFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &configAlmFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *configAlmFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *configAlmFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_configAlmFrame))
        return static_cast<void*>(const_cast< configAlmFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int configAlmFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
