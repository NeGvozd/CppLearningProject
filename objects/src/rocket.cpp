#include <typeinfo>
#include <cmath>

#include "rocket.h"
#include "point.h"
#include "plane.h"
#include "sam.h"


Rocket::Rocket(float damage, float speed, float range, Point* location, std::weak_ptr<Point> target) :
    damage_(damage), speed_(speed), range_(range),  Point(location->GetX(), location->GetY()),
    target_(target) {}

void Rocket::Move()
{
    auto target = target_.lock();
    if (!target) return;

    float dx = target->GetX() - x_;
    float dy = target->GetY() - y_;

    float dist = std::sqrt(dx*dx + dy*dy);
    if (dist > 0) 
    {
        
    }
}

void Rocket::Hit()
{
    if (auto target = std::dynamic_pointer_cast<Plane>(target_.lock()))
        target->ReceiveDamage(damage_);
    if (auto target = std::dynamic_pointer_cast<SAM>(target_.lock()))
        target->ReceiveDamage(damage_);

    // target_.ReceiveDamage();
}
