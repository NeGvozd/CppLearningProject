#ifndef PLANE_H
#define PLANE_H

#include <QDebug>
#include <vector>

#include "point.h"

class Rocket;
class SAM;

class Plane : public Point {
public:
    Plane(float health, float speed, const QString& model,
          std::shared_ptr<QVector<Point>>& tragectory);
    ~Plane() = default;

    void Move();
    void ReceiveDamage(float amout);
    void SetTragectory(std::shared_ptr<QVector<Point>>& tragectory);

    float Angle() const;

private:
    float health_;
    float speed_;
    float angle_ = 0.;
    QString model_;

    std::shared_ptr<QVector<Point>>& tragectory_ ;
    int prev_route_point_;
    int curr_route_point_;
};

#endif
