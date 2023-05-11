#include "datawindow.h"
#include "ui_datawindow.h"
#include <QMessageBox>

void DataWindow::disabled_buttons(QPushButton * btn)
{
    QList<QPushButton *> buttons = findChildren<QPushButton *>();
    for (auto *but: buttons)
    {
        but->setEnabled(true);
    }
    btn->setEnabled(false);
}

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
    disabled_buttons(ui->planeButton);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    emit sig_typeTable_clicked(AIRPLANS);
}

void DataWindow::on_zrkButton_clicked()
{
    disabled_buttons(ui->zrkButton);
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


void DataWindow::on_rocketButton_clicked()
{
    disabled_buttons(ui->rocketButton);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    emit sig_typeTable_clicked(ROCKET);
}

void DataWindow::on_spriteButton_clicked()
{
    disabled_buttons(ui->spriteButton);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    emit sig_typeTable_clicked(SPRITE);
}

