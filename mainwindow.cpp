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
    connect(lineDialog, &ChooseLine::itemClickSend, engine, &Engine::addPlane);
    connect(this, SIGNAL(sig_block_db()),dbController,SLOT(slot_block_db()));
    connect(this, SIGNAL(sig_unblock_db()),dbController,SLOT(slot_unblock_db()));
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
    forNameScale = new QLabel("Scale : ");
    forValuesScale = new QLabel();

    QPixmap pix(":/rec/img/location_icon.png");
    forIconCoord->setPixmap(pix);
    forValuesCoord->setFrameShape(QFrame::StyledPanel);
    forValuesScale->setFrameShape(QFrame::StyledPanel);

    ui->statusbar->addPermanentWidget(spacer, 2);
    ui->statusbar->addPermanentWidget(forIconCoord);
    ui->statusbar->addPermanentWidget(forNameCoord);
    ui->statusbar->addPermanentWidget(forValuesCoord, 1);
    forValuesCoord->setText(QString("%1 : %2").arg(x).arg(y));
    ui->statusbar->addPermanentWidget(forNameScale);
    ui->statusbar->addPermanentWidget(forValuesScale, 1);
    forValuesScale->setText(QString("%1").arg(scale));
}

void MainWindow::show(){
    QMainWindow::show();
    ui->DockWidgetForTree->raise();
    ui->DockWidgetForTree->close();
}

void MainWindow::updateMapCoord(double x, double y){
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
        MyTreeItem *sam = new MyTreeItem(zrk, zrks[i].id, zrks[i].type, zrks[i].name, 0, 0, zrks[i].distance, zrks[i].damage);
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
