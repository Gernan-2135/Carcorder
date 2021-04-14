/****************************************************************************
** Meta object code from reading C++ file 'decodewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/widget/decodewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'decodewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DecodeWidget_t {
    QByteArrayData data[11];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DecodeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DecodeWidget_t qt_meta_stringdata_DecodeWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DecodeWidget"
QT_MOC_LITERAL(1, 13, 14), // "choosePathSlot"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 9), // "enterSlot"
QT_MOC_LITERAL(4, 39, 7), // "escSlot"
QT_MOC_LITERAL(5, 47, 15), // "listItemClicked"
QT_MOC_LITERAL(6, 63, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 80, 4), // "item"
QT_MOC_LITERAL(8, 85, 6), // "rcvSig"
QT_MOC_LITERAL(9, 92, 5), // "value"
QT_MOC_LITERAL(10, 98, 10) // "updateSlot"

    },
    "DecodeWidget\0choosePathSlot\0\0enterSlot\0"
    "escSlot\0listItemClicked\0QListWidgetItem*\0"
    "item\0rcvSig\0value\0updateSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DecodeWidget[] = {

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
       4,    0,   46,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x08 /* Private */,
       8,    1,   50,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void DecodeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DecodeWidget *_t = static_cast<DecodeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choosePathSlot(); break;
        case 1: _t->enterSlot(); break;
        case 2: _t->escSlot(); break;
        case 3: _t->listItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->rcvSig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateSlot(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DecodeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DecodeWidget.data,
      qt_meta_data_DecodeWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DecodeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DecodeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DecodeWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DecodeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
