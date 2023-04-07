#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QtSql>


class AirplansTable
{
public:
    AirplansTable();
    int select(int id);

};

class ZRKTable
{
public:
    ZRKTable();
    int select(int id);

};

#endif // DATABASE_H
