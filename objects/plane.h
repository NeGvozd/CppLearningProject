#ifndef PLANE_H
#define PLANE_H

#include <QDebug>
#include <vector>

class Point;
class Rocket;

class Plane {
public:
    Plane(float health, float speed, const QString& model);
    virtual ~Plane() = default;
    virtual void Move(const std::vector<Point*>& Points) const;
    virtual void Fire(Point* Point) const;

protected:
    float health;
    float speed;
    QString model;
};

#endif
