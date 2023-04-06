#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QMainWindow>
#include <QTableWidget>
#include <QDialog>
#include <QGridLayout>
#include <QMainWindow>
#include <QSqlTableModel>
#include <database.h>

enum Table{AIRPLANS,ZRK};//will be more tables



class DatabaseController
{
public:
    DatabaseController();
    QSqlDatabase return_db();
    int connection();
    int closing();
    int select(Table table,int id);//where and what
private:
    QSqlDatabase db;//database//how to make *??
    AirplansTable* airplanTable; //table with Airplans
    ZRKTable* zrkTable;
public:
    QSqlTableModel *model = nullptr;//object which show tables on screen
};


#endif // DATABASECONTROLLER_H
