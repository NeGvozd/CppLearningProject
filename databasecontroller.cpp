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

}

int DatabaseController::connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/media/psf/Home/Downloads/QT_pr/CppLearningProject/database/tth.db");


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

int DatabaseController::select(Table table,int id)
{
    if(table == AIRPLANS)
    {
        airplanTable->select(id);
    }
    else if(table == ZRK)
    {
        zrkTable->select(id);
    }
    return 0;
}


QVector<InfoAboutElement> DatabaseController::select_all(Table table)
{
    QVector<InfoAboutElement> ans;
    if(table == AIRPLANS)
    {
        ans = airplanTable->select_all();
    }
    else if(table == ZRK)
    {
        ans = zrkTable->select_all();
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
        case AIRPLANS://???
            model->setTable("AIRPLANS");
            break;
        case ZRK:
            model->setTable("ZRK");
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
