#include "object.h"


Point Point::operator+(const Point p)
{
    int x0 = x + p.x;
    int y0 = y + p.y;

    return Point(x0,y0);
}

Point Point::operator-(const Point p)
{
    int x0 = x - p.x;
    int y0 = y - p.y;

    return Point(x0,y0);
}
