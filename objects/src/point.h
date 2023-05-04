#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(float x, float y);
    virtual ~Point() = default;
    float X() const;
    float Y() const;

private:
    float x;
    float y;
};

#endif // POINT_H
