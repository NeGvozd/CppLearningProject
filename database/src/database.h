#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QtSql>
#include <QVector>

enum Table{AIRPLANS,ZRK,ROCKET,SPRITE};//will be more tables

class InfoAboutRocket
{
public:
    int id;
    QString name;
    int speed;
    int damage;
    int distance;
    int guidance_type;
    int sprite_id;

};

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

class ROCKETTable//:public BaseTable
{
public:
    InfoAboutRocket select(int id);// override;
    QVector<InfoAboutRocket> select_all();// override;
};

class SpriteTable//:public BaseTable
{
public:
    QString select(int id);// override;
};



#endif // DATABASE_H
