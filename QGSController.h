

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

#include <QVector>
#include <qgslinestring.h>
#include <qgswkbtypes.h>

#include <QTreeWidget>
#include <qgscircle.h>

#pragma once

class QGSController:public QObject{
    Q_OBJECT
public:
    QGSController(QWidget* Map);
    ~QGSController();
    void addLayer();
    void startLayer();
    void setCrs();
    void activateSelectingPoint();
    void activateSelectingSquare();
    void renderCycle();

    void selectionPoints();

    void activatePanTool();
    void getLineId(int id);
    void renderCycleLine();
    QPair<double, double> calculatingLineVector(double x, double y);
signals:
    void sendLine(int id, QString name);
public slots:
    void addLine(bool checked);
private slots:
    void addPoint(const QgsPointXY &point, Qt::MouseButton button);
    void addRadar(const QgsPointXY &point, Qt::MouseButton button);
    void addPointLine(const QgsPointXY &point, Qt::MouseButton button);

    void moving();

    void lineFollow();
private:
    QgsMapToolPan* panTool;
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

    int tempLineId = -1;
    int tempNumberOfLine = -1;
    QgsMapToolEmitPoint* PointTool;
    bool isMoving = true;
public:
    QgsMapToolEmitPoint* selectionPointTool;
};
