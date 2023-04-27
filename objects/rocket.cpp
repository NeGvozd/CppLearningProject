#include "rocket.h"
#include "point.h"
Rocket::Rocket(float damage, float speed, float range, Point* target) :
    damage(damage), speed(speed), range(range), target(target) {}

void Rocket::Launch() const {
//    std::cout << "Rocket launched at target at (" << target->X() << "," << target->Y() << ") with damage: " << damage << ", speed: " << speed << ", range: " << range << std::endl;
}
