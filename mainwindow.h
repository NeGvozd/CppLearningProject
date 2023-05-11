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
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QPicture>

#include <database/src/database.h>
#include "datawindow.h"
#include "database/src/databasecontroller.h"
//#include "QGSController/src/QGSController.h"
#include "QGSController/src/chooseline.h"

#include "Engine/src/engine.h"

#include "itemslist.h"
#include "ItemsListWindow.h"

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
//    void LinesWidgetInit();
private: 
    void createStatusBar();
signals:
    void createNewObject(InfoAboutElement element);
    void sig_block_db();
    void sig_unblock_db();
    void selectRocketItem(int id, QString name, QString model, float damage, float speed, float range, float x, float y);
    void selectSAMItem(int id, QString name, QString model, float health, float distance, int ammo, float x, float y);
    void selectPlaneItem(int id, QString name, QString model, float health, float speed, float x, float y);
private slots:
    void on_actionLine_triggered();

    void on_handButton_clicked();
    void setLineHide();

    void on_addFromTreeButton_clicked();
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionauthors_triggered();
    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);
    void on_DataBaseButton_clicked();
    void fillTreeFromDb();
    void showLinesDialog();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void itemsListShow();
    void itemsListClicked(QTreeWidgetItem *item, int column);

public slots:
    void addedToDb();
    void updateMapCoord(double x, double y);
    void updateMapScale(double s);
    void planeCreated();
    void addPlaneToItems(int id, QString name, QString model, float health, float speed, float x, float y);
    void addSAMToItems(int id, QString name, QString model, float health, float distance, int ammo, float x, float y);
    void addRocketToItems(int id, QString name, QString model, float damage, float speed, float range, float x, float y);

private:
    //if you don't have QGS comment bottom line
    //QGSController* QgsController;
    Ui::MainWindow *ui;

    QLabel* msg;
    QLabel* forIconCoord;
    QLabel* forNameCoord;
    QLabel* forValuesCoord;
    QLabel* forIconScale;
    QLabel* forNameScale;
    QLabel* forValuesScale;

    QPushButton* SetLine;
    QPushButton* RadarBtn;

    ChooseLine* lineDialog;
    DatabaseController *dbController;
    //ObjectFactory *objFactory;
    Engine* engine;

    ItemsListItem* planes = nullptr;
    ItemsListItem* sams = nullptr;
    ItemsListItem* rockets = nullptr;

    ItemsListWindow* ListWindow;
};

#endif // MAINWINDOW_H
