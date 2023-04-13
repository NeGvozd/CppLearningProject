#ifndef OBJECT_H
#define OBJECT_H
#include <string>

//class Point
//{
//public:
//    double x;
//    double y;
//    Point();
//    Point(double x_,double y_): x{x_},y{y_} {};
//    ~Point();

//    Point operator+(const Point);
//    Point operator-(const Point);
//};

//class SpriteImage
//{
//public:
//    SpriteImage(float x, float y, std::string image_source)
//    {
//        this->img_path_ = image_source;
//    }

//    float& Width() { return this->width; }
//    float& Height() { return this->height; }

//    ~SpriteImage();
//private:
//    float width;
//    float height;
//    std::string img_path_;
//};

class Object
{
public:
    Object(float x, float y, float speed)
    {
        this->x = x;
        this->y = y;
        this->speed = speed;
    }
    ~Object();

    float& X() { return this->x; }
    float& Y() { return this->y; }
private:
    float x;
    float y;
    float speed;
};


class DamageableObject : Object
{
public:
    DamageableObject(float x, float y, float speed, float health)
    : Object(x, y, speed)
    {
        this->health_ = health;
    }
    ~DamageableObject();
    
    float Health() const { return this->health_; }
    void TakeDamage(float amount);
    virtual void Fire();
private:
    float health_;
};


class DamagingObject : Object
{
public:
    DamagingObject(float x, float y, float speed, float damage)
    : Object(x, y, speed)
    {
        this->damage_ = damage;
    }
    ~DamagingObject();

    float Damage() const { return this->damage_; }
    void Damage(float damage) { this->damage_ = std::move(damage); }

    virtual void Chase(DamageableObject* target);
private:
    double damage_;
};


class Plane : DamageableObject
{
public:
    Plane(float x, float y, float speed, float health)
    : DamageableObject(x, y, speed, health) {}
    ~Plane();

    void Move();
    void Fire() override;
};


class Missile : DamagingObject
{
public:
    Missile(float x, float y, float speed, float damage)
    : DamagingObject(x, y, speed, damage) {}
    ~Missile();

    void Chase(DamageableObject *target) override;
};

//class MovableObject: Object
//{
//protected:
//    double speed;
//    MovableObject(Point p_,SpriteImage sprite_,double speed_):Object{p_,sprite_},speed{speed_}{};
//    ~MovableObject();
//};

#endif // OBJECT_H
