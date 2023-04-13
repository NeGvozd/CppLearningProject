#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->TreeAddedItems->clear();



//    MyTreeItem *zrk = new MyTreeItem(ui->TreeAddedItems, 0, "zrk", 0, 111);
//    MyTreeItem *plane = new MyTreeItem(ui->TreeAddedItems, 1);
//    MyTreeItem *gyro = new MyTreeItem(ui->TreeAddedItems, 2);


//    zrk->setText(0, "ЗРК");
//    plane->setText(0, "Самолёты");
//    gyro->setText(0, "Вертолеты");
//    zrk->setIcon(0, QIcon(":/rec/img/zrk.png"));
//    plane->setIcon(0, QIcon(":/rec/img/plane.png"));
//    gyro->setIcon(0, QIcon(":/rec/img/gyrocopter.png"));

//    //childs
//    MyTreeItem *firstZrk = new MyTreeItem(zrk, 0);
//    firstZrk->setText(0, "zrk_1");

//    MyTreeItem *firstPlane = new MyTreeItem(plane, 1);
//    firstPlane->setText(0, "plane_1");
//    MyTreeItem *firstGyro = new MyTreeItem(gyro, 2);
//    firstGyro->setText(0, "gyro_1");


}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::test()
{
    qInfo() << "lfjaidhadjpadjf";
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

//MyTreeItem
MyTreeItem::MyTreeItem(MyTreeItem *parent, int id, QString name, int speed, int mass) : QTreeWidgetItem(parent){
    this->id=id;
    this->name = name;
    this->speed = speed;
    this->mass = mass;
    this->setText(0, name);
}

MyTreeItem::MyTreeItem(QTreeWidget *parent, int id, QString name, int speed, int mass): QTreeWidgetItem(parent){
    this->id=id;
    this->name = name;
    this->speed = speed;
    this->mass = mass;
    this->setText(0, name);
}

void MyTreeItem::get_info()
{
    qInfo() << id;
    qInfo() << name;
    qInfo() << speed;
    qInfo() << mass;
}


void MainWindow::on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->childCount()!=0)
        return;
    dynamic_cast<MyTreeItem*>(item)->get_info();
}


void MainWindow::on_DataBaseButton_clicked()
{
    dbWindow = new DataWindow(this);
    dbWindow->show();
    fillTreeFromDb();

    connect(dbWindow, &DataWindow::signal, this, &MainWindow::slot);

//    DataWindow dbWindow;
//    dbWindow.setModal(true);
    //    dbWindow.exec();
}

void MainWindow::fillTreeFromDb()
{
    QVector<InfoAboutElement> planes = dbWindow->dbController.select_all(AIRPLANS);
    QVector<InfoAboutElement> zrks = dbWindow->dbController.select_all(ZRK);

    MyTreeItem *zrk = new MyTreeItem(ui->TreeAddedItems, 0, "ЗРК");
    MyTreeItem *plane = new MyTreeItem(ui->TreeAddedItems, 1, "Самолеты");
    MyTreeItem *gyro = new MyTreeItem(ui->TreeAddedItems, 2, "Вертолеты");

    zrk->setIcon(0, QIcon(":/rec/img/zrk.png"));
    plane->setIcon(0, QIcon(":/rec/img/plane.png"));
    gyro->setIcon(0, QIcon(":/rec/img/gyrocopter.png"));

    //childs
/*
    int sizeZrks = zrks.size();
    QVector<MyTreeItem> massOfZRK;
    for(int i = 0; i < sizeZrks; i++)
    {
        //MyTreeItem pl(zrk, zrks[i].id, zrks[i].name, zrks[i].speed, zrks[i].mass);
        massOfZRK.push_back(MyTreeItem(zrk, zrks[i].id, zrks[i].name, zrks[i].speed, zrks[i].mass));
        //massOfZRK.append(pl);
        //massOfZRK[i]->setText(0, zrks[i].name);
   }*/

    MyTreeItem *firstZrk = new MyTreeItem(zrk, zrks[0].id, zrks[0].name, zrks[0].speed, zrks[0].mass);
    MyTreeItem *secondZrk = new MyTreeItem(zrk, zrks[1].id, zrks[1].name, zrks[1].speed, zrks[1].mass);
    MyTreeItem *thirdZrk = new MyTreeItem(zrk, zrks[2].id, zrks[2].name, zrks[2].speed, zrks[2].mass);

    MyTreeItem *firstPlane = new MyTreeItem(plane, planes[0].id, planes[0].name, planes[0].speed, planes[0].mass);
    MyTreeItem *secondPlane = new MyTreeItem(plane, planes[1].id, planes[1].name, planes[1].speed, planes[1].mass);
    MyTreeItem *thirdPlane = new MyTreeItem(plane, planes[2].id, planes[2].name, planes[2].speed, planes[2].mass);

    MyTreeItem *firstGyro = new MyTreeItem(gyro, 2);



}

void MainWindow::slot()
{
    qInfo() << "ojfdwifjdi";

}
