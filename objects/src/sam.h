#ifndef SAM_H
#define SAM_H

#include <QDebug>
#include "point.h"

class Rocket;
class Plane;

class SAM : public Point {
public:
    SAM(float health, const QString& model, float distance,
        std::unique_ptr<Point> location);
    ~SAM() = default;

    std::unique_ptr<Rocket> Fire(std::shared_ptr<const Plane> plane);
    void ReceiveDamage(float amout);
    float Distance() const;
    void Reload(); // when rocket is destroyed, can create a new one
protected:
    float health_;
    QString model_;
    float distance_;
    int battery_ = 1;
};

#endif // SAM_H
