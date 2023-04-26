#include "ObjectFactory.h"
#include "Point.h"
#include "Plane.h"
#include "SAM.h"

std::unique_ptr<Point> ObjectFactory::CreateTarget(float x, float y) {
    return std::make_unique<Point>(x, y);
}

std::unique_ptr<Plane> ObjectFactory::CreatePlane(float health, float speed, const std::string& model) {
    return std::make_unique<Plane>(health, speed, model);
}

std::unique_ptr<SAM> ObjectFactory::CreateSAM(float health, const std::string& model) {
    return std::make_unique<SAM>(health, model);
}
