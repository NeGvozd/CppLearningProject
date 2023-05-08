#include "engine.h"
#include <QDebug>

Engine::Engine() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Engine::moveObjects);
    sendTimer = new QTimer(this);
    connect(sendTimer, &QTimer::timeout, this, &Engine::packAllObjects);
};

void Engine::createNewObject(InfoAboutElement element){
    lastelement_ = element; //можно threadом сделать без сохранения, но пока сделаем с сохранением параметра.
    switch (element.type)
    {
        case AIRPLANS:
        {
            emit planeCreated();
        }
        break;
        case ZRK:
        {
            //auto sam = ObjectFactory::CreateSAM(element.mass, element.name, element.distance, std::make_unique<Point>(0,0));
            emit samCreated(); 
        }
        break;
        default:
            break;
    }
}

void Engine::addLine(QVector<QPair<double, double>>* linePoints) 
{
    for(auto i = linePoints->begin(); i < linePoints->end(); ++i)
        allLines.push_back(std::make_shared<Point>((*i).first, (*i).second));
}

void Engine::addSAM(double x, double y){ 
    //создал SAM здесь, кинул emit об этом в QGIS, QGIS дал мне точку на которую кликнули, я её добавил в движке и кинул QGIS обратно какого радиуса круги и где создать
    sams.push_back(std::make_shared<SAM>(lastelement_.mass, lastelement_.name, lastelement_.distance, std::make_unique<Point>(x,y)));
    emit createSAMCircles(x, y, sams[sams.size()-1]->Distance());
}

void Engine::addPlane(QVector<QPair<double, double>>* points) {
    std::shared_ptr<QVector<std::shared_ptr<Point>>> vec(new QVector<std::shared_ptr<Point>>);
    for (const auto& pair : *points) {
            vec->append(std::make_shared<Point>(pair.first, pair.second));
        }
    planes.push_back(std::make_shared<Plane>(lastelement_.mass,lastelement_.speed,lastelement_.name, vec));
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
    int pos = 0;
    for(std::vector<std::shared_ptr<Rocket>>::iterator it=rockets.begin(); it<rockets.end();)
    if((*it)->isAlive()){
        (*it)->Move();
        ++it;
        pos++;
    }
    else {
            qInfo() << (*it)->isAlive();
            pauseRenderCycle();
            rockets.erase(it);
            rockets[pos]->~Rocket();
            emit deleteRocket(pos);
            pos--;
        }
    SAMscane();
}

void Engine::SAMscane()
{
    for(int i = 0; i < sams.size(); ++i)
    {
        for(int j = 0; j < planes.size(); ++j)
        {
            if(sams[i]->DistanceTo(planes[j])<sams[i]->Distance()){
                auto rocket = sams[i]->Fire(planes[j]);
                if(rocket) {
                    rockets.push_back(rocket);
                    emit rocketCreated(sams[i]->X(), sams[i]->Y());
                }
            }
        }
    }
}
//здесь надо concept(можно SFINAE)
template<class T>
QVector<QList<double>>* Engine::packObjects(std::vector<std::shared_ptr<T>> vector){
    constexpr bool hasAngle = requires(T t){ t.Angle(); };
    QVector<QList<double>>* send = new QVector<QList<double>>(0);
    if constexpr (hasAngle){
        for(int i = 0; i<vector.size(); ++i){
        qInfo() << vector[i]->isAlive() << vector[i].use_count() << vector.size();
        if(vector[i]->isAlive()) 
            send->push_back({vector[i]->X(), vector[i]->Y(), vector[i]->Angle()}); 
        }
    }
    else{
        for(int i = 0; i<vector.size(); ++i)
        if(vector[i]->isAlive()) 
            send->push_back({vector[i]->X(), vector[i]->Y()});
    }
    return send;
}

void Engine::packAllObjects(){
    emit sendObjects(packObjects<SAM>(sams), packObjects<Plane>(planes), packObjects<Rocket>(rockets));
}