#include "QGSController.h"

QGSController::QGSController(QWidget* Map){
    this->Map = Map;

    canvas =new QgsMapCanvas(this->Map);

    canvas->enableAntiAliasing(true);
    canvas->setMapSettingsFlags(canvas->mapSettings().flags() | QgsMapSettings::RenderPreviewJob);
    canvas->setParallelRenderingEnabled(true);
    canvas->setCachingEnabled(true);
    canvas->setPreviewJobsEnabled(true);
    canvas->setMapUpdateInterval(500); //ToDO::check possible values


    startLayer();

    QGridLayout* gl =new QGridLayout(this->Map);
    gl->addWidget(canvas);

    //Tools
    panTool= new QgsMapToolPan(canvas);


    connect(canvas, &QgsMapCanvas::xyCoordinates, this, &QGSController::mouseMoved);
    connect(canvas, &QgsMapCanvas::scaleChanged, this, &QGSController::mapScaled);
}

void QGSController::activatePanTool() {
    if(!panTool->isActive())
        canvas->setMapTool(panTool);
    else{
        canvas->unsetMapTool(panTool);
    }
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
            qInfo()<<layerPath;
            QgsVectorLayer* newLayer = new QgsVectorLayer(layerPath, layerPath, "ogr");

            layers.push_back(newLayer);

            crs=layers.at(layers.size()-1)->crs();

            canvas->setLayers(layers);
            for(int i=2;i<layers.length();i++)
                canvas->setExtent(layers[i]->extent());

            canvas->refresh();
            qInfo() << canvas->size();
        }
    }
}

void QGSController::initVectorLayer(QgsVectorLayer* layer){
    layer->startEditing();
    layer->dataProvider()->addAttributes({QgsField("name", QVariant::String)});
    layer->updateFields();

    //Комментарии принадлежат к коду ниже
    //Устанавливает, должны ли быть включены метки для слоя.
    layer->setLabelsEnabled(true);
    //Contains settings for how a map layer will be labeled.
    QgsPalLayerSettings pls;
    pls.fieldName = "name";

    //Так и нужно(для понимания стоит перейти в изначальный класс)
    pls.placement = QgsPalLayerSettings::Placement::Line;

    //Basic implementation of the labeling interface.
    QgsVectorLayerSimpleLabeling* simple_label = new QgsVectorLayerSimpleLabeling(pls);
    layer->setLabeling(simple_label);
    layer->commitChanges();
}

void QGSController::initVectorLayerWithSVG(QgsVectorLayer *layer){
    layer->dataProvider()->addAttributes({{"type", QVariant::Int},{"angle",QVariant::Double}});
    layer->updateFields();

    QgsSvgMarkerSymbolLayer* svgL = new QgsSvgMarkerSymbolLayer(":/rec/img/airplane.svg",10);
    QgsSymbol* s= QgsSymbol::defaultSymbol(layer->geometryType());
    s->changeSymbolLayer(0,svgL);

    //Magic?
    QgsMarkerSymbol* m =dynamic_cast<QgsMarkerSymbol*>(s);
    //A store for object properties.
    QgsProperty p;
    p.setField("angle");
    m->setDataDefinedAngle(p);

    QgsRuleBasedRenderer::Rule* rule =new QgsRuleBasedRenderer::Rule(s,0,0);

    QgsRuleBasedRenderer* render= new QgsRuleBasedRenderer(rule);

    layer->setRenderer(render);
    layer->commitChanges();
}

void QGSController::startLayer()
{
    initVectorLayer(controlPointsLayer);
    initVectorLayer(controlSquareLayer);
    initVectorLayer(controlLineLayer);

    initVectorLayerWithSVG(controlPlanes);

    setCrs();
    layers.push_back(radarCirclesLayer);
    layers.push_back(controlPointsLayer);
    layers.push_back(controlSquareLayer);
    layers.push_back(controlLineLayer);
    layers.push_back(controlLinePointsLayer);

    layers.push_back(controlPlanes);

    layers.push_back(baseEarthLayer);
    layers.push_back(baseWaterLayer);


    crs=layers.at(layers.size()-1)->crs();

    canvas->setLayers(layers);
    for(int i=2;i<layers.length();i++)
        canvas->setExtent(layers[i]->extent());

    canvas->refresh();
}

