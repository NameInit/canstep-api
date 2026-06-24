#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
    , webSocket(new QWebSocket())
    , mqttClient(new QMqttClient(this))
{
    mqttClient->setHostname("127.0.0.1");
    mqttClient->setPort(1883);

    connect(mqttClient, &QMqttClient::connected, this, &MainWindow::onMqttConnected);
    connect(mqttClient, &QMqttClient::messageReceived, this, &MainWindow::onMqttMessageReceived);

    mqttClient->connectToHost();

    ui->setupUi(this);

    QObject::connect(ui->pushButtonAutosender, &QPushButton::clicked, this, &MainWindow::ButtonAutosender);
    QObject::connect(ui->pushButtonConnect, &QPushButton::clicked, this, &MainWindow::ButtonConnect);
    QObject::connect(ui->pushButtonDebugOn, &QPushButton::clicked, this, &MainWindow::ButtonDebugOn);
    QObject::connect(ui->pushButtonBoard, &QPushButton::clicked, this, &MainWindow::ButtonBoard);
    QObject::connect(ui->pushButtonSteps, &QPushButton::clicked, this, &MainWindow::ButtonSteps);
    QObject::connect(ui->pushButtonSpeed, &QPushButton::clicked, this, &MainWindow::ButtonSpeed);
    QObject::connect(ui->pushButtonAccel, &QPushButton::clicked, this, &MainWindow::ButtonAccel);
    QObject::connect(ui->pushButtonDecel, &QPushButton::clicked, this, &MainWindow::ButtonDecel);
    QObject::connect(ui->pushButtonForward, &QPushButton::clicked, this, &MainWindow::ButtonForward);
    QObject::connect(ui->pushButtonBackward, &QPushButton::clicked, this, &MainWindow::ButtonBackward);
    QObject::connect(ui->pushButtonHomingZero, &QPushButton::clicked, this, &MainWindow::ButtonHomZero);
    QObject::connect(ui->pushButtonHomingMax, &QPushButton::clicked, this, &MainWindow::ButtonHomMax);
    QObject::connect(ui->pushButtonReserDRVRErr, &QPushButton::clicked, this, &MainWindow::ResetDRVRError);
    QObject::connect(ui->pushButtonStop, &QPushButton::clicked, this, &MainWindow::Stop);
    QObject::connect(ui->pushButtonBrakeOff, &QPushButton::clicked, this, &MainWindow::BrakeOff);
    QObject::connect(ui->pushButtonBrakeOn, &QPushButton::clicked, this, &MainWindow::BrakeOn);
    QObject::connect(ui->pushButtonRezervOff, &QPushButton::clicked, this, &MainWindow::RezervOff);
    QObject::connect(ui->pushButtonRezervOn, &QPushButton::clicked, this, &MainWindow::RezervOn);
    QObject::connect(ui->pushButtonAlarmResetOn, &QPushButton::clicked, this, &MainWindow::AlarmResetOn);
    QObject::connect(ui->pushButtonAlarmResetOff, &QPushButton::clicked, this, &MainWindow::AlarmResetOff);
    QObject::connect(ui->pushButtoncurrentPos, &QPushButton::clicked, this, &MainWindow::CurrentPos);
    QObject::connect(ui->pushButtonResetCANStep, &QPushButton::clicked, this, &MainWindow::ResetCANStep);
    QObject::connect(ui->pushButtonDriverOn, &QPushButton::clicked, this, &MainWindow::DriverOn);
    QObject::connect(ui->pushButtonDriverOff, &QPushButton::clicked, this, &MainWindow::DriverOff);
    QObject::connect(ui->pushButtonResetLostCntrs, &QPushButton::clicked, this, &MainWindow::ResetLostCounters);
    QObject::connect(ui->pushButtonMotorTorque, &QPushButton::clicked, this, &MainWindow::MotorTorque);
    QObject::connect(ui->pushButtonMotorSpeed, &QPushButton::clicked, this, &MainWindow::MotorSpeed);
    QObject::connect(ui->pushButtonAbsPosRot, &QPushButton::clicked, this, &MainWindow::AbsPosRot);
    QObject::connect(ui->pushButtonAlarmCode, &QPushButton::clicked, this, &MainWindow::AlarmCode);
    QObject::connect(ui->pushButtonSaveNumBoard, &QPushButton::clicked, this, &MainWindow::SaveNumBoard);
    QObject::connect(ui->pushButtonSaveNumGroup, &QPushButton::clicked, this, &MainWindow::SaveNumGroup);
    QObject::connect(ui->pushButtonSaveStartPos, &QPushButton::clicked, this, &MainWindow::SaveStartPos);
    QObject::connect(ui->pushButtonSaveEndPos, &QPushButton::clicked, this, &MainWindow::SaveEndPos);
    QObject::connect(ui->pushButtonSaveMaxSpeed, &QPushButton::clicked, this, &MainWindow::SaveMaxSpeed);
    QObject::connect(ui->pushButtonSaveDefSpeed, &QPushButton::clicked, this, &MainWindow::SaveDefaultSpeed);
    QObject::connect(ui->pushButtonSaveAccel, &QPushButton::clicked, this, &MainWindow::SaveAccel);
    QObject::connect(ui->pushButtonSaveDecel, &QPushButton::clicked, this, &MainWindow::SaveDecel);
    QObject::connect(ui->pushButtonSaveDelta, &QPushButton::clicked, this, &MainWindow::SaveDelta);
    QObject::connect(ui->pushButtonMicroSteps, &QPushButton::clicked, this, &MainWindow::MicroSteps);
    QObject::connect(ui->pushButtonStepsTurn, &QPushButton::clicked, this, &MainWindow::StepsTurn);
    QObject::connect(ui->pushButtonSensor1Polarity, &QPushButton::clicked, this, &MainWindow::Sensor1Polarity);
    QObject::connect(ui->pushButtonSensor2Polarity, &QPushButton::clicked, this, &MainWindow::Sensor2Polarity);
    QObject::connect(ui->pushButtonSensor3Polarity, &QPushButton::clicked, this, &MainWindow::Sensor3Polarity);
    QObject::connect(ui->pushButtonSensor4Polarity, &QPushButton::clicked, this, &MainWindow::Sensor4Polarity);
    QObject::connect(ui->pushButtonSensor1Dir, &QPushButton::clicked, this, &MainWindow::Sensor1Dir);
    QObject::connect(ui->pushButtonSensor2Dir, &QPushButton::clicked, this, &MainWindow::Sensor2Dir);
    QObject::connect(ui->pushButtonSensor3Dir, &QPushButton::clicked, this, &MainWindow::Sensor3Dir);
    QObject::connect(ui->pushButtonSensor4Dir, &QPushButton::clicked, this, &MainWindow::Sensor4Dir);
    QObject::connect(ui->pushButtonSRVRDYPolarity, &QPushButton::clicked, this, &MainWindow::SRVRDYPolarity);
    QObject::connect(ui->pushButtonINPOSPolarity, &QPushButton::clicked, this, &MainWindow::INPOSPolarity);
    QObject::connect(ui->pushButtonFAULTPolarity, &QPushButton::clicked, this, &MainWindow::FAULTPolarity);
    QObject::connect(ui->pushButtonBrakePolarity, &QPushButton::clicked, this, &MainWindow::BrakePolarity);
    QObject::connect(ui->pushButtonDirPolarity, &QPushButton::clicked, this, &MainWindow::DirPolarity);
    QObject::connect(ui->pushButtonEnPolarity, &QPushButton::clicked, this, &MainWindow::EnPolarity);
    QObject::connect(ui->pushButtonAl_CLRPolarity, &QPushButton::clicked, this, &MainWindow::Al_CLRPolarity);
    QObject::connect(ui->pushButtonAl_OBrakePolarity, &QPushButton::clicked, this, &MainWindow::Al_OBrakePolarity);
    QObject::connect(ui->pushButtonAl_ORezervPolarity, &QPushButton::clicked, this, &MainWindow::Al_ORezervPolarity);
    QObject::connect(ui->pushButtonEncoderActive, &QPushButton::clicked, this, &MainWindow::EncoderActive);
    QObject::connect(ui->pushButtonEncoderConfig, &QPushButton::clicked, this, &MainWindow::EncoderConfig);
    QObject::connect(ui->pushButtonFLASH, &QPushButton::clicked, this, &MainWindow::startFLASH);
    QObject::connect(ui->pushButtonINSTALL, &QPushButton::clicked, this, &MainWindow::startINSTALL);
    QObject::connect(ui->pushButtonSAVE, &QPushButton::clicked, this, &MainWindow::startSAVE);
    QObject::connect(ui->pushButtonLoadMech, &QPushButton::clicked, this, &MainWindow::loadMech);
    QObject::connect(ui->pushButtonExSce, &QPushButton::clicked, this, &MainWindow::executeSce);

    QObject::connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onApiReplyFinished);

    QObject::connect(webSocket, &QWebSocket::connected, this, &MainWindow::onSocketConnected);
    QObject::connect(webSocket, &QWebSocket::disconnected, this, &MainWindow::onSocketDisconnected);
    QObject::connect(webSocket, &QWebSocket::textMessageReceived, this, &MainWindow::onWebSocketTextMessageReceived);
    QObject::connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    webSocket->open(QUrl("ws://localhost:8081/ws"));
}

