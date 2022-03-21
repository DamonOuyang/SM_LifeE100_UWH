/****************************************************************************
** Meta object code from reading C++ file 'calprmdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calprmdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calprmdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_calPrmDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      26,   13,   13,   13, 0x08,
      51,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_calPrmDialog[] = {
    "calPrmDialog\0\0OnUpdData()\0"
    "on_closeButton_clicked()\0"
    "on_setButton_clicked()\0"
};

void calPrmDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        calPrmDialog *_t = static_cast<calPrmDialog *>(_o);
        switch (_id) {
        case 0: _t->OnUpdData(); break;
        case 1: _t->on_closeButton_clicked(); break;
        case 2: _t->on_setButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData calPrmDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject calPrmDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_calPrmDialog,
      qt_meta_data_calPrmDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &calPrmDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *calPrmDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *calPrmDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_calPrmDialog))
        return static_cast<void*>(const_cast< calPrmDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int calPrmDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
