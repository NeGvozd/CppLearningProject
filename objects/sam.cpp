#include "sam.h"
#include "rocket.h"
#include "cmath"

SAM::SAM(float health, const QString& model, float distance, Point coord) :
    health(health), model(model), distance(distance), coord(coord) {}

void SAM::Fire() const {
    /* Supposed example of usage
    Rocket rocket(100, 1000, 2000, nullptr);
    rocket.Launch();
    */
}

void SAM::RLSWithPoint(Point p)
{
    //calculating dist between point and zrk:
    float l =  pow(pow((coord.X()-p.X()),2) + pow((coord.Y()-p.Y()), 2), 0.5);
    if( l <= distance ){
        qInfo() << "Object detected! WARNING!!!";
    }
}