MainWindow::~MainWindow()
{
    webSocket->close();
    delete ui;
}

void MainWindow::ButtonAutosender(){
    qDebug() << "ButtonAutosender";
    QJsonObject data;
    data["type"]=ui->lineEditAutosenderType->text().toInt();
    data["ms"]=ui->lineEditAutosenderMs->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/autosender",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Autosender",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Autosender",data);
    }
    return ;
}

void MainWindow::ButtonConnect()
{
    qDebug() << "ButtonConnect";
    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/connect");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Connect");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Connect");
    }
    return ;
}

void MainWindow::ButtonDebugOn()
{
    qDebug() << "ButtonDebugOn";
    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/debug/on");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("DebugOn");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("DebugOn");
    }
    return ;
}

void MainWindow::ButtonBoard(){
    qDebug() << "ButtonBoard";
    QJsonObject data;
    data["numBoard"]=ui->lineEditBoard->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/board/set", data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Board", data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Board", data);
    }
    return ;
}

void MainWindow::ButtonSteps()
{
    qDebug() << "ButtonSteps";
    QJsonObject data;
    data["numSteps"]=ui->lineEditSteps->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/steps/set",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Steps", data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Steps", data);
    }
    return ;
}

void MainWindow::ButtonSpeed()
{
    qDebug() << "ButtonSpeed";
    QJsonObject data;
    data["numSpeed"]=ui->lineEditSpeed->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/speed/set",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Speed", data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Speed", data);
    }
    return ;
}

