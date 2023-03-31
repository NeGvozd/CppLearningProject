#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QMainWindow>
#include <QTableWidget>
#include <QDialog>
#include <QGridLayout>

#include <database.h>

class DatabaseController
{
public:
    DatabaseController();
    QSqlDatabase return_db();//also
    int connection();//возможно в дальнейшем нужно будет передавать аргумент отвечающий за контретную дб
    int closing();
private:
    AirplansDB airplanDB;

};


#endif // DATABASECONTROLLER_H
