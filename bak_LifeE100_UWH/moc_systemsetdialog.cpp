/****************************************************************************
** Meta object code from reading C++ file 'systemsetdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "systemsetdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemsetdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SystemSetDialog[] = {

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
      17,   16,   16,   16, 0x0a,
      37,   16,   16,   16, 0x0a,
      53,   16,   16,   16, 0x0a,
      80,   73,   16,   16, 0x0a,
     107,   16,   16,   16, 0x0a,
     135,  118,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SystemSetDialog[] = {
    "SystemSetDialog\0\0BackButtonClicked()\0"
    "OnClickUpdate()\0OnFirtActiveTimer()\0"
    "unTpye\0UpChooseDev(unsigned char)\0"
    "UpCanlce()\0unPre,unFailType\0"
    "UpdateFail(UINT8,UINT8)\0"
};

void SystemSetDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SystemSetDialog *_t = static_cast<SystemSetDialog *>(_o);
        switch (_id) {
        case 0: _t->BackButtonClicked(); break;
        case 1: _t->OnClickUpdate(); break;
        case 2: _t->OnFirtActiveTimer(); break;
        case 3: _t->UpChooseDev((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 4: _t->UpCanlce(); break;
        case 5: _t->UpdateFail((*reinterpret_cast< UINT8(*)>(_a[1])),(*reinterpret_cast< UINT8(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SystemSetDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SystemSetDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SystemSetDialog,
      qt_meta_data_SystemSetDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SystemSetDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SystemSetDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SystemSetDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SystemSetDialog))
        return static_cast<void*>(const_cast< SystemSetDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SystemSetDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
