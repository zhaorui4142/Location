/****************************************************************************
** Meta object code from reading C++ file 'detector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../location/detector/detector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'detector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Detector_t {
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Detector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Detector_t qt_meta_stringdata_Detector = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Detector"
QT_MOC_LITERAL(1, 9, 11), // "resultReady"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 18), // "DetectResultStruct"
QT_MOC_LITERAL(4, 41, 6), // "result"
QT_MOC_LITERAL(5, 48, 12), // "receiveFrame"
QT_MOC_LITERAL(6, 61, 18), // "FrameRawDataStruct"
QT_MOC_LITERAL(7, 80, 5) // "frame"

    },
    "Detector\0resultReady\0\0DetectResultStruct\0"
    "result\0receiveFrame\0FrameRawDataStruct\0"
    "frame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Detector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Detector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Detector *_t = static_cast<Detector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        case 1: _t->receiveFrame((*reinterpret_cast< FrameRawDataStruct(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Detector::*_t)(DetectResultStruct );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Detector::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Detector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Detector.data,
      qt_meta_data_Detector,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Detector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Detector::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Detector.stringdata0))
        return static_cast<void*>(const_cast< Detector*>(this));
    return QObject::qt_metacast(_clname);
}

int Detector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Detector::resultReady(DetectResultStruct _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[5];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 11), // "resultReady"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 18), // "DetectResultStruct"
QT_MOC_LITERAL(4, 39, 6) // "result"

    },
    "Worker\0resultReady\0\0DetectResultStruct\0"
    "result"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Worker *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Worker::*_t)(DetectResultStruct );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worker.data,
      qt_meta_data_Worker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(const_cast< Worker*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< Worker*>(this));
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Worker::resultReady(DetectResultStruct _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
