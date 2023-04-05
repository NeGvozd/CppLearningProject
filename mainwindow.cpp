#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model);

    HorizontalToolbar=ui->HorizontalToolbar;
    VerticalToolbar=ui->VerticalToolbar;
    Map=ui->Map;
    WindowAddedItems=ui->WindowAddedItems;


    //Если у вас нет Qgs, то вырубайте
    setupQgs();
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

//Если у вас нет Qgs, то вырубайте
void MainWindow::setupQgs()
{
    canvas =new QgsMapCanvas(this->Map);

    canvas->setWindowFlags(canvas->windowFlags() & ~Qt::WindowStaysOnBottomHint);
    canvas->setCanvasColor("blue");

    QGridLayout* gl =new QGridLayout(this->Map);
    gl->addWidget(canvas);
    ui->WindowAddedItems->setParent(canvas);


    /*
    mainCrs.createFromProj("+proj=longlat +datum=WGS84 +no_defs");

    this->setCentralWidget(canvas);
            QgsVectorLayer::LayerOptions options;
    options.loadDefaultStyle = false;


    QgsVectorLayer* layer =new QgsVectorLayer("/home/runspaer/maps/kx-world-land-areas-110-million-SHP/world-land-areas-110-million.shp",
    "/home/runspaer/maps/kx-world-land-areas-110-million-SHP/world-land-areas-110-million","ogr" , options);
    if(!layer->isValid())
    {
        printf("Failed to open the layer");
    }

    // добавляем слой к списку
    QList<QgsMapLayer*> layers;
    layers.push_back(layer);
    QgsProject::instance()->addMapLayers(layers);
    // добавляем слои на карту
    canvas->setLayers(layers);
    */
}


void MainWindow:: show()
{
    this->QMainWindow::show();
    this->WindowAddedItems->close();
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{

    QFileDialog dialog(this, QString("Добавить слой").toLocal8Bit());
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    dialog.setNameFilter("*.shp");
    if (dialog.exec() == QDialog::Accepted)
    {
        QString layerPath =dialog.selectedFiles()[0];
        if (!QFile::exists(layerPath))
            return;
        //std::unique_ptr<LayerHandler> layerHandler;
        if (layerPath.contains(".shp"))
        {

            QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
            QgsVectorLayer* trajectoryPointsLayer = new QgsVectorLayer("Point", "Points", "memory");

            QgsVectorLayer* earthLayer = new QgsVectorLayer(layerPath, "earth", "ogr");

            controlPointsLayer->startEditing();
            controlPointsLayer->dataProvider()->addAttributes({QgsField("fid", QVariant::Int)});
            controlPointsLayer->updateFields();

            controlPointsLayer->setLabelsEnabled(true);
            QgsPalLayerSettings pls;
            pls.fieldName = "fid";
            pls.placement = QgsPalLayerSettings::Placement::Line;
            QgsVectorLayerSimpleLabeling* simple_label = new QgsVectorLayerSimpleLabeling(pls);
            controlPointsLayer->setLabeling(simple_label);
            controlPointsLayer->commitChanges();

            canvas->setLayers({controlPointsLayer, trajectoryPointsLayer, earthLayer});
            canvas->setExtent(earthLayer->extent());
            QgsCoordinateReferenceSystem crs("EPSG:4326");
            canvas->setDestinationCrs(crs);
            canvas->refresh();
        }
    }
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

MyTreeItem::MyTreeItem(MyTreeItem *parent, int type) : QTreeWidgetItem(parent){
    this->type=type;
}

MyTreeItem::MyTreeItem(QTreeWidget *parent, int type): QTreeWidgetItem(parent){
    this->type=type;
}

void MyTreeItem::get_type()
{
    if (type == 0) qDebug("zrk");
    if (type == 1) qDebug("plane");
    if (type == 2) qDebug("gyro");
}

void MyTreeItem::selected()
{
    qDebug()<<"Selected ";
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
