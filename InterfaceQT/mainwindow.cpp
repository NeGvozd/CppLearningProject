#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->WindowAddedItems->close();

   // QFileSystemModel *model = new QFileSystemModel;
   // model->setRootPath(QDir::currentPath());
   // ui->treeView->setModel(model);

    //added HELP menu with noHelp aaction
    QMenu *help = menuBar()->addMenu("HELP");
        QAction *noHelp = new QAction(tr("NO HELP"), this);
    help->addAction(noHelp);

    //add icons
    noHelp->setIcon(QIcon(":/rec/img/zrk.png"));

}

MainWindow::~MainWindow()
{
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
