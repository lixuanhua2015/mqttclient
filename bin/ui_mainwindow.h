/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_7;
    QFrame *frame_menuButton;
    QPushButton *pushButton_mqttClients;
    QPushButton *pushButton_createMqttClient;
    QFrame *frame_mainWindow;
    QFrame *frame_setParam;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *lineEdit_port;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_username;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *lineEdit_password;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_host;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_clientName;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_saveParam;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_clientId;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1299, 682);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        frame_menuButton = new QFrame(centralwidget);
        frame_menuButton->setObjectName(QString::fromUtf8("frame_menuButton"));
        frame_menuButton->setFrameShape(QFrame::StyledPanel);
        frame_menuButton->setFrameShadow(QFrame::Raised);
        pushButton_mqttClients = new QPushButton(frame_menuButton);
        pushButton_mqttClients->setObjectName(QString::fromUtf8("pushButton_mqttClients"));
        pushButton_mqttClients->setGeometry(QRect(10, 10, 101, 20));
        pushButton_createMqttClient = new QPushButton(frame_menuButton);
        pushButton_createMqttClient->setObjectName(QString::fromUtf8("pushButton_createMqttClient"));
        pushButton_createMqttClient->setGeometry(QRect(130, 10, 151, 20));
        pushButton_createMqttClient->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 255, 127);"));

        verticalLayout_7->addWidget(frame_menuButton);

        frame_mainWindow = new QFrame(centralwidget);
        frame_mainWindow->setObjectName(QString::fromUtf8("frame_mainWindow"));
        frame_mainWindow->setFrameShape(QFrame::StyledPanel);
        frame_mainWindow->setFrameShadow(QFrame::Raised);
        frame_setParam = new QFrame(frame_mainWindow);
        frame_setParam->setObjectName(QString::fromUtf8("frame_setParam"));
        frame_setParam->setGeometry(QRect(10, 0, 561, 251));
        frame_setParam->setFrameShape(QFrame::StyledPanel);
        frame_setParam->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_setParam);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(frame_setParam);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_5->addLayout(horizontalLayout_5);

        lineEdit_port = new QLineEdit(frame_setParam);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));

        verticalLayout_5->addWidget(lineEdit_port);


        gridLayout->addLayout(verticalLayout_5, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(frame_setParam);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        lineEdit_username = new QLineEdit(frame_setParam);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));

        verticalLayout_2->addWidget(lineEdit_username);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(frame_setParam);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_6->addLayout(horizontalLayout_6);

        lineEdit_password = new QLineEdit(frame_setParam);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));

        verticalLayout_6->addWidget(lineEdit_password);


        gridLayout->addLayout(verticalLayout_6, 2, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(7);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(frame_setParam);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_4);

        lineEdit_host = new QLineEdit(frame_setParam);
        lineEdit_host->setObjectName(QString::fromUtf8("lineEdit_host"));

        verticalLayout_4->addWidget(lineEdit_host);


        gridLayout->addLayout(verticalLayout_4, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(frame_setParam);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        lineEdit_clientName = new QLineEdit(frame_setParam);
        lineEdit_clientName->setObjectName(QString::fromUtf8("lineEdit_clientName"));

        verticalLayout->addWidget(lineEdit_clientName);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        pushButton_saveParam = new QPushButton(frame_setParam);
        pushButton_saveParam->setObjectName(QString::fromUtf8("pushButton_saveParam"));

        horizontalLayout_7->addWidget(pushButton_saveParam);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_7, 3, 0, 1, 2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(frame_setParam);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        lineEdit_clientId = new QLineEdit(frame_setParam);
        lineEdit_clientId->setObjectName(QString::fromUtf8("lineEdit_clientId"));

        verticalLayout_3->addWidget(lineEdit_clientId);


        gridLayout->addLayout(verticalLayout_3, 2, 0, 1, 1);


        verticalLayout_7->addWidget(frame_mainWindow);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 19);

        gridLayout_2->addLayout(verticalLayout_7, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_mqttClients->setText(QCoreApplication::translate("MainWindow", "MQTT CLIENTS", nullptr));
        pushButton_createMqttClient->setText(QCoreApplication::translate("MainWindow", "Create MQTT Client", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        lineEdit_port->setText(QCoreApplication::translate("MainWindow", "1885", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        lineEdit_username->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        lineEdit_password->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        lineEdit_host->setText(QCoreApplication::translate("MainWindow", "47.111.206.60", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "MQTT Client Name", nullptr));
        lineEdit_clientName->setText(QCoreApplication::translate("MainWindow", "MQTT Client Name", nullptr));
        pushButton_saveParam->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "MQTT Client Id", nullptr));
        lineEdit_clientId->setText(QCoreApplication::translate("MainWindow", "6402202001010001", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
