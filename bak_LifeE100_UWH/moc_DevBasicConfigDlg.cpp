/****************************************************************************
** Meta object code from reading C++ file 'DevBasicConfigDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DevBasicConfigDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DevBasicConfigDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DevBasicConfigDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      31,   18,   18,   18, 0x0a,
      47,   18,   18,   18, 0x0a,
      69,   63,   18,   18, 0x0a,
     100,   92,   18,   18, 0x0a,
     134,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DevBasicConfigDlg[] = {
    "DevBasicConfigDlg\0\0OnClickOK()\0"
    "OnClickCancel()\0OnActiveTimer()\0strIn\0"
    "confirmString(QString)\0old,now\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "OnItemEdit()\0"
};

void DevBasicConfigDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DevBasicConfigDlg *_t = static_cast<DevBasicConfigDlg *>(_o);
        switch (_id) {
        case 0: _t->OnClickOK(); break;
        case 1: _t->OnClickCancel(); break;
        case 2: _t->OnActiveTimer(); break;
        case 3: _t->confirmString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 5: _t->OnItemEdit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DevBasicConfigDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DevBasicConfigDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DevBasicConfigDlg,
      qt_meta_data_DevBasicConfigDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DevBasicConfigDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DevBasicConfigDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DevBasicConfigDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DevBasicConfigDlg))
        return static_cast<void*>(const_cast< DevBasicConfigDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int DevBasicConfigDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
