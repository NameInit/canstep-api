#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QWebSocket>
#include <QTimer>
#include <QProcess>
#include <QtMqtt/QMqttClient>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QWebSocket *webSocket;
    QMqttClient *mqttClient;

private:
    void processWebSocketMessage(const QJsonObject &message);
    void sendGrpcViaConsole(const QString &methodName, const QJsonObject &data = QJsonObject());

public slots:
    void ButtonAutosender();
    void ButtonConnect();
    void ButtonDebugOn();
    void ButtonBoard();
    void ButtonSteps();
    void ButtonSpeed();
    void ButtonAccel();
    void ButtonDecel();
    void ButtonForward();
    void ButtonBackward();
    void ButtonHomZero();
    void ButtonHomMax();
    void ResetDRVRError();
    void Stop();
    void BrakeOff();
    void BrakeOn();
    void RezervOff();
    void RezervOn();
    void AlarmResetOn();
    void AlarmResetOff();
    void CurrentPos();
    void ResetCANStep();
    void DriverOn();
    void DriverOff();
    void ResetLostCounters();
    void MotorTorque();
    void MotorSpeed();
    void AbsPosRot();
    void AlarmCode();
    void SaveNumBoard();
    void SaveNumGroup();
    void SaveStartPos();
    void SaveEndPos();
    void SaveMaxSpeed();
    void SaveDefaultSpeed();
    void SaveAccel();
    void SaveDecel();
    void SaveDelta();
    void MicroSteps();
    void StepsTurn();
    void Sensor1Polarity();
    void Sensor2Polarity();
    void Sensor3Polarity();
    void Sensor4Polarity();
    void Sensor1Dir();
    void Sensor2Dir();
    void Sensor3Dir();
    void Sensor4Dir();
    void SRVRDYPolarity();
    void INPOSPolarity();
    void FAULTPolarity();
    void BrakePolarity();
    void DirPolarity();
    void EnPolarity();
    void Al_CLRPolarity();
    void Al_OBrakePolarity();
    void Al_ORezervPolarity();
    void EncoderActive();
    void EncoderConfig();
    void startFLASH();
    void startINSTALL();
    void startSAVE();

    void sendApiRequest(const QString &endpoint, const QJsonObject &data = QJsonObject());
    void onApiReplyFinished(QNetworkReply *reply);
    void showApiError(const QString &error);

    void onSocketConnected();
    void onSocketDisconnected();
    void onWebSocketTextMessageReceived(const QString &message);
    void onSocketError(QAbstractSocket::SocketError error);

    //mqtt:
    void sendMqttRequest(const QString &part, const QJsonObject &data = QJsonObject());
    void onMqttConnected();
    void onMqttMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
};
#endif // MAINWINDOW_H