void MainWindow::ButtonAccel()
{
    qDebug() << "ButtonAccel";
    QJsonObject data;
    data["numAccel"]=ui->lineEditAccel->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/accel/set",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Accel", data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Accel", data);
    }
    return ;
}

void MainWindow::ButtonDecel()
{
    qDebug() << "ButtonDecel";
    QJsonObject data;
    data["numDecel"]=ui->lineEditDecel->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/decel/set",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Decel", data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Decel", data);
    }
    return ;
}

void MainWindow::ButtonForward()
{
    qDebug() << "ButtonForward";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/move/forward");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Forward");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Forward");
    }
    return ;
}

void MainWindow::ButtonBackward()
{
    qDebug() << "ButtonBackward";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/move/backward");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Backward");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Backward");
    }
    return ;
}

void MainWindow::ButtonHomZero()
{
    qDebug() << "ButtonHomZero";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/homing/zero");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("HomingZero");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("HomingZero");
    }
    return ;
}

void MainWindow::ButtonHomMax()
{
    qDebug() << "ButtonHomMax";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/homing/max");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("HomingMax");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("HomingMax");
    }
    return ;
}

void MainWindow::ResetDRVRError()
{
    qDebug() << "ResetDRVRError";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/reset/driver/error");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("ResetDRVError");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("ResetDRVError");
    }
    return ;
}

