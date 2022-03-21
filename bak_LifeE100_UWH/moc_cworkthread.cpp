/****************************************************************************
** Meta object code from reading C++ file 'cworkthread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cworkthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cworkthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CWorkThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      24,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CWorkThread[] = {
    "CWorkThread\0\0ShowInfo()\0UpdateConfigInfo()\0"
};

void CWorkThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CWorkThread *_t = static_cast<CWorkThread *>(_o);
        switch (_id) {
        case 0: _t->ShowInfo(); break;
        case 1: _t->UpdateConfigInfo(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CWorkThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CWorkThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CWorkThread,
      qt_meta_data_CWorkThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CWorkThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CWorkThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CWorkThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CWorkThread))
        return static_cast<void*>(const_cast< CWorkThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CWorkThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CWorkThread::ShowInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CWorkThread::UpdateConfigInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
