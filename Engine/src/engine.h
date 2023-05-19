#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>
#include <vector>
#include "qgspack.h"

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

    void sendVectorsToDB();

private:
    void SAMscan(std::weak_ptr<Plane> plane);
    template<class T >
    QVector<QList<double>>* packObjects(std::vector<std::shared_ptr<T>>& vector);
signals:
    void planeCreated();
    void samCreated();
    void sendObjects(QVector<QList<double>>* sendPlanes, QVector<QList<double>>* sendRockets);
    void rocketCreated(double x, double y, int id);
    void createSAMCircles(double x, double y, double radius);
    void deleteRocket(int id);
    void sendRocketToList(int id, QString name, QString model, float damage, float speed, float range, float x, float y);
    void sendSAMToList(int id, QString name, QString model, float health, float distance, int ammo, float x, float y);
    void sendPlaneToList(int id, QString name, QString model, float health, float speed, float x, float y);
    void sendElementCoords(float x, float y);
    void deletePlane(int id);
    void sendPlaneId(int id);
    void loadSavedLines(QVector<QVector<QPair<double, double>>> lines, QVector<QList<double>> sendPlanes, QVector<QList<double>> sendSams);
    void sendDATA(std::vector<std::shared_ptr<Plane>> &planes, std::vector<std::shared_ptr<SAM>> &sams, std::vector<std::shared_ptr<Rocket>> &rockets);
public slots:
    void createNewObject(InfoAboutElement element);
    void addSAM(double x, double y);
    void addPlane(QVector<QPair<double, double>>* points);
    void getPlaneCoords(int id);
    void getRocketCoords(int id);
    void getSavedData(QPair<std::shared_ptr<QVector<std::shared_ptr<PacketToEngine_sams>>>, std::shared_ptr<QVector<std::shared_ptr<PacketToEngine_planes>>>> pair);
private slots:
    void packAllObjects();
    void moveObjects();
private:
    std::vector<std::shared_ptr<Plane>> planes;
    std::vector<std::shared_ptr<SAM>> sams;
    std::vector<std::shared_ptr<Rocket>> rockets;

    QTimer* timer;
    QTimer* sendTimer;
    int render_countdown = 0;

    InfoAboutElement lastelement_;
};

#endif