void QGSController::setCrs()
{
    crs.createFromProj("+proj=longlat +datum=WGS84 +no_defs");
    canvas->setDestinationCrs(crs);
}

void QGSController::activateSelectingPoint(){

    pointTool = new QgsMapToolEmitPoint(canvas);
    canvas->setMapTool(pointTool);
    //TODO как-то перенести в MainWindow?
    connect(pointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addPoint);
}


void QGSController::activateSelectingSquare(){
    QgsMapToolEmitPoint* emitPointTool= new QgsMapToolEmitPoint(canvas);
    canvas->setMapTool(emitPointTool);
    connect(emitPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addRadar);
}

void QGSController::addElementToLayer(QgsVectorLayer* layer, QgsGeometry geom){
    layer->startEditing();
    QgsFeature feat;
    //Assigns a field map with the feature to allow attribute access by attribute name.
    feat.setFields(layer->fields(), true);

    feat.setAttribute("name", QString::number(int(layer->featureCount())+1));
    feat.setGeometry(geom);
    layer->addFeature(feat);
    layer->commitChanges();
}

void QGSController::addElementToLayerWithSVG(QgsVectorLayer *layer, QgsGeometry geom){
    layer->startEditing();


    QgsFeature feat;
    //Assigns a field map with the feature to allow attribute access by attribute name.
    feat.setFields(layer->fields(), true);
    feat.setGeometry(geom);

    double angle=90;
    feat.setAttribute("angle",angle);
    //feat.setAttribute("type",0);


    layer->addFeature(feat);

    layer->commitChanges();
}

void QGSController::addPoint(const QgsPointXY &point, Qt::MouseButton button){
    addElementToLayer(controlPointsLayer, QgsGeometry::fromPointXY(point)); //правильно ли так созданные объекты передавать не по указателю
}

void QGSController::addCircleToLayer(QgsVectorLayer* layer, const QgsPointXY &point, const double radius){
    QgsCircle* circle = new QgsCircle(QgsPoint(point), radius);
    addElementToLayer(layer, QgsGeometry::fromWkt(circle->toCircularString()->asWkt()));
}

void QGSController::addLineToLayer(QgsVectorLayer* layer, const QgsPointXY &point1, const QgsPointXY &point2){
    addElementToLayer(layer, QgsGeometry::fromPolylineXY({point1, point2}));
}

void QGSController::addSquareToLayer(QgsVectorLayer* layer, const QgsPointXY &point, const double size){
    addElementToLayer(layer, QgsGeometry::fromRect(QgsRectangle(point+QgsVector(-size/2,-size/2),point+QgsVector(size/2,size/2))));
}

void QGSController::addRadar(const QgsPointXY &point, Qt::MouseButton button){

    addSquareToLayer(controlSquareLayer, point, 1.);

    addCircleToLayer(radarCirclesLayer, point, 2.);
    addCircleToLayer(radarCirclesLayer, point, 4.);
    addCircleToLayer(radarCirclesLayer, point, 6.);

    addLineToLayer(radarCirclesLayer, point+QgsVector(-6.,0.), point+QgsVector(6., 0.));
    addLineToLayer(radarCirclesLayer, point+QgsVector(0.,-6.), point+QgsVector(0., 6.));

    emit createSAM(point.x(), point.y());
}

void QGSController::showRadarZones(){
    if(layers.contains(radarCirclesLayer))
        layers.removeOne(radarCirclesLayer);
    else
        layers.push_back(radarCirclesLayer);

    canvas->setLayers(layers);
    for(int i=2;i<layers.length();i++)
        canvas->setExtent(layers[i]->extent());

    canvas->refresh();
}

void QGSController::addLine(bool checked){
    if(!linePoints->isEmpty()){
        emit sendLine(int(controlLineLayer->featureCount())+1, QString::number(int(controlLineLayer->featureCount())+1));
        QgsGeometry geom= QgsGeometry();//Странно, почему нельзя просто поставить скобочки?
        geom.addPart(*linePoints, QgsWkbTypes::GeometryType::LineGeometry);
        addElementToLayer(controlLineLayer, geom);
        linePoints->clear();
        deletePointsForLine();
    }
}

