#include "clientobj.h"

ClientObj::ClientObj(QObject *parent) : QObject(parent)
{
    m_mqttClient = new QMQTT::Client();
    m_mqttClient->setAutoReconnect(true);
    connect(m_mqttClient, SIGNAL(connected()), this, SLOT(mqttConnectedSlot()));
}

void ClientObj::connectHost()
{

}

void ClientObj::mqttConnectedSlot()
{

}
