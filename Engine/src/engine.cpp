#include "engine.h"
#include <QDebug>
#include <type_traits>

Engine::Engine() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Engine::moveObjects);
    sendTimer = new QTimer(this);
    connect(sendTimer, &QTimer::timeout, this, &Engine::packAllObjects);
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

void Engine::addLine(QVector<QPair<double, double>>* linePoints) 
{
    for(auto i = linePoints->begin(); i < linePoints->end(); ++i)
        allLines.push_back(std::make_shared<Point>((*i).first, (*i).second));
}

void Engine::addSAM(double x, double y) { 
    //создал SAM здесь, кинул emit об этом в QGIS, QGIS дал мне точку на которую кликнули, я её добавил в движке и кинул QGIS обратно какого радиуса круги и где создать
    sams.push_back(std::make_shared<SAM>(lastelement_.mass, lastelement_.name, lastelement_.distance, std::make_unique<Point>(x,y)));
    emit createSAMCircles(x, y, sams[sams.size()-1]->Distance());
    emit sendSAMToList(sams.size()-1, lastelement_.name+QString::number(sams.size()-1), lastelement_.name, lastelement_.health, lastelement_.distance, 0, x, y);
}

void Engine::addPlane(QVector<QPair<double, double>>* points) {
    std::shared_ptr<QVector<std::shared_ptr<Point>>> vec(new QVector<std::shared_ptr<Point>>);
    for (const auto& pair : *points) {
            vec->append(std::make_shared<Point>(pair.first, pair.second));
        }
    planes.push_back(std::make_shared<Plane>(lastelement_.mass,lastelement_.speed,lastelement_.name, vec));
    emit sendPlaneToList(planes.size()-1, lastelement_.name+QString::number(planes.size()-1), lastelement_.name, lastelement_.health, lastelement_.speed, points->at(0).first, points->at(0).second);
}

void Engine::startRenderCycle() {
    if(!timer->isActive())
        timer->start(100);
    if(!sendTimer->isActive())
        sendTimer->start(500);
}

void Engine::pauseRenderCycle() {
    if(timer->isActive())
        timer->stop();
    if(sendTimer->isActive())
        sendTimer->stop();
}

void Engine::moveObjects()
{
    for(int i = 0; i<planes.size(); ++i)
        planes[i]->Move();

    int pos = 0;

    for(std::vector<std::shared_ptr<Rocket>>::iterator it=rockets.begin(); it<rockets.end();)
    {
        if((*it)->IsAlive())
        {
            (*it)->Move();
            ++it;
            pos++;
        } else {
                pauseRenderCycle();

                // rockets[pos]->~Rocket();
                rockets.erase(it);
                //qInfo() << "Erased" << rockets.size();
                if (pos > 0)
                    pos--;

                emit deleteRocket(pos);
        }
    }
    SAMscane();
}

void Engine::SAMscane()
{
    for(int i = 0; i < sams.size(); ++i)
    {
        for(int j = 0; j < planes.size(); ++j)
        {
            if(sams[i]->DistanceTo(planes[j])<sams[i]->Distance())
            {
                auto rocket = sams[i]->Fire(planes[j]);
                if(rocket)
                {
                    rockets.push_back(rocket);
                    emit rocketCreated(sams[i]->X(), sams[i]->Y());
                    emit sendRocketToList(rockets.size()-1, "0", "0", rocket->Damage(), rocket->Speed(), rocket->Range(), sams[i]->X(), sams[i]->Y());
                }
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

    //QString type;
    // if constexpr (std::is_same_v<T, Plane>)
    //     type = "Planes";
    // if constexpr (std::is_same_v<T, SAM>)
    //     type = "SAM";
    //if constexpr (std::is_same_v<T, Rocket>)
    //    type = "Rockets";

    if constexpr (hasAngle)
    {        
        for(int i = 0; i<vector.size(); ++i)
        {            
            //qInfo() << type << vector[i]->IsAlive() << vector[i].use_count() << vector.size();
            if (!vector[i]->IsAlive()) 
            {
                vector.erase(vector.begin()+i);
                emit deleteRocket(i);
            }

            if(vector.size() > 0 && vector[i]->IsAlive()) 
                send->push_back({vector[i]->X(), vector[i]->Y(), vector[i]->Angle()}); 
        }
    } else {
        for(int i = 0; i<vector.size(); ++i)
            if(vector[i]->IsAlive()) 
                send->push_back({vector[i]->X(), vector[i]->Y()});
    }
    
    //if (type == "Rockets")
    //    qInfo() << "all send!" << type << send->size();
    return send;
}

void Engine::packAllObjects() {
    emit sendObjects(packObjects<SAM>(sams), packObjects<Plane>(planes), packObjects<Rocket>(rockets));
}