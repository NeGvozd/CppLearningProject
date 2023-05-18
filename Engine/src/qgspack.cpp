#include "qgspack.h"

QGSPack::QGSPack(double x, double y, double angle, int id) : x_(x), y_(y), angle_(angle), id_(id) {};

double QGSPack::X() const {return x_;};
   
double QGSPack::Y() const {return y_;};
    
double QGSPack::Angle() const {return angle_;};
    
int QGSPack::Id() const {return id_;};