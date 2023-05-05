#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <memory>
#include "point.h"
#include "plane.h"
#include "sam.h"
#include <QDebug>

class Point;
class Plane;
class SAM;

class ObjectFactory {
public:
    static std::unique_ptr<Point> CreateTarget(float x, float y);
    static std::unique_ptr<Plane> CreatePlane(float health, float speed, const QString& model, Point coord);
    static std::unique_ptr<SAM> CreateSAM(float health, const QString& model, float distance, Point coord);
};

#endif // OBJECT_FACTORY_H
