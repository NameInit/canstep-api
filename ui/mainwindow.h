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
    void BrakeOff();
    void BrakeOn();
    void RezervOff();
    void RezervOn();
    void AlarmResetOn();
    void AlarmResetOff();
    void CurrentPos();
    void SaveNumBoard();
    void SaveNumGroup();
    void SaveStartPos();
    void SaveEndPos();
    void SaveMaxSpeed();
    void SaveDefaultSpeed();
    void SaveAccel();
    void SaveDecel();
    void SaveDelta();

    void sendApiRequest(const QString &endpoint, const QJsonObject &data = QJsonObject());
    void onApiReplyFinished(QNetworkReply *reply);
    void showApiError(const QString &error);
};
#endif // MAINWINDOW_H
