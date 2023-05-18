#include "sam.h"
#include "rocket.h"
#include "plane.h"

#define KM 0.0115

SAM::SAM(float health, const QString& model, float distance, 
         std::unique_ptr<Point> location) :
    health_(health), model_(model), distance_(distance*KM), Point(location->X(), location->Y()) {}

void SAM::ReceiveDamage(float amount) {
    health_ -= amount;
    if (health_ <= 0) delete this;
}

float SAM::Distance() const {
    return distance_;
}

void SAM::Reload() {
    battery_++;
}

float SAM::HEALTH() const
{
    return health_;
}

QString SAM::MODEL() const
{
    return model_;
}

float SAM::DISTANCE() const
{
    return distance_;
}

int SAM::BATTERY() const
{
    return battery_;
}

std::shared_ptr<Rocket> SAM::Fire(std::weak_ptr<Plane> target)
{
    if (battery_ > 0) {
        battery_--;
        const std::weak_ptr<SAM> rocket_parent = shared_from_this();
        return std::make_shared<Rocket>(20000, 1200, 0.5, target, rocket_parent);//пока не понятно как создавать ракеты из бд
    }
    return nullptr;
}
