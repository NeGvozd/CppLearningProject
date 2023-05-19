

// Если у вас нет Qgs, то вырубайте
#include <qgsmapcanvas.h>
#include <qlayout.h>
#include <qgsvectorlayer.h>
#include <utility>
#include <qgssymbol.h>
#include <qgsgeometry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsmarkersymbollayer.h>
#include <qgsmaptoolpan.h>
#include <qgsvectorfilewriter.h>
#include <qgslabeling.h>
#include <qgsvectorlayerlabeling.h>
#include <qgspallabeling.h>
#include <qgsrulebasedrenderer.h>
#include <qgsfield.h>
#include <qgsmaptoolemitpoint.h>
#include <qgsmaptoolpan.h>
#include <qgsmaptoolidentifyfeature.h>
#include <qgslinesymbollayer.h>

#include <qmap.h>

#include <QObject>
#include <QVector>
#include <qgslinestring.h>
#include <qgswkbtypes.h>

#include <qgscircle.h>

#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QMap>

#include <qgsrulebasedrenderer.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsmarkersymbollayer.h>

// #include <qgssvgcache.h> //мб для svg
#include <qgscategorizedsymbolrenderer.h>

#pragma once

class QGSController : public QObject
{
    Q_OBJECT
public:
    QGSController(QWidget *Map);
    ~QGSController();
    void addLayer();
    void startLayer();
    void setCrs();

    void selectionPoints();

    void activatePanTool();
    QPair<double, double> calculatingLineVector(double x, double y);

    void addCircleToLayer(QgsVectorLayer *layer, const QgsPointXY &point, const double radius);
    void addLineToLayer(QgsVectorLayer *layer, const QgsPointXY &point1, const QgsPointXY &point2);

private:
    void deletePointsForLine();

    void initVectorLayer(QgsVectorLayer *layer);
    void initVectorLayerWithSVG(QgsVectorLayer *layer, QString name, int size);

    void setVectorLayerColorAndScale(QgsVectorLayer *layer, QColor color, double scale=0);

    void addElementToLayer(QgsVectorLayer *layer, QgsGeometry geom);
    void addElementToLayerWithSVG(QgsVectorLayer *layer, QgsGeometry geom);

    void sentChosenLine(int id);
signals:
    void sendPointsCoords(QVector<QPair<double, double>> *points);
    void sendLine(int id, QString name);
    void coordChanged(double x, double y);
    void scaleChanged(double s);
    void createLine(QVector<QPair<double, double>> *linePoints);
    void createSAM(double x, double y);
    void continueRender();
public slots:
    void addLine(bool checked);
    void showRadarZones();
    void lineChangeName(int id, QString name);
    void activateSelectingSquare();
    void addPointToLine(int id);

    void renderObject(QVector<QList<double>> *planes, QVector<QList<double>> *rockets);
    void addRocket(double x, double y, int id);
    void addRadarCircles(double x, double y, double radius);
    void deleteRocket(int pos);
    void deleteLine(int id);
    void deletePlane(int pos);
    void catchNewPlaneId(int id);

private slots:
    void addRadar(const QgsPointXY &point, Qt::MouseButton button);
    void addPointLine(const QgsPointXY &point, Qt::MouseButton button);
    void mouseMoved(const QgsPointXY &p);
    void mapScaled(double s);

private:
    QgsMapToolPan *panTool;
    QgsMapToolEmitPoint *pointTool;

    QgsMapCanvas *canvas;

    QWidget *Map;

    QgsCoordinateReferenceSystem crs;
    QList<QgsMapLayer *> layers;

    QgsVectorLayer *controlSAM = new QgsVectorLayer("Point", "SAM", "memory");

    QgsVectorLayer *rocketsLayer = new QgsVectorLayer("Point", "Rockets", "memory");
    QgsVectorLayer *rocketsLineLayer = new QgsVectorLayer("multilinestring", "RocketsLine", "memory");

    QgsVectorLayer *baseWaterLayer = new QgsVectorLayer("../CppLearningProject/maps/world-bathymetry-110-million.shp", "water", "ogr");
    QgsVectorLayer *baseEarthLayer = new QgsVectorLayer("../CppLearningProject/maps/world-land-areas-110-million.shp", "earth", "ogr");

    QgsVectorLayer *controlPlanes = new QgsVectorLayer("Point", "Planes", "memory");

    QgsVectorLayer *controlLineLayer = new QgsVectorLayer("multilinestring", "LineLayer", "memory");
    QgsVectorLayer *controlLinePointsLayer = new QgsVectorLayer("Point", "LinePointsLayer", "memory");

    QgsVectorLayer *radarCirclesLayer = new QgsVectorLayer("multilinestring", "RadarCircles", "memory");

    QVector<QgsPointXY> *linePoints = new QVector<QgsPointXY>();

    QVector<int>* planesId = new QVector<int>();
    QVector<int>* rocketsId = new QVector<int>();
    QMap<int, int> rocketsPaths = QMap<int, int>();


public:
    QgsMapToolEmitPoint *selectionPointTool;
};
