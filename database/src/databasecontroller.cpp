#include "databasecontroller.h"

DatabaseController::DatabaseController()
{
    this->connection();
    dbWindow = new DataWindow;

     connect(dbWindow, SIGNAL(sig_typeTable_clicked(Table)), this,SLOT(slot_typeTable_clicked(Table)));
     connect(this, SIGNAL(sig_table(QSqlTableModel *)), dbWindow,SLOT(slot_table(QSqlTableModel *)));
     connect(dbWindow, SIGNAL(sig_addButton_clicked()), this,SLOT(slot_addButton_clicked()));
     connect(dbWindow, SIGNAL(sig_deleteButton_clicked()), this,SLOT(slot_deleteButton_clicked()));
     connect(dbWindow, SIGNAL(sig_tableView_clicked(const QModelIndex &)), this,SLOT(slot_tableView_clicked(const QModelIndex &)));
     connect(dbWindow, SIGNAL(sig_UserPressedEnterToSaveChanges()), this, SLOT(slot_userAddedData()));
     connect(this, SIGNAL(sig_block_db()), dbWindow,SLOT(slot_block_db()));
     connect(this, SIGNAL(sig_unblock_db()), dbWindow,SLOT(slot_unblock_db()));
}

int DatabaseController::connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("TECHNICALFEATURES.db");

    if (db.open())
    {
        qInfo() << "Database is open!";
        model = new QSqlTableModel(NULL,db);
        return 0;
    }
    else {
        qInfo() << "Can not open database! "<<db.lastError().databaseText();
        return -1;
    }


}

InfoAboutElement DatabaseController::select(Table table,int id)
{
    switch (table) {
    case AIRPLANS:
        return airplanTable->select(id);
        break;
    case ZRK:
        return zrkTable->select(id);
        break;
    default:
        return InfoAboutElement();
        break;
    }
}


QVector<InfoAboutElement> DatabaseController::select_all(Table table)
{
    QVector<InfoAboutElement> ans;
    switch (table) {
    case AIRPLANS:
        ans = airplanTable->select_all();
        rocketTable->select_all();
        break;
    case ZRK:
        ans = zrkTable->select_all();
        break;
    default:
        break;
    }
    return ans;
}

void DatabaseController::dataWindow_show()
{
    dbWindow->show();
}


void DatabaseController::slot_typeTable_clicked(Table table)
{
    switch (table)
    {
        case AIRPLANS:
            model->setTable("AIRPLANS");
            break;
        case ZRK:
            model->setTable("ZRK");
            break;
        case ROCKET:
            model->setTable("ROCKET");
            break;
        case SPRITE:
            model->setTable("SPRITES");
            break;

        default:
            break;
    }

    model->select();
    emit sig_table(model);
}

void DatabaseController::slot_addButton_clicked()
{
    model->insertRow(model->rowCount());
    emit sig_addedToDb();
}

void DatabaseController::slot_deleteButton_clicked()
{
        model->removeRow(currentRow);
        model->select();
}

void DatabaseController::slot_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}


void DatabaseController::slot_userAddedData()
{
    emit sig_addedToDb();
}

void DatabaseController::slot_make_backup(std::vector<std::shared_ptr<Plane> > &planes, std::vector<std::shared_ptr<SAM> > &sams, std::vector<std::shared_ptr<Rocket> > &rockets)
{
    qInfo() << "test";
    std::vector<std::shared_ptr<SAM> > my_sams;
    my_sams.push_back(std::make_shared<SAM>(100, "test", 1000, std::make_unique<Point>(1,1)));
    my_sams.push_back(std::make_shared<SAM>(123, "smth", 123, std::make_unique<Point>(5,5)));
    //save sams
    QJsonArray sams_jsonArray;
    for (const auto& sam : my_sams) {
        QJsonObject jsonObj;
        jsonObj["health"] = sam->HEALTH();
        jsonObj["model"] = sam->MODEL();
        jsonObj["battery"] = sam->BATTERY();
        jsonObj["distance"] = sam->DISTANCE();
        jsonObj["x"] = sam->X();
        jsonObj["y"] = sam->Y();

        sams_jsonArray.append(jsonObj);
    }
    QJsonDocument sams_jsonDoc(sams_jsonArray);

    QFile sams_jsonFile("jsonData/sams.json");
    if (sams_jsonFile.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&sams_jsonFile);
        stream << sams_jsonDoc.toJson();
        sams_jsonFile.close();
    }
    //save planes
    QJsonArray planes_jsonArray;
    for (const auto& plane : planes) {
        QJsonObject jsonObj;
        jsonObj["health"] = plane->HEALTH();
        jsonObj["speed"] = plane->SPEED();
        jsonObj["angle"] = plane->Angle();
        jsonObj["model"] = plane->MODEL();
        jsonObj["x"] = plane->X();
        jsonObj["y"] = plane->Y();

        planes_jsonArray.append(jsonObj);
    }
    QJsonDocument planes_jsonDoc(planes_jsonArray);

    QFile planes_jsonFile("jsonData/planes.json");
    if (planes_jsonFile.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&planes_jsonFile);
        stream << planes_jsonDoc.toJson();
        planes_jsonFile.close();
    }


}
void DatabaseController::slot_block_db()
{
    emit sig_block_db();
}

void DatabaseController::slot_unblock_db()
{
    emit sig_unblock_db();
}

QSqlDatabase DatabaseController::return_db()
{
    return db;
}

int DatabaseController::closing()
{
     db.close();
     qInfo() << "Database is closed!";

     return 0;
}
