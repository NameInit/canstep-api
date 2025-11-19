#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
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

    QObject::connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onApiReplyFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonAutosender(){
    qDebug() << "ButtonAutosender";
    QJsonObject data;
    data["numType"]=ui->lineEditAutosenderType->text().toInt();
    data["numMs"]=ui->lineEditAutosenderMs->text().toInt();
    this->sendApiRequest("api/autosender",data);
    return ;
}

void MainWindow::ButtonConnect()
{
    qDebug() << "ButtonConnect";
    this->sendApiRequest("api/connect");
    return ;
}

void MainWindow::ButtonDebugOn()
{
    qDebug() << "ButtonDebugOn";
    this->sendApiRequest("api/debug/on");
    return ;
}

void MainWindow::ButtonBoard(){
    qDebug() << "ButtonBoard";
    QJsonObject data;
    data["numBoard"]=ui->lineEditBoard->text().toInt();
    this->sendApiRequest("api/board/set",data);
    return ;
}

void MainWindow::ButtonSteps()
{
    qDebug() << "ButtonSteps";
    QJsonObject data;
    data["numSteps"]=ui->lineEditSteps->text().toInt();
    this->sendApiRequest("api/steps/set",data);
    return ;
}

void MainWindow::ButtonSpeed()
{
    qDebug() << "ButtonSpeed";
    QJsonObject data;
    data["numSpeed"]=ui->lineEditSpeed->text().toInt();
    this->sendApiRequest("api/speed/set",data);
    return ;
}

void MainWindow::ButtonAccel()
{
    qDebug() << "ButtonAccel";
    QJsonObject data;
    data["numAccel"]=ui->lineEditAccel->text().toInt();
    this->sendApiRequest("api/accel/set",data);
    return ;
}

void MainWindow::ButtonDecel()
{
    qDebug() << "ButtonDecel";
    QJsonObject data;
    data["numDecel"]=ui->lineEditDecel->text().toInt();
    this->sendApiRequest("api/decel/set",data);
    return ;
}

void MainWindow::ButtonForward()
{
    qDebug() << "ButtonForward";
    this->sendApiRequest("api/move/forward");
    return ;
}

void MainWindow::ButtonBackward()
{
    qDebug() << "ButtonBackward";
    this->sendApiRequest("api/move/backward");
    return ;
}

void MainWindow::ButtonHomZero()
{
    qDebug() << "ButtonHomZero";
    this->sendApiRequest("api/homing/zero");
    return ;
}

void MainWindow::ButtonHomMax()
{
    qDebug() << "ButtonHomMax";
    this->sendApiRequest("api/homing/max");
    return ;
}

void MainWindow::ResetDRVRError()
{
    qDebug() << "ResetDRVRError";
    this->sendApiRequest("api/reset/driver/error");
    return ;
}

void MainWindow::Stop()
{
    qDebug() << "Stop";
    this->sendApiRequest("api/move/stop");
    return ;
}

void MainWindow::BrakeOff()
{
    qDebug() << "BrakeOff";
    this->sendApiRequest("api/brake/off");
    return ;
}

void MainWindow::BrakeOn()
{
    qDebug() << "BrakeOn";
    this->sendApiRequest("api/brake/on");
    return ;
}

void MainWindow::RezervOff()
{
    qDebug() << "RezervOff";
    this->sendApiRequest("api/rezerv/off");
    return ;
}

void MainWindow::RezervOn()
{
    qDebug() << "RezervOn";
    this->sendApiRequest("api/rezerv/on");
    return ;
}

void MainWindow::AlarmResetOn()
{
    qDebug() << "AlarmResetOn";
    this->sendApiRequest("api/alarm/reset/on");
    return ;
}

void MainWindow::AlarmResetOff()
{
    qDebug() << "AlarmResetOff";
    this->sendApiRequest("api/alarm/reset/off");
    return ;
}

void MainWindow::CurrentPos()
{
    qDebug() << "CurrentPos";
    QJsonObject data;
    data["numPos"]=ui->lineEditcurrentPos->text().toInt();
    this->sendApiRequest("api/current/pos",data);
    return ;
}

void MainWindow::ResetCANStep()
{
    qDebug() << "ResetCANStep";
    this->sendApiRequest("api/reset/canstep");
    return ;
}

