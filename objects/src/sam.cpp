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

float SAM::distance(){
    return distance_;
}

std::unique_ptr<Rocket> SAM::Fire(std::shared_ptr<Plane> target){
    /*if(fired>0){
        fired--;
        return ObjectFactory::CreateRocket(1000, 1200, 0.5, this, target);//пока не понятно как создавать ракеты из бд
    }*/
}
