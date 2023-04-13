#include "object.h"

void DamageableObject::TakeDamage(float amount)
{
    if (this->health_ > 0) this->health_ -= amount;
}


void Plane::Move()
{
    /// Moving ///
}


void Plane::Fire()
{
    /// Spawn Missile ///
}


void Missile::Chase(DamageableObject *target)
{
    /// Somehow chasing targeted object ///
}
//Point Point::operator+(const Point p)
//{
//    int x0 = x + p.x;
//    int y0 = y + p.y;

//    return Point(x0,y0);
//}

//Point Point::operator-(const Point p)
//{
//    int x0 = x - p.x;
//    int y0 = y - p.y;

//    return Point(x0,y0);
//}
