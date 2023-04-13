#include "database.h"

int AirplansTable::select(int id)
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

    qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed <<"Mass ="<< mass;

    return 0;

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


        qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed <<"Mass ="<< mass;
        struct InfoAboutElement plane = {id, name, speed, mass};
        vec.append(plane);
    }

    return vec;
}

int ZRKTable::select(int id)
{
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM ZRK WHERE id = (:id)");
    my_query.bindValue(":id", id);
    my_query.exec();

    QSqlRecord rec = my_query.record();
    my_query.first();

    QString name = my_query.value(rec.indexOf("Name")).toString();
    int distance = my_query.value(rec.indexOf("Distance")).toInt();
    int damage = my_query.value(rec.indexOf("Damage")).toInt();

    qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Distance ="<< distance <<"Damage ="<< damage;

    return 0;

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
        int speed = my_query.value(rec.indexOf("Speed")).toInt();
        int mass = my_query.value(rec.indexOf("Mass")).toInt();


        qInfo() << "Row with id =" <<id<<"Name = "<< name <<"Speed ="<< speed <<"Mass ="<< mass;
        struct InfoAboutElement zrk = {id, name, speed, mass};
        vec.append(zrk);
    }

    return vec;
}
