#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

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
    QObject::connect(ui->pushButtonBrakeOff, &QPushButton::clicked, this, &MainWindow::BrakeOff);
    QObject::connect(ui->pushButtonBrakeOn, &QPushButton::clicked, this, &MainWindow::BrakeOn);
    QObject::connect(ui->pushButtonRezervOff, &QPushButton::clicked, this, &MainWindow::RezervOff);
    QObject::connect(ui->pushButtonRezervOn, &QPushButton::clicked, this, &MainWindow::RezervOn);

    QObject::connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onApiReplyFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    this->sendApiRequest("api/board",data);
    return ;
}

void MainWindow::ButtonSteps()
{
    qDebug() << "ButtonSteps";
    QJsonObject data;
    data["numSteps"]=ui->lineEditSteps->text().toInt();
    this->sendApiRequest("api/steps",data);
    return ;
}

void MainWindow::ButtonSpeed()
{
    qDebug() << "ButtonSpeed";
    QJsonObject data;
    data["numSpeed"]=ui->lineEditSteps->text().toInt();
    this->sendApiRequest("api/speed",data);
    return ;
}

void MainWindow::ButtonAccel()
{
    qDebug() << "ButtonAccel";
    QJsonObject data;
    data["numAccel"]=ui->lineEditSteps->text().toInt();
    this->sendApiRequest("api/accel",data);
    return ;
}

void MainWindow::ButtonDecel()
{
    qDebug() << "ButtonDecel";
    QJsonObject data;
    data["numDecel"]=ui->lineEditSteps->text().toInt();
    this->sendApiRequest("api/decel",data);
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

