#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>
#include <vector>

#include "../../objects/src/point.h"
#include "../../objects/src/plane.h"
#include "../../objects/src/rocket.h"
#include "../../objects/src/sam.h"
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
private:
    void SAMscane();
    template< class T >
    QVector<QList<double>>* packObjects(std::vector<std::shared_ptr<T>> vector);
signals:
    void planeCreated();
    void samCreated();
    void sendObjects(QVector<QList<double>>* sendSams, QVector<QList<double>>* sendPlanes, QVector<QList<double>>* sendRockets);
    void rocketCreated(double x, double y);
    void createSAMCircles(double x, double y, double radius);
public slots:
    void createNewObject(InfoAboutElement element);
    void addLine(QVector<QPair<double, double>>* linePoints);
    void addSAM(double x, double y);
    void addPlane(QVector<QPair<double, double>>* points);
private slots:
    void packAllObjects();
    void moveObjects();
private:
    std::vector<std::shared_ptr<Plane>> planes;
    std::vector<std::shared_ptr<SAM>> sams;
    std::vector<std::shared_ptr<Rocket>> rockets;
    std::vector<std::shared_ptr<Point>> allLines;

    QTimer* timer;
    QTimer* sendTimer;

    InfoAboutElement lastelement_;
};

#endif
