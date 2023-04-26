#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <vector>

class Point;
class Rocket;

class Plane {
public:
    Plane(float health, float speed, const std::string& model);
    virtual ~Plane() = default;
    virtual void Move(const std::vector<Point*>& Points) const;
    virtual void Fire(Point* Point) const;

protected:
    float health;
    float speed;
    std::string model;
};

#endif // PLANE_H