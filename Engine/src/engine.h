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

    void startRenderCycle();
    void pauseRenderCycle();
private:
    double segmentLength(double x, double y);
    double segmentAngle(double x, double y);
    void moveObjects();
    
signals:
    void planeCreated();
    void samCreated();
public slots:
    void createNewObject(InfoAboutElement element);
    void addLine(QVector<QPair<double, double>>* linePoints);
    void addSAM(double x, double y);
    void addPlane(int lineNumber);
private:
    std::vector<std::pair<std::unique_ptr<Plane>, int>> planes;
    std::vector<std::unique_ptr<SAM>> sams;
    std::vector<std::vector<Point*>> allLines;

    QTimer* timer;
};

#endif
