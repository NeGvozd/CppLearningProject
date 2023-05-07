#ifndef SAM_H
#define SAM_H

#include <QDebug>
#include <memory>
#include "point.h"

class Rocket;
class Plane;

class SAM : public Point{
public:
    SAM(float health, const QString& model, float distance,
        Point* location);
    virtual ~SAM() = default;

    Rocket* Fire(Plane* target);
    void ReceiveDamage(float amout);
    float distance();
    void rocketDead();
protected:
    float health_;
    QString model_;
    float distance_;
    int fired = 1;
};

#endif // SAM_H
