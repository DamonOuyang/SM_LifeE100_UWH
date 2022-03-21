/****************************************************************************
** Meta object code from reading C++ file 'closepumwindialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "closepumwindialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'closepumwindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClosePumWinDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   18,   18,   18, 0x08,
      76,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClosePumWinDialog[] = {
    "ClosePumWinDialog\0\0bState\0"
    "sendCloseState(bool)\0on_cancelPumButton_clicked()\0"
    "on_closePumButton_clicked()\0"
};

void ClosePumWinDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClosePumWinDialog *_t = static_cast<ClosePumWinDialog *>(_o);
        switch (_id) {
        case 0: _t->sendCloseState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_cancelPumButton_clicked(); break;
        case 2: _t->on_closePumButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ClosePumWinDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClosePumWinDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClosePumWinDialog,
      qt_meta_data_ClosePumWinDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClosePumWinDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClosePumWinDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClosePumWinDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClosePumWinDialog))
        return static_cast<void*>(const_cast< ClosePumWinDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClosePumWinDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ClosePumWinDialog::sendCloseState(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
