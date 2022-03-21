/****************************************************************************
** Meta object code from reading C++ file 'BatteryLogManage.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "BatteryLogManage.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BatteryLogManage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BatteryLogManage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
      14,  119, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   17,   17,   17, 0x08,
      76,   58,   17,   17, 0x0a,
      98,   58,   17,   17, 0x0a,
     125,  116,   17,   17, 0x0a,
     153,  144,   17,   17, 0x0a,
     172,   18,   17,   17, 0x0a,
     202,  188,   17,   17, 0x0a,
     232,  221,   17,   17, 0x0a,
     253,  221,   17,   17, 0x0a,
     277,  272,   17,   17, 0x0a,
     292,  272,   17,   17, 0x0a,
     318,  305,   17,   17, 0x0a,
     348,  339,   17,   17, 0x0a,
     376,  365,   17,   17, 0x0a,
     412,  395,   17,   17, 0x0a,
     455,  440,   17,   17, 0x0a,
     497,  481,   17,   17, 0x0a,
     538,  524,   17,   17, 0x0a,
     580,  563,   17,   17, 0x0a,
     623,  608,   17,   17, 0x0a,

 // properties: name, type, flags
     116,  649, ((uint)QMetaType::QReal << 24) | 0x00095103,
     144,  649, ((uint)QMetaType::QReal << 24) | 0x00095103,
      18,  649, ((uint)QMetaType::QReal << 24) | 0x00095103,
     221,  649, ((uint)QMetaType::QReal << 24) | 0x00095103,
     272,  649, ((uint)QMetaType::QReal << 24) | 0x00095103,
     305,  655, 0x02095103,
     339,  655, 0x02095103,
     365,  655, 0x02095103,
     395,  659, 0x43095103,
     440,  659, 0x43095103,
     481,  659, 0x43095103,
     524,  659, 0x43095103,
     563,  659, 0x43095103,
     608,  659, 0x43095103,

       0        // eod
};

static const char qt_meta_stringdata_BatteryLogManage[] = {
    "BatteryLogManage\0\0value\0valueChanged(qreal)\0"
    "updateValue()\0minValue,maxValue\0"
    "setRange(qreal,qreal)\0setRange(int,int)\0"
    "minValue\0setMinValue(qreal)\0maxValue\0"
    "setMaxValue(qreal)\0setValue(qreal)\0"
    "value,bDisFlg\0setValue(int,bool)\0"
    "alarmValue\0setAlarmValue(qreal)\0"
    "setAlarmValue(int)\0step\0setStep(qreal)\0"
    "setStep(int)\0borderRadius\0"
    "setBorderRadius(int)\0bgRadius\0"
    "setBgRadius(int)\0headRadius\0"
    "setHeadRadius(int)\0borderColorStart\0"
    "setBorderColorStart(QColor)\0borderColorEnd\0"
    "setBorderColorEnd(QColor)\0alarmColorStart\0"
    "setAlarmColorStart(QColor)\0alarmColorEnd\0"
    "setAlarmColorEnd(QColor)\0normalColorStart\0"
    "setNormalColorStart(QColor)\0normalColorEnd\0"
    "setNormalColorEnd(QColor)\0qreal\0int\0"
    "QColor\0"
};

void BatteryLogManage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BatteryLogManage *_t = static_cast<BatteryLogManage *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->updateValue(); break;
        case 2: _t->setRange((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 3: _t->setRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->setMinValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 5: _t->setMaxValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->setValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->setValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->setAlarmValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 9: _t->setAlarmValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setStep((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 11: _t->setStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setBorderRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setBgRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setHeadRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->setBorderColorStart((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 16: _t->setBorderColorEnd((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 17: _t->setAlarmColorStart((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 18: _t->setAlarmColorEnd((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 19: _t->setNormalColorStart((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 20: _t->setNormalColorEnd((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BatteryLogManage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BatteryLogManage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BatteryLogManage,
      qt_meta_data_BatteryLogManage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BatteryLogManage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BatteryLogManage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BatteryLogManage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BatteryLogManage))
        return static_cast<void*>(const_cast< BatteryLogManage*>(this));
    return QWidget::qt_metacast(_clname);
}

int BatteryLogManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = getMinValue(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = getMaxValue(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = getValue(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = getAlarmValue(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = getStep(); break;
        case 5: *reinterpret_cast< int*>(_v) = getBorderRadius(); break;
        case 6: *reinterpret_cast< int*>(_v) = getBgRadius(); break;
        case 7: *reinterpret_cast< int*>(_v) = getHeadRadius(); break;
        case 8: *reinterpret_cast< QColor*>(_v) = getBorderColorStart(); break;
        case 9: *reinterpret_cast< QColor*>(_v) = getBorderColorEnd(); break;
        case 10: *reinterpret_cast< QColor*>(_v) = getAlarmColorStart(); break;
        case 11: *reinterpret_cast< QColor*>(_v) = getAlarmColorEnd(); break;
        case 12: *reinterpret_cast< QColor*>(_v) = getNormalColorStart(); break;
        case 13: *reinterpret_cast< QColor*>(_v) = getNormalColorEnd(); break;
        }
        _id -= 14;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMinValue(*reinterpret_cast< qreal*>(_v)); break;
        case 1: setMaxValue(*reinterpret_cast< qreal*>(_v)); break;
        case 2: setValue(*reinterpret_cast< qreal*>(_v)); break;
        case 3: setAlarmValue(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setStep(*reinterpret_cast< qreal*>(_v)); break;
        case 5: setBorderRadius(*reinterpret_cast< int*>(_v)); break;
        case 6: setBgRadius(*reinterpret_cast< int*>(_v)); break;
        case 7: setHeadRadius(*reinterpret_cast< int*>(_v)); break;
        case 8: setBorderColorStart(*reinterpret_cast< QColor*>(_v)); break;
        case 9: setBorderColorEnd(*reinterpret_cast< QColor*>(_v)); break;
        case 10: setAlarmColorStart(*reinterpret_cast< QColor*>(_v)); break;
        case 11: setAlarmColorEnd(*reinterpret_cast< QColor*>(_v)); break;
        case 12: setNormalColorStart(*reinterpret_cast< QColor*>(_v)); break;
        case 13: setNormalColorEnd(*reinterpret_cast< QColor*>(_v)); break;
        }
        _id -= 14;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BatteryLogManage::valueChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
