#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QComboBox> // 下拉框
#include <QSpacerItem>
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
    /**
     * @brief createSubcriber 创建订阅主题的窗口
     * @param index int入参，用来计算geome的X、Y
     * @param sqlRecord 数据库行数据
     */
    void createSubcriber(const int &index, const QSqlRecord &sqlRecord);
    /**
     * @brief setSubcriberVisible 设置订阅者窗口是否可视化
     * @param isVisible 是否可视化
     */
    void setSubcriberVisible(const bool &isVisible);
    /**
     * @brief deleteSubcriber 删除客户端对应的订阅者窗体
     */
    void deleteSubcriber();
    /**
     * @brief deleteClientObj 删除mqtt客户端对象
     */
    void deleteClientObj();
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
    /**
     * @brief updatePublishTopicToDb 更新发布主题到数据库
     */
    void updatePublishTopicToDb();
    /**
     * @brief addSubcriberSlot 添加订阅者的槽函数
     */
    void addSubcriberSlot();
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
    /**
     * @brief m_publishLables 发布主题模块中的label
     */
    QVector<QLabel *> m_publishLables;
    /**
     * @brief m_publishTopicLineEdit 编辑发布主题的lienEdit
     */
    QLineEdit *m_publishTopicLineEdit;
    /**
     * @brief m_qosTypeCombox qos等级的下拉框
     */
    QComboBox *m_qosTypeCombox;
    /**
     * @brief m_cmdTypeCombox 发送命令的下拉框
     */
    QComboBox *m_cmdTypeCombox;
    /**
     * @brief m_publishPushBtn 发布主题内容的按钮
     */
    QPushButton *m_publishPushBtn;
    /**
     * @brief m_publishVLayout 发布主题的布局组件
     */
    QVBoxLayout *m_publishVLayout;
    /**
     * @brief m_cmdVLayout 发送不同命令的布局组件
     */
    QVBoxLayout *m_cmdVLayout;
    /**
     * @brief m_cmdSpaceItem 发送命令的布局间隔
     */
    QSpacerItem *m_cmdSpaceItem;
    /**
     * @brief m_publishSpacerOne publish按钮右布局间隔
     */
    QSpacerItem *m_publishSpacerRight;
    /**
     * @brief m_publishHLayout publish按钮布局组件
     */
    QHBoxLayout *m_publishHLayout;
    /**
     * @brief m_subcribeScrollAreaHash 存储订阅主题和订阅编号的hash表
     */
    QHash<QString, QScrollArea*> m_subcribeScrollAreaHash;

};
#endif // MAINWINDOW_H
