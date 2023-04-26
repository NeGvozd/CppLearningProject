#include "SAM.h"
#include "Rocket.h"

SAM::SAM(float health, const QString& model) :
    health(health), model(model) {}

void SAM::Fire() const {
    /* Supposed example of usage
    Rocket rocket(100, 1000, 2000, nullptr);
    rocket.Launch();
    */
}
