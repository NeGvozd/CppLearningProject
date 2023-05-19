#ifndef POINT_H
#define POINT_H

#include <memory>

class Point {
public:
    Point(float x, float y);
    Point();
    virtual ~Point() = default;

    float X() const;
    void X(float x);

    float Y() const;
    void Y(float y);

    float DistanceTo(const std::weak_ptr<const Point>& object);
    float AngleWith(const std::weak_ptr<const Point> object);

    void OnDead();
    bool IsAlive() const;
    int Id();
    
protected:
    float x_;
    float y_;
    bool is_alive_ = true;
    int id_;
};

#endif // POINT_H