void MainWindow::Stop()
{
    qDebug() << "Stop";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/move/stop");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Stop");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Stop");
    }
    return ;
}

void MainWindow::BrakeOff()
{
    qDebug() << "BrakeOff";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/brake/off");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("BrakeOff");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("BrakeOff");
    }
    return ;
}

void MainWindow::BrakeOn()
{
    qDebug() << "BrakeOn";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/brake/on");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("BrakeOn");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("BrakeOn");
    }
    return ;
}

void MainWindow::RezervOff()
{
    qDebug() << "RezervOff";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/rezerv/off");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("RezervOff");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("RezervOff");
    }
    return ;
}

void MainWindow::RezervOn()
{
    qDebug() << "RezervOn";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/rezerv/on");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("RezervOn");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("RezervOn");
    }
    return ;
}

void MainWindow::AlarmResetOn()
{
    qDebug() << "AlarmResetOn";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/alarm/reset/on");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("AlarmResetOn");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("AlarmResetOn");
    }
    return ;
}

void MainWindow::AlarmResetOff()
{
    qDebug() << "AlarmResetOff";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/alarm/reset/off");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("AlarmResetOff");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("AlarmResetOff");
    }
    return ;
}

void MainWindow::CurrentPos()
{
    qDebug() << "CurrentPos";
    QJsonObject data;
    data["numPos"]=ui->lineEditcurrentPos->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/current/pos",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("CurrentPos",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("CurrentPos");
    }
    return ;
}

void MainWindow::ResetCANStep()
{
    qDebug() << "ResetCANStep";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/reset/canstep");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("ResetCANStep");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("ResetCANStep");
    }
    return ;
}

void MainWindow::DriverOn()
{
    qDebug() << "DriverOn";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/driver/on");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("DriverOn");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("DriverOn");
    }
    return ;
}

void MainWindow::DriverOff()
{
    qDebug() << "DriverOff";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/driver/off");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("DriverOff");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("DriverOff");
    }
    return ;
}

void MainWindow::ResetLostCounters()
{
    qDebug() << "ResetLostCounters";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/lostcounters/reset");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("ResetLostCounters");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("ResetLostCounters");
    }
    return ;
}

void MainWindow::MotorTorque()
{
    qDebug() << "MotorTorque";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/motor/torque");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("MotorTorque");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("MotorTorque");
    }
    return ;
}

void MainWindow::MotorSpeed()
{
    qDebug() << "MotorSpeed";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/motor/speed");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("MotorSpeed");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("MotorSpeed");
    }
    return ;
}

void MainWindow::AbsPosRot()
{
    qDebug() << "AbsPosRot";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/pos/absolute");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("AbsolutePositionRotorUint");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("AbsolutePositionRotorUint");
    }
    return ;
}

void MainWindow::AlarmCode()
{
    qDebug() << "AlarmCode";

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/alarm/code");
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("AlarmCode");
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("AlarmCode");
    }
    return ;
}


void MainWindow::SaveNumBoard()
{
    qDebug() << "SaveNumBoard";
    QJsonObject data;
    data["numBoard"]=ui->lineEditSaveNumBoard->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/board",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveNumBoard",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveNumBoard",data);
    }
    return ;
}

