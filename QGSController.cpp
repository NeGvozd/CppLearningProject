
#include <QMessageBox>
#include <QDebug>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QFileDialog>
#include "QGSController.h"

QGSController::QGSController(QWidget* Map){
    this->Map = Map;

    canvas =new QgsMapCanvas(this->Map);

    canvas->setCanvasColor("blue");

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
            dialog.close();

            if (flag==0)
            {
                QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
                QgsVectorLayer* trajectoryPointsLayer = new QgsVectorLayer("Point", "Points", "memory");

                layers.push_back(controlPointsLayer);
                layers.push_back(trajectoryPointsLayer);



                (dynamic_cast<QgsVectorLayer*>(layers[0]))->startEditing();
                (dynamic_cast<QgsVectorLayer*>(layers[0]))->dataProvider()->addAttributes({QgsField("fid", QVariant::Int)});
                (dynamic_cast<QgsVectorLayer*>(layers[0]))->updateFields();

                (dynamic_cast<QgsVectorLayer*>(layers[0]))->setLabelsEnabled(true);
                QgsPalLayerSettings pls;
                pls.fieldName = "fid";
                pls.placement = QgsPalLayerSettings::Placement::Line;
                QgsVectorLayerSimpleLabeling* simple_label = new QgsVectorLayerSimpleLabeling(pls);
                (dynamic_cast<QgsVectorLayer*>(layers[0]))->setLabeling(simple_label);
                (dynamic_cast<QgsVectorLayer*>(layers[0]))->commitChanges();

                QgsCoordinateReferenceSystem crs("EPSG:4326");
                canvas->setDestinationCrs(crs);


                flag=1;
            }

            QgsVectorLayer* newLayer = new QgsVectorLayer(layerPath, layerPath, "ogr");

            layers.push_back(newLayer);

            canvas->setLayers(layers);
            for(int i=2;i<layers.length();i++)
                canvas->setExtent(layers[i]->extent());
            canvas->refresh();
        }
    }
}