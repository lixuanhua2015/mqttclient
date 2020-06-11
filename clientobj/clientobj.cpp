#include "clientobj.h"

ClientObj::ClientObj(QObject *parent) : QObject(parent)
{
    m_mqttClient = new QMQTT::Client();
    m_mqttClient->setAutoReconnect(true);
    connect(m_mqttClient, SIGNAL(connected()), this, SLOT(mqttConnectedSlot()));
    m_checkConnectStateTimer = new QTimer;
    connect(m_checkConnectStateTimer, &QTimer::timeout, this, &ClientObj::checkMqttConnectStateSlot);
    m_checkConnectStateTimer->start(2000); // 2秒
    m_dbManagerRefere = nullptr;
    m_isConnected = false;
}

void ClientObj::connectHost()
{
    QSqlRecord paramRecord = m_dbManagerRefere->getFirstFilterRecord(m_dbManagerRefere->getDB(), "db_baseparam",
                                                                    "ClientIndex", m_clientIndexStr);
    m_clientNameStr = paramRecord.value("ClientName").toString();
    m_clientIdStr = paramRecord.value("ClientId").toString();
    m_usernameStr = paramRecord.value("Username").toString();
    m_hostStr = paramRecord.value("Host").toString();
    m_portStr = paramRecord.value("Port").toString();
    m_passwordStr = paramRecord.value("Password").toString();
    OBJ_DEBUG << m_clientIndexStr << m_clientNameStr << m_clientIdStr << m_usernameStr
              << m_hostStr << m_portStr << m_passwordStr;
    if (QHostAddress(m_hostStr).toString().isEmpty()) { // 域名
        m_mqttClient->setHostName(m_hostStr);
    } else { // IP
        m_mqttClient->setHost(QHostAddress(m_hostStr));
    }
    m_mqttClient->setPort(m_portStr.toInt());
    m_mqttClient->setKeepAlive(1000);
    m_mqttClient->setClientId(m_clientIdStr);
    m_mqttClient->setUsername(m_usernameStr);
    m_mqttClient->setPassword(m_passwordStr.toLatin1());
    m_mqttClient->connectToHost();
    OBJ_DEBUG << "mqttclient start to connect to host " << m_hostStr << m_portStr;
}

void ClientObj::mqttConnectedSlot()
{
    OBJ_DEBUG << "connected to " << m_mqttClient->host().toString() << m_mqttClient->port();
}

void ClientObj::checkMqttConnectStateSlot()
{
    OBJ_DEBUG << "Check MQTT connect state:" << m_mqttClient->isConnectedToHost();
    if (m_isConnected != m_mqttClient->isConnectedToHost()) {
        m_isConnected = m_mqttClient->isConnectedToHost();
        emit sendConnectStateSignal(m_isConnected);
    }
    if (!m_mqttClient->isConnectedToHost()) {
        OBJ_DEBUG << "MQTT not connected! start to connect";
        connectHost();
    }
}

QString ClientObj::clientIndexStr() const
{
    return m_clientIndexStr;
}

void ClientObj::setClientIndexStr(const QString &clientIndexStr)
{
    m_clientIndexStr = clientIndexStr;
}
