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

#include "QGSController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//MyTreeItem
class MyTreeItem : public QTreeWidgetItem
{

public:
    int type;
    MyTreeItem(MyTreeItem *parent = nullptr, int type = 0);
    MyTreeItem(QTreeWidget *parent = nullptr, int type = 0);

    int get_type();
    void selected();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget *Map;

    virtual void show();
private slots:
    void on_addFromTreeButton_clicked();

private slots:


    void on_actionNew_triggered();
    void on_actionauthors_triggered();
    void on_actionExit_triggered();
    void on_pushButton_2_clicked();

    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);

    void on_DataBaseButton_clicked();
private:
    //if you don't have QGS comment bottom line
    QGSController* QgsController;

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
