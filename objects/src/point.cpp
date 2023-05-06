#include "point.h"
#include <math.h>

Point::Point(float x, float y) :
    x_(x), y_(y) {}
Point::Point(const Point& p) : 
    x_(p.X()), y_(p.Y()) {};
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

float Point::length(const Point* p){
    return sqrt((p->X()-x_)*(p->X()-x_)+(p->Y()-y_)*(p->Y()-y_));
};

void Point::dead(){
    isAlive = false;
}

float Point::angle(const Point* p){
    return atan2((p->Y()-y_), (p->X()-x_));
};