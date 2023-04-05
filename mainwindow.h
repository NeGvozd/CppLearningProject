#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QFileDialog>
#include <memory>

//Если у вас нет Qgs, то вырубайте
#include <qgsmapcanvas.h>
#include <qlayout.h>
#include <qgsvectorlayer.h>
#include <utility>
#include <qgssymbol.h>
#include <qgsgeometry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsmarkersymbollayer.h>
#include <qgsfields.h>
#include <qgsvectorfilewriter.h>
#include <qgslabeling.h>
#include <qgsvectorlayerlabeling.h>
#include <qgspallabeling.h>
#include <qgsrulebasedrenderer.h>

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

    void get_type();
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
    void setupQgs();
private slots:


    void on_actionNew_triggered();
    void on_actionauthors_triggered();
    void on_actionExit_triggered();
    void on_pushButton_2_clicked();

    void on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column);

private:
    QDockWidget *WindowAddedItems;
    QFrame *HorizontalToolbar;
    QFrame *VerticalToolbar;


    //Если у вас нет Qgs, то вырубайте
    QgsMapCanvas* canvas;

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
