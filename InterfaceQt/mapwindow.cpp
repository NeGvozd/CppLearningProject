#include "mapwindow.h"

MapWindow::MapWindow(QWidget *parent) : QWidget(parent)
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

    map = new QgsMapCanvas(this);
    map->setLayers({controlPointsLayer, trajectoryPointsLayer, earthLayer, oceanLayer});
    map->setExtent(earthLayer->extent());
    QgsCoordinateReferenceSystem crs("EPSG:4326");
    map->setDestinationCrs(crs);
    map->refresh();

    centr = new QWidget();
    centr = map;

    this->setMinimumSize(800, 600);

/*    toolBar = new QToolBar(this);

    QAction* activatePanAction = new QAction(QIcon("/home/kretki/testQGS/icons/grab.svg"), "Пан", toolBar);
    QAction* activateSelectMode = new QAction(QIcon("/home/kretki/testQGS/icons/select.svg"), "Выбор начальной и конечной точек", toolBar);
    QAction* playAction = new QAction(QIcon("/home/kretki/testQGS/icons/play.svg"), "Запуск", toolBar);
    QAction* clearAction = new QAction(QIcon("/home/kretki/testQGS/icons/back2.svg"), "Очистить точки", toolBar);

    toolBar->addAction(activatePanAction);
    toolBar->addSeparator();
    toolBar->addAction(activateSelectMode);
    toolBar->addSeparator();
    toolBar->addAction(playAction);
    toolBar->addSeparator();
    toolBar->addAction(clearAction);

    connect(activatePanAction, &QAction::triggered, this, &MapWindow::activatePan);
    connect(activateSelectMode, &QAction::triggered, this, &MapWindow::activateSelecting);
    connect(playAction, &QAction::triggered, this, &MapWindow::play);
    connect(clearAction, &QAction::triggered, this, &MapWindow::clearAllPoints);

*///    this->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
}

MapWindow::~MapWindow()
{
    delete map;
    delete controlPointsLayer;
    delete trajectoryPointsLayer;
    delete earthLayer;
    delete oceanLayer;
//    delete toolBar;
}

void MapWindow::activatePan()
{
    QgsMapToolPan* panTool = new QgsMapToolPan(map);
    map->setMapTool(panTool);
}

void MapWindow::clearAllPoints()
{
    twoPoints.clear();

    controlPointsLayer->startEditing();
    QgsFeature f;
    QgsFeatureIterator iter = controlPointsLayer->getFeatures();
    while(iter.nextFeature(f))
        controlPointsLayer->deleteFeature(f.id());
    controlPointsLayer->commitChanges();

    trajectoryPointsLayer->startEditing();
    QgsFeature f1;
    QgsFeatureIterator iter1 = trajectoryPointsLayer->getFeatures();
    while(iter1.nextFeature(f1))
        trajectoryPointsLayer->deleteFeature(f1.id());
    trajectoryPointsLayer->commitChanges();

}
void MapWindow::play()
{
    if (twoPoints.empty())
        return;

    this->setEnabled(false);

    double xdiff = twoPoints[1].x() - twoPoints[0].x();
    double ydiff = twoPoints[1].y() - twoPoints[0].y();

    int stepsCount = 10;

    for (auto i = 0; i < stepsCount; i++)
    {
        addTrajectoryPoint({twoPoints[0].x() + i * xdiff / 10.0,  twoPoints[0].y() + i * ydiff / 10.0});
        QTest::qWait(1000);
    }

    this->setEnabled(true);
}

void MapWindow::addTrajectoryPoint(QgsPointXY point)
{
    QgsFeature f;
    f.setFields(trajectoryPointsLayer->fields(), true);

    f.setGeometry(QgsGeometry::fromPointXY(point));

    trajectoryPointsLayer->startEditing();
    trajectoryPointsLayer->addFeature(f);
    trajectoryPointsLayer->commitChanges();
}

void MapWindow::activateSelecting()
{
    QgsMapToolEmitPoint* emitPointTool = new QgsMapToolEmitPoint(map);
    map->setMapTool(emitPointTool);

    connect(emitPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &MapWindow::addControlPoint);
}

void MapWindow::addControlPoint(const QgsPointXY &point, Qt::MouseButton button)
{
    if (twoPoints.size() < 2)
    {
        twoPoints.push_back(point);

        controlPointsLayer->startEditing();

        QgsFeature feat;
        feat.setFields(controlPointsLayer->fields(), true);
        feat.setAttribute("fid", twoPoints.size() - 1);
        feat.setGeometry(QgsGeometry::fromPointXY(point));
        controlPointsLayer->addFeature(feat);
        controlPointsLayer->commitChanges();
    }
    else
    {
        activatePan();
    }
}
