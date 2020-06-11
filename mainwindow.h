#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include "clientobj.h"
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief initMqttClient 初始化
     */
    void initMqttClient();
protected:
    /**
     * @brief resizeEvent 重新实现基类的虚函数，接收窗口大小改变的事件
     * @param event 窗口大小改变的事件
     */
    void resizeEvent(QResizeEvent * event);
private:
    /**
     * @brief initDb 初始化数据库
     */
    void initDb();
    /**
     * @brief initDbDataToWindow 用数据库数据初始化窗口lineEdit
     * @param paramRecord sql数据
     */
    void initDbDataToWindow(const QSqlRecord &paramRecord);
    /**
     * @brief initWindowModule 初始化窗体组件
     */
    void initWindowModule();
    /**
     * @brief initMqttClients 初始化MQTT客户端集群
     */
    void initMqttClients();
    /**
     * @brief connectMqttServer 连接mqtt服务端
     * @param clientIndex 客户端序号
     */
    void connectMqttServer(const QString &clientIndex);
    /**
     * @brief deleteClientsPushButton 删除mqtt客户端对应的显示列表
     * @param clientIndex 客户端序号
     */
    void deleteClientsPushButton(const QString &clientIndex);
signals:
    /**
     * @brief openMqttClientParamSignal 根据入参打开对应客户端的参数表的信号
     * @param clientIndex 客户端序号
     */
    void openMqttClientSignal(const QString clientIndex);

private slots:

    /**
     * @brief saveParamToDbSlot 保存参数到数据库中
     */
    void saveParamToDbSlot();
    /**
     * @brief openMqttClientParamSlot 根据入参打开对应客户端的参数表的槽函数
     * @param clientIndex 客户端序号
     */
    void openMqttClientSlot(const QString clientIndex);
    /**
     * @brief createMqttClientSlot 创建MQTT客户端的槽函数
     */
    void createMqttClientSlot();
    /**
     * @brief returnMqttClientsWindowSlot 返回mqtt客户端列表界面
     */
    void returnMqttClientsWindowSlot();
    /**
     * @brief editClientParamSlot 编辑客户端参数
     */
    void editClientParamSlot();
    /**
     * @brief deleteClientParamSlot 删除客户端
     */
    void deleteClientParamSlot();
    /**
     * @brief recvConnectStateSlot 接收客户端连接状态的槽函数
     * @param connectState 客户端连接状态
     */
    void recvConnectStateSlot(const bool &connectState);
private:
    Ui::MainWindow *ui;
    /**
     * @brief m_clientObjHash mqtt客户端对象hash表
     */
    QHash<QString ,ClientObj *> m_clientObjHash;
    /**
     * @brief m_dbManager 数据库对象
     */
    DatabaseManager m_dbManager;
    /**
     * @brief m_clientsPushButtonHash 记录mqtt客户端序号和QPushButton的hash表
     */
    QHash<QString, QPushButton *> m_clientsPushButtonHash;
    /**
     * @brief m_curClientIndexStr 当前mqtt客户端序号
     */
    QString m_curClientIndexStr;
    /**
     * @brief m_returnClients 返回客户端列表
     */
    QPushButton *m_returnClientsPushButton;
    /**
     * @brief m_clientConnectStatePusnBtn MQTT客户端连接状态
     */
    QPushButton *m_clientConnectStatePusnBtn;
    /**
     * @brief m_addSubscriberPusnBtn 添加订阅者窗口
     */
    QPushButton *m_addSubscriberPusnBtn;
    /**
     * @brief m_editClientParamPushBtn 编辑当前mqtt客户端参数
     */
    QPushButton *m_editClientParamPushBtn;
    /**
     * @brief m_labelShowClientParam 显示当前客户端的一些参数
     */
    QLabel *m_labelShowClientParam;
    /**
     * @brief m_publishFrame 发布主题以及编辑payload的窗口
     */
    QFrame *m_publishFrame;
};
#endif // MAINWINDOW_H
