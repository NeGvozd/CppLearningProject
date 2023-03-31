#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>

class AirplansDB
{
public:
    AirplansDB();
    int connection();
    int closing();
    int select(int id);
    QSqlDatabase return_db();
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
