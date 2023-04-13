#include "datawindow.h"
#include "ui_datawindow.h"
#include <QDebug>//
DataWindow::DataWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataWindow)
{
    ui->setupUi(this);

}

DataWindow::~DataWindow()
{
    delete ui;
}

void DataWindow::on_planeButton_clicked()
{
    ui->planeButton->setEnabled(false);
    ui->zrkButton->setEnabled(true);

    //emit sig_planeButton_clicked();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    //QSqlTableModel* model;
    //emit sig_return_model();

    //ui->tableView->setModel(model);//???
}

void DataWindow::on_zrkButton_clicked()
{
    ui->zrkButton->setEnabled(false);
    ui->planeButton->setEnabled(true);

    //emit sig_zrkButton_clicked();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    //QSqlTableModel* model;
    //emit sig_return_model();

    //ui->tableView->setModel(model);//???
}

void DataWindow::on_addButton_clicked()
{
    //emit sig_addButton_clicked();
}

void DataWindow::on_deleteButton_clicked()
{
    //emit sig_deleteButton_clicked();
}

void DataWindow::on_tableView_clicked(const QModelIndex &index)
{
    //emit sig_tableView_clicked(index);
}


void DataWindow::on_zalupa_clicked()
{
    qInfo() << "OH nOOOO!";
    emit sig_planeButton_clicked();
}
