#include "sam.h"
#include "rocket.h"
#include "plane.h"

SAM::SAM(float health, const QString& model, float distance, std::unique_ptr<Point> location) :
    health_(health), model_(model), distance_(distance), Point(location->X(), location->Y()) {}

void SAM::ReceiveDamage(float amount)
{
    health_ -= amount;
    if (health_ <= 0) delete this;
}


std::unique_ptr<Rocket> SAM::Fire(std::weak_ptr<Plane>)
{
//    return std::make_unique<Rocket>();
}
