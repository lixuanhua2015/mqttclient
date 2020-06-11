#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QIcon>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_curClientIndexStr = "1";
    setWindowState(Qt::WindowMaximized);//窗口最大化
    connect(ui->pushButton_saveParam, SIGNAL(clicked()), this, SLOT(saveParamToDbSlot()));
    connect(ui->pushButton_createMqttClient, &QPushButton::clicked, this, &MainWindow::createMqttClientSlot);
    connect(ui->pushButton_deleteClient, &QPushButton::clicked, this, &MainWindow::deleteClientParamSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMqttClient()
{
    initWindowModule();
    initDb();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    OBJ_DEBUG << width() << width();
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
    ui->frame_mainWindow->setWindowState(Qt::WindowMaximized);//窗口最大化
    // 设置圆角边框
    ui->frame_setParam->setStyleSheet("QFrame{border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->frame_menuButton->setStyleSheet("QPushButton{border:2px groove gray;border-radius:5px;padding:2px 4px}");

    m_returnClientsPushButton = new QPushButton(ui->frame_menuButton);
    // 设置图标
    QIcon returnIcon(tr("../返回.png"));
    m_returnClientsPushButton->setIcon(returnIcon);
    m_returnClientsPushButton->setVisible(false);
    connect(m_returnClientsPushButton, &QPushButton::clicked, this, &MainWindow::returnMqttClientsWindowSlot);
    // 将m_returnClientsPushButton插入到布局组件中，插入到第一位
    ui->horizontalLayout_8->insertWidget(0, m_returnClientsPushButton);
    // 设置布局组件中元素之间的间隔
    ui->horizontalLayout_8->setSpacing(10);
    // 连接状态的按钮
    {
        m_clientConnectStatePusnBtn = new QPushButton(ui->frame_menuButton);
        m_clientConnectStatePusnBtn->setText("Not Connected");
        m_clientConnectStatePusnBtn->setStyleSheet("QPushButton{background-color: rgb(255, 0, 0)}");
        ui->horizontalLayout_8->insertWidget(1, m_clientConnectStatePusnBtn);
        m_clientConnectStatePusnBtn->setVisible(false);
    }
    // 添加订阅者按钮配置
    {
        m_addSubscriberPusnBtn = new QPushButton(ui->frame_menuButton);
        m_addSubscriberPusnBtn->setText("Add subscriber");
        ui->horizontalLayout_8->insertWidget(2, m_addSubscriberPusnBtn);
        m_addSubscriberPusnBtn->setVisible(false);
    }
    // 编辑当前MQTT客户端参数
    {
        m_editClientParamPushBtn = new QPushButton(ui->frame_menuButton);
        QIcon editIcon(tr("../编辑.png"));
        m_editClientParamPushBtn->setIcon(editIcon);
        ui->horizontalLayout_8->insertWidget(3, m_editClientParamPushBtn);
        m_editClientParamPushBtn->setVisible(false);
        connect(m_editClientParamPushBtn, &QPushButton::clicked, this, &MainWindow::editClientParamSlot);
    }
    connect(this, &MainWindow::openMqttClientSignal, this, &MainWindow::openMqttClientSlot);
    // 初始化显示当前客户端参数
    {
         m_labelShowClientParam = new QLabel(ui->frame_mainWindow);
         m_labelShowClientParam->setVisible(false);
    }
    // 初始化发布主题和编辑payload的窗口
    {
        m_publishFrame = new QFrame(ui->frame_mainWindow);
    }
}

void MainWindow::initMqttClients()
{
    int rowCountInt = m_dbManager.getTableRowCount(m_dbManager.getDB(), "db_baseparam");

    int heightInt = 100;
    int mainWinWidthInt = width();
    OBJ_DEBUG << rowCountInt << mainWinWidthInt;
    int widthMaxInt = 400;
    int widthMinInt = 300;
    int geometryX = 0;
    int geometryY = 10;
    int geometryIndex = 0;
    int offsetInt = 1;
    for (int i = 1; i <= rowCountInt; ++i) {
        QSqlRecord paramRecord = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam", "rowid", QString::number(i));
        QString clientIdStr = paramRecord.value("ClientIndex").toString();
        OBJ_DEBUG << clientIdStr;
        if (!m_clientsPushButtonHash.contains(clientIdStr)) {
            m_clientsPushButtonHash[clientIdStr] = new QPushButton(ui->frame_mainWindow);
        }
        QString textStr = paramRecord.value("ClientName").toString() + "\n"
                + paramRecord.value("Host").toString() + ":"
                + paramRecord.value("Port").toString();
        m_clientsPushButtonHash[clientIdStr]->setText(textStr);
        // 设置圆角边框
        m_clientsPushButtonHash[clientIdStr]->setStyleSheet("border:2px groove green;border-radius:10px;padding:2px 4px");
        int widthInt = widthInt = mainWinWidthInt / rowCountInt;;
        if (widthInt > widthMaxInt) {
            widthInt = widthMaxInt;
        } else if (widthInt < widthMinInt) {
            widthInt = widthMinInt;
        }
        geometryX = ((widthInt + 10) * (i - offsetInt) + 10);
        if (geometryX + widthInt > mainWinWidthInt) {
            offsetInt = i;
            geometryX = 10;
            geometryIndex++;
            geometryY = ((heightInt + 10) * geometryIndex + 10);
        }
        m_clientsPushButtonHash[clientIdStr]->setGeometry(geometryX, geometryY, widthInt, heightInt);
        OBJ_DEBUG << geometryX << geometryY << widthInt << heightInt;
        connect(m_clientsPushButtonHash[clientIdStr], &QPushButton::clicked, this,
                [this,clientIdStr](){emit this->openMqttClientSignal(clientIdStr);}); // 使用lambda表达式创建信号槽
    }
}

void MainWindow::connectMqttServer(const QString &clientIndex)
{
    if (!m_clientObjHash.contains(clientIndex)) {
        m_clientObjHash[clientIndex] = new ClientObj();
        m_clientObjHash[clientIndex]->setClientIndexStr(clientIndex);
        m_clientObjHash[clientIndex]->setDbManager(&m_dbManager);
        m_clientObjHash[clientIndex]->connectHost();
        connect(m_clientObjHash[clientIndex], SIGNAL(sendConnectStateSignal(const bool &)),
                this, SLOT(recvConnectStateSlot(const bool &)));
    }
}

void MainWindow::deleteClientsPushButton(const QString &clientIndex)
{
    delete m_clientsPushButtonHash[clientIndex];
    m_clientsPushButtonHash.remove(clientIndex);
    OBJ_DEBUG << m_clientsPushButtonHash.size();
}

void MainWindow::saveParamToDbSlot()
{
    // 保存lineEdit中的数据到数据库中
    QString clientIndexStr = m_curClientIndexStr;
    // 说明不是新增的MQTT客户端
    QString clientNameStr = ui->lineEdit_clientName->text();
    QString clientIdStr = ui->lineEdit_clientId->text();
    QString usernameStr = ui->lineEdit_username->text();
    QString hostStr = ui->lineEdit_host->text();
    QString portStr = ui->lineEdit_port->text();
    QString passwordStr = ui->lineEdit_password->text();
    if (clientIndexStr.toInt() <= m_dbManager.getTableRowCount(m_dbManager.getDB(), "db_baseparam")) {
        QSqlRecord paramRecord = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam",
                                                                  "ClientIndex", clientIndexStr);
        if (clientNameStr != paramRecord.value("ClientName").toString()) {
            m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "ClientName", clientNameStr,
                                    "ClientIndex", clientIndexStr);
        }
        if (clientIdStr != paramRecord.value("ClientId").toString()) {
            m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "ClientId", clientIdStr,
                                    "ClientIndex", clientIndexStr);
        }
        if (usernameStr != paramRecord.value("Username").toString()) {
            m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Username", usernameStr,
                                    "ClientIndex", clientIndexStr);
        }
        if (hostStr != paramRecord.value("Host").toString()) {
            m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Host", hostStr,
                                    "ClientIndex", clientIndexStr);
        }
        if (portStr != paramRecord.value("Port").toString()) {
            m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Port", portStr,
                                    "ClientIndex", clientIndexStr);
        }
        if (passwordStr != paramRecord.value("Password").toString()) {
            m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Password", passwordStr,
                                    "ClientIndex", clientIndexStr);
        }
    } else { // 当clientIndexStr大于数据库中客户端数时，说明是新建MQTT客户端
        QVector<QString> colClientParam;
        colClientParam.clear();
        colClientParam.append(clientNameStr);
        colClientParam.append(clientIdStr);
        colClientParam.append(usernameStr);
        colClientParam.append(hostStr);
        colClientParam.append(portStr);
        colClientParam.append(passwordStr);
        colClientParam.append(clientIndexStr);
        m_dbManager.insertValue2Table(m_dbManager.getDB(),"db_baseparam",colClientParam);
    }
    initMqttClients();
}

