#ifndef CLIENTOBJ_H
#define CLIENTOBJ_H
#include <QObject>
#include "qmqtt.h"
#include "baseparam.h"

/**
 * @brief The ClientObj class MQTT客户端
 */
class ClientObj : public QObject
{
    Q_OBJECT
public:
    explicit ClientObj(QObject *parent = nullptr);
    /**
     * @brief connectHost 连接服务端
     */
    void connectHost();
private slots:
    /**
     * @brief mqttConnectedSlot 已连接的槽函数
     */
    void mqttConnectedSlot();
private:
    /**
     * @brief m_mqttClient mqtt客户端
     */
    QMQTT::Client *m_mqttClient;
};

#endif // CLIENTOBJ_H
