#ifndef SAM_H
#define SAM_H

#include <QDebug>
// #include <vector>
<<<<<<< HEAD
=======
#include "point.h"
>>>>>>> Interface

class Rocket;

class SAM {
public:
    SAM(float health, const QString& model, float distance, Point coord);
    virtual ~SAM() = default;
    virtual void Fire() const;
    void RLSWithPoint(Point p);

protected:
    float health;
    QString model;
    float distance;
    Point coord;
};

#endif // SAM_H
