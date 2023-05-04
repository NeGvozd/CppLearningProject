#include "engine.h"

Engine::Engine() {};
void Engine::createNewObject(InfoAboutElement element){
    switch (element.type)
    {
        case AIRPLANS:
        {
            auto plane = ObjectFactory::CreatePlane(element.mass,element.speed,element.name);
            emit planeCreated();
        }
        break;
        case ZRK:
        {
            auto sam = ObjectFactory::CreateSAM(element.mass,element.name, element.distance, Point(0,0));
            emit samCreated();
        }
        break;
        default:
            break;
    }
}