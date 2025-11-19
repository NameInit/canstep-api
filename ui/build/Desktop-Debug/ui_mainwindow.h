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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
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
    QPushButton *pushButtonBrakeOn;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonAccel;
    QPushButton *pushButtonAl_ORezervPolarity;
    QLineEdit *lineEditSteps;
    QPushButton *pushButtonAl_CLRPolarity;
    QPushButton *pushButtonSensor4Dir;
    QPushButton *pushButtonReserDRVRErr;
    QPushButton *pushButtonHomingMax;
    QPushButton *pushButtonAl_OBrakePolarity;
    QHBoxLayout *horizontalLayoutTrunData;
    QLabel *labelTurnData;
    QLineEdit *lineEditTurnData;
    QLineEdit *lineEditSaveMaxSpeed;
    QComboBox *comboBoxSensor4Dir;
    QPushButton *pushButtonFAULTPolarity;
    QPushButton *pushButtonMotorSpeed;
    QComboBox *comboBoxEnPolarity;
    QPushButton *pushButtonSaveDefSpeed;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEditSaveDelta;
    QPushButton *pushButtonStepsTurn;
    QPushButton *pushButtonSensor1Dir;
    QPushButton *pushButtonSRVRDYPolarity;
    QPushButton *pushButtonSensor3Dir;
    QComboBox *comboBoxBrakePolarity;
    QPushButton *pushButtonBrakePolarity;
    QComboBox *comboBoxFAULTPolarity;
    QPushButton *pushButtonSaveAccel;
    QComboBox *comboBoxSensor2Dir;
    QHBoxLayout *horizontalLayoutPolarity;
    QLabel *labelPolarity;
    QLineEdit *lineEditPolarity;
    QComboBox *comboBoxEncoderActive;
    QPushButton *pushButtonSensor4Polarity;
    QComboBox *comboBoxSensor4Polarity;
    QPushButton *pushButtonHomingZero;
    QPushButton *pushButtonSpeed;
    QPushButton *pushButtonEnPolarity;
    QPushButton *pushButtonSensor2Dir;
    QLineEdit *lineEditMicroSteps;
    QPushButton *pushButtonINPOSPolarity;
    QPushButton *pushButtonSensor2Polarity;
    QPushButton *pushButtonSensor3Polarity;
    QPushButton *pushButtonSteps;
    QPushButton *pushButtonBoard;
    QLineEdit *lineEditSaveStartPos;
    QPushButton *pushButtonAlarmCode;
    QLineEdit *lineEditSpeed;
    QLineEdit *lineEditBoard;
    QPushButton *pushButtonSaveNumBoard;
    QLineEdit *lineEditAccel;
    QLineEdit *lineEditSaveEndPos;
    QPushButton *pushButtonMotorTorque;
    QPushButton *pushButtonRezervOff;
    QLineEdit *lineEditSaveDecel;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonDriverOn;
    QPushButton *pushButtonBrakeOff;
    QComboBox *comboBoxSensor3Polarity;
    QLineEdit *lineEditSaveDefSpeed;
    QPushButton *pushButtonSaveStartPos;
    QPushButton *pushButtonDriverOff;
    QLineEdit *lineEditcurrentPos;
    QLineEdit *lineEditSaveAccel;
    QPushButton *pushButtonDebugOn;
    QPushButton *pushButtonSaveNumGroup;
    QPushButton *pushButtonSaveDecel;
    QLineEdit *lineEditSaveNumBoard;
    QComboBox *comboBoxSensor2Polarity;
    QPushButton *pushButtonAbsPosRot;
    QPushButton *pushButtonDecel;
    QComboBox *comboBoxSensor1Dir;
    QComboBox *comboBoxAl_CLRPolarity;
    QPushButton *pushButtonBackward;
    QPushButton *pushButtonSaveEndPos;
    QComboBox *comboBoxAl_OBrakePolarity;
    QPushButton *pushButtonSaveDelta;
    QPushButton *pushButtonAlarmResetOn;
    QPushButton *pushButtonForward;
    QLineEdit *lineEditDecel;
    QPushButton *pushButtoncurrentPos;
    QLineEdit *lineEditSaveNumGroup;
    QComboBox *comboBoxSensor1Polarity;
    QPushButton *pushButtonAlarmResetOff;
    QPushButton *pushButtonDirPolarity;
    QPushButton *pushButtonResetLostCntrs;
    QHBoxLayout *horizontalLayoutDelta;
    QLabel *labelDelta;
    QLineEdit *lineEditDelta;
    QComboBox *comboBoxSensor3Dir;
    QComboBox *comboBoxAl_ORezervPolarity;
    QPushButton *pushButtonEncoderActive;
    QComboBox *comboBoxSRVRDYPolarity;
    QPushButton *pushButtonMicroSteps;
    QPushButton *pushButtonRezervOn;
    QPushButton *pushButtonSaveMaxSpeed;
    QPushButton *pushButtonConnect;
    QComboBox *comboBoxDirPolarity;
    QComboBox *comboBoxINPOSPolarity;
    QPushButton *pushButtonSensor1Polarity;
    QPushButton *pushButtonResetCANStep;
    QLineEdit *lineEditStepsTurn;
    QPushButton *pushButtonEncoderConfig;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(983, 646);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 859, 572));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonBrakeOn = new QPushButton(layoutWidget);
        pushButtonBrakeOn->setObjectName("pushButtonBrakeOn");

        gridLayout->addWidget(pushButtonBrakeOn, 9, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        pushButtonAccel = new QPushButton(layoutWidget);
        pushButtonAccel->setObjectName("pushButtonAccel");

        gridLayout->addWidget(pushButtonAccel, 4, 0, 1, 1);

        pushButtonAl_ORezervPolarity = new QPushButton(layoutWidget);
        pushButtonAl_ORezervPolarity->setObjectName("pushButtonAl_ORezervPolarity");

        gridLayout->addWidget(pushButtonAl_ORezervPolarity, 14, 6, 1, 1);

        lineEditSteps = new QLineEdit(layoutWidget);
        lineEditSteps->setObjectName("lineEditSteps");

        gridLayout->addWidget(lineEditSteps, 2, 1, 1, 1);

        pushButtonAl_CLRPolarity = new QPushButton(layoutWidget);
        pushButtonAl_CLRPolarity->setObjectName("pushButtonAl_CLRPolarity");

        gridLayout->addWidget(pushButtonAl_CLRPolarity, 12, 6, 1, 1);

        pushButtonSensor4Dir = new QPushButton(layoutWidget);
        pushButtonSensor4Dir->setObjectName("pushButtonSensor4Dir");

        gridLayout->addWidget(pushButtonSensor4Dir, 8, 6, 1, 1);

        pushButtonReserDRVRErr = new QPushButton(layoutWidget);
        pushButtonReserDRVRErr->setObjectName("pushButtonReserDRVRErr");

        gridLayout->addWidget(pushButtonReserDRVRErr, 8, 0, 1, 1);

        pushButtonHomingMax = new QPushButton(layoutWidget);
        pushButtonHomingMax->setObjectName("pushButtonHomingMax");

        gridLayout->addWidget(pushButtonHomingMax, 7, 1, 1, 1);

        pushButtonAl_OBrakePolarity = new QPushButton(layoutWidget);
        pushButtonAl_OBrakePolarity->setObjectName("pushButtonAl_OBrakePolarity");

        gridLayout->addWidget(pushButtonAl_OBrakePolarity, 13, 6, 1, 1);

        horizontalLayoutTrunData = new QHBoxLayout();
        horizontalLayoutTrunData->setObjectName("horizontalLayoutTrunData");
        labelTurnData = new QLabel(layoutWidget);
        labelTurnData->setObjectName("labelTurnData");

        horizontalLayoutTrunData->addWidget(labelTurnData);

        lineEditTurnData = new QLineEdit(layoutWidget);
        lineEditTurnData->setObjectName("lineEditTurnData");

        horizontalLayoutTrunData->addWidget(lineEditTurnData);


        gridLayout->addLayout(horizontalLayoutTrunData, 16, 3, 1, 1);

        lineEditSaveMaxSpeed = new QLineEdit(layoutWidget);
        lineEditSaveMaxSpeed->setObjectName("lineEditSaveMaxSpeed");

        gridLayout->addWidget(lineEditSaveMaxSpeed, 0, 4, 1, 1);

        comboBoxSensor4Dir = new QComboBox(layoutWidget);
        comboBoxSensor4Dir->addItem(QString());
        comboBoxSensor4Dir->addItem(QString());
        comboBoxSensor4Dir->addItem(QString());
        comboBoxSensor4Dir->setObjectName("comboBoxSensor4Dir");

        gridLayout->addWidget(comboBoxSensor4Dir, 8, 7, 1, 1);

        pushButtonFAULTPolarity = new QPushButton(layoutWidget);
        pushButtonFAULTPolarity->setObjectName("pushButtonFAULTPolarity");

        gridLayout->addWidget(pushButtonFAULTPolarity, 2, 6, 1, 1);

        pushButtonMotorSpeed = new QPushButton(layoutWidget);
        pushButtonMotorSpeed->setObjectName("pushButtonMotorSpeed");

        gridLayout->addWidget(pushButtonMotorSpeed, 11, 4, 1, 1);

        comboBoxEnPolarity = new QComboBox(layoutWidget);
        comboBoxEnPolarity->addItem(QString());
        comboBoxEnPolarity->addItem(QString());
        comboBoxEnPolarity->addItem(QString());
        comboBoxEnPolarity->setObjectName("comboBoxEnPolarity");

        gridLayout->addWidget(comboBoxEnPolarity, 11, 7, 1, 1);

        pushButtonSaveDefSpeed = new QPushButton(layoutWidget);
        pushButtonSaveDefSpeed->setObjectName("pushButtonSaveDefSpeed");

        gridLayout->addWidget(pushButtonSaveDefSpeed, 1, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        lineEditSaveDelta = new QLineEdit(layoutWidget);
        lineEditSaveDelta->setObjectName("lineEditSaveDelta");

        gridLayout->addWidget(lineEditSaveDelta, 4, 4, 1, 1);

        pushButtonStepsTurn = new QPushButton(layoutWidget);
        pushButtonStepsTurn->setObjectName("pushButtonStepsTurn");

        gridLayout->addWidget(pushButtonStepsTurn, 14, 3, 1, 1);

        pushButtonSensor1Dir = new QPushButton(layoutWidget);
        pushButtonSensor1Dir->setObjectName("pushButtonSensor1Dir");

        gridLayout->addWidget(pushButtonSensor1Dir, 5, 6, 1, 1);

        pushButtonSRVRDYPolarity = new QPushButton(layoutWidget);
        pushButtonSRVRDYPolarity->setObjectName("pushButtonSRVRDYPolarity");

        gridLayout->addWidget(pushButtonSRVRDYPolarity, 0, 6, 1, 1);

        pushButtonSensor3Dir = new QPushButton(layoutWidget);
        pushButtonSensor3Dir->setObjectName("pushButtonSensor3Dir");

        gridLayout->addWidget(pushButtonSensor3Dir, 7, 6, 1, 1);

        comboBoxBrakePolarity = new QComboBox(layoutWidget);
        comboBoxBrakePolarity->addItem(QString());
        comboBoxBrakePolarity->addItem(QString());
        comboBoxBrakePolarity->addItem(QString());
        comboBoxBrakePolarity->setObjectName("comboBoxBrakePolarity");

        gridLayout->addWidget(comboBoxBrakePolarity, 3, 7, 1, 1);

        pushButtonBrakePolarity = new QPushButton(layoutWidget);
        pushButtonBrakePolarity->setObjectName("pushButtonBrakePolarity");

        gridLayout->addWidget(pushButtonBrakePolarity, 3, 6, 1, 1);

        comboBoxFAULTPolarity = new QComboBox(layoutWidget);
        comboBoxFAULTPolarity->addItem(QString());
        comboBoxFAULTPolarity->addItem(QString());
        comboBoxFAULTPolarity->addItem(QString());
        comboBoxFAULTPolarity->setObjectName("comboBoxFAULTPolarity");

        gridLayout->addWidget(comboBoxFAULTPolarity, 2, 7, 1, 1);

        pushButtonSaveAccel = new QPushButton(layoutWidget);
        pushButtonSaveAccel->setObjectName("pushButtonSaveAccel");

        gridLayout->addWidget(pushButtonSaveAccel, 2, 3, 1, 1);

        comboBoxSensor2Dir = new QComboBox(layoutWidget);
        comboBoxSensor2Dir->addItem(QString());
        comboBoxSensor2Dir->addItem(QString());
        comboBoxSensor2Dir->addItem(QString());
        comboBoxSensor2Dir->setObjectName("comboBoxSensor2Dir");

        gridLayout->addWidget(comboBoxSensor2Dir, 6, 7, 1, 1);

        horizontalLayoutPolarity = new QHBoxLayout();
        horizontalLayoutPolarity->setObjectName("horizontalLayoutPolarity");
        labelPolarity = new QLabel(layoutWidget);
        labelPolarity->setObjectName("labelPolarity");

        horizontalLayoutPolarity->addWidget(labelPolarity);

        lineEditPolarity = new QLineEdit(layoutWidget);
        lineEditPolarity->setObjectName("lineEditPolarity");

        horizontalLayoutPolarity->addWidget(lineEditPolarity);


        gridLayout->addLayout(horizontalLayoutPolarity, 15, 4, 1, 1);

        comboBoxEncoderActive = new QComboBox(layoutWidget);
        comboBoxEncoderActive->addItem(QString());
        comboBoxEncoderActive->addItem(QString());
        comboBoxEncoderActive->setObjectName("comboBoxEncoderActive");

        gridLayout->addWidget(comboBoxEncoderActive, 4, 7, 1, 1);

        pushButtonSensor4Polarity = new QPushButton(layoutWidget);
        pushButtonSensor4Polarity->setObjectName("pushButtonSensor4Polarity");

        gridLayout->addWidget(pushButtonSensor4Polarity, 8, 3, 1, 1);

        comboBoxSensor4Polarity = new QComboBox(layoutWidget);
        comboBoxSensor4Polarity->addItem(QString());
        comboBoxSensor4Polarity->addItem(QString());
        comboBoxSensor4Polarity->addItem(QString());
        comboBoxSensor4Polarity->setObjectName("comboBoxSensor4Polarity");

        gridLayout->addWidget(comboBoxSensor4Polarity, 8, 4, 1, 1);

        pushButtonHomingZero = new QPushButton(layoutWidget);
        pushButtonHomingZero->setObjectName("pushButtonHomingZero");

        gridLayout->addWidget(pushButtonHomingZero, 7, 0, 1, 1);

        pushButtonSpeed = new QPushButton(layoutWidget);
        pushButtonSpeed->setObjectName("pushButtonSpeed");

        gridLayout->addWidget(pushButtonSpeed, 3, 0, 1, 1);

        pushButtonEnPolarity = new QPushButton(layoutWidget);
        pushButtonEnPolarity->setObjectName("pushButtonEnPolarity");

        gridLayout->addWidget(pushButtonEnPolarity, 11, 6, 1, 1);

        pushButtonSensor2Dir = new QPushButton(layoutWidget);
        pushButtonSensor2Dir->setObjectName("pushButtonSensor2Dir");

        gridLayout->addWidget(pushButtonSensor2Dir, 6, 6, 1, 1);

        lineEditMicroSteps = new QLineEdit(layoutWidget);
        lineEditMicroSteps->setObjectName("lineEditMicroSteps");

        gridLayout->addWidget(lineEditMicroSteps, 13, 4, 1, 1);

        pushButtonINPOSPolarity = new QPushButton(layoutWidget);
        pushButtonINPOSPolarity->setObjectName("pushButtonINPOSPolarity");

        gridLayout->addWidget(pushButtonINPOSPolarity, 1, 6, 1, 1);

        pushButtonSensor2Polarity = new QPushButton(layoutWidget);
        pushButtonSensor2Polarity->setObjectName("pushButtonSensor2Polarity");

        gridLayout->addWidget(pushButtonSensor2Polarity, 6, 3, 1, 1);

        pushButtonSensor3Polarity = new QPushButton(layoutWidget);
        pushButtonSensor3Polarity->setObjectName("pushButtonSensor3Polarity");

        gridLayout->addWidget(pushButtonSensor3Polarity, 7, 3, 1, 1);

        pushButtonSteps = new QPushButton(layoutWidget);
        pushButtonSteps->setObjectName("pushButtonSteps");

        gridLayout->addWidget(pushButtonSteps, 2, 0, 1, 1);

        pushButtonBoard = new QPushButton(layoutWidget);
        pushButtonBoard->setObjectName("pushButtonBoard");

        gridLayout->addWidget(pushButtonBoard, 1, 0, 1, 1);

        lineEditSaveStartPos = new QLineEdit(layoutWidget);
        lineEditSaveStartPos->setObjectName("lineEditSaveStartPos");

        gridLayout->addWidget(lineEditSaveStartPos, 15, 1, 1, 1);

        pushButtonAlarmCode = new QPushButton(layoutWidget);
        pushButtonAlarmCode->setObjectName("pushButtonAlarmCode");

        gridLayout->addWidget(pushButtonAlarmCode, 12, 4, 1, 1);

        lineEditSpeed = new QLineEdit(layoutWidget);
        lineEditSpeed->setObjectName("lineEditSpeed");

        gridLayout->addWidget(lineEditSpeed, 3, 1, 1, 1);

        lineEditBoard = new QLineEdit(layoutWidget);
        lineEditBoard->setObjectName("lineEditBoard");

        gridLayout->addWidget(lineEditBoard, 1, 1, 1, 1);

        pushButtonSaveNumBoard = new QPushButton(layoutWidget);
        pushButtonSaveNumBoard->setObjectName("pushButtonSaveNumBoard");

        gridLayout->addWidget(pushButtonSaveNumBoard, 13, 0, 1, 1);

        lineEditAccel = new QLineEdit(layoutWidget);
        lineEditAccel->setObjectName("lineEditAccel");

        gridLayout->addWidget(lineEditAccel, 4, 1, 1, 1);

        lineEditSaveEndPos = new QLineEdit(layoutWidget);
        lineEditSaveEndPos->setObjectName("lineEditSaveEndPos");

        gridLayout->addWidget(lineEditSaveEndPos, 16, 1, 1, 1);

        pushButtonMotorTorque = new QPushButton(layoutWidget);
        pushButtonMotorTorque->setObjectName("pushButtonMotorTorque");

        gridLayout->addWidget(pushButtonMotorTorque, 11, 3, 1, 1);

        pushButtonRezervOff = new QPushButton(layoutWidget);
        pushButtonRezervOff->setObjectName("pushButtonRezervOff");

        gridLayout->addWidget(pushButtonRezervOff, 10, 0, 1, 1);

        lineEditSaveDecel = new QLineEdit(layoutWidget);
        lineEditSaveDecel->setObjectName("lineEditSaveDecel");

        gridLayout->addWidget(lineEditSaveDecel, 3, 4, 1, 1);

        pushButtonStop = new QPushButton(layoutWidget);
        pushButtonStop->setObjectName("pushButtonStop");

        gridLayout->addWidget(pushButtonStop, 8, 1, 1, 1);

        pushButtonDriverOn = new QPushButton(layoutWidget);
        pushButtonDriverOn->setObjectName("pushButtonDriverOn");

        gridLayout->addWidget(pushButtonDriverOn, 10, 3, 1, 1);

        pushButtonBrakeOff = new QPushButton(layoutWidget);
        pushButtonBrakeOff->setObjectName("pushButtonBrakeOff");

        gridLayout->addWidget(pushButtonBrakeOff, 9, 0, 1, 1);

        comboBoxSensor3Polarity = new QComboBox(layoutWidget);
        comboBoxSensor3Polarity->addItem(QString());
        comboBoxSensor3Polarity->addItem(QString());
        comboBoxSensor3Polarity->addItem(QString());
        comboBoxSensor3Polarity->setObjectName("comboBoxSensor3Polarity");

        gridLayout->addWidget(comboBoxSensor3Polarity, 7, 4, 1, 1);

        lineEditSaveDefSpeed = new QLineEdit(layoutWidget);
        lineEditSaveDefSpeed->setObjectName("lineEditSaveDefSpeed");

        gridLayout->addWidget(lineEditSaveDefSpeed, 1, 4, 1, 1);

        pushButtonSaveStartPos = new QPushButton(layoutWidget);
        pushButtonSaveStartPos->setObjectName("pushButtonSaveStartPos");

        gridLayout->addWidget(pushButtonSaveStartPos, 15, 0, 1, 1);

        pushButtonDriverOff = new QPushButton(layoutWidget);
        pushButtonDriverOff->setObjectName("pushButtonDriverOff");

        gridLayout->addWidget(pushButtonDriverOff, 10, 4, 1, 1);

        lineEditcurrentPos = new QLineEdit(layoutWidget);
        lineEditcurrentPos->setObjectName("lineEditcurrentPos");

        gridLayout->addWidget(lineEditcurrentPos, 12, 1, 1, 1);

        lineEditSaveAccel = new QLineEdit(layoutWidget);
        lineEditSaveAccel->setObjectName("lineEditSaveAccel");

        gridLayout->addWidget(lineEditSaveAccel, 2, 4, 1, 1);

        pushButtonDebugOn = new QPushButton(layoutWidget);
        pushButtonDebugOn->setObjectName("pushButtonDebugOn");

        gridLayout->addWidget(pushButtonDebugOn, 0, 1, 1, 1);

        pushButtonSaveNumGroup = new QPushButton(layoutWidget);
        pushButtonSaveNumGroup->setObjectName("pushButtonSaveNumGroup");

        gridLayout->addWidget(pushButtonSaveNumGroup, 14, 0, 1, 1);

        pushButtonSaveDecel = new QPushButton(layoutWidget);
        pushButtonSaveDecel->setObjectName("pushButtonSaveDecel");

        gridLayout->addWidget(pushButtonSaveDecel, 3, 3, 1, 1);

        lineEditSaveNumBoard = new QLineEdit(layoutWidget);
        lineEditSaveNumBoard->setObjectName("lineEditSaveNumBoard");

        gridLayout->addWidget(lineEditSaveNumBoard, 13, 1, 1, 1);

        comboBoxSensor2Polarity = new QComboBox(layoutWidget);
        comboBoxSensor2Polarity->addItem(QString());
        comboBoxSensor2Polarity->addItem(QString());
        comboBoxSensor2Polarity->addItem(QString());
        comboBoxSensor2Polarity->setObjectName("comboBoxSensor2Polarity");

        gridLayout->addWidget(comboBoxSensor2Polarity, 6, 4, 1, 1);

        pushButtonAbsPosRot = new QPushButton(layoutWidget);
        pushButtonAbsPosRot->setObjectName("pushButtonAbsPosRot");

        gridLayout->addWidget(pushButtonAbsPosRot, 12, 3, 1, 1);

        pushButtonDecel = new QPushButton(layoutWidget);
        pushButtonDecel->setObjectName("pushButtonDecel");

        gridLayout->addWidget(pushButtonDecel, 5, 0, 1, 1);

        comboBoxSensor1Dir = new QComboBox(layoutWidget);
        comboBoxSensor1Dir->addItem(QString());
        comboBoxSensor1Dir->addItem(QString());
        comboBoxSensor1Dir->addItem(QString());
        comboBoxSensor1Dir->setObjectName("comboBoxSensor1Dir");

        gridLayout->addWidget(comboBoxSensor1Dir, 5, 7, 1, 1);

        comboBoxAl_CLRPolarity = new QComboBox(layoutWidget);
        comboBoxAl_CLRPolarity->addItem(QString());
        comboBoxAl_CLRPolarity->addItem(QString());
        comboBoxAl_CLRPolarity->addItem(QString());
        comboBoxAl_CLRPolarity->setObjectName("comboBoxAl_CLRPolarity");

        gridLayout->addWidget(comboBoxAl_CLRPolarity, 12, 7, 1, 1);

        pushButtonBackward = new QPushButton(layoutWidget);
        pushButtonBackward->setObjectName("pushButtonBackward");

        gridLayout->addWidget(pushButtonBackward, 6, 1, 1, 1);

        pushButtonSaveEndPos = new QPushButton(layoutWidget);
        pushButtonSaveEndPos->setObjectName("pushButtonSaveEndPos");

        gridLayout->addWidget(pushButtonSaveEndPos, 16, 0, 1, 1);

        comboBoxAl_OBrakePolarity = new QComboBox(layoutWidget);
        comboBoxAl_OBrakePolarity->addItem(QString());
        comboBoxAl_OBrakePolarity->addItem(QString());
        comboBoxAl_OBrakePolarity->addItem(QString());
        comboBoxAl_OBrakePolarity->setObjectName("comboBoxAl_OBrakePolarity");

        gridLayout->addWidget(comboBoxAl_OBrakePolarity, 13, 7, 1, 1);

        pushButtonSaveDelta = new QPushButton(layoutWidget);
        pushButtonSaveDelta->setObjectName("pushButtonSaveDelta");

        gridLayout->addWidget(pushButtonSaveDelta, 4, 3, 1, 1);

        pushButtonAlarmResetOn = new QPushButton(layoutWidget);
        pushButtonAlarmResetOn->setObjectName("pushButtonAlarmResetOn");

        gridLayout->addWidget(pushButtonAlarmResetOn, 11, 0, 1, 1);

        pushButtonForward = new QPushButton(layoutWidget);
        pushButtonForward->setObjectName("pushButtonForward");

        gridLayout->addWidget(pushButtonForward, 6, 0, 1, 1);

        lineEditDecel = new QLineEdit(layoutWidget);
        lineEditDecel->setObjectName("lineEditDecel");

        gridLayout->addWidget(lineEditDecel, 5, 1, 1, 1);

        pushButtoncurrentPos = new QPushButton(layoutWidget);
        pushButtoncurrentPos->setObjectName("pushButtoncurrentPos");

        gridLayout->addWidget(pushButtoncurrentPos, 12, 0, 1, 1);

        lineEditSaveNumGroup = new QLineEdit(layoutWidget);
        lineEditSaveNumGroup->setObjectName("lineEditSaveNumGroup");

        gridLayout->addWidget(lineEditSaveNumGroup, 14, 1, 1, 1);

        comboBoxSensor1Polarity = new QComboBox(layoutWidget);
        comboBoxSensor1Polarity->addItem(QString());
        comboBoxSensor1Polarity->addItem(QString());
        comboBoxSensor1Polarity->addItem(QString());
        comboBoxSensor1Polarity->setObjectName("comboBoxSensor1Polarity");

        gridLayout->addWidget(comboBoxSensor1Polarity, 5, 4, 1, 1);

        pushButtonAlarmResetOff = new QPushButton(layoutWidget);
        pushButtonAlarmResetOff->setObjectName("pushButtonAlarmResetOff");

        gridLayout->addWidget(pushButtonAlarmResetOff, 11, 1, 1, 1);

        pushButtonDirPolarity = new QPushButton(layoutWidget);
        pushButtonDirPolarity->setObjectName("pushButtonDirPolarity");

        gridLayout->addWidget(pushButtonDirPolarity, 10, 6, 1, 1);

        pushButtonResetLostCntrs = new QPushButton(layoutWidget);
        pushButtonResetLostCntrs->setObjectName("pushButtonResetLostCntrs");

        gridLayout->addWidget(pushButtonResetLostCntrs, 9, 4, 1, 1);

        horizontalLayoutDelta = new QHBoxLayout();
        horizontalLayoutDelta->setObjectName("horizontalLayoutDelta");
        labelDelta = new QLabel(layoutWidget);
        labelDelta->setObjectName("labelDelta");

        horizontalLayoutDelta->addWidget(labelDelta);

        lineEditDelta = new QLineEdit(layoutWidget);
        lineEditDelta->setObjectName("lineEditDelta");

        horizontalLayoutDelta->addWidget(lineEditDelta);


        gridLayout->addLayout(horizontalLayoutDelta, 16, 4, 1, 1);

        comboBoxSensor3Dir = new QComboBox(layoutWidget);
        comboBoxSensor3Dir->addItem(QString());
        comboBoxSensor3Dir->addItem(QString());
        comboBoxSensor3Dir->addItem(QString());
        comboBoxSensor3Dir->setObjectName("comboBoxSensor3Dir");

        gridLayout->addWidget(comboBoxSensor3Dir, 7, 7, 1, 1);

        comboBoxAl_ORezervPolarity = new QComboBox(layoutWidget);
        comboBoxAl_ORezervPolarity->addItem(QString());
        comboBoxAl_ORezervPolarity->addItem(QString());
        comboBoxAl_ORezervPolarity->addItem(QString());
        comboBoxAl_ORezervPolarity->setObjectName("comboBoxAl_ORezervPolarity");

        gridLayout->addWidget(comboBoxAl_ORezervPolarity, 14, 7, 1, 1);

        pushButtonEncoderActive = new QPushButton(layoutWidget);
        pushButtonEncoderActive->setObjectName("pushButtonEncoderActive");

        gridLayout->addWidget(pushButtonEncoderActive, 4, 6, 1, 1);

        comboBoxSRVRDYPolarity = new QComboBox(layoutWidget);
        comboBoxSRVRDYPolarity->addItem(QString());
        comboBoxSRVRDYPolarity->addItem(QString());
        comboBoxSRVRDYPolarity->addItem(QString());
        comboBoxSRVRDYPolarity->setObjectName("comboBoxSRVRDYPolarity");

        gridLayout->addWidget(comboBoxSRVRDYPolarity, 0, 7, 1, 1);

        pushButtonMicroSteps = new QPushButton(layoutWidget);
        pushButtonMicroSteps->setObjectName("pushButtonMicroSteps");

        gridLayout->addWidget(pushButtonMicroSteps, 13, 3, 1, 1);

        pushButtonRezervOn = new QPushButton(layoutWidget);
        pushButtonRezervOn->setObjectName("pushButtonRezervOn");

        gridLayout->addWidget(pushButtonRezervOn, 10, 1, 1, 1);

        pushButtonSaveMaxSpeed = new QPushButton(layoutWidget);
        pushButtonSaveMaxSpeed->setObjectName("pushButtonSaveMaxSpeed");

        gridLayout->addWidget(pushButtonSaveMaxSpeed, 0, 3, 1, 1);

        pushButtonConnect = new QPushButton(layoutWidget);
        pushButtonConnect->setObjectName("pushButtonConnect");

        gridLayout->addWidget(pushButtonConnect, 0, 0, 1, 1);

        comboBoxDirPolarity = new QComboBox(layoutWidget);
        comboBoxDirPolarity->addItem(QString());
        comboBoxDirPolarity->addItem(QString());
        comboBoxDirPolarity->addItem(QString());
        comboBoxDirPolarity->setObjectName("comboBoxDirPolarity");

        gridLayout->addWidget(comboBoxDirPolarity, 10, 7, 1, 1);

        comboBoxINPOSPolarity = new QComboBox(layoutWidget);
        comboBoxINPOSPolarity->addItem(QString());
        comboBoxINPOSPolarity->addItem(QString());
        comboBoxINPOSPolarity->addItem(QString());
        comboBoxINPOSPolarity->setObjectName("comboBoxINPOSPolarity");

        gridLayout->addWidget(comboBoxINPOSPolarity, 1, 7, 1, 1);

        pushButtonSensor1Polarity = new QPushButton(layoutWidget);
        pushButtonSensor1Polarity->setObjectName("pushButtonSensor1Polarity");

        gridLayout->addWidget(pushButtonSensor1Polarity, 5, 3, 1, 1);

        pushButtonResetCANStep = new QPushButton(layoutWidget);
        pushButtonResetCANStep->setObjectName("pushButtonResetCANStep");

        gridLayout->addWidget(pushButtonResetCANStep, 9, 3, 1, 1);

        lineEditStepsTurn = new QLineEdit(layoutWidget);
        lineEditStepsTurn->setObjectName("lineEditStepsTurn");

        gridLayout->addWidget(lineEditStepsTurn, 14, 4, 1, 1);

        pushButtonEncoderConfig = new QPushButton(layoutWidget);
        pushButtonEncoderConfig->setObjectName("pushButtonEncoderConfig");

        gridLayout->addWidget(pushButtonEncoderConfig, 15, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 983, 23));
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
        pushButtonBrakeOn->setText(QCoreApplication::translate("MainWindow", "BrakeOn", nullptr));
        pushButtonAccel->setText(QCoreApplication::translate("MainWindow", "accel", nullptr));
        pushButtonAl_ORezervPolarity->setText(QCoreApplication::translate("MainWindow", "Al_ORezervPolarity", nullptr));
        pushButtonAl_CLRPolarity->setText(QCoreApplication::translate("MainWindow", "Al_CLRPolarity", nullptr));
        pushButtonSensor4Dir->setText(QCoreApplication::translate("MainWindow", "SensorDir4", nullptr));
        pushButtonReserDRVRErr->setText(QCoreApplication::translate("MainWindow", "ReserDRVRErr", nullptr));
        pushButtonHomingMax->setText(QCoreApplication::translate("MainWindow", "HomingMax", nullptr));
        pushButtonAl_OBrakePolarity->setText(QCoreApplication::translate("MainWindow", "Al_OBrakePolarity", nullptr));
        labelTurnData->setText(QCoreApplication::translate("MainWindow", "TurnData:", nullptr));
        comboBoxSensor4Dir->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBoxSensor4Dir->setItemText(1, QCoreApplication::translate("MainWindow", "Forward", nullptr));
        comboBoxSensor4Dir->setItemText(2, QCoreApplication::translate("MainWindow", "Backward", nullptr));

        pushButtonFAULTPolarity->setText(QCoreApplication::translate("MainWindow", "FAULTPolarity", nullptr));
        pushButtonMotorSpeed->setText(QCoreApplication::translate("MainWindow", "MotorSpeed", nullptr));
        comboBoxEnPolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxEnPolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxEnPolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonSaveDefSpeed->setText(QCoreApplication::translate("MainWindow", "SaveDefSpeed", nullptr));
        pushButtonStepsTurn->setText(QCoreApplication::translate("MainWindow", "StepsTurn", nullptr));
        pushButtonSensor1Dir->setText(QCoreApplication::translate("MainWindow", "Sensor1Dir", nullptr));
        pushButtonSRVRDYPolarity->setText(QCoreApplication::translate("MainWindow", "SRVRDYPolarity", nullptr));
        pushButtonSensor3Dir->setText(QCoreApplication::translate("MainWindow", "SensorDir3", nullptr));
        comboBoxBrakePolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxBrakePolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxBrakePolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonBrakePolarity->setText(QCoreApplication::translate("MainWindow", "BrakePolarity", nullptr));
        comboBoxFAULTPolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxFAULTPolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxFAULTPolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonSaveAccel->setText(QCoreApplication::translate("MainWindow", "SaveAccel", nullptr));
        comboBoxSensor2Dir->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBoxSensor2Dir->setItemText(1, QCoreApplication::translate("MainWindow", "Forward", nullptr));
        comboBoxSensor2Dir->setItemText(2, QCoreApplication::translate("MainWindow", "Backward", nullptr));

        labelPolarity->setText(QCoreApplication::translate("MainWindow", "Pol:", nullptr));
        comboBoxEncoderActive->setItemText(0, QCoreApplication::translate("MainWindow", "True", nullptr));
        comboBoxEncoderActive->setItemText(1, QCoreApplication::translate("MainWindow", "False", nullptr));

        pushButtonSensor4Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor4Polarity", nullptr));
        comboBoxSensor4Polarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxSensor4Polarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxSensor4Polarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonHomingZero->setText(QCoreApplication::translate("MainWindow", "HomingZero", nullptr));
        pushButtonSpeed->setText(QCoreApplication::translate("MainWindow", "speed", nullptr));
        pushButtonEnPolarity->setText(QCoreApplication::translate("MainWindow", "EnPolarity", nullptr));
        pushButtonSensor2Dir->setText(QCoreApplication::translate("MainWindow", "SensorDir2", nullptr));
        pushButtonINPOSPolarity->setText(QCoreApplication::translate("MainWindow", "INPOSPolarity", nullptr));
        pushButtonSensor2Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor2Polarity", nullptr));
        pushButtonSensor3Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor3Polarity", nullptr));
        pushButtonSteps->setText(QCoreApplication::translate("MainWindow", "steps", nullptr));
        pushButtonBoard->setText(QCoreApplication::translate("MainWindow", "board", nullptr));
        pushButtonAlarmCode->setText(QCoreApplication::translate("MainWindow", "AlarmCode", nullptr));
        pushButtonSaveNumBoard->setText(QCoreApplication::translate("MainWindow", "SaveNumBoard", nullptr));
        pushButtonMotorTorque->setText(QCoreApplication::translate("MainWindow", "MotorTorque", nullptr));
        pushButtonRezervOff->setText(QCoreApplication::translate("MainWindow", "RezervOff", nullptr));
        pushButtonStop->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        pushButtonDriverOn->setText(QCoreApplication::translate("MainWindow", "DriverOn", nullptr));
        pushButtonBrakeOff->setText(QCoreApplication::translate("MainWindow", "BrakeOff", nullptr));
        comboBoxSensor3Polarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxSensor3Polarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxSensor3Polarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonSaveStartPos->setText(QCoreApplication::translate("MainWindow", "SaveStartPos", nullptr));
        pushButtonDriverOff->setText(QCoreApplication::translate("MainWindow", "DriverOff", nullptr));
        pushButtonDebugOn->setText(QCoreApplication::translate("MainWindow", "debugOn", nullptr));
        pushButtonSaveNumGroup->setText(QCoreApplication::translate("MainWindow", "SaveNumGroup", nullptr));
        pushButtonSaveDecel->setText(QCoreApplication::translate("MainWindow", "SaveDecel", nullptr));
        comboBoxSensor2Polarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxSensor2Polarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxSensor2Polarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonAbsPosRot->setText(QCoreApplication::translate("MainWindow", "AbsPosRot", nullptr));
        pushButtonDecel->setText(QCoreApplication::translate("MainWindow", "decel", nullptr));
        comboBoxSensor1Dir->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBoxSensor1Dir->setItemText(1, QCoreApplication::translate("MainWindow", "Forward", nullptr));
        comboBoxSensor1Dir->setItemText(2, QCoreApplication::translate("MainWindow", "Backward", nullptr));

        comboBoxAl_CLRPolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxAl_CLRPolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxAl_CLRPolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonBackward->setText(QCoreApplication::translate("MainWindow", "backward", nullptr));
        pushButtonSaveEndPos->setText(QCoreApplication::translate("MainWindow", "SaveEndPos", nullptr));
        comboBoxAl_OBrakePolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxAl_OBrakePolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxAl_OBrakePolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonSaveDelta->setText(QCoreApplication::translate("MainWindow", "SaveDelta", nullptr));
        pushButtonAlarmResetOn->setText(QCoreApplication::translate("MainWindow", "AlarmResetOn", nullptr));
        pushButtonForward->setText(QCoreApplication::translate("MainWindow", "forward", nullptr));
        pushButtoncurrentPos->setText(QCoreApplication::translate("MainWindow", "currentPos", nullptr));
        comboBoxSensor1Polarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxSensor1Polarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxSensor1Polarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonAlarmResetOff->setText(QCoreApplication::translate("MainWindow", "AlarmResetOff", nullptr));
        pushButtonDirPolarity->setText(QCoreApplication::translate("MainWindow", "DirPolarity", nullptr));
        pushButtonResetLostCntrs->setText(QCoreApplication::translate("MainWindow", "ResetLostCntrs", nullptr));
        labelDelta->setText(QCoreApplication::translate("MainWindow", "Delta:", nullptr));
        comboBoxSensor3Dir->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBoxSensor3Dir->setItemText(1, QCoreApplication::translate("MainWindow", "Forward", nullptr));
        comboBoxSensor3Dir->setItemText(2, QCoreApplication::translate("MainWindow", "Backward", nullptr));

        comboBoxAl_ORezervPolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxAl_ORezervPolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxAl_ORezervPolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonEncoderActive->setText(QCoreApplication::translate("MainWindow", "EncoderActive", nullptr));
        comboBoxSRVRDYPolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxSRVRDYPolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxSRVRDYPolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonMicroSteps->setText(QCoreApplication::translate("MainWindow", "MicroSteps", nullptr));
        pushButtonRezervOn->setText(QCoreApplication::translate("MainWindow", "RezervOn", nullptr));
        pushButtonSaveMaxSpeed->setText(QCoreApplication::translate("MainWindow", "SaveMaxSpeed", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        comboBoxDirPolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxDirPolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxDirPolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        comboBoxINPOSPolarity->setItemText(0, QCoreApplication::translate("MainWindow", "Inverted", nullptr));
        comboBoxINPOSPolarity->setItemText(1, QCoreApplication::translate("MainWindow", "NotInverted", nullptr));
        comboBoxINPOSPolarity->setItemText(2, QCoreApplication::translate("MainWindow", "UnknownInverted", nullptr));

        pushButtonSensor1Polarity->setText(QCoreApplication::translate("MainWindow", "Sensor1Polarity", nullptr));
        pushButtonResetCANStep->setText(QCoreApplication::translate("MainWindow", "ResetCANStep", nullptr));
        pushButtonEncoderConfig->setText(QCoreApplication::translate("MainWindow", "EncoderConfig", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
