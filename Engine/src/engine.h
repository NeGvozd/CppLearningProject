#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>
#include <vector>
#include "../../objects/src/point.h"
#include "../../objects/src/plane.h"
#include "../../objects/src/sam.h"
#include "../../objects/src/ObjectFactory.h"
#include <../../database.h>

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
private:
    std::vector<Plane*> planes;
    std::vector<SAM*> sams;

};

#endif
