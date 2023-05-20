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

void QGSController::initVectorLayerWithSVG(QgsVectorLayer *layer, QString name, int size){
    layer->dataProvider()->addAttributes({{"type", QVariant::Int},{"angle",QVariant::Double}});
    layer->updateFields();

    QgsSvgMarkerSymbolLayer* svgL = new QgsSvgMarkerSymbolLayer(":/rec/img/"+name,size);
    QgsSymbol* s= QgsSymbol::defaultSymbol(layer->geometryType());
    s->changeSymbolLayer(0,svgL);

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

void QGSController::setVectorLayerColorAndScale(QgsVectorLayer *layer, QColor color,double scale)
{
    layer->startEditing();

    QgsSymbol* s= QgsSymbol::defaultSymbol(layer->geometryType());
    s->setColor(color);

    if (scale!=0)
    {
        QgsLineSymbolLayer* lineLayer =dynamic_cast<QgsLineSymbolLayer*>(s->symbolLayer(0)->clone()) ;
        lineLayer->setWidth(scale);
        s->changeSymbolLayer(0,lineLayer);
    }

    QgsRuleBasedRenderer::Rule* rule =new QgsRuleBasedRenderer::Rule(s,0,0);

    QgsRuleBasedRenderer* render= new QgsRuleBasedRenderer(rule);

    layer->setRenderer(render);
    layer->commitChanges();
}

void QGSController::startLayer()
{
    initVectorLayer(controlLineLayer);

    initVectorLayerWithSVG(controlPlanes,"plane1.svg",10);
    initVectorLayerWithSVG(rocketsLayer,"rocket.svg",6);
    initVectorLayerWithSVG(controlSAM,"zrk.svg",10);

    setVectorLayerColorAndScale(controlLinePointsLayer,QColor(Qt::black));
    setVectorLayerColorAndScale(rocketsLineLayer,QColor(Qt::darkRed));
    setVectorLayerColorAndScale(controlLineLayer,QColor(Qt::yellow),0.5);
    setVectorLayerColorAndScale(radarCirclesLayer,QColor(Qt::magenta),0.5);

    setCrs();
    layers.push_back(radarCirclesLayer);

    layers.push_back(controlPlanes);
    layers.push_back(rocketsLayer);
    
    layers.push_back(controlSAM);
    layers.push_back(controlLineLayer);
    layers.push_back(controlLinePointsLayer);
    layers.push_back(rocketsLineLayer);

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

void QGSController::addRocket(double x, double y, int id){
    addElementToLayer(rocketsLayer, QgsGeometry::fromPointXY(QgsPointXY(x, y)));
    addElementToLayer(rocketsLineLayer, QgsGeometry::fromMultiPolylineXY(QgsMultiPolylineXY(1)));
    rocketsPaths[id] = rocketsLineLayer->allFeatureIds().size()-1;
    rocketsId->push_back(id);
}

void QGSController::addCircleToLayer(QgsVectorLayer* layer, const QgsPointXY &point, const double radius){
    QgsCircle* circle = new QgsCircle(QgsPoint(point), radius);
    addElementToLayer(layer, QgsGeometry::fromWkt(circle->toCircularString()->asWkt()));
}

void QGSController::addLineToLayer(QgsVectorLayer* layer, const QgsPointXY &point1, const QgsPointXY &point2){
    addElementToLayer(layer, QgsGeometry::fromPolylineXY({point1, point2}));
}

void QGSController::addRadar(const QgsPointXY &point, Qt::MouseButton button){

    addElementToLayer(controlSAM, QgsGeometry::fromPointXY(point));

    emit createSAM(point.x(), point.y());
}

void QGSController::addRadarCircles(double x, double y, double radius){
    QgsPointXY point = QgsPointXY(x, y);
    for(int i = 1; i<=3; ++i)
        addCircleToLayer(radarCirclesLayer, point, radius*i/3);

    addLineToLayer(radarCirclesLayer, point+QgsVector(-radius,0.), point+QgsVector(radius, 0.));
    addLineToLayer(radarCirclesLayer, point+QgsVector(0.,-radius), point+QgsVector(0., radius));
}

void QGSController::showRadarZones(){
    if(radarCirclesLayer->opacity())
        radarCirclesLayer->setOpacity(0);
    else
        radarCirclesLayer->setOpacity(1);
    canvas->refresh();
}

void QGSController::addTrajToLayer(QgsGeometry geom, QString name){
    controlLineLayer->startEditing();
    QgsFeature feat;
    feat.setFields(controlLineLayer->fields(), true);
    feat.setAttribute("name", name);
    feat.setGeometry(geom);
    controlLineLayer->addFeature(feat);
    controlLineLayer->commitChanges();
}

void QGSController::addLine(bool checked){
    if(!linePoints->isEmpty()){
        trajId->push_back(globalLineId);
        qInfo() << globalLineId;
        emit sendLine(globalLineId, "Траектория "+QString::number(globalLineId));
        QgsGeometry geom= QgsGeometry();//Странно, почему нельзя просто поставить скобочки?
        geom.addPart(*linePoints, QgsWkbTypes::GeometryType::LineGeometry);
        addTrajToLayer(geom, "Траектория "+QString::number(globalLineId));
        globalLineId++;
        linePoints->clear();
        deletePointsForLine();
    }
}

void QGSController::deleteRocket(int id) {
    rocketsLayer->startEditing();
    QgsFeatureIds featIds = rocketsLayer->allFeatureIds();
    rocketsLayer->deleteFeature(*(featIds.begin()+rocketsId->indexOf(id)));
    rocketsLayer->commitChanges();
    rocketsId->remove(rocketsId->indexOf(id));
    emit continueRender();
}

void QGSController::deletePlane(int id) {
    controlPlanes->startEditing();
    QgsFeatureIds featIds = controlPlanes->allFeatureIds();
    controlPlanes->deleteFeature(*(featIds.begin()+planesId->indexOf(id)));
    controlPlanes->commitChanges();
    planesId->remove(planesId->indexOf(id));
    emit continueRender();
} 

void QGSController::addSavedLine(QVector<QPair<double, double>> vec){
    trajId->push_back(globalLineId);
    for(int i = 0; i<vec.size(); ++i)
        linePoints->push_back(QgsPointXY(vec[i].first, vec[i].second));
    emit sendLine(globalLineId, "Траектория "+QString::number(globalLineId));
    QgsGeometry geom= QgsGeometry();//Странно, почему нельзя просто поставить скобочки?
    geom.addPart(*linePoints, QgsWkbTypes::GeometryType::LineGeometry);
    addTrajToLayer(geom, "Траектория "+QString::number(globalLineId));
    globalLineId++;
    linePoints->clear();
}

void QGSController::loadSavedLines(QVector<QVector<QPair<double, double>>> lines, QVector<QList<double>> sendPlanes, QVector<QList<double>> sendSams){
    controlSAM->startEditing();
    rocketsLayer->startEditing();
    rocketsLineLayer->startEditing();
    controlPlanes->startEditing();
    controlLineLayer->startEditing();
    controlLinePointsLayer->startEditing();
    radarCirclesLayer->startEditing();
    controlSAM->deleteFeatures(controlSAM->allFeatureIds());
    for(int i = 0; i<sendSams.size(); ++i){
        QgsFeature feat;
        feat.setFields(controlSAM->fields(), true);
        feat.setAttribute("name", QString::number(int(controlSAM->featureCount())+1));
        feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(sendSams[i][0], sendSams[i][1])));
        controlSAM->addFeature(feat);
    }
    rocketsLayer->deleteFeatures(rocketsLayer->allFeatureIds());
    rocketsLineLayer->deleteFeatures(rocketsLineLayer->allFeatureIds());
    controlPlanes->deleteFeatures(controlPlanes->allFeatureIds());
    planesId->clear();
    for(int i = 0; i<sendPlanes.size(); ++i){
        QgsFeature feat;
        feat.setFields(controlPlanes->fields(), true);
        feat.setAttribute("name", QString::number(int(controlPlanes->featureCount())+1));
        feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(sendPlanes[i][0], sendPlanes[i][1])));
        feat.setAttribute("angle",sendPlanes[i][2]);
        controlPlanes->addFeature(feat);
        planesId->push_back(sendPlanes[i][3]);
    }
    controlLineLayer->deleteFeatures(controlLineLayer->allFeatureIds());
    controlLinePointsLayer->deleteFeatures(controlLinePointsLayer->allFeatureIds());
    radarCirclesLayer->deleteFeatures(radarCirclesLayer->allFeatureIds());
    rocketsId->clear();
    rocketsPaths.clear();
    trajId->clear();
    controlSAM->commitChanges();
    rocketsLayer->commitChanges();
    rocketsLineLayer->commitChanges();
    controlPlanes->commitChanges();
    controlLineLayer->commitChanges();
    controlLinePointsLayer->commitChanges();
    radarCirclesLayer->commitChanges();
    for(int i = 0; i<lines.size(); ++i)
        addSavedLine(lines[i]);
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
    connect(selectionPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addPointLine);
}

