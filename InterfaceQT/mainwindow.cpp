#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbController.connection();
    //Connect viewTable with AirDB - is it true?
    model = new QSqlTableModel(this,dbController.return_db());

    //added HELP menu with noHelp aaction
    QMenu *help = menuBar()->addMenu("HELP");
    QAction *noHelp = new QAction(tr("NO HELP"), this);
    help->addAction(noHelp);

    //add icons
    noHelp->setIcon(QIcon(":/rec/img/zrk.png"));

}

MainWindow::~MainWindow()
{
    dbController.closing();
    delete ui;

}


void MainWindow::on_actionauthors_triggered()
{
        QMessageBox *msg = new QMessageBox;
        msg->setText(" Max1 \n Max2 \n Ilya \n Nikita \n Oleg");
        msg->exec();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_dbButton_clicked()
{
    model->setTable("AIRPLANS");
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->setModel(model);
}

void MainWindow::on_addToBdButton_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

void MainWindow::on_moveFromBdButton_clicked()
{
    model->removeRow(currentRow);
    model->select();
}
