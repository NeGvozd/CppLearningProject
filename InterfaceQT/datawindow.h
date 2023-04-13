#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QDialog>
#include "databasecontroller.h"

namespace Ui {
class DataWindow;
}

class DataWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataWindow(QWidget *parent = nullptr);
    ~DataWindow();

private slots:
    void on_planeButton_clicked();
    void on_zrkButton_clicked();

    void on_addButton_clicked();
    void on_deleteButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_zalupa_clicked();

signals:
    void signal();

public:
    Ui::DataWindow *ui;

public:
    DatabaseController dbController;
    int currentRow;
};

#endif // DATAWINDOW_H
