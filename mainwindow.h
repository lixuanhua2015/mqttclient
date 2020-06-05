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

private slots:
    /**
     * @brief connectMqttServer 连接mqtt服务端的槽函数
     */
    void connectMqttServerSlot();
    /**
     * @brief saveParamToDbSlot 保存参数到数据库中
     */
    void saveParamToDbSlot();

private:
    Ui::MainWindow *ui;
    /**
     * @brief m_clientObj mqtt客户端对象
     */
    ClientObj *m_clientObj;
    /**
     * @brief m_dbManager 数据库对象
     */
    DatabaseManager m_dbManager;
};
#endif // MAINWINDOW_H
