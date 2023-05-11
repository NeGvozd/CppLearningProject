#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QMainWindow>
#include <QTableWidget>
#include <QDialog>
#include <QGridLayout>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



#include <../../datawindow.h>
#include <database.h>
#include "../../objects/src/point.h"
#include "../../objects/src/plane.h"
#include "../../objects/src/rocket.h"
#include "../../objects/src/sam.h"




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
    void sig_block_db();
    void sig_unblock_db();

public slots:
    void slot_typeTable_clicked(Table table);
    void slot_addButton_clicked();
    void slot_deleteButton_clicked();
    void slot_tableView_clicked(const QModelIndex &index);
    void slot_block_db();
    void slot_unblock_db();
    void slot_userAddedData();
    void slot_make_backup(std::vector<std::shared_ptr<Plane> > &planes, std::vector<std::shared_ptr<SAM> > &sams, std::vector<std::shared_ptr<Rocket> > &rockets);

private:
    QSqlDatabase db;
    AirplansTable* airplanTable; //table with Airplans
    ZRKTable* zrkTable;
    ROCKETTable* rocketTable;
    SpriteTable* spritTable;
    DataWindow* dbWindow;
    int currentRow;

public:
    QSqlTableModel *model = nullptr;//object which show tables on screen

};


#endif // DATABASECONTROLLER_H
