/****************************************************************************
** Meta object code from reading C++ file 'akkwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Akk/akkwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'akkwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AkkWindow_t {
    QByteArrayData data[16];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AkkWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AkkWindow_t qt_meta_stringdata_AkkWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AkkWindow"
QT_MOC_LITERAL(1, 10, 10), // "currentRow"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "curRow"
QT_MOC_LITERAL(4, 29, 15), // "PassTextChanged"
QT_MOC_LITERAL(5, 45, 3), // "str"
QT_MOC_LITERAL(6, 49, 17), // "SearchTextChanged"
QT_MOC_LITERAL(7, 67, 11), // "LoadClicked"
QT_MOC_LITERAL(8, 79, 10), // "addClicked"
QT_MOC_LITERAL(9, 90, 11), // "editClicked"
QT_MOC_LITERAL(10, 102, 10), // "delClicked"
QT_MOC_LITERAL(11, 113, 11), // "saveClicked"
QT_MOC_LITERAL(12, 125, 13), // "saveAsClicked"
QT_MOC_LITERAL(13, 139, 9), // "addToAkks"
QT_MOC_LITERAL(14, 149, 14), // "encryptClicked"
QT_MOC_LITERAL(15, 164, 14) // "decryptClicked"

    },
    "AkkWindow\0currentRow\0\0curRow\0"
    "PassTextChanged\0str\0SearchTextChanged\0"
    "LoadClicked\0addClicked\0editClicked\0"
    "delClicked\0saveClicked\0saveAsClicked\0"
    "addToAkks\0encryptClicked\0decryptClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AkkWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    1,   77,    2, 0x08 /* Private */,
       6,    1,   80,    2, 0x08 /* Private */,
       7,    0,   83,    2, 0x08 /* Private */,
       8,    0,   84,    2, 0x08 /* Private */,
       9,    0,   85,    2, 0x08 /* Private */,
      10,    0,   86,    2, 0x08 /* Private */,
      11,    0,   87,    2, 0x08 /* Private */,
      12,    0,   88,    2, 0x08 /* Private */,
      13,    0,   89,    2, 0x08 /* Private */,
      14,    0,   90,    2, 0x08 /* Private */,
      15,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AkkWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AkkWindow *_t = static_cast<AkkWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->PassTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SearchTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->LoadClicked(); break;
        case 4: _t->addClicked(); break;
        case 5: _t->editClicked(); break;
        case 6: _t->delClicked(); break;
        case 7: _t->saveClicked(); break;
        case 8: _t->saveAsClicked(); break;
        case 9: _t->addToAkks(); break;
        case 10: _t->encryptClicked(); break;
        case 11: _t->decryptClicked(); break;
        default: ;
        }
    }
}

const QMetaObject AkkWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AkkWindow.data,
      qt_meta_data_AkkWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AkkWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AkkWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AkkWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AkkWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