void QGSController::deletePointsForLine(){
    controlLinePointsLayer->startEditing();
    QgsFeatureIds featIds = controlLinePointsLayer->allFeatureIds(); 
    QVector<QPair<double, double>>* linePoints = new QVector<QPair<double, double>>;
    for(auto i = featIds.begin(); i != featIds.end(); ++i){
        QgsPointXY point = controlLinePointsLayer->getFeature(*i).geometry().asPoint();
        linePoints->push_back({point.x(), point.y()});
    }
    controlLinePointsLayer->deleteFeatures(controlLinePointsLayer->allFeatureIds());
    emit createLine(linePoints);
    controlLinePointsLayer->commitChanges();
}

void QGSController::addPointLine(const QgsPointXY &point, Qt::MouseButton button){
    if (button==Qt::LeftButton){
        addElementToLayer(controlLinePointsLayer, QgsGeometry::fromPointXY(point));
        linePoints->push_back(point);
    }
    else
        addLine(1);
}

void QGSController::selectionPoints(){
    selectionPointTool = new QgsMapToolEmitPoint(canvas);
    canvas->setMapTool(selectionPointTool);
    //TODO как-то перенести в MainWindow
    connect(selectionPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addPointLine);
    //connect(Map->SetLine, &QPushButton::Pressed, this, &QGSController::addLine);
}

void QGSController::getLineId(int id){
    QVector<int>l{id,0,0};
    li_P_Nl.append(l);
    addPointToLine(id);
}

void QGSController::addPointToLine(int id){
    QgsPointXY point(controlLineLayer->getFeature(id).geometry().asMultiPolyline()[0][0]);
    sentChosenLine(id);
    addElementToLayerWithSVG(controlPlanes,QgsGeometry::fromPointXY(point));

    li_P_Nl[li_P_Nl.size()-1][1]=controlPointsLayer->featureCount();
}

void QGSController::sentChosenLine(int id){
    QVector<QPair<double, double>>* points = new QVector<QPair<double, double>>(0);
    QgsMultiPolylineXY polyline = controlLineLayer->getFeature(id).geometry().asMultiPolyline();
    for(QgsPolylineXY line : polyline)
        for(QgsPointXY point : line)
            points->push_back({point.x(), point.y()});
    emit sendPointsCoords(points);
}

void QGSController::lineChangeName(int id, QString name){
    controlLineLayer->startEditing();
    controlLineLayer->changeAttributeValue(id,0,name);
    controlLineLayer->commitChanges();
}

void QGSController::renderObject(QVector<QPair<double, double>>* sams, QVector<QList<double>>* planes){
    //Planes
    controlPlanes->startEditing();
    QgsFeatureIds featIds = controlPlanes->allFeatureIds();
    int k = 0;
    for(auto i = featIds.begin(); i != featIds.end(); ++i){
        QgsPointXY point = controlPlanes->getFeature(*i).geometry().asPoint();
        point.set(planes->at(k)[0], planes->at(k)[1]);
        QgsGeometry g = QgsGeometry::fromPointXY(point);
        controlPlanes->changeGeometry(*i, g);
        controlPlanes->changeAttributeValue(*i,1,-planes->at(k)[2]*180/M_PI);
        k++;
    }
    controlPlanes->commitChanges();

/*
    controlPointsLayer->startEditing();
    featIds = controlPointsLayer->allFeatureIds();
    k = 0;
    for(auto i = featIds.begin(); i != featIds.end(); ++i){
        QgsPointXY point = controlPointsLayer->getFeature(*i).geometry().asPoint();
        point.set(planes->at(k)[0], planes->at(k)[1]);
        QgsGeometry g = QgsGeometry::fromPointXY(point);
        controlPointsLayer->changeGeometry(*i, g);
        k++;
    }
    controlPointsLayer->commitChanges();*/
    controlSquareLayer->startEditing();
    featIds = controlSquareLayer->allFeatureIds();
    k = 0;
    for(auto i = featIds.begin(); i != featIds.end(); ++i){
        QgsPointXY point = controlSquareLayer->getFeature(*i).geometry().asPoint();
        point.set(sams->at(k).first, sams->at(k).second);
        QgsGeometry g = QgsGeometry::fromPointXY(point);
        controlSquareLayer->changeGeometry(*i, g);
        k++;
    }
    controlSquareLayer->commitChanges();
}

void QGSController::mouseMoved(const QgsPointXY &p ){
    emit coordChanged(p.x(), p.y());
}

void QGSController::mapScaled( double s ){
    emit scaleChanged(s);
}
