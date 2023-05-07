#ifndef ROCKET_H
#define ROCKET_H

#include "point.h"
#include "sam.h"

class Rocket : public Point {
public:
    Rocket(float damage, float speed, float range, 
           std::shared_ptr<const Plane> target,
           const std::weak_ptr<SAM> parent);
    ~Rocket() = default;

    void Move();
    void Hit();
    float Angle() const;

private:
    float damage_;
    float speed_;
    float range_;
    float angle_;
    
    std::shared_ptr<const Plane> target_;
    const std::weak_ptr<SAM> parent_;
};

#endif // ROCKET_H
