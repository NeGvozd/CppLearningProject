#ifndef SAM_H
#define SAM_H

#include <QDebug>
// #include <vector>

class Rocket;

class SAM {
public:
    SAM(float health, const QString& model);
    virtual ~SAM() = default;
    virtual void Fire() const;

protected:
    float health;
    QString model;
};

#endif // SAM_H
