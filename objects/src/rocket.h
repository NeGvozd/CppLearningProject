#ifndef ROCKET_H
#define ROCKET_H

#include <memory>
#include "point.h"

class Rocket : public Point {
public:
    Rocket(float damage, float speed, float range, Point* location, std::weak_ptr<Point> target);
    ~Rocket() = default;

    void Move();
    void Hit();

private:
    float damage_;
    float speed_;
    float range_;
    
    std::weak_ptr<Point> target_;
};

#endif // ROCKET_H
