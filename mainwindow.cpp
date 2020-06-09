#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);//窗口最大化
    connect(ui->pushButton_saveParam, SIGNAL(clicked()), this, SLOT(saveParamToDbSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMqttClient()
{
    initWindowModule();
    initDb();
    initMqttClients();
}

void MainWindow::initDb()
{
    m_dbManager.connectDB();
    // 新建连接服务端的参数列表
    // 参数名
    QVector<QString> colNames;
    colNames << "ClientName" << "ClientId" << "Username" << "Host" << "Port" << "Password";
    // 参数值类型
    QVector<QString> colTypes;
    colTypes << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(40)";
    m_dbManager.creatTable(m_dbManager.getDB(),"db_baseparam", colNames, colTypes, -1);
    QVector<QString> colValues;
    // 添加客户端序号
    m_dbManager.addVarcharCol2Table(m_dbManager.getDB(), "db_baseparam", "ClientIndex", "1");
}

void MainWindow::initDbDataToWindow(const QSqlRecord &paramRecord)
{
    ui->lineEdit_clientName->setText(paramRecord.value("ClientName").toString());
    ui->lineEdit_clientId->setText(paramRecord.value("ClientId").toString());
    ui->lineEdit_username->setText(paramRecord.value("Username").toString());
    ui->lineEdit_host->setText(paramRecord.value("Host").toString());
    ui->lineEdit_port->setText(paramRecord.value("Port").toString());
    ui->lineEdit_password->setText(paramRecord.value("Password").toString());
    OBJ_DEBUG << paramRecord.value("ClientName").toString()
              << paramRecord.value("ClientId").toString()
              << paramRecord.value("Username").toString()
              << paramRecord.value("Host").toString()
              << paramRecord.value("Port").toString()
              << paramRecord.value("Password").toString();
}

void MainWindow::initWindowModule()
{
    // 输入的时候显示为圆点
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    // 设置为不显示
    ui->frame_setParam->setVisible(false);
    // 设置为不可编辑
    ui->pushButton_mqttClients->setEnabled(false);
    // 设置圆角边框
//    ui->frame_setParam->setStyleSheet("QFrame{border:2px groove gray;border-radius:10px;padding:2px 4px}");
}

void MainWindow::initMqttClients()
{
    int rowCountInt = m_dbManager.getTableRowCount(m_dbManager.getDB(), "db_baseparam");

    int heightInt = 100;
    int mainWinWidthInt = ui->frame_mainWindow->width();
    OBJ_DEBUG << rowCountInt << mainWinWidthInt;
    int widthMaxInt = 600;
    int widthMinInt = 400;

    for (int i = 1; i <= rowCountInt; ++i) {
        int widthInt = widthMinInt;
        QString clientIdStr = QString::number(i);
        QSqlRecord paramRecord = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam", "ClientIndex", clientIdStr);
        m_clientsPushButtonHash[clientIdStr] = new QPushButton(ui->frame_mainWindow);
        QString textStr = paramRecord.value("ClientName").toString() + "\n"
                + paramRecord.value("Host").toString() + ":"
                + paramRecord.value("Port").toString();
        m_clientsPushButtonHash[clientIdStr]->setText(textStr);
        // 设置圆角边框
        m_clientsPushButtonHash[clientIdStr]->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
        if (widthMaxInt > mainWinWidthInt / rowCountInt
                && widthMinInt < mainWinWidthInt / rowCountInt) {
            widthInt = mainWinWidthInt / rowCountInt;
        }
        m_clientsPushButtonHash[clientIdStr]->resize(widthInt, heightInt);
        connect(m_clientsPushButtonHash[clientIdStr], &QPushButton::clicked, this,
                [this,clientIdStr](){emit this->openMqttClientSignal(clientIdStr);}); // 使用lambda表达式创建信号槽
    }
    connect(this, &MainWindow::openMqttClientSignal, this, &MainWindow::openMqttClientSlot);
}

void MainWindow::connectMqttServer(const QString &clientIndex)
{
    if (!m_clientObjHash.contains(clientIndex)) {
        m_clientObjHash[clientIndex] = new ClientObj();
        m_clientObjHash[clientIndex]->setClientIndexStr(clientIndex);
        m_clientObjHash[clientIndex]->setDbManager(&m_dbManager);
        m_clientObjHash[clientIndex]->connectHost();
    }
}

void MainWindow::saveParamToDbSlot()
{
    // 保存lineEdit中的数据到数据库中
    QString clientIndexStr = "1";
    QSqlRecord paramRecord = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam",
                                                              "ClientIndex", clientIndexStr);
    QString clientNameStr = ui->lineEdit_clientName->text();
    if (clientNameStr != paramRecord.value("ClientName").toString()) {
        m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "ClientName", clientNameStr,
                                "ClientIndex", clientIndexStr);
    }
    QString clientIdStr = ui->lineEdit_clientId->text();
    if (clientIdStr != paramRecord.value("ClientId").toString()) {
        m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "ClientId", clientIdStr,
                                "ClientIndex", clientIndexStr);
    }
    QString usernameStr = ui->lineEdit_username->text();
    if (usernameStr != paramRecord.value("Username").toString()) {
        m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Username", usernameStr,
                                "ClientIndex", clientIndexStr);
    }
    QString hostStr = ui->lineEdit_host->text();
    if (hostStr != paramRecord.value("Host").toString()) {
        m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Host", hostStr,
                                "ClientIndex", clientIndexStr);
    }
    QString portStr = ui->lineEdit_port->text();
    if (portStr != paramRecord.value("Port").toString()) {
        m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Port", portStr,
                                "ClientIndex", clientIndexStr);
    }
    QString passwordStr = ui->lineEdit_password->text();
    if (passwordStr != paramRecord.value("Password").toString()) {
        m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Password", passwordStr,
                                "ClientIndex", clientIndexStr);
    }
}

void MainWindow::openMqttClientSlot(const QString clientIndex)
{
    OBJ_DEBUG << clientIndex;
    m_clientsPushButtonHash[clientIndex]->setVisible(false);
    connectMqttServer(clientIndex);
}

