

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

class QGSController:public QObject{
public:
    QGSController(QWidget* Map);
    ~QGSController();
    void addLayer();
    void startLayer();
    void setCrs();
    void activateSelectingPoint();
    void activateSelectingSquare();
    void go_rend();
private slots:
    void addPoint(const QgsPointXY &point, Qt::MouseButton button);
    void addSquare(const QgsPointXY &point, Qt::MouseButton button);

    void go();
private:


    QgsMapCanvas* canvas;
    QWidget* Map;

    QgsCoordinateReferenceSystem crs;
    QList<QgsMapLayer *> layers;

    QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
    QgsVectorLayer* controlSquareLayer = new QgsVectorLayer("Polygon", "Points", "memory");
};
