#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>


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

public slots:
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

    void sendApiRequest(const QString &endpoint, const QJsonObject &data = QJsonObject());
    void onApiReplyFinished(QNetworkReply *reply);
    void showApiError(const QString &error);
};
#endif // MAINWINDOW_H
