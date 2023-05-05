#ifndef PLANE_H
#define PLANE_H

#include <QDebug>
#include <vector>
#include <memory>
#include "point.h"

class Rocket;
class SAM;

class Plane : public Point {
public:
    Plane(float health, float speed, const QString& model,
          const std::shared_ptr<QVector<Point>> tragectory);
    ~Plane() = default;

    void Move();
    std::unique_ptr<Rocket> Fire(std::weak_ptr<SAM> target);
    void ReceiveDamage(float amout);

private:
    float health_;
    float speed_;
    QString model_;
    QVector<Point> tragectory_;
};

#endif