void QGSController::deleteLine(int id){
    controlLineLayer->startEditing();
    controlLineLayer->deleteFeature(*(controlLineLayer->allFeatureIds().begin()+trajId->indexOf(id)-1));
    controlLineLayer->commitChanges();
}

void QGSController::addPlaneToLine(int id){
    int tmp = trajId->indexOf(id);
    QgsPointXY point(controlLineLayer->getFeature(*(controlLineLayer->allFeatureIds().begin()+trajId->indexOf(id))).geometry().asMultiPolyline()[0][0]);
    sentChosenLine(id);
    addElementToLayerWithSVG(controlPlanes,QgsGeometry::fromPointXY(point));
}

void QGSController::sentChosenLine(int id){
    QVector<QPair<double, double>>* points = new QVector<QPair<double, double>>(0);
    QgsMultiPolylineXY polyline = controlLineLayer->getFeature(*(controlLineLayer->allFeatureIds().begin()+trajId->indexOf(id))).geometry().asMultiPolyline();
    for(QgsPolylineXY line : polyline)
        for(QgsPointXY point : line)
            points->push_back({point.x(), point.y()});
    emit sendPointsCoords(points);
}

void QGSController::catchNewPlaneId(int id){
    planesId->push_back(id);
}

void QGSController::lineChangeName(int id, QString name){
    controlLineLayer->startEditing();
    controlLineLayer->changeAttributeValue(trajId->indexOf(id),0,name);
    controlLineLayer->commitChanges();
}
//здесь чет плохой код