void MainWindow::SaveNumGroup()
{
    qDebug() << "SaveNumGroup";
    QJsonObject data;
    data["numGroup"]=ui->lineEditSaveNumGroup->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/group",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveNumGroup",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveNumGroup",data);
    }
    return ;
}

void MainWindow::SaveStartPos()
{
    qDebug() << "SaveStartPos";
    QJsonObject data;
    data["numPos"]=ui->lineEditSaveStartPos->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/start/pos",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveStartPos",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveStartPos",data);
    }
    return ;
}

void MainWindow::SaveEndPos()
{
    qDebug() << "SaveEndPos";
    QJsonObject data;
    data["numPos"]=ui->lineEditSaveEndPos->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/end/pos",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveEndPos",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveEndPos",data);
    }
    return ;
}

void MainWindow::SaveMaxSpeed()
{
    qDebug() << "SaveMaxSpeed";
    QJsonObject data;
    data["numSpeed"]=ui->lineEditSaveMaxSpeed->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/max/speed",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveMaxSpeed",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveMaxSpeed",data);
    }
    return ;
}

void MainWindow::SaveDefaultSpeed()
{
    qDebug() << "SaveDefaultSpeed";
    QJsonObject data;
    data["numSpeed"]=ui->lineEditSaveDefSpeed->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/default/speed",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveDefaultSpeed",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveDefaultSpeed",data);
    }
    return ;
}

void MainWindow::SaveAccel()
{
    qDebug() << "SaveAccel";
    QJsonObject data;
    data["numAccel"]=ui->lineEditSaveAccel->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/accel",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveAccel",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveAccel",data);
    }
    return ;
}

void MainWindow::SaveDecel()
{
    qDebug() << "SaveDecel";
    QJsonObject data;
    data["numDecel"]=ui->lineEditSaveDecel->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/decel",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveDecel",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveDecel",data);
    }
    return ;
}

void MainWindow::SaveDelta()
{
    qDebug() << "SaveDelta";
    QJsonObject data;
    data["numDelta"]=ui->lineEditSaveDelta->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/save/delta",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SaveDelta",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SaveDelta",data);
    }
    return ;
}

void MainWindow::MicroSteps()
{
    qDebug() << "MicroSteps";
    QJsonObject data;
    data["numSteps"]=ui->lineEditMicroSteps->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/steps/micro/set",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("MicroSteps",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("MicroSteps",data);
    }
    return ;
}

void MainWindow::StepsTurn()
{
    qDebug() << "StepsTurn";
    QJsonObject data;
    data["numSteps"]=ui->lineEditStepsTurn->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/steps/turn/set",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("TurnSteps",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("TurnSteps",data);
    }
    return ;
}

void MainWindow::Sensor1Polarity(){
    qDebug() << "Sensor1Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor1Polarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/1",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor1Polarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor1Polarity",data);
    }
    return ;
}

void MainWindow::Sensor2Polarity(){
    qDebug() << "Sensor2Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor2Polarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/2",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor2Polarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor2Polarity",data);
    }
    return ;
}

void MainWindow::Sensor3Polarity(){
    qDebug() << "Sensor3Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor3Polarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/3",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor3Polarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor3Polarity",data);
    }
    return ;
}

void MainWindow::Sensor4Polarity(){
    qDebug() << "Sensor4Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor4Polarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/4",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor4Polarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor4Polarity",data);
    }
    return ;
}

void MainWindow::Sensor1Dir(){
    qDebug() << "Sensor1Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor1Dir->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/direction/1",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor1Dir",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor1Dir",data);
    }
    return ;
}

void MainWindow::Sensor2Dir(){
    qDebug() << "Sensor2Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor2Dir->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/direction/2",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor2Dir",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor2Dir",data);
    }
    return ;
}

void MainWindow::Sensor3Dir(){
    qDebug() << "Sensor3Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor3Dir->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/direction/3",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor3Dir",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor3Dir",data);
    }
    return ;
}

