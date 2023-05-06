#ifndef ROCKET_H
#define ROCKET_H

#include <memory>
#include "point.h"

class Rocket : public Point {
public:
    Rocket(float damage, float speed, float range, Point* location, Point* target);
    ~Rocket() = default;

    void Move();
    void Hit();
    float retAngle();

private:
    float damage_;
    float speed_;
    float range_;
    float angle_;
    
    std::weak_ptr<Point> target_;
};

#endif // ROCKET_H