void QGSController::renderObject(QVector<QList<double>>* planes, QVector<QList<double>>* rockets){
    controlPlanes->startEditing();
    QgsFeatureIds featIds = controlPlanes->allFeatureIds(); 
    int k = 0;
    int id = -1;
    for(int i = 0; i < planes->size(); ++i){
        id = int(planes->at(k)[3]);
        QgsPointXY point = controlPlanes->getFeature(*(featIds.begin()+planesId->indexOf(id))).geometry().asPoint();
        point.set(planes->at(k)[0], planes->at(k)[1]);
        QgsGeometry g = QgsGeometry::fromPointXY(point);
        controlPlanes->changeGeometry(*(featIds.begin()+planesId->indexOf(id)), g);
        controlPlanes->changeAttributeValue(*(featIds.begin()+planesId->indexOf(id)),1,-planes->at(k)[2]*180/M_PI);
        k++;
    }
    controlPlanes->commitChanges();
    rocketsLayer->startEditing();
    rocketsLineLayer->startEditing();
    featIds = rocketsLayer->allFeatureIds();
    k = 0;
    for(int i = 0; i < rockets->size(); ++i){
        id = int(rockets->at(k)[3]);
        QgsPointXY point = rocketsLayer->getFeature(*(featIds.begin()+rocketsId->indexOf(id))).geometry().asPoint();
        point.set(rockets->at(k)[0], rockets->at(k)[1]);
        QgsGeometry g = QgsGeometry::fromPointXY(point);
        rocketsLayer->changeGeometry(*(featIds.begin()+rocketsId->indexOf(id)), g);
        rocketsLayer->changeAttributeValue(*(featIds.begin()+rocketsId->indexOf(id)),1,-rockets->at(k)[2]*180/M_PI);
        QgsMultiPolylineXY line = rocketsLineLayer->getFeature(*(rocketsLineLayer->allFeatureIds().begin()+rocketsPaths[id])).geometry().asMultiPolyline();
        qInfo() << rocketsPaths[id] << rocketsLineLayer->allFeatureIds().size();
        line[0].push_back(point);
        g = QgsGeometry::fromMultiPolylineXY(line);
        rocketsLineLayer->changeGeometry(*(rocketsLineLayer->allFeatureIds().begin()+rocketsPaths[id]), g);
        k++;
    }
    rocketsLayer->commitChanges();
    rocketsLineLayer->commitChanges();
}

void QGSController::mouseMoved(const QgsPointXY &p ){
    emit coordChanged(p.x(), p.y());
}

void QGSController::mapScaled( double s ){
    emit scaleChanged(s);
}
