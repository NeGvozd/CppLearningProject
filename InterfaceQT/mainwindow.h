#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QDockWidget>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionauthors_triggered();

    void on_actionExit_triggered();

    void on_dbButton_clicked();

    void on_addToBdButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_moveFromBdButton_clicked();

private:
    QSqlTableModel *model;
    Ui::MainWindow *ui;
    AirplansDB db;
    int currentRow;
};
#endif // MAINWINDOW_H
