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
    this->setStyleSheet("background-color: rgba(195, 218, 240, 0.92);");
    //this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0.898, x2:1, y2:0, stop:0 rgba(85, 170, 255, 245), stop:1 rgba(128, 213, 255, 255))");
    ui->statusbar->setStyleSheet("background-color: rgba(149, 200, 249, 0.95);");
    ui->HorizontalToolbar->setStyleSheet("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(0, 130, 255, 69), stop:0.375 rgba(0, 140, 255, 69), stop:0.423533 rgba(0, 255, 240, 145), stop:0.45 rgba(0, 255, 240, 208), stop:0.452632 rgba(0, 120, 255, 145), stop:0.477581 rgba(71, 93, 255, 130), stop:0.518717 rgba(71, 255, 245, 130), stop:0.531579 rgba(71, 129, 255, 130), stop:0.55 rgba(0, 170, 255, 255), stop:0.57754 rgba(0, 255, 240, 130), stop:0.605263 rgba(0, 140, 255, 255), stop:0.625 rgba(0, 255, 240, 69), stop:1 rgba(0, 210, 255, 69))");
    ui->VerticalToolbar->setStyleSheet("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(0, 130, 255, 69), stop:0.375 rgba(0, 140, 255, 69), stop:0.423533 rgba(0, 255, 240, 145), stop:0.45 rgba(0, 255, 240, 208), stop:0.452632 rgba(0, 120, 255, 145), stop:0.477581 rgba(71, 93, 255, 130), stop:0.518717 rgba(71, 255, 245, 130), stop:0.531579 rgba(71, 129, 255, 130), stop:0.55 rgba(0, 170, 255, 255), stop:0.57754 rgba(0, 255, 240, 130), stop:0.605263 rgba(0, 140, 255, 255), stop:0.625 rgba(0, 255, 240, 69), stop:1 rgba(0, 210, 255, 69))");
    ui->menubar->setStyleSheet("background-color: rgba(149, 200, 249, 0.95);");

    Map=ui->Map;
    dbController = new DatabaseController;

    QFileSystemModel *model = new QFileSystemModel;
    QGridLayout* g = new QGridLayout(ui->Center);
    //objFactory = new ObjectFactory;
    g->addWidget(Map);

    model->setRootPath(QDir::currentPath());

    //if you don't have QGS comment bottom line
    QgsController = new QGSController(Map);
    
    connect(dbController, SIGNAL(sig_addedToDb()), this, SLOT(addedToDb()));
    createStatusBar();
    ui->TreeAddedItems->clear();
    SetLine = ui->SetLine;
    RadarBtn = ui->RadarButton;
    lineDialog = new ChooseLine(this);
    connect(SetLine, &QPushButton::clicked, QgsController, &QGSController::addLine);
    SetLine->hide();
    connect(ui->LinesButton, &QPushButton::clicked, this, &MainWindow::showLinesDialog);

    connect(lineDialog, &ChooseLine::itemClickSend, QgsController, &QGSController::getLineId);
    connect(lineDialog, &ChooseLine::itemNameChange, QgsController, &QGSController::lineChangeName);
    connect(QgsController, &QGSController::sendLine, lineDialog, &ChooseLine::addLine);
    connect(RadarBtn, &QPushButton::clicked, QgsController, &QGSController::showRadarZones);
    connect(QgsController, &QGSController::coordChanged, this, &MainWindow::updateMapCoord);
    connect(QgsController, &QGSController::scaleChanged, this, &MainWindow::updateMapScale);
    engine = new Engine();
    connect(this, &MainWindow::createNewObject, engine, &Engine::createNewObject);
    connect(engine, &Engine::planeCreated, this, &MainWindow::planeCreated);
    connect(engine, &Engine::samCreated, QgsController, &QGSController::activateSelectingSquare);
    connect(QgsController, &QGSController::createLine, engine, &Engine::addLine);
    connect(QgsController, &QGSController::createSAM, engine, &Engine::addSAM);
    connect(QgsController, &QGSController::sendPointsCoords, engine, &Engine::addPlane);
    connect(this, SIGNAL(sig_block_db()),dbController,SLOT(slot_block_db()));
    connect(this, SIGNAL(sig_unblock_db()),dbController,SLOT(slot_unblock_db()));
    connect(engine, &Engine::sendObjects, QgsController, &QGSController::renderObject);
    connect(engine, &Engine::rocketCreated, QgsController, &QGSController::addRocket);
    connect(engine, &Engine::createSAMCircles, QgsController, &QGSController::addRadarCircles);
    connect(engine, &Engine::deleteRocket, QgsController, &QGSController::deleteRocket);
    connect(QgsController, &QGSController::continueRender, engine, &Engine::startRenderCycle);
    connect(ui->ItemsListButton, &QPushButton::clicked, this, &MainWindow::itemsListShow);

    connect(engine, &Engine::sendPlaneToList, this, &MainWindow::addPlaneToItems);
    connect(engine, &Engine::sendSAMToList, this, &MainWindow::addSAMToItems);
    connect(engine, &Engine::sendRocketToList, this, &MainWindow::addRocketToItems);
    connect(ui->ItemsListWidget, &QTreeWidget::itemClicked, this, &MainWindow::itemsListClicked);
    ListWindow = new ItemsListWindow();
    connect(this, &MainWindow::selectPlaneItem, ListWindow, &ItemsListWindow::planeCharacteristics);
    connect(this, &MainWindow::selectRocketItem, ListWindow, &ItemsListWindow::RocketCharacteristics);
    connect(this, &MainWindow::selectSAMItem, ListWindow, &ItemsListWindow::SAMCharacteristics);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::createStatusBar()
{
    float x = 543343334343.433;
    float y = 1.0;
    float scale = 135;

    //bad...
    msg=new QLabel();
    ui->statusbar->addPermanentWidget(msg);


    QLabel *spacer = new QLabel(); // fake spacer
    forIconCoord = new QLabel();
    forNameCoord = new QLabel("Coordinate : ");
    forValuesCoord = new QLabel();
    forIconScale = new QLabel();
    forNameScale = new QLabel("Scale : ");
    forValuesScale = new QLabel();

    QPixmap pixCoord(":/rec/img/location_icon.png");
    forIconCoord->setPixmap(pixCoord);
    QPixmap pixScale(":/rec/img/scale.png");
    forIconScale->setPixmap(pixScale);
    forValuesCoord->setFrameShape(QFrame::StyledPanel);
    forValuesScale->setFrameShape(QFrame::StyledPanel);

    ui->statusbar->addPermanentWidget(spacer, 2);
    ui->statusbar->addPermanentWidget(forIconCoord);
    ui->statusbar->addPermanentWidget(forNameCoord);
    ui->statusbar->addPermanentWidget(forValuesCoord, 1);
    forValuesCoord->setText(QString("%1 : %2").arg(x).arg(y));
    ui->statusbar->addPermanentWidget(forIconScale);
    ui->statusbar->addPermanentWidget(forNameScale);
    ui->statusbar->addPermanentWidget(forValuesScale, 1);
    forValuesScale->setText(QString("%1").arg(scale));
}