void MainWindow::DriverOn()
{
    qDebug() << "DriverOn";
    this->sendApiRequest("api/driver/on");
    return ;
}

void MainWindow::DriverOff()
{
    qDebug() << "DriverOff";
    this->sendApiRequest("api/driver/off");
    return ;
}

void MainWindow::ResetLostCounters()
{
    qDebug() << "ResetLostCounters";
    this->sendApiRequest("api/lostcounters/reset");
    return ;
}

void MainWindow::MotorTorque()
{
    qDebug() << "MotorTorque";
    this->sendApiRequest("api/motor/torque");
    return ;
}

void MainWindow::MotorSpeed()
{
    qDebug() << "MotorSpeed";
    this->sendApiRequest("api/motor/speed");
    return ;
}

void MainWindow::AbsPosRot()
{
    qDebug() << "AbsPosRot";
    this->sendApiRequest("api/pos/absolute");
    return ;
}

void MainWindow::AlarmCode()
{
    qDebug() << "AlarmCode";
    this->sendApiRequest("api/alarm/code");
    return ;
}


void MainWindow::SaveNumBoard()
{
    qDebug() << "SaveNumBoard";
    QJsonObject data;
    data["numBoard"]=ui->lineEditSaveNumBoard->text().toInt();
    this->sendApiRequest("api/save/board",data);
    return ;
}

void MainWindow::SaveNumGroup()
{
    qDebug() << "SaveNumGroup";
    QJsonObject data;
    data["numGroup"]=ui->lineEditSaveNumGroup->text().toInt();
    this->sendApiRequest("api/save/group",data);
    return ;
}

void MainWindow::SaveStartPos()
{
    qDebug() << "SaveStartPos";
    QJsonObject data;
    data["numPos"]=ui->lineEditSaveStartPos->text().toInt();
    this->sendApiRequest("api/save/start/pos",data);
    return ;
}

void MainWindow::SaveEndPos()
{
    qDebug() << "SaveEndPos";
    QJsonObject data;
    data["numPos"]=ui->lineEditSaveEndPos->text().toInt();
    this->sendApiRequest("api/save/end/pos",data);
    return ;
}

void MainWindow::SaveMaxSpeed()
{
    qDebug() << "SaveMaxSpeed";
    QJsonObject data;
    data["numSpeed"]=ui->lineEditSaveMaxSpeed->text().toInt();
    this->sendApiRequest("api/save/max/speed",data);
    return ;
}

void MainWindow::SaveDefaultSpeed()
{
    qDebug() << "SaveDefaultSpeed";
    QJsonObject data;
    data["numSpeed"]=ui->lineEditSaveDefSpeed->text().toInt();
    this->sendApiRequest("api/save/default/speed",data);
    return ;
}

void MainWindow::SaveAccel()
{
    qDebug() << "SaveAccel";
    QJsonObject data;
    data["numAccel"]=ui->lineEditSaveAccel->text().toInt();
    this->sendApiRequest("api/save/accel",data);
    return ;
}

void MainWindow::SaveDecel()
{
    qDebug() << "SaveDecel";
    QJsonObject data;
    data["numDecel"]=ui->lineEditSaveDecel->text().toInt();
    this->sendApiRequest("api/save/decel",data);
    return ;
}

void MainWindow::SaveDelta()
{
    qDebug() << "SaveDelta";
    QJsonObject data;
    data["numDelta"]=ui->lineEditSaveDelta->text().toInt();
    this->sendApiRequest("api/save/delta",data);
    return ;
}

void MainWindow::MicroSteps()
{
    qDebug() << "MicroSteps";
    QJsonObject data;
    data["numSteps"]=ui->lineEditMicroSteps->text().toInt();
    this->sendApiRequest("api/steps/micro/set",data);
    return ;
}

void MainWindow::StepsTurn()
{
    qDebug() << "StepsTurn";
    QJsonObject data;
    data["numSteps"]=ui->lineEditStepsTurn->text().toInt();
    this->sendApiRequest("api/steps/turn/set",data);
    return ;
}

void MainWindow::Sensor1Polarity(){
    qDebug() << "Sensor1Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor1Polarity->currentText();
    this->sendApiRequest("api/sensor/polarity/1",data);
    return ;
}

