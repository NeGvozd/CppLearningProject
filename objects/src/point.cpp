#include "point.h"
#include <math.h>

Point::Point(float x, float y) :
    x_(x), y_(y) {
        static int globalId_ = 0;
        id_ = globalId_;
        globalId_++;}

// Point::Point(const Point& p) :
//     x_(p.X()), y_(p.Y()) {};

float Point::X() const {
    return x_;
}

void Point::X(float x) {
    x_ = x;
}

float Point::Y() const {
    return y_;
}

void Point::Y(float y) {
    y_ = y;
}

float Point::DistanceTo(const std::weak_ptr<const Point>& object) {
    auto obj = object.lock();
    return sqrt((obj->X()-x_)*(obj->X()-x_)+(obj->Y()-y_)*(obj->Y()-y_));
};

void Point::OnDead() {
    is_alive_ = false;
}

bool Point::IsAlive() const {
    return is_alive_;
}

int Point::Id() {
    return id_;
}

float Point::AngleWith(const std::weak_ptr<const Point> object) {
    auto obj = object.lock();
    return atan2((obj->Y()-y_), (obj->X()-x_));
};
