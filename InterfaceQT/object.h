#ifndef OBJECT_H
#define OBJECT_H
#include <string>

class Point
{
public:
    double x;
    double y;
    Point();
    Point(double x_,double y_): x{x_},y{y_} {};
    ~Point();

    Point operator+(const Point);
    Point operator-(const Point);
};

class SpriteImage
{
public:
    double width;
    double height;
    std::string spritePath;
    SpriteImage(double width_,double height_): width{width_},height{height_} {};
    ~SpriteImage();

};

class Object
{
protected:
    Point p;
    SpriteImage sprite;
    Object(Point p_,SpriteImage sprite_):p{p_},sprite{sprite_}{};
    ~Object();
};

class MovableObject: Object
{
protected:
    double speed;
    MovableObject(Point p_,SpriteImage sprite_,double speed_):Object{p_,sprite_},speed{speed_}{};
    ~MovableObject();
};

class DefenceObject: MovableObject
{
protected:
    DefenceObject(Point p_,SpriteImage sprite_,double speed_):MovableObject{p_,sprite_,speed_}{};
    ~DefenceObject();
};

class EnemyObject: MovableObject
{
protected:
    EnemyObject(Point p_,SpriteImage sprite_,double speed_):MovableObject{p_,sprite_,speed_}{};
    ~EnemyObject();
};

class DamageObject: MovableObject
{
protected:
    double damage;
    DamageObject(Point p_,SpriteImage sprite_,double speed_,double damage_):MovableObject{p_,sprite_,speed_},damage{damage_}{};
    ~DamageObject();
};

class Bullet:DamageObject
{
public:
    Bullet(Point p_,SpriteImage sprite_,double speed_,double damage_):DamageObject{p_,sprite_,speed_,damage_}{};
    ~Bullet();
};

#endif // OBJECT_H
