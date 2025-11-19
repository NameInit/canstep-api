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
    uint offsetsAndSizes[138];
    char stringdata0[11];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[14];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[12];
    char stringdata8[12];
    char stringdata9[12];
    char stringdata10[14];
    char stringdata11[15];
    char stringdata12[14];
    char stringdata13[13];
    char stringdata14[15];
    char stringdata15[5];
    char stringdata16[9];
    char stringdata17[8];
    char stringdata18[10];
    char stringdata19[9];
    char stringdata20[13];
    char stringdata21[14];
    char stringdata22[11];
    char stringdata23[13];
    char stringdata24[9];
    char stringdata25[10];
    char stringdata26[18];
    char stringdata27[12];
    char stringdata28[11];
    char stringdata29[10];
    char stringdata30[10];
    char stringdata31[13];
    char stringdata32[13];
    char stringdata33[13];
    char stringdata34[11];
    char stringdata35[13];
    char stringdata36[17];
    char stringdata37[10];
    char stringdata38[10];
    char stringdata39[10];
    char stringdata40[11];
    char stringdata41[10];
    char stringdata42[16];
    char stringdata43[16];
    char stringdata44[16];
    char stringdata45[16];
    char stringdata46[11];
    char stringdata47[11];
    char stringdata48[11];
    char stringdata49[11];
    char stringdata50[15];
    char stringdata51[14];
    char stringdata52[14];
    char stringdata53[14];
    char stringdata54[12];
    char stringdata55[11];
    char stringdata56[15];
    char stringdata57[18];
    char stringdata58[19];
    char stringdata59[14];
    char stringdata60[14];
    char stringdata61[15];
    char stringdata62[9];
    char stringdata63[5];
    char stringdata64[19];
    char stringdata65[15];
    char stringdata66[6];
    char stringdata67[13];
    char stringdata68[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 16),  // "ButtonAutosender"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 13),  // "ButtonConnect"
        QT_MOC_LITERAL(43, 13),  // "ButtonDebugOn"
        QT_MOC_LITERAL(57, 11),  // "ButtonBoard"
        QT_MOC_LITERAL(69, 11),  // "ButtonSteps"
        QT_MOC_LITERAL(81, 11),  // "ButtonSpeed"
        QT_MOC_LITERAL(93, 11),  // "ButtonAccel"
        QT_MOC_LITERAL(105, 11),  // "ButtonDecel"
        QT_MOC_LITERAL(117, 13),  // "ButtonForward"
        QT_MOC_LITERAL(131, 14),  // "ButtonBackward"
        QT_MOC_LITERAL(146, 13),  // "ButtonHomZero"
        QT_MOC_LITERAL(160, 12),  // "ButtonHomMax"
        QT_MOC_LITERAL(173, 14),  // "ResetDRVRError"
        QT_MOC_LITERAL(188, 4),  // "Stop"
        QT_MOC_LITERAL(193, 8),  // "BrakeOff"
        QT_MOC_LITERAL(202, 7),  // "BrakeOn"
        QT_MOC_LITERAL(210, 9),  // "RezervOff"
        QT_MOC_LITERAL(220, 8),  // "RezervOn"
        QT_MOC_LITERAL(229, 12),  // "AlarmResetOn"
        QT_MOC_LITERAL(242, 13),  // "AlarmResetOff"
        QT_MOC_LITERAL(256, 10),  // "CurrentPos"
        QT_MOC_LITERAL(267, 12),  // "ResetCANStep"
        QT_MOC_LITERAL(280, 8),  // "DriverOn"
        QT_MOC_LITERAL(289, 9),  // "DriverOff"
        QT_MOC_LITERAL(299, 17),  // "ResetLostCounters"
        QT_MOC_LITERAL(317, 11),  // "MotorTorque"
        QT_MOC_LITERAL(329, 10),  // "MotorSpeed"
        QT_MOC_LITERAL(340, 9),  // "AbsPosRot"
        QT_MOC_LITERAL(350, 9),  // "AlarmCode"
        QT_MOC_LITERAL(360, 12),  // "SaveNumBoard"
        QT_MOC_LITERAL(373, 12),  // "SaveNumGroup"
        QT_MOC_LITERAL(386, 12),  // "SaveStartPos"
        QT_MOC_LITERAL(399, 10),  // "SaveEndPos"
        QT_MOC_LITERAL(410, 12),  // "SaveMaxSpeed"
        QT_MOC_LITERAL(423, 16),  // "SaveDefaultSpeed"
        QT_MOC_LITERAL(440, 9),  // "SaveAccel"
        QT_MOC_LITERAL(450, 9),  // "SaveDecel"
        QT_MOC_LITERAL(460, 9),  // "SaveDelta"
        QT_MOC_LITERAL(470, 10),  // "MicroSteps"
        QT_MOC_LITERAL(481, 9),  // "StepsTurn"
        QT_MOC_LITERAL(491, 15),  // "Sensor1Polarity"
        QT_MOC_LITERAL(507, 15),  // "Sensor2Polarity"
        QT_MOC_LITERAL(523, 15),  // "Sensor3Polarity"
        QT_MOC_LITERAL(539, 15),  // "Sensor4Polarity"
        QT_MOC_LITERAL(555, 10),  // "Sensor1Dir"
        QT_MOC_LITERAL(566, 10),  // "Sensor2Dir"
        QT_MOC_LITERAL(577, 10),  // "Sensor3Dir"
        QT_MOC_LITERAL(588, 10),  // "Sensor4Dir"
        QT_MOC_LITERAL(599, 14),  // "SRVRDYPolarity"
        QT_MOC_LITERAL(614, 13),  // "INPOSPolarity"
        QT_MOC_LITERAL(628, 13),  // "FAULTPolarity"
        QT_MOC_LITERAL(642, 13),  // "BrakePolarity"
        QT_MOC_LITERAL(656, 11),  // "DirPolarity"
        QT_MOC_LITERAL(668, 10),  // "EnPolarity"
        QT_MOC_LITERAL(679, 14),  // "Al_CLRPolarity"
        QT_MOC_LITERAL(694, 17),  // "Al_OBrakePolarity"
        QT_MOC_LITERAL(712, 18),  // "Al_ORezervPolarity"
        QT_MOC_LITERAL(731, 13),  // "EncoderActive"
        QT_MOC_LITERAL(745, 13),  // "EncoderConfig"
        QT_MOC_LITERAL(759, 14),  // "sendApiRequest"
        QT_MOC_LITERAL(774, 8),  // "endpoint"
        QT_MOC_LITERAL(783, 4),  // "data"
        QT_MOC_LITERAL(788, 18),  // "onApiReplyFinished"
        QT_MOC_LITERAL(807, 14),  // "QNetworkReply*"
        QT_MOC_LITERAL(822, 5),  // "reply"
        QT_MOC_LITERAL(828, 12),  // "showApiError"
        QT_MOC_LITERAL(841, 5)   // "error"
    },
    "MainWindow",
    "ButtonAutosender",
    "",
    "ButtonConnect",
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
    "MicroSteps",
    "StepsTurn",
    "Sensor1Polarity",
    "Sensor2Polarity",
    "Sensor3Polarity",
    "Sensor4Polarity",
    "Sensor1Dir",
    "Sensor2Dir",
    "Sensor3Dir",
    "Sensor4Dir",
    "SRVRDYPolarity",
    "INPOSPolarity",
    "FAULTPolarity",
    "BrakePolarity",
    "DirPolarity",
    "EnPolarity",
    "Al_CLRPolarity",
    "Al_OBrakePolarity",
    "Al_ORezervPolarity",
    "EncoderActive",
    "EncoderConfig",
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
      63,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  392,    2, 0x0a,    1 /* Public */,
       3,    0,  393,    2, 0x0a,    2 /* Public */,
       4,    0,  394,    2, 0x0a,    3 /* Public */,
       5,    0,  395,    2, 0x0a,    4 /* Public */,
       6,    0,  396,    2, 0x0a,    5 /* Public */,
       7,    0,  397,    2, 0x0a,    6 /* Public */,
       8,    0,  398,    2, 0x0a,    7 /* Public */,
       9,    0,  399,    2, 0x0a,    8 /* Public */,
      10,    0,  400,    2, 0x0a,    9 /* Public */,
      11,    0,  401,    2, 0x0a,   10 /* Public */,
      12,    0,  402,    2, 0x0a,   11 /* Public */,
      13,    0,  403,    2, 0x0a,   12 /* Public */,
      14,    0,  404,    2, 0x0a,   13 /* Public */,
      15,    0,  405,    2, 0x0a,   14 /* Public */,
      16,    0,  406,    2, 0x0a,   15 /* Public */,
      17,    0,  407,    2, 0x0a,   16 /* Public */,
      18,    0,  408,    2, 0x0a,   17 /* Public */,
      19,    0,  409,    2, 0x0a,   18 /* Public */,
      20,    0,  410,    2, 0x0a,   19 /* Public */,
      21,    0,  411,    2, 0x0a,   20 /* Public */,
      22,    0,  412,    2, 0x0a,   21 /* Public */,
      23,    0,  413,    2, 0x0a,   22 /* Public */,
      24,    0,  414,    2, 0x0a,   23 /* Public */,
      25,    0,  415,    2, 0x0a,   24 /* Public */,
      26,    0,  416,    2, 0x0a,   25 /* Public */,
      27,    0,  417,    2, 0x0a,   26 /* Public */,
      28,    0,  418,    2, 0x0a,   27 /* Public */,
      29,    0,  419,    2, 0x0a,   28 /* Public */,
      30,    0,  420,    2, 0x0a,   29 /* Public */,
      31,    0,  421,    2, 0x0a,   30 /* Public */,
      32,    0,  422,    2, 0x0a,   31 /* Public */,
      33,    0,  423,    2, 0x0a,   32 /* Public */,
      34,    0,  424,    2, 0x0a,   33 /* Public */,
      35,    0,  425,    2, 0x0a,   34 /* Public */,
      36,    0,  426,    2, 0x0a,   35 /* Public */,
      37,    0,  427,    2, 0x0a,   36 /* Public */,
      38,    0,  428,    2, 0x0a,   37 /* Public */,
      39,    0,  429,    2, 0x0a,   38 /* Public */,
      40,    0,  430,    2, 0x0a,   39 /* Public */,
      41,    0,  431,    2, 0x0a,   40 /* Public */,
      42,    0,  432,    2, 0x0a,   41 /* Public */,
      43,    0,  433,    2, 0x0a,   42 /* Public */,
      44,    0,  434,    2, 0x0a,   43 /* Public */,
      45,    0,  435,    2, 0x0a,   44 /* Public */,
      46,    0,  436,    2, 0x0a,   45 /* Public */,
      47,    0,  437,    2, 0x0a,   46 /* Public */,
      48,    0,  438,    2, 0x0a,   47 /* Public */,
      49,    0,  439,    2, 0x0a,   48 /* Public */,
      50,    0,  440,    2, 0x0a,   49 /* Public */,
      51,    0,  441,    2, 0x0a,   50 /* Public */,
      52,    0,  442,    2, 0x0a,   51 /* Public */,
      53,    0,  443,    2, 0x0a,   52 /* Public */,
      54,    0,  444,    2, 0x0a,   53 /* Public */,
      55,    0,  445,    2, 0x0a,   54 /* Public */,
      56,    0,  446,    2, 0x0a,   55 /* Public */,
      57,    0,  447,    2, 0x0a,   56 /* Public */,
      58,    0,  448,    2, 0x0a,   57 /* Public */,
      59,    0,  449,    2, 0x0a,   58 /* Public */,
      60,    0,  450,    2, 0x0a,   59 /* Public */,
      61,    2,  451,    2, 0x0a,   60 /* Public */,
      61,    1,  456,    2, 0x2a,   63 /* Public | MethodCloned */,
      64,    1,  459,    2, 0x0a,   65 /* Public */,
      67,    1,  462,    2, 0x0a,   67 /* Public */,

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
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   62,   63,
    QMetaType::Void, QMetaType::QString,   62,
    QMetaType::Void, 0x80000000 | 65,   66,
    QMetaType::Void, QMetaType::QString,   68,

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
        // method 'ButtonAutosender'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        // method 'MicroSteps'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'StepsTurn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor1Polarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor2Polarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor3Polarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor4Polarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor1Dir'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor2Dir'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor3Dir'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Sensor4Dir'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SRVRDYPolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'INPOSPolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'FAULTPolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'BrakePolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'DirPolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'EnPolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Al_CLRPolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Al_OBrakePolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Al_ORezervPolarity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'EncoderActive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'EncoderConfig'
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
        case 59: _t->sendApiRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 60: _t->sendApiRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 61: _t->onApiReplyFinished((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 62: _t->showApiError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 61:
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
        if (_id < 63)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 63;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 63)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 63;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
