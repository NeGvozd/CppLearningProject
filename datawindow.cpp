#include "datawindow.h"
#include "ui_datawindow.h"

DataWindow::DataWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataWindow)
{
    ui->setupUi(this);


    //dbController.select(AIRPLANS,0);//test
    //dbController.select(ZRK,1);//test
}

DataWindow::~DataWindow()
{
    delete ui;
}

void DataWindow::on_planeButton_clicked()
{
    ui->planeButton->setEnabled(false);
    ui->zrkButton->setEnabled(true);
    dbController.model->setTable("AIRPLANS");
    dbController.model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setModel(dbController.model);
}

void DataWindow::on_zrkButton_clicked()
{
    ui->zrkButton->setEnabled(false);
    ui->planeButton->setEnabled(true);
    dbController.model->setTable("ZRK");
    dbController.model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setModel(dbController.model);
}

void DataWindow::on_addButton_clicked()
{
    dbController.model->insertRow(dbController.model->rowCount());
}

void DataWindow::on_deleteButton_clicked()
{
    dbController.model->removeRow(currentRow);
    dbController.model->select();
}

void DataWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}
