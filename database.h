#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QtSql>
#include <QVector>

enum Table{AIRPLANS,ZRK};//will be more tables


struct InfoAboutElement
{
public:
    int id;
    QString name;
    int speed;
    int mass;
    Table type;
/*
    InfoAboutElement(int id, QString name, int speed, int mass){
        this->id = id;
        this->name = name;
        this->speed = speed;
        this->mass = mass;
    }*/

};

// class Table() toDO:: create base class
class AirplansTable
{
public:
    AirplansTable();
    int select(int id);
    QVector<InfoAboutElement> select_all();
};

class ZRKTable
{
public:
    ZRKTable();
    int select(int id);    
    QVector<InfoAboutElement> select_all();
};


#endif // DATABASE_H
