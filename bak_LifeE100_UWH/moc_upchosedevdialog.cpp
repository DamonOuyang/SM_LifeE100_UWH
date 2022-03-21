/****************************************************************************
** Meta object code from reading C++ file 'upchosedevdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "upchosedevdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'upchosedevdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UpChoseDevDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      47,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      70,   62,   17,   17, 0x08,
      99,   62,   17,   17, 0x08,
     128,   62,   17,   17, 0x08,
     157,   62,   17,   17, 0x08,
     186,   17,   17,   17, 0x08,
     208,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UpChoseDevDialog[] = {
    "UpChoseDevDialog\0\0sendChooseDev(unsigned char)\0"
    "sendCanlceUp()\0checked\0"
    "on_pushButton1_clicked(bool)\0"
    "on_pushButton2_clicked(bool)\0"
    "on_pushButton3_clicked(bool)\0"
    "on_pushButton4_clicked(bool)\0"
    "on_upCancel_clicked()\0on_upOk_clicked()\0"
};

void UpChoseDevDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UpChoseDevDialog *_t = static_cast<UpChoseDevDialog *>(_o);
        switch (_id) {
        case 0: _t->sendChooseDev((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 1: _t->sendCanlceUp(); break;
        case 2: _t->on_pushButton1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_pushButton2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_pushButton3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_pushButton4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_upCancel_clicked(); break;
        case 7: _t->on_upOk_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UpChoseDevDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UpChoseDevDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UpChoseDevDialog,
      qt_meta_data_UpChoseDevDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UpChoseDevDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UpChoseDevDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UpChoseDevDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpChoseDevDialog))
        return static_cast<void*>(const_cast< UpChoseDevDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UpChoseDevDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void UpChoseDevDialog::sendChooseDev(unsigned char _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UpChoseDevDialog::sendCanlceUp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
