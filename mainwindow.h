#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
     */
    void initDbDataToWindow();
    /**
     * @brief initWindowModule 初始化窗体组件
     */
    void initWindowModule();
    /**
     * @brief connectMqttServer 连接mqtt服务端
     * @param clientIndex 客户端序号
     */
    void connectMqttServer(const QString &clientIndex);

private slots:

    /**
     * @brief saveParamToDbSlot 保存参数到数据库中
     */
    void saveParamToDbSlot();

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
};
#endif // MAINWINDOW_H