void MainWindow::openMqttClientSlot(const QString clientIndex)
{
    OBJ_DEBUG << clientIndex;
    m_curClientIndexStr = clientIndex;
    for (int i = 0; i < m_clientsPushButtonHash.size(); ++i) {
        m_clientsPushButtonHash.values().at(i)->setVisible(false);
    }
    m_returnClientsPushButton->setVisible(true);
    ui->label_mqttClients->setVisible(false);
    ui->pushButton_createMqttClient->setVisible(false);
    m_clientConnectStatePusnBtn->setVisible(true);
    m_addSubscriberPusnBtn->setVisible(true);
    m_editClientParamPushBtn->setVisible(true);
    connectMqttServer(clientIndex);
    // 设置当前客户端一些参数
    {
        QSqlRecord paramRecord = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam",
                                                                  "ClientIndex", m_curClientIndexStr);
        QString showParamStr = paramRecord.value("ClientName").toString() + " - "
                + paramRecord.value("Host").toString() + ":" + paramRecord.value("Port").toString();
        m_labelShowClientParam->setText(showParamStr);
        m_labelShowClientParam->setVisible(true);
    }
}

void MainWindow::createMqttClientSlot()
{
    ui->frame_setParam->setVisible(true);
    for (int i = 0; i < m_clientsPushButtonHash.size(); ++i) {
        m_clientsPushButtonHash.values().at(i)->setVisible(false);
    }
    int rowCountInt = m_dbManager.getTableRowCount(m_dbManager.getDB(), "db_baseparam");
    m_curClientIndexStr = QString::number(rowCountInt + 1);
    ui->label_mqttClients->setVisible(false);
    m_returnClientsPushButton->setVisible(true);
    ui->pushButton_deleteClient->setVisible(false);
}

