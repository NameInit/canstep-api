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
    uint offsetsAndSizes[102];
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
    char stringdata11[14];
    char stringdata12[13];
    char stringdata13[15];
    char stringdata14[5];
    char stringdata15[9];
    char stringdata16[8];
    char stringdata17[10];
    char stringdata18[9];
    char stringdata19[13];
    char stringdata20[14];
    char stringdata21[11];
    char stringdata22[13];
    char stringdata23[9];
    char stringdata24[10];
    char stringdata25[18];
    char stringdata26[12];
    char stringdata27[11];
    char stringdata28[10];
    char stringdata29[10];
    char stringdata30[13];
    char stringdata31[13];
    char stringdata32[13];
    char stringdata33[11];
    char stringdata34[13];
    char stringdata35[17];
    char stringdata36[10];
    char stringdata37[10];
    char stringdata38[10];
    char stringdata39[16];
    char stringdata40[16];
    char stringdata41[16];
    char stringdata42[16];
    char stringdata43[15];
    char stringdata44[9];
    char stringdata45[5];
    char stringdata46[19];
    char stringdata47[15];
    char stringdata48[6];
    char stringdata49[13];
    char stringdata50[6];
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
        QT_MOC_LITERAL(129, 13),  // "ButtonHomZero"
        QT_MOC_LITERAL(143, 12),  // "ButtonHomMax"
        QT_MOC_LITERAL(156, 14),  // "ResetDRVRError"
        QT_MOC_LITERAL(171, 4),  // "Stop"
        QT_MOC_LITERAL(176, 8),  // "BrakeOff"
        QT_MOC_LITERAL(185, 7),  // "BrakeOn"
        QT_MOC_LITERAL(193, 9),  // "RezervOff"
        QT_MOC_LITERAL(203, 8),  // "RezervOn"
        QT_MOC_LITERAL(212, 12),  // "AlarmResetOn"
        QT_MOC_LITERAL(225, 13),  // "AlarmResetOff"
        QT_MOC_LITERAL(239, 10),  // "CurrentPos"
        QT_MOC_LITERAL(250, 12),  // "ResetCANStep"
        QT_MOC_LITERAL(263, 8),  // "DriverOn"
        QT_MOC_LITERAL(272, 9),  // "DriverOff"
        QT_MOC_LITERAL(282, 17),  // "ResetLostCounters"
        QT_MOC_LITERAL(300, 11),  // "MotorTorque"
        QT_MOC_LITERAL(312, 10),  // "MotorSpeed"
        QT_MOC_LITERAL(323, 9),  // "AbsPosRot"
        QT_MOC_LITERAL(333, 9),  // "AlarmCode"
        QT_MOC_LITERAL(343, 12),  // "SaveNumBoard"
        QT_MOC_LITERAL(356, 12),  // "SaveNumGroup"
        QT_MOC_LITERAL(369, 12),  // "SaveStartPos"
        QT_MOC_LITERAL(382, 10),  // "SaveEndPos"
        QT_MOC_LITERAL(393, 12),  // "SaveMaxSpeed"
        QT_MOC_LITERAL(406, 16),  // "SaveDefaultSpeed"
        QT_MOC_LITERAL(423, 9),  // "SaveAccel"
        QT_MOC_LITERAL(433, 9),  // "SaveDecel"
        QT_MOC_LITERAL(443, 9),  // "SaveDelta"
        QT_MOC_LITERAL(453, 15),  // "Sensor1Polarity"
        QT_MOC_LITERAL(469, 15),  // "Sensor2Polarity"
        QT_MOC_LITERAL(485, 15),  // "Sensor3Polarity"
        QT_MOC_LITERAL(501, 15),  // "Sensor4Polarity"
        QT_MOC_LITERAL(517, 14),  // "sendApiRequest"
        QT_MOC_LITERAL(532, 8),  // "endpoint"
        QT_MOC_LITERAL(541, 4),  // "data"
        QT_MOC_LITERAL(546, 18),  // "onApiReplyFinished"
        QT_MOC_LITERAL(565, 14),  // "QNetworkReply*"
        QT_MOC_LITERAL(580, 5),  // "reply"
        QT_MOC_LITERAL(586, 12),  // "showApiError"
        QT_MOC_LITERAL(599, 5)   // "error"
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
    "ButtonHomZero",
    "ButtonHomMax",
    "ResetDRVRError",
    "Stop",
    "BrakeOff",
    "BrakeOn",
    "RezervOff",
    "RezervOn",
    "AlarmResetOn",
    "AlarmResetOff",
    "CurrentPos",
    "ResetCANStep",
    "DriverOn",
    "DriverOff",
    "ResetLostCounters",
    "MotorTorque",
    "MotorSpeed",
    "AbsPosRot",
    "AlarmCode",
    "SaveNumBoard",
    "SaveNumGroup",
    "SaveStartPos",
    "SaveEndPos",
    "SaveMaxSpeed",
    "SaveDefaultSpeed",
    "SaveAccel",
    "SaveDecel",
    "SaveDelta",
    "Sensor1Polarity",
    "Sensor2Polarity",
    "Sensor3Polarity",
    "Sensor4Polarity",
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
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  284,    2, 0x0a,    1 /* Public */,
       3,    0,  285,    2, 0x0a,    2 /* Public */,
       4,    0,  286,    2, 0x0a,    3 /* Public */,
       5,    0,  287,    2, 0x0a,    4 /* Public */,
       6,    0,  288,    2, 0x0a,    5 /* Public */,
       7,    0,  289,    2, 0x0a,    6 /* Public */,
       8,    0,  290,    2, 0x0a,    7 /* Public */,
       9,    0,  291,    2, 0x0a,    8 /* Public */,
      10,    0,  292,    2, 0x0a,    9 /* Public */,
      11,    0,  293,    2, 0x0a,   10 /* Public */,
      12,    0,  294,    2, 0x0a,   11 /* Public */,
      13,    0,  295,    2, 0x0a,   12 /* Public */,
      14,    0,  296,    2, 0x0a,   13 /* Public */,
      15,    0,  297,    2, 0x0a,   14 /* Public */,
      16,    0,  298,    2, 0x0a,   15 /* Public */,
      17,    0,  299,    2, 0x0a,   16 /* Public */,
      18,    0,  300,    2, 0x0a,   17 /* Public */,
      19,    0,  301,    2, 0x0a,   18 /* Public */,
      20,    0,  302,    2, 0x0a,   19 /* Public */,
      21,    0,  303,    2, 0x0a,   20 /* Public */,
      22,    0,  304,    2, 0x0a,   21 /* Public */,
      23,    0,  305,    2, 0x0a,   22 /* Public */,
      24,    0,  306,    2, 0x0a,   23 /* Public */,
      25,    0,  307,    2, 0x0a,   24 /* Public */,
      26,    0,  308,    2, 0x0a,   25 /* Public */,
      27,    0,  309,    2, 0x0a,   26 /* Public */,
      28,    0,  310,    2, 0x0a,   27 /* Public */,
      29,    0,  311,    2, 0x0a,   28 /* Public */,
      30,    0,  312,    2, 0x0a,   29 /* Public */,
      31,    0,  313,    2, 0x0a,   30 /* Public */,
      32,    0,  314,    2, 0x0a,   31 /* Public */,
      33,    0,  315,    2, 0x0a,   32 /* Public */,
      34,    0,  316,    2, 0x0a,   33 /* Public */,
      35,    0,  317,    2, 0x0a,   34 /* Public */,
      36,    0,  318,    2, 0x0a,   35 /* Public */,
      37,    0,  319,    2, 0x0a,   36 /* Public */,
      38,    0,  320,    2, 0x0a,   37 /* Public */,
      39,    0,  321,    2, 0x0a,   38 /* Public */,
      40,    0,  322,    2, 0x0a,   39 /* Public */,
      41,    0,  323,    2, 0x0a,   40 /* Public */,
      42,    0,  324,    2, 0x0a,   41 /* Public */,
      43,    2,  325,    2, 0x0a,   42 /* Public */,
      43,    1,  330,    2, 0x2a,   45 /* Public | MethodCloned */,
      46,    1,  333,    2, 0x0a,   47 /* Public */,
      49,    1,  336,    2, 0x0a,   49 /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   44,   45,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::Void, 0x80000000 | 47,   48,
    QMetaType::Void, QMetaType::QString,   50,

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
        // method 'ButtonHomZero'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ButtonHomMax'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ResetDRVRError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'BrakeOff'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'BrakeOn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'RezervOff'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'RezervOn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AlarmResetOn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AlarmResetOff'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'CurrentPos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ResetCANStep'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'DriverOn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'DriverOff'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ResetLostCounters'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'MotorTorque'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'MotorSpeed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AbsPosRot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AlarmCode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveNumBoard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveNumGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveStartPos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveEndPos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveMaxSpeed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveDefaultSpeed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveAccel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveDecel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SaveDelta'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor1Polarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor2Polarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor3Polarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor4Polarity'
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
        case 9: _t->ButtonHomZero(); break;
        case 10: _t->ButtonHomMax(); break;
        case 11: _t->ResetDRVRError(); break;
        case 12: _t->Stop(); break;
        case 13: _t->BrakeOff(); break;
        case 14: _t->BrakeOn(); break;
        case 15: _t->RezervOff(); break;
        case 16: _t->RezervOn(); break;
        case 17: _t->AlarmResetOn(); break;
        case 18: _t->AlarmResetOff(); break;
        case 19: _t->CurrentPos(); break;
        case 20: _t->ResetCANStep(); break;
        case 21: _t->DriverOn(); break;
        case 22: _t->DriverOff(); break;
        case 23: _t->ResetLostCounters(); break;
        case 24: _t->MotorTorque(); break;
        case 25: _t->MotorSpeed(); break;
        case 26: _t->AbsPosRot(); break;
        case 27: _t->AlarmCode(); break;
        case 28: _t->SaveNumBoard(); break;
        case 29: _t->SaveNumGroup(); break;
        case 30: _t->SaveStartPos(); break;
        case 31: _t->SaveEndPos(); break;
        case 32: _t->SaveMaxSpeed(); break;
        case 33: _t->SaveDefaultSpeed(); break;
        case 34: _t->SaveAccel(); break;
        case 35: _t->SaveDecel(); break;
        case 36: _t->SaveDelta(); break;
        case 37: _t->Sensor1Polarity(); break;
        case 38: _t->Sensor2Polarity(); break;
        case 39: _t->Sensor3Polarity(); break;
        case 40: _t->Sensor4Polarity(); break;
        case 41: _t->sendApiRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 42: _t->sendApiRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 43: _t->onApiReplyFinished((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 44: _t->showApiError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 43:
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
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
