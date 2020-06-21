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
    // 添加客户端发布的主题
    m_dbManager.addVarcharCol2Table(m_dbManager.getDB(), "db_baseparam", "Topic", "");
    // 存储订阅者信息的数据库
    {
        colNames.clear();
        colNames << "Topic" << "Qos";
        colTypes.clear();
        colTypes << "nvarchar(100)" << "nvarchar(20)";
        m_dbManager.creatTable(m_dbManager.getDB(),"db_subcriber", colNames, colTypes, -1);
        // 添加当前客户端的index
        m_dbManager.addVarcharCol2Table(m_dbManager.getDB(), "db_subcriber", "ClientIndex", "");
        // 添加当前订阅主题的index
        m_dbManager.addVarcharCol2Table(m_dbManager.getDB(), "db_subcriber", "SubcribeIndex", "");
    }
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
    ui->frame_setParam->setStyleSheet("#frame_setParam{border:2px groove gray;border-radius:10px;padding:2px 4px}");
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
        connect(m_addSubscriberPusnBtn, &QPushButton::clicked, this, &MainWindow::addSubcriberSlot);
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
        m_publishFrame->setStyleSheet(".QFrame{border:2px groove rgb(0, 58, 85);border-radius:10px;padding:2px 4px}");
        m_publishFrame->setVisible(false);
        QStringList labelText = {"Topic to publish", "QoS", "Cmd Type"};
        for (int i = 0; i < 3; ++i) {
            m_publishLables.append(new QLabel());
            m_publishLables[i]->setParent(m_publishFrame);
            m_publishLables[i]->setText(labelText[i]);
        }
        m_publishTopicLineEdit = new QLineEdit(m_publishFrame);
        m_publishTopicLineEdit->setStyleSheet("QLineEdit{border:2px groove gray;border-radius:5px;padding:2px 4px}");
        connect(m_publishTopicLineEdit, &QLineEdit::textEdited, this, &MainWindow::updatePublishTopicToDb);
        // 初始化qos等级下拉框
        m_qosTypeCombox = new QComboBox(m_publishFrame);
        m_qosTypeCombox->setStyleSheet("QComboBox{border:2px groove gray;border-radius:5px;padding:2px 4px}");
        m_qosTypeCombox->addItem("QOS0-Almost Once");
        m_qosTypeCombox->addItem("QOS1-Atleast Once");
        m_qosTypeCombox->addItem("QOS2-Exactly Once");
        // 初始化指令类型下拉框
        m_cmdTypeCombox = new QComboBox(m_publishFrame);
        m_cmdTypeCombox->setStyleSheet("QComboBox{border:2px groove gray;border-radius:5px;padding:2px 4px}");
        m_cmdTypeCombox->addItem("Down Config"); // 下载配置
        m_cmdTypeCombox->addItem("Get Sample Param"); // 查看测点采样间隔
        m_cmdTypeCombox->addItem("Set Sample Param"); // 设置测点采样间隔
        m_cmdTypeCombox->addItem("Get Threshold"); // 查看测点阈值
        m_cmdTypeCombox->addItem("Set Threshold"); // 设置测点阈值
        m_cmdTypeCombox->addItem("Get Work Mode"); // 查看RTU工作模式
        m_cmdTypeCombox->addItem("Set Tork Mode"); // 设置RTU工作模式
        m_cmdTypeCombox->addItem("Sample"); // 遥测
        m_cmdTypeCombox->addItem("Get Time"); // 查看RTU时间
        m_cmdTypeCombox->addItem("Set Time"); // 设置RTU时间
        m_cmdTypeCombox->addItem("Sound Light Alarm"); // 远程开启声光报警
        m_cmdTypeCombox->addItem("Reboot"); // 重启RTU
        m_cmdTypeCombox->addItem("Get Status"); // 查看RTU和测点状态
        m_cmdTypeCombox->addItem("Upgrade"); // 远程升级程序
        m_cmdTypeCombox->addItem("Get Param"); // 查看测点参数
        m_cmdTypeCombox->addItem("Set Param"); // 设置测点参数
        m_cmdTypeCombox->addItem("Down Document"); // 远程下载文件
        m_publishPushBtn = new QPushButton(m_publishFrame);
        m_publishPushBtn->setStyleSheet(
                    "QPushButton{border-radius:5px;padding:2px 4px;background-color: rgb(0, 78, 118);}");
        m_publishPushBtn->setText("Publish");
        m_publishVLayout = new QVBoxLayout(m_publishFrame);
        m_cmdVLayout = new QVBoxLayout();
        m_publishHLayout = new QHBoxLayout();
        m_cmdSpaceItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
        m_publishSpacerRight = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_publishVLayout->addWidget(m_publishLables[0], 1);
        m_publishVLayout->addWidget(m_publishTopicLineEdit, 1);
        m_publishVLayout->addWidget(m_publishLables[1], 1);
        m_publishVLayout->addWidget(m_qosTypeCombox, 1);
        m_publishVLayout->addWidget(m_publishLables[2], 1);
        m_publishVLayout->addWidget(m_cmdTypeCombox, 1);

        m_publishVLayout->addItem(m_cmdVLayout);
        m_cmdVLayout->addItem(m_cmdSpaceItem);
        m_publishVLayout->setStretchFactor(m_cmdVLayout, 15);

        m_publishHLayout->addWidget(m_publishPushBtn, 1);
        m_publishHLayout->addItem(m_publishSpacerRight);
        m_publishHLayout->setStretch(1,10);

        m_publishVLayout->addItem(m_publishHLayout);
        m_publishVLayout->setStretchFactor(m_publishHLayout, 1);
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

