/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../location/glwidget/glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GlWidget_t {
    QByteArrayData data[11];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GlWidget_t qt_meta_stringdata_GlWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GlWidget"
QT_MOC_LITERAL(1, 9, 7), // "cleanup"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "receiveFrame"
QT_MOC_LITERAL(4, 31, 18), // "FrameRawDataStruct"
QT_MOC_LITERAL(5, 50, 5), // "frame"
QT_MOC_LITERAL(6, 56, 21), // "receiveDetectorResult"
QT_MOC_LITERAL(7, 78, 18), // "DetectResultStruct"
QT_MOC_LITERAL(8, 97, 6), // "result"
QT_MOC_LITERAL(9, 104, 16), // "showErrorPicture"
QT_MOC_LITERAL(10, 121, 12) // "refreshFrame"

    },
    "GlWidget\0cleanup\0\0receiveFrame\0"
    "FrameRawDataStruct\0frame\0receiveDetectorResult\0"
    "DetectResultStruct\0result\0showErrorPicture\0"
    "refreshFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GlWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,
       9,    0,   46,    2, 0x0a /* Public */,
      10,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GlWidget *_t = static_cast<GlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cleanup(); break;
        case 1: _t->receiveFrame((*reinterpret_cast< FrameRawDataStruct(*)>(_a[1]))); break;
        case 2: _t->receiveDetectorResult((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        case 3: _t->showErrorPicture(); break;
        case 4: _t->refreshFrame(); break;
        default: ;
        }
    }
}

const QMetaObject GlWidget::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_GlWidget.data,
      qt_meta_data_GlWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GlWidget.stringdata0))
        return static_cast<void*>(const_cast< GlWidget*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< GlWidget*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int GlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
