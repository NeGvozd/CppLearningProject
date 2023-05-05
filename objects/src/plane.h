#ifndef PLANE_H
#define PLANE_H

#include <QDebug>
#include <vector>
#include "point.h"

class Rocket;

class Plane {
public:
    Plane(float health, float speed, const QString& model, Point point);
    virtual ~Plane() = default;
    virtual void Move(const std::vector<Point*>& Points) const;
    virtual void Fire(Point* Point) const;
    void setCoord(Point p);
    Point getCoord();

protected:
    float health;
    float speed;
    QString model;
    Point coord;
};

#endif
