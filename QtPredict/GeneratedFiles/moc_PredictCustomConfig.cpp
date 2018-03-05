/****************************************************************************
** Meta object code from reading C++ file 'PredictCustomConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PredictCustomConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PredictCustomConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PredictCustomConfig_t {
    QByteArrayData data[11];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PredictCustomConfig_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PredictCustomConfig_t qt_meta_stringdata_PredictCustomConfig = {
    {
QT_MOC_LITERAL(0, 0, 19), // "PredictCustomConfig"
QT_MOC_LITERAL(1, 20, 6), // "onSave"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "onCancel"
QT_MOC_LITERAL(4, 37, 14), // "onValueChanged"
QT_MOC_LITERAL(5, 52, 11), // "QtProperty*"
QT_MOC_LITERAL(6, 64, 4), // "prop"
QT_MOC_LITERAL(7, 69, 3), // "var"
QT_MOC_LITERAL(8, 73, 10), // "onShowMore"
QT_MOC_LITERAL(9, 84, 11), // "onStatistic"
QT_MOC_LITERAL(10, 96, 11) // "onCalculate"

    },
    "PredictCustomConfig\0onSave\0\0onCancel\0"
    "onValueChanged\0QtProperty*\0prop\0var\0"
    "onShowMore\0onStatistic\0onCalculate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PredictCustomConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    2,   46,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,
       9,    0,   52,    2, 0x0a /* Public */,
      10,    0,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QVariant,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PredictCustomConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PredictCustomConfig *_t = static_cast<PredictCustomConfig *>(_o);
        switch (_id) {
        case 0: _t->onSave(); break;
        case 1: _t->onCancel(); break;
        case 2: _t->onValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 3: _t->onShowMore(); break;
        case 4: _t->onStatistic(); break;
        case 5: _t->onCalculate(); break;
        default: ;
        }
    }
}

const QMetaObject PredictCustomConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PredictCustomConfig.data,
      qt_meta_data_PredictCustomConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PredictCustomConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PredictCustomConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PredictCustomConfig.stringdata))
        return static_cast<void*>(const_cast< PredictCustomConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int PredictCustomConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
