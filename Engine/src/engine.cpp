#include "engine.h"
#include <QDebug>

Engine::Engine() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Engine::moveObjects);
    sendTimer = new QTimer(this);
    connect(sendTimer, &QTimer::timeout, this, &Engine::packObjects);
};

void Engine::createNewObject(InfoAboutElement element){
    switch (element.type)
    {
        case AIRPLANS:
        {
            std::unique_ptr<Plane> plane = ObjectFactory::CreatePlane(element.mass,element.speed,element.name, nullptr);

            planes.push_back(std::move(plane)); // это не будет работать, если отменить создание объекта до создания любого объекта, что плохо
            emit planeCreated();
        }
        break;
        case ZRK:
        {
            //auto sam = ObjectFactory::CreateSAM(element.mass, element.name, element.distance, std::make_unique<Point>(0,0));
            std::unique_ptr<SAM> sam(new SAM(element.mass, element.name, element.distance, std::make_unique<Point>(0,0)));
            sams.push_back(std::move(sam));
            emit samCreated();
        }
        break;
        default:
            break;
    }
}

void Engine::addLine(QVector<QPair<double, double>>* linePoints){
    std::vector<Point*> vec;
    for(auto i = linePoints->begin(); i<linePoints->end(); ++i)
        vec.push_back(new Point((*i).first, (*i).second));
    allLines.push_back(vec);
}

void Engine::addSAM(double x, double y){
    sams[sams.size()-1]->X(x);
    sams[sams.size()-1]->Y(y);
}

void Engine::addPlane(QVector<QPair<double, double>>* points) {
    std::shared_ptr<QVector<Point*>> vec = std::make_shared<QVector<Point*>>(0); 
    for(auto i : *points)
        vec->push_back(new Point(i.first, i.second));
    planes[planes.size()-1]->setTragectory(vec);
}

void Engine::startRenderCycle(){
    if(!timer->isActive())
        timer->start(100);
    if(!sendTimer->isActive())
        sendTimer->start(500);
}

void Engine::pauseRenderCycle(){
    if(timer->isActive())
        timer->stop();
    if(sendTimer->isActive())
        sendTimer->stop();
}

void Engine::moveObjects(){
    for(int i = 0; i<planes.size(); ++i)
        planes[i]->Move();
    for(int i = 0; i<rockets.size(); ++i)
        rockets[i]->Move();
}

void Engine::SAMscane(){
    for(int i = 0; i<sams.size(); ++i)
        for(int j = 0; j<planes.size(); ++j){
            if(sams[i]->length(planes[j].release())<sams[i]->distance()){ //чет смысл unique_ptr кончился
                std::unique_ptr<Rocket> rocket = ObjectFactory::CreateRocket(1000, 1200, 0.5, sams[i].release(), planes[j].release());
                rockets.push_back(std::move(rocket));
                emit rocketCreated(sams[i]->X(), sams[i]->Y());
            }
        }
}

void Engine::packObjects(){
    QVector<QList<double>>* sendPlanes = new QVector<QList<double>>(0);
    for(int i = 0; i<planes.size(); ++i)
        sendPlanes->push_back({planes[i]->X(), planes[i]->Y(), planes[i]->retAngle()});
    QVector<QPair<double, double>>* sendSams = new QVector<QPair<double, double>>(0);
    for(int i = 0; i<sams.size(); ++i)
        sendSams->push_back({sams[i]->X(), sams[i]->Y()});
    QVector<QList<double>>* sendRockets = new QVector<QList<double>>(0);
    for(int i = 0; i<rockets.size(); ++i)
        sendRockets->push_back({rockets[i]->X(), rockets[i]->Y(), rockets[i]->retAngle()});
    emit sendObjects(sendSams, sendPlanes, sendRockets);
}