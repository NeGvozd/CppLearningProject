#ifndef SAM_H
#define SAM_H

#include <QDebug>
// #include <vector>
#include "point.h"

class Rocket;

class SAM {
public:
    SAM(float health, const QString& model, float distance, Point coord);
    virtual ~SAM() = default;
    virtual void Fire() const;
    void RLSWithPoint(Point p);
    void setCoord(Point p);
    Point getCoord();
protected:
    float health;
    QString model;
    float distance;
    Point coord;
};

#endif // SAM_H
