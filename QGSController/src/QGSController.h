

//Если у вас нет Qgs, то вырубайте
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

#include <qmap.h>

#include <QVector>
#include <qgslinestring.h>
#include <qgswkbtypes.h>

#include <qgscircle.h>

#include <QDebug>
#include <QDialog>
#include <QFileDialog>

//#include <qgssvgcache.h> //мб для svg
#include <qgscategorizedsymbolrenderer.h>

#pragma once

class QGSController:public QObject{
    Q_OBJECT
public:
    QGSController(QWidget* Map);
    ~QGSController();
    void addLayer();
    void addPointToLine(int id);
    void startLayer();
    void setCrs();

    void activateSelectingPoint();

    void selectionPoints();

    void activatePanTool();
    QPair<double, double> calculatingLineVector(double x, double y);

    void addCircleToLayer(QgsVectorLayer* layer, const QgsPointXY &point, const double radius);
    void addLineToLayer(QgsVectorLayer* layer, const QgsPointXY &point1, const QgsPointXY &point2);
    void addSquareToLayer(QgsVectorLayer* layer, const QgsPointXY &point, const double size);
private:
    void deletePointsForLine();
    void initVectorLayer(QgsVectorLayer* layer);
    void addElementToLayer(QgsVectorLayer* layer, QgsGeometry geom);
    void sentChosenLine(int id);
signals:
    void sendPointsCoords(QVector<QPair<double, double>>* points);
    void sendLine(int id, QString name);
    void coordChanged(double x, double y);
    void scaleChanged(double s);
    void createLine(QVector<QPair<double, double>>* linePoints);
    void createSAM(double x, double y);
public slots:
    void addLine(bool checked);
    void showRadarZones();
    void getLineId(int id);
    void lineChangeName(int id, QString name);
    void activateSelectingSquare();

    void renderObject(QVector<QPair<double, double>>* sams, QVector<QPair<double, double>>* planes);

private slots:
    void addPoint(const QgsPointXY &point, Qt::MouseButton button);
    void addRadar(const QgsPointXY &point, Qt::MouseButton button);
    void addPointLine(const QgsPointXY &point, Qt::MouseButton button);
    void mouseMoved(const QgsPointXY &p );
    void mapScaled( double s );
    
private:
    QgsMapToolPan* panTool;
    QgsMapToolEmitPoint* pointTool;

    QgsMapCanvas* canvas;
    

    QWidget* Map;

    QgsCoordinateReferenceSystem crs;
    QList<QgsMapLayer *> layers;

    QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
    QgsVectorLayer* controlSquareLayer = new QgsVectorLayer("Polygon", "Points2", "memory");


    QgsVectorLayer* controlLineLayer = new QgsVectorLayer("multilinestring", "Points3", "memory");
    QgsVectorLayer* controlLinePointsLayer = new QgsVectorLayer("Point", "Points31", "memory");

    QgsVectorLayer* radarCirclesLayer = new QgsVectorLayer("multilinestring", "Circles", "memory");

    QVector<QgsPointXY>* linePoints = new QVector<QgsPointXY>();

    //QVector<QVector<int>> lineId-Point-Numberline;
    QVector<QVector<int>> li_P_Nl;



public:
    QgsMapToolEmitPoint* selectionPointTool;
};
