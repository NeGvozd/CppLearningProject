#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QtSql>
#include <QVector>

enum Table{AIRPLANS,ZRK};//will be more tables


class InfoAboutElement
{
public:
    int id;
    QString name;
    int speed;
    int mass;
    Table type;

    //InfoAboutElement(int id, QString name, int speed, int mass,Table type);


};

// class Table() toDO:: create base class
class AirplansTable
{
public:
    AirplansTable();
    InfoAboutElement select(int id);
    QVector<InfoAboutElement> select_all();
};

class ZRKTable
{
public:
    ZRKTable();
    InfoAboutElement select(int id);
    QVector<InfoAboutElement> select_all();
};


#endif // DATABASE_H
