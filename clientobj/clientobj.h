#ifndef CLIENTOBJ_H
#define CLIENTOBJ_H
#include <QObject>

/**
 * @brief The ClientObj class MQTT客户端
 */
class ClientObj : public QObject
{
    Q_OBJECT
public:
    explicit ClientObj(QObject *parent = nullptr);
};

#endif // CLIENTOBJ_H
