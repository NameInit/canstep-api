/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[86];
    char stringdata0[1102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "ButtonAutosender"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "ButtonConnect"
QT_MOC_LITERAL(4, 43, 13), // "ButtonDebugOn"
QT_MOC_LITERAL(5, 57, 11), // "ButtonBoard"
QT_MOC_LITERAL(6, 69, 11), // "ButtonSteps"
QT_MOC_LITERAL(7, 81, 11), // "ButtonSpeed"
QT_MOC_LITERAL(8, 93, 11), // "ButtonAccel"
QT_MOC_LITERAL(9, 105, 11), // "ButtonDecel"
QT_MOC_LITERAL(10, 117, 13), // "ButtonForward"
QT_MOC_LITERAL(11, 131, 14), // "ButtonBackward"
QT_MOC_LITERAL(12, 146, 13), // "ButtonHomZero"
QT_MOC_LITERAL(13, 160, 12), // "ButtonHomMax"
QT_MOC_LITERAL(14, 173, 14), // "ResetDRVRError"
QT_MOC_LITERAL(15, 188, 4), // "Stop"
QT_MOC_LITERAL(16, 193, 8), // "BrakeOff"
QT_MOC_LITERAL(17, 202, 7), // "BrakeOn"
QT_MOC_LITERAL(18, 210, 9), // "RezervOff"
QT_MOC_LITERAL(19, 220, 8), // "RezervOn"
QT_MOC_LITERAL(20, 229, 12), // "AlarmResetOn"
QT_MOC_LITERAL(21, 242, 13), // "AlarmResetOff"
QT_MOC_LITERAL(22, 256, 10), // "CurrentPos"
QT_MOC_LITERAL(23, 267, 12), // "ResetCANStep"
QT_MOC_LITERAL(24, 280, 8), // "DriverOn"
QT_MOC_LITERAL(25, 289, 9), // "DriverOff"
QT_MOC_LITERAL(26, 299, 17), // "ResetLostCounters"
QT_MOC_LITERAL(27, 317, 11), // "MotorTorque"
QT_MOC_LITERAL(28, 329, 10), // "MotorSpeed"
QT_MOC_LITERAL(29, 340, 9), // "AbsPosRot"
QT_MOC_LITERAL(30, 350, 9), // "AlarmCode"
QT_MOC_LITERAL(31, 360, 12), // "SaveNumBoard"
QT_MOC_LITERAL(32, 373, 12), // "SaveNumGroup"
QT_MOC_LITERAL(33, 386, 12), // "SaveStartPos"
QT_MOC_LITERAL(34, 399, 10), // "SaveEndPos"
QT_MOC_LITERAL(35, 410, 12), // "SaveMaxSpeed"
QT_MOC_LITERAL(36, 423, 16), // "SaveDefaultSpeed"
QT_MOC_LITERAL(37, 440, 9), // "SaveAccel"
QT_MOC_LITERAL(38, 450, 9), // "SaveDecel"
QT_MOC_LITERAL(39, 460, 9), // "SaveDelta"
QT_MOC_LITERAL(40, 470, 10), // "MicroSteps"
QT_MOC_LITERAL(41, 481, 9), // "StepsTurn"
QT_MOC_LITERAL(42, 491, 15), // "Sensor1Polarity"
QT_MOC_LITERAL(43, 507, 15), // "Sensor2Polarity"
QT_MOC_LITERAL(44, 523, 15), // "Sensor3Polarity"
QT_MOC_LITERAL(45, 539, 15), // "Sensor4Polarity"
QT_MOC_LITERAL(46, 555, 10), // "Sensor1Dir"
QT_MOC_LITERAL(47, 566, 10), // "Sensor2Dir"
QT_MOC_LITERAL(48, 577, 10), // "Sensor3Dir"
QT_MOC_LITERAL(49, 588, 10), // "Sensor4Dir"
QT_MOC_LITERAL(50, 599, 14), // "SRVRDYPolarity"
QT_MOC_LITERAL(51, 614, 13), // "INPOSPolarity"
QT_MOC_LITERAL(52, 628, 13), // "FAULTPolarity"
QT_MOC_LITERAL(53, 642, 13), // "BrakePolarity"
QT_MOC_LITERAL(54, 656, 11), // "DirPolarity"
QT_MOC_LITERAL(55, 668, 10), // "EnPolarity"
QT_MOC_LITERAL(56, 679, 14), // "Al_CLRPolarity"
QT_MOC_LITERAL(57, 694, 17), // "Al_OBrakePolarity"
QT_MOC_LITERAL(58, 712, 18), // "Al_ORezervPolarity"
QT_MOC_LITERAL(59, 731, 13), // "EncoderActive"
QT_MOC_LITERAL(60, 745, 13), // "EncoderConfig"
QT_MOC_LITERAL(61, 759, 10), // "startFLASH"
QT_MOC_LITERAL(62, 770, 12), // "startINSTALL"
QT_MOC_LITERAL(63, 783, 9), // "startSAVE"
QT_MOC_LITERAL(64, 793, 8), // "loadMech"
QT_MOC_LITERAL(65, 802, 10), // "executeSce"
QT_MOC_LITERAL(66, 813, 14), // "sendApiRequest"
QT_MOC_LITERAL(67, 828, 8), // "endpoint"
QT_MOC_LITERAL(68, 837, 4), // "data"
QT_MOC_LITERAL(69, 842, 18), // "onApiReplyFinished"
QT_MOC_LITERAL(70, 861, 14), // "QNetworkReply*"
QT_MOC_LITERAL(71, 876, 5), // "reply"
QT_MOC_LITERAL(72, 882, 12), // "showApiError"
QT_MOC_LITERAL(73, 895, 5), // "error"
QT_MOC_LITERAL(74, 901, 17), // "onSocketConnected"
QT_MOC_LITERAL(75, 919, 20), // "onSocketDisconnected"
QT_MOC_LITERAL(76, 940, 30), // "onWebSocketTextMessageReceived"
QT_MOC_LITERAL(77, 971, 7), // "message"
QT_MOC_LITERAL(78, 979, 13), // "onSocketError"
QT_MOC_LITERAL(79, 993, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(80, 1022, 15), // "sendMqttRequest"
QT_MOC_LITERAL(81, 1038, 4), // "part"
QT_MOC_LITERAL(82, 1043, 15), // "onMqttConnected"
QT_MOC_LITERAL(83, 1059, 21), // "onMqttMessageReceived"
QT_MOC_LITERAL(84, 1081, 14), // "QMqttTopicName"
QT_MOC_LITERAL(85, 1096, 5) // "topic"

    },
    "MainWindow\0ButtonAutosender\0\0ButtonConnect\0"
    "ButtonDebugOn\0ButtonBoard\0ButtonSteps\0"
    "ButtonSpeed\0ButtonAccel\0ButtonDecel\0"
    "ButtonForward\0ButtonBackward\0ButtonHomZero\0"
    "ButtonHomMax\0ResetDRVRError\0Stop\0"
    "BrakeOff\0BrakeOn\0RezervOff\0RezervOn\0"
    "AlarmResetOn\0AlarmResetOff\0CurrentPos\0"
    "ResetCANStep\0DriverOn\0DriverOff\0"
    "ResetLostCounters\0MotorTorque\0MotorSpeed\0"
    "AbsPosRot\0AlarmCode\0SaveNumBoard\0"
    "SaveNumGroup\0SaveStartPos\0SaveEndPos\0"
    "SaveMaxSpeed\0SaveDefaultSpeed\0SaveAccel\0"
    "SaveDecel\0SaveDelta\0MicroSteps\0StepsTurn\0"
    "Sensor1Polarity\0Sensor2Polarity\0"
    "Sensor3Polarity\0Sensor4Polarity\0"
    "Sensor1Dir\0Sensor2Dir\0Sensor3Dir\0"
    "Sensor4Dir\0SRVRDYPolarity\0INPOSPolarity\0"
    "FAULTPolarity\0BrakePolarity\0DirPolarity\0"
    "EnPolarity\0Al_CLRPolarity\0Al_OBrakePolarity\0"
    "Al_ORezervPolarity\0EncoderActive\0"
    "EncoderConfig\0startFLASH\0startINSTALL\0"
    "startSAVE\0loadMech\0executeSce\0"
    "sendApiRequest\0endpoint\0data\0"
    "onApiReplyFinished\0QNetworkReply*\0"
    "reply\0showApiError\0error\0onSocketConnected\0"
    "onSocketDisconnected\0"
    "onWebSocketTextMessageReceived\0message\0"
    "onSocketError\0QAbstractSocket::SocketError\0"
    "sendMqttRequest\0part\0onMqttConnected\0"
    "onMqttMessageReceived\0QMqttTopicName\0"
    "topic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      76,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  394,    2, 0x0a /* Public */,
       3,    0,  395,    2, 0x0a /* Public */,
       4,    0,  396,    2, 0x0a /* Public */,
       5,    0,  397,    2, 0x0a /* Public */,
       6,    0,  398,    2, 0x0a /* Public */,
       7,    0,  399,    2, 0x0a /* Public */,
       8,    0,  400,    2, 0x0a /* Public */,
       9,    0,  401,    2, 0x0a /* Public */,
      10,    0,  402,    2, 0x0a /* Public */,
      11,    0,  403,    2, 0x0a /* Public */,
      12,    0,  404,    2, 0x0a /* Public */,
      13,    0,  405,    2, 0x0a /* Public */,
      14,    0,  406,    2, 0x0a /* Public */,
      15,    0,  407,    2, 0x0a /* Public */,
      16,    0,  408,    2, 0x0a /* Public */,
      17,    0,  409,    2, 0x0a /* Public */,
      18,    0,  410,    2, 0x0a /* Public */,
      19,    0,  411,    2, 0x0a /* Public */,
      20,    0,  412,    2, 0x0a /* Public */,
      21,    0,  413,    2, 0x0a /* Public */,
      22,    0,  414,    2, 0x0a /* Public */,
      23,    0,  415,    2, 0x0a /* Public */,
      24,    0,  416,    2, 0x0a /* Public */,
      25,    0,  417,    2, 0x0a /* Public */,
      26,    0,  418,    2, 0x0a /* Public */,
      27,    0,  419,    2, 0x0a /* Public */,
      28,    0,  420,    2, 0x0a /* Public */,
      29,    0,  421,    2, 0x0a /* Public */,
      30,    0,  422,    2, 0x0a /* Public */,
      31,    0,  423,    2, 0x0a /* Public */,
      32,    0,  424,    2, 0x0a /* Public */,
      33,    0,  425,    2, 0x0a /* Public */,
      34,    0,  426,    2, 0x0a /* Public */,
      35,    0,  427,    2, 0x0a /* Public */,
      36,    0,  428,    2, 0x0a /* Public */,
      37,    0,  429,    2, 0x0a /* Public */,
      38,    0,  430,    2, 0x0a /* Public */,
      39,    0,  431,    2, 0x0a /* Public */,
      40,    0,  432,    2, 0x0a /* Public */,
      41,    0,  433,    2, 0x0a /* Public */,
      42,    0,  434,    2, 0x0a /* Public */,
      43,    0,  435,    2, 0x0a /* Public */,
      44,    0,  436,    2, 0x0a /* Public */,
      45,    0,  437,    2, 0x0a /* Public */,
      46,    0,  438,    2, 0x0a /* Public */,
      47,    0,  439,    2, 0x0a /* Public */,
      48,    0,  440,    2, 0x0a /* Public */,
      49,    0,  441,    2, 0x0a /* Public */,
      50,    0,  442,    2, 0x0a /* Public */,
      51,    0,  443,    2, 0x0a /* Public */,
      52,    0,  444,    2, 0x0a /* Public */,
      53,    0,  445,    2, 0x0a /* Public */,
      54,    0,  446,    2, 0x0a /* Public */,
      55,    0,  447,    2, 0x0a /* Public */,
      56,    0,  448,    2, 0x0a /* Public */,
      57,    0,  449,    2, 0x0a /* Public */,
      58,    0,  450,    2, 0x0a /* Public */,
      59,    0,  451,    2, 0x0a /* Public */,
      60,    0,  452,    2, 0x0a /* Public */,
      61,    0,  453,    2, 0x0a /* Public */,
      62,    0,  454,    2, 0x0a /* Public */,
      63,    0,  455,    2, 0x0a /* Public */,
      64,    0,  456,    2, 0x0a /* Public */,
      65,    0,  457,    2, 0x0a /* Public */,
      66,    2,  458,    2, 0x0a /* Public */,
      66,    1,  463,    2, 0x2a /* Public | MethodCloned */,
      69,    1,  466,    2, 0x0a /* Public */,
      72,    1,  469,    2, 0x0a /* Public */,
      74,    0,  472,    2, 0x0a /* Public */,
      75,    0,  473,    2, 0x0a /* Public */,
      76,    1,  474,    2, 0x0a /* Public */,
      78,    1,  477,    2, 0x0a /* Public */,
      80,    2,  480,    2, 0x0a /* Public */,
      80,    1,  485,    2, 0x2a /* Public | MethodCloned */,
      82,    0,  488,    2, 0x0a /* Public */,
      83,    2,  489,    2, 0x0a /* Public */,

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
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   67,   68,
    QMetaType::Void, QMetaType::QString,   67,
    QMetaType::Void, 0x80000000 | 70,   71,
    QMetaType::Void, QMetaType::QString,   73,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   77,
    QMetaType::Void, 0x80000000 | 79,   73,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   81,   68,
    QMetaType::Void, QMetaType::QString,   81,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 84,   77,   85,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ButtonAutosender(); break;
        case 1: _t->ButtonConnect(); break;
        case 2: _t->ButtonDebugOn(); break;
        case 3: _t->ButtonBoard(); break;
        case 4: _t->ButtonSteps(); break;
        case 5: _t->ButtonSpeed(); break;
        case 6: _t->ButtonAccel(); break;
        case 7: _t->ButtonDecel(); break;
        case 8: _t->ButtonForward(); break;
        case 9: _t->ButtonBackward(); break;
        case 10: _t->ButtonHomZero(); break;
        case 11: _t->ButtonHomMax(); break;
        case 12: _t->ResetDRVRError(); break;
        case 13: _t->Stop(); break;
        case 14: _t->BrakeOff(); break;
        case 15: _t->BrakeOn(); break;
        case 16: _t->RezervOff(); break;
        case 17: _t->RezervOn(); break;
        case 18: _t->AlarmResetOn(); break;
        case 19: _t->AlarmResetOff(); break;
        case 20: _t->CurrentPos(); break;
        case 21: _t->ResetCANStep(); break;
        case 22: _t->DriverOn(); break;
        case 23: _t->DriverOff(); break;
        case 24: _t->ResetLostCounters(); break;
        case 25: _t->MotorTorque(); break;
        case 26: _t->MotorSpeed(); break;
        case 27: _t->AbsPosRot(); break;
        case 28: _t->AlarmCode(); break;
        case 29: _t->SaveNumBoard(); break;
        case 30: _t->SaveNumGroup(); break;
        case 31: _t->SaveStartPos(); break;
        case 32: _t->SaveEndPos(); break;
        case 33: _t->SaveMaxSpeed(); break;
        case 34: _t->SaveDefaultSpeed(); break;
        case 35: _t->SaveAccel(); break;
        case 36: _t->SaveDecel(); break;
        case 37: _t->SaveDelta(); break;
        case 38: _t->MicroSteps(); break;
        case 39: _t->StepsTurn(); break;
        case 40: _t->Sensor1Polarity(); break;
        case 41: _t->Sensor2Polarity(); break;
        case 42: _t->Sensor3Polarity(); break;
        case 43: _t->Sensor4Polarity(); break;
        case 44: _t->Sensor1Dir(); break;
        case 45: _t->Sensor2Dir(); break;
        case 46: _t->Sensor3Dir(); break;
        case 47: _t->Sensor4Dir(); break;
        case 48: _t->SRVRDYPolarity(); break;
        case 49: _t->INPOSPolarity(); break;
        case 50: _t->FAULTPolarity(); break;
        case 51: _t->BrakePolarity(); break;
        case 52: _t->DirPolarity(); break;
        case 53: _t->EnPolarity(); break;
        case 54: _t->Al_CLRPolarity(); break;
        case 55: _t->Al_OBrakePolarity(); break;
        case 56: _t->Al_ORezervPolarity(); break;
        case 57: _t->EncoderActive(); break;
        case 58: _t->EncoderConfig(); break;
        case 59: _t->startFLASH(); break;
        case 60: _t->startINSTALL(); break;
        case 61: _t->startSAVE(); break;
        case 62: _t->loadMech(); break;
        case 63: _t->executeSce(); break;
        case 64: _t->sendApiRequest((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 65: _t->sendApiRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 66: _t->onApiReplyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 67: _t->showApiError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 68: _t->onSocketConnected(); break;
        case 69: _t->onSocketDisconnected(); break;
        case 70: _t->onWebSocketTextMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 71: _t->onSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 72: _t->sendMqttRequest((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 73: _t->sendMqttRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 74: _t->onMqttConnected(); break;
        case 75: _t->onMqttMessageReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QMqttTopicName(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 66:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 71:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 75:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttTopicName >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 76)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 76;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 76)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 76;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
