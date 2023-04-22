

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

class QGSController:public QObject{
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
public slots:
    void addLine(bool checked);
private slots:
    void addPoint(const QgsPointXY &point, Qt::MouseButton button);
    void addSquare(const QgsPointXY &point, Qt::MouseButton button);
    void addPointLine(const QgsPointXY &point, Qt::MouseButton button);

    void moving();
private:
    QgsMapToolPan* panTool;

    QgsMapCanvas* canvas;
    QWidget* Map;

    QgsCoordinateReferenceSystem crs;
    QList<QgsMapLayer *> layers;

    QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
    QgsVectorLayer* controlSquareLayer = new QgsVectorLayer("Polygon", "Points2", "memory");


    QgsVectorLayer* controlLineLayer = new QgsVectorLayer("Linestring", "Points3", "memory");
    QgsVectorLayer* controlLinePointsLayer = new QgsVectorLayer("Point", "Points31", "memory");

    QVector<QgsPointXY>* linePoints = new QVector<QgsPointXY>();

};
