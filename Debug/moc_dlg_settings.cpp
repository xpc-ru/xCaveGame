/****************************************************************************
** Meta object code from reading C++ file 'dlg_settings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dlg_settings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlg_settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dlgSettings_t {
    QByteArrayData data[9];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dlgSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dlgSettings_t qt_meta_stringdata_dlgSettings = {
    {
QT_MOC_LITERAL(0, 0, 11), // "dlgSettings"
QT_MOC_LITERAL(1, 12, 7), // "fullscr"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "window"
QT_MOC_LITERAL(4, 28, 8), // "maximise"
QT_MOC_LITERAL(5, 37, 6), // "setVol"
QT_MOC_LITERAL(6, 44, 7), // "new_vol"
QT_MOC_LITERAL(7, 52, 7), // "setname"
QT_MOC_LITERAL(8, 60, 4) // "name"

    },
    "dlgSettings\0fullscr\0\0window\0maximise\0"
    "setVol\0new_vol\0setname\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dlgSettings[] = {

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
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    1,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void dlgSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dlgSettings *_t = static_cast<dlgSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fullscr(); break;
        case 1: _t->window(); break;
        case 2: _t->maximise(); break;
        case 3: _t->setVol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setname((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject dlgSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dlgSettings.data,
      qt_meta_data_dlgSettings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *dlgSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dlgSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_dlgSettings.stringdata0))
        return static_cast<void*>(const_cast< dlgSettings*>(this));
    if (!strcmp(_clname, "Ui::Settings"))
        return static_cast< Ui::Settings*>(const_cast< dlgSettings*>(this));
    return QDialog::qt_metacast(_clname);
}

int dlgSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