void MainWindow::createSubcriber(const int &index, const QSqlRecord &sqlRecord)
{
    if (m_subcribeScrollAreaHash.contains(sqlRecord.value("SubcribeIndex").toString())) {
        m_subcribeScrollAreaHash[sqlRecord.value("SubcribeIndex").toString()]->setVisible(true);
        return;
    }
    QScrollArea *scrollArea = new QScrollArea(ui->frame_mainWindow);
    m_subcribeScrollAreaHash.insert(sqlRecord.value("SubcribeIndex").toString(), scrollArea);
    scrollArea->setStyleSheet(".QScrollArea{border:2px groove gray;border-radius:5px;padding:2px 4px}");
    int geomeX = index % 3 * width() / 3;
    int geomeY = index / 3 * 800;
    OBJ_DEBUG << geomeX << geomeY;
    scrollArea->setGeometry(geomeX, geomeY + m_labelShowClientParam->height() + 5, width() / 3 - 18, 790);
    scrollArea->setVisible(true);
}

void MainWindow::setSubcriberVisible(const bool &isVisible)
{
    QSqlQueryModel sqlModel;
    m_dbManager.getFilterEntries(m_dbManager.getDB(), "db_subcriber",
                                                   "ClientIndex", m_curClientIndexStr, sqlModel);
    int rowCountInt = sqlModel.rowCount();
    for (int i = 0; i < rowCountInt; ++i) {
        QSqlRecord sqlRecord = sqlModel.record(i);
        m_subcribeScrollAreaHash[sqlRecord.value("SubcribeIndex").toString()]->setVisible(isVisible);
    }
}

void MainWindow::deleteSubcriber()
{
    QSqlQueryModel sqlModel;
    m_dbManager.getFilterEntries(m_dbManager.getDB(), "db_subcriber",
                                                   "ClientIndex", m_curClientIndexStr, sqlModel);
    int rowCountInt = sqlModel.rowCount();
    OBJ_DEBUG << m_subcribeScrollAreaHash.size();
    for (int i = 0; i < rowCountInt; ++i) {
        QSqlRecord sqlRecord = sqlModel.record(i);
        if (m_subcribeScrollAreaHash.contains(sqlRecord.value("SubcribeIndex").toString())) {
            delete m_subcribeScrollAreaHash[sqlRecord.value("SubcribeIndex").toString()];
            m_subcribeScrollAreaHash.remove(sqlRecord.value("SubcribeIndex").toString());
        }
    }
    OBJ_DEBUG << m_subcribeScrollAreaHash.size();
}

