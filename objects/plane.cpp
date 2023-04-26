#include "Plane.h"
#include "Rocket.h"
#include "Point.h"

Plane::Plane(float health, float speed, const QString& model) :
    health(health), speed(speed), model(model) {}

void Plane::Move(const std::vector<Point*>& points) const 
{
//    std::cout << "Plane " << model << " moving along trajectory: ";
//    for (auto oint : points) {
//        std::cout << "(" << point->getX() << "," << point->getY() << ") ";
//    }
//    std::cout << std::endl;
}

void Plane::Fire(Point* point) const
{
    /* Supposed example of usage
    Rocket rocket(50, 500, 1000, point);
    rocket.Launch(); 
    */
}
