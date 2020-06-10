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
     * @brief m_clientsLayout 记录mqtt客户端和布局管理的hash表
     */
    QHash<QString, QLayout *> m_clientsLayout;
    /**
     * @brief m_curClientIndexStr 当前mqtt客户端序号
     */
    QString m_curClientIndexStr;
};
#endif // MAINWINDOW_H