void MainWindow::show(){
    QMainWindow::show();
    ui->DockWidgetForTree->raise();
    ui->DockWidgetForTree->close();
    ui->ItemsListWidget->raise();
    ui->ItemsListWidget->close();
}

void MainWindow::updateMapCoord(double x, double y) {
    forValuesCoord->setText(QString("%1 : %2").arg(x).arg(y));
}

void MainWindow::updateMapScale(double s){
    forValuesScale->setText(QString("%1").arg(s));
}

void MainWindow::on_actionNew_triggered(){
    //if you don't have QGS comment bottom line
    QgsController->addLayer();
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

void MainWindow::planeCreated(){
    lineDialog->exec();
}

void MainWindow::on_TreeAddedItems_itemClicked(QTreeWidgetItem *item, int column){
    if (item->childCount()!=0)
        return;
    Table type = dynamic_cast<MyTreeItem*>(item)->get_type();
    int id = dynamic_cast<MyTreeItem*>(item)->get_id();
    //dynamic_cast<MyTreeItem*>(item)->get_info();
    emit createNewObject(dbController->select(type,id));
}

MyTreeItem::MyTreeItem(MyTreeItem *parent, int id, Table type, QString name, int speed, int mass, int distance, int damage) : QTreeWidgetItem(parent){
    this->id=id;
    this->type=type;
    this->name = name;
    this->speed = speed;
    this->mass = mass;
    this->distance = distance;
    this->damage = damage;
    this->setText(0, name);
}

MyTreeItem::MyTreeItem(QTreeWidget *parent, int id, QString name) : QTreeWidgetItem(parent){
    this->id=id;
    this->name = name;
    this->setText(0, name);
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
    ui->TreeAddedItems->clear();
    QVector<InfoAboutElement> planes = dbController->select_all(AIRPLANS);
    QVector<InfoAboutElement> zrks = dbController->select_all(ZRK);
    MyTreeItem *zrk = new MyTreeItem(ui->TreeAddedItems, 0,  "ЗРК");
    MyTreeItem *plane = new MyTreeItem(ui->TreeAddedItems, 1, "Самолеты");
    MyTreeItem *gyro = new MyTreeItem(ui->TreeAddedItems, 2,  "Вертолеты");

    zrk->setIcon(0, QIcon(":/rec/img/zrk.png"));
    plane->setIcon(0, QIcon(":/rec/img/plane.png"));
    gyro->setIcon(0, QIcon(":/rec/img/gyrocopter.png"));

    //childs
    int sizeOfplanes = planes.size();
    for(int i = 0; i<sizeOfplanes ;i++){
        MyTreeItem *pl = new MyTreeItem(plane, planes[i].id, planes[i].type, planes[i].name, planes[i].speed, planes[i].mass, 0 , 0);
    }


    int sizeOfzrks = zrks.size();
    for(int i = 0; i<sizeOfzrks ;i++){
        MyTreeItem *sam = new MyTreeItem(zrk, zrks[i].id, zrks[i].type, zrks[i].name, 0, 0, zrks[i].distance);
    }

    MyTreeItem *firstGyro = new MyTreeItem(gyro, 2);

}

void MainWindow::on_addFromTreeButton_clicked(){

    if ((!ui->DockWidgetForTree->isVisible()))//maybe you must write '!' (on macOS it does not work)
        ui->DockWidgetForTree->show();
    else
        ui->DockWidgetForTree->close();

    if(ui->TreeAddedItems->topLevelItemCount()==0)
        fillTreeFromDb();
}

void MainWindow::itemsListShow(){
    if ((!ui->ItemsListWidget->isVisible()))//maybe you must write '!' (on macOS it does not work)
        ui->ItemsListWidget->show();
    else
        ui->ItemsListWidget->close();
}

void MainWindow::addedToDb(){
    qInfo() << "slot in main window" ;
    fillTreeFromDb();
}


void MainWindow::on_actionLine_triggered(){
    SetLine->show();
    SetLine->raise();
    QgsController->selectionPoints();
    msg->setText("Если вы хотите создать линию нажмите ПКМ");
    connect(QgsController->selectionPointTool, &QgsMapToolEmitPoint::deactivated, this, &MainWindow::setLineHide);
    //приходится курсор доставать
}
void MainWindow::setLineHide(){
    SetLine->hide();
    msg->setText("");
}
void MainWindow::showLinesDialog(){    
    lineDialog->exec();
}

void MainWindow::on_handButton_clicked()
{
    QgsController->activatePanTool();
}

void MainWindow::on_playButton_clicked()
{
    engine->startRenderCycle();
    emit sig_block_db();
}

void MainWindow::on_pauseButton_clicked()
{
    engine->pauseRenderCycle();
    emit sig_unblock_db();
}

void MainWindow::addPlaneToItems(int id, QString name, QString model, float health, float speed, float x, float y){
    if(!planes){
        planes = new ItemsListItem(ui->ItemsListWidget, "Самолеты");
        planes->setIcon(0, QIcon(":/rec/img/plane.png"));
    }
    ItemsListItem *plane = new ItemsListItem(planes, id, name, model, health, speed, x, y);
}

void MainWindow::addSAMToItems(int id, QString name, QString model, float health, float distance, int ammo, float x, float y){
    if(!sams){
        sams = new ItemsListItem(ui->ItemsListWidget, "ЗРК");
        sams->setIcon(0, QIcon(":/rec/img/zrk.png"));
    }
    ItemsListItem *sam = new ItemsListItem(sams, id, name, model, health, distance, ammo, x, y);
}

void MainWindow::addRocketToItems(int id, QString name, QString model, float damage, float speed, float range, float x, float y){
    if(!rockets){
        rockets = new ItemsListItem(ui->ItemsListWidget, "Ракеты");
    }
    ItemsListItem *rocket = new ItemsListItem(rocket, id, name, model, damage, speed, range, x, y);
}

void MainWindow::itemsListClicked(QTreeWidgetItem *item, int column){
    ItemsListItem* selected = dynamic_cast<ItemsListItem*>(item);
    if(selected->ammo()!=-1){
        ListWindow->show();
        emit selectSAMItem(column, selected->name(), selected->model(), selected->health(), selected->distance(), selected->ammo(), selected->x(), selected->y());
    }
    else if(selected->range()!=-1){
        ListWindow->show();
        //emit selectRocketItem(column, selected->name(), selected->model(), selected->damage(), selected->speed(), selected->range(), selected->x(), selected->y());
    }
    else{
        ListWindow->show();
        //emit selectPlaneItem(column, selected->name(), selected->model(), selected->health(), selected->speed(), selected->x(), selected->y());
    }
}