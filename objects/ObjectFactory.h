#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <memory>
#include "Point.h"
#include "Plane.h"
#include "SAM.h"
#include <QDebug>

class Point;
class Plane;
class SAM;

class ObjectFactory {
public:
    static std::unique_ptr<Point> CreateTarget(float x, float y);
    static std::unique_ptr<Plane> CreatePlane(float health, float speed, const QString& model);
    static std::unique_ptr<SAM> CreateSAM(float health, const QString& model);
};

#endif // OBJECT_FACTORY_H
