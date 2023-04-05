#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <qgsgeometry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsmarkersymbollayer.h>
#include <QToolBar>
#include <qgsmaptoolpan.h>
#include <qgsmaptoolemitpoint.h>
#include <qgslabeling.h>
#include <qgsfield.h>
#include <qgsvectorlayerlabeling.h>
#include <qgspallabeling.h>
#include <qgsrulebasedrenderer.h>
#include <QStatusBar>
#include <qgssymbol.h>
#include <qgsgeometry.h>
#include <QTest>

class MapWindow : public QWidget
{
    Q_OBJECT

public:
    MapWindow(QWidget *parent = nullptr);
    ~MapWindow();

private slots:
    void activatePan();
    void clearAllPoints();
    void play();
    void activateSelecting();
    void addControlPoint(const QgsPointXY &point, Qt::MouseButton button);

private:
    QgsMapCanvas* map = nullptr;

    QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
    QgsVectorLayer* trajectoryPointsLayer = new QgsVectorLayer("Point", "Points", "memory");

    QgsVectorLayer* earthLayer = new QgsVectorLayer("/home/kretki/testQGS/kx-world-land-areas-110-million-SHP/world-land-areas-110-million.shp", "earth", "ogr");
    QgsVectorLayer* oceanLayer = new QgsVectorLayer("/home/kretki/testQGS/kx-world-bathymetry-110-million-SHP/world-bathymetry-110-million.shp", "water", "ogr");

    QToolBar* toolBar;

    QVector<QgsPointXY> twoPoints;

    QWidget* centr;

    void addTrajectoryPoint(QgsPointXY point);
};
#endif // MAPWINDOW_H
