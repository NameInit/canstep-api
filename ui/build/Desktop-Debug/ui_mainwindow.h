/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonDecel;
    QLineEdit *lineEditAccel;
    QPushButton *pushButtonReserDRVRErr;
    QPushButton *pushButtonForward;
    QPushButton *pushButtonRezervOn;
    QPushButton *pushButtonSaveNumBoard;
    QPushButton *pushButtonSaveStartPos;
    QPushButton *pushButtonRezervOff;
    QPushButton *pushButtonBrakeOff;
    QPushButton *pushButtonBoard;
    QLineEdit *lineEditSaveNumBoard;
    QLineEdit *lineEditSaveStartPos;
    QPushButton *pushButtonSaveMaxSpeed;
    QLineEdit *lineEditSteps;
    QLineEdit *lineEditSaveEndPos;
    QPushButton *pushButtoncurrentPos;
    QLineEdit *lineEditcurrentPos;
    QPushButton *pushButtonHomingZero;
    QLineEdit *lineEditBoard;
    QPushButton *pushButtonDebugOn;
    QPushButton *pushButtonBackward;
    QPushButton *pushButtonBrakeOn;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonAccel;
    QPushButton *pushButtonSaveNumGroup;
    QLineEdit *lineEditDecel;
    QPushButton *pushButtonAlarmResetOn;
    QPushButton *pushButtonAlarmResetOff;
    QPushButton *pushButtonHomingMax;
    QPushButton *pushButtonSaveEndPos;
    QPushButton *pushButtonSpeed;
    QLineEdit *lineEditSaveNumGroup;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditSpeed;
    QPushButton *pushButtonSteps;
    QLineEdit *lineEditSaveMaxSpeed;
    QPushButton *pushButtonSaveDefSpeed;
    QLineEdit *lineEditSaveDefSpeed;
    QPushButton *pushButtonSaveAccel;
    QLineEdit *lineEditSaveAccel;
    QPushButton *pushButtonSaveDecel;
    QLineEdit *lineEditSaveDecel;
    QPushButton *pushButtonSaveDelta;
    QLineEdit *lineEditSaveDelta;
    QPushButton *pushButtonSensor1Polarity;
    QLineEdit *lineEditSensor1Polarity;
    QPushButton *pushButtonSensor2Polarity;
    QLineEdit *lineEditSensor2Polarity;
    QPushButton *pushButtonSensor3Polarity;
    QLineEdit *lineEditSensor3Polarity;
    QPushButton *pushButtonSensor4Polarity;
    QLineEdit *lineEditSensor4Polarity;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 497, 558));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonDecel = new QPushButton(layoutWidget);
        pushButtonDecel->setObjectName("pushButtonDecel");

        gridLayout->addWidget(pushButtonDecel, 5, 0, 1, 1);

        lineEditAccel = new QLineEdit(layoutWidget);
        lineEditAccel->setObjectName("lineEditAccel");

        gridLayout->addWidget(lineEditAccel, 4, 1, 1, 1);

        pushButtonReserDRVRErr = new QPushButton(layoutWidget);
        pushButtonReserDRVRErr->setObjectName("pushButtonReserDRVRErr");

        gridLayout->addWidget(pushButtonReserDRVRErr, 8, 0, 1, 1);

        pushButtonForward = new QPushButton(layoutWidget);
        pushButtonForward->setObjectName("pushButtonForward");

        gridLayout->addWidget(pushButtonForward, 6, 0, 1, 1);

        pushButtonRezervOn = new QPushButton(layoutWidget);
        pushButtonRezervOn->setObjectName("pushButtonRezervOn");

        gridLayout->addWidget(pushButtonRezervOn, 10, 1, 1, 1);

        pushButtonSaveNumBoard = new QPushButton(layoutWidget);
        pushButtonSaveNumBoard->setObjectName("pushButtonSaveNumBoard");

        gridLayout->addWidget(pushButtonSaveNumBoard, 13, 0, 1, 1);

        pushButtonSaveStartPos = new QPushButton(layoutWidget);
        pushButtonSaveStartPos->setObjectName("pushButtonSaveStartPos");

        gridLayout->addWidget(pushButtonSaveStartPos, 15, 0, 1, 1);

        pushButtonRezervOff = new QPushButton(layoutWidget);
        pushButtonRezervOff->setObjectName("pushButtonRezervOff");

        gridLayout->addWidget(pushButtonRezervOff, 10, 0, 1, 1);

        pushButtonBrakeOff = new QPushButton(layoutWidget);
        pushButtonBrakeOff->setObjectName("pushButtonBrakeOff");

        gridLayout->addWidget(pushButtonBrakeOff, 9, 0, 1, 1);

        pushButtonBoard = new QPushButton(layoutWidget);
        pushButtonBoard->setObjectName("pushButtonBoard");

        gridLayout->addWidget(pushButtonBoard, 1, 0, 1, 1);

        lineEditSaveNumBoard = new QLineEdit(layoutWidget);
        lineEditSaveNumBoard->setObjectName("lineEditSaveNumBoard");

        gridLayout->addWidget(lineEditSaveNumBoard, 13, 1, 1, 1);

        lineEditSaveStartPos = new QLineEdit(layoutWidget);
        lineEditSaveStartPos->setObjectName("lineEditSaveStartPos");

        gridLayout->addWidget(lineEditSaveStartPos, 15, 1, 1, 1);

        pushButtonSaveMaxSpeed = new QPushButton(layoutWidget);
        pushButtonSaveMaxSpeed->setObjectName("pushButtonSaveMaxSpeed");

        gridLayout->addWidget(pushButtonSaveMaxSpeed, 0, 3, 1, 1);

        lineEditSteps = new QLineEdit(layoutWidget);
        lineEditSteps->setObjectName("lineEditSteps");

        gridLayout->addWidget(lineEditSteps, 2, 1, 1, 1);

        lineEditSaveEndPos = new QLineEdit(layoutWidget);
        lineEditSaveEndPos->setObjectName("lineEditSaveEndPos");

        gridLayout->addWidget(lineEditSaveEndPos, 16, 1, 1, 1);

        pushButtoncurrentPos = new QPushButton(layoutWidget);
        pushButtoncurrentPos->setObjectName("pushButtoncurrentPos");

        gridLayout->addWidget(pushButtoncurrentPos, 12, 0, 1, 1);

        lineEditcurrentPos = new QLineEdit(layoutWidget);
        lineEditcurrentPos->setObjectName("lineEditcurrentPos");

        gridLayout->addWidget(lineEditcurrentPos, 12, 1, 1, 1);

        pushButtonHomingZero = new QPushButton(layoutWidget);
        pushButtonHomingZero->setObjectName("pushButtonHomingZero");

        gridLayout->addWidget(pushButtonHomingZero, 7, 0, 1, 1);

        lineEditBoard = new QLineEdit(layoutWidget);
        lineEditBoard->setObjectName("lineEditBoard");

        gridLayout->addWidget(lineEditBoard, 1, 1, 1, 1);

        pushButtonDebugOn = new QPushButton(layoutWidget);
        pushButtonDebugOn->setObjectName("pushButtonDebugOn");

        gridLayout->addWidget(pushButtonDebugOn, 0, 1, 1, 1);

        pushButtonBackward = new QPushButton(layoutWidget);
        pushButtonBackward->setObjectName("pushButtonBackward");

        gridLayout->addWidget(pushButtonBackward, 6, 1, 1, 1);

        pushButtonBrakeOn = new QPushButton(layoutWidget);
        pushButtonBrakeOn->setObjectName("pushButtonBrakeOn");

        gridLayout->addWidget(pushButtonBrakeOn, 9, 1, 1, 1);

        pushButtonConnect = new QPushButton(layoutWidget);
        pushButtonConnect->setObjectName("pushButtonConnect");

        gridLayout->addWidget(pushButtonConnect, 0, 0, 1, 1);

        pushButtonAccel = new QPushButton(layoutWidget);
        pushButtonAccel->setObjectName("pushButtonAccel");

        gridLayout->addWidget(pushButtonAccel, 4, 0, 1, 1);

        pushButtonSaveNumGroup = new QPushButton(layoutWidget);
        pushButtonSaveNumGroup->setObjectName("pushButtonSaveNumGroup");

        gridLayout->addWidget(pushButtonSaveNumGroup, 14, 0, 1, 1);

        lineEditDecel = new QLineEdit(layoutWidget);
        lineEditDecel->setObjectName("lineEditDecel");

        gridLayout->addWidget(lineEditDecel, 5, 1, 1, 1);

        pushButtonAlarmResetOn = new QPushButton(layoutWidget);
        pushButtonAlarmResetOn->setObjectName("pushButtonAlarmResetOn");

        gridLayout->addWidget(pushButtonAlarmResetOn, 11, 0, 1, 1);

        pushButtonAlarmResetOff = new QPushButton(layoutWidget);
        pushButtonAlarmResetOff->setObjectName("pushButtonAlarmResetOff");

        gridLayout->addWidget(pushButtonAlarmResetOff, 11, 1, 1, 1);

        pushButtonHomingMax = new QPushButton(layoutWidget);
        pushButtonHomingMax->setObjectName("pushButtonHomingMax");

        gridLayout->addWidget(pushButtonHomingMax, 7, 1, 1, 1);

        pushButtonSaveEndPos = new QPushButton(layoutWidget);
        pushButtonSaveEndPos->setObjectName("pushButtonSaveEndPos");

        gridLayout->addWidget(pushButtonSaveEndPos, 16, 0, 1, 1);

        pushButtonSpeed = new QPushButton(layoutWidget);
        pushButtonSpeed->setObjectName("pushButtonSpeed");

        gridLayout->addWidget(pushButtonSpeed, 3, 0, 1, 1);

        lineEditSaveNumGroup = new QLineEdit(layoutWidget);
        lineEditSaveNumGroup->setObjectName("lineEditSaveNumGroup");

        gridLayout->addWidget(lineEditSaveNumGroup, 14, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        lineEditSpeed = new QLineEdit(layoutWidget);
        lineEditSpeed->setObjectName("lineEditSpeed");

        gridLayout->addWidget(lineEditSpeed, 3, 1, 1, 1);

        pushButtonSteps = new QPushButton(layoutWidget);
        pushButtonSteps->setObjectName("pushButtonSteps");

        gridLayout->addWidget(pushButtonSteps, 2, 0, 1, 1);

        lineEditSaveMaxSpeed = new QLineEdit(layoutWidget);
        lineEditSaveMaxSpeed->setObjectName("lineEditSaveMaxSpeed");

        gridLayout->addWidget(lineEditSaveMaxSpeed, 0, 4, 1, 1);

        pushButtonSaveDefSpeed = new QPushButton(layoutWidget);
        pushButtonSaveDefSpeed->setObjectName("pushButtonSaveDefSpeed");

        gridLayout->addWidget(pushButtonSaveDefSpeed, 1, 3, 1, 1);

        lineEditSaveDefSpeed = new QLineEdit(layoutWidget);
        lineEditSaveDefSpeed->setObjectName("lineEditSaveDefSpeed");

        gridLayout->addWidget(lineEditSaveDefSpeed, 1, 4, 1, 1);

        pushButtonSaveAccel = new QPushButton(layoutWidget);
        pushButtonSaveAccel->setObjectName("pushButtonSaveAccel");

        gridLayout->addWidget(pushButtonSaveAccel, 2, 3, 1, 1);

        lineEditSaveAccel = new QLineEdit(layoutWidget);
        lineEditSaveAccel->setObjectName("lineEditSaveAccel");

        gridLayout->addWidget(lineEditSaveAccel, 2, 4, 1, 1);

        pushButtonSaveDecel = new QPushButton(layoutWidget);
        pushButtonSaveDecel->setObjectName("pushButtonSaveDecel");

        gridLayout->addWidget(pushButtonSaveDecel, 3, 3, 1, 1);

        lineEditSaveDecel = new QLineEdit(layoutWidget);
        lineEditSaveDecel->setObjectName("lineEditSaveDecel");

        gridLayout->addWidget(lineEditSaveDecel, 3, 4, 1, 1);

        pushButtonSaveDelta = new QPushButton(layoutWidget);
        pushButtonSaveDelta->setObjectName("pushButtonSaveDelta");

        gridLayout->addWidget(pushButtonSaveDelta, 4, 3, 1, 1);

        lineEditSaveDelta = new QLineEdit(layoutWidget);
        lineEditSaveDelta->setObjectName("lineEditSaveDelta");

        gridLayout->addWidget(lineEditSaveDelta, 4, 4, 1, 1);

        pushButtonSensor1Polarity = new QPushButton(layoutWidget);
        pushButtonSensor1Polarity->setObjectName("pushButtonSensor1Polarity");

        gridLayout->addWidget(pushButtonSensor1Polarity, 5, 3, 1, 1);

        lineEditSensor1Polarity = new QLineEdit(layoutWidget);
        lineEditSensor1Polarity->setObjectName("lineEditSensor1Polarity");

        gridLayout->addWidget(lineEditSensor1Polarity, 5, 4, 1, 1);

        pushButtonSensor2Polarity = new QPushButton(layoutWidget);
        pushButtonSensor2Polarity->setObjectName("pushButtonSensor2Polarity");

        gridLayout->addWidget(pushButtonSensor2Polarity, 6, 3, 1, 1);

        lineEditSensor2Polarity = new QLineEdit(layoutWidget);
        lineEditSensor2Polarity->setObjectName("lineEditSensor2Polarity");

        gridLayout->addWidget(lineEditSensor2Polarity, 6, 4, 1, 1);

        pushButtonSensor3Polarity = new QPushButton(layoutWidget);
        pushButtonSensor3Polarity->setObjectName("pushButtonSensor3Polarity");

        gridLayout->addWidget(pushButtonSensor3Polarity, 7, 3, 1, 1);

        lineEditSensor3Polarity = new QLineEdit(layoutWidget);
        lineEditSensor3Polarity->setObjectName("lineEditSensor3Polarity");

        gridLayout->addWidget(lineEditSensor3Polarity, 7, 4, 1, 1);

        pushButtonSensor4Polarity = new QPushButton(layoutWidget);
        pushButtonSensor4Polarity->setObjectName("pushButtonSensor4Polarity");

        gridLayout->addWidget(pushButtonSensor4Polarity, 8, 3, 1, 1);

        lineEditSensor4Polarity = new QLineEdit(layoutWidget);
        lineEditSensor4Polarity->setObjectName("lineEditSensor4Polarity");

        gridLayout->addWidget(lineEditSensor4Polarity, 8, 4, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonDecel->setText(QCoreApplication::translate("MainWindow", "decel", nullptr));
        pushButtonReserDRVRErr->setText(QCoreApplication::translate("MainWindow", "ReserDRVRErr", nullptr));
        pushButtonForward->setText(QCoreApplication::translate("MainWindow", "forward", nullptr));
        pushButtonRezervOn->setText(QCoreApplication::translate("MainWindow", "RezervOn", nullptr));
        pushButtonSaveNumBoard->setText(QCoreApplication::translate("MainWindow", "SaveNumBoard", nullptr));
        pushButtonSaveStartPos->setText(QCoreApplication::translate("MainWindow", "SaveStartPos", nullptr));
        pushButtonRezervOff->setText(QCoreApplication::translate("MainWindow", "RezervOff", nullptr));
        pushButtonBrakeOff->setText(QCoreApplication::translate("MainWindow", "BrakeOff", nullptr));
        pushButtonBoard->setText(QCoreApplication::translate("MainWindow", "board", nullptr));
        pushButtonSaveMaxSpeed->setText(QCoreApplication::translate("MainWindow", "SaveMaxSpeed", nullptr));
        pushButtoncurrentPos->setText(QCoreApplication::translate("MainWindow", "currentPos", nullptr));
        pushButtonHomingZero->setText(QCoreApplication::translate("MainWindow", "HomingZero", nullptr));
        pushButtonDebugOn->setText(QCoreApplication::translate("MainWindow", "debugOn", nullptr));
        pushButtonBackward->setText(QCoreApplication::translate("MainWindow", "backward", nullptr));
        pushButtonBrakeOn->setText(QCoreApplication::translate("MainWindow", "BrakeOn", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        pushButtonAccel->setText(QCoreApplication::translate("MainWindow", "accel", nullptr));
        pushButtonSaveNumGroup->setText(QCoreApplication::translate("MainWindow", "SaveNumGroup", nullptr));
        pushButtonAlarmResetOn->setText(QCoreApplication::translate("MainWindow", "AlarmResetOn", nullptr));
        pushButtonAlarmResetOff->setText(QCoreApplication::translate("MainWindow", "AlarmResetOff", nullptr));
        pushButtonHomingMax->setText(QCoreApplication::translate("MainWindow", "HomingMax", nullptr));
        pushButtonSaveEndPos->setText(QCoreApplication::translate("MainWindow", "SaveEndPos", nullptr));
        pushButtonSpeed->setText(QCoreApplication::translate("MainWindow", "speed", nullptr));
        pushButtonSteps->setText(QCoreApplication::translate("MainWindow", "steps", nullptr));
        pushButtonSaveDefSpeed->setText(QCoreApplication::translate("MainWindow", "SaveDefSpeed", nullptr));
        pushButtonSaveAccel->setText(QCoreApplication::translate("MainWindow", "SaveAccel", nullptr));
        pushButtonSaveDecel->setText(QCoreApplication::translate("MainWindow", "SaveDecel", nullptr));
        pushButtonSaveDelta->setText(QCoreApplication::translate("MainWindow", "SaveDelta", nullptr));
        pushButtonSensor1Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor1Polarity", nullptr));
        pushButtonSensor2Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor2Polarity", nullptr));
        pushButtonSensor3Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor3Polarity", nullptr));
        pushButtonSensor4Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor4Polarity", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