void MainWindow::Sensor4Dir(){
    qDebug() << "Sensor4Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor4Dir->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/direction/4",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Sensor4Dir",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Sensor4Dir",data);
    }
    return ;
}

void MainWindow::SRVRDYPolarity(){
    qDebug() << "SRVRDYPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSRVRDYPolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/srvrdy",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("SRVRDYPolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("SRVRDYPolarity",data);
    }
    return ;
}

void MainWindow::INPOSPolarity(){
    qDebug() << "INPOSPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxINPOSPolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/inpos",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("INPOSPolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("INPOSPolarity",data);
    }
    return ;
}

void MainWindow::FAULTPolarity(){
    qDebug() << "FAULTPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxFAULTPolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/fault",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("FAULTPolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("FAULTPolarity",data);
    }
    return ;
}

void MainWindow::BrakePolarity(){
    qDebug() << "BrakePolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxBrakePolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/brake",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("BrakePolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("BrakePolarity",data);
    }
    return ;
}

void MainWindow::DirPolarity(){
    qDebug() << "DirPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxDirPolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/direction",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("DirPolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("DirPolarity",data);
    }
    return ;
}

void MainWindow::EnPolarity(){
    qDebug() << "EnPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxEnPolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/en",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("EnPolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("EnPolarity",data);
    }
    return ;
}

void MainWindow::Al_CLRPolarity(){
    qDebug() << "Al_CLRPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxAl_CLRPolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/al_clr",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Al_CLRPolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Al_CLRPolarity",data);
    }
    return ;
}

void MainWindow::Al_OBrakePolarity(){
    qDebug() << "Al_OBrakePolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxAl_OBrakePolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/al_obrake",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Al_OBrakePolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Al_OBrakePolarity",data);
    }
    return ;
}

void MainWindow::Al_ORezervPolarity(){
    qDebug() << "Al_ORezervPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxAl_ORezervPolarity->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/polarity/al_orezerv",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("Al_ORezervPolarity",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("Al_ORezervPolarity",data);
    }
    return ;
}

void MainWindow::EncoderActive()
{
    qDebug() << "EncoderActive";
    QJsonObject data;
    data["statusActive"]=ui->comboBoxEncoderActive->currentText()=="True" ? true : false;

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/encoder/active",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("EncoderActive",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("EncoderActive",data);
    }
    return ;
}

void MainWindow::EncoderConfig()
{
    qDebug() << "EncoderConfig";
    QJsonObject data;
    data["numPolarity"]=ui->lineEditPolarity->text().toInt();
    data["numDelta"]=ui->lineEditDelta->text().toInt();
    data["numTurnData"]=ui->lineEditTurnData->text().toInt();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/sensor/encoder/config",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("EncoderConfig",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("EncoderConfig",data);
    }
    return ;
}

void MainWindow::startFLASH()
{
    qDebug() << "EncoderConfig";
    QJsonObject data;
    data["filename"]=ui->lineEditFilename->text();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/flash/run",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("FlashBoot",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("FlashBoot",data);
    }
    return ;
}

void MainWindow::startINSTALL(){
    qDebug() << "startINSTALL";
    QJsonObject data;
    data["type"]=ui->comboBoxFLASH->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/flash/type/set",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("FlashTypeBootSet",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("FlashTypeBootSet",data);
    }
    return ;
}

