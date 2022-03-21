/****************************************************************************
** Meta object code from reading C++ file 'setvaldialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "setvaldialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setvaldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SetValDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   14,   13,   13, 0x05,
      46,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   13,   13,   13, 0x08,
      88,   13,   13,   13, 0x08,
     115,   13,   13,   13, 0x08,
     131,   13,   13,   13, 0x08,
     154,   13,   13,   13, 0x08,
     178,   13,   13,   13, 0x08,
     197,   13,   13,   13, 0x08,
     219,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SetValDialog[] = {
    "SetValDialog\0\0gemfield\0sendSetNumber(QString)\0"
    "sendSetCanlce()\0on_reduceButton_pressed()\0"
    "on_reduceButton_released()\0OnReduceTimer()\0"
    "on_addButton_pressed()\0on_addButton_released()\0"
    "OnAddButtonTimer()\0on_okButton_clicked()\0"
    "on_cancelButton_clicked()\0"
};

void SetValDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SetValDialog *_t = static_cast<SetValDialog *>(_o);
        switch (_id) {
        case 0: _t->sendSetNumber((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendSetCanlce(); break;
        case 2: _t->on_reduceButton_pressed(); break;
        case 3: _t->on_reduceButton_released(); break;
        case 4: _t->OnReduceTimer(); break;
        case 5: _t->on_addButton_pressed(); break;
        case 6: _t->on_addButton_released(); break;
        case 7: _t->OnAddButtonTimer(); break;
        case 8: _t->on_okButton_clicked(); break;
        case 9: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SetValDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SetValDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetValDialog,
      qt_meta_data_SetValDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SetValDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SetValDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SetValDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetValDialog))
        return static_cast<void*>(const_cast< SetValDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetValDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SetValDialog::sendSetNumber(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SetValDialog::sendSetCanlce()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
