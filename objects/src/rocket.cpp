#include <typeinfo>
#include <cmath>

#include "rocket.h"
#include "point.h"
#include "plane.h"

#include <math.h>

#define KM 0.0115

Rocket::Rocket(float damage, float speed, float range, Point* target, SAM* parent) :
    damage_(damage), speed_(speed/60), range_(range), angle_(0), parent_(parent), Point(parent->X(), parent->Y()),
    target_(target) {}

void Rocket::Move()
{
    if (!target_ || !isAlive) return;

    float dx = target_->X() - x_;
    float dy = target_->Y() - y_;

    float dist = sqrt(dx*dx + dy*dy);
    float angle_ = atan2(dy, dx);
    if (dist > range_) 
    {
        y_+=speed_*KM*sin(angle_);
        x_+=speed_*KM*cos(angle_);
        
    }
    else{
//        target_->dead();
        isAlive = !isAlive;
        parent_->rocketDead();
    }
}

float Rocket::retAngle(){
    return angle_;
}

void Rocket::Hit()
{
    if (auto target = dynamic_cast<Plane*>(target_))
        target->ReceiveDamage(damage_);
    if (auto target = dynamic_cast<SAM*>(target_))
        target->ReceiveDamage(damage_);

    // target_.ReceiveDamage();
}
