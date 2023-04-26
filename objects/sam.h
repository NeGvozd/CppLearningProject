#ifndef SAM_H
#define SAM_H

#include <string>
// #include <vector>

class Rocket;

class SAM {
public:
    SAM(float health, const std::string& model);
    virtual ~SAM() = default;
    virtual void Fire() const;

protected:
    float health;
    std::string model;
};

#endif // SAM_H
