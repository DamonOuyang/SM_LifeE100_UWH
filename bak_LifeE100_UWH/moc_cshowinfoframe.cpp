/****************************************************************************
** Meta object code from reading C++ file 'cshowinfoframe.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cshowinfoframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cshowinfoframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CShowInfoFrame[] = {

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
      16,   15,   15,   15, 0x08,
      47,   39,   15,   15, 0x08,
      73,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CShowInfoFrame[] = {
    "CShowInfoFrame\0\0on_pClearBut_clicked()\0"
    "checked\0on_pStopBut_clicked(bool)\0"
    "ShowString()\0"
};

void CShowInfoFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CShowInfoFrame *_t = static_cast<CShowInfoFrame *>(_o);
        switch (_id) {
        case 0: _t->on_pClearBut_clicked(); break;
        case 1: _t->on_pStopBut_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ShowString(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CShowInfoFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CShowInfoFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CShowInfoFrame,
      qt_meta_data_CShowInfoFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CShowInfoFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CShowInfoFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CShowInfoFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CShowInfoFrame))
        return static_cast<void*>(const_cast< CShowInfoFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int CShowInfoFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
