#include "plane.h"
#include "rocket.h"
#include "point.h"
#include "sam.h"

Plane::Plane(float health, float speed, const QString& model, 
             const std::shared_ptr<QVector<Point>> tragectory) :
    health_(health), speed_(speed), model_(model),
    Point(tragectory->first().GetX(), tragectory->first().GetY()) {}

void Plane::Move() 
{

}

std::unique_ptr<Rocket> Plane::Fire(std::weak_ptr<SAM>)
{
//    return std::make_unique<Rocket>();
}

void Plane::ReceiveDamage(float amount)
{
    health_ -= amount;
    if (health_ <= 0) delete this;
}
