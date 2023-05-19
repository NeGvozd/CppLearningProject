#include "engine.h"
#include <QDebug>
#include <type_traits>

#define KM 0.0115

Engine::Engine() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Engine::moveObjects);
    sendTimer = new QTimer(this);
    // connect(sendTimer, &QTimer::timeout, this, &Engine::packAllObjects);
};

void Engine::createNewObject(InfoAboutElement element) {
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

//void Engine::loadSave(QVector<QPair<InfoAboutElement, std::shared_ptr<QVector<std::shared_ptr<Point>>>>> planes, QVector<InfoAboutElement> sams){

//}
void Engine::addSAM(double x, double y) {
    //создал SAM здесь, кинул emit об этом в QGIS, QGIS дал мне точку на которую кликнули, я её добавил в движке и кинул QGIS обратно какого радиуса круги и где создать
    sams.push_back(std::make_shared<SAM>(lastelement_.mass, lastelement_.name, lastelement_.distance, std::make_unique<Point>(x,y)));
    emit createSAMCircles(x, y, sams[sams.size()-1]->Distance());
    emit sendSAMToList(sams[sams.size()-1]->Id(), lastelement_.name+" "+QString::number(sams[sams.size()-1]->Id()), lastelement_.name, lastelement_.health, lastelement_.distance, 0, x, y);
}

void Engine::addPlane(QVector<QPair<double, double>>* points) {
    std::shared_ptr<QVector<std::shared_ptr<Point>>> vec(new QVector<std::shared_ptr<Point>>);
    for (const auto& pair : *points) {
            vec->append(std::make_shared<Point>(pair.first, pair.second));
        }
    planes.push_back(std::make_shared<Plane>(lastelement_.mass,lastelement_.speed,lastelement_.name, vec));
    emit sendPlaneToList(planes[planes.size()-1]->Id(), lastelement_.name+" "+QString::number(planes[planes.size()-1]->Id()), lastelement_.name, lastelement_.health, lastelement_.speed, points->at(0).first, points->at(0).second);
    emit sendPlaneId(planes[planes.size()-1]->Id());
}

void Engine::getSavedData(QPair<std::shared_ptr<QVector<std::shared_ptr<PacketToEngine_sams>>>, std::shared_ptr<QVector<std::shared_ptr<PacketToEngine_planes>>>> pair){
    sams.clear();
    planes.clear();
    rockets.clear();
    QVector<QVector<QPair<double, double>>> allLines;
    QVector<QList<double>> sendPlanes;
    QVector<QList<double>> sendSams;
    for(int i = 0; i<(*pair.first).size(); ++i){
        PacketToEngine_sams tmp = (*(*pair.first)[i]);
        sams.push_back(std::make_shared<SAM>(tmp.health, tmp.model, tmp.distance/(KM*1000), std::make_unique<Point>(tmp.x, tmp.y)));
        sendSams.push_back({tmp.x, tmp.y, double(sams[i]->Id())});
        emit sendSAMToList(sams[i]->Id(), tmp.model+" "+QString::number(sams[i]->Id()), tmp.model, tmp.health, tmp.distance/(KM*1000), 0, tmp.x, tmp.y);
    }
    for(int i = 0; i<(*pair.second).size(); ++i){
        PacketToEngine_planes tmp = (*(*pair.second)[i]);
        planes.push_back(std::make_shared<Plane>(tmp.health, tmp.speed/KM, tmp.model, tmp.tragectory));
        planes[i]->setIdForLoad(tmp.id);
        QVector<std::shared_ptr<Point>> traj = (*tmp.tragectory);
        QVector<QPair<double, double>> trajstd = QVector<QPair<double, double>>();
        for(int i = 0; i<traj.size(); ++i)
            trajstd.push_back({(*traj[i]).X(), (*traj[i]).Y()});
        allLines.push_back(trajstd);
        sendPlanes.push_back({tmp.x, tmp.y, tmp.angle, double(planes[i]->Id())});
        emit sendPlaneToList(planes[planes.size()-1]->Id(), tmp.model+" "+QString::number(planes[planes.size()-1]->Id()), tmp.model, tmp.health, tmp.speed/KM, tmp.x, tmp.y);
    }
    emit loadSavedLines(allLines, sendPlanes, sendSams);
    for(int i = 0; i<(*pair.first).size(); ++i) emit createSAMCircles((*(*pair.first)[i]).x, (*(*pair.first)[i]).y, sams[i]->Distance());
};

void Engine::startRenderCycle() {
    if(!timer->isActive())
        timer->start(100);
    // if(!sendTimer->isActive())
    //     sendTimer->start(500);
}

void Engine::pauseRenderCycle() {
    if(timer->isActive())
        timer->stop();
    if(sendTimer->isActive())
        sendTimer->stop();
}

void Engine::sendVectorsToDB()
{
    emit sendDATA(planes, sams, rockets);
}

void Engine::moveObjects()
{  
    render_countdown += 100;
    int pos = 0;
    for(auto& rocket : rockets)
    {
        rocket->Move();
        if (!rocket->IsAlive())
        {
            emit deleteRocket(rocket->Id());
            pos--;
        }
        pos++;
    }
    rockets.erase(std::remove_if(rockets.begin(), rockets.end(), 
                  [](const std::shared_ptr<Rocket>& rocket) { return !rocket->IsAlive(); }), rockets.end());

    pos = 0;
    for(auto& plane : planes)
    {
        plane->Move();
        SAMscan(plane);
        if (!plane->IsAlive())
        {
            emit deletePlane(plane->Id());
            pos--;
        }
        pos++;
    }
    planes.erase(std::remove_if(planes.begin(), planes.end(), 
                 [](const std::shared_ptr<Plane>& plane) { return !plane->IsAlive(); }), planes.end());

    if (render_countdown >= 500)
    {
        packAllObjects();
        render_countdown = 0;
    }
}

void Engine::SAMscan(std::weak_ptr<Plane> plane)
{
    auto plane_obj = plane.lock();
    for(int i = 0; i < sams.size(); ++i)
    {
        if(sams[i]->DistanceTo(plane) < sams[i]->Distance() && plane_obj->IsAlive())
        {
            auto rocket = sams[i]->Fire(plane);
            if(rocket)
            {
                rockets.push_back(rocket);
                emit rocketCreated(sams[i]->X(), sams[i]->Y(), rocket->Id());
            }
        }
    }
}

//здесь надо constexpr(можно SFINAE) <- не надо!. прим. Никита(да, можно и без этого)
template<class T>
QVector<QList<double>>* Engine::packObjects(std::vector<std::shared_ptr<T>>& vector)
{
    constexpr bool hasAngle = requires(T t){ t.Angle(); };
    QVector<QList<double>>* send = new QVector<QList<double>>(0);
    // QString type;
    // if constexpr (std::is_same_v<T, Plane>)
    //     type = "Planes";
    // if constexpr (std::is_same_v<T, SAM>)
    //     type = "SAM";
    // if constexpr (std::is_same_v<T, Rocket>)
    //    type = "Rockets";

    if constexpr (hasAngle)
    {        
        for(int i = 0; i<vector.size(); ++i)
        { 
            if(vector.size() > 0 && vector[i]->IsAlive()) 
                send->push_back({vector[i]->X(), vector[i]->Y(), vector[i]->Angle(), double(vector[i]->Id())}); 
        }
    } else {
        for(int i = 0; i<vector.size(); ++i)
            if(vector[i]->IsAlive()) 
                send->push_back({vector[i]->X(), vector[i]->Y(), vector[i]->Id()});
    }
    return send;
}

void Engine::packAllObjects() {
    emit sendObjects(packObjects<Plane>(planes), packObjects<Rocket>(rockets));
}

void Engine::getPlaneCoords(int id){
    for(int i = 0; i<planes.size(); ++i)
        if(planes[i]->Id() == id)
            emit sendElementCoords(planes[i]->X(), planes[i]->Y());
};

void Engine::getRocketCoords(int id){
    for(int i = 0; i<rockets.size(); ++i)
        if(rockets[i]->Id() == id)
            emit sendElementCoords(rockets[i]->X(), rockets[i]->Y());
};
