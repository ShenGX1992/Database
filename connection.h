#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlQuery>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("EParam.db");
    if(!db.open()) return false;
    QSqlQuery query;
    query.exec(QString(
      "create table EParameter (编号 int primary key, 偏置 double, 脉宽 int, 脉间 int, 电流 double, 速度 double, 丝速 double)"));
    query.exec(QString("insert into EParameter values (0,0.3,10,4,4,31,4)"));
    query.exec(QString("insert into EParameter values (1,0.4,8,6,3,23,3)"));
    query.exec(QString("insert into EParameter values (2,0.15,9,5,2,40,2)"));
    query.exec(QString("insert into EParameter values (3,0.2,7,2,3,27,2)"));
    return true;
}
#endif // CONNECTION_H
