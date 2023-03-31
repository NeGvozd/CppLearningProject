#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QAbstractButton>

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

    //: QTreeWidgetItem(parent)  {}
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
    void on_pushButton_2_clicked();

    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
