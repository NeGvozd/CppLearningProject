#include "datawindow.h"
#include "ui_datawindow.h"

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
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    emit sig_typeTable_clicked(AIRPLANS);
}

void DataWindow::on_zrkButton_clicked()
{
    ui->zrkButton->setEnabled(false);
    ui->planeButton->setEnabled(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    emit sig_typeTable_clicked(ZRK);
}

void DataWindow::on_addButton_clicked()
{emit sig_addButton_clicked();}

void DataWindow::on_deleteButton_clicked()
{emit sig_deleteButton_clicked();}

void DataWindow::on_tableView_clicked(const QModelIndex &index)
{emit sig_tableView_clicked(index);}

void DataWindow::slot_table(QSqlTableModel *model)
{
    ui->tableView->setModel(model);
}

void DataWindow::slot_block_db()
{
    ui->addButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
}

void DataWindow::slot_unblock_db()
{
    ui->addButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
}
