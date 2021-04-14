/****************************************************************************
** Meta object code from reading C++ file 'carcorderwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/widget/carcorderwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'carcorderwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CarcorderWidget_t {
    QByteArrayData data[13];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CarcorderWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CarcorderWidget_t qt_meta_stringdata_CarcorderWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CarcorderWidget"
QT_MOC_LITERAL(1, 16, 14), // "timer_out_slot"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "hide_slot"
QT_MOC_LITERAL(4, 42, 12), // "capture_slot"
QT_MOC_LITERAL(5, 55, 5), // "index"
QT_MOC_LITERAL(6, 61, 5), // "image"
QT_MOC_LITERAL(7, 67, 12), // "captureClick"
QT_MOC_LITERAL(8, 80, 11), // "replay_slot"
QT_MOC_LITERAL(9, 92, 10), // "image_slot"
QT_MOC_LITERAL(10, 103, 11), // "decode_slot"
QT_MOC_LITERAL(11, 115, 12), // "setting_slot"
QT_MOC_LITERAL(12, 128, 8) // "esc_slot"

    },
    "CarcorderWidget\0timer_out_slot\0\0"
    "hide_slot\0capture_slot\0index\0image\0"
    "captureClick\0replay_slot\0image_slot\0"
    "decode_slot\0setting_slot\0esc_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CarcorderWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    2,   61,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CarcorderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CarcorderWidget *_t = static_cast<CarcorderWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timer_out_slot(); break;
        case 1: _t->hide_slot(); break;
        case 2: _t->capture_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 3: _t->captureClick(); break;
        case 4: _t->replay_slot(); break;
        case 5: _t->image_slot(); break;
        case 6: _t->decode_slot(); break;
        case 7: _t->setting_slot(); break;
        case 8: _t->esc_slot(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CarcorderWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CarcorderWidget.data,
      qt_meta_data_CarcorderWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CarcorderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CarcorderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CarcorderWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CarcorderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