void MainWindow::returnMqttClientsWindowSlot()
{
    OBJ_DEBUG << width();
    for (int i = 0; i < m_clientsPushButtonHash.size(); ++i) {
        m_clientsPushButtonHash.values().at(i)->setVisible(true);
    }
    ui->label_mqttClients->setVisible(true);
    ui->pushButton_createMqttClient->setVisible(true);
    m_returnClientsPushButton->setVisible(false);
    ui->frame_setParam->setVisible(false);
    m_clientConnectStatePusnBtn->setVisible(false);
    m_addSubscriberPusnBtn->setVisible(false);
    m_editClientParamPushBtn->setVisible(false);
    m_labelShowClientParam->setVisible(false);
    // 所有客户端参数初始化
    {
        ui->lineEdit_clientName->setText("MQTT Client Name");
        ui->lineEdit_username->setText("Username");
        ui->lineEdit_clientId->setText("6405202001010001");
        ui->lineEdit_host->setText("47.111.206.60");
        ui->lineEdit_port->setText("1885");
        ui->lineEdit_password->setText("password");
    }
}

void MainWindow::editClientParamSlot()
{
    QSqlRecord paramRecord = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam",
                                                              "ClientIndex", m_curClientIndexStr);
    initDbDataToWindow(paramRecord);
    ui->frame_setParam->setVisible(true);
    ui->pushButton_deleteClient->setVisible(true);
    m_addSubscriberPusnBtn->setVisible(false);
    m_clientConnectStatePusnBtn->setVisible(false);
    m_editClientParamPushBtn->setVisible(false);
    m_labelShowClientParam->setVisible(false);
}

void MainWindow::deleteClientParamSlot()
{
    QString cmdStr = "ClientIndex="+m_curClientIndexStr;
    m_dbManager.deleteEntries(m_dbManager.getDB(), "db_baseparam", cmdStr);
    deleteClientsPushButton(m_curClientIndexStr);
    returnMqttClientsWindowSlot();
    initMqttClients();
}

void MainWindow::recvConnectStateSlot(const bool &connectState)
{
    OBJ_DEBUG << connectState;
    if (connectState) {
        m_clientConnectStatePusnBtn->setText("Connected");
        m_clientConnectStatePusnBtn->setStyleSheet("QPushButton{background-color: rgb(72, 217, 106)}");
    } else {
        m_clientConnectStatePusnBtn->setText("Not Connected");
        m_clientConnectStatePusnBtn->setStyleSheet("QPushButton{background-color: rgb(255, 0, 0)}");
    }
}

