#include "databasecontroller.h"

DatabaseController::DatabaseController()
{
}

int DatabaseController::connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../CppLearningProject/database/tth.db");


    if (db.open())
    {
        qInfo() << "Database is open!";
        model = new QSqlTableModel(NULL,db);
        return 0;
    }
    else {
        qInfo() << "Can not open database! "<<db.lastError().databaseText();
        return -1;
    }


}

int DatabaseController::select(Table table,int id)
{
    if(table == AIRPLANS)
    {
        airplanTable->select(id);
    }
    else if(table == ZRK)
    {
        zrkTable->select(id);
    }
    return 0;
}

QVector<InfoAboutElement> DatabaseController::select_all(Table table)
{
    QVector<InfoAboutElement> ans;
    if(table == AIRPLANS)
    {
        ans = airplanTable->select_all();
    }
    else if(table == ZRK)
    {
        ans = zrkTable->select_all();
    }
    return ans;
}

QSqlDatabase DatabaseController::return_db()
{
    return db;
}

int DatabaseController::closing()
{
     db.close();
     qInfo() << "Database is closed!";

     return 0;
}
