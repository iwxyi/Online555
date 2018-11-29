/****************************************************************************
** Meta object code from reading C++ file 'boardwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../boardwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'boardwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BoardWindow_t {
    QByteArrayData data[14];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BoardWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BoardWindow_t qt_meta_stringdata_BoardWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BoardWindow"
QT_MOC_LITERAL(1, 12, 14), // "signalUserInfo"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "username"
QT_MOC_LITERAL(4, 37, 8), // "integral"
QT_MOC_LITERAL(5, 46, 4), // "rank"
QT_MOC_LITERAL(6, 51, 14), // "slotSwitchRecv"
QT_MOC_LITERAL(7, 66, 3), // "str"
QT_MOC_LITERAL(8, 70, 18), // "slotMovesGridEvent"
QT_MOC_LITERAL(9, 89, 1), // "x"
QT_MOC_LITERAL(10, 91, 1), // "y"
QT_MOC_LITERAL(11, 93, 17), // "slotGameOverEvent"
QT_MOC_LITERAL(12, 111, 6), // "winner"
QT_MOC_LITERAL(13, 118, 4) // "nums"

    },
    "BoardWindow\0signalUserInfo\0\0username\0"
    "integral\0rank\0slotSwitchRecv\0str\0"
    "slotMovesGridEvent\0x\0y\0slotGameOverEvent\0"
    "winner\0nums"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BoardWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   41,    2, 0x0a /* Public */,
       8,    2,   44,    2, 0x0a /* Public */,
      11,    2,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,

       0        // eod
};

void BoardWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BoardWindow *_t = static_cast<BoardWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUserInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->slotSwitchRecv((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotMovesGridEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotGameOverEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BoardWindow::*_t)(QString , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BoardWindow::signalUserInfo)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject BoardWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BoardWindow.data,
      qt_meta_data_BoardWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BoardWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BoardWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BoardWindow.stringdata0))
        return static_cast<void*>(const_cast< BoardWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int BoardWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BoardWindow::signalUserInfo(QString _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
