/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[38];
    char stringdata0[11];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[12];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[12];
    char stringdata8[12];
    char stringdata9[14];
    char stringdata10[15];
    char stringdata11[15];
    char stringdata12[9];
    char stringdata13[5];
    char stringdata14[19];
    char stringdata15[15];
    char stringdata16[6];
    char stringdata17[13];
    char stringdata18[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 13),  // "ButtonConnect"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 13),  // "ButtonDebugOn"
        QT_MOC_LITERAL(40, 11),  // "ButtonBoard"
        QT_MOC_LITERAL(52, 11),  // "ButtonSteps"
        QT_MOC_LITERAL(64, 11),  // "ButtonSpeed"
        QT_MOC_LITERAL(76, 11),  // "ButtonAccel"
        QT_MOC_LITERAL(88, 11),  // "ButtonDecel"
        QT_MOC_LITERAL(100, 13),  // "ButtonForward"
        QT_MOC_LITERAL(114, 14),  // "ButtonBackward"
        QT_MOC_LITERAL(129, 14),  // "sendApiRequest"
        QT_MOC_LITERAL(144, 8),  // "endpoint"
        QT_MOC_LITERAL(153, 4),  // "data"
        QT_MOC_LITERAL(158, 18),  // "onApiReplyFinished"
        QT_MOC_LITERAL(177, 14),  // "QNetworkReply*"
        QT_MOC_LITERAL(192, 5),  // "reply"
        QT_MOC_LITERAL(198, 12),  // "showApiError"
        QT_MOC_LITERAL(211, 5)   // "error"
    },
    "MainWindow",
    "ButtonConnect",
    "",
    "ButtonDebugOn",
    "ButtonBoard",
    "ButtonSteps",
    "ButtonSpeed",
    "ButtonAccel",
    "ButtonDecel",
    "ButtonForward",
    "ButtonBackward",
    "sendApiRequest",
    "endpoint",
    "data",
    "onApiReplyFinished",
    "QNetworkReply*",
    "reply",
    "showApiError",
    "error"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x0a,    1 /* Public */,
       3,    0,   93,    2, 0x0a,    2 /* Public */,
       4,    0,   94,    2, 0x0a,    3 /* Public */,
       5,    0,   95,    2, 0x0a,    4 /* Public */,
       6,    0,   96,    2, 0x0a,    5 /* Public */,
       7,    0,   97,    2, 0x0a,    6 /* Public */,
       8,    0,   98,    2, 0x0a,    7 /* Public */,
       9,    0,   99,    2, 0x0a,    8 /* Public */,
      10,    0,  100,    2, 0x0a,    9 /* Public */,
      11,    2,  101,    2, 0x0a,   10 /* Public */,
      11,    1,  106,    2, 0x2a,   13 /* Public | MethodCloned */,
      14,    1,  109,    2, 0x0a,   15 /* Public */,
      17,    1,  112,    2, 0x0a,   17 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   12,   13,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'ButtonConnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonDebugOn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonBoard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonSteps'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonSpeed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonAccel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonDecel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonForward'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonBackward'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendApiRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonObject &, std::false_type>,
        // method 'sendApiRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onApiReplyFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'showApiError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ButtonConnect(); break;
        case 1: _t->ButtonDebugOn(); break;
        case 2: _t->ButtonBoard(); break;
        case 3: _t->ButtonSteps(); break;
        case 4: _t->ButtonSpeed(); break;
        case 5: _t->ButtonAccel(); break;
        case 6: _t->ButtonDecel(); break;
        case 7: _t->ButtonForward(); break;
        case 8: _t->ButtonBackward(); break;
        case 9: _t->sendApiRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 10: _t->sendApiRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->onApiReplyFinished((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 12: _t->showApiError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
