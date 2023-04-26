#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <memory>
#include <string>

class Point;
class Plane;
class SAM;

class ObjectFactory {
public:
    static std::unique_ptr<Point> CreateTarget(float x, float y);
    static std::unique_ptr<Plane> CreatePlane(float health, float speed, const std::string& model);
    static std::unique_ptr<SAM> CreateSAM(float health, const std::string& model);
};

#endif // OBJECT_FACTORY_H
