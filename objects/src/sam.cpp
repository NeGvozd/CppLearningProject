#include "sam.h"
#include "rocket.h"
#include "plane.h"

#define KM 0.0115

SAM::SAM(float health, const QString& model, float distance, 
         std::unique_ptr<Point> location) :
    health_(health), model_(model), distance_(distance*KM), Point(location->X(), location->Y()) {
        launchTimer = new QTimer();
    }

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

std::shared_ptr<Rocket> SAM::Fire(std::weak_ptr<Plane> target)
{
    if (battery_ > 0 && !launchTimer->isActive()) {
        battery_--;
        const std::weak_ptr<SAM> rocket_parent = shared_from_this();
        return std::make_shared<Rocket>(1000, 1200, 0.5, target, rocket_parent);//пока не понятно как создавать ракеты из бд
        launchTimer->start(2000);
    }
    return nullptr;
}
