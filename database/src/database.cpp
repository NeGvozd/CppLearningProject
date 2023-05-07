#include "database.h"

//InfoAboutElement::InfoAboutElement(int _id, QString _name, int _speed, int _mass,Table _type):id{_id},name{_name},speed{_speed},mass{_mass},type{_type} {}

InfoAboutElement AirplansTable::select(int id)
{
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM AIRPLANS WHERE id = (:id)");
    my_query.bindValue(":id", id);
    my_query.exec();

    QSqlRecord rec = my_query.record();
    my_query.first();

    QString name = my_query.value(rec.indexOf("Name")).toString();
    int speed = my_query.value(rec.indexOf("Speed")).toInt();
    int mass = my_query.value(rec.indexOf("Mass")).toInt();
    int health = my_query.value(rec.indexOf("Health")).toInt();
    int rocket = my_query.value(rec.indexOf("Rocket")).toInt();
    int sprite_id = my_query.value(rec.indexOf("Sprtite_id")).toInt();//ops

    //qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed <<"Mass ="<< mass;
    InfoAboutElement plane = {id, AIRPLANS, name, speed, mass,health,0,rocket,sprite_id};
    //InfoAboutElement plane = InfoAboutElement(id, AIRPLANS, name, speed, mass,health,0,0,0,0);
    return plane;
}

QVector<InfoAboutElement> AirplansTable::select_all()
{
    QVector<InfoAboutElement> vec;
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM AIRPLANS");
    my_query.exec();

    QSqlRecord rec = my_query.record();
    while(my_query.next())
    {
        int id = my_query.value(rec.indexOf("id")).toInt();
        QString name = my_query.value(rec.indexOf("Name")).toString();
        int speed = my_query.value(rec.indexOf("Speed")).toInt();
        int mass = my_query.value(rec.indexOf("Mass")).toInt();
        int health = my_query.value(rec.indexOf("Health")).toInt();
        int rocket = my_query.value(rec.indexOf("Rocket")).toInt();
        int sprite_id = my_query.value(rec.indexOf("Sprtite_id")).toInt();//ops

        //qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed <<"Mass ="<< mass;
        InfoAboutElement plane = {id, AIRPLANS, name, speed, mass,health,0,rocket,sprite_id};
        //InfoAboutElement plane = InfoAboutElement(id, AIRPLANS, name, speed, mass,health,0,0,0,0);
        vec.append(plane);
    }

    return vec;
}


InfoAboutElement ZRKTable::select(int id)
{
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM ZRK WHERE id = (:id)");
    my_query.bindValue(":id", id);
    my_query.exec();

    QSqlRecord rec = my_query.record();
    my_query.first();

    QString name = my_query.value(rec.indexOf("Name")).toString();
    int distance = my_query.value(rec.indexOf("Distance")).toInt();
    int health = my_query.value(rec.indexOf("Health")).toInt();
    int rocket = my_query.value(rec.indexOf("Rocket")).toInt();
    int sprite_id = my_query.value(rec.indexOf("Sprite_id")).toInt();
    //qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Distance ="<< distance <<"Damage ="<< damage;

    //InfoAboutElement zrk = InfoAboutElement(id, ZRK, name,0,0,health, distance , damage,0,0);
    InfoAboutElement zrk = {id, ZRK, name,0,health, distance,rocket,sprite_id};
    return zrk;

}


QVector<InfoAboutElement> ZRKTable::select_all()
{
    QVector<InfoAboutElement> vec;
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM ZRK");
    my_query.exec();

    QSqlRecord rec = my_query.record();
    while(my_query.next())
    {
        int id = my_query.value(rec.indexOf("id")).toInt();
        QString name = my_query.value(rec.indexOf("Name")).toString();
        int distance = my_query.value(rec.indexOf("Distance")).toInt();
        int health = my_query.value(rec.indexOf("Health")).toInt();
        int rocket = my_query.value(rec.indexOf("Rocket")).toInt();
        int sprite_id = my_query.value(rec.indexOf("Sprite_id")).toInt();//ops

        //qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed <<"Mass ="<< mass;
        //InfoAboutElement zrk = InfoAboutElement(id, ZRK, name,0,0,health, distance , damage,0,0);
        InfoAboutElement zrk = {id, ZRK, name,0,health, distance,rocket,sprite_id};
        vec.append(zrk);
    }

    return vec;
}



InfoAboutRocket ROCKETTable::select(int id)
{
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM ROCKET WHERE id = (:id)");
    my_query.bindValue(":id", id);
    my_query.exec();

    QSqlRecord rec = my_query.record();
    my_query.first();

    QString name = my_query.value(rec.indexOf("Name")).toString();
    int speed = my_query.value(rec.indexOf("Speed")).toInt();
    int damage = my_query.value(rec.indexOf("Damage")).toInt();
    int distance = my_query.value(rec.indexOf("Distance")).toInt();
    int guidance_type = my_query.value(rec.indexOf("Guidance type")).toInt();

    qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed;
    InfoAboutRocket rocket = {id, name,speed, damage, distance, guidance_type};

    return rocket;
}

QVector<InfoAboutRocket> ROCKETTable::select_all()
{
    QVector<InfoAboutRocket> vec;
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM ROCKET");
    my_query.exec();

    QSqlRecord rec = my_query.record();
    while(my_query.next())
    {
        int id = my_query.value(rec.indexOf("id")).toInt();
        QString name = my_query.value(rec.indexOf("Name")).toString();
        int speed = my_query.value(rec.indexOf("Speed")).toInt();
        int damage = my_query.value(rec.indexOf("Damage")).toInt();
        int distance = my_query.value(rec.indexOf("Distance")).toInt();
        int guidance_type = my_query.value(rec.indexOf("Guidance type")).toInt();

        qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed;
        InfoAboutRocket rocket = {id, name,speed, damage, distance, guidance_type};
        vec.append(rocket);
    }

    return vec;
}

