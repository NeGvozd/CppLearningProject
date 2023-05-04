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
    InfoAboutElement select(Table table,int id);//where and what
    QVector<InfoAboutElement> select_all(Table table);
    void dataWindow_show();

signals:
    void sig_table(QSqlTableModel *model);
    void sig_addedToDb();

public slots:
    void slot_typeTable_clicked(Table table);
    void slot_addButton_clicked();
    void slot_deleteButton_clicked();
    void slot_tableView_clicked(const QModelIndex &index);

    void slot_userAddedData();

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
