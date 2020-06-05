#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_clientObj = new ClientObj();
    connect(ui->pushButton_saveParam, SIGNAL(clicked()), this, SLOT(saveParamToDbSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMqttClient()
{
    initDb();
}

void MainWindow::initDb()
{
    m_dbManager.connectDB();
    // 新建连接服务端的参数列表
    // 参数名
    QVector<QString> colNames;
    colNames << "ClientName" << "ClientId" << "Username" << "Host" << "Port" << "Password";
    // 参数值类型
    QVector<QString> colTypes;
    colTypes << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(20)" << "nvarchar(40)";
    m_dbManager.creatTable(m_dbManager.getDB(),"db_baseparam", colNames, colTypes, -1);
    QVector<QString> colValues;
    if (m_dbManager.getTableRowCount(m_dbManager.getDB(),"db_baseparam") == 0)
    {
        colValues << "clientTest" << "6402201901010001" << "TOEHOLD" << "47.111.206.60" << "1885" << "BBA17F4F2F99EAB1C519A158E56C05A8";
        m_dbManager.insertValue2Table(m_dbManager.getDB(),"db_baseparam",colNames,colValues);
        OBJ_DEBUG << m_dbManager.getTableRowCount(m_dbManager.getDB(),"t_baseparam");
    }
}

void MainWindow::connectMqttServerSlot()
{

}

void MainWindow::saveParamToDbSlot()
{
    QString clientNameStr = ui->lineEdit_clientName->text();
    m_dbManager.updateEntry(m_dbManager.getDB(),"db_baseparam", "ClientName", clientNameStr,"rowid", "1");
}

