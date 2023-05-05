#include "point.h"

Point::Point(float x, float y) :
    x_(x), y_(y) {}

float Point::GetX() const {
    return x_;
}

void Point::SetX(float x) {
    x_ = x;
}

float Point::GetY() const {
    return y_;
}

void Point::SetY(float y) {
    y_ = y;
}
