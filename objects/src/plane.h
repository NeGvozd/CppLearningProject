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
          QVector<Point*>* tragectory);
    ~Plane() = default;

    void Move();
    Rocket* Fire(SAM* target);
    void ReceiveDamage(float amout);
    void setTragectory(QVector<Point*>* tragectory);
    float retAngle();

private:
    float health_;
    float speed_;
    float angle_;
    QString model_;
    QVector<Point*>* tragectory_ = nullptr;
    int prevTragPoint;
    int curTragPoint;
};

#endif
