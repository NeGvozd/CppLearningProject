
#include <QMessageBox>
#include <QDebug>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QFileDialog>
#include "QGSController.h"

QGSController::QGSController(QWidget* Map){
    this->Map = Map;
}

QGSController::~QGSController(){
    delete Map;
}
void QGSController::setupQGS()
{
    canvas =new QgsMapCanvas(this->Map);

    canvas->setWindowFlags(canvas->windowFlags() & ~Qt::WindowStaysOnBottomHint);
    canvas->setCanvasColor("blue");

    QGridLayout* gl =new QGridLayout(this->Map);
    gl->addWidget(canvas);
    
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