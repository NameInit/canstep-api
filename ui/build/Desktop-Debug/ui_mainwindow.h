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
    QPushButton *pushButtonBrakeOff;
    QPushButton *pushButtonBoard;
    QLineEdit *lineEditSteps;
    QPushButton *pushButtonHomingZero;
    QLineEdit *lineEditBoard;
    QPushButton *pushButtonDebugOn;
    QPushButton *pushButtonBackward;
    QPushButton *pushButtonBrakeOn;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonAccel;
    QLineEdit *lineEditDecel;
    QPushButton *pushButtonHomingMax;
    QPushButton *pushButtonSpeed;
    QLineEdit *lineEditSpeed;
    QPushButton *pushButtonSteps;
    QPushButton *pushButtonRezervOff;
    QPushButton *pushButtonRezervOn;
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
        layoutWidget->setGeometry(QRect(20, 20, 231, 348));
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

        pushButtonBrakeOff = new QPushButton(layoutWidget);
        pushButtonBrakeOff->setObjectName("pushButtonBrakeOff");

        gridLayout->addWidget(pushButtonBrakeOff, 9, 0, 1, 1);

        pushButtonBoard = new QPushButton(layoutWidget);
        pushButtonBoard->setObjectName("pushButtonBoard");

        gridLayout->addWidget(pushButtonBoard, 1, 0, 1, 1);

        lineEditSteps = new QLineEdit(layoutWidget);
        lineEditSteps->setObjectName("lineEditSteps");

        gridLayout->addWidget(lineEditSteps, 2, 1, 1, 1);

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

        lineEditDecel = new QLineEdit(layoutWidget);
        lineEditDecel->setObjectName("lineEditDecel");

        gridLayout->addWidget(lineEditDecel, 5, 1, 1, 1);

        pushButtonHomingMax = new QPushButton(layoutWidget);
        pushButtonHomingMax->setObjectName("pushButtonHomingMax");

        gridLayout->addWidget(pushButtonHomingMax, 7, 1, 1, 1);

        pushButtonSpeed = new QPushButton(layoutWidget);
        pushButtonSpeed->setObjectName("pushButtonSpeed");

        gridLayout->addWidget(pushButtonSpeed, 3, 0, 1, 1);

        lineEditSpeed = new QLineEdit(layoutWidget);
        lineEditSpeed->setObjectName("lineEditSpeed");

        gridLayout->addWidget(lineEditSpeed, 3, 1, 1, 1);

        pushButtonSteps = new QPushButton(layoutWidget);
        pushButtonSteps->setObjectName("pushButtonSteps");

        gridLayout->addWidget(pushButtonSteps, 2, 0, 1, 1);

        pushButtonRezervOff = new QPushButton(layoutWidget);
        pushButtonRezervOff->setObjectName("pushButtonRezervOff");

        gridLayout->addWidget(pushButtonRezervOff, 10, 0, 1, 1);

        pushButtonRezervOn = new QPushButton(layoutWidget);
        pushButtonRezervOn->setObjectName("pushButtonRezervOn");

        gridLayout->addWidget(pushButtonRezervOn, 10, 1, 1, 1);

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
        pushButtonBrakeOff->setText(QCoreApplication::translate("MainWindow", "BrakeOff", nullptr));
        pushButtonBoard->setText(QCoreApplication::translate("MainWindow", "board", nullptr));
        pushButtonHomingZero->setText(QCoreApplication::translate("MainWindow", "HomingZero", nullptr));
        pushButtonDebugOn->setText(QCoreApplication::translate("MainWindow", "debugOn", nullptr));
        pushButtonBackward->setText(QCoreApplication::translate("MainWindow", "backward", nullptr));
        pushButtonBrakeOn->setText(QCoreApplication::translate("MainWindow", "BrakeOn", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        pushButtonAccel->setText(QCoreApplication::translate("MainWindow", "accel", nullptr));
        pushButtonHomingMax->setText(QCoreApplication::translate("MainWindow", "HomingMax", nullptr));
        pushButtonSpeed->setText(QCoreApplication::translate("MainWindow", "speed", nullptr));
        pushButtonSteps->setText(QCoreApplication::translate("MainWindow", "steps", nullptr));
        pushButtonRezervOff->setText(QCoreApplication::translate("MainWindow", "RezervOff", nullptr));
        pushButtonRezervOn->setText(QCoreApplication::translate("MainWindow", "RezervOn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
