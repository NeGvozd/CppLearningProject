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

#include <database.h>
#include "datawindow.h"
#include "databasecontroller.h"
#include "QGSController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//MyTreeItem
class MyTreeItem : public QTreeWidgetItem
{

public: //ToDO: transfer to private
    int id;
    QString name;
    int speed;
    int mass;
    Table type;

    MyTreeItem(MyTreeItem *parent = nullptr, int id = 0, QString name = "none", int speed = 0, int mass = 0, Table type=AIRPLANS);
    MyTreeItem(QTreeWidget *parent = nullptr, int id = 0, QString name = "none", int speed = 0, int mass = 0, Table type=AIRPLANS);

    Table get_type() const;
    void get_info();
};

class LineTreeItem : public QTreeWidgetItem{
public:
    int id;
    QString name;
    LineTreeItem(LineTreeItem * parent, int id, QString name);
    LineTreeItem(QTreeWidget * parent, int id, QString name);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget *Map;
    void show();
    void LinesWidgetInit();

private slots:
    void on_actionLine_triggered();

private slots:
    void on_actionHand_triggered();
    void setLineHide();

private slots:
    void on_addFromTreeButton_clicked();
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionauthors_triggered();
    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);
    void on_DataBaseButton_clicked();
    void fillTreeFromDb();
    void showLinesListWidget();
    void addLine(int id, QString name);
    void getLineId(QTreeWidgetItem *item, int column);

private:
    //if you don't have QGS comment bottom line
    QGSController* QgsController;

    Ui::MainWindow *ui;
    DatabaseController dbController;

    QPushButton* SetLine;

    LineTreeItem *lines;
};

#endif // MAINWINDOW_H
