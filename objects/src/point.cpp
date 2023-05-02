#include "point.h"

Point::Point(float x, float y) :
    x(x), y(y) {}

float Point::X() const {
    return x;
}

float Point::Y() const {
    return y;
}
