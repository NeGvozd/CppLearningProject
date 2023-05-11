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
    Table type;
    QString name;
    int speed;
    int mass;
    int health;
    int distance;
    int damage;
    int rocket;
    int sprite_id;
   // InfoAboutElement(int id,Table type,QString name,int speed,int mass,int health,int rocket = 0,int sprite_id = 0);
//    InfoAboutElement(int id,Table type,QString name,int mass,int health,int distance,int damage,int rocket = 0,int sprite_id = 0);

};

// class Table() toDO:: create base class
class  BaseTable
{
public:
    virtual InfoAboutElement select(int id)=0;
    virtual QVector<InfoAboutElement> select_all()=0;
};

class AirplansTable//:public BaseTable
{
public:
    InfoAboutElement select(int id);// override;
    QVector<InfoAboutElement> select_all();// override;
};

class ZRKTable//:public BaseTable
{
public:
    InfoAboutElement select(int id);// override;
    QVector<InfoAboutElement> select_all();// override;
};


#endif // DATABASE_H
