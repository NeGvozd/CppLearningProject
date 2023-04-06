#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QMessageBox>
#include <typeinfo>


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

    void get_type();
    void selected();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionauthors_triggered();

    void on_actionExit_triggered();

    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);


    void on_DataBaseButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

