#include <typeinfo>
#include <math.h>
// #include <cmath>
#include "rocket.h"
#include "point.h"
#include "plane.h"

#define KM 0.0115

Rocket::~Rocket()
{
    qInfo() << "rocket destructed";
    target_.reset();
}

Rocket::Rocket(float damage, float speed, float range, 
               std::weak_ptr<Plane> target,
               const std::weak_ptr<SAM> parent) :
    damage_(damage), speed_(speed/60), range_(range), angle_(0), parent_(parent), 
    Point(parent.lock()->X(), parent.lock()->Y()),
    target_(target) {}

void Rocket::Move()
{
    if (!is_alive_ || target_.expired() == true) return;

    auto target = target_.lock();

    float dx = target->X() - x_;
    float dy = target->Y() - y_;

    float dist = sqrt(dx*dx + dy*dy);
    float angle_ = atan2(dy, dx);

    if (dist > range_) 
    {
        y_+=speed_*KM*sin(angle_);
        x_+=speed_*KM*cos(angle_);
        
    } else {
        this->Hit();
        
        auto parent = parent_.lock();
        parent->Reload();

        this->OnDead();
    }
}

float Rocket::Angle() const {
    return angle_;
}

void Rocket::Hit()
{
    if (target_.expired() == true) return;

    auto t = target_.lock();
    if (auto target = std::dynamic_pointer_cast<Plane>(t))
        target->ReceiveDamage(damage_);
    if (auto target = std::dynamic_pointer_cast<SAM>(t))
        target->ReceiveDamage(damage_);
    // target_.ReceiveDamage();
}