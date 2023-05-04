#include "plane.h"
#include "rocket.h"
#include "point.h"

Plane::Plane(float health, float speed, const QString& model, Point point) :
    health(health), speed(speed), model(model), coord(point) {}

void Plane::Move(const std::vector<Point*>& points) const 
{
//    std::cout << "Plane " << model << " moving along trajectory: ";
//    for (auto oint : points) {
//        std::cout << "(" << point->getX() << "," << point->getY() << ") ";
//    }
//    std::cout << std::endl;
}

void Plane::setCoord(Point p){
    coord = p;
}

Point Plane::getCoord(){
    return coord;
}

void Plane::Fire(Point* point) const
{
    /* Supposed example of usage
    Rocket rocket(50, 500, 1000, point);
    rocket.Launch(); 
    */
}
