
#include <QMessageBox>
#include <QDebug>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QFileDialog>
#include <QGridLayout>
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

    //qInfo() << QgsSvgCache().getImageData("26562.svg");

    startLayer();

    QGridLayout* gl =new QGridLayout(this->Map);
    gl->addWidget(canvas);

    //Tools
    panTool= new QgsMapToolPan(canvas);

    //Здесь код для вставления картинки
/*    controlPointsLayer->startEditing();

    QgsFeatureRenderer * layerRenderer= controlPointsLayer->renderer();
    QgsSingleSymbolRenderer *mSingleRenderer = QgsSingleSymbolRenderer::convertFromRenderer(layerRenderer);
    QgsMarkerSymbol* symbol = new  QgsMarkerSymbol();
    QVariantMap mp;
       // mp[QString("fill")]= QString("red");
    mp[QString("name")]= QString("26562.svg");
    mp[QString("size")]= QString("6");
      //  mp[QString("outline")]=QString("black");
     //   mp[QString("outline-width")]=QString("6.8");
    QgsSvgMarkerSymbolLayer* planeLayer = new QgsSvgMarkerSymbolLayer("26562.svg");
    //planeLayer->setPath("26562.svg");
    //qInfo() << planeLayer->path();
    //planeLayer->setColor(QColor(1, 1, 0));
    QgsSymbolLayer* svgsymbol=planeLayer->create(mp);
//    QgsMarkerSymbol* newsym=symbol->createSimple(mp);
    QgsSymbol* newsym = QgsSymbol::defaultSymbol(controlPointsLayer->geometryType());
    newsym->deleteSymbolLayer(0);
    newsym->insertSymbolLayer(0, svgsymbol);
    QList<QgsRendererCategory> Categories;
    QgsRendererCategory MyCategorie = QgsRendererCategory(QVariant("1"),newsym,"26562.svg");
    Categories.append(MyCategorie);
    QgsCategorizedSymbolRenderer* lrenderer = new QgsCategorizedSymbolRenderer("RVER",Categories);
    controlPointsLayer->setRenderer(lrenderer);
//    controlPointsLayer->setRenderer(mSingleRenderer);
    controlPointsLayer->triggerRepaint();
    controlPointsLayer->commitChanges();*/
    
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

void QGSController::startLayer()
{
    initVectorLayer(controlPointsLayer);
    initVectorLayer(controlSquareLayer);
    initVectorLayer(controlLineLayer);

    setCrs();
    layers.push_back(radarCirclesLayer);
    layers.push_back(controlPointsLayer);
    layers.push_back(controlSquareLayer);
    layers.push_back(controlLineLayer);
    layers.push_back(controlLinePointsLayer);
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

void QGSController::addPoint(const QgsPointXY &point, Qt::MouseButton button){

    addElementToLayer(controlPointsLayer, QgsGeometry::fromPointXY(point)); //правильно ли так созданные объекты передавать не по указателю

    if(controlPointsLayer->featureCount()==1)
        if(tempLineId == -1){
        renderCycle();
        } else {
        canvas->unsetMapTool(pointTool);
        renderCycleLine();
        }
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
    controlLinePointsLayer->deleteFeatures(controlLinePointsLayer->allFeatureIds());
    controlLinePointsLayer->commitChanges();
}

void QGSController::addPointLine(const QgsPointXY &point, Qt::MouseButton button){
    addElementToLayer(controlLinePointsLayer, QgsGeometry::fromPointXY(point));
    linePoints->push_back(point);
}

void QGSController::moving(){
    controlPointsLayer->startEditing();

    for (int i=0;i<controlPointsLayer->featureCount();i++)
    {
        QgsPointXY myP=controlPointsLayer->getFeature(i+1).geometry().asPoint();
        myP.setX(myP.x()+0.1);
        myP.setY(myP.y()+0.1);
        QgsGeometry g =QgsGeometry::fromPointXY(myP);
        controlPointsLayer->changeGeometry(i+1,g);
    }

    controlPointsLayer->commitChanges();
}

void QGSController::renderCycle(){
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QGSController::moving);
    timer->start(50);
}

void QGSController::selectionPoints(){
    selectionPointTool = new QgsMapToolEmitPoint(canvas);
    canvas->setMapTool(selectionPointTool);
    //TODO как-то перенести в MainWindow
    connect(selectionPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &QGSController::addPointLine);
    //connect(Map->SetLine, &QPushButton::Pressed, this, &QGSController::addLine);
}

void QGSController::getLineId(int id){
    this->tempLineId = id;
    activateSelectingPoint();
}

void QGSController::lineChangeName(int id, QString name){
    controlLineLayer->startEditing();
    controlLineLayer->changeAttributeValue(id,0,name);
    controlLineLayer->commitChanges();
}

QPair<double, double> QGSController::calculatingLineVector(double x, double y){
    return {x/sqrt(x*x+y*y), y/sqrt(x*x+y*y)};
}

void QGSController::lineFollow(){
    if(isMoving){
        controlPointsLayer->startEditing();

        QgsPointXY myP=controlPointsLayer->getFeature(controlPointsLayer->featureCount()).geometry().asPoint();
        QVector<QgsPolylineXY> followLines=controlLineLayer->getFeature(tempLineId).geometry().asMultiPolyline();
        if(tempNumberOfLine==-1){
            myP.set(followLines[0][0].x(), followLines[0][0].y());
            tempNumberOfLine++;
            QgsGeometry g =QgsGeometry::fromPointXY(myP);
            controlPointsLayer->changeGeometry(tempLineId,g);

            controlPointsLayer->commitChanges();
            return;
        }
        QVector<QgsPointXY> curLine = followLines[0];
        QPair<double, double> pointVec = calculatingLineVector(curLine[tempNumberOfLine+1].x()-curLine[tempNumberOfLine].x(), curLine[tempNumberOfLine+1].y()-curLine[tempNumberOfLine].y());
        while(abs(myP.x()+0.3*pointVec.first-curLine[tempNumberOfLine].x())>abs(curLine[tempNumberOfLine+1].x()-curLine[tempNumberOfLine].x())){
            tempNumberOfLine+=1;
            if(tempNumberOfLine==curLine.size()-1){
                isMoving = false;
                return;
                }
            myP.set(curLine[tempNumberOfLine].x(), curLine[tempNumberOfLine].y());
            return;
        }
        myP.setX(myP.x()+0.1*pointVec.first);
        myP.setY(myP.y()+0.1*pointVec.second);
        QgsGeometry g =QgsGeometry::fromPointXY(myP);
        controlPointsLayer->changeGeometry(tempLineId,g);

        controlPointsLayer->commitChanges();
    }
}

void QGSController::renderCycleLine(){
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QGSController::lineFollow);
    timer->start(50);
}

void QGSController::mouseMoved(const QgsPointXY &p ){
    emit coordChanged(p.x(), p.y()); //ПРАВИЛЬНО ЛИ ДЕЛАТЬ ПЕРЕБРОСКУ ПРОМЕЖУТОЧНОГО СИГНАЛА? ПРИ ТОМ, ЧТО КАНВАС - ПРИВАТНЫЙ
}

void QGSController::mapScaled( double s ){
    emit scaleChanged(s);
}
