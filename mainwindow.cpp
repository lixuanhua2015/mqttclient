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
    initDbDataToWindow();
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
    if (m_dbManager.getTableRowCount(m_dbManager.getDB(),"db_baseparam") == 0)
    {
        colValues << "clientTest" << "6402201901010001" << "TOEHOLD" << "47.111.206.60" << "1885" << "BBA17F4F2F99EAB1C519A158E56C05A8";
        m_dbManager.insertValue2Table(m_dbManager.getDB(),"db_baseparam",colNames,colValues);
        OBJ_DEBUG << m_dbManager.getTableRowCount(m_dbManager.getDB(),"t_baseparam");
    }
    // 添加客户端序号
    m_dbManager.addVarcharCol2Table(m_dbManager.getDB(), "db_baseparam", "ClientIndex", "1");
}

void MainWindow::initDbDataToWindow()
{
    QSqlRecord paramRecord = m_dbManager.getTabelRecord(m_dbManager.getDB(), "db_baseparam", 0);

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
    // 根据参数连接服务器
    connectMqttServer(clientIndexStr);
}

