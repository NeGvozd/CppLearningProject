#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QMainWindow>
#include <QTableWidget>
#include <QDialog>
#include <QGridLayout>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QObject>
#include <database.h>
#include <datawindow.h>

enum Table{AIRPLANS,ZRK};//will be more tables


class DatabaseController: public QObject
{
    Q_OBJECT
public:
    DatabaseController();
    QSqlDatabase return_db();
    int closing();
    void connection();
    int select(Table table,int id);//where and what
    void return_model();

public slots:
   void slot_planeButton_clicked();
//    void slot_zrkButton_clicked();

//    void slot_addButton_clicked();
//    void slot_deleteButton_clicked();
//    void slot_tableView_clicked(const QModelIndex &index);


private:
    QSqlDatabase db;//database//how to make *??
    AirplansTable* airplanTable; //table with Airplans
    ZRKTable* zrkTable;
    DataWindow* dataWindow;
    int currentRow;
public:
    QSqlTableModel *model;//object which shows tables on screen
};


#endif // DATABASECONTROLLER_H
