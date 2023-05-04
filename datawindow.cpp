#include "datawindow.h"
#include "ui_datawindow.h"
#include <QMessageBox>

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

void DataWindow::keyPressEvent(QKeyEvent *e)
{
    if ( (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
    {
        emit sig_UserPressedEnterToSaveChanges();
    }
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

void DataWindow::on_addButton_clicked(){
    QMessageBox m;
    m.information(nullptr, " ", " if you want to save changes in DataBase, press 'Enter' one more time after filling row \n You will reviece 'DataBase Updated'");

    emit sig_addButton_clicked();
}

void DataWindow::on_deleteButton_clicked()
{emit sig_deleteButton_clicked();}

void DataWindow::on_tableView_clicked(const QModelIndex &index)
{emit sig_tableView_clicked(index);}

void DataWindow::slot_table(QSqlTableModel *model)
{
    ui->tableView->setModel(model);
}
