#include "ObjectFactory.h"


std::unique_ptr<Point> ObjectFactory::CreateTarget(float x, float y) {
    return std::make_unique<Point>(x, y);
}

std::unique_ptr<Plane> CreatePlane(float health, float speed, const QString& model,
                                    const std::shared_ptr<QVector<Point>> tragectory) {
    return std::make_unique<Plane>(health, speed, model, tragectory);
}

std::unique_ptr<SAM> CreateSAM(float health, const QString& model, float distance, Point* location) {
    return std::make_unique<SAM>(health, model, distance, location);
}
