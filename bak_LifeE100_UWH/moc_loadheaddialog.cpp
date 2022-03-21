/****************************************************************************
** Meta object code from reading C++ file 'loadheaddialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "loadheaddialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loadheaddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoadHeadDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   15,   15,   15, 0x08,
      57,   15,   15,   15, 0x08,
      82,   15,   15,   15, 0x08,
     105,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LoadHeadDialog[] = {
    "LoadHeadDialog\0\0sendCloseHead()\0"
    "on_loadLastBut_clicked()\0"
    "on_loadNextBut_clicked()\0"
    "on_loadOkBut_clicked()\0on_loseAllBut_clicked()\0"
};

void LoadHeadDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoadHeadDialog *_t = static_cast<LoadHeadDialog *>(_o);
        switch (_id) {
        case 0: _t->sendCloseHead(); break;
        case 1: _t->on_loadLastBut_clicked(); break;
        case 2: _t->on_loadNextBut_clicked(); break;
        case 3: _t->on_loadOkBut_clicked(); break;
        case 4: _t->on_loseAllBut_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LoadHeadDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoadHeadDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LoadHeadDialog,
      qt_meta_data_LoadHeadDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadHeadDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadHeadDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadHeadDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadHeadDialog))
        return static_cast<void*>(const_cast< LoadHeadDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LoadHeadDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void LoadHeadDialog::sendCloseHead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