void MainWindow::Sensor2Polarity(){
    qDebug() << "Sensor2Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor2Polarity->currentText();
    this->sendApiRequest("api/sensor/polarity/2",data);
    return ;
}

void MainWindow::Sensor3Polarity(){
    qDebug() << "Sensor3Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor3Polarity->currentText();
    this->sendApiRequest("api/sensor/polarity/3",data);
    return ;
}

void MainWindow::Sensor4Polarity(){
    qDebug() << "Sensor4Polarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor4Polarity->currentText();
    this->sendApiRequest("api/sensor/polarity/4",data);
    return ;
}

void MainWindow::Sensor1Dir(){
    qDebug() << "Sensor1Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor1Dir->currentText();
    this->sendApiRequest("api/sensor/direction/1",data);
    return ;
}

void MainWindow::Sensor2Dir(){
    qDebug() << "Sensor2Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor2Dir->currentText();
    this->sendApiRequest("api/sensor/direction/2",data);
    return ;
}

void MainWindow::Sensor3Dir(){
    qDebug() << "Sensor3Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor3Dir->currentText();
    this->sendApiRequest("api/sensor/direction/3",data);
    return ;
}

void MainWindow::Sensor4Dir(){
    qDebug() << "Sensor4Dir";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSensor4Dir->currentText();
    this->sendApiRequest("api/sensor/direction/4",data);
    return ;
}

void MainWindow::SRVRDYPolarity(){
    qDebug() << "SRVRDYPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxSRVRDYPolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/srvrdy",data);
    return ;
}

void MainWindow::INPOSPolarity(){
    qDebug() << "INPOSPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxINPOSPolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/inpos",data);
    return ;
}

void MainWindow::FAULTPolarity(){
    qDebug() << "FAULTPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxFAULTPolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/fault",data);
    return ;
}

void MainWindow::BrakePolarity(){
    qDebug() << "BrakePolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxBrakePolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/brake",data);
    return ;
}

void MainWindow::DirPolarity(){
    qDebug() << "DirPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxDirPolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/direction",data);
    return ;
}

void MainWindow::EnPolarity(){
    qDebug() << "EnPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxEnPolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/en",data);
    return ;
}

void MainWindow::Al_CLRPolarity(){
    qDebug() << "Al_CLRPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxAl_CLRPolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/al_clr",data);
    return ;
}

void MainWindow::Al_OBrakePolarity(){
    qDebug() << "Al_OBrakePolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxAl_OBrakePolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/al_obrake",data);
    return ;
}

void MainWindow::Al_ORezervPolarity(){
    qDebug() << "Al_ORezervPolarity";
    QJsonObject data;
    data["statusInverting"]=ui->comboBoxAl_ORezervPolarity->currentText();
    this->sendApiRequest("api/sensor/polarity/al_orezerv",data);
    return ;
}

void MainWindow::EncoderActive()
{
    qDebug() << "EncoderActive";
    QJsonObject data;
    data["statusActive"]=ui->comboBoxEncoderActive->currentText()=="True" ? true : false;
    this->sendApiRequest("api/sensor/encoder/active",data);
    return ;
}

void MainWindow::EncoderConfig()
{
    qDebug() << "EncoderConfig";
    QJsonObject data;
    data["numPolarity"]=ui->lineEditPolarity->text().toInt();
    data["numDelta"]=ui->lineEditDelta->text().toInt();
    data["numTurnData"]=ui->lineEditTurnData->text().toInt();
    this->sendApiRequest("api/sensor/encoder/config",data);
    return ;
}

void MainWindow::sendApiRequest(const QString &endpoint, const QJsonObject &data)
{
    qDebug() << "Sending request to:" << endpoint;

    QUrl url("http://localhost:5000/" + endpoint);
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

        // Показываем ответ в статусбаре или message box
        ui->statusbar->showMessage("Success: " + QString(response), 3000);
    } else {
        QString error = reply->errorString();
        qDebug() << "Error:" << error;
        ui->statusbar->showMessage("Error: " + error, 5000);
    }

    reply->deleteLater();
}

void MainWindow::showApiError(const QString &error)
{
    qDebug() << "showApiError";
    return ;
}

