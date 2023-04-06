#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "datawindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
//    ui->treeView->setModel(model);

//    HorizontalToolbar=ui->HorizontalToolbar;
//    VerticalToolbar=ui->VerticalToolbar;
    Map=ui->Map;
//    WindowAddedItems=ui->WindowAddedItems;


//    ui->WindowAddedItems->setParent(ui->Center);
    QgsController = new QGSController(Map);
    ui->TreeAddedItems->clear();
    MyTreeItem *zrk = new MyTreeItem(ui->TreeAddedItems, 0);
    MyTreeItem *plane = new MyTreeItem(ui->TreeAddedItems, 1);
    MyTreeItem *gyro = new MyTreeItem(ui->TreeAddedItems, 2);


    zrk->setText(0, "ЗРК");
    plane->setText(0, "Самолёты");
    gyro->setText(0, "Вертолеты");
    zrk->setIcon(0, QIcon(":/rec/img/zrk.png"));
    plane->setIcon(0, QIcon(":/rec/img/plane_115212.png"));
    gyro->setIcon(0, QIcon(":/rec/img/gyrocopter.png"));

    //childs
    MyTreeItem *firstZrk = new MyTreeItem(zrk, 0);
    firstZrk->setText(0, "zrk_1");
    MyTreeItem *firstPlane = new MyTreeItem(plane, 1);
    firstPlane->setText(0, "plane_1");
    MyTreeItem *firstGyro = new MyTreeItem(gyro, 2);
    firstGyro->setText(0, "gyro_1");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow:: show()
{
    this->QMainWindow::show();
//    this->WindowAddedItems->close();
//    this->WindowAddedItems->raise();
}

void MainWindow::on_actionNew_triggered()
{
    QgsController->addLayer();
}
void MainWindow::on_actionauthors_triggered()
{
    QMessageBox *msg = new QMessageBox;
    msg->setText(" Max1 \n Max2 \n Ilya \n Nikita \n Oleg");
    msg->exec();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QWidget *window2 = new QWidget;
    window2->show();
}

void MainWindow::on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->childCount()!=0)
        return;
    dynamic_cast<MyTreeItem*>(item)->get_type();
}


MyTreeItem::MyTreeItem(MyTreeItem *parent, int type) : QTreeWidgetItem(parent){
    this->type=type;
}

MyTreeItem::MyTreeItem(QTreeWidget *parent, int type): QTreeWidgetItem(parent){
    this->type=type;
}

void MyTreeItem::get_type()
{
    qInfo() << type;

    if (type == 0) qDebug("zrk");
    if (type == 1) qDebug("plane");
    if (type == 2) qDebug("gyro");
}

void MyTreeItem::selected()
{
    qDebug()<<"Selected ";
}

void MainWindow::on_DataBaseButton_clicked()
{
    DataWindow dbWindow;
    dbWindow.setModal(true);
    dbWindow.exec();
}