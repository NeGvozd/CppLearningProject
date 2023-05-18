#include "jsondata.h"


JsonData::JsonData(std::vector<std::shared_ptr<Plane> > & _planes, std::vector<std::shared_ptr<SAM> > & _sams):
    planes{_planes}, sams{_sams}
{}

void JsonData::save()
{
    save_planes();
    save_sams();
    qInfo() << "Data was saved";
}

QVector<InfoAboutElement> JsonData::return_sams()
{
    QVector<InfoAboutElement> vec;
    QFile jsonFile("jsonData/sams.json");
    QString json_string;
    if (jsonFile.open(QIODevice::ReadWrite))
    {
        QTextStream file_text(&jsonFile);
        json_string = file_text.readAll();
        jsonFile.close();
    }
    else
    {
        qWarning() << "Failed to open file for reading.";
    }

    QByteArray json_bytes = json_string.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);
    auto json_array = json_doc.array();
    for(int i = 0;i < json_array.size();i++)
    {
        auto json_obj = json_array[i].toObject();
        //тут надо дописать мб новые поля которые нужно сохранять аналогично
        int health = json_obj["health"].toInt();
        QString model = json_obj["model"].toString();
        qInfo() << model;
        int battery = json_obj["battery"].toInt();
        int distance = json_obj["distance"].toInt();
        int x = json_obj["x"].toInt();
        int y = json_obj["y"].toInt();
        //append to vec

    }

    return vec;
}

QVector<InfoAboutElement> JsonData::return_planes()
{
    QVector<InfoAboutElement> vec;
    QFile jsonFile("jsonData/planes.json");
    QString json_string;
    if (jsonFile.open(QIODevice::ReadWrite))
    {
        QTextStream file_text(&jsonFile);
        json_string = file_text.readAll();
        jsonFile.close();
    }
    else
    {
        qWarning() << "Failed to open file for reading.";
    }

    QByteArray json_bytes = json_string.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);
    auto json_array = json_doc.array();
    for(int i = 0;i < json_array.size();i++)
    {
        auto json_obj = json_array[i].toObject();
        //тут надо дописать мб новые поля которые нужно сохранять аналогично
        int health = json_obj["health"].toInt();
        QString model = json_obj["model"].toString();
        qInfo() << model;
        int speed = json_obj["speed"].toInt();
        int angle = json_obj["angle"].toInt();
        int x = json_obj["x"].toInt();
        int y = json_obj["y"].toInt();

        //std::make_shared<QVector<std::shared_ptr<Point> >>(unpack_tragectory(json_obj["tragectory"]));
        //append to vec
        std::shared_ptr<QVector<std::shared_ptr<Point> > > vec = unpack_tragectory(json_obj["tragectory"].toString());
    }
    return vec;
}
void JsonData::save_sams()
{
    QJsonArray jsonArray;
    for (const auto& sam : sams) {
        //тут надо дописать мб новые поля которые нужно сохранять
        QJsonObject jsonObj;
        jsonObj["health"] = sam->HEALTH();
        jsonObj["model"] = sam->MODEL();
        jsonObj["battery"] = sam->BATTERY();
        jsonObj["distance"] = sam->DISTANCE();
        jsonObj["x"] = sam->X();
        jsonObj["y"] = sam->Y();

        jsonArray.append(jsonObj);
    }
    QJsonDocument jsonDoc(jsonArray);

    QFile jsonFile("jsonData/sams.json");
    if (jsonFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&jsonFile);
        stream << jsonDoc.toJson();
        jsonFile.close();
    }
}

void JsonData::save_planes()
{
    QJsonArray planes_jsonArray;
    for (const auto& plane : planes) {
        //тут надо дописать мб новые поля которые нужно сохранять
        QJsonObject jsonObj;

        jsonObj["health"] = plane->HEALTH();
        jsonObj["speed"] = plane->SPEED();
        jsonObj["angle"] = plane->Angle();
        jsonObj["model"] = plane->MODEL();
        jsonObj["x"] = plane->X();
        jsonObj["y"] = plane->Y();

        jsonObj["tragectory"] = pack_tragectory(plane->TRAGECTORY());

        planes_jsonArray.append(jsonObj);
    }
    QJsonDocument jsonDoc(planes_jsonArray);

    QFile jsonFile("jsonData/planes.json");
    if (jsonFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&jsonFile);
        stream << jsonDoc.toJson();
        jsonFile.close();
    }
}

QString JsonData::pack_tragectory(std::shared_ptr<QVector<std::shared_ptr<Point> > > vec)
{
    QJsonArray jsonArray;
    for (const auto& p : *vec) {
        QJsonObject jsonObj;
        jsonObj["x"] = p->X();
        jsonObj["y"] = p->Y();

        jsonArray.append(jsonObj);
    }

    QJsonDocument tragectory_jsonDoc(jsonArray);
    QString jsonString = tragectory_jsonDoc.toJson(QJsonDocument::Compact);
    //qInfo() << jsonString;

    return jsonString;
}

std::shared_ptr<QVector<std::shared_ptr<Point> > >  JsonData::unpack_tragectory(QString tragectory)
{
    QVector<std::shared_ptr<Point> >  vec;
    QByteArray json_bytes = tragectory.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);
    auto json_array = json_doc.array();
    for(int i = 0;i < json_array.size();i++)
    {
        auto json_obj = json_array[i].toObject();
        float x = json_obj["x"].toDouble();
        float y = json_obj["y"].toDouble();
        vec.append(std::make_shared<Point>(x,y));
    }

    return std::make_shared<QVector<std::shared_ptr<Point> >>(vec);
}
