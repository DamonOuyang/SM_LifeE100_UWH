/****************************************************************************
** Meta object code from reading C++ file 'configbasicframe.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "configbasicframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configbasicframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConfigBasicFrame[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   17,   17,   17, 0x0a,
      45,   17,   17,   17, 0x0a,
      61,   17,   17,   17, 0x0a,
      80,   17,   17,   17, 0x0a,
     104,   98,   17,   17, 0x0a,
     135,  127,   17,   17, 0x0a,
     169,   17,   17,   17, 0x0a,
     182,   17,   17,   17, 0x0a,
     198,   17,   17,   17, 0x0a,
     213,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigBasicFrame[] = {
    "ConfigBasicFrame\0\0ExitLoginFlg()\0"
    "OnClickOK()\0OnClickCancel()\0"
    "OnClickAlarmPath()\0OnClickDatePath()\0"
    "strIn\0confirmString(QString)\0old,now\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "OnItemEdit()\0OnUpdDateTime()\0"
    "OnPwdModEdit()\0OnExitLogin()\0"
};

void ConfigBasicFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConfigBasicFrame *_t = static_cast<ConfigBasicFrame *>(_o);
        switch (_id) {
        case 0: _t->ExitLoginFlg(); break;
        case 1: _t->OnClickOK(); break;
        case 2: _t->OnClickCancel(); break;
        case 3: _t->OnClickAlarmPath(); break;
        case 4: _t->OnClickDatePath(); break;
        case 5: _t->confirmString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 7: _t->OnItemEdit(); break;
        case 8: _t->OnUpdDateTime(); break;
        case 9: _t->OnPwdModEdit(); break;
        case 10: _t->OnExitLogin(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConfigBasicFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigBasicFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ConfigBasicFrame,
      qt_meta_data_ConfigBasicFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigBasicFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigBasicFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigBasicFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigBasicFrame))
        return static_cast<void*>(const_cast< ConfigBasicFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int ConfigBasicFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ConfigBasicFrame::ExitLoginFlg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
