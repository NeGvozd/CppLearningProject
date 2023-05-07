#include <typeinfo>
#include <math.h>
// #include <cmath>
#include "rocket.h"
#include "point.h"
#include "plane.h"


#define KM 0.0115

Rocket::Rocket(float damage, float speed, float range, 
               std::shared_ptr<const Plane> target,
               const std::weak_ptr<SAM> parent) :
    damage_(damage), speed_(speed/60), range_(range), angle_(0), parent_(parent), 
    Point(parent.lock()->X(), parent.lock()->Y()),
    target_(target) {}

void Rocket::Move()
{
    if (!target_ || !is_alive_) return;

    float dx = target_->X() - x_;
    float dy = target_->Y() - y_;

    float dist = sqrt(dx*dx + dy*dy);
    float angle_ = atan2(dy, dx);

    if (dist > range_) 
    {
        y_+=speed_*KM*sin(angle_);
        x_+=speed_*KM*cos(angle_);
        
    } else {
        //target_->dead();
        is_alive_ = !is_alive_;

        auto parent = parent_.lock();
        parent->Reload();
    }
}

float Rocket::Angle() const {
    return angle_;
}

void Rocket::Hit()
{
    if (auto target = std::dynamic_pointer_cast<Plane>(target_))
        target->ReceiveDamage(damage_);
    if (auto target = std::dynamic_pointer_cast<SAM>(target_))
        target->ReceiveDamage(damage_);
    // target_.ReceiveDamage();
}
