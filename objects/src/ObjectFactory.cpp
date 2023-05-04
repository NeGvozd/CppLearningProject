#include "ObjectFactory.h"


std::unique_ptr<Point> ObjectFactory::CreateTarget(float x, float y) {
    return std::make_unique<Point>(x, y);
}

std::unique_ptr<Plane> ObjectFactory::CreatePlane(float health, float speed, const QString& model, Point coord) {
    return std::make_unique<Plane>(health, speed, model, coord);
}

std::unique_ptr<SAM> ObjectFactory::CreateSAM(float health, const QString& model, float distance, Point coord) {
    return std::make_unique<SAM>(health, model, distance, coord);
}
