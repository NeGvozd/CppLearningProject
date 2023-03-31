#include "database.h"

AirplansDB::AirplansDB()
{

}

int AirplansDB::connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/maksim/qt_pr/testing_db/database/tth.db");

    if (db.open())
    {
        qInfo() << "Database is open!";
        return 0;
    }
    else {
        qInfo() << "Can not open database! "<<db.lastError().databaseText();
        return -1;
    }
}

int AirplansDB::closing()
{
    db.close();
    qInfo() << "Database is closed!";

    return 0;
}

QSqlDatabase AirplansDB::return_db()
{
    return this->db;
}

int AirplansDB::select(int id)
{
//    QString str = "SELECT * FROM AIRPLANS WHERE id = :_id";
//    QSqlQuery query(str);
//    query.bindValue(":_id", id);
//    query.setForwardOnly( true );
//    query.exec();

//    QSqlQuery query();
//    query.setForwardOnly(true);
//    query.prepare("SELECT * FROM AIRPLANS WHERE id = :_id");
//    query.bindValue(":_id",id);
//    if (!query.exec())
//        qDebug() << "SQL QUERY ERROR:" << wordQuery.lastError().text();

    return 0;

}
