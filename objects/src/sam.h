#ifndef SAM_H
#define SAM_H

#include <QDebug>
#include <memory>
#include "point.h"
#include "ObjectFactory.h"

class Rocket;
class Plane;

class SAM : public Point{
public:
    SAM(float health, const QString& model, float distance,
        std::unique_ptr<Point> location);
    virtual ~SAM() = default;

    std::unique_ptr<Rocket> Fire(std::shared_ptr<Plane> target);
    void ReceiveDamage(float amout);
    float distance();
protected:
    float health_;
    QString model_;
    float distance_;
    int fired = 5;
};

#endif // SAM_H
