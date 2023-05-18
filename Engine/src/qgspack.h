#ifndef QGSPACK_H
#define QGSPACK_H

class QGSPack{
public:
    QGSPack(double x, double y, double angle, int id);
    double X() const;
    double Y() const;
    double Angle() const;
    int Id() const;
private:
    double x_;
    double y_;
    double angle_;
    int id_;
};

#endif
