#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>
#include <vector>

#include "../../objects/src/point.h"
#include "../../objects/src/plane.h"
#include "../../objects/src/sam.h"
#include "../../objects/src/ObjectFactory.h"
#include "../../database/src/database.h"

#pragma once

class Engine : public QObject {
    Q_OBJECT
public:
    Engine();
    ~Engine() = default;
signals:
    void planeCreated();
    void samCreated();
public slots:
    void createNewObject(InfoAboutElement element);
    void addLine(QVector<QPair<double, double>>* linePoints);
    void addSAM(double x, double y);
    void addPlane(int lineNumber);
private:
    std::vector<std::unique_ptr<Plane>> planes;
    std::vector<std::unique_ptr<SAM>> sams;
    std::vector<std::vector<Point*>> allLines;
};

#endif
