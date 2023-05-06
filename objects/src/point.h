#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(float x, float y);
    Point(const Point& p);
    virtual ~Point() = default;

    float X() const;
    void X(float x);

    float Y() const;
    void Y(float y);

    float length(const Point* p);
    float angle(const Point* p);
protected:
    float x_;
    float y_;
};

#endif // POINT_H
