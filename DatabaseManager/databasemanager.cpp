#include "databasemanager.h"
#include <QSqlError>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::connectDB()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mqttclient.db");

    if (db.open()){
        OBJ_DEBUG << "open db sucess";
    } else {
        OBJ_DEBUG << "open db fail";
    }
     OBJ_DEBUG<<Q_FUNC_INFO<<__LINE__<<db.connectionName()<<db.databaseName();
}

void DatabaseManager::connectDB(QString dbName)
{
    QSqlDatabase db;

    if (dbName == NULL){
        db = QSqlDatabase::addDatabase("QSQLITE");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE",dbName);
    }
    db.setDatabaseName("mqttclient.db");

    if (db.open()){
        OBJ_DEBUG << "open db sucess";
    } else {
        OBJ_DEBUG << "open db fail";
    }
    OBJ_DEBUG<<Q_FUNC_INFO<<__LINE__<<db.connectionName()<<db.databaseName();
}

QSqlDatabase DatabaseManager::getDB(QString dbName)
{
    QSqlDatabase db;

    if (dbName == NULL){
        db = QSqlDatabase::database();
    } else {
        if (QSqlDatabase::contains(dbName)){
            db = QSqlDatabase::database(dbName);
        } else {
            db = QSqlDatabase::addDatabase("QSQLITE",dbName);
        }
    }
    return db;
}

QSqlDatabase DatabaseManager::getDB()
{
    QSqlDatabase db;
    db = QSqlDatabase::database();
    return db;
}

void DatabaseManager::disconnectDB(QString dbName)
{
    if (dbName != NULL && QSqlDatabase::contains(dbName)){
        QSqlDatabase::removeDatabase(dbName);
    }
}

