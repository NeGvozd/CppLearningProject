#include "point.h"

Point::Point(float x, float y) :
    x_(x), y_(y) {}

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
