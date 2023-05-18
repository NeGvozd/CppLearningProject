#include "plane.h"
#include "rocket.h"
#include "point.h"
#include "sam.h"

#include <math.h>

#include <QDebug>

#define KM 0.0115

Plane::Plane(float health, float speed, const QString& model, 
             std::shared_ptr<QVector<std::shared_ptr<Point>>> tragectory) :
    health_(health), 
    speed_(speed/60), 
    model_(model), 
    tragectory_(tragectory), 
    curr_route_point_(-1), //скорость за 15 мин
    Point(tragectory->at(0)->X(), tragectory->at(0)->Y())
    {   
        if (tragectory_->count() >= 0) curr_route_point_ = 0;
    }

Plane::~Plane()
{
    qInfo() << "plane destructed";
    tragectory_.reset();
}

void Plane::Move()
{
    if (!is_alive_) return;

    if (curr_route_point_ == -1)// && tragectory_)
    {
        // if the next route point is not reached
        if (!(x_== tragectory_->at(tragectory_->size()-1)->X() && y_== tragectory_->at(tragectory_->size()-1)->Y()))
        {
            curr_route_point_ = prev_route_point_;
        }
    }
    if (curr_route_point_ != -1)
    {
        // if at the last point of the route
        if (curr_route_point_ == tragectory_->size()-1)
        {
            prev_route_point_ = curr_route_point_;
            curr_route_point_ = -1;
        } else {
            auto destination = *tragectory_->at(curr_route_point_+1);
            float dist = this->DistanceTo(std::make_shared<Point>(destination));
            angle_ = this->AngleWith(std::make_shared<Point>(destination));

            // if the end of the tragectory is closer than one step
            if (dist < speed_*KM)
            {
                curr_route_point_ += 1;
                x_ = tragectory_->at(curr_route_point_)->X();
                y_ = tragectory_->at(curr_route_point_)->Y();
            } else {
                y_ += speed_ * KM * sin(angle_);
                x_ += speed_ * KM * cos(angle_);
            }
        }
    }
}

void Plane::SetTragectory(std::shared_ptr<QVector<std::shared_ptr<Point>>> tragectory)
{
    if (curr_route_point_ != -1) 
    {   
        tragectory_->append(*tragectory);
    } else { 
        tragectory_ = tragectory;
        X(tragectory->at(0)->X());
        Y(tragectory->at(0)->Y());
        curr_route_point_ = 0;
    }
}

void Plane::ReceiveDamage(float amount) {
    health_ -= amount;
    if (health_ <= 0) OnDead();
    // qInfo() << IsAlive();
}

float Plane::Angle() const {
    return angle_;
}
float Plane::HEALTH() const
{
    return health_;
}

QString Plane::MODEL() const
{
    return model_;
}

float Plane::SPEED() const
{
    return speed_;
}

std::shared_ptr<QVector<std::shared_ptr<Point> > > Plane::TRAGECTORY() const
{
    return tragectory_;
}
