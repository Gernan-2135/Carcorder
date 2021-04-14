/****************************************************************************
** Meta object code from reading C++ file 'playvideowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/widget/playvideowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playvideowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayVideoWidget_t {
    QByteArrayData data[11];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayVideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayVideoWidget_t qt_meta_stringdata_PlayVideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PlayVideoWidget"
QT_MOC_LITERAL(1, 16, 9), // "backClick"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "exportClick"
QT_MOC_LITERAL(4, 39, 10), // "startClick"
QT_MOC_LITERAL(5, 50, 9), // "downClick"
QT_MOC_LITERAL(6, 60, 7), // "upClick"
QT_MOC_LITERAL(7, 68, 16), // "getOneFrame_slot"
QT_MOC_LITERAL(8, 85, 3), // "img"
QT_MOC_LITERAL(9, 89, 12), // "clickCapture"
QT_MOC_LITERAL(10, 102, 10) // "getCapture"

    },
    "PlayVideoWidget\0backClick\0\0exportClick\0"
    "startClick\0downClick\0upClick\0"
    "getOneFrame_slot\0img\0clickCapture\0"
    "getCapture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayVideoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    1,   59,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    1,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    8,

       0        // eod
};

void PlayVideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayVideoWidget *_t = static_cast<PlayVideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backClick(); break;
        case 1: _t->exportClick(); break;
        case 2: _t->startClick(); break;
        case 3: _t->downClick(); break;
        case 4: _t->upClick(); break;
        case 5: _t->getOneFrame_slot((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 6: _t->clickCapture(); break;
        case 7: _t->getCapture((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayVideoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayVideoWidget.data,
      qt_meta_data_PlayVideoWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayVideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayVideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayVideoWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayVideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
