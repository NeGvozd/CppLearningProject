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
    Map=ui->Map;
    dbController = new DatabaseController;

    QFileSystemModel *model = new QFileSystemModel;
    QGridLayout* g = new QGridLayout(ui->Center);
    //objFactory = new ObjectFactory;
    g->addWidget(Map);

    model->setRootPath(QDir::currentPath());

    //if you don't have QGS comment bottom line
    //QgsController = new QGSController(Map);

    ui->TreeAddedItems->clear();

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow:: show(){
    QMainWindow::show();
    ui->DockWidgetForTree->raise();
    ui->DockWidgetForTree->close();
}

void MainWindow::on_actionNew_triggered(){
    //if you don't have QGS comment bottom line
    //QgsController->addLayer();
}
void MainWindow::on_actionauthors_triggered(){
    //TODO вынести в connect это
    //QgsController->activateSelectingPoint();
    //QMessageBox *msg = new QMessageBox;
    //msg->setText(" Max1 \n Max2 \n Ilya \n Nikita \n Oleg");
    //msg->exec();
}

void MainWindow::on_actionExit_triggered(){
    close();
}

void MainWindow::on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column){
    if (item->childCount()!=0)
        return;
    Table type = dynamic_cast<MyTreeItem*>(item)->get_type();
    int id = dynamic_cast<MyTreeItem*>(item)->get_id();
    //dynamic_cast<MyTreeItem*>(item)->get_info();
    this->create_new_object(id,type);
    switch (type) {
    case ZRK:
        //QgsController->activateSelectingSquare();
        break;
    case AIRPLANS:
        //QgsController->activateSelectingPoint();
        break;
    default:
        break;
    }
}

MyTreeItem::MyTreeItem(MyTreeItem *parent, int id, QString name, int speed, int mass, Table type) : QTreeWidgetItem(parent){
    this->id=id;
    this->name = name;
    this->speed = speed;
    this->mass = mass;
    this->type=type;
    this->setText(0, name);
}

MyTreeItem::MyTreeItem(QTreeWidget *parent, int id, QString name, int speed, int mass, Table type): QTreeWidgetItem(parent){
    this->id=id;
    this->name = name;
    this->speed = speed;
    this->mass = mass;
    this->type=type;
    this->setText(0, name);
}

void MyTreeItem::get_info()
{
    qInfo() << id;
    qInfo() << name;
    qInfo() << speed;
    qInfo() << mass;
}

int MyTreeItem::get_id() const{
    return id;
}
Table MyTreeItem::get_type() const{
    return type;
}


void MainWindow::on_DataBaseButton_clicked(){
    dbController->dataWindow_show();
}

void MainWindow::fillTreeFromDb()
{
    QVector<InfoAboutElement> planes = dbController->select_all(AIRPLANS);
    QVector<InfoAboutElement> zrks = dbController->select_all(ZRK);
    MyTreeItem *zrk = new MyTreeItem(ui->TreeAddedItems, 0, "ЗРК");
    MyTreeItem *plane = new MyTreeItem(ui->TreeAddedItems, 1, "Самолеты");
    MyTreeItem *gyro = new MyTreeItem(ui->TreeAddedItems, 2, "Вертолеты");

    zrk->setIcon(0, QIcon(":/rec/img/zrk.png"));
    plane->setIcon(0, QIcon(":/rec/img/plane.png"));
    gyro->setIcon(0, QIcon(":/rec/img/gyrocopter.png"));

    //childs
    int sizeOfplanes = planes.size();
    QVector<MyTreeItem*> mass;
    for(int i = 0; i<sizeOfplanes ;i++){
        MyTreeItem *pl = new MyTreeItem(plane, planes[i].id, planes[i].name, planes[i].speed, planes[i].mass,planes[i].type);
    }


    MyTreeItem *firstZrk = new MyTreeItem(zrk, zrks[0].id, zrks[0].name, zrks[0].speed, zrks[0].mass,zrks[0].type); //toDO:: create ctr from InfoElements
    MyTreeItem *secondZrk = new MyTreeItem(zrk, zrks[1].id, zrks[1].name, zrks[1].speed, zrks[1].mass,zrks[1].type);
    MyTreeItem *thirdZrk = new MyTreeItem(zrk, zrks[2].id, zrks[2].name, zrks[2].speed, zrks[2].mass,zrks[2].type);

    //MyTreeItem *firstPlane = new MyTreeItem(plane, planes[0].id, planes[0].name, planes[0].speed, planes[0].mass,planes[0].type);
    //MyTreeItem *secondPlane = new MyTreeItem(plane, planes[1].id, planes[1].name, planes[1].speed, planes[1].mass,planes[1].type);
    //MyTreeItem *thirdPlane = new MyTreeItem(plane, planes[2].id, planes[2].name, planes[2].speed, planes[2].mass,planes[2].type);

    MyTreeItem *firstGyro = new MyTreeItem(gyro, 2);

}

void MainWindow::create_new_object(int id,Table type)//временное создание объектов(потом переделать) то есть сделать это по клику
{
    InfoAboutElement element = dbController->select(type,id);
    switch (type)
    {
        case AIRPLANS:
            {
                auto plane = ObjectFactory::CreatePlane(element.mass,element.speed,element.name);
            }
        break;
        case ZRK:
            {
                auto zrk = ObjectFactory::CreateSAM(element.mass,element.name);
            }
        break;
        default:
            break;
    }
//    if(type == AIRPLANS)
//        auto plane = ObjectFactory::CreatePlane(element.mass,element.speed,element.name);
//    else if(type == ZRK)
//        auto zrk = ObjectFactory::CreateSAM(element.mass,element.name);
}


void MainWindow::on_addFromTreeButton_clicked(){

    if ((!ui->DockWidgetForTree->isVisible()))//maybe you must write '!' (on macOS it does not work)
        ui->DockWidgetForTree->show();
    else
        ui->DockWidgetForTree->close();

    if(ui->TreeAddedItems->topLevelItemCount()==0)
        fillTreeFromDb();
}
