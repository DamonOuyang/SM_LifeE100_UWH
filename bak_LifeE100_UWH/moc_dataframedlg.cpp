/****************************************************************************
** Meta object code from reading C++ file 'dataframedlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dataframedlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataframedlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataFrameDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      36,   30,   13,   13, 0x08,
      60,   13,   13,   13, 0x08,
      75,   13,   13,   13, 0x08,
      92,   13,   13,   13, 0x08,
     105,   13,   13,   13, 0x08,
     121,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DataFrameDlg[] = {
    "DataFrameDlg\0\0OnExportFiles()\0index\0"
    "OnFileOpen(QModelIndex)\0OnFileOpenEx()\0"
    "OnReflashFiles()\0OnDelFiles()\0"
    "OnDelAllFiles()\0OnTabChanged()\0"
};

void DataFrameDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataFrameDlg *_t = static_cast<DataFrameDlg *>(_o);
        switch (_id) {
        case 0: _t->OnExportFiles(); break;
        case 1: _t->OnFileOpen((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->OnFileOpenEx(); break;
        case 3: _t->OnReflashFiles(); break;
        case 4: _t->OnDelFiles(); break;
        case 5: _t->OnDelAllFiles(); break;
        case 6: _t->OnTabChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DataFrameDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataFrameDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_DataFrameDlg,
      qt_meta_data_DataFrameDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataFrameDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataFrameDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataFrameDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataFrameDlg))
        return static_cast<void*>(const_cast< DataFrameDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int DataFrameDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
