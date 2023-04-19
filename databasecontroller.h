#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QMainWindow>
#include <QTableWidget>
#include <QDialog>
#include <QGridLayout>
#include <QMainWindow>
#include <QSqlTableModel>

#include <datawindow.h>
#include <database.h>




class DatabaseController:public QObject
{
    Q_OBJECT
public:
    DatabaseController();
    QSqlDatabase return_db();
    int connection();
    int closing();
    int select(Table table,int id);//where and what
    QVector<InfoAboutElement> select_all(Table table);
    void dataWindow_show();

signals:
    void sig_table(QSqlTableModel *model);

public slots:
    void slot_typeTable_clicked(int table);
    void slot_addButton_clicked();
    void slot_deleteButton_clicked();
    void slot_tableView_clicked(const QModelIndex &index);

private:
    QSqlDatabase db;
    AirplansTable* airplanTable; //table with Airplans
    ZRKTable* zrkTable;
    DataWindow* dbWindow;
    int currentRow;

public:
    QSqlTableModel *model = nullptr;//object which show tables on screen

};


#endif // DATABASECONTROLLER_H