void MainWindow::deleteClientObj()
{
    if (m_clientObjHash.contains(m_curClientIndexStr)) {
        delete m_clientObjHash[m_curClientIndexStr];
        m_clientObjHash.remove(m_curClientIndexStr);
    }
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
    int clientCountInt = m_dbManager.getTableRowCount(m_dbManager.getDB(), "db_baseparam");
    if (clientIndexStr.toInt() <= m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam", "rowid",
                                                                   QString::number(clientCountInt)).value("ClientIndex").toInt()) {
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
        colClientParam.append("");
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
        m_publishTopicLineEdit->setText(paramRecord.value("Topic").toString());
        m_labelShowClientParam->setText(showParamStr);
        m_labelShowClientParam->setVisible(true);
    }
    // 初始化publish模块的内容
    {
        m_publishFrame->setGeometry(0, m_labelShowClientParam->height() + 5, width() / 3 - 18, 790);
        m_publishFrame->setVisible(true);
    }
    // 初始化subcriber模块
    {
        QSqlQueryModel sqlModel;
        m_dbManager.getFilterEntries(m_dbManager.getDB(), "db_subcriber",
                                                       "ClientIndex", m_curClientIndexStr, sqlModel);
        int rowCountInt = sqlModel.rowCount();
        for (int i = 0; i < rowCountInt; ++i) {
            QSqlRecord sqlRecord = sqlModel.record(i);
            createSubcriber(i + 1, sqlRecord);
        }
    }
}

void MainWindow::createMqttClientSlot()
{
    ui->frame_setParam->setVisible(true);
    for (int i = 0; i < m_clientsPushButtonHash.size(); ++i) {
        m_clientsPushButtonHash.values().at(i)->setVisible(false);
    }
    int rowCountInt = m_dbManager.getTableRowCount(m_dbManager.getDB(), "db_baseparam");
    int clientMaxIndexInt = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_baseparam", "rowid",
                                                             QString::number(rowCountInt)).value("ClientIndex").toInt();
    m_curClientIndexStr = QString::number(clientMaxIndexInt + 1);
    OBJ_DEBUG << rowCountInt << clientMaxIndexInt;
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
    m_publishFrame->setVisible(false);
    setSubcriberVisible(false);
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
    m_publishFrame->setVisible(false);
    setSubcriberVisible(false);
}

void MainWindow::deleteClientParamSlot()
{
    deleteClientObj();
    QString cmdStr = "ClientIndex="+m_curClientIndexStr;
    deleteSubcriber();
    m_dbManager.deleteEntries(m_dbManager.getDB(), "db_baseparam", cmdStr);
    m_dbManager.deleteEntries(m_dbManager.getDB(), "db_subcriber", cmdStr);
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

void MainWindow::updatePublishTopicToDb()
{
    m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "Topic", m_publishTopicLineEdit->text(),
                            "ClientIndex", m_curClientIndexStr);
}

void MainWindow::addSubcriberSlot()
{
    // 订阅者初始化信息保存到数据库
    {
        QVector<QString> colSubcriberParam;
        colSubcriberParam.clear();
        colSubcriberParam.append("Topic to subcribe");
        colSubcriberParam.append("0");
        colSubcriberParam.append(m_curClientIndexStr);
        int rowCountInt = m_dbManager.getTableRowCount(m_dbManager.getDB(), "db_subcriber");
        int subcribeIndexInt = m_dbManager.getFirstFilterRecord(m_dbManager.getDB(), "db_subcriber", "rowid",
                                         QString::number(rowCountInt)).value("SubcribeIndex").toInt();
        colSubcriberParam.append(QString::number(subcribeIndexInt + 1));
        m_dbManager.insertValue2Table(m_dbManager.getDB(),"db_subcriber",colSubcriberParam);
    }
    QSqlQueryModel sqlModel;
    m_dbManager.getFilterEntries(m_dbManager.getDB(), "db_subcriber",
                                                   "ClientIndex", m_curClientIndexStr, sqlModel);
    int rowCountInt = sqlModel.rowCount();
    QSqlRecord sqlRecord = sqlModel.record(rowCountInt - 1);
    createSubcriber(rowCountInt, sqlRecord);
}

