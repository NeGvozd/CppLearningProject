#include "engine.h"
#include <QDebug>
Engine::Engine() {};
void Engine::createNewObject(InfoAboutElement element){
    switch (element.type)
    {
        case AIRPLANS:
        {
            std::unique_ptr<Plane> plane = ObjectFactory::CreatePlane(element.mass,element.speed,element.name, Point(0,0));
            planes.push_back(std::move(plane)); // это не будет работать, если отменить создание объекта до создания любого объекта, что плохо
            emit planeCreated();
        }
        break;
        case ZRK:
        {
            std::unique_ptr<SAM> sam = ObjectFactory::CreateSAM(element.mass,element.name, element.distance, Point(0,0));
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
    sams[sams.size()-1]->setCoord(Point(x, y));
}

void Engine::addPlane(int lineNumber){
    planes[planes.size()-1]->setCoord(*allLines[lineNumber-1][0]);
}