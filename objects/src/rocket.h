#ifndef ROCKET_H
#define ROCKET_H

class Point;

class Rocket {
public:
    Rocket(float damage, float speed, float range, Point* target);
    virtual ~Rocket() = default;
    virtual void Launch() const;

protected:
    float damage;
    float speed;
    float range;
    Point* target;
};

#endif // ROCKET_H