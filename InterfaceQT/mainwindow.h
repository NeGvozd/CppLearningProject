#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QMessageBox>
#include <typeinfo>
#include "datawindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//MyTreeItem
class MyTreeItem : public QTreeWidgetItem
{

public:
    int id;
    QString name;
    int speed;
    int mass;


    MyTreeItem(MyTreeItem *parent = nullptr, int id = 0, QString name = "none", int speed = 0, int mass = 0);
    MyTreeItem(QTreeWidget *parent = nullptr, int id = 0, QString name = "none", int speed = 0, int mass = 0);

    void get_info();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void test();

    void on_actionauthors_triggered();
    void on_actionExit_triggered();

    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);

    void on_DataBaseButton_clicked();
    void fillTreeFromDb();

private:
    Ui::MainWindow *ui;
    DataWindow *dbWindow;

public slots:
    void slot();

};
#endif // MAINWINDOW_H

