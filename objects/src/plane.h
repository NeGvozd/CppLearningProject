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
          std::shared_ptr<QVector<std::shared_ptr<Point>>> tragectory);
    ~Plane();

    void Move();
    void ReceiveDamage(float amout);
    void SetTragectory(std::shared_ptr<QVector<std::shared_ptr<Point>>> tragectory);
    float Angle() const;
    float HEALTH() const;
    QString MODEL() const;
    float SPEED() const;

private:
    float health_;
    float speed_;
    float angle_ = 0.;
    QString model_;

    std::shared_ptr<QVector<std::shared_ptr<Point>>> tragectory_ ;
    int prev_route_point_;
    int curr_route_point_;
};

#endif
