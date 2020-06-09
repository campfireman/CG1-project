/****************************************************************************
** Meta object code from reading C++ file 'CgQtGui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CgQtViewer/CgQtGui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CgQtGui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CgQtGui_t {
    QByteArrayData data[22];
    char stringdata0[380];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CgQtGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CgQtGui_t qt_meta_stringdata_CgQtGui = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CgQtGui"
QT_MOC_LITERAL(1, 8, 10), // "mouseEvent"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 33, 5), // "event"
QT_MOC_LITERAL(5, 39, 15), // "viewportChanged"
QT_MOC_LITERAL(6, 55, 20), // "slotTrackballChanged"
QT_MOC_LITERAL(7, 76, 22), // "slotRGBRedInputChanged"
QT_MOC_LITERAL(8, 99, 5), // "value"
QT_MOC_LITERAL(9, 105, 24), // "slotRGBGreenInputChanged"
QT_MOC_LITERAL(10, 130, 23), // "slotRGBBlueInputChanged"
QT_MOC_LITERAL(11, 154, 23), // "slotLateralStepsChanged"
QT_MOC_LITERAL(12, 178, 21), // "slotIterationsChanged"
QT_MOC_LITERAL(13, 200, 12), // "slotNChanged"
QT_MOC_LITERAL(14, 213, 26), // "slotShowFaceNormalsChanged"
QT_MOC_LITERAL(15, 240, 5), // "state"
QT_MOC_LITERAL(16, 246, 28), // "slotShowVertexNormalsChanged"
QT_MOC_LITERAL(17, 275, 26), // "slotObjectSelectionChanged"
QT_MOC_LITERAL(18, 302, 6), // "object"
QT_MOC_LITERAL(19, 309, 21), // "slotDrawButtonPressed"
QT_MOC_LITERAL(20, 331, 31), // "slotButtonGroupSelectionChanged"
QT_MOC_LITERAL(21, 363, 16) // "slotLoadMeshFile"

    },
    "CgQtGui\0mouseEvent\0\0QMouseEvent*\0event\0"
    "viewportChanged\0slotTrackballChanged\0"
    "slotRGBRedInputChanged\0value\0"
    "slotRGBGreenInputChanged\0"
    "slotRGBBlueInputChanged\0slotLateralStepsChanged\0"
    "slotIterationsChanged\0slotNChanged\0"
    "slotShowFaceNormalsChanged\0state\0"
    "slotShowVertexNormalsChanged\0"
    "slotObjectSelectionChanged\0object\0"
    "slotDrawButtonPressed\0"
    "slotButtonGroupSelectionChanged\0"
    "slotLoadMeshFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CgQtGui[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x08 /* Private */,
       5,    2,   92,    2, 0x08 /* Private */,
       6,    0,   97,    2, 0x08 /* Private */,
       7,    1,   98,    2, 0x08 /* Private */,
       9,    1,  101,    2, 0x08 /* Private */,
      10,    1,  104,    2, 0x08 /* Private */,
      11,    1,  107,    2, 0x08 /* Private */,
      12,    1,  110,    2, 0x08 /* Private */,
      13,    1,  113,    2, 0x08 /* Private */,
      14,    1,  116,    2, 0x08 /* Private */,
      16,    1,  119,    2, 0x08 /* Private */,
      17,    1,  122,    2, 0x08 /* Private */,
      19,    0,  125,    2, 0x08 /* Private */,
      20,    0,  126,    2, 0x08 /* Private */,
      21,    0,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CgQtGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CgQtGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->viewportChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotTrackballChanged(); break;
        case 3: _t->slotRGBRedInputChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotRGBGreenInputChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotRGBBlueInputChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotLateralStepsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotIterationsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slotNChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotShowFaceNormalsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slotShowVertexNormalsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slotObjectSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slotDrawButtonPressed(); break;
        case 13: _t->slotButtonGroupSelectionChanged(); break;
        case 14: _t->slotLoadMeshFile(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CgQtGui::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CgQtGui.data,
    qt_meta_data_CgQtGui,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CgQtGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CgQtGui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CgQtGui.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CgObservable"))
        return static_cast< CgObservable*>(this);
    return QWidget::qt_metacast(_clname);
}

int CgQtGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
