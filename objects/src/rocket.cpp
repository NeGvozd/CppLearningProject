#include <typeinfo>
#include <cmath>

#include "rocket.h"
#include "point.h"
#include "plane.h"
#include "sam.h"

#include <math.h>

#define KM 0.0115

Rocket::Rocket(float damage, float speed, float range, Point* location, Point* target) :
    damage_(damage), speed_(speed), range_(range), angle_(0),  Point(location->X(), location->Y()),
    target_(target) {}

void Rocket::Move()
{
    auto target = target_.lock();
    if (!target) return;

    float dx = target->X() - x_;
    float dy = target->Y() - y_;

    float dist = sqrt(dx*dx + dy*dy);
    float angle_ = atan2(dy, dx);
    if (dist > range_) 
    {
        y_+=speed_*KM*sin(angle_);
        x_+=speed_*KM*cos(angle_);
        
    }
    else{
        target->dead();
    }
}

float Rocket::retAngle(){
    return angle_;
}

void Rocket::Hit()
{
    if (auto target = std::dynamic_pointer_cast<Plane>(target_.lock()))
        target->ReceiveDamage(damage_);
    if (auto target = std::dynamic_pointer_cast<SAM>(target_.lock()))
        target->ReceiveDamage(damage_);

    // target_.ReceiveDamage();
}
