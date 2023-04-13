#include "databasecontroller.h"

DatabaseController::DatabaseController()
{
    this->connection();
    dataWindow = new DataWindow;

    QObject::connect(dataWindow, SIGNAL(sig_planeButton_clicked()), this,SLOT(slot_planeButton_clicked()));
    //QObject::connect(dataWindow->ui->zalupa, SLOT(clicked()), this,&DatabaseController::slot_planeButton_clicked);
//    QObject::connect(dataWindow, &DataWindow::sig_zrkButton_clicked, this, &DatabaseController::slot_zrkButton_clicked);
//    QObject::connect(dataWindow, &DataWindow::sig_return_model, this,&DatabaseController::return_model);

    //QObject::connect(dataWindow, &DataWindow::sig_connection, this, &DatabaseController::connection);

//    QObject::connect(dataWindow, &DataWindow::sig_addButton_clicked, this, &DatabaseController::slot_addButton_clicked);
//    QObject::connect(dataWindow, &DataWindow::sig_deleteButton_clicked, this, &DatabaseController::slot_deleteButton_clicked);
//    QObject::connect(dataWindow, &DataWindow::sig_tableView_clicked, this, &DatabaseController::slot_tableView_clicked);

}


void DatabaseController::connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../CppLearningProject/database/tth.db");


    if (db.open())
    {
        qInfo() << "Database is open!";
        model = new QSqlTableModel(NULL,db);
    }
    else {
        qInfo() << "Can not open database! "<<db.lastError().databaseText();
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


void DatabaseController::slot_planeButton_clicked()
{
    qInfo() << "HEllo!";
//    model->setTable("AIRPLANS");
//    model->select();
}

//void DatabaseController::slot_zrkButton_clicked()
//{
//    model->setTable("ZRK");
//    model->select();
//}

//void DatabaseController::return_model()
//{
//     qInfo() << "I am here!";
//}

//QSqlDatabase DatabaseController::return_db()
//{
//    return db;
//}

//int DatabaseController::closing()
//{
//     db.close();
//     qInfo() << "Database is closed!";

//     return 0;
//}

//void DatabaseController::slot_addButton_clicked()
//{
//    model->insertRow(model->rowCount());
//}
//void DatabaseController::slot_deleteButton_clicked()
//{
//    model->removeRow(currentRow);
//    model->select();
//}
//void DatabaseController::slot_tableView_clicked(const QModelIndex &index)
//{
//    currentRow = index.row();
//}
