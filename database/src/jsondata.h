#ifndef JSONDATA_H
#define JSONDATA_H
#include "../../objects/src/point.h"
#include "../../objects/src/plane.h"
#include "../../objects/src/rocket.h"
#include "../../objects/src/sam.h"
#include "database.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class JsonData
{
public:
    JsonData(std::vector<std::shared_ptr<Plane> >& _planes,
    std::vector<std::shared_ptr<SAM> >& _sams);

    void save();
    QVector<InfoAboutElement> return_sams();
    QVector<InfoAboutElement> return_planes();

private:
    std::vector<std::shared_ptr<Plane> > planes;
    std::vector<std::shared_ptr<SAM> > sams;

    void save_sams();
    void save_planes();
    QString pack_tragectory(std::shared_ptr<QVector<std::shared_ptr<Point> > > vec);
    std::shared_ptr<QVector<std::shared_ptr<Point> > >  unpack_tragectory(QString tragectory);



};

#endif // JSONDATA_H
