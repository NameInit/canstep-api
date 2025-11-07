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
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonDebugOn;
    QPushButton *pushButtonBoard;
    QLineEdit *lineEditBoard;
    QPushButton *pushButtonSteps;
    QLineEdit *lineEditSteps;
    QPushButton *pushButtonSpeed;
    QLineEdit *lineEditSpeed;
    QPushButton *pushButtonAccel;
    QLineEdit *lineEditAccel;
    QPushButton *pushButtonDecel;
    QLineEdit *lineEditDecel;
    QPushButton *pushButtonForward;
    QPushButton *pushButtonBackward;
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
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 20, 230, 220));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonConnect = new QPushButton(widget);
        pushButtonConnect->setObjectName("pushButtonConnect");

        gridLayout->addWidget(pushButtonConnect, 0, 0, 1, 1);

        pushButtonDebugOn = new QPushButton(widget);
        pushButtonDebugOn->setObjectName("pushButtonDebugOn");

        gridLayout->addWidget(pushButtonDebugOn, 0, 1, 1, 1);

        pushButtonBoard = new QPushButton(widget);
        pushButtonBoard->setObjectName("pushButtonBoard");

        gridLayout->addWidget(pushButtonBoard, 1, 0, 1, 1);

        lineEditBoard = new QLineEdit(widget);
        lineEditBoard->setObjectName("lineEditBoard");

        gridLayout->addWidget(lineEditBoard, 1, 1, 1, 1);

        pushButtonSteps = new QPushButton(widget);
        pushButtonSteps->setObjectName("pushButtonSteps");

        gridLayout->addWidget(pushButtonSteps, 2, 0, 1, 1);

        lineEditSteps = new QLineEdit(widget);
        lineEditSteps->setObjectName("lineEditSteps");

        gridLayout->addWidget(lineEditSteps, 2, 1, 1, 1);

        pushButtonSpeed = new QPushButton(widget);
        pushButtonSpeed->setObjectName("pushButtonSpeed");

        gridLayout->addWidget(pushButtonSpeed, 3, 0, 1, 1);

        lineEditSpeed = new QLineEdit(widget);
        lineEditSpeed->setObjectName("lineEditSpeed");

        gridLayout->addWidget(lineEditSpeed, 3, 1, 1, 1);

        pushButtonAccel = new QPushButton(widget);
        pushButtonAccel->setObjectName("pushButtonAccel");

        gridLayout->addWidget(pushButtonAccel, 4, 0, 1, 1);

        lineEditAccel = new QLineEdit(widget);
        lineEditAccel->setObjectName("lineEditAccel");

        gridLayout->addWidget(lineEditAccel, 4, 1, 1, 1);

        pushButtonDecel = new QPushButton(widget);
        pushButtonDecel->setObjectName("pushButtonDecel");

        gridLayout->addWidget(pushButtonDecel, 5, 0, 1, 1);

        lineEditDecel = new QLineEdit(widget);
        lineEditDecel->setObjectName("lineEditDecel");

        gridLayout->addWidget(lineEditDecel, 5, 1, 1, 1);

        pushButtonForward = new QPushButton(widget);
        pushButtonForward->setObjectName("pushButtonForward");

        gridLayout->addWidget(pushButtonForward, 6, 0, 1, 1);

        pushButtonBackward = new QPushButton(widget);
        pushButtonBackward->setObjectName("pushButtonBackward");

        gridLayout->addWidget(pushButtonBackward, 6, 1, 1, 1);

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
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        pushButtonDebugOn->setText(QCoreApplication::translate("MainWindow", "debugOn", nullptr));
        pushButtonBoard->setText(QCoreApplication::translate("MainWindow", "board", nullptr));
        pushButtonSteps->setText(QCoreApplication::translate("MainWindow", "steps", nullptr));
        pushButtonSpeed->setText(QCoreApplication::translate("MainWindow", "speed", nullptr));
        pushButtonAccel->setText(QCoreApplication::translate("MainWindow", "accel", nullptr));
        pushButtonDecel->setText(QCoreApplication::translate("MainWindow", "decel", nullptr));
        pushButtonForward->setText(QCoreApplication::translate("MainWindow", "forward", nullptr));
        pushButtonBackward->setText(QCoreApplication::translate("MainWindow", "backward", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