void DatabaseManager::disconnectDB()
{
    QString s;
    {
        s = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(s);
}

bool DatabaseManager::isContainTable(QSqlDatabase db, QString tableName)
{
    QSqlQuery query(db);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name = '%1'").arg(tableName));
    if (query.next()){
        if (query.value(0).toInt() == 0) {
            query.finish();
            return false;
        } else {
            query.finish();
            return true;
        }
    }
    query.finish();
    return false;
}

void DatabaseManager::creatTable(QSqlDatabase db, QString tableName, QVector<QString> colNames, QVector<QString> colType, int keyCol)
{
    if (isContainTable(db,tableName)) {
        QSqlQuery queryTemp(db);
        QString strQuer = "PRAGMA table_info([" + tableName + "])";
        queryTemp.exec(strQuer);
        int index = 0;
        bool match = true;
        while(queryTemp.next() && index < colNames.size()) {
            OBJ_DEBUG << queryTemp.record().value(1).toString() << colNames[index];
            if (queryTemp.record().value(1).toString() != colNames[index]) {
                match = false;
                break;
            }
            index++;
        }
        if (match) {
            return;//如果已经存在表，就退出
        } else {
            queryTemp.finish();
            OBJ_DEBUG << deleteTable(tableName);
        }
    }

    QSqlQuery query(db);
    QString strQuery ="create table if not exists " + tableName + "(";

    for (int i = 0; i < colNames.size(); i++)
    {
        strQuery += colNames[i] + " " + colType[i];
        if (keyCol == i) strQuery += " PRIMARY KEY autoincrement";        //一般主键都在服务器中设置好了，这里不太需要
        if (i != colNames.size() - 1) strQuery += ",";
    }

    strQuery += ")";
    query.exec(strQuery);
    query.finish();
}

void DatabaseManager::addValue2Table(QSqlDatabase db, QString tableName, QVector<QString> values)
{
    QSqlQuery query(db);
    QString strQuery = "insert into " + tableName + " values(";

    for (int i = 0; i < values.size(); i++)
    {
        strQuery += values[i];
        if (i != values.size() -1) strQuery += ",";
    }

    strQuery += ")";
    query.exec(strQuery);
    query.finish();
}

QSqlQuery DatabaseManager::getSelectValues(QSqlDatabase db, QString strQuery)
{
    QSqlQuery query(db);
    query.exec(strQuery);
    return query;
}

QSqlQuery DatabaseManager::getFilterValues(QSqlDatabase db, QString tableName, QString colName, QString colValue)
{
    QString strQuery = "select * from " + tableName + " where " + colName + " = " + colValue;
    QSqlQuery query(db);
    query.exec(strQuery);
    return query;
}

bool DatabaseManager::updateAndDelete(QSqlDatabase db, QString strQuery)
{
    QSqlQuery query(db);
    bool f = query.exec(strQuery);
    query.finish();
    return f;
}

bool DatabaseManager::isContainDB(QString dbName)
{
    return QSqlDatabase::contains(dbName);
}

int DatabaseManager::getTableRowCount(QSqlDatabase db, QString tableName)
{
    QSqlTableModel model(0,db);
    model.setTable(tableName);
    model.select();

    return model.rowCount();
}

void DatabaseManager::insertValue2Table(QSqlDatabase db, QString tableName, QVector<QString> colName, QVector<QString> value)
{
    QSqlTableModel model(0,db);
    model.setTable(tableName);
    model.select();
    QSqlRecord record = model.record();
    for (int i = 0; i < colName.size(); i++)
        record.setValue(colName[i],value[i]);
    model.insertRecord(model.rowCount(),record);
}

void DatabaseManager::insertValue2Table(QSqlDatabase db, QString tableName, QVector<QString> value)
{
    QSqlTableModel model(0,db);
    model.setTable(tableName);
    model.select();

    QSqlRecord record = model.record();
    for (int i = 0; i < record.count(); i++)
        record.setValue(i,value[i]);
    OBJ_DEBUG<<Q_FUNC_INFO<<__LINE__<<model.insertRecord(model.rowCount(),record)<<value;
}

QSqlRecord DatabaseManager::getTabelRecord(QSqlDatabase db, QString tableName, int index)
{
    QSqlTableModel model(0,db);
    model.setTable(tableName);
    model.select();

    QSqlRecord record;
    if (model.rowCount() > index)
        record = model.record(index);
    else
        record = model.record();

    return record;
}

void DatabaseManager::clearTableValues(QSqlDatabase db, QString tableName)
{
    QSqlTableModel model(0,db);
    model.setTable(tableName);
    model.select();

    int k = model.rowCount();
    while (k > 0)
    {
        k--;
        model.removeRow(k);
    }
    OBJ_DEBUG << "remove all";
}

QSqlRecord DatabaseManager::getFirstFilterRecord(QSqlDatabase db, QString tableName, QString colName, QString colValue)
{
    QSqlTableModel model(0,db);
    QString strFilter = colName + "='" + colValue + "'";

    model.setTable(tableName);
    model.setFilter(strFilter);
    model.select();

    if (model.rowCount() == 0)
        return model.record();
    else
        return model.record(0);
}

bool DatabaseManager::updateEntry(
        QSqlDatabase db,
        const QString &tabName,
        const QString &entryName,
        const QString &entryVal,
        const QString &idColName,
        const QString &idVal
        )
{
    // 修改网关下发的配置无法更新到数据库的问题；
    QSqlQuery m_query(db);
    QString sql = "UPDATE " + tabName + " SET " + entryName
                + " = '" + entryVal + "' WHERE " + idColName
                + " = '" + idVal
            + "'";
    m_query.prepare(sql);
    if(!m_query.exec(sql)) {
        OBJ_DEBUG<<"Cannot update " + entryName + "!";
        OBJ_DEBUG<<"CMD: "<<sql;
        m_query.finish();
        return false;
    }
    m_query.finish();
    return true;
}

bool DatabaseManager::updateEntry(QSqlDatabase db,const QString &tabName,
        const QString &entryName,
        const QString &entryVal,
        const QString &idColName,
        const QString &idVal,        
        const QString &sign,
        const int &num
        )
{
    QSqlQuery m_query(db);
    QString sql = "UPDATE " + tabName + " SET " + entryName + " = '" + entryVal
            + "' WHERE " + sign + " in (select " + sign + " from " + tabName
            + " where " + idColName + " = " + idVal + " limit 0,"+ QString::number(num,10) +")";

    m_query.prepare(sql);
    if(!m_query.exec(sql)) {
        OBJ_DEBUG<<"Cannot update " + entryName + "!";
        OBJ_DEBUG<<"CMD: "<<sql;
        m_query.finish();
        return false;
    }

    m_query.finish();
    return true;
}


bool DatabaseManager::getFilterEntries(QSqlDatabase db, QString tabName, QString colName, QString colValue, QSqlQueryModel &model)
{
    QString sql = "SELECT * from [" + tabName + "] where " + colName + " = " + colValue;
    model.setQuery(sql, db);

    while (model.canFetchMore())
    {
        model.fetchMore();
    }
    return true;
}

bool DatabaseManager::getFilterEntries(QSqlDatabase db, QString tabName, QString colName, QString colValue, QSqlQueryModel &model, int num)
{
    QString sql = "SELECT * from [" + tabName + "] where " + colName + " = " + colValue + " limit 0," + QString::number(num,10);
    model.setQuery(sql, db);

    while (model.canFetchMore())
    {
        model.fetchMore();
    }
    return true;
}

bool DatabaseManager::getFilterEntries(QSqlDatabase /*db*/, QString tabName, QString colName, QString colValue, QSqlQuery &query, int num)
{
    QString sql = "SELECT * from [" + tabName + "] where " + colName + " = " + colValue + " limit 0," + QString::number(num,10);
    return query.exec(sql);
}

bool DatabaseManager::deleteEntries(QSqlDatabase db,QString tabName, QString command)
{
    QSqlQuery m_query(db);
    QString sql = "delete from " + tabName + " where " + command;

    m_query.prepare(sql);
    if(!m_query.exec(sql)) {
        OBJ_DEBUG<<"Cannot delete " + tabName + "!";
        OBJ_DEBUG<<"CMD: "<<sql;
        m_query.finish();
        return false;
    }
    m_query.finish();
    // 删除特定数据后，数据库的大小并没有变化，需要用vacuum命令来清除空闲列表，然后重新加载数据库文件
    QSqlQuery vacQuery(db);
    QString vacSql = "VACUUM";
    vacQuery.prepare(vacSql);
    if(!vacQuery.exec(vacSql)) {
        OBJ_DEBUG<<vacSql << "database fail!";
    }
    vacQuery.finish();
    return true;
}

// 清除表格
bool DatabaseManager::deleteTable(QString tableName)
{
    QSqlQuery query(QSqlDatabase::database());
    QString sqlCmd = "DROP TABLE " + tableName;
    OBJ_DEBUG << "DELETE table: " << sqlCmd;
    bool ret = query.exec(sqlCmd);
    if (!ret) {
        OBJ_DEBUG << query.lastError().type() << query.lastError().text() << query.lastError().nativeErrorCode();
    }
    query.finish();
    return ret;
}

bool DatabaseManager::addValues2Table(QSqlDatabase db,QString tabName, QVector<QVector<QString> > values)
{
    QSqlQuery m_query(db);
    QString sql = "";

    db.transaction();
    for (int i = 0; i < values.length(); i++)
    {
        sql = "insert into " + tabName + " values (";
        for (int j = 0; j < values.at(i).length(); j++)
        {
            sql += "'" + values.at(i).at(j) + "'";
            if (j != values.at(i).length() - 1) sql += ",";
        }
        sql += ")";

        m_query.prepare(sql);
        if (!m_query.exec()){
            m_query.finish();
            OBJ_DEBUG << "CMD:" << sql;
            break;
        }
    }

    if (db.commit()){
        return true;
    } else {
        OBJ_DEBUG << "save data 2 db fail!";
        return false;
    }
}

bool DatabaseManager::addVarcharCol2Table(QSqlDatabase db,
        const QString &tabName, 
        const QString &colName,
        const QString &defaultV
        )
{
    QSqlQuery m_query(db);
    QString sql = "ALTER table " + tabName + " ADD " + colName + " varchar DEFAULT \'" + defaultV + "\'";
    m_query.prepare(sql);
    if (!m_query.exec()){
        OBJ_DEBUG << "Cannot add column CMD:" << sql;
        m_query.finish();
        return false;
    }
    m_query.finish();
    return true;
}

