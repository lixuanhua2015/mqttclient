/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLineEdit *lineEdit_clientName;
    QLabel *label_2;
    QLineEdit *lineEdit_username;
    QLabel *label_3;
    QLineEdit *lineEdit_clientId;
    QLabel *label_4;
    QLineEdit *lineEdit_host;
    QLineEdit *lineEdit_port;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_saveParam;
    QWidget *tab_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1299, 682);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 10, 1041, 601));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 101, 16));
        lineEdit_clientName = new QLineEdit(tab);
        lineEdit_clientName->setObjectName(QString::fromUtf8("lineEdit_clientName"));
        lineEdit_clientName->setGeometry(QRect(10, 50, 161, 20));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 54, 12));
        lineEdit_username = new QLineEdit(tab);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setGeometry(QRect(10, 110, 161, 20));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 140, 101, 16));
        lineEdit_clientId = new QLineEdit(tab);
        lineEdit_clientId->setObjectName(QString::fromUtf8("lineEdit_clientId"));
        lineEdit_clientId->setGeometry(QRect(10, 170, 191, 20));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 210, 54, 12));
        lineEdit_host = new QLineEdit(tab);
        lineEdit_host->setObjectName(QString::fromUtf8("lineEdit_host"));
        lineEdit_host->setGeometry(QRect(10, 250, 211, 20));
        lineEdit_port = new QLineEdit(tab);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(10, 310, 113, 20));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 280, 54, 12));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 350, 54, 12));
        lineEdit_password = new QLineEdit(tab);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(10, 380, 381, 20));
        pushButton_saveParam = new QPushButton(tab);
        pushButton_saveParam->setObjectName(QString::fromUtf8("pushButton_saveParam"));
        pushButton_saveParam->setGeometry(QRect(450, 490, 80, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1299, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "MQTT Client Name", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "MQTT Client Id", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        pushButton_saveParam->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "ConnectParam", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