void MainWindow::startSAVE(){
    qDebug() << "startSAVE";
    QJsonObject data;
    data["type"]=ui->comboBoxFLASH->currentText();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("api/flash/type/save",data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("FlashTypeBootSave",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("FlashTypeBootSet",data);
    }
    return ;
}

void MainWindow::loadMech(){
    qDebug() << "loadMech";
    QJsonObject data;
    data["filename"] = ui->lineEditLoadMech->text();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("/api/mech/load", data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("LoadMech",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("LoadMech",data);
    }
    return ;
}

void MainWindow::executeSce(){
    qDebug() << "executeSce";
    QJsonObject data;
    data["filename"] = ui->lineEditExSce->text();

    if(ui->comboBoxApiType->currentText() == "REST"){
        this->sendApiRequest("/api/sce/execute", data);
    }
    else if(ui->comboBoxApiType->currentText() == "GRPC"){
        this->sendGrpcViaConsole("ExecuteSce",data);
    }
    else if(ui->comboBoxApiType->currentText() == "MQTT"){
        this->sendMqttRequest("ExecuteSce",data);
    }
    return ;
}

void MainWindow::sendApiRequest(const QString &endpoint, const QJsonObject &data)
{
    qDebug() << "Sending request to:" << endpoint;

    QUrl url("http://localhost:8080/" + endpoint);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if(data.empty()){
        // GET request
        networkManager->get(request);
    }
    else{
        // POST request
        QJsonDocument doc(data);
        QByteArray jsonData = doc.toJson();
        networkManager->post(request, jsonData);
    }
}

void MainWindow::onApiReplyFinished(QNetworkReply *reply)
{
    qDebug() << "Response received";

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "Response:" << response;

        ui->statusbar->showMessage("Success: " + QString(response), 3000);
    } else {
        QString error = reply->errorString();
        qDebug() << "Error:" << error;
        ui->statusbar->showMessage("Error: " + error, 8080);
    }

    reply->deleteLater();
}

void MainWindow::showApiError(const QString &error)
{
    qDebug() << "showApiError";
    qDebug() << error;
    return ;
}

void MainWindow::onSocketConnected()
{
    qDebug() << "WebSocket connected";
    ui->statusbar->showMessage("WebSocket: Connected", 3000);

    // Можно отправить приветственное сообщение или подписку
    // webSocket->sendTextMessage("{\"type\":\"subscribe\",\"data\":\"status\"}");
}

void MainWindow::onSocketDisconnected()
{
    qDebug() << "WebSocket disconnected";
    ui->statusbar->showMessage("WebSocket: Disconnected", 3000);

    // Автопереподключение через 3 секунды
    QTimer::singleShot(3000, this, [this]() {
        qDebug() << "Attempting to reconnect WebSocket...";
        webSocket->open(QUrl("ws://localhost:8080/ws"));
    });
}

void MainWindow::onWebSocketTextMessageReceived(const QString &message)
{
    // qDebug() << "WebSocket message received:" << message;

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isNull() && doc.isObject()) {
        QJsonObject json = doc.object();
        processWebSocketMessage(json);
    } else {
        qDebug() << "Invalid JSON received:" << message;
    }
}

void MainWindow::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << "WebSocket error:" << error << webSocket->errorString();
    ui->statusbar->showMessage("WebSocket Error: " + webSocket->errorString(), 5000);
}

void MainWindow::sendMqttRequest(const QString &part, const QJsonObject &data)
{
    if (mqttClient->state() != QMqttClient::Connected) {
        qDebug() << "Not connected!";
        return;
    }
    QJsonDocument doc(data);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);
    QString topic = "cancontroller/command/"+part;
    mqttClient->publish(QMqttTopicName(topic), payload);
    return ;
}

void MainWindow::onMqttConnected()
{
    qDebug() << "Connected to Broker!";

    mqttClient->subscribe(QMqttTopicFilter("cancontroller/response"));
    return ;
}

void MainWindow::onMqttMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << "MQTT received: " << topic.name() << ":" << message;
    return ;
}

