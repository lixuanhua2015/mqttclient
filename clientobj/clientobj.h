#ifndef CLIENTOBJ_H
#define CLIENTOBJ_H
#include <QObject>
#include "qmqtt.h"
#include "baseparam.h"
#include "databasemanager.h"

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
    /**
     * @brief clientIndexStr 获取客户端序号
     * @return 客户端序号
     */
    QString clientIndexStr() const;
    /**
     * @brief setClientIndexStr 设置客户端序号
     * @param clientIndexStr 客户端序号
     */
    void setClientIndexStr(const QString &clientIndexStr);
    void setDbManager(DatabaseManager *dbManager)
    {
        if (ASSERT_POINT_IS_NULL(m_dbManagerRefere)) {
            OBJ_DEBUG;
            m_dbManagerRefere = dbManager;
        }
    }

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
    /**
     * @brief m_clientIndexStr 记录客户端序号
     */
    QString m_clientIndexStr;
    /**
     * @brief m_dbManagerRefere 数据库指针
     */
    DatabaseManager *m_dbManagerRefere;
    /**
     * @brief m_clientNameStr 客户端名称
     */
    QString m_clientNameStr;
    /**
     * @brief m_clientIdStr 连接服务器的客户端ID
     */
    QString m_clientIdStr;
    /**
     * @brief m_usernameStr 连接服务器的用户名
     */
    QString m_usernameStr;
    /**
     * @brief m_hostStr 服务器IP或者域名
     */
    QString m_hostStr;
    /**
     * @brief m_portStr 连接服务器的端口
     */
    QString m_portStr;
    /**
     * @brief m_passwordStr 连接服务器的密码
     */
    QString m_passwordStr;
};

#endif // CLIENTOBJ_H
