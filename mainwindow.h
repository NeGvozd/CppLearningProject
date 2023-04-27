#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <typeinfo>
#include <memory>

#include <QAbstractButton>

#include <database.h>
#include "datawindow.h"
#include "databasecontroller.h"
#include "objects/ObjectFactory.h"
//#include "QGSController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//MyTreeItem
class MyTreeItem : public QTreeWidgetItem
{

public: //ToDO: transfer to private
    int id;
    Table type;
    QString name;
    int speed;
    int mass;
    int distance;
    int damage;

    MyTreeItem(MyTreeItem *parent=nullptr, int id=0, Table type=AIRPLANS, QString name="none", int speed=0, int mass=0, int distance=0, int damage=0);
    MyTreeItem(QTreeWidget *parent=nullptr, int id=0, QString name="none");

    int get_id() const;
    Table get_type() const;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget *Map;
    void show();

private slots:
    void on_addFromTreeButton_clicked();
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionauthors_triggered();
    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);
    void on_DataBaseButton_clicked();
    void fillTreeFromDb();
    void create_new_object(int id,Table type);

public slots:
    void addedToDb();

private:
    //if you don't have QGS comment bottom line
    //QGSController* QgsController;

    Ui::MainWindow *ui;
    DatabaseController *dbController;
    //ObjectFactory *objFactory;

};

#endif // MAINWINDOW_H
