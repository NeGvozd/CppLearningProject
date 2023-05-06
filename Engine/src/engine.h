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

//Один тик таймера - 15 минут
//Один км - 0.0115 в числах

class Engine : public QObject {
    Q_OBJECT
public:
    Engine();
    ~Engine() = default;

    void startRenderCycle();
    void pauseRenderCycle();    
signals:
    void planeCreated();
    void samCreated();
    void sendObjects(QVector<QPair<double, double>>* sendSams, QVector<QList<double>>* sendPlanes);
public slots:
    void createNewObject(InfoAboutElement element);
    void addLine(QVector<QPair<double, double>>* linePoints);
    void addSAM(double x, double y);
    void addPlane(QVector<QPair<double, double>>* points);
private slots:
    void packObjects();
    void moveObjects();
private:
    std::vector<std::unique_ptr<Plane>> planes = std::vector<std::unique_ptr<Plane>>(0);
    std::vector<std::unique_ptr<SAM>> sams = std::vector<std::unique_ptr<SAM>>(0);
    std::vector<std::vector<Point*>> allLines;

    QTimer* timer;
    QTimer* sendTimer;
};

#endif
