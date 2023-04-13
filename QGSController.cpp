
#include <QMessageBox>
#include <QDebug>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QFileDialog>
#include <QGridLayout>
#include "QGSController.h"

QGSController::QGSController(QWidget* Map){
    this->Map = Map;

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

    canvas =new QgsMapCanvas(this->Map);

    canvas->enableAntiAliasing(true);
    canvas->setMapSettingsFlags(canvas->mapSettings().flags() | QgsMapSettings::RenderPreviewJob);
    canvas->setParallelRenderingEnabled(true);
    canvas->setCachingEnabled(true);
    canvas->setPreviewJobsEnabled(true);
    canvas->setMapUpdateInterval(500); //ToDO::check possible values


    layers.push_back(controlPointsLayer);
    canvas->setLayers(layers);
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
            startLayer();

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
    if (layers.size()==0)
    {
        QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
        QgsVectorLayer* trajectoryPointsLayer = new QgsVectorLayer("Point", "Points", "memory");


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

        setCrs();

        layers.push_back(controlPointsLayer);
        layers.push_back(trajectoryPointsLayer);
    }
}

void QGSController::setCrs()
{
    crs.createFromProj("+proj=longlat +datum=WGS84 +no_defs");
    canvas->setDestinationCrs(crs);
}

void QGSController::activateSelecting(){
    QgsMapToolEmitPoint* emitPointTool = new QgsMapToolEmitPoint(canvas);
    canvas->setMapTool(emitPointTool);
    //TODO как-то перенести в MainWindow
    connect(emitPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addPoint);
}

void QGSController::addPoint(const QgsPointXY &point, Qt::MouseButton button){
    Points.push_back(point);
    controlPointsLayer->startEditing();

    QgsFeature feat;

    feat.setFields(controlPointsLayer->fields(), true);
    feat.setAttribute("fid", Points.size()-1);
    feat.setGeometry(QgsGeometry::fromPointXY(point));
    controlPointsLayer->addFeature(feat);
    controlPointsLayer->commitChanges();
}
