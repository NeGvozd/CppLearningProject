#ifndef ROCKET_H
#define ROCKET_H

#include <memory>
#include "point.h"
#include "sam.h"

class Rocket : public Point {
public:
    Rocket(float damage, float speed, float range, Point* target, SAM* parent);
    ~Rocket() = default;

    void Move();
    void Hit();
    float retAngle();

private:
    float damage_;
    float speed_;
    float range_;
    float angle_;
    
    Point* target_;
    SAM* parent_;
};

#endif // ROCKET_H
