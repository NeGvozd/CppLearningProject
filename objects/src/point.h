#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(float x, float y);
    virtual ~Point() = default;

    float GetX() const;
    void SetX(float x);

    float GetY() const;
    void SetY(float y);

protected:
    float x_;
    float y_;
};

#endif // POINT_H
