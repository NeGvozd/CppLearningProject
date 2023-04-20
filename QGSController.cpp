
#include <QMessageBox>
#include <QDebug>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QFileDialog>
#include <QGridLayout>
#include "QGSController.h"

QGSController::QGSController(QWidget* Map){
    this->Map = Map;

    canvas =new QgsMapCanvas(this->Map);

    canvas->enableAntiAliasing(true);
    canvas->setMapSettingsFlags(canvas->mapSettings().flags() | QgsMapSettings::RenderPreviewJob);
    canvas->setParallelRenderingEnabled(true);
    canvas->setCachingEnabled(true);
    canvas->setPreviewJobsEnabled(true);
    canvas->setMapUpdateInterval(500); //ToDO::check possible values

    startLayer();

    QGridLayout* gl =new QGridLayout(this->Map);
    gl->addWidget(canvas);

}

QGSController::~QGSController(){
    delete Map;
}

void QGSController::addLayer(){
    QFileDialog dialog(Map, QString("Добавить слой").toLocal8Bit());
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    dialog.setNameFilter("*.shp");
    if (dialog.exec() == QDialog::Accepted)
    {
        QString layerPath =dialog.selectedFiles()[0];
        if (!QFile::exists(layerPath))
            return;
        if (layerPath.contains(".shp"))
        {

            QgsVectorLayer* newLayer = new QgsVectorLayer(layerPath, layerPath, "ogr");

            layers.push_back(newLayer);

            crs=layers.at(layers.size()-1)->crs();

            canvas->setLayers(layers);
            for(int i=2;i<layers.length();i++)
                canvas->setExtent(layers[i]->extent());

            canvas->refresh();
        }
    }
}

void QGSController::startLayer()
{
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

    controlSquareLayer->startEditing();
    controlSquareLayer->dataProvider()->addAttributes({QgsField("fid", QVariant::Int)});
    controlSquareLayer->updateFields();

    controlSquareLayer->setLabelsEnabled(true);
    QgsPalLayerSettings pls2;
    pls2.fieldName = "fid";
    pls2.placement = QgsPalLayerSettings::Placement::Line;
    QgsVectorLayerSimpleLabeling* simple_label2 = new QgsVectorLayerSimpleLabeling(pls2);
    controlSquareLayer->setLabeling(simple_label2);
    controlSquareLayer->commitChanges();


    setCrs();

    layers.push_back(controlPointsLayer);
    layers.push_back(controlSquareLayer);
}

void QGSController::setCrs()
{
    crs.createFromProj("+proj=longlat +datum=WGS84 +no_defs");
    canvas->setDestinationCrs(crs);
}

void QGSController::activateSelectingPoint(){
    QgsMapToolEmitPoint* emitPointTool = new QgsMapToolEmitPoint(canvas);
    canvas->setMapTool(emitPointTool);
    //TODO как-то перенести в MainWindow
    connect(emitPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addPoint);
}


void QGSController::activateSelectingSquare(){
    QgsMapToolEmitPoint* emitPointTool = new QgsMapToolEmitPoint(canvas);
    canvas->setMapTool(emitPointTool);
    //TODO как-то перенести в MainWindow
    connect(emitPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addSquare);
}

void QGSController::addPoint(const QgsPointXY &point, Qt::MouseButton button){

    controlPointsLayer->startEditing();

    QgsFeature feat;
    feat.setFields(controlPointsLayer->fields(), true);
    feat.setAttribute("fid",int(controlPointsLayer->featureCount())+1);
    feat.setGeometry(QgsGeometry::fromPointXY(point));

    controlPointsLayer->addFeature(feat);

    controlPointsLayer->commitChanges();

    if(controlPointsLayer->featureCount()==1)
        go_rend();
}

void QGSController::addSquare(const QgsPointXY &point, Qt::MouseButton button){

    controlSquareLayer->startEditing();

    QgsFeature feat;
    feat.setFields(controlSquareLayer->fields(), true);
    feat.setAttribute("fid",int(controlSquareLayer->featureCount())+1);
    feat.setGeometry(QgsGeometry::fromRect(QgsRectangle(point,point+QgsVector(1,1))));

    controlSquareLayer->addFeature(feat);

    controlSquareLayer->commitChanges();
}


void QGSController::go(){
    controlPointsLayer->startEditing();

    for (int i=0;i<controlPointsLayer->featureCount();i++)
    {
        QgsPointXY myP=controlPointsLayer->getFeature(i+1).geometry().asPoint();
        myP.setX(myP.x()+0.1);
        myP.setY(myP.y()+0.1);
        QgsGeometry g =QgsGeometry::fromPointXY(myP);
        controlPointsLayer->changeGeometry(i+1,g);
    }

    controlPointsLayer->commitChanges();
}

void QGSController::go_rend(){
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QGSController::go);
    timer->start(50);
}