void MainWindow::processWebSocketMessage(const QJsonObject &message)
{
    // qDebug()<<"message = " << message;

    if (message.contains("server_time") && message["server_time"].isString()) {
        QString serverTime = message["server_time"].toString();
        ui->labelServerTimeInfo->setText(serverTime);
    }

    if (message.contains("timestamp") && message["timestamp"].isString()) {
        QString timestamp = message["timestamp"].toString();
        ui->labelTimestampInfo->setText(timestamp);
    }

    if (message.contains("isConnected") && message["isConnected"].isString()) {
        QString isConnected = message["isConnected"].toString();
        ui->labelIsConnectedInfo->setText(isConnected);
    }

    if (message.contains("numBoard") && message["numBoard"].isString()) {
        QString numBoard = message["numBoard"].toString();
        ui->labelNumBoardInfo->setText(numBoard);
    }

    if (message.contains("numSteps") && message["numSteps"].isString()) {
        QString numSteps = message["numSteps"].toString();
        ui->labelNumStepsInfo->setText(numSteps);
    }

    if (message.contains("numSpeed") && message["numSpeed"].isString()) {
        QString numSpeed = message["numSpeed"].toString();
        ui->labelNumSpeedInfo->setText(numSpeed);
    }

    if (message.contains("numAccel") && message["numAccel"].isString()) {
        QString numAccel = message["numAccel"].toString();
        ui->labelNumAccelInfo->setText(numAccel);
    }

    if (message.contains("numDecel") && message["numDecel"].isString()) {
        QString numDecel = message["numDecel"].toString();
        ui->labelNumDecelInfo->setText(numDecel);
    }

    if (message.contains("numBoard") && message["numBoard"].isString()) {
        QString numBoard = message["numBoard"].toString();
        ui->labelNumBoardInfo->setText(numBoard);
    }

    if (message.contains("currentPos") && message["currentPos"].isString()) {
        QString currentPos = message["currentPos"].toString();
        ui->labelCurrentPosInfo->setText(currentPos);
    }

    if (message.contains("startPos") && message["startPos"].isString()) {
        QString startPos = message["startPos"].toString();
        ui->labelStartPosInfo->setText(startPos);
    }

    if (message.contains("endPos") && message["endPos"].isString()) {
        QString endPos = message["endPos"].toString();
        ui->labelEndPosInfo->setText(endPos);
    }
}

void MainWindow::sendGrpcViaConsole(const QString &methodName, const QJsonObject &data)
{
    qDebug() << "Executing grpcurl for method:" << methodName;

    QProcess *process = new QProcess(this);

    // Команда: grpcurl
    QString program = "grpcurl";

    QStringList arguments;
    arguments << "-plaintext";

    // Данные: -d '{"key": val}'
    QJsonDocument doc(data);
    QString jsonString = QString(doc.toJson(QJsonDocument::Compact));

    // Если данных нет, grpcurl требует пустой объект '{}'
    if (jsonString.isEmpty() || jsonString == "null") {
        jsonString = "{}";
    }

    arguments << "-d" << jsonString;

    // Адрес
    arguments << "localhost:50051";

    // Метод (Сервис/Метод)
    arguments << "cancontroller.CanControllerService/" + methodName;

    // Обработка результата
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, process, methodName](int exitCode, QProcess::ExitStatus exitStatus) {

                if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                    QByteArray output = process->readAllStandardOutput();
                    qDebug() << "gRPC Response:" << output;

                    // grpcurl обычно возвращает JSON, можно его распарсить
                    QJsonDocument respDoc = QJsonDocument::fromJson(output);
                    QJsonObject respJson = respDoc.object();

                    if (respJson["success"].toBool()) {
                        ui->statusbar->showMessage("gRPC OK: " + respJson["message"].toString(), 3000);
                    } else {
                        // Если grpcurl вернул ошибку сервера
                        ui->statusbar->showMessage("gRPC Server Error: " + QString(output), 5000);
                    }

                } else {
                    QByteArray error = process->readAllStandardError();
                    qDebug() << "grpcurl execution failed:" << error;
                    ui->statusbar->showMessage("grpcurl Error: " + QString(error), 5000);
                }

                process->deleteLater();
            });

    process->start(program, arguments);
    qDebug()<<arguments;
}
