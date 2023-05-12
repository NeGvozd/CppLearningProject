#ifndef SAM_H
#define SAM_H

#include <QDebug>
#include <QTimer>
#include "point.h"

class Rocket;
class Plane;

class SAM : public Point, public std::enable_shared_from_this<SAM> {
public:
    SAM(float health, const QString& model, float distance,
        std::unique_ptr<Point> location);
    ~SAM() = default;

    std::shared_ptr<Rocket> Fire(std::weak_ptr<Plane> target);
    void ReceiveDamage(float amout);
    float Distance() const;
    void Reload(); // when rocket is destroyed, can create a new one
protected:
    float health_;
    QString model_;
    float distance_;
    int battery_ = 2;
    QTimer* launchTimer;
};

#endif // SAM_H
